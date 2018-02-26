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
	if (command == "add")
	{
		writeAdd();
	}
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
		loadDfromAWithValue(index);
		storeDToPointerLocation("SP");
		
		// Increase SP.
		increaseStackPointer();
	}
}

void CodeWriter::writeAdd(void)
{
	// Decrease SP and read and store M[SP] in R13.
	popStackValueToD();
	storeDToLocation("R13");

	// Decrease SP add R13 and M[SP] and store in R13.
	popStackValueToD();
	addLocationWithD("R13");

	// Store result from R13 to M[SP].
	loadDFromLocation("R13");
	storeDToPointerLocation("SP");

	// Increase SP.
	increaseStackPointer();
}

void CodeWriter::popStackValueToD(void)
{
	outputFile << "@SP" << std::endl;
	outputFile << "M=M-1" << std::endl;
	outputFile << "A=M" << std::endl;
	outputFile << "D=M" << std::endl;
}

void CodeWriter::increaseStackPointer(void)
{
	outputFile << "@SP" << std::endl;
	outputFile << "M=M+1" << std::endl;
}

void CodeWriter::storeDToLocation(std::string location)
{
	outputFile << "@" << location << std::endl;
	outputFile << "M=D" << std::endl;
}

void CodeWriter::loadDFromLocation(std::string location)
{
	outputFile << "@" << location << std::endl;
	outputFile << "D=M" << std::endl;
}

void CodeWriter::loadDfromAWithValue(int value)
{
	outputFile << "@" << value << std::endl;
	outputFile << "D=A" << std::endl;
}

void CodeWriter::storeDToPointerLocation(std::string location)
{
	outputFile << "@" << location << std::endl;
	outputFile << "A=M" << std::endl;
	outputFile << "M=D" << std::endl;
}

void CodeWriter::addLocationWithD(std::string location)
{
	outputFile << "@" << location << std::endl;
	outputFile << "M=D+M" << std::endl;
}
