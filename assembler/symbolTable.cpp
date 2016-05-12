#include <iostream>

#include "symbolTable.h"

SymbolTable::SymbolTable()
{
	// Create hash map.
	symbolTable["SP"] 		= 0x0000;
	symbolTable["LCL"] 		= 0x0001;
	symbolTable["ARG"] 		= 0x0002;
	symbolTable["THIS"] 	= 0x0003;
	symbolTable["THAT"] 	= 0x0004;
	symbolTable["R0"] 		= 0x0000;
	symbolTable["R1"] 		= 0x0001;
	symbolTable["R2"] 		= 0x0002;
	symbolTable["R3"] 		= 0x0003;
	symbolTable["R4"] 		= 0x0004;
	symbolTable["R5"] 		= 0x0005;
	symbolTable["R6"] 		= 0x0006;
	symbolTable["R7"] 		= 0x0007;
	symbolTable["R8"] 		= 0x0008;
	symbolTable["R9"] 		= 0x0009;
	symbolTable["R10"] 		= 0x000A;
	symbolTable["R11"] 		= 0x000B;
	symbolTable["R12"] 		= 0x000C;
	symbolTable["R13"] 		= 0x000D;
	symbolTable["R14"] 		= 0x000E;
	symbolTable["R15"] 		= 0x000F;
	symbolTable["SCREEN"]	= 0x4000;
	symbolTable["KBD"] 		= 0x6000;
}

void SymbolTable::printSymbolTable(void)
{
	for( const auto& n : symbolTable ) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
}

void SymbolTable::addEntry(std::string symbol, int address)
{
	symbolTable[symbol] = address;
}

bool SymbolTable::contains(std::string symbol)
{
	auto search = symbolTable.find(symbol);
	if(search != symbolTable.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int SymbolTable::getAddress(std::string symbol)
{
	return symbolTable[symbol];
}
