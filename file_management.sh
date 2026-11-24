#!/bin/bash
# File management commands: cat, cp, rm, mv, cmp, comm, diff, find, grep, awk
# Run this script in a disposable directory because it creates and removes files.

printf "Rahul 85\nAman 72\nPriya 91\nNeha 64\n" > students.txt
cat students.txt
cp students.txt backup.txt
mv backup.txt marks.txt
cmp students.txt marks.txt

printf "Aman 72\nNeha 64\nRahul 85\nPriya 91\nZoya 77\n" > list2.txt
cmp students.txt list2.txt

sort students.txt > s1.txt
sort list2.txt > s2.txt
comm s1.txt s2.txt
diff students.txt list2.txt
find . -name "*.txt"
grep "Priya" students.txt
awk '{sum += $2} END {print "Total =", sum}' students.txt

rm marks.txt s1.txt s2.txt
ls
