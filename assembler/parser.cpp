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
				else if(currentCommand.find("//") == 0)	// Lock for comment
				{
					//cout << "  Comment" << endl;
				}
				else
				{
					hasMoreCmds = true;
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
	if(currentCommand.find("=") != string::npos)
	{
		retVal = C_COMMAND;
	}
	// Look for l command.
	if(currentCommand.find("(") == 0)
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
	
	return retVal.substr(0, retVal.find("="));
}

string Parser::comp()
{
	string retVal = currentCommand;
	
	return retVal.substr(retVal.find("=") + 1, retVal.find(";") - 2);
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