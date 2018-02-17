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
				// Look for non white space, non comment line and non line break.
				if(!currentCommand.empty() && !(currentCommand.find("//") == 0) && (currentCommand[0] != '\r'))
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

					//cout << currentCommand << endl;
				}
				else
				{
					//cout << "NO COMMAND: " << currentCommand << endl;
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
	
	if(isArithmeticCommand(currentCommand))
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
	string argument = s;
	if((pos = s.find(delimiter)) != string::npos)
	{
		argument = s.substr(0, pos);
	}
	
	if(!isArithmeticCommand(argument))
	{
		s.erase(0, pos + 1);
		if((pos = s.find(delimiter)) != string::npos)
		{
			argument = s.substr(0, pos);
		}
	}

	return argument;
}

int Parser::arg2(void)
{
	return 0;
}

bool Parser::isArithmeticCommand(std::string command)
{
	bool retVal = false;
	
	if(command.find("add") == 0)
	{
		retVal = true;
	}
	else if(command.find("sub") == 0)
	{
		retVal = true;
	}
	else if(command.find("neg") == 0)
	{
		retVal = true;
	}
	else if(command.find("eq") == 0)
	{
		retVal = true;
	}
	else if(command.find("gt") == 0)
	{
		retVal = true;
	}
	else if(command.find("lt") == 0)
	{
		retVal = true;
	}
	else if(command.find("and") == 0)
	{
		retVal = true;
	}
	else if(command.find("or") == 0)
	{
		retVal = true;
	}
	else if(command.find("not") == 0)
	{
		retVal = true;
	}
	
	return retVal;
}
