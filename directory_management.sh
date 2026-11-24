#!/bin/bash
# Directory management commands: cd, mkdir, rmdir, ls
mkdir -p project
cd project || exit 1
pwd
cd ..
mkdir -p demo/sub
ls
ls -l demo
rmdir demo/sub
rmdir demo
ls
