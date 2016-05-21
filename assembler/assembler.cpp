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
			//std::cout << std::endl << parser.currentCommand << std::endl;
			commandType_e cmdType = parser.commandType();
			//std::cout << cmdType << std::endl;
			if(cmdType == A_COMMAND)
			{
				//std::cout << romAddress << " @: " << parser.symbol() << std::endl;
				romAddress++;
			}
			else if (cmdType == L_COMMAND)
			{
				//std::cout << " (): " << parser.symbol() << std::endl;
				symbolTable.addEntry(parser.symbol(), romAddress);
			}
			else if(cmdType == C_COMMAND)
			{
				/*std::cout << romAddress << std::endl; 
				std::cout << " Dest: " << parser.dest() << std::endl;
				std::cout << " Comp: " << parser.comp() << std::endl;
				std::cout << " Jump: " << parser.jump() << std::endl;*/
				romAddress++;
			}
			
			/*if(outFile.is_open())
			{
				outFile << romAddress << " " << parser.currentCommand << "\n";
			}
			else
			{
				std::cout << "Output file not open!" << std::endl;
				break;
			}*/
		}
	}
	
	symbolTable.printSymbolTable();
	
	moreCommands = true;
	parser.resetInputFile();
	
	// Second pass.
	while(moreCommands)
	{
		parser.advance();
		moreCommands = parser.hasMoreCommands();
		if(moreCommands)
		{
			std::cout << std::endl << parser.currentCommand << std::endl;
			commandType_e cmdType = parser.commandType();
			//std::cout << cmdType << std::endl;
			if(cmdType == A_COMMAND)
			{
				string symbol = parser.symbol();
				//output = "0" + bitset<15>(std::stoi(symbol,nullptr,10)).to_string();
				std::cout << "@: " << symbol<< std::endl;
				// Look if number.
				if(symbol.find_first_not_of("0123456789") != std::string::npos)
				{	// Not a number.
					// Look if label.
					if(symbol.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") != std::string::npos)
					{	// Not a label.
						// Look if variable.
						if(symbol.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789_.") != std::string::npos)
						{	// Not a variable.
							std::cout << "Error not a valid symbol." << std::endl;
							break;
						}
						else // Was variable.
						{
							// Should be possible to simplify this...
							if(!symbolTable.contains(symbol))
							{
								symbolTable.addEntry(symbol, ramAddress);
								ramAddress++;
							}
							if(symbolTable.contains(symbol))
							{
								symbol = std::to_string(symbolTable.getAddress(symbol));
								std::cout << "Variable: " << symbol << std::endl;
							}
							else{
								std::cout << "No such symbol: " << symbol << std::endl;
							}
						}
					}
					else // Was label.
					{
						if(symbolTable.contains(symbol))
						{
							symbol = std::to_string(symbolTable.getAddress(symbol));
							std::cout << "Label: " << symbol << std::endl;
						}
						else{
							std::cout << "No such symbol: " << symbol << std::endl;
						}
					}
				}
				output = "0" + bitset<15>(std::stoi(symbol,nullptr,10)).to_string();
			}
			else if (cmdType == L_COMMAND)
			{
				std::cout << "(): " << parser.symbol() << std::endl;
				/*if(parser.symbol().find_first_not_of("0123456789") != std::string::npos)
				{
				}*/
			}
			else if(cmdType == C_COMMAND)
			{
				output = "111" + code.comp(parser.comp()) + code.dest(parser.dest()) + code.jump(parser.jump());
				//std::cout << " " << code.dest(parser.dest()) << std::endl;
				//std::cout << "  " << code.comp(parser.comp()) << std::endl;
				//std::cout << "   " << code.jump(parser.jump()) << std::endl;
				std::cout << "Dest: " << parser.dest() << std::endl;
				std::cout << "Comp: " << parser.comp() << std::endl;
				std::cout << "Jump: " << parser.jump() << std::endl;
			}
			
			if(outFile.is_open())
			{
				//std::cout << output << std::endl;
				if((cmdType != L_COMMAND) && (cmdType != NO_COMMAND))
				{
					std::cout << cmdType << std::endl;
					outFile << output << "\n";
				}
				//outFile << parser.currentCommand << "\n";
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