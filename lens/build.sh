#!/bin/sh
. ../owshell.sh
wcl -bcl=DOS -ml -6 -fp6 -ox lens.cpp
export exit_code=$?
if [ $exit_code -ne 0 ] ; then
    echo "Compilation failed"
else
    dosbox lens.exe -exit
fi


