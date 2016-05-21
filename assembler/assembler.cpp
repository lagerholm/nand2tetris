#include <iostream>
#include <string>
#include <bitset>

#include "parser.h"
#include "code.h"
#include "symbolTable.h"

using std::string;
using std::bitset;
using std::ofstream;

int main()
{
	bool moreCommands = true;
	Parser parser("asm/Pong.asm");
	ofstream outFile("Pong.hack");
	Code code;
	SymbolTable symbolTable;
	int romAddress = 0;
	int ramAddress = 16;
	string output;
	
	// First pass.
	while(moreCommands)
	{
		parser.advance();
		moreCommands = parser.hasMoreCommands();
		if(moreCommands)
		{
			commandType_e cmdType = parser.commandType();
			if(cmdType == A_COMMAND)
			{
				romAddress++;
			}
			else if (cmdType == L_COMMAND)
			{
				symbolTable.addEntry(parser.symbol(), romAddress);
			}
			else if(cmdType == C_COMMAND)
			{
				romAddress++;
			}
		}
	}
	
	// Second pass. Reset.
	moreCommands = true;
	parser.resetInputFile();
	
	while(moreCommands)
	{
		parser.advance();
		moreCommands = parser.hasMoreCommands();
		if(moreCommands)
		{
			commandType_e cmdType = parser.commandType();
			if(cmdType == A_COMMAND)
			{
				string symbol = parser.symbol();
	
				// Look if number.
				if(symbol.find_first_not_of("0123456789") != std::string::npos)
				{	// Not a number.
					if(!symbolTable.contains(symbol))
					{
						symbolTable.addEntry(symbol, ramAddress);
						ramAddress++;
					}
					if(symbolTable.contains(symbol))
					{
						symbol = std::to_string(symbolTable.getAddress(symbol));
					}
					else{
						std::cout << "No such symbol: " << symbol << std::endl;
					}
				}
				output = "0" + bitset<15>(std::stoi(symbol,nullptr,10)).to_string();
			}
			else if(cmdType == C_COMMAND)
			{
				output = "111" + code.comp(parser.comp()) + code.dest(parser.dest()) + code.jump(parser.jump());
			}
			
			if(outFile.is_open())
			{
				if((cmdType != L_COMMAND) && (cmdType != NO_COMMAND))
				{
					outFile << output << "\n";
				}
			}
			else
			{
				std::cout << "Output file not open!" << std::endl;
				break;
			}
		}
	}
	
	outFile.close();
	
	return 0;
}