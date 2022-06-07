
#include "Monom.h"

TMonom::TMonom(TMonomData _data) : TListElem<TMonomData>(_data)
{
}

TMonom::TMonom(double* _data, int _dim, double _K) : TListElem<TMonomData>(0)
{
    if (_dim < 0)
        throw - 1;
    this->data.dim = _dim;
    this->data.K = _K;
    if (this->data.dim > 0)
    {
        this->data.data = new double[data.dim];
        for (int i = 0; i < data.dim; i++)
            this->data.data[i] = _data[i];
    }
}

TMonom::TMonom(const TMonom& _v) :TListElem<TMonomData>(_v)
{
    prev = 0;
    next = 0;
}

TMonom::~TMonom()
{
}

bool TMonom::operator==(const TMonom& _v)
{
    if (this->data.dim != _v.data.dim)
        throw - 1;

    if (this->data.dim > 0)
    {
        for (int i = 0; i < data.dim; i++)
            if (this->data.data[i] != _v.data.data[i])
                return false;
        return true;
    }
    else
        return this->data.K == _v.data.K;
}

bool TMonom::operator!=(const TMonom& _v)
{
    return !this->operator==(_v);
}

bool TMonom::operator>(const TMonom& _v)
{
    if (this->data.dim != _v.data.dim)
        throw - 1;
    if (this->data.dim > 0)
    {
        for (int i = 0; i < data.dim; i++)
            if (this->data.data[i] > _v.data.data[i])
                return true;
            else if (this->data.data[i] < _v.data.data[i])
                return false;
        return false;
    }
    else
        return this->data.K > _v.data.K;
}

bool TMonom::operator<(const TMonom& _v)
{
    if (this->data.dim != _v.data.dim)
        throw - 1;
    if (this->data.dim > 0)
    {
        for (int i = 0; i < data.dim; i++)
            if (this->data.data[i] < _v.data.data[i])
                return true;
            else if (this->data.data[i] > _v.data.data[i])
                return false;
        return false;
    }
    else
        return this->data.K < _v.data.K;
}

TMonomData& TMonom::operator*(int)
{
    return data;
}

TMonom* TMonom::GetNext()
{
    return static_cast<TMonom*>(next);
}

TMonomData& TMonom::operator*()
{
    return data;
}

double TMonom::GetK()
{
    return data.K;
}

TMonom* TMonom::Clone()
{
    TMonom* res = new TMonom(*this);
    return res;
}

void TMonom::SetK(double _K)
{
    this->data.K = _K;
}

int TMonom::GetDim()
{
    return data.dim;
}

void TMonom::SetDim(int _dim)
{
    if (this->data.dim == _dim)
        return;
    if (_dim < 0)
        throw - 1;
    else if (_dim == 0)
    {
        if (this->data.dim > 0)
            delete[] data.data;
        this->data.dim = 0;
        data.data = 0;
    }
    else
    {
        if (this->data.dim > 0)
            delete[] data.data;
        data.data = new double[this->data.dim];
        for (int i = 0; i < this->data.dim; i++)
            data.data[i] = 0;
    }
}

string TMonom::GetMonom()
{
    string res = "";
    if (data.K < 0)
    {
        res += "-";
        res += data.K * (-1) + '0';
    }
    else
        res += data.K + '0';
    for (int i = 0; i < data.dim; i++)
        if (data.data[i] < 0)
        {
            res += "-";
            res += data.data[i] * (-1) + '0';
        }
        else
            res += data.data[i] + '0';
    return res;
}


TMonom& TMonom::operator=(const TMonom& _v)
{
    if (this == &_v)
        return *this;
    this->next = 0;
    this->prev = 0;
    this->data.K = _v.data.K;

    if (this->data.dim == _v.data.dim)
    {
        for (int i = 0; i < this->data.dim; i++)
            this->data.data[i] = _v.data.data[i];
    }
    else if (_v.data.dim == 0)
    {
        if (this->data.dim > 0)
            delete[] this->data.data;
        this->data.dim = 0;
        this->data.data = 0;
    }
    else
    {
        if (this->data.dim > 0)
            delete[] this->data.data;
        this->data.dim = _v.data.dim;
        this->data.data = new double[this->data.dim];
        for (int i = 0; i < this->data.dim; i++)
            this->data.data[i] = _v.data.data[i];
    }
}

double& TMonom::operator[](int i)
{
    return data.data[i];
}

TMonom TMonom::operator*(const TMonom& _v)
{
    if (this->data.dim != _v.data.dim)
        throw - 1;
    TMonom tmp(*this);
    tmp.data.K = this->data.K * _v.data.K;

    for (int i = 0; i < tmp.data.dim; i++)
        tmp.data.data[i] = this->data.data[i] + _v.data.data[i];
    return tmp;
}

TMonom TMonom::operator/(const TMonom& _v)
{
    if (this->data.dim != _v.data.dim)
        throw - 1;
    TMonom tmp(*this);
    tmp.data.K = this->data.K / _v.data.K;
    for (int i = 0; i < tmp.data.dim; i++)
        tmp.data.data[i] = this->data.data[i] - _v.data.data[i];
    return tmp;
}

TMonom* TMonom::operator+(const TMonom& _v)
{
    if (this->data.dim != _v.data.dim)
        throw - 1;
    TMonom* tmp = 0;
    if (*this == _v)
    {
        tmp = new TMonom(*this);
        tmp->data.K = this->data.K + _v.data.K;
    }
    else
    {
        tmp = new TMonom[2];
        if (*this > _v)
        {
            tmp[0] = *this;
            tmp[1] = _v;
        }
        else
        {
            tmp[1] = *this;
            tmp[0] = _v;
        }
    }
    return tmp;
}

TMonom* TMonom::operator-(const TMonom& _v)
{
    if (this->data.dim != _v.data.dim)
        throw - 1;
    TMonom* tmp = 0;
    if (*this == _v)
    {
        tmp = new TMonom(*this);
        tmp->data.K = this->data.K - _v.data.K;
    }
    else
    {
        tmp = new TMonom[2];
        if (*this > _v)
        {
            tmp[0] = *this;
            tmp[1] = _v;
        }
        else
        {
            tmp[1] = *this;
            tmp[0] = _v;
        }
    }
    return tmp;
}

ostream& operator<<(ostream& ostr, const TMonom& M)
{
    ostr << M.data.K;
    for (int i = 0; i < M.data.dim; i++)
        ostr << " * x[" << i << "] ^ " << M.data.data[i];
    ostr << " ";
    return ostr;
}

istream& operator>>(istream& istr, TMonom& M)
{
    int dim = 0;
    if (M.data.dim != 0)
        dim = M.data.dim;
    else
    {
        istr >> dim;
        M.SetDim(dim);
    }
    istr >> M.data.K;
    for (int i = 0; i < M.data.dim; i++)
        istr >> M.data.data[i];
    return istr;
}

ofstream& operator<<(ofstream& ofstr, const TMonom& M)
{
    ofstr << M.data.K;
    for (int i = 0; i < M.data.dim; i++)
        ofstr << M.data.data[i];
    return ofstr;
}

TMonomData::TMonomData(int t)
{
    if (t < 0)
        throw - 1;
    if (t == 0)
    {
        dim = 0;
        data = 0;
    }
    else
    {
        dim = t;
        data = new double[dim];
        for (int i = 0; i < dim; i++)
            data[i] = 0;
    }
    K = 0;
}

TMonomData::TMonomData(double* _data, int _dim, double _K)
{
    if (_dim < 0)
        throw - 1;
    this->dim = _dim;
    this->K = _K;
    this->data = 0;

    if (this->dim > 0)
    {
        this->data = new double[dim];
        for (int i = 0; i < dim; i++)
            this->data[i] = _data[i];
    }
}

TMonomData::TMonomData(const TMonomData& _v)
{
    this->dim = _v.dim;
    this->K = _v.K;
    this->data = 0;
    if (this->dim > 0)
    {
        this->data = new double[dim];
        for (int i = 0; i < dim; i++)
            this->data[i] = _v.data[i];
    }
}

TMonomData::~TMonomData()
{
    if (data != 0)
    {
        delete[] data;
        data = 0;
        dim = 0;
        K = 0;
    }
}