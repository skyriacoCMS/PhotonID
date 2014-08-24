#!/usr/bin/env python
import os
import shutil
import subprocess
import sys

os.system("root -l -q run.C")
os.system("root -l -q run_l.C")
os.system("hadd 20INF.root SingleMatchPhoton_20to40.root SingleMatchPhoton_40.root")

os.system("root -l -q run_EfAreas_Derivation.C")
os.system("root -l -q run_TreeM.C")
 
print " the Trainning Samples are generated Please change the directory in the condor submiting files as to match their current location  "

os.system("root -l ./BAR/Trainer/Scr99.C")
os.system("root -l ./END/Trainer/Scr99.C")

os.system("condor_submit ./BAR/Trainer.jcl")
os.system("condor_submit ./END/Trainer.jcl")

print "---jobs submited---- GA Trainnign initiated "
