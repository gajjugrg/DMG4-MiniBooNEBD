#!/bin/bash

SOURCE_FILES=ebrem*.root
#check if a copy of final file is present

TARGET_FILE=dm_mass_0.100_bias_1e3_Ethres_0.010_pot_1e6.root
if [ -e $TARGET_FILE ] ; then
   rm -r $TARGET_FILE
fi

hadd $TARGET_FILE $SOURCE_FILES

echo "Merging all files into a single root file $TARGET_FILE" 

#after completely merging the files and rm all rootfiles
if [ -e $TARGET_FILE ] ; then
   echo "Deleting all source files in the directory"
   rm -f $SOURCE_FILES
fi
#mv $TARGET_FILE /cluster/home/ggurung/outputfiles/slices/
