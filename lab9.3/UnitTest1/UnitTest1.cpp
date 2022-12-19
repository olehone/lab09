#include "pch.h"
#include "CppUnitTest.h"
#include "../Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{

			Visitor* v = new Visitor[1];
			v[0].type_of_nomer = DOUBLES;
			int x = TypeOf(v, 0);
			Assert::AreEqual(x, 2);
		}
	};
}
