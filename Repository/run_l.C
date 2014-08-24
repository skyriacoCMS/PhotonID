
#include <stdlib>
#include <TSystem.h>


void run_l(){

  gSystem->CompileMacro("CSA14_l.C");
  CSA14_l t; 
  

  t.Loop(); 
  
  
}
