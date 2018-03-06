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
	int labelIndex;
	void handlePushCommand(std::string segment, int index);
	void handlePopCommand(std::string segment, int index);
	void writeAdd(void);
	void writeSub(void);
	void writeNeg(void);
	void writeEq(void);
	void writeLt(void);
	void writeGt(void);
	void writeAnd(void);
	void writeOr(void);
	void writeNot(void);
	void writeCompareCommand(std::string comparison);
	void popStackValueToD(void);
	void increaseStackPointer(void);
	void decreaseStackPointer(void);
	void setAtoValue(std::string value);
	void storeDToLocation(std::string location);
	void loadDFromLocation(std::string location);
	void loadDFromAWithValue(int value);
	void loadDFromPointer(void);
	void storeToPointerFromLocation(std::string location, std::string value);
	void storeDToPointer(void);
	void storeSegmentWithIndexToGpRegister(std::string segment, int index, std::string gpRegister);
	void addLocationWithD(std::string location);
	void addPointerWithD(void);
	void subtractPointerWithD(void);
	void pushLineToFile(std::string command);
	void pushLineToFileWithLocation(std::string command, std::string location);
	void subtractDWithPointer(void);
	void andPointerWithD(void);
	void orPointerWithD(void);
	void jumpToLabel(std::string label, std::string compare, std::string jump);
	void insertLabel(std::string label);
	std::string generateNewLabel(void);
};