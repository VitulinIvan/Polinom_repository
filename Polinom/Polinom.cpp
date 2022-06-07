#include <math.h>

#include "Polinom.h"

TPolinom::TPolinom() :TList<TMonomData>()
{
}

TPolinom::TPolinom(TPolinom& _v) : TList<TMonomData>(_v)
{
}

TPolinom::~TPolinom()
{
}

TPolinom& TPolinom::operator=(const TPolinom& _v)
{
    if (this == &_v) {
        return *this;
    }
    if (this->root != 0)
    {
        TMonom* i = static_cast<TMonom*>(this->root);
        TMonom* p = 0;
        while (i != 0)
        {
            p = i;
            i = i->GetNext();
            delete p;
        }
        root = 0;
    }
    this->count = _v.count;
    TMonom* i = static_cast<TMonom*>(_v.root);
    while (i != 0)
    {
        *this += *i;
        i = i->GetNext();
    }
    return *this;
}

TPolinom& TPolinom::operator+=(TMonom& _v)
{
    if (this->root == 0)
    {
        this->root = _v.Clone();
        this->end = this->root;
        this->count++;
    }
    else
    {
        TMonom* temp = static_cast<TMonom*>(this->root);
        while (temp != 0)
            if (*temp == _v)
            {
                temp->SetK(temp->GetK() + _v.GetK());
                return *this;
            }
            else
            {
                TMonom* _v2 = _v.Clone();
                if (*temp < _v)
                {
                    _v2->SetPrev(temp->GetPrev());
                    _v2->SetNext(temp);

                    if (temp->GetPrev() != 0)
                        temp->GetPrev()->SetNext(_v2);
                    else
                        this->root = _v2;

                    temp->SetPrev(_v2);
                    this->count++;
                    return *this;
                }
                else if (temp->GetNext() == 0)
                {
                    _v2->SetPrev(temp);
                    temp->SetNext(_v2);
                    this->end = _v2;
                    this->count++;
                    return *this;
                }
                else
                    temp = temp->GetNext();
            }
    }
    return *this;
}

TPolinom TPolinom::operator*(const TPolinom& _v)
{
    TPolinom res;
    TMonom* tmp1 = static_cast<TMonom*>(this->root);
    if (this->root == 0 && _v.root == 0)
        throw - 1;
    while (tmp1 != 0)
    {
        TMonom* tmp2 = static_cast<TMonom*>(_v.root);
        while (tmp2 != 0)
        {
            TMonom tmp3 = *tmp2 * *tmp1;
            res += tmp3;
            tmp2 = tmp2->GetNext();
        }
        tmp1 = tmp1->GetNext();
    }
    return res;
}

TPolinom TPolinom::operator+(const TPolinom& _v)
{
    if (_v.root == 0 || this->root == 0)
        throw - 1;
    TPolinom res;
    TMonom* tmp1 = static_cast<TMonom*>(_v.root);
    TMonom* tmp2 = static_cast<TMonom*>(this->root);
    TMonom* r = 0;

    while (tmp1 != 0 && tmp2 != 0)
    {
        TMonom tmp3;
        if (*tmp1 == *tmp2)
        {
            tmp3 = (*tmp1 + *tmp2)[0];
            tmp1 = tmp1->GetNext();
            tmp2 = tmp2->GetNext();
        }
        else if (*tmp1 < *tmp2)
        {
            tmp3 = *tmp2;
            tmp2 = tmp2->GetNext();
        }
        else
        {
            tmp3 = *tmp1;
            tmp1 = tmp1->GetNext();
        }

        if (r == 0)
        {
            res += tmp3;
            r = static_cast<TMonom*>(res.root);
        }
        else
        {
            r->SetNext(tmp3.Clone());
            r->GetNext()->SetPrev(static_cast<TMonom*>(r));
            r = r->GetNext();
        }
    }
    if (tmp1 != 0)
        while (tmp1 != 0)
        {
            r->SetNext(tmp1->Clone());
            r->GetNext()->SetPrev(static_cast<TMonom*>(r));
            r = r->GetNext();
            tmp1 = tmp1->GetNext();
        }
    else if (tmp2 != 0)
        while (tmp2 != 0)
        {
            r->SetNext(tmp2->Clone());
            r->GetNext()->SetPrev(static_cast<TMonom*>(r));
            r = r->GetNext();
            tmp2 = tmp2->GetNext();
        }
    return res;
}

TPolinom TPolinom::operator-(const TPolinom& _v)
{
    if (_v.root == 0 || this->root == 0)
        throw - 1;
    TPolinom res;
    TMonom* tmp1 = static_cast<TMonom*>(_v.root);
    TMonom* tmp2 = static_cast<TMonom*>(this->root);
    TMonom* r = 0;
    while (tmp1 != 0 && tmp2 != 0)
    {
        TMonom tmp3;
        if (*tmp1 == *tmp2)
        {
            tmp3 = (*tmp1 + *tmp2)[0];
            tmp1 = tmp1->GetNext();
            tmp2 = tmp2->GetNext();
        }
        else if (*tmp1 < *tmp2)
        {
            tmp3 = *tmp2;
            tmp2 = tmp2->GetNext();
        }
        else
        {
            tmp1->SetK(tmp1->GetK() * (-1));
            tmp3 = *tmp1;
            tmp1 = tmp1->GetNext();
        }
        if (r == 0)
        {
            res += tmp3;
            r = static_cast<TMonom*>(res.root);
        }
        else
        {
            r->SetNext(tmp3.Clone());
            r->GetNext()->SetPrev(static_cast<TMonom*>(r));
            r = r->GetNext();
        }
    }
    if (tmp1 != 0)
        while (tmp1 != 0)
        {
            r->SetNext(tmp1->Clone());
            r->GetNext()->SetPrev(static_cast<TMonom*>(r));
            r = r->GetNext();
            tmp1 = tmp1->GetNext();
        }
    else if (tmp2 != 0)
        while (tmp2 != 0)
        {
            r->SetNext(tmp2->Clone());
            r->GetNext()->SetPrev(static_cast<TMonom*>(r));
            r = r->GetNext();
            tmp2 = tmp2->GetNext();
        }
    return res;
}

string TPolinom::GetPolinom()
{
    string res = "";
    TMonom* i = static_cast<TMonom*>(root);
    while (i != 0)
    {
        res += i->GetMonom();
        i = i->GetNext();
    }
    return res;
}

ostream& operator<<(ostream& ostr, const TPolinom& P)
{
    if (P.IsEmpty())
        return ostr;
    TMonom* i = static_cast<TMonom*>(P.root);
    ostr << *i;
    i = i->GetNext();
    while (i != 0)
    {
        if (i->GetK() > 0)
            ostr << "+";
        ostr << *i;
        i = i->GetNext();
    }
    return ostr;
}

istream& operator>>(istream& istr, TPolinom& P)
{
    int count;
    istr >> count;
    TPolinom res;
    for (int i = 0; i < count; i++)
    {
        TMonom tmp;
        istr >> tmp;
        res += tmp;
    }
    P = res;
    return istr;
}

ofstream& operator<<(ofstream& ofstr, const TPolinom& P)
{
    if (P.IsEmpty())
        return ofstr;
    TMonom* i = static_cast<TMonom*>(P.root);
    while (i != 0)
    {
        ofstr << *i;
        i = i->GetNext();
    }
    return ofstr;
}

void TPolinom::WriteToFile(string filename)
{
    ofstream fout(filename.c_str());
    fout << *this;
    fout.close();
}

