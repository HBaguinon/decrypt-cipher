/*******************************************************************************
* NAME: HAROLD DANE C. BAGUINON                                                *
* DATE: 02/06/2016                                                             *
* DATE DUE: 02/11/2016 11:59:00 PM                                             *
* COURSE: CSC555 010                                                           *
* PROFESSOR: DR. ZHANG                                                         *
* PROJECT: #1                                                                  *
* FILENAME: decrypt.cpp                                                        *
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

using namespace std;

// wordRec is the struct which will contain each letter with its mapping.
struct wordRec
{
    char letter;
    char keyLetter;
};

// Functions used ...
/*
	Function name: initMap
	Description: Initializes the map array which contains the key letter
                 mapping, using an array of structs. The initial values are the
                 letter and an asterisk to show that no new letter has been
                 mapped.
	Parameters: wordRec map[]: The array which stores the key letter mapping.
	Return Value: None.
*/
void initMap(wordRec[]);

/*
	Function name: printMap
	Description: Prints the map array which contains the key letter mapping.
	Parameters: wordRec map[]: The array which stores the key letter mapping.
	Return Value: None.
*/
void printMap(wordRec[]);

/*
	Function name: editMap
	Description: Allows the user to change the mapping of letters and alters the
                 ciphertext with each new mapping.
	Parameters: wordRec map[]: The array which stores the key letter mapping.
                char cipher[]: The array which stores the message (ciphertext).
                int items: The integer whose value is the message length.
	Return Value: None.
*/
void editMap(wordRec[], char[], int);

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
    Function name: readMessage
    Description: Reads the message into an array of characters and increments
                 the count of each character added.
    Parameters: ifstream &inf: The variable to use ifstream.
                char cipher[]: The array which stores the message (ciphertext).
                int &items: The integer whose value is the message length.
    Return Value: None.
*/
void readMessage(ifstream&, char[], int&);

/*
	Function name: printMessage
	Description: Prints all of the characters in the array which contains the
                 ciphertext message. Letters are all capitalized initially.
	Parameters: char cipher[]: The array which stores the message (ciphertext).
				int &items: The integer whose value is the message length.
	Return Value: None.
*/
void printMessage(char cipher[], int items);

/*
    Function name: menu                                                        
    Description: Displays menu choices, prompting the user to type a single    
                 character as input in order to choose which menu option to    
                 select. Once an option is executed, the menu appears again,   
                 unless Q is chosen, which would quit the program. Input is not
                 case sensitive.                                               
    Parameters: None.                                                          
    Return Value: char SelectedCharacter: Export; returns input from user.            
*/
char menu();

/*
    Function name: regulateOutput                                              
    Description: Regulates the output based on user input from the menu.                     
    Parameters: wordRec map[]: The array which stores the key letter mapping.
                char cipher[]: The array which stores the message (ciphertext).
                int items: The integer whose value is the message length.
    Return Value: None.                                                        
*/
void regulateOutput(wordRec[], char[], int);

int main() {
    ifstream inf;
    string fileName;
    char cipher[1000];
    int items = 0;
    wordRec map[26];
    
    initMap(map);
    openFile(inf, fileName);
    readMessage(inf, cipher, items);
    printMessage(cipher, items);
    printMap(map);
    regulateOutput(map, cipher, items);
    inf.close();
    return 0;
}

/*
	Function name: initMap
	Description: Initializes the map array which contains the key letter
                 mapping, using an array of structs. The initial values are the
                 letter and an asterisk to show that no new letter has been
                 mapped.
*/
void initMap(wordRec map[])
{
    char letter = 'A';
    for (int i = 0; i < 26; i++)
    {
        map[i].letter = letter;
        map[i].keyLetter = '*';
        letter++;
    }
}

/*
	Function name: printMap
	Description: Prints the map array which contains the key letter mapping.
*/
void printMap(wordRec map[])
{
    cout << "Key: " << endl;
	for (int x = 0; x < 26; x++)
	{
        cout << map[x].letter;
	}
    cout << "\n";
    for (int x = 0; x < 26; x++)
	{
        cout << map[x].keyLetter;
	}
    cout << "\n";
    //cout << "\n********************" << endl;
}

/*
	Function name: editMap
	Description: Allows the user to change the mapping of letters and alters the
                 ciphertext with each new mapping.
*/
void editMap(wordRec map[], char cipher[], int items)
{
    char subLet;
    char newLet;
    char input;
    cout << "Which letter would you like to change? " << endl;
    cin >> input;
    subLet = toupper(input);
    cout << "You entered letter " << subLet << endl;
    cout << "What letter would you like to change it to?" << endl;
    cin >> input;
    newLet = tolower(input);
	for (int x = 0; x < 26; x++)
	{
        if (map[x].letter == subLet)
            map[x].keyLetter = newLet;
	}
    cout << "\n";
    for (int x = 0; x < items; x++)
	{
        if (cipher[x] == subLet)
            cipher[x] = newLet;
	}
    cout << "\n";
    cout << "Ciphertext has been changed." << endl;
    printMessage(cipher, items);
    cout << "Key mapping has been changed." << endl;
    printMap(map);
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
    Function name: readMessage
    Description: Reads the message into an array of characters and increments
                 the count of each character added.
*/
void readMessage(ifstream &inf, char cipher[], int &items)
{
    char nextCh;
    
    nextCh = inf.get();
    while (!inf.eof())
    {
        cipher[items] = toupper(nextCh);
        nextCh = inf.get();
        items++;
    }
}

/*
	Function name: printMessage
	Description: Prints all of the characters in the array which contains the
                 ciphertext message. Letters are all capitalized initially.
*/
void printMessage(char cipher[], int items)
{
    cout << "\n----------------------" << endl;
    cout << "CIPHERTEXT: " << endl;
	for (int x = 0; x < items; x++)
	{
        cout << cipher[x];
	}
    cout << "\n----------------------" << endl;
}

/*
    Function name: menu                                                        
    Description: Displays menu choices, prompting the user to type a single    
                 character as input in order to choose which menu option to    
                 select. Once an option is executed, the menu appears again,   
                 unless Q is chosen, which would quit the program. Input is not
                 case sensitive.                                               
*/
char menu()
{
  char SelectedCharacter;
  cout << "PLEASE ENTER A CHOICE: \n";
  cout << "A) Print message (ciphertext)" << endl;
  cout << "B) Print letter mapping" << endl;
  cout << "C) Edit letter mapping" << endl;
  cout << "Q) Quit" << endl;
  cin >> SelectedCharacter;
  return SelectedCharacter;
}

/*
    Function name: regulateOutput                                               
    Description: Regulates the output based on user input.                      
*/
void regulateOutput(wordRec map[], char cipher[], int items)
{ 
  char inputCharacter=menu();
  while (inputCharacter!='Q' && inputCharacter!='q')
    {
      switch(inputCharacter)
        {
        case 'a':
        case 'A':
          printMessage(cipher, items);
          break;
        case 'b':
        case 'B':
          printMap(map);
          break;
        case 'c':
        case 'C':
          editMap(map, cipher, items);
          break;
        default:
          cout<<"\n";
          cout<<"Error: Invalid Entry"<<endl;
          break;
        }
      inputCharacter=menu();
    }
}