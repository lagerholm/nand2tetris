#include <iostream>

#include "parser.h"

int main()
{
	bool moreCommands = true;
	Parser parser("add.asm");
	
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
				std::cout << "    " << parser.dest() << std::endl;
			}
		}
	}
		
	return 0;
}