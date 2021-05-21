#include <iostream>
#include "Monom.h"
#include "Polinom.h"

using namespace std;

int main()
{
	TMonom a(new double[3]{ 1,2,3 }, 3, 1);
	TMonom b(new double[3]{ 3,2,1 }, 3, 1);
	
	TMonom c(new double[3]{ 1,1,1 }, 3, 1);
	TMonom d(new double[3]{ 2,2,2 }, 3, 1);

	TPolinom p1, p2, p3;

	p1 += a;
	p1 += b;

	p2 += c;
	p2 += d;

	p3 = p1 * p2;
	cout << p3 << endl;
	p3 = p1 + p2;
	cout << p3 << endl;
	p3 = p1 - p2;
	cout << p3 << endl;
	return 0;
}