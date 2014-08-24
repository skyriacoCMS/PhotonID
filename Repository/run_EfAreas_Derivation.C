#include <Fitter.C>
#include <stdlib>
#include <TSystem.h>
#include <TableWriter.C>

void run_EfAreas_Derivation(){
  //-----------------Macro Describtion----------------------------------------------------------
  //
  // This macro wraps the whole procedure in a single shell. 
  // Initialy it caluclates the effective areas -macros (AreaCalc.C + Fitter.C) 
  // and then feed them in a Tree Maker, that makes a Tree with the variables of interest 
  // separated to background/signal and weight based on the pt, for possible MVA techinques 
  // and to derive the cuts. 
  // This file to run, needs the full construction of the CUTID class and also the extra macros
  // for each of the specified process. 
  //
  //--------------------------------------------------------------------------------------------

  gSystem->CompileMacro("CutID.C");
  CutID t; 
  
  // here you declare the number of eta  bins 

  double isoP,isoN,isoC;
  ofstream myfile; 
  myfile.open("./EfAreas/EffectiveAreas.txt");
 



  cout<<"------------------------------------------------------------"<<endl;
  cout<<"Creating the bins and retrieving the effective area for each"<<endl;
  cout<<"-----------------------------------------------------------"<<endl;


  //First Bin
  double emin =0; 
  double emax =1;
  t.ArCalc(emin,emax,1);
  Fitter(0,1,1,isoP,isoC,isoN);
  if(isoC < 0) isoC =0; 
  if(isoN < 0) isoN =0; 
  if(isoP < 0) isoP =0; 
  myfile<<isoC<<" "<<isoN<<" "<<isoP<<endl;

  //Second Bin
  emin =1; 
  emax =1.479;
  t.ArCalc(emin,emax,2);  
  Fitter(emin,emax,2,isoP,isoC,isoN);
  if(isoC < 0) isoC =0; 
  if(isoN < 0) isoN =0; 
  if(isoP < 0) isoP =0; 
  myfile<<isoC<<" "<<isoN<<" "<<isoP<<endl;
  

  //Third Bin
  emin = 1.479;
  emax = 2.0;
  t.ArCalc(emin,emax,3);
  Fitter(emin,emax,3,isoP,isoC,isoN);
  if(isoC < 0) isoC =0; 
  if(isoN < 0) isoN =0; 
  if(isoP < 0) isoP =0; 
  myfile<<isoC<<" "<<isoN<<" "<<isoP<<endl;


   cout<<"              ----- 4"<<endl;

  //Fourth Bin
  emin = 2.0;
  emax = 2.2;
  t.ArCalc(emin,emax,4);
  Fitter(emin,emax,4,isoP,isoC,isoN);
  if(isoC < 0) isoC =0; 
  if(isoN < 0) isoN =0; 
  if(isoP < 0) isoP =0; 
  myfile<<isoC<<" "<<isoN<<" "<<isoP<<endl;

   cout<<"              ----- 5"<<endl;


  //Fifth Bin
  emin = 2.2;
  emax = 2.3;
  t.ArCalc(emin,emax,5);
  Fitter(emin,emax,5,isoP,isoC,isoN);
  if(isoC < 0) isoC =0; 
  if(isoN < 0) isoN =0; 
  if(isoP < 0) isoP =0;  
  myfile<<isoC<<" "<<isoN<<" "<<isoP<<endl;

   cout<<"              ----- 6"<<endl;


  //Sixth Bin
  emin = 2.3;
  emax = 2.4;
  t.ArCalc(emin,emax,6);
  Fitter(emin,emax,6,isoP,isoC,isoN);
  if(isoC < 0) isoC =0; 
  if(isoN < 0) isoN =0; 
  if(isoP < 0) isoP =0;  
  myfile<<isoC<<" "<<isoN<<" "<<isoP<<endl;



  cout<<"              ----- 7"<<endl;

  //Seventh Bin
  emin = 2.4;
  emax = 5;
  t.ArCalc(emin,emax,7);
  Fitter(emin,emax,7,isoP,isoC,isoN);
  if(isoC < 0) isoC =0; 
  if(isoN < 0) isoN =0; 
  if(isoP < 0) isoP =0;  
  myfile<<isoC<<" "<<isoN<<" "<<isoP<<endl;
  myfile.close();



}
