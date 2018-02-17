#include <iostream>
#include <string>

#include "parser.h"

using std::string;
using std::ofstream;

int main(int argc, char* argv[])
{
	bool moreCommands = true;
	
	Parser parser("ProjectFiles/SimpleAdd/SimpleAdd.vm");
	
	while(moreCommands)
	{
		parser.advance();
		moreCommands = parser.hasMoreCommands();
		if(moreCommands)
		{
			std::cout << parser.commandType() << std::endl;
			if(parser.commandType() != C_RETURN)
			{
				string s = parser.arg1();
				std::cout << "parser.arg1() = " << s << std::endl;
			}
		}
	}
	return 0;
}