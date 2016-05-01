#pragma once

#include <fstream>
#include <string>

enum commandType 
{
	A_COMMAND,
	C_COMMAND,
	L_COMMAND
};

class Parser
{
	std::ifstream inputFile;
	std::string currentCommand;
	std::string lastReadLine;
	
	public:
	// Constructor
	Parser(std::string);
	
	// Member functions
	bool hasMoreCommands();
	void advance();
	commandType commandType();
	std::string symbol();
	std::string dest();
	std::string comp();
	std::string jump();
};