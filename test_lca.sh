#!/bin/bash
rm -rf git/
make 
./mygit init
./mygit add test_lca.sh
./mygit commit -m "first"
./mygit add test.sh
./mygit commit -m "second"
./mygit branch x
./mygit branch y
./mygit checkout y
touch y.txt
./mygit add y.txt
./mygit commit -m "y_0"
touch y1.txt
./mygit add y1.txt
./mygit commit -m "y_1"
./mygit checkout x
touch x.txt
./mygit add x.txt
./mygit commit -m "x_0"
touch x1.txt
./mygit add x1.txt
./mygit commit -m "x_1"
