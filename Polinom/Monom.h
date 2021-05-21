#pragma once

#include "List.h"

class TMonomData
{
public:
	double* data;
	double K;
	int dim;
	TMonomData(int t);
	TMonomData(double* _data = 0, int _dim = 0, double _K = 0);
	TMonomData(const TMonomData& _v);
	~TMonomData();
};

class TMonom : public TListElem<TMonomData>
{
public:
	TMonom(TMonomData _data);
	TMonom(double* _data = 0, int _dim = 0, double _K = 0);
	TMonom(const TMonom& _v);
	~TMonom();
	bool operator ==(const TMonom& _v);
	bool operator !=(const TMonom& _v);
	bool operator >(const TMonom& _v);
	bool operator <(const TMonom& _v);
	TMonomData& operator*(int);
	TMonomData& operator*();
	virtual TMonom* GetNext();
	virtual TMonom* Clone();
	double GetK();
	void SetK(double _K);
	int GetDim();
	void SetDim(int _dim);
	string GetMonom();
	TMonom& operator =(const TMonom& _v);
	double& operator [](int i);
	TMonom operator *(const TMonom& _v);
	TMonom operator /(const TMonom& _v);
	TMonom* operator +(const TMonom& _v);
	TMonom* operator -(const TMonom& _v);
	friend ostream& operator <<(ostream& ostr, const TMonom& M);
	friend istream& operator >>(istream& istr, TMonom& M);
	friend ofstream& operator <<(ofstream& ofstr, const TMonom& M);
};