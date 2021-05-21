#pragma once

#include "ListElem.h"
#include "ListIterator.h"
#include <vector>

template <class T1>
class TListIterator;

template <class T>
class TList
{
protected:
    TListElem<T>* root;
    TListElem<T>* end;
    int count;
public:
    TList();
    TList(TList<T>& _v);
    virtual ~TList();
    virtual TList<T>& operator =(TList<T>& _v);
    void InsFirst(T d);
    void InsLast(T d);
    void Ins(TListIterator<T> e, T d);
    bool IsEmpty(void) const;
    bool IsFull(void) const;
    TListIterator<T> begin();
    TListElem<T>* GetFirst();
    TListElem<T>* GetLast();
    int GetCount();
    void DelFirst();
    void DelLast();
    void Del(TListIterator<T> e);
    template <class T1>
    friend ostream& operator<<(ostream& ostr, const TList<T1>& L);
    template <class T1>
    friend istream& operator>>(istream& istr, TList<T1>& L);
    vector<int> ElemsModZero(int n); 
    void WriteToFile(string filename); 
    template <class T1>
    friend ofstream& operator<<(ofstream& ofstr, const TList<T1>& L);
    template <class T1>
    friend class TListIterator;
};

template<class T>
inline TList<T>::TList()
{
    root = 0;
    end = 0;
    count = 0;
}

template <class T>
TList<T>::TList(TList<T>& _v)
{
    this->count = _v.count;
    TListElem<T>* i = _v.root;
    TListElem<T>* j = this->root;
    TListElem<T>* p = 0;
    root = 0;
    end = 0;
    while (i != 0)
    {
        j = i->Clone();
        j->SetNext(0);
        if (p != 0)
        {
            p->SetNext(j);
            j->SetPrev(p);
        }
        p = j;
        end = j;
        if (root == 0)
            root = j;
        i = i->GetNext();
    }
}

template <class T>
TList<T>::~TList()
{
    if (root != 0)
    {
        TListElem<T>* i = root;
        TListElem<T>* p = 0;

        while (i != 0)
        {
            p = i;
            i = i->GetNext();
            delete p;
        }
        root = 0;
        end = 0;
        count = 0;
    }
}

template <class T>
TList<T>& TList<T>::operator=(TList<T>& _v)
{
    if (this == &_v)
        return *this;
    if (root != 0)
    {
        TListElem<T>* i = root;
        TListElem<T>* p = 0;

        while (i != 0)
        {
            p = i;
            i = i->GetNext();
            delete p;
        }

        root = 0;
        end = 0;
        count = 0;
    }

    this->count = _v.count;

    TListElem<T>* i = _v.root;
    TListElem<T>* j = this->root;
    TListElem<T>* p = 0;

    while (i != 0)
    {
        j = i->Clone();
        j->SetNext(0);

        if (p != 0)
        {
            p->SetNext(j);
            j->SetPrev(p);
        }

        p = j;
        end = j;

        if (root == 0)
            root = j;

        i = i->GetNext();
    }
}

template<class T>
inline void TList<T>::InsFirst(T d)
{
    if (this->IsFull())
        throw - 1;
    TListElem<T>* tmp = d.Clone();
    tmp->SetNext(root);
    root = tmp;
    if (end == 0)
        end = tmp;
    count++;
}

template<class T>
inline void TList<T>::InsLast(T d)
{
    if (this->IsFull())
        throw - 1;
    TListElem<T>* tmp = d.Clone();
    if (end != 0)
    {
        end->SetNext(tmp);
        tmp->SetPrev(end);
    }
    end = d.Clone();
    if (root == 0)
        root = tmp;
    count++;
}

template<class T>
inline void TList<T>::Ins(TListIterator<T> e, T d)
{
    if (this->IsFull())
        throw - 1;
    TListElem<T>* tmp = d.Clone();
    tmp->SetNext(e.elem->GetNext());
    tmp->SetPrev(e.elem);
    if (e.elem->GetNext() != 0)
        e.elem->GetNext()->SetPrev(tmp);
    else
        end = tmp;
    e.elem->SetNext(tmp);
    count++;
}

template<class T>
inline bool TList<T>::IsEmpty(void) const
{
    return count == 0;
}

template<class T>
inline bool TList<T>::IsFull(void) const
{
    try
    {
        TListElem<T>* tmp = new TListElem<T>(0);
        delete tmp;
        return false;
    }
    catch (...)
    {
        return true;
    }
}

template<class T>
inline TListIterator<T> TList<T>::begin()
{
    return TListIterator<T>(root);
}

template<class T>
inline TListElem<T>* TList<T>::GetFirst()
{
    return root;
}

template<class T>
inline TListElem<T>* TList<T>::GetLast()
{
    return end;
}

template<class T>
inline void TList<T>::DelFirst()
{
    if (this->IsEmpty())
        throw - 1;
    TListElem<T>* i = root;
    root = root->GetNext();
    count--;
    delete i;
}

template<class T>
inline void TList<T>::DelLast()
{
    if (this->IsEmpty())
        throw - 1;
    TListElem<T>* i = end;
    end = end->GetPrev();
    end->SetNext(0);
    count--;
    delete i;
}

template<class T>
inline void TList<T>::Del(TListIterator<T> e)
{
    if (this->IsEmpty())
        throw - 1;
    e.elem->GetPrev()->SetNext(e.elem->GetNext());
    e.elem->GetNext()->SetPrev(e.elem->GetPrev());
    count--;
    delete e.elem;
}

template<class T>
inline int TList<T>::GetCount()
{
    return count;
}

template <class T1>
ostream& operator<<(ostream& ostr, const TList<T1>& L) 
{
    if (L.IsEmpty())
        return ostr;
    TListElem<T1>* i = L.root;
    while (i != 0)
    {
        ostr << *i << endl;
        i = i->GetNext();
    }
    return ostr;
}

template <class T1>
istream& operator>>(istream& istr, TList<T1>& L)
{
    if (L.IsFull())
        throw - 1;
    int count;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        T1 d;
        istr >> d;
        L.InsLast(d);
    }
    return istr;
}

template<class T1>
inline ofstream& operator<<(ofstream& ofstr, TList<T1>& L)
{
    if (L.IsEmpty())
        return ofstr;
    for (TListIterator<int> iter = L.begin(); !iter.IsEmpty(); ++iter)
        ofstr << *iter;
    return ofstr;
}

template<class T>
vector<int> TList<T>::ElemsModZero(int n)
{
    vector<int> res;
    if (this->IsEmpty())
        return res;
    for (TListIterator<int> iter = this->begin(); !iter.IsEmpty(); ++iter)
        if (*iter % n == 0)
            res.push_back(*iter);
}

template<class T>
inline void TList<T>::WriteToFile(string filename)
{
    ofstream fout(filename.c_str());
    fout << *this;
    fout.close();
}



