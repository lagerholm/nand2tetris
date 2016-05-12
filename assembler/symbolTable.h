#pragma once

#include <string>
#include <unordered_map>

class SymbolTable
{
	std::unordered_map<std::string, int> symbolTable;

	public:
	// Constructor
	SymbolTable();
	
	// Member functions
	void printSymbolTable(void);
	void addEntry(std::string, int);
	bool contains(std::string);
	int getAddress(std::string);
};