// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля

#include <iostream>
#include "tbitfield.h"
#include "tset.h"

TSet::TSet(size_t mp) : bitField(mp) {
    maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : bitField(s.bitField) {
    this->bitField = s.bitField;
    maxPower = s.maxPower;

}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : bitField(bf) {
    maxPower = bf.getLength();
    bitField = bf;
}

TSet::operator TBitField()
{
    TBitField ans(maxPower);
    ans = this->bitField;
    return ans;
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return maxPower;
}

bool TSet::isMember(const myuint elem) const // элемент множества?
{
    if (bitField.getBit(elem))
    {
        return true;
    }
    return false;
}

void TSet::insElem(const myuint elem) // включение элемента множества
{
    bitField.setBit(elem);
}

void TSet::delElem(const myuint elem) // исключение элемента множества
{
    bitField.clrBit(elem);
}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (*this != s)
    {
        this->maxPower = s.maxPower;
        this->bitField = s.bitField;

    }
    return *this;
}

bool TSet::operator==(const TSet& s) const // сравнение
{
    if (this->bitField == s.bitField)
        return true;
    return false;
}

bool TSet::operator!=(const TSet& s) const // сравнение
{
    if (this->bitField == s.bitField)
        return false;
    return true;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    if (this->maxPower < s.maxPower)
    {
        TSet ans(s.maxPower);
        for (int i = 0; i < s.maxPower; i++)
        {
            if (s.bitField.getBit(i))
                ans.insElem(i);
        }
        for (int i = 0; i < maxPower; i++)
            if (bitField.getBit(i))
                ans.insElem(i);
        return ans;
    }
    else
    {
        TSet ans(maxPower);
        for (int i = 0; i < maxPower; i++)
        {
            if (bitField.getBit(i))
                ans.insElem(i);
        }
        for (int i = 0; i < s.getMaxPower(); i++)
            if (s.bitField.getBit(i))
                ans.insElem(i);
        return ans;

    }

}

TSet TSet::operator+(const myuint elem) // объединение с элементом
{
    bitField.setBit(elem);
    return *this;
}

TSet TSet::operator-(const myuint elem) // разность с элементом
{
    return TSet(1);
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    int max = 0;
    if (s.maxPower < maxPower)
    {
        max = maxPower;
    }
    else
        max = s.maxPower;

    TBitField ans(max);
    ans = bitField & s.bitField;


    return TSet(ans);
}

TSet TSet::operator~() // дополнение
{
    TSet ans(maxPower);
    ans.bitField = ~(bitField);

    return ans;
}

// перегрузка ввода/вывода
std::istream& operator>>(std::istream& istr, TSet& s) // ввод
{
    using namespace std;

    istr >> s.maxPower;
    istr >> s.bitField;

    
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TSet& s) // вывод
{
    ostr << s.bitField;
    return ostr;
}
