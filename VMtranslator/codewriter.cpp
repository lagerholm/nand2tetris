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
	else if (command == "sub")
	{
		writeSub();
	}
	else if (command == "neg")
	{
		writeNeg();
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
	else if (command == "and")
	{
		writeAnd();
	}
	else if (command == "or")
	{
		writeOr();
	}
	else if (command == "not")
	{
		writeNot();
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
				handlePopCommand(segment, index);
			break;
		
		default:
			// ERROR!!
			break;
	}
}

void CodeWriter::writeInit(void)
{

}

void CodeWriter::writeLabel(std::string label)
{
	std::string str("(");
	str.append(label);
	str.append(")");
	pushLineToFile(str);
}

void CodeWriter::writeGoto(std::string label)
{

}

void CodeWriter::writeIf(std::string label)
{
	// Pop stack to D.
	popStackValueToD();
	// Jump D eq 0 to Label+End
	std::string labelStr(label);
	labelStr.append("_END");
	std::string str("(");
	str.append(labelStr);
	str.append(")");
	jumpToLabel(labelStr, "D", "JEQ");

	// Jump to Label
	jumpToLabel(label, "0", "JMP");

	// Write Label+End
	pushLineToFile(str);
}

void CodeWriter::writeCall(std::string functionName, int numArgs)
{

}

void CodeWriter::writeReturn(void)
{

}

void CodeWriter::writeFunction(std::string functionName, int numLocals)
{

}

void CodeWriter::close(void)
{
	outputFile.close();
}

void CodeWriter::handlePushCommand(std::string segment, int index)
{
	if (segment == "argument")
	{
		pushFromSegmentWithIndex("ARG", index);
	}
	else if (segment == "local")
	{
		pushFromSegmentWithIndex("LCL", index);
	}
	else if (segment == "static")
	{
		// RAM[16-255]
		loadDFromLocation(to_string(16+index));
		pushDToStack();
	}
	else if (segment == "constant")
	{
		// Access memory at SP and set it to index.
		loadDFromAWithValue(index);
		storeToPointerFromLocation("SP", "D");
		
		// Increase SP.
		increaseStackPointer();
	}
	else if (segment == "this")
	{
		pushFromSegmentWithIndex("THIS", index);
	}
	else if (segment == "that")
	{
		pushFromSegmentWithIndex("THAT", index);
	}
	else if (segment == "pointer")
	{
		if(index == 0)
		{
			//  Puh this to stack.
			loadDFromLocation("THIS");
			pushDToStack();
		}
		else if(index == 1)
		{
			//  Puh that to stack.
			loadDFromLocation("THAT");
			pushDToStack();
		}
		else
		{
			// Throw error;
		}
	}
	else if (segment == "temp")
	{
		// RAM[5-12]
		loadDFromLocation(to_string(5+index));
		pushDToStack();
	}
}

void CodeWriter::handlePopCommand(std::string segment, int index)
{
	if (segment == "argument")
	{
		storeSegmentWithIndexToGpRegister("ARG", index, "R13");
	}
	else if (segment == "local")
	{
		storeSegmentWithIndexToGpRegister("LCL", index, "R13");
	}
	else if (segment == "this")
	{
		storeSegmentWithIndexToGpRegister("THIS", index, "R13");
	}
	else if (segment == "that")
	{
		storeSegmentWithIndexToGpRegister("THAT", index, "R13");
	}
	else if (segment == "static")
	{
		// RAM[16-255]
		popStackValueToD();
		storeDToLocation(to_string(16+index));
	}
	else if (segment == "constant")
	{
		// Makes no sense?
	}
	else if (segment == "pointer")
	{
		if(index == 0)
		{
			// Pop stack to this.
			popStackValueToD();
			storeDToLocation("THIS");
		}
		else if(index == 1)
		{
			// Pop stack to that.
			popStackValueToD();
			storeDToLocation("THAT");
		}
		else
		{
			// Throw error;
		}
	}
	else if (segment == "temp")
	{
		// RAM[5-12]
		popStackValueToD();
		storeDToLocation(to_string(5+index));
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

void CodeWriter::writeSub(void)
{
	// Decrease stack pointer.
	decreaseStackPointer();

	// Store pointer value to D.
	loadDFromPointer();

	// Decrease stack pointer.
	decreaseStackPointer();

	// Add pointer with D.
	subtractPointerWithD();

	// Increase SP.
	increaseStackPointer();
}

void CodeWriter::writeNeg(void)
{
	// Decrease stack pointer.
	decreaseStackPointer();

	// Store pointer value to D.
	loadDFromPointer();

	// Negate D and store to pointer.
	storeToPointerFromLocation("SP", "-D");

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

void CodeWriter::writeAnd(void)
{
	// Decrease stack pointer.
	decreaseStackPointer();

	// Store pointer value to D.
	loadDFromPointer();

	// Decrease stack pointer.
	decreaseStackPointer();

	// Add pointer with D.
	andPointerWithD();

	// Increase SP.
	increaseStackPointer();
}

void CodeWriter::writeOr(void)
{
	// Decrease stack pointer.
	decreaseStackPointer();

	// Store pointer value to D.
	loadDFromPointer();

	// Decrease stack pointer.
	decreaseStackPointer();

	// Add pointer with D.
	orPointerWithD();

	// Increase SP.
	increaseStackPointer();
}

void CodeWriter::writeNot(void)
{
	// Decrease stack pointer.
	decreaseStackPointer();

	// Store pointer value to D.
	loadDFromPointer();

	// Negate D and store to pointer.
	storeToPointerFromLocation("SP", "!D");

	// Increase SP.
	increaseStackPointer();
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

void CodeWriter::pushDToStack(void)
{
	setAtoValue("SP");
	storeDToPointer();
	increaseStackPointer();
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

void CodeWriter::setAtoValue(std::string value)
{
	string str("@");
	str.append(value);
	pushLineToFile(str);
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

void CodeWriter::storeSegmentWithIndexToGpRegister(std::string segment, int index, std::string gpRegister)
{
	loadDFromLocation(segment);

	setAtoValue(to_string(index));

	pushLineToFile("D=D+A");

	storeDToLocation(gpRegister);

	popStackValueToD();

	setAtoValue(gpRegister);

	storeDToPointer();
}

void CodeWriter::pushFromSegmentWithIndex(std::string segment, int index)
{
	loadDFromLocation(segment);
	setAtoValue(to_string(index));
	pushLineToFile("A=D+A");
	pushLineToFile("D=M");
	pushDToStack();
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

void CodeWriter::subtractPointerWithD(void)
{
	pushLineToFile("A=M");
	pushLineToFile("M=M-D");
}

void CodeWriter::subtractDWithPointer(void)
{
	pushLineToFile("A=M");
	pushLineToFile("D=D-M");
}

void CodeWriter::andPointerWithD(void)
{
	pushLineToFile("A=M");
	pushLineToFile("M=D&M");
}

void CodeWriter::orPointerWithD(void)
{
	pushLineToFile("A=M");
	pushLineToFile("M=D|M");
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