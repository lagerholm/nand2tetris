#include <iostream>
#include <string>
#include <bitset>

#include "parser.h"
#include "code.h"

using std::string;
using std::bitset;

int main()
{
	bool moreCommands = true;
	Parser parser("add.asm");
	Code code;
	string output;
	
	while(moreCommands)
	{
		moreCommands = parser.hasMoreCommands();
		if(moreCommands)
		{
			parser.advance();
			//std::cout << parser.currentCommand << std::endl;
			commandType_e cmdType = parser.commandType();
			//std::cout << "  " << cmdType << std::endl;
			if(cmdType == A_COMMAND)
			{
				output = "0" + bitset<15>(std::stoi(parser.symbol(),nullptr,10)).to_string();
				std::cout << output << std::endl;
				//std::cout << "    " << parser.symbol() << std::endl;
			}
			else if (cmdType == L_COMMAND)
			{
				std::cout << "Not supported yet" << std::endl;
			}
			else if(cmdType == C_COMMAND)
			{
				output = "111" + code.comp(parser.comp()) + code.dest(parser.dest()) + code.jump(parser.jump());
				std::cout << output << std::endl;
				//std::cout << "    " << code.dest(parser.dest()) << std::endl;
				//std::cout << "      " << code.comp(parser.comp()) << std::endl;
				//std::cout << "      " << code.jump(parser.jump()) << std::endl;
				//std::cout << "    " << parser.dest() << std::endl;
				//std::cout << "      " << parser.comp() << std::endl;
				//std::cout << "        " << parser.jump() << std::endl;
			}
		}
	}
		
	return 0;
}