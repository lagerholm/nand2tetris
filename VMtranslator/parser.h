#pragma once

#include <fstream>
#include <string>

enum commandType_e 
{
	C_ARITHMETIC,
	C_PUSH,
	C_POP,
	C_LABEL,
	C_GOTO,
	C_IF,
	C_FUNCTION,
	C_RETURN,
	C_CALL,
	NO_COMMAND
};

class Parser
{
	public:
	std::string currentCommand;
	
	// Constructor
	Parser(std::string);
	
	// Member functions
	bool hasMoreCommands();
	void advance();
	commandType_e commandType();
	std::string arg1(void);
	int arg2(void);
	void resetInputFile();
	
	private:
	std::ifstream inputFile;
	bool hasMoreCmds;
	bool isArithmeticCommand();
};