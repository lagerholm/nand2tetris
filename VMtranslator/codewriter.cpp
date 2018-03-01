#include "codewriter.hpp"

using namespace std;

CodeWriter::CodeWriter(string output):labelIndex(0)
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
	else if (command == "eq")
	{
		writeEq();
	}
	else if (command == "lt")
	{
		writeLt();
	}
	else if (command == "gt")
	{
		writeGt();
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
		storeToPointerFromLocation("SP", "D");
		
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

void CodeWriter::writeEq(void)
{
	writeCompareCommand("JEQ");
}

void CodeWriter::writeLt(void)
{
	writeCompareCommand("JGT");	// JGT is due to how we read the stack.
}

void CodeWriter::writeGt(void)
{
	writeCompareCommand("JLT");	// JLT is due to how we read the stack.
}

void CodeWriter::writeCompareCommand(std::string comparison)
{
	// Decrease stack pointer.
	decreaseStackPointer();

	// Put pointer value in D.
	loadDFromPointer();

	// Decrease stack pointer.
	decreaseStackPointer();

	// Subtract D with value from pointer.
	subtractDWithPointer();

	// Do jump depening on comparion.
	std::string trueLabel(generateNewLabel());
	jumpToLabel(trueLabel, "D", comparison);

	// No jump store false.
	storeToPointerFromLocation("SP", "0");	// 0 is false.

	// Go to end.
	std::string endLabel(generateNewLabel());
	jumpToLabel(endLabel, "0", "JMP");

	// Handle true label.
	insertLabel(trueLabel);
	storeToPointerFromLocation("SP", "-1");	// -1 is true.

	// Handle end label.
	insertLabel(endLabel);
	increaseStackPointer();
}

void CodeWriter::popStackValueToD(void)
{
	pushLineToFile("@SP");
	pushLineToFile("M=M-1");
	pushLineToFile("A=M");
	pushLineToFile("D=M");
}

void CodeWriter::increaseStackPointer(void)
{
	pushLineToFile("@SP");
	pushLineToFile("M=M+1");
}

void CodeWriter::decreaseStackPointer(void)
{
	pushLineToFile("@SP");
	pushLineToFile("M=M-1");
}

void CodeWriter::storeDToLocation(std::string location)
{
	pushLineToFileWithLocation("@", location);
	pushLineToFile("M=D");
}

void CodeWriter::loadDFromLocation(std::string location)
{
	pushLineToFileWithLocation("@", location);
	pushLineToFile("D=M");
}

void CodeWriter::loadDFromAWithValue(int value)
{
	pushLineToFileWithLocation("@", std::to_string(value));
	pushLineToFile("D=A");
}

void CodeWriter::loadDFromPointer(void)
{
	pushLineToFile("A=M");
	pushLineToFile("D=M");
}

void CodeWriter::storeToPointerFromLocation(std::string location, std::string value)
{
	pushLineToFileWithLocation("@", location);
	pushLineToFile("A=M");
	pushLineToFileWithLocation("M=", value);
}

void CodeWriter::storeDToPointer(void)
{
	pushLineToFile("A=M");
	pushLineToFile("M=D");
}

void CodeWriter::addLocationWithD(std::string location)
{
	pushLineToFileWithLocation("@", location);
	pushLineToFile("M=D+M");
}

void CodeWriter::addPointerWithD(void)
{
	pushLineToFile("A=M");
	pushLineToFile("M=D+M");
}

void CodeWriter::subtractDWithPointer(void)
{
	pushLineToFile("A=M");
	pushLineToFile("D=D-M");
}

void CodeWriter::jumpToLabel(std::string label, std::string compare, std::string jump)
{
	pushLineToFileWithLocation("@", label);
	std::string str(compare);
	str.append(";");
	str.append(jump);
	pushLineToFile(str);
}

void CodeWriter::insertLabel(std::string label)
{
	std::string str("(");
	str.append(label);
	str.append(")");
	pushLineToFile(str);
}

void CodeWriter::pushLineToFile(std::string command)
{
	outputFile << command << std::endl;
}

void CodeWriter::pushLineToFileWithLocation(std::string command, std::string location)
{
	outputFile << command << location << std::endl;
}

std::string CodeWriter::generateNewLabel(void)
{
	std::string str("LABEL");
	return str.append(std::to_string(labelIndex++));
}