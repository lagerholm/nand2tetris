#include "code.h"

using std::string;

enum destMnemonic 
{
	DEST_NULL,
	M,
	D,
	MD,
	A,
	AM,
	AD,
	AMD,
	NO_MNEMONIC
};

namespace {
	destMnemonic hashDest(string const& dest)
	{
		if (dest == "") 	return DEST_NULL;
		if (dest == "M") 	return M;
		if (dest == "D") 	return D;
		if (dest == "MD") 	return MD;
		if (dest == "A") 	return A;
		if (dest == "AM") 	return AM;
		if (dest == "AD") 	return AD;
		if (dest == "AMD") 	return AMD;
		return NO_MNEMONIC;
	}
}

string Code::dest(string dest)
{
	string retVal = "";
	
	switch(hashDest(dest))
	{
	case DEST_NULL:
		retVal = "000";
		break;
	case M:
		retVal = "001";
		break;
	case D:
		retVal = "010";
		break;
	case MD:
		retVal = "011";
		break;
	case A:
		retVal = "100";
		break;
	case AM:
		retVal = "101";
		break;
	case AD:
		retVal = "110";
		break;
	case AMD:
		retVal = "111";
		break;
	case NO_MNEMONIC:
	default:
		break;
	}
	return retVal;
}