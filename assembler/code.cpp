#include "code.h"

using std::string;

enum destMnemonic 
{
	DEST_NULL,
	DEST_M,
	DEST_D,
	DEST_MD,
	DEST_A,
	DEST_AM,
	DEST_AD,
	DEST_AMD,
	DEST_NO_MNEMONIC
};

enum compMnemonic 
{
	COMP_NULL,
	COMP_ZERO,
	COMP_ONE,
	COMP_NEGATIVE_ONE,
	COMP_D,
	COMP_A,
	COMP_NOT_D,
	COMP_NOT_A,
	COMP_MINUS_D,
	COMP_MINUS_A,
	COMP_D_PULS_ONE,
	COMP_A_PLUS_ONE,
	COMP_D_MINUS_ONE,
	COMP_A_MINUS_ONE,
	COMP_D_PLUS_A,
	COMP_D_MINUS_A,
	COMP_A_MINUS_D,
	COMP_D_AND_A,
	COMP_D_OR_A,
	COMP_M,
	COMP_NOT_M,
	COMP_MINUS_M,
	COMP_M_PLUS_ONE,
	COMP_M_MINUS_ONE,
	COMP_D_PLUS_M,
	COMP_D_MINUS_M,
	COMP_M_MINUS_D,
	COMP_D_AND_M,
	COMP_D_OR_M,
	COMP_NO_MNEMONIC
};

enum jumpMnemonic 
{
	JUMP_NULL,
	JUMP_JGT,
	JUMP_JEQ,
	JUMP_JGE,
	JUMP_JLT,
	JUMP_JNE,
	JUMP_JLE,
	JUMP_JMP,
	JUMP_NO_MNEMONIC
};

namespace {
	destMnemonic hashDest(string const& dest)
	{
		if (dest == "") 	return DEST_NULL;
		if (dest == "M") 	return DEST_M;
		if (dest == "D") 	return DEST_D;
		if (dest == "MD") 	return DEST_MD;
		if (dest == "A") 	return DEST_A;
		if (dest == "AM") 	return DEST_AM;
		if (dest == "AD") 	return DEST_AD;
		if (dest == "AMD") 	return DEST_AMD;
		return DEST_NO_MNEMONIC;
	}
	
	compMnemonic hashComp(string const& comp)
	{
		if (comp == "") 	return COMP_NULL;
		if (comp == "0") 	return COMP_ZERO;
		if (comp == "1") 	return COMP_ONE;
		if (comp == "-1") 	return COMP_NEGATIVE_ONE;
		if (comp == "D") 	return COMP_D;
		if (comp == "A") 	return COMP_A;
		if (comp == "!D") 	return COMP_NOT_D;
		if (comp == "!A") 	return COMP_NOT_A;
		if (comp == "-D") 	return COMP_MINUS_D;
		if (comp == "-A") 	return COMP_MINUS_A;
		if (comp == "D+1") 	return COMP_D_PULS_ONE;
		if (comp == "A+1") 	return COMP_A_PLUS_ONE;
		if (comp == "D-1") 	return COMP_D_MINUS_ONE;
		if (comp == "A-1") 	return COMP_A_MINUS_ONE;
		if (comp == "D+A") 	return COMP_D_PLUS_A;
		if (comp == "D-A") 	return COMP_D_MINUS_A;
		if (comp == "A-D") 	return COMP_A_MINUS_D;
		if (comp == "D&A") 	return COMP_D_AND_A;
		if (comp == "D|A") 	return COMP_D_OR_A;
		if (comp == "M") 	return COMP_M;
		if (comp == "!M") 	return COMP_NOT_M;
		if (comp == "-M") 	return COMP_MINUS_M;
		if (comp == "M+1") 	return COMP_M_PLUS_ONE;
		if (comp == "M-1") 	return COMP_M_MINUS_ONE;
		if (comp == "D+M") 	return COMP_D_PLUS_M;
		if (comp == "D-M") 	return COMP_D_MINUS_M;
		if (comp == "M-D") 	return COMP_M_MINUS_D;
		if (comp == "D&M") 	return COMP_D_AND_M;
		if (comp == "D|M") 	return COMP_D_OR_M;
		return COMP_NO_MNEMONIC;        
	}
	
	jumpMnemonic hashJump(string const& jump)
	{
		if (jump == "") 	return JUMP_NULL;
		if (jump == "JGT") 	return JUMP_JGT;
		if (jump == "JEQ") 	return JUMP_JEQ;
		if (jump == "JGE") 	return JUMP_JGE;
		if (jump == "JLT") 	return JUMP_JLT;
		if (jump == "JNE") 	return JUMP_JNE;
		if (jump == "JLE") 	return JUMP_JLE;
		if (jump == "JMP") 	return JUMP_JMP;
		return JUMP_NO_MNEMONIC;   
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
	case DEST_M:
		retVal = "001";
		break;
	case DEST_D:
		retVal = "010";
		break;
	case DEST_MD:
		retVal = "011";
		break;
	case DEST_A:
		retVal = "100";
		break;
	case DEST_AM:
		retVal = "101";
		break;
	case DEST_AD:
		retVal = "110";
		break;
	case DEST_AMD:
		retVal = "111";
		break;
	case DEST_NO_MNEMONIC:
	default:
		break;
	}
	return retVal;
}

string Code::comp(string comp)
{
	string retVal = "";
	
	switch(hashComp(comp))
	{
	case COMP_ZERO:
		retVal = "0101010";
		break;
	case COMP_ONE:
		retVal = "0111111";
		break;
	case COMP_NEGATIVE_ONE:
		retVal = "0111010";
		break;
	case COMP_D:
		retVal = "0001100";
		break;
	case COMP_A:
		retVal = "0110000";
		break;
	case COMP_NOT_D:
		retVal = "0001101";
		break;
	case COMP_NOT_A:
		retVal = "0110001";
		break;
	case COMP_MINUS_D:
		retVal = "0001111";
		break;
	case COMP_MINUS_A:
		retVal = "0110011";
		break;
	case COMP_D_PULS_ONE:
		retVal = "0011111";
		break;
	case COMP_A_PLUS_ONE:
		retVal = "0110111";
		break;
	case COMP_D_MINUS_ONE:
		retVal = "0001110";
		break;
	case COMP_A_MINUS_ONE:
		retVal = "0110010";
		break;
	case COMP_D_PLUS_A:
		retVal = "0000010";
		break;		
	case COMP_D_MINUS_A:
		retVal = "0010011";
		break;		
	case COMP_A_MINUS_D:
		retVal = "0000111";
		break;		
	case COMP_D_AND_A:
		retVal = "0000000";
		break;		
	case COMP_D_OR_A:
		retVal = "0010101";
		break;		
	case COMP_M:
		retVal = "1110000";
		break;
	case COMP_NOT_M:
		retVal = "1110001";
		break;
	case COMP_MINUS_M:
		retVal = "1110011";
		break;
	case COMP_M_PLUS_ONE:
		retVal = "1110111";
		break;
	case COMP_M_MINUS_ONE:
		retVal = "1110010";
		break;
	case COMP_D_PLUS_M:
		retVal = "1000010";
		break;
	case COMP_D_MINUS_M:
		retVal = "1010011";
		break;
	case COMP_M_MINUS_D:
		retVal = "1000111";
		break;
	case COMP_D_AND_M:
		retVal = "1000000";
		break;
	case COMP_D_OR_M:
		retVal = "1010101";
		break;
	case COMP_NULL:
	case COMP_NO_MNEMONIC:
	default:
		break;
	}
	return retVal;
}

string Code::jump(string jump)
{
	string retVal = "";
	
	switch(hashJump(jump))
	{
	case JUMP_NULL:
		retVal = "000";
		break;
	case JUMP_JGT:
		retVal = "001";
		break;
	case JUMP_JEQ:
		retVal = "010";
		break;
	case JUMP_JGE:
		retVal = "011";
		break;
	case JUMP_JLT:
		retVal = "100";
		break;
	case JUMP_JNE:
		retVal = "101";
		break;
	case JUMP_JLE:
		retVal = "110";
		break;
	case JUMP_JMP:
		retVal = "111";
		break;
	case JUMP_NO_MNEMONIC:
	default:
		break;
	}
	return retVal;
}