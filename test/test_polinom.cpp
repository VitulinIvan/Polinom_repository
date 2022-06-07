#include <../gtest/gtest.h>
#include "Polinom.h"
#include <sstream>

TEST(TPolinom, create_polinom)
{
	ASSERT_NO_THROW(TPolinom());
}

TEST(TPolinom, multiply)
{
	TPolinom P, P1, P2;
	TMonom a(new double[3]{ 1,1,1 }, 3, -1);
	TMonom b(new double[3]{ 2,2,2 }, 3, 1);
	P1 += a;
	P1 += b;
	TMonom c(new double[3]{ 3,2,1 }, 3, 1);
	TMonom d(new double[3]{ 1,2,3 }, 3, -1);
	P2 += c;
	P2 += d;
	P = P1 * P2;
	string res = P.GetPolinom();
	string expPolinom = "1543-1432-13451234";
	EXPECT_EQ(expPolinom, res);
}

TEST(TPolinom, plus)
{
	TPolinom P, P1, P2;
	TMonom a(new double[3]{ 1,1,1 }, 3, -1);
	TMonom b(new double[3]{ 2,2,2 }, 3, 1);
	P1 += a;
	P1 += b;
	TMonom c(new double[3]{ 3,2,1 }, 3, 1);
	TMonom d(new double[3]{ 1,2,3 }, 3, -1);
	P2 += c;
	P2 += d;
	P = P1 + P2;
	string res = P.GetPolinom();
	string expPolinom = "13211222-1123-1111";
	EXPECT_EQ(expPolinom, res);
}

TEST(TPolinom, sub)
{

	TPolinom P, P1, P2;
	TMonom a(new double[3]{ 1,1,1 }, 3, -1);
	TMonom b(new double[3]{ 2,2,2 }, 3, 1);
	P1 += a;
	P1 += b;
	TMonom c(new double[3]{ 3,2,1 }, 3, 1);
	TMonom d(new double[3]{ 1,2,3 }, 3, -1);
	P2 += c;
	P2 += d;
	P = P1 - P2;
	string res = P.GetPolinom();
	string expPolinom = "-132112221123-1111";
	EXPECT_EQ(expPolinom, res);
}


TEST(TPolinom, write_polinom_file)
{
	const int size = 4;
	TPolinom P;
	TMonom a(new double[3]{ 3,2,1 }, 3, 1);
	TMonom b(new double[3]{ 2,1,2 }, 3, -2);
	TMonom c(new double[3]{ 1,2,3 }, 3, 1);
	P += a;
	P += b;
	P += c;
	P.WriteToFile("PolinomOI.txt");
	string expPolinom = "1321-22121123";
	string Polinom = "";
	ifstream fin("PolinomOI.txt");
	fin >> Polinom;
	fin.close();
	EXPECT_EQ(expPolinom, Polinom);
}