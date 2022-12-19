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

			Student* p = new Student[1];
				p[0].rat_physics = 4;
				p[0].rat_math= 3;
				p[0].rat_prog= 5;
			int x = MiddBal(p,0);
			Assert::AreEqual(x, 4);
		}
	};
}
