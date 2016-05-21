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
				//cout << currentCommand << endl;
				if(currentCommand.empty())
				{
					//cout << "  White space" << endl;
				}
				else if(currentCommand.find("//") == 0)	// Lock for starting comment
				{
					//cout << "  Comment" << endl;
				}
				else
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

string Parser::symbol()
{
	string retVal = currentCommand;
	
	if(commandType() == A_COMMAND)
	{
			retVal.erase(retVal.begin());
			//cout << retVal << endl;
	}
	else if(commandType() == L_COMMAND)
	{
			retVal.erase(retVal.begin());
			retVal.erase(retVal.end() - 1);
	}
	
	return retVal;
}

string Parser::dest()
{
	string retVal = currentCommand;
	if(retVal.find("=") != string::npos)
	{
		retVal = retVal.substr(0, retVal.find("="));
	}
	else 
	{
		retVal = "";
	}
	
	return retVal;
}

string Parser::comp()
{
	string retVal = currentCommand;
	if(retVal.find("=") != string::npos)
	{
		retVal = retVal.substr(retVal.find("=") + 1, retVal.find(";") - 2);
	}
	else
	{
		retVal = retVal.substr(0, retVal.find(";"));
	}
	
	return retVal;
}

string Parser::jump()
{
	string retVal = currentCommand;
	size_t found = retVal.find(";");
	if(found != string::npos)
	{
		return retVal.substr(found + 1, retVal.length() - 1);
	}
	else 
	{
		return "";
	}
}

void Parser::resetInputFile()
{
	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);
}
