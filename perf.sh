#!/bin/bash

echo Projet parallèlisation 
make all 
cd bin

echo -e "\nExemple satisfiable non paralléliser \n"
time ./solver.exe satisfiable

echo -e "\nExemple non satisfiable non paralléliser \n"
time ./solver.exe insatisfiable


echo -e "\nExemple satisfiable paralléliser \n"
time ./psolver.exe satisfiable


echo -e "\nExemple non satisfiable paralléliser \n"
time ./psolver.exe insatisfiable
exit 0