#include <iostream>

#include "parser.h"
#include "code.h"

int main()
{
	bool moreCommands = true;
	Parser parser("add.asm");
	Code code;
	
	while(moreCommands)
	{
		moreCommands = parser.hasMoreCommands();
		if(moreCommands)
		{
			parser.advance();
			std::cout << parser.currentCommand << std::endl;
			commandType_e cmdType = parser.commandType();
			std::cout << "  " << cmdType << std::endl;
			if((cmdType == A_COMMAND) || (cmdType == L_COMMAND))
			{
				std::cout << "    " << parser.symbol() << std::endl;
			}
			else if(cmdType == C_COMMAND)
			{
				std::cout << "    " << code.dest(parser.dest()) << std::endl;
				//std::cout << "    " << parser.dest() << std::endl;
				//std::cout << "      " << parser.comp() << std::endl;
				//std::cout << "        " << parser.jump() << std::endl;
			}
		}
	}
		
	return 0;
}