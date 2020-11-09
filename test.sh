#!/bin/bash
rm -rf git/
./a.out init
./a.out add ab.txt
./a.out commit -m "first"
./a.out branch other
./a.out checkout other
./a.out add i.txt
./a.out commit -m "second"
./a.out checkout master
./a.out checkout other
./a.out checkout master
./a.out checkout other
./a.out checkout master
./a.out checkout other
./a.out checkout master
./a.out checkout other