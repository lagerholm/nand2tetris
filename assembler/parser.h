#pragma once

#include <fstream>
#include <string>

enum commandType_e 
{
	A_COMMAND,
	C_COMMAND,
	L_COMMAND,
	NO_COMMAND
};

class Parser
{
	std::ifstream inputFile;
	bool hasMoreCmds;
	
	public:
	std::string currentCommand;
	
	// Constructor
	Parser(std::string);
	
	// Member functions
	bool hasMoreCommands();
	void advance();
	commandType_e commandType();
	std::string symbol();
	std::string dest();
	std::string comp();
	std::string jump();
};