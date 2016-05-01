#include <iostream>

#include "parser.h"

int main()
{
	Parser parser("add.asm");
	
	while(parser.hasMoreCommands());
	
	return 0;
}