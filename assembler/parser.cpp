#include "parser.h"

#include <iostream>

using namespace std;

Parser::Parser(string input):inputFile(input.c_str()){};

bool Parser::hasMoreCommands()
{
	bool retVal = false;
	string lastReadLine;
	bool commandFound = false;
	
	if(inputFile.is_open())
	{
		while (!commandFound)
		{
			if(getline(inputFile, lastReadLine))
			{
				if(lastReadLine.empty())
				{
					cout << "White space" << endl;
				}
				else if(lastReadLine.find("//") == 0)	// Lock for comment
				{
					cout << "Comment" << endl;
				}
				else
				{
					commandFound = true;
					retVal = true;
				}
			}
			else if(inputFile.eof())
			{
				retVal = false;
				cout << "End of file!" << endl;
				break;
			}
			else
			{
				cout << "Error when reading from file" << endl;
				break;
			}
		}
	}
	else
	{
		cout << "No file was open!" << endl;
	}
	
	return retVal;
}
