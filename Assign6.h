
/********************************************

CSCI 480 - Assignment 6
Progammer: Tim Dickens
Z-ID: z1804759
Section: 2
Date Due: April 10, 2019

Purpose: Header file containing relevant funtion names and class definitions

*******************************************/


#ifndef ASSIGN6_H
#define ASSIGN6_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <list>
#include <string>
#include <fstream>

#define KB 1024
#define MB KB * KB
#define HOW_OFTEN 5

using namespace std;

void bFitRun();
void fFitRun();
void printState();
void fFitLoad(string, string, string, string);
void bFitLoad(string, string, string, string);
void terminate(string);
void deallocate(string, string);

class Memory{
        public:
        int startLocation;
        int blockSize;
        string processID;
        string blockID;
        Memory(int newSize, int newAddress){
                this->blockSize = newSize;
                this->startLocation = newAddress;
        }
        Memory *previous = NULL;
        Memory *next = NULL;
};

list<Memory> Avail;
list<Memory> InUse;

void sortAvail(Memory);

#endif

