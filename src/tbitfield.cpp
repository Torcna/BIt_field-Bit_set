// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"

TBitField::TBitField(size_t len)
{
    bitLen = len;
    memLen = 1 + len / capacity();
    this->pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++)
    {
        this->pMem[i] = this->pMem[i] & 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{

}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    return (n/sizeof(uint)*8);
}

uint TBitField::getMask(const size_t n) const // битовая маска для бита n
{
    uint temp = 0;
    temp = temp | 1 << (n % (sizeof(uint) * 8));
    return temp;
}

// доступ к битам битового поля
uint TBitField::getLength() const // получить длину (к-во битов)
{
    return bitLen;
}

size_t TBitField::getNumBytes() const // получить количество байт выделенной памяти
{
    return memLen * sizeof(uint);
}

void TBitField::setBit(const size_t n) // установить бит
{
    int elemPosArray = getIndex(n);
    pMem[elemPosArray] = pMem[elemPosArray] | 1 << (n % capacity()) - 1;
}

void TBitField::clrBit(const size_t n) // очистить бит
{
    int elemPosArray = getIndex(n);
    uint mask = ~(getMask(n));
    this->pMem[elemPosArray] = pMem[elemPosArray] & mask;
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    int elemPosArray = getIndex(n);
    int number_in_uint = n % (sizeof(uint)*8);
    uint temp = (uint)pMem[elemPosArray];
    int t=0;
    int ans = 0;
    while (temp)
    {
        ans = temp % 2;
        t++;
        if ((sizeof(uint) * 8) == n - t + 1)
        {
            return ans;
        }
        
        temp /= 2;
    }
}

// битовые операции
TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    delete[] pMem;
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    this->pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++)
    {
        this->pMem[i] = bf.pMem[i];
    }
    return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (bf.bitLen != this->bitLen)
        return false;
    return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return TBitField(1);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return TBitField(1);
}

TBitField TBitField::operator~() // отрицание
{
    return TBitField(1);
}

TBitField::~TBitField()
{

}

// ввод/вывод
std::istream &operator>>(std::istream &istr, TBitField &bf) // ввод
{
    return istr;
}

std::ostream &operator<<(std::ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
