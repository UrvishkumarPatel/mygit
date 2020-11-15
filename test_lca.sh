#!/bin/bash
rm -rf git/
g++ main.cpp 
./a.out init
./a.out add test_lca.sh
./a.out commit -m "first"
./a.out add test.sh
./a.out commit -m "second"
./a.out branch x
./a.out branch y
./a.out checkout y
touch y.txt
./a.out add y.txt
./a.out commit -m "y_0"
touch y1.txt
./a.out add y1.txt
./a.out commit -m "y_1"
./a.out checkout x
touch x.txt
./a.out add x.txt
./a.out commit -m "x_0"
touch x1.txt
./a.out add x1.txt
./a.out commit -m "x_1"