#pragma once

#include "Monom.h"

class TPolinom :public TList<TMonomData>
{
public:
	TPolinom();
	TPolinom(TPolinom& _v);
	~TPolinom();
	TPolinom& operator =(const TPolinom& _v);
	TPolinom& operator +=(TMonom& _v);
	TPolinom operator *(const TPolinom& _v);
	TPolinom operator +(const TPolinom& _v);
	TPolinom operator -(const TPolinom& _v);
	string GetPolinom();
	friend ostream& operator <<(ostream& ostr, const TPolinom& P);
	friend istream& operator >>(istream& istr, TPolinom& P);
	void WriteToFile(string filename); //Доп. задание 2
	friend ofstream& operator <<(ofstream& ofstr, const TPolinom& P);

};

//Доп. задания 1 и 3 реализованы в Monom.h