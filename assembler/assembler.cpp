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
	Parser parser("asm/Max.asm");
	ofstream outFile("Max.hack");
	Code code;
	SymbolTable symbolTable;
	int romAddress = 0;
	string output;
	
	// First pass.
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
				std::cout << romAddress << " @: " << parser.symbol() << std::endl;
				romAddress++;
			}
			else if (cmdType == L_COMMAND)
			{
				std::cout << " (): " << parser.symbol() << std::endl;
				symbolTable.addEntry(parser.symbol(), romAddress + 1);
			}
			else if(cmdType == C_COMMAND)
			{
				std::cout << romAddress << std::endl; 
				std::cout << " Dest: " << parser.dest() << std::endl;
				std::cout << " Comp: " << parser.comp() << std::endl;
				std::cout << " Jump: " << parser.jump() << std::endl;
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
	
	// Second pass.
	/*while(moreCommands)
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
				//output = "0" + bitset<15>(std::stoi(parser.symbol(),nullptr,10)).to_string();
				std::cout << "@: " << parser.symbol() << std::endl;
			}
			else if (cmdType == L_COMMAND)
			{
				std::cout << "(): " << parser.symbol() << std::endl;
			}
			else if(cmdType == C_COMMAND)
			{
				//output = "111" + code.comp(parser.comp()) + code.dest(parser.dest()) + code.jump(parser.jump());
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
				//outFile << output << "\n";
				outFile << parser.currentCommand << "\n";
			}
			else
			{
				std::cout << "Output file not open!" << std::endl;
				break;
			}
		}
	}*/
	
	outFile.close();
	
	return 0;
}