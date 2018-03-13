#include <iostream>
#include <string>

#include "parser.h"
#include "codewriter.hpp"

using std::string;

int main(int argc, char* argv[])
{
	bool moreCommands = true;

	//Parser parser("ProjectFiles/SimpleAdd/SimpleAdd.vm");
	//Parser parser("ProjectFiles/StackArithmetic/StackTest/StackTest.vm");
	//Parser parser("ProjectFiles/MemoryAccess/BasicTest/BasicTest.vm");
	//Parser parser("ProjectFiles/MemoryAccess/StaticTest/StaticTest.vm");
	Parser parser("ProjectFiles/8/ProgramFlow/BasicLoop/BasicLoop.vm");


	CodeWriter codeWriter("ProjectFiles/8/ProgramFlow/BasicLoop/BasicLoop.asm");

	while(moreCommands)
	{
		parser.advance();
		moreCommands = parser.hasMoreCommands();
		if(moreCommands)
		{
			CommandType commandType = parser.commandType();
			string arg1 = "";
			int arg2 = 0;

			std::cout << commandType << std::endl;
			if(commandType != CommandType::C_RETURN)
			{
				arg1 = parser.arg1();
				std::cout << "parser.arg1() = " << arg1 << std::endl;
				if(parser.commandHasArg2())
				{
					arg2 = parser.arg2();
					std::cout << "parser.arg2() = " << arg2 << std::endl;
				}

				if ((commandType == CommandType::C_POP) || (commandType == CommandType::C_PUSH))
				{
					codeWriter.writePushPop(commandType, arg1, arg2);
				}
				else if (parser.isCurrentCommandArithmetic())
				{
					codeWriter.writeArithmetic(arg1);
				}
				else if (commandType == CommandType::C_LABEL)
				{
					codeWriter.writeLabel(arg1);
				}
				else if (commandType == CommandType::C_GOTO)
				{
					codeWriter.writeGoto(arg1);
				}
				else if (commandType == CommandType::C_IF)
				{
					codeWriter.writeIf(arg1);
				}
				else if (commandType == CommandType::C_FUNCTION)
				{
					codeWriter.writeCall(arg1, arg2);
				}
				else if (commandType == CommandType::C_RETURN)
				{
					codeWriter.writeReturn();
				}
				else if (commandType == CommandType::C_CALL)
				{
					codeWriter.writeFunction(arg1, arg2);
				}
			}
		}
	}

	codeWriter.close();
	return 0;
}