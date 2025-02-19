#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества
{
    if ((Elem >= MaxPower) || (Elem < 0))
    {
        throw exception("uncorrect element");
    }
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if ((Elem >= MaxPower) || (Elem < 0))
    {
        throw out_of_range("uncorrect element");
    }
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if ((Elem >= MaxPower) || (Elem < 0))
    {
        throw out_of_range("uncorrect element");
    }
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (*this == s)
    {
        return (*this);
    }
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return (*this);
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return s.BitField == BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
     return !(s.BitField == BitField);
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet res(std::max(s.MaxPower, MaxPower));
    res.BitField = BitField | s.BitField;
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if ((Elem >= MaxPower) || (Elem < 0))
    {
        throw out_of_range("uncorrect element");
    }
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if ((Elem >= MaxPower) || (Elem < 0))
    {
        throw out_of_range("uncorrect element");
    }
    TSet res(*this);
    res.DelElem(Elem);
    return res;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet res(s);
    res.BitField = BitField & s.BitField;
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(*this);
    res.BitField = ~res.BitField;
    return res;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int n;
    istr >> n;
    if ((n <= 0) || (n > s.MaxPower))
        throw out_of_range("out of range");
    for (int i = 0; i < n; i++)
    {
        int element;
        istr >> element;
        if ((element < 0) || (element >= s.MaxPower))
            throw out_of_range("out of range");
        s.InsElem(element);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.MaxPower; i++)
    {
        if (s.IsMember(i))
            ostr << i << ' ';
    }
    ostr << "\n";
    return ostr;
}
