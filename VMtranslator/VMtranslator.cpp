#include <iostream>
#include <string>

#include "parser.h"

using std::string;
using std::ofstream;

int main(int argc, char* argv[])
{
	bool moreCommands = true;
	
	Parser parser("ProjectFiles/SimpleAdd/SimpleAdd.vm");
	//Parser parser("ProjectFiles/StackArithmetic/StackTest/StackTest.vm");
	//Parser parser("ProjectFiles/MemoryAccess/BasicTest/BasicTest.vm");
	
	while(moreCommands)
	{
		parser.advance();
		moreCommands = parser.hasMoreCommands();
		if(moreCommands)
		{
			std::cout << parser.commandType() << std::endl;
			if(parser.commandType() != C_RETURN)
			{
				string arg1 = parser.arg1();
				std::cout << "parser.arg1() = " << arg1 << std::endl;
				if(parser.commandType() == (C_PUSH || C_POP || C_FUNCTION || C_CALL))
				{
					int arg2 = parser.arg2();
					std::cout << "parser.arg2() = " << arg2 << std::endl;
				}
			}
		}
	}
	return 0;
}