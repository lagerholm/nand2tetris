#pragma once

#include <string>
#include <fstream>

#include "common.hpp"

class CodeWriter
{
	public:
	CodeWriter(std::string);

	void setFileName(std::string fileName);
	void writeArithmetic(std::string command);
	void writePushPop(CommandType commandType, std::string segment, int index);
	void close(void);

	private:
	std::ofstream outputFile;
	std::string currentFileName;
	void handlePushCommand(std::string segment, int index);
	void writeAdd(void);
	void popStackValueToD(void);
	void increaseStackPointer(void);
	void storeDToLocation(std::string location);
	void loadDFromLocation(std::string location);
	void loadDfromAWithValue(int value);
	void storeDToPointerLocation(std::string location);
	void addLocationWithD(std::string location);
};