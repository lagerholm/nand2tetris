#pragma once

#include <string>

class SymbolTable
{
	// Constructor
	SymbolTable();
	
	// Member functions
	void addEntry(std::string, int);
	bool contains(std::string);
	int getAddress(std::string);
};