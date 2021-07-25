@echo off 
gen >in.txt
main <in.txt >out.txt
brute <in.txt >ok.txt
FC ok.txt out.txt
if errorlevel 1 exit
run