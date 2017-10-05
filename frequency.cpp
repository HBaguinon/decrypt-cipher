/*******************************************************************************
* NAME: HAROLD DANE C. BAGUINON                                                *
* DATE: 02/06/2016                                                             *
* DATE DUE: 02/11/2016 11:59:00 PM                                             *
* COURSE: CSC555 010                                                           *
* PROFESSOR: DR. ZHANG                                                         *
* PROJECT: #1                                                                  *
* FILENAME: frequency.cpp                                                      *
* PURPOSE: This program is the first project. The purpose of the project is to *
*          decrypt a message which was encrypted using a monoalphabetic cipher.*
*          The first program will read in the ciphertext file and analyze it   *
*          for the frequency of letters. The second program will allow the user*
*          to manually decrypt the message by substituing individual letters in*
*          the ciphertext, eventually leading to the decrypted message.        *
*******************************************************************************/

#include <iostream>				// for i/o functions
#include <fstream>				// for external file streams
#include <cstdlib>				// for EXIT_FAILURE
#include <string>				// for string objects
#include <algorithm>			// for swap 
using namespace std;

// wordRec is the struct which will contain each letter with its occurrence.
struct wordRec
{
    char letter;
    int occurrence;
};

// Functions used ...
/*
	Function name: openFile
	Description: Opens the file and outputs an error message if the file does
				 not exist. Ask user for file name. Read into parameter
                 fileName.
	Parameters: ifstream &inf: The variable to use ifstream.
				string &fileName: The name of the file. - input
	Return Value: None.
*/
void openFile(ifstream&, string&);

/*
    Function name: countChars
    Description: Counts the characters found in the text file and prints out
                 the total number of characters (letters only) and commas.
    Parameters: ifstream &inf: The variable to use ifstream.
                int &totalChars: Total number of letters.
    Return Value: None.
*/
void countChars(ifstream&, int&);
/*
	Function name: selSort
	Description: Sorts the letters in the array and removes duplicates,
				 increasing the counter for each individual letter.
	Parameters: wordRec list[]: The array which stores the letters and counts.
				int &items: The maximum number of letters to process.
	Return Value: None.
*/
void selSort(wordRec list[], int &items);

/*
	Function name: freqSort
	Description: Sorts the letters in the array based on frequency. This is 
                 still just an experimental function. Not used in submission.
	Parameters: wordRec list[]: The array which stores the letters and counts.
				int &items: The maximum number of letters to process.
	Return Value: None.
*/
void freqSort(wordRec list[], int &items);

/*
	Function name: reopenFile
	Description: Reopens the file.
	Parameters: ifstream &inf: The variable to use ifstream.
				string &fileName: The name of the file. - input
	Return Value: None.
*/
void reopenFile(ifstream&, string&);

/*
	Function name: readTokens
	Description: Reads the file and inputs each letter into an array of wordRec
				 structs, with the count of each letter set to 1.
	Parameters: ifstream &inf: The variable to use ifstream.
				wordRec list[]: The array which stores the letters and counts.
				int &items: The maximum number of letters to process.
	Return Value: None.
*/
void readTokens(ifstream&, wordRec list[], int &items);

/*
	Function name: printAll
	Description: Prints all of the letters in the array with the corresponding
                 occurrence (count) of each letter.
	Parameters: wordRec list[]: The array which stores the letters and counts.
				int &items: The maximum number of letters to process.
	Return Value: None.
*/
void printAll(wordRec list[], int items, int totalChars);

int main() {
    ifstream inf;
    string fileName;
    wordRec list[1000];
    int items = 0;
    int totalChars = 0;
    
    openFile(inf, fileName);
    countChars(inf, totalChars);
    reopenFile(inf, fileName);
    readTokens(inf, list, items);
    selSort(list, items);
    // freqSort(list, items);              EXPERIMENTAL FUNCTION. COMMENT OUT.
    cout << "Frequency analysis for " << fileName << ": \n";
    printAll(list, items, totalChars);
    return 0;
}

/*
	Function name: openFile
	Description: Opens the file and outputs an error message if the file does
				 not exist. Ask user for file name. Read into parameter
                 fileName.
*/
void openFile(ifstream &inf, string &fileName)
{
	cout << "Please input the name of the file you want to open: " << endl;
	cin >> fileName;
	inf.open(fileName.c_str());
	
	if (inf.fail())
	{
		cerr << "I'm sorry. The file doesn't exist." << endl;
		return;
	}
}

/*
    Function name: countChars
    Description: Counts the characters found in the text file and prints out
                 the total number of characters (letters only) and commas.
*/
void countChars(ifstream &inf, int &totalChars)
{
    char nextCh;
    int charCount = 0;
    int commaCount = 0;
    int periodCount = 0;
    int spaceCount = 0;
    
    nextCh = inf.get();
    while (!inf.eof())
    {
        cout << nextCh;
        if (nextCh == ' ')
            spaceCount++;
        else if (nextCh == ',')
            commaCount++;
        else if (nextCh == '.')
            periodCount++;
        else
            charCount++;
        nextCh = inf.get();
    }
    totalChars = charCount;
    cout << "\nLetter count: " << totalChars << ", Comma count: " << commaCount
         << endl;
}

/*
	Function name: reopenFile
	Description: Reopens the file.
*/
void reopenFile(ifstream &inf, string &fileName)
{
	inf.close();
	inf.clear();
	inf.open(fileName.c_str());
}

/*
	Function name: readTokens
	Description: Reads the file and inputs each letter into an array,
				 with the occurrence set to 1.
*/

// Read tokens into an array of wordRec struct
void readTokens(ifstream &inf, wordRec list[], int &items)
{
	char inputChar;
	
	while (items < 1000 && inf >> inputChar)
	{
		list[items].letter = inputChar;
		list[items].occurrence = 1;
		items++;
	}
	cout << "********************" << endl; 
}

/*
	Function name: selSort
	Description: Sorts the letters in the array and removes duplicates,
				 increasing the counter for each individual letter.
*/
void selSort(wordRec list[], int &items)
{
	for (int spot = 0; spot < items; spot++)
	{
		int idxMin = spot;
		for (int idx = spot; idx < items; idx++)
		{
			if (list[idx].letter < list[idxMin].letter)
				idxMin = idx;
			//spot--;
		}
		if (spot > 0 && list[spot-1].letter == list[idxMin].letter)
		{
			list[spot-1].occurrence++;
			swap(list[idxMin], list[items-1]);
			items--;
			spot--;
		}
		else if (idxMin != spot)
			swap(list[idxMin], list[spot]);
	}	// for spot
}

/*
	Function name: freqSort
	Description: Sorts the letters in the array based on frequency. This is 
                 still just an experimental function. Not used in submission.
*/
void freqSort(wordRec list[], int &items)
{
	for (int spot = 0; spot < items; spot++)
	{
		int idxMin = spot;
		for (int idx = spot; idx < items; idx++)
		{
			if (list[idx].occurrence > list[idxMin].occurrence)
				idxMin = idx;
			//spot--;
		}
		if (spot > 0 && list[spot-1].occurrence == list[idxMin].occurrence)
		{
			//list[spot-1].occurrence++;
			//swap(list[idxMin], list[items-1]);
			//items--;
			//spot--;
		}
		else if (idxMin != spot)
			swap(list[idxMin], list[spot]);
	}	// for spot
}

/*
	Function name: printAll
	Description: Prints all of the letters in the array with the corresponding
                 occurrence (count) of each letter.
*/
void printAll(wordRec list[], int items, int totalChars)
{
    double frequency;
    cout << "(character: frequency)" << endl;
	for (int x = 0; x < items; x++)
	{
        frequency = (double)list[x].occurrence/(double)totalChars*100;
		cout << "(" << list[x].letter << ": " << frequency << "%)" << endl;
	}
    cout << "********************" << endl;
}