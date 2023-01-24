# "24 Card Game" Solver

> A program that find all solution for "24 Card Game" using brute force algorithm.

## Table of Contents

- [General Info](#general-information)
- [Features](#features)
- [Usage](#usage)
- [Project Directories](#project-directories)
- [Author](#author)

## General Information

This program will find all solution for "24 Card Game" using brute force algorithm. This is one of the task in Algorithm Strategies course (IF2211) which intended to implement brute force algorithm in a program.

## Features

There are 2 menu that can be choosed:

- Input from keyboard
- Generate 4 random cards

Then, the program will do the brute force algorithm to find all solution from these card combination.

The program can also save the solution in a .txt file.

## Usage

Make sure the current directory is `Tucil1_13521071`

Run this command `./bin/24solver`

First, the program takes an input (1 or 2) for menu. If the user choose menu 1, the program will take four inputs for the cards. If the user choose menu 2, the program will generate four random cards. Then, the program will do the brute force for all permutation of the cards, operators, and precedence. After calculating all posibilities, the program will output the total and all solution that the program found, along with the time execution for the brute force algorithm. Next, the program will ask if we want to save the solution in a file and we can input the filename.

## Project Directories

```bash
Tucil1_13521071
│   README.md
│
├───bin
│       24solver.exe
│
├───doc
│       Tucil1_K1_13521071_Margaretha Olivia Haryono.pdf
│
├───src
│       24solver.cpp
│
└───test
        tc1.txt
        tc2.txt
        tc3.txt
        tc4.txt
        tc5.txt
        tc6.txt
        tc7.txt
        tc8.txt
        tc9.txt
        tc10.txt

```

## Author

Margaretha Olivia Haryono (13521071)
