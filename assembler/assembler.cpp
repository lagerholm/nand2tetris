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
		}
	}
		
	return 0;
}