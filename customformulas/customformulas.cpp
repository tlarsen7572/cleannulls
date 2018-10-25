#include "stdafx.h"
#include "customformulas.h"
#include <map>
#include <bitset>

using namespace std;

void SetString(FormulaAddInData *pReturnValue, const wchar_t *pString)
{
	size_t nLen = wcslen(pString);
	wchar_t *pStringRet = (wchar_t *)GlobalAlloc(GMEM_FIXED, (nLen + 1) * sizeof(wchar_t));
	wcscpy(pStringRet, pString);
	pReturnValue->pVal = pStringRet;
	pReturnValue->nVarType = 2;
	pReturnValue->isNull = 0;
}

void SetDouble(FormulaAddInData *pReturnValue, double value)
{
	pReturnValue->dVal = value;
	pReturnValue->nVarType = 1;
	pReturnValue->isNull = 0;
}

long CleanNulls(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	if (nNumArgs != 1)
	{
		SetString(pReturnValue, L"Only one parameter can be provided.");
		return 0;
	}

	FormulaAddInData arg = pArgs[0];
	if (arg.isNull == 1)
	{
		if (arg.nVarType == 2)
		{
			SetString(pReturnValue, L"");
		}
		else
		{
			SetDouble(pReturnValue, 0.0);
		}
	}
	else
	{
		if (arg.nVarType == 2)
		{
			SetString(pReturnValue, arg.pVal);
		}
		else
		{
			SetDouble(pReturnValue, arg.dVal);
		}
	}

	return 1;
}

long SimpleStrToInt(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue)
{
	if (pArgs->isNull == 1) {
		pReturnValue->isNull = 1;
		return 1;
	}
	if (nNumArgs != 1)
	{
		SetString(pReturnValue, L"Only one parameter can be provided.");
		return 0;
	}
	if (pArgs->nVarType == 1) {
		SetString(pReturnValue, L"Value must be a string.");
		return 0;
	}
	if (wcslen(pArgs->pVal) > 10) {
		SetString(pReturnValue, L"String must be 10 characters or less.");
		return 0;
	}
	if (wcslen(pArgs->pVal) == 0) {
		SetDouble(pReturnValue, 0.0);
		return 1;
	}

	map<WCHAR, std::bitset<6>> bitmap = {
		{ '0', 0b000001 },
		{ '1', 0b000010 },
		{ '2', 0b000011 },
		{ '3', 0b000100 },
		{ '4', 0b000101 },
		{ '5', 0b000110 },
		{ '6', 0b000111 },
		{ '7', 0b001000 },
		{ '8', 0b001001 },
		{ '9', 0b001010 },
		{ 'A', 0b001011 },
		{ 'B', 0b001100 },
		{ 'C', 0b001101 },
		{ 'D', 0b001110 },
		{ 'E', 0b001111 },
		{ 'F', 0b010000 },
		{ 'G', 0b010001 },
		{ 'H', 0b010010 },
		{ 'I', 0b010011 },
		{ 'J', 0b010100 },
		{ 'K', 0b010101 },
		{ 'L', 0b010110 },
		{ 'M', 0b010111 },
		{ 'N', 0b011000 },
		{ 'O', 0b011001 },
		{ 'P', 0b011010 },
		{ 'Q', 0b011011 },
		{ 'R', 0b011100 },
		{ 'S', 0b011101 },
		{ 'T', 0b011110 },
		{ 'U', 0b011111 },
		{ 'V', 0b100000 },
		{ 'W', 0b100001 },
		{ 'X', 0b100010 },
		{ 'Y', 0b100011 },
		{ 'Z', 0b100100 },
		{ ' ', 0b100101 },
		{ '_', 0b100110 },
		{ '-', 0b100111 },
		{ '.', 0b101000 },
	};

	return 0;
}
