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
		loadDFromAWithValue(index);
		storeDToPointerFromLocation("SP");
		
		// Increase SP.
		increaseStackPointer();
	}
}

void CodeWriter::writeAdd(void)
{
	// Decrease stack pointer.
	decreaseStackPointer();

	// Store pointer value to D.
	loadDFromPointer();

	// Decrease stack pointer.
	decreaseStackPointer();

	// Add pointer with D.
	addPointerWithD();

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

void CodeWriter::decreaseStackPointer(void)
{
	outputFile << "@SP" << std::endl;
	outputFile << "M=M-1" << std::endl;
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

void CodeWriter::loadDFromAWithValue(int value)
{
	outputFile << "@" << value << std::endl;
	outputFile << "D=A" << std::endl;
}

void CodeWriter::loadDFromPointer(void)
{
	outputFile << "A=M" << std::endl;
	outputFile << "D=M" << std::endl;
}

void CodeWriter::storeDToPointerFromLocation(std::string location)
{
	outputFile << "@" << location << std::endl;
	outputFile << "A=M" << std::endl;
	outputFile << "M=D" << std::endl;
}

void CodeWriter::storeDToPointer(void)
{
	outputFile << "A=M" << std::endl;
	outputFile << "M=D" << std::endl;
}

void CodeWriter::addLocationWithD(std::string location)
{
	outputFile << "@" << location << std::endl;
	outputFile << "M=D+M" << std::endl;
}

void CodeWriter::addPointerWithD(void)
{
	outputFile << "A=M"  << std::endl;
	outputFile << "M=D+M" << std::endl;
}
