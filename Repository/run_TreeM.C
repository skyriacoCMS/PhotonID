
#include <stdlib>
#include <TSystem.h>


void run_TreeM(){

  gSystem->CompileMacro("CutID.C");
  CutID t; 


  // 0- c, 1- n , 2 - p

  double efa[7][3];
  int CoB; 
  cout<<"This treemaker will take the effective areas from this file ./EfArea/EffectiveAreas.txt"<<endl;
  cout<<"                  "<<endl;
  cout<<" 1 - for continue ; other for stop"<<endl;
  cin>>CoB; 
  if(CoB != 1 ) goto endd; 

  ifstream myfile; 
  myfile.open("./EfArea/EffectiveAreas.txt");



  int indx = 0; 
  if(myfile.is_open()){
    while(!myfile.eof()){
      myfile>>efa[indx][0]>>efa[indx][1]>>efa[indx][2];
      
      indx ++;
    }
  }
  cout<<"Succesfully parsed the effective Areas"<<endl;
  
  t.CutBasedID(1,efa);
  t.CutBasedID(2,efa);

  

 endd:  
  if(CoB != 1 )cout<<"Tree Maker did not run"<<endl;



}
