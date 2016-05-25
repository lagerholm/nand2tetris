#include "parser.h"

#include <iostream>

using namespace std;

Parser::Parser(string input):inputFile(input.c_str()), hasMoreCmds(true){}

bool Parser::hasMoreCommands()
{

	return hasMoreCmds;
}

void Parser::advance()
{
	hasMoreCmds = false;
	
	if(inputFile.is_open())
	{
		while (!hasMoreCmds)
		{
			if(getline(inputFile, currentCommand))
			{
				// Look for non white space and non comment line.
				if(!currentCommand.empty() && !(currentCommand.find("//") == 0))
				{
					hasMoreCmds = true;
					// Trim the command.
					// Remove leading white space.
					size_t found = currentCommand.find_first_not_of(" \t\n\r\f\v");
					if(found != string::npos)
					{
						currentCommand.erase(0, found);
					}
					// Remove comments.
					found = currentCommand.find("//");
					if(found != string::npos)
					{
						currentCommand.erase(found);
					}
					// Remove trailing white space.
					found = currentCommand.find_last_not_of(" \t\n\r\f\v");
					if(found != string::npos)
					{
						currentCommand.erase(found + 1);
					}
				}
			}
			else if(inputFile.eof())
			{
				currentCommand = "";
				cout << "End of file!" << endl;
				break;
			}
			else
			{
				currentCommand = "";
				cout << "Error when reading from file" << endl;
				break;
			}
		}
	}
	else
	{
		cout << "No file was open!" << endl;
	}
	
}

commandType_e Parser::commandType()
{
	commandType_e retVal = NO_COMMAND;
	
	// Look for a command.
	if(currentCommand.find("@") == 0)
	{
		retVal = A_COMMAND;
	}
	// Look for c command.
	else if((currentCommand.find("=") != string::npos) || (currentCommand.find(";") != string::npos))
	{
		retVal = C_COMMAND;
	}
	// Look for l command.
	else if(currentCommand.find("(") == 0)
	{
		retVal = L_COMMAND;
	}
	return retVal;
}

void Parser::resetInputFile()
{
	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);
}
