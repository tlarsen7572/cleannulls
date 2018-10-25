#include "stdafx.h"
#include "CppUnitTest.h"
#include "customformulas.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(CleanNulls_Tests)
{
public:
	TEST_METHOD(NullStringReturnsEmpty)
	{
		FormulaAddInData *data = CreateNullData(2);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = CleanNulls(1, data, pReturnValue);
			
		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(L"", pReturnValue->pVal);
		Assert::AreEqual(0, pReturnValue->isNull);
		Assert::AreEqual(2, pReturnValue->nVarType);
	}

	TEST_METHOD(NullDoubleReturnZero)
	{
		FormulaAddInData *data = CreateNullData(1);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = CleanNulls(1, data, pReturnValue);

		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(0.0, pReturnValue->dVal);
		Assert::AreEqual(0, pReturnValue->isNull);
		Assert::AreEqual(1, pReturnValue->nVarType);
	}

	TEST_METHOD(PopulatedStringHasNoChange)
	{
		FormulaAddInData *data = CreatePopulatedData(2);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = CleanNulls(1, data, pReturnValue);

		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(L"Hello world", pReturnValue->pVal);
		Assert::AreEqual(0, pReturnValue->isNull);
		Assert::AreEqual(2, pReturnValue->nVarType);
	}

	TEST_METHOD(PopulatedDoubleHasNoChange)
	{
		FormulaAddInData *data = CreatePopulatedData(1);
		FormulaAddInData *pReturnValue = CreateReturnValue();

		int returnCode = CleanNulls(1, data, pReturnValue);

		Assert::AreEqual(1, returnCode);
		Assert::AreEqual(10.0, pReturnValue->dVal);
		Assert::AreEqual(0, pReturnValue->isNull);
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

	FormulaAddInData * CreatePopulatedData(int varType)
	{
		return CreateData(0, varType);
	}

	FormulaAddInData * CreateNullData(int varType)
	{
		return CreateData(1, varType);
	}

	FormulaAddInData * CreateData(int isNull, int varType)
	{
		FormulaAddInData *data = new FormulaAddInData();
		data->nVarType = varType;
		data->isNull = isNull;
		data->dVal = 10.0;
		data->pVal = L"Hello world";
		return data;
	}
};
