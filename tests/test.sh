#!/bin/bash
rm -rf git/
g++ main.cpp 
./a.out init
./a.out add test.sh
./a.out commit -m "first"
./a.out branch x
./a.out branch y
./a.out checkout y
touch y.txt
./a.out add y.txt
./a.out commit -m "second"
./a.out checkout x
touch x.txt
./a.out add x.txt
./a.out commit -m "third"