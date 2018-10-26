#include "stdafx.h"
#include "CppUnitTest.h"
#include "customformulas.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(SimpleStrToInt_Tests)
{
public:
	TEST_METHOD(longPow2) {
		unsigned long long value = longPow(40, 2);
		unsigned long long expected = 1600;
		Assert::IsTrue(value == expected);
	}
	TEST_METHOD(longPow0) {
		unsigned long long value = longPow(40, 0);
		unsigned long long expected = 1;
		Assert::IsTrue(value == expected);
	}

	TEST_METHOD(longPow1) {
		unsigned long long value = longPow(40, 1);
		unsigned long long expected = 40;
		Assert::IsTrue(value == expected);
	}
	TEST_METHOD(longPow11) {
		unsigned long long value = longPow(40, 11);
		unsigned long long expected = 419430400000000000;
		Assert::IsTrue(value == expected);
	}

	TEST_METHOD(NullReturnNull)
	{
		FormulaAddInData *data = CreateNullData(1);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = SimpleStrToInt(1, data, pReturnValue);

		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	TEST_METHOD(ErrorMoreThanOneArg) {
		FormulaAddInData *data = CreatePopulatedData(L"ABCD");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = SimpleStrToInt(2, data, pReturnValue);
		Assert::AreEqual(0, returnCode);
		Assert::AreEqual(L"Only one parameter can be provided.", pReturnValue->pVal);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	TEST_METHOD(ErrorMoreThan12Chars) {
		FormulaAddInData *data = CreatePopulatedData(L"1234567890ABC");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = SimpleStrToInt(1, data, pReturnValue);
		Assert::AreEqual(0, returnCode);
		Assert::AreEqual(L"String must be 12 characters or less.", pReturnValue->pVal);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	TEST_METHOD(ErrorIfNumber) {
		FormulaAddInData *data = new FormulaAddInData();
		data->nVarType = 1;
		data->isNull = 0;
		data->dVal = 0.0;
		data->pVal = L"";

		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = SimpleStrToInt(1, data, pReturnValue);
		Assert::AreEqual(0, returnCode);
		Assert::AreEqual(L"Value must be a string.", pReturnValue->pVal);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	TEST_METHOD(ABCConversion) {
		FormulaAddInData *data = CreatePopulatedData(L"ABC");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		signed long long checkval = INT64_MIN + 23016;
		wstring checkvalStr = to_wstring(checkval);
		const wchar_t * checkvalwChar{ checkvalStr.c_str() };
		int returnCode = SimpleStrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(checkvalwChar, pReturnValue->pVal);
		Assert::AreEqual(2, pReturnValue->nVarType);
	}

	TEST_METHOD(ZZZZZZZZZZZZConversion) {
		FormulaAddInData *data = CreatePopulatedData(L"ZZZZZZZZZZZZ");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		signed long long checkval = INT64_MIN + 16777215999999999999;
		wstring checkvalStr = to_wstring(checkval);
		const wchar_t * checkvalwChar{ checkvalStr.c_str() };
		int returnCode = SimpleStrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(checkvalwChar, pReturnValue->pVal);
		Assert::AreEqual(2, pReturnValue->nVarType);
	}

	TEST_METHOD(BlankStringConversion) {
		FormulaAddInData *data = CreatePopulatedData(L"");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = SimpleStrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	FormulaAddInData * CreateReturnValue()
	{
		FormulaAddInData *pReturnValue = new FormulaAddInData();
		pReturnValue->dVal = -1.0;
		pReturnValue->pVal = L"Null";
		pReturnValue->nVarType = -1;
		pReturnValue->isNull = -1;
		return pReturnValue;
	}

	FormulaAddInData * CreatePopulatedData(const wchar_t *pString)
	{
		return CreateData(0, pString);
	}

	FormulaAddInData * CreateNullData(int varType)
	{
		return CreateData(1, L"");
	}

	FormulaAddInData * CreateData(int isNull, const wchar_t *pString)
	{
		FormulaAddInData *data = new FormulaAddInData();
		data->nVarType = 2;
		data->isNull = isNull;
		data->dVal = 0.0;
		data->pVal = pString;
		return data;
	}
};
