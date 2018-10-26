#pragma once

struct FormulaAddInData
{
	int nVarType; // 1 for double, 2 for wchar_t
	int isNull; // 1 if NULL, 0 if valid
	double dVal; // valid if nVarType==1 && isNull==0
	const wchar_t * pVal; // valid if nVarType==2 && isNull==0
};

void SetString(FormulaAddInData *pReturnValue, const wchar_t *pString);
void SetDouble(FormulaAddInData *pReturnValue, double value);
extern "C" unsigned long long _declspec(dllexport) _stdcall longPow(unsigned long value, int pow);
extern "C" long _declspec(dllexport) _stdcall CleanNulls(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue);
extern "C" long _declspec(dllexport) _stdcall SimpleStrToInt(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue);
extern "C" long _declspec(dllexport) _stdcall StrToInt(int nNumArgs, FormulaAddInData *pArgs, FormulaAddInData *pReturnValue);
