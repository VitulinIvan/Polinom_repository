#pragma once

#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class TListElem
{
protected:
	T data;
	TListElem* next;
	TListElem* prev;
public:
	TListElem(T _data);
	~TListElem();
	T& GetData();
	virtual TListElem* GetNext();
	TListElem* GetPrev();
	void SetData(T _data);
	void SetNext(TListElem* _next);
	void SetPrev(TListElem* _prev);
	virtual TListElem<T>* Clone();
	template <class T1>
	friend ostream& operator<< (ostream& ostr, const TListElem<T1>& E);
	template <class T1>
	friend istream& operator >> (istream& istr, TListElem<T1>& E);
	template <class T1>
	friend ofstream& operator<<(ofstream& ofstr, const TListElem<T1>& E);
};

template<class T>
inline TListElem<T>::TListElem(T _data)
{
	this->data = _data;
	next = 0;
	prev = 0;
}

template<class T>
inline TListElem<T>::~TListElem()
{
	next = 0;
	prev = 0;
}

template<class T>
inline T& TListElem<T>::GetData()
{
	return data;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetNext()
{
	return next;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetPrev()
{
	return prev;
}

template<class T>
inline void TListElem<T>::SetData(T _data)
{
	this->data = _data;
}

template<class T>
inline void TListElem<T>::SetNext(TListElem<T>* _next)
{
	this->next = _next;
}

template<class T>
inline void TListElem<T>::SetPrev(TListElem<T>* _prev)
{
	this->prev = _prev;
}

template<class T>
inline TListElem<T>* TListElem<T>::Clone()
{
	TListElem<T>* res = new TListElem<T>(*this);
	return res;
}

template<class T1>
inline ostream& operator<<(ostream& ostr, const TListElem<T1>& E)
{
	ostr << E.data;
	return ostr;
}

template<class T1>
inline istream& operator>>(istream& istr, TListElem<T1>& E)
{
	istr >> E.data;
	return istr;
}

template<class T1>
inline ofstream& operator<<(ofstream& ofstr, const TListElem<T1>& E)
{
	ofstr << E.data;
	return ofstr;
}

