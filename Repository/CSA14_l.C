#define CSA14_l_cxx
#include "CSA14_l.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <TMath.h>
#include <vector>
#include <TVector3.h>

void CSA14_l::Loop()
{
  TFile *f1 = new TFile("SingleMatchPhoton_20to40.root","recreate");
  TTree *t1 = new TTree("t1","EventsTree");
  float gedPhEta,gedPhPt,gedPhPhi,gedPhoIso,gedChgIso,gedNeuIso,gedPhTower,gedPhSieie,gedPhisPrompt,Rho,gedPhweightXS;
  float gedPhSieie2012,gedGenPt;
  int gedPhPixSeed,NVtx; 
  TH2D *RvsPV = new TH2D("RvsPV","Rho versus primary vertices",70,0,70,4500,0,450);

  t1->Branch("Rho",&Rho,"Rho/F");
  t1->Branch("NVtx",&NVtx,"NVtx/I");  
  t1->Branch("gedPhEta",&gedPhEta,"gedPhEta/F");
  t1->Branch("gedPhPhi",&gedPhPhi,"gedPhPhi/F");
  t1->Branch("gedPhPt",&gedPhPt,"gedPhPt/F");
  t1->Branch("gedPhSieie",&gedPhSieie,"gedPhSieie/F");
  t1->Branch("gedPhSieie2012",&gedPhSieie2012,"gedPhSieie2012/F");
  t1->Branch("gedPhTower",&gedPhTower,"gedPhTower/F");
  t1->Branch("gedPhisPrompt",&gedPhisPrompt,"gedPhisPrompt/F");
  t1->Branch("gedPhoIso",&gedPhoIso,"gedPhoIso/F");
  t1->Branch("gedChgIso",&gedChgIso,"gedChgIso/F");
  t1->Branch("gedNeuIso",&gedNeuIso,"gedNeuIso/F");
  t1->Branch("gedGenPt",&gedGenPt,"gedGenPt/F");
  t1->Branch("gedPhPixSeed",&gedPhPixSeed,"gedPhPixSeed/F");
  t1->Branch("gedPhweightXS",&gedPhweightXS,"gedPhweightXS/F");

  int sigg = 0;
  int bckk = 0;

  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  double weightt1 = 17180*0.038*100000.0/(nentries*5.35989);

  cout<<"weight of  this sample "<<weightt1<<endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    
    if(jentry % 100000 == 0)cout<<jentry<<endl;
    RvsPV->Fill(nVtx,rho);
        
    for(uint ipho = 0; ipho < (*phoEt).size(); ipho++){
      double pEta = (*phoEta)[ipho]; 
      double pPhi = (*phoPhi)[ipho]; 
    	
      Rho = rho;
      NVtx = nVtx;
      gedPhPt = (*phoEt)[ipho];
      gedPhEta = pEta; 
      gedPhPhi = pPhi;
      gedPhSieie = (*phoSigmaIEtaIEta)[ipho];
      gedPhSieie2012 = (*phoSigmaIEtaIEta2012)[ipho];
      gedPhTower   = (*phoHoverE)[ipho];
      gedPhoIso = (*phoPFPhoIso)[ipho];
      gedChgIso = (*phoPFChIso)[ipho];
      gedNeuIso = (*phoPFNeuIso)[ipho];
      gedPhPixSeed  = (*phohasPixelSeed)[ipho];
      gedPhweightXS = weightt1;
      
      // (1.0/0.001776);
      
      int pass = 0;
      double genPt = -1;
      int firstPh = 0; 
      
      for(uint imc = 0; imc < (*mcPID).size(); imc++){
	double msts = (*mcStatus)[imc];
	
	if((msts != 1)&&((*mcPID)[imc] != 22)&&(firstPh))continue;
	
	if((abs((*mcMomPID)[imc]) !=21) && (abs((*mcMomPID)[imc]) !=1)&&(abs((*mcMomPID)[imc]) !=2)&&(abs((*mcMomPID)[imc]) !=3)&&(abs((*mcMomPID)[imc]) !=4)&&(abs((*mcMomPID)[imc]) !=5)&&(abs((*mcMomPID)[imc]) !=6))continue;
	
	firstPh = 1; 
	double meta = (*mcEta)[imc];
	double mphi = (*mcPhi)[imc];	  
	
	TVector3 mcphoton;
	TVector3 recoPHOTOn;
	
	mcphoton.SetPtEtaPhi(1.0,meta,mphi);
	recoPHOTOn.SetPtEtaPhi(1.0,pEta,pPhi);			       
	double DR = mcphoton.DrEtaPhi(recoPHOTOn);
	
	
	if(DR < 0.1 ){
	  pass = 1; 
	  genPt = (*mcPt)[imc];
	  break;
	}	
      }//EOF MC Particles loop 
      gedPhisPrompt = pass;
      gedGenPt = genPt; 
      if(gedPhisPrompt) sigg ++;
      if(gedPhisPrompt == 0) bckk ++;
      
      t1->Fill();
    }//EOF Photon Loop
    
    
  }//EOF EVENT LOOP 
  
   cout<<"SIGNAL   "<<sigg <<endl;
   cout<<"background   "<<bckk <<endl;


   RvsPV->Write();   
   TCanvas *c1  = new TCanvas("c1","Rho profile.",700,700);
   c1->Divide(2,1);
   c1->cd(1);
   RvsPV->Draw();   
   c1->cd(2);
   t1->Write();
}

