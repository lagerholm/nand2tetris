#include "codewriter.hpp"

using namespace std;

CodeWriter::CodeWriter(string output)
{
	outputFile.open(output.c_str());
}

void CodeWriter::close(void)
{
	outputFile.close();
}