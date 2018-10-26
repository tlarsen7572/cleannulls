#include "stdafx.h"
#include "CppUnitTest.h"
#include "customformulas.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

TEST_CLASS(StrToInt_Tests)
{
public:
	TEST_METHOD(NullReturnNull) {
		FormulaAddInData *data = CreateNullData(1);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);

		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	TEST_METHOD(ErrorMoreThanOneArg) {
		FormulaAddInData *data = CreatePopulatedData(L"100");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(2, data, pReturnValue);
		Assert::AreEqual(0, returnCode);
		Assert::AreEqual(L"Only one parameter can be provided.", pReturnValue->pVal);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	TEST_METHOD(ErrorIfNumber) {
		FormulaAddInData *data = new FormulaAddInData();
		data->nVarType = 1;
		data->isNull = 0;
		data->dVal = 0.0;
		data->pVal = L"";

		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);
		Assert::AreEqual(0, returnCode);
		Assert::AreEqual(L"Value must be a string.", pReturnValue->pVal);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	TEST_METHOD(BlankStringConversion) {
		FormulaAddInData *data = CreatePopulatedData(L"");
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(1, pReturnValue->isNull);
	}

	TEST_METHOD(Convert1) {
		const wchar_t * value = L"1";
		FormulaAddInData *data = CreatePopulatedData(value);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(2, pReturnValue->nVarType);
		Assert::AreEqual(0, pReturnValue->isNull);
		Assert::AreEqual(value, pReturnValue->pVal);
	}

	TEST_METHOD(ConvertNeg1) {
		const wchar_t * value = L"-1";
		FormulaAddInData *data = CreatePopulatedData(value);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(2, pReturnValue->nVarType);
		Assert::AreEqual(0, pReturnValue->isNull);
		Assert::AreEqual(value, pReturnValue->pVal);
	}

	TEST_METHOD(ConvertHyphen) {
		const wchar_t * value = L"-";
		FormulaAddInData *data = CreatePopulatedData(value);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);
		Assert::AreEqual(0, returnCode);
		Assert::AreEqual(L"Not a valid integer", pReturnValue->pVal);
	}

	TEST_METHOD(Convert10A0) {
		const wchar_t * value = L"10A0";
		FormulaAddInData *data = CreatePopulatedData(value);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);
		Assert::AreEqual(0, returnCode);
		Assert::AreEqual(L"Not a valid integer", pReturnValue->pVal);
	}

	TEST_METHOD(Convert100) {
		const wchar_t * value = L"100";
		FormulaAddInData *data = CreatePopulatedData(value);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(value, pReturnValue->pVal);
	}

	TEST_METHOD(ConvertNeg100) {
		const wchar_t * value = L"-100";
		FormulaAddInData *data = CreatePopulatedData(value);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = StrToInt(1, data, pReturnValue);
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(value, pReturnValue->pVal);
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
