#!/bin/bash
rm -rf git/
g++ main.cpp -lz
./a.out init
./a.out add ab.txt
./a.out commit -m "first"
./a.out branch other
./a.out checkout other
./a.out add test.sh
./a.out commit -m "second"