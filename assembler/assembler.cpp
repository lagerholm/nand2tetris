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
			std::cout << parser.commandType() << std::endl;
		}
	}
		
	return 0;
}