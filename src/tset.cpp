// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество - реализация через битовые поля

#include <iostream>
#include "tbitfield.h"
#include "tset.h"

TSet::TSet(size_t mp) : bitField(1) {}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf) {}

TSet::operator TBitField()
{
    return TBitField(1);
}

size_t TSet::getMaxPower() const // получить макс. к-во эл-тов
{
    return 0;
}

bool TSet::isMember(const uint elem) const // элемент множества?
{
    return false;
}

void TSet::insElem(const uint elem) // включение элемента множества
{

}

void TSet::delElem(const uint elem) // исключение элемента множества
{

}

// теоретико-множественные операции
TSet& TSet::operator=(const TSet &s) // присваивание
{
    return *this;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
    return false;
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    return true;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    return TSet(1);
}

TSet TSet::operator+(const uint elem) // объединение с элементом
{
    return TSet(1);
}

TSet TSet::operator-(const uint elem) // разность с элементом
{
    return TSet(1);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    return TSet(1);
}

TSet TSet::operator~() // дополнение
{
    return TSet(1);
}

// перегрузка ввода/вывода
std::istream &operator>>(std::istream &istr, TSet &s) // ввод
{
    return istr;
}

std::ostream& operator<<(std::ostream &ostr, const TSet &s) // вывод
{
    return ostr;
}
