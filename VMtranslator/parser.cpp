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
					
					cout << currentCommand << endl;
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
	
	if(isArithmeticCommand())
	{
		retVal = C_ARITHMETIC;
	}
	else if(currentCommand.find("push") == 0)
	{
		retVal = C_PUSH;
	}
	else if(currentCommand.find("pop") == 0)
	{
		retVal = C_POP;
	}
	else if(currentCommand.find("label") == 0)
	{
		retVal = C_LABEL;
	}
	else if(currentCommand.find("goto") == 0)
	{
		retVal = C_GOTO;
	}
	else if(currentCommand.find("if") == 0)
	{
		retVal = C_IF;
	}
	else if(currentCommand.find("function") == 0)
	{
		retVal = C_FUNCTION;
	}
	else if(currentCommand.find("return") == 0)
	{
		retVal = C_RETURN;
	}
	else if(currentCommand.find("call") == 0)
	{
		retVal = C_CALL;
	}

	return retVal;
}

void Parser::resetInputFile()
{
	inputFile.clear();
	inputFile.seekg(0, inputFile.beg);
}

string Parser::arg1(void)
{
	string s = currentCommand;
	string delimiter = " ";
	
	size_t pos = 0;
	string argument;
	while ((pos = s.find(delimiter)) != string::npos)
	{
		argument = s.substr(0, pos);
		cout << argument << " : " << s << endl;
		s.erase(0, pos+delimiter.length());
		cout << argument << " : " << s << endl;
	}
	cout << argument << " : " << s <<  endl;
	
	return argument;
}

int Parser::arg2(void)
{
	return 0;
}

bool Parser::isArithmeticCommand()
{
	bool retVal = false;
	
	if(currentCommand.find("add") == 0)
	{
		retVal = true;
	}
	else if(currentCommand.find("sub") == 0)
	{
		retVal = true;
	}
	else if(currentCommand.find("neg") == 0)
	{
		retVal = true;
	}
	else if(currentCommand.find("eq") == 0)
	{
		retVal = true;
	}
	else if(currentCommand.find("gt") == 0)
	{
		retVal = true;
	}
	else if(currentCommand.find("lt") == 0)
	{
		retVal = true;
	}
	else if(currentCommand.find("and") == 0)
	{
		retVal = true;
	}
	else if(currentCommand.find("or") == 0)
	{
		retVal = true;
	}
	else if(currentCommand.find("not") == 0)
	{
		retVal = true;
	}
	
	return retVal;
}
