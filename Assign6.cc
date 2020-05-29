/********************************************

CSCI 480 - Assignment 6
Progammer: Tim Dickens
Z-ID: z1804759
Section: 2
Date Due: April 10, 2019

Purpose: A simulation of memory management using best fit and first fit algorithms

*******************************************/

#include "Assign6.h"

int start = 3 * MB;

/***************************************************

int main()

Returns: 0
Arguments: none

Purpose: Controls the main flow of the program, determining whether to use best fit or first fit algorithm,
and ensures the Available list is initialized with blocks of memory for use

***************************************************/

int main(){
	string check;
	cout << endl << "'B' for best fit and 'F' for first fit" << endl;
        cin >> check;
	cout << endl;
        if(check != "B" && check != "F"){
                cout << endl << "'B' for best fit and 'F' for first fit" << endl;
                exit (-1);
        }
        if(check == ""){
                cout << "Please enter at least one argument" << endl;
                exit(-1);
        }
	Avail.push_back(*(new Memory(MB, start)));
	start = start + MB;
        Avail.push_back(*(new Memory(2 * MB, start)));
        start = start + 2 * MB;
        Avail.push_back(*(new Memory(2 *MB, start)));
        start = start + 2 * MB;
        Avail.push_back(*(new Memory(4 * MB, start)));
        start = start + 4 * MB;
        Avail.push_back(*(new Memory(4 * MB, start)));
        start = start + 4 *MB;
    	if(check == "F"){
    		fFitRun();
	}
	else if(check == "B"){
		bFitRun();
	}
	return 0;
}

/***************************************************

void bFitRun()

Purpose: Simulation for Best Fit transaction checks the transaction, then calls the appropriate function
using a split string as parameters

***************************************************/

void bFitRun()
{
	ifstream inFile;
        inFile.open("data.txt");
        string line;
        string check;
        cout << "Memory Management Simulation for Best Fit Algorithm" << endl << endl;
        cout << "Beginning of the Run" << endl << endl;
        printState();
        string transaction;
        string processID;
        string blockSize;
        string blockID;

	//read the file and check transaction

        while(!inFile.eof()){
                getline(inFile, line);
                istringstream inStream(line);
                inStream >> transaction;
                check = transaction;
                if(check == "L" || check == "A"){
                        inStream >> processID >> blockSize >> blockID;
                        bFitLoad(transaction, processID, blockSize, blockID);
                }
                else if(check == "T"){
                        inStream >> processID;
                        terminate(processID);
                }
                else if(check == "D"){
                        inStream >> processID >> blockID;
                        deallocate(processID, blockID);
                }
                if(check != "?"){
                        printState();
                }
        }
        inFile.close();
        cout << "Run ended" << endl;
        printState();
}

/***************************************************

void fFitRun()

Purpose: Simulation for First Fit transaction checks the transaction, then calls the appropriate function
using a split string as parameters

***************************************************/


void fFitRun()
{
	ifstream inFile;
	inFile.open("data.txt");
	string line;
	string check;
	cout << "Memory Management Simulation for First Fit Algorithm" << endl << endl;
	cout << "Beginning of the Run" << endl << endl;
	printState();
	string transaction;
	string processID;
	string blockSize;
	string blockID;

	//read the file and check transaction

	while(!inFile.eof()){
		getline(inFile, line);
		istringstream inStream(line);
		inStream >> transaction;
		check = transaction;
		if(check == "L" || check == "A"){
		        inStream >> processID >> blockSize >> blockID;
			fFitLoad(transaction, processID, blockSize, blockID);
		}
		else if(check == "T"){
			inStream >> processID;
			terminate(processID);
		}
		else if(check == "D"){
			inStream >> processID >> blockID;
			deallocate(processID, blockID);
		}
		if(check != "?"){
			printState();
		}
	}
	inFile.close();
	cout << "Run ended" << endl;
	printState();
}

/***************************************************

void deallocate(string processID, string blockID)

Arguments: two strings representing the Block and Process ID which are used to find the block to deallocate

Purpose: Deletes the found block from the InUse list, and calls sortAvail to insert the memory back to Avail

***************************************************/


void deallocate(string processID, string blockID){
	list<Memory>::iterator Memiter;
	cout << "Transaction: request to deallocate Block ID " << blockID << " for process " << processID << endl;
        bool found = false;
        for( Memiter = InUse.begin(); Memiter != InUse.end(); Memiter++){
                if(Memiter->processID == processID && Memiter->blockID == blockID){
                        sortAvail(*(new Memory(Memiter->blockSize, Memiter->startLocation)));
                        InUse.erase(Memiter);
                        Memiter--;
                        found = true;
                }
        }
        if(found){
                cout << "Success in deallocating a block" << endl << endl;
        }
        else{
                cout << "Unable to comply: indicated process not found." << endl << endl;
        }

}

/***************************************************

void terminate(string processID)

Arguments: a strings representing the Process ID which is used to find the blocks to deallocate

Purpose: Deletes the found block from the InUse list, and calls sortAvail to insert the memory back to Avail

***************************************************/


void terminate(string processID){
	list<Memory>::iterator Memiter;
	cout << "Transaction: request to Terminate Process " << processID << endl;
	bool found = false;
	for( Memiter = InUse.begin(); Memiter != InUse.end(); Memiter++){
		if(Memiter->processID == processID){
			sortAvail(*(new Memory(Memiter->blockSize, Memiter->startLocation)));
			InUse.erase(Memiter);
			Memiter--;
			found = true;
		}
	}
	if(found){
		cout << "Success in terminating a process" << endl << endl;
	}
	else{
		cout << "Unable to comply: indicated process not found." << endl << endl;
	}
}

/***************************************************

void sortAvail(Memory memory)

Arguments: a memory object to return to avail

Purpose: Checks the avail list for the proper place to insert the memory, then merges blocks if applicable

***************************************************/


void sortAvail(Memory memory){
	list<Memory>::iterator Memiter;
	list<Memory>::iterator Memiter2;
	bool inserted = false;

	//find the spot for the block

	for(Memiter = Avail.begin(); inserted != true && Memiter != Avail.end(); Memiter++){
		if(Memiter->startLocation > memory.startLocation){
			Avail.insert(Memiter,memory);
			inserted = true;
		}
	}

	//if a spot wasn't found, push the memory back at the end

	if(!inserted){
		Memiter--;
		Avail.push_front(memory);
	}

	//merge blocks if applicable

	for(Memiter = Avail.begin(); Memiter != Avail.end(); Memiter++){
		Memiter2 = Memiter;
		Memiter2++;
		if((Memiter->blockSize + Memiter->startLocation) == Memiter2->startLocation){
			if((Memiter->blockSize + Memiter2->blockSize) <= 4 * MB) {
				cout << "Merging two blocks at " << Memiter->startLocation << " and " << Memiter2->startLocation << endl;
				Memiter->blockSize = Memiter->blockSize + Memiter2->blockSize;
				Avail.erase(Memiter2);
				Memiter--;
			}
		}
	}
}

/***************************************************

void bFitLoad(string transaction, string ProcessID, string blockSize, string blockID)

Arguments: four strings, which represent a transaction to carry out (either load or allocate),
a process and block ID to use for loading, and a block size to determine how much memory will be used

Purpose: Allocates memory for the best fit block of memory

***************************************************/

void bFitLoad(string transaction, string processID, string blockSize, string blockID){
	string procID = processID;
	string blocID = blockID;
	string size = blockSize;
	int intSize = atoi(blockSize.c_str());
        if(transaction == "L"){
                cout << "Transaction: request to Load Process " << procID << ", blockID: " << blocID << " using " << size << " bytes" << endl;
        }
        else{
                cout << "Transaction: request to Allocate " << size << " bytes for process " << procID << ", blockID: " << blocID << endl;
        }

	//set the minimum and found variables to values that always flag the first run

	list<Memory>::iterator Memiter;
	int minimum = 13 * MB;
	bool found = false;
	for(Memiter = Avail.begin(); Memiter != Avail.end() && found != true; Memiter++){

		//if the current block fits better than the last, and a block is found

		if((Memiter->blockSize - intSize) < minimum && (Memiter->blockSize - intSize) > 0){
			minimum = Memiter->blockSize - intSize;
			found = true;
		}
	}
	if(found){
		Memiter--;
		cout << "Found a block of size " << Memiter->blockSize << endl;
		Memiter->blockSize = Memiter->blockSize - intSize;
                Memory memory(intSize, Memiter->startLocation);
                Memiter->startLocation = Memiter->startLocation + intSize;
                memory.processID = processID;
                memory.blockID = blockID;
                if( Memiter->blockSize == 0 ){
                        Avail.erase(Memiter);
                }
                InUse.push_front(memory);
                cout << "Success in Allocating a block!" << endl << endl;
        }
        else{
                cout << "Unable to comply: no block of adequate size was available" << endl << endl;
        }
}


/***************************************************

void fFitLoad(string transaction, string ProcessID, string blockSize, string blockID)

Arguments: four strings, which represent a transaction to carry out (either load or allocate),
a process and block ID to use for loading, and a block size to determine how much memory will be used

Purpose: Allocates memory for the first fitting block of memory

***************************************************/


void fFitLoad(string transaction, string processID, string blockSize, string blockID){
	string procID = processID;
	string blocID = blockID;
	string size = blockSize;
	int intSize = atoi(blockSize.c_str());
	if(transaction == "L"){
		cout << "Transaction: request to Load Process " << procID << ", blockID: " << blocID << " using " << size << " bytes" << endl;
	}
	else{
	        cout << "Transaction: request to Allocate " << size << " bytes for process " << procID << ", blockID: " << blocID << endl;
	}

	//set found variable to a value that will always flag once

	bool found = false;
	list<Memory>::iterator Memiter;

	//find the first available block

	for(Memiter = Avail.begin(); found != true && Memiter != Avail.end(); Memiter++){
		if(Memiter->blockSize - intSize >= 0){
			found = true;
			cout << "Found a block of size " << Memiter->blockSize << endl;
		}
	}
	if(found){
		Memiter--;
		Memiter->blockSize = Memiter->blockSize - intSize;
		Memory memory(intSize, Memiter->startLocation);
		Memiter->startLocation = Memiter->startLocation + intSize;
		memory.processID = processID;
		memory.blockID = blockID;
		if( Memiter->blockSize == 0 ){
			Avail.erase(Memiter);
		}
		InUse.push_front(memory);
		cout << "Success in Allocating a block!" << endl << endl;
	}
	else{
		cout << "Unable to comply: no block of adequate size was available" << endl << endl;
	}
}


/***************************************************

void printState()

Purpose: Prints the available and in use lists after every transaction

***************************************************/


void printState(){
	list<Memory>::iterator Memiter;
	cout <<  "List of availale blocks:" << endl;
	int totalSize = 0;

	//print the Avail list

	if(Avail.size() == 0){
		cout << "(none)" << endl;
		cout << "Total Size of the List = " << totalSize << endl << endl;
	}
	else{
		for(Memiter = Avail.begin(); Memiter != Avail.end(); Memiter++){
			cout<<"Start Address =" << setw(9) << Memiter->startLocation;
			cout<<" Size =" << setw(8) << Memiter->blockSize << endl;
			totalSize = totalSize + Memiter->blockSize;
		}
		cout << "Total Size of the List = " << totalSize << endl << endl;
	}
	totalSize = 0;
        cout <<  "List of blocks in use:" << endl;

	//print the InUse list

	if(InUse.size() == 0){
		cout << "(none)" << endl;
		cout << "Total Size of the List = 0" << endl << endl;
	}
	else{
		for(Memiter = InUse.begin(); Memiter != InUse.end(); Memiter++){
			cerr<<"Start Address =" << setw(9) << Memiter->startLocation;
			cerr<<" Size =" << setw(8) << Memiter->blockSize;
			cerr<<" Process ID =" << setw(5) << Memiter->processID;
			cerr<<" Block ID =" << setw(6) << Memiter->blockID << endl;
			totalSize = totalSize + Memiter->blockSize;
		}
	cout << "Total Size of the List = " << totalSize << endl << endl;
	}
}
