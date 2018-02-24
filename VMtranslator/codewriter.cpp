#include "codewriter.hpp"

using namespace std;

CodeWriter::CodeWriter(string output)
{
	outputFile.open(output.c_str());
}

void CodeWriter::setFileName(std::string fileName)
{
	currentFileName = fileName;
}

void CodeWriter::writeArithmetic(std::string command)
{

}

void CodeWriter::writePushPop(CommandType commandType, std::string segment, int index)
{
	switch(commandType)
	{
		case CommandType::C_PUSH:
				handlePushCommand(segment, index);
			break;

		case CommandType::C_POP:

			break;
		
		default:
			// ERROR!!
			break;
	}
}

void CodeWriter::close(void)
{
	outputFile.close();
}

void CodeWriter::handlePushCommand(std::string segment, int index)
{
	if (segment == "constant")
	{
		// Access memory at SP and set it to index.
		outputFile << "@" << index << std::endl;
		outputFile << "D=A" << std::endl;
		outputFile << "@SP" << std::endl;
		outputFile << "A=M" << std::endl;
		outputFile << "M=D" << std::endl;
		
		// Increase SP by 1.
		outputFile << "@SP" << std::endl;
		outputFile << "M=M+1" << std::endl;
	}
}
