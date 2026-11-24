#!/bin/bash
# Input/output redirection and pipes
printf "banana\napple\ncherry\napple\n" > fruits.txt
cat fruits.txt
sort < fruits.txt > sorted.txt
cat sorted.txt
echo "mango" >> fruits.txt
wc -l < fruits.txt
sort fruits.txt | uniq
cat fruits.txt | grep "an" | wc -l
ls nofile 2> error.txt
cat error.txt
