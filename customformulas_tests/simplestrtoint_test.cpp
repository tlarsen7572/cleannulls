#include "stdafx.h"
#include "CppUnitTest.h"
#include "customformulas.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(SimpleStrToInt_Tests)
{
public:
	TEST_METHOD(NullReturnZero)
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
	}

	TEST_METHOD(ErrorMoreThan10Chars) {
		FormulaAddInData *data = CreatePopulatedData(L"1234567890A");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = SimpleStrToInt(1, data, pReturnValue);
		Assert::AreEqual(0, returnCode);
		Assert::AreEqual(L"String must be 10 characters or less.", pReturnValue->pVal);
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
	}

	TEST_METHOD(ABCConversion) {
		FormulaAddInData *data = CreatePopulatedData(L"ABC");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = SimpleStrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(41676.0, pReturnValue->dVal);
		Assert::AreEqual(1, pReturnValue->nVarType);
	}

	TEST_METHOD(BlankStringConversion) {
		FormulaAddInData *data = CreatePopulatedData(L"");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = SimpleStrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(0.0, pReturnValue->dVal);
		Assert::AreEqual(1, pReturnValue->nVarType);
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
