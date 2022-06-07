#pragma once

#include <iostream>

using namespace std;

template <class T1>
class TListElem;

template <class T1>
class TList;

template <class T> 
class TListIterator
{
    protected:
        TListElem<T>* elem;
    public:
        TListIterator();
        TListIterator(TListElem<T>* _elem);
        TListIterator(const TListIterator<T>& _v);
        TListIterator<T>& operator =(const TListIterator<T>& _v);
        bool IsEmpty();
        TListIterator<T>& operator++();
        TListIterator<T>& operator--();
        T& operator*(int);
        T& operator*();
        template <class T1>
        friend class TList;
};

template<class T>
inline TListIterator<T>::TListIterator()
{
    elem = 0;
}

template<class T>
inline TListIterator<T>::TListIterator(TListElem<T>* _elem)
{
    this->elem = _elem;
}

template<class T>
inline TListIterator<T>::TListIterator(const TListIterator<T>& _v)
{
    this->elem = _v.elem;
}

template<class T>
inline TListIterator<T>& TListIterator<T>::operator=(const TListIterator<T>& _v)
{
    this->elem = _v.elem;
}

template<class T>
inline bool TListIterator<T>::IsEmpty()
{
    return elem == 0;
}

template<class T>
inline TListIterator<T>& TListIterator<T>::operator++()
{
    if (!IsEmpty())
        elem = elem->GetNext();
    else
        throw - 1;
    return *this;
}

template<class T>
inline TListIterator<T>& TListIterator<T>::operator--()
{
    if (!IsEmpty())
        elem = elem->GetPrev();
    else
        throw - 1;
    return *this;
}

template<class T>
inline T& TListIterator<T>::operator*(int)
{
    if (elem == 0)
        throw - 1;
    return elem->GetData();
}

template<class T>
inline T& TListIterator<T>::operator*()
{
    if (elem == 0)
        throw - 1;
    return elem->GetData();
}