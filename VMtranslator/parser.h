#pragma once

#include <fstream>
#include <string>

#include "common.hpp"

class Parser
{
	public:
	// Constructor
	Parser(std::string);
	
	// Member functions
	bool hasMoreCommands();
	void advance();
	CommandType commandType();
	bool commandHasArg2(void);
	std::string arg1(void);
	int arg2(void);
	void resetInputFile();
	
	private:
	std::string currentCommand;
	std::ifstream inputFile;
	std::string argument1;
	int argument2;
	bool hasMoreCmds;
	bool isArithmeticCommand(std::string);
	void findArguments(std::string);
};