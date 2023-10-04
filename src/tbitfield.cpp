// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#include <limits>
#include <iostream>
#include "tbitfield.h"
#include <string>
#include<exception>

class FatalError : private std::exception
{

};


TBitField::TBitField(size_t len)
{
    bitLen = len;
    if (len > 0)
        memLen = 1 + len / capacity();
    else if (len == 0)
        memLen = 0;

    this->pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++)
    {
        this->pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    this->bitLen = bf.bitLen;
    this->memLen = bf.memLen;
    this->pMem = new uint[memLen];
    for (int i = 0; i < this->memLen; i++)
    {
        this->pMem[i] = bf.pMem[i];
    }
}

size_t TBitField::getIndex(const size_t n) const  // индекс в pМем для бита n
{
    return (n / (sizeof(uint) * 8));
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
    if (bitLen < n)
    {
        FatalError a;
        throw a;
    }
    else
    {
        int elemPosArray = getIndex(n);
        pMem[elemPosArray] = pMem[elemPosArray] | getMask(n);
    }

}

void TBitField::clrBit(const size_t n) // очистить бит
{
    if ((bitLen < n) || (n < 0))
    {
        FatalError a;
        throw a;
    }
    else
    {
        int elemPosArray = getIndex(n);
        uint mask = ~(getMask(n));
        this->pMem[elemPosArray] = pMem[elemPosArray] & mask;
    }
}

bool TBitField::getBit(const size_t n) const // получить значение бита
{
    using namespace std;

    if (n > bitLen || n < 0)
    {
        FatalError a;
        throw a;
    }
    else
    {
        int elemPosArray = getIndex(n);
        int number_in_uint = n % (sizeof(uint) * 8);
        /*
        uint temp = (uint)pMem[elemPosArray];
        int t = 0;
        int ans = 0;
        string str = "";
        int w = sizeof(uint) * 8;
        for (int i = 0; i < w; i++)
        {
            str = to_string(temp % 2) + str;
            temp /= 2;
        }
        if (str[sizeof(uint) * 8 - number_in_uint - 1] == '1')
            return true;
        else
            return false;*/
        uint temp(bitLen);
        temp = getMask(number_in_uint);
        if (temp & pMem[elemPosArray])
            return true;
        else
            return false;
    }
}

// битовые операции
TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    delete[]pMem;
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new uint[memLen];
    for (int i = 0; i < memLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (bf.bitLen != this->bitLen)
        return false;
    else
    {
        for (int i = 0; i < this->memLen; i++)
        {
            if (bf.pMem[i] != pMem[i])
                return false;
        }
    }
    return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
    if (bf == *this)
    {
        return false;
    }
    return true;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{

    if (bf.bitLen == this->bitLen)
    {
        TBitField result(bitLen);
        for (int i = 0; i < bitLen; i++)
        {
            if (bf.getBit(i) == 1 || this->getBit(i) == 1)
                result.setBit(i);

        }
        return result;
    }

    else
    {
        if (bf.bitLen > bitLen)
        {
            TBitField result(bf.bitLen);

            for (int i = 0; i < bitLen; i++)
            {
                if (bf.getBit(i) == 1 || getBit(i) == 1)
result.setBit(i);
            }
            for (int i = bitLen; i < bf.bitLen; i++)
                if (bf.getBit(i) == 1)
                    result.setBit(i);
            return result;
        }
        else
        {
        TBitField result(bitLen);
        for (int i = 0; i < bitLen - bf.bitLen; i++)
        {
            if (getBit(i) == 1)
                result.setBit(i);
        }
        for (int i = bitLen - bf.bitLen; i < bitLen; i++)
        {
            if (bf.getBit(i - (bitLen - bf.bitLen)) == 1 || this->getBit(i) == 1)
                result.setBit(i);
        }
        return result;
        }
    }
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{

    if (bf.bitLen == this->bitLen)
    {
        TBitField result(bitLen);
        for (int i = 0; i < bitLen; i++)
        {
            if (bf.getBit(i) == 1 && this->getBit(i) == 1)
                result.setBit(i);
        }
        return result;
    }
    else
    {

        int max_of_two;
        int min;
        if (bf.bitLen > bitLen)
            max_of_two = bf.bitLen;
        else
            max_of_two = bitLen;
        if (bitLen == max_of_two)
            min = bf.bitLen;
        else
            min = bitLen;
        TBitField result(max_of_two);
        for (int i = 0; i < min; i++)
        {
            if (bf.getBit(i) == 1 && this->getBit(i) == 1)
                result.setBit(i);
        }
        return result;
    }

}

TBitField TBitField::operator~() // отрицание
{
    TBitField result(bitLen);
    for (int i = 0; i < memLen - 1; i++)
    {
        result.pMem[i] = ~(this->pMem[i]);
    }
    for (int i = capacity() * (memLen - 1); i < bitLen; i++)
    {
        if (getBit(i) == 0)
            result.setBit(i);
    }
    return result;
}

TBitField::~TBitField()
{
    delete[]pMem;
}

// ввод/вывод
std::istream& operator>>(std::istream& istr, TBitField& bf) // ввод
{
    using namespace std;
    int n;
    cin >> bf.bitLen;
    if (bf.bitLen == 0)
    {
        bf.memLen = 0;
    }
    if (bf.bitLen < 0)
    {
        FatalError a;
        throw a;
    }
    bf.memLen = bf.bitLen / (sizeof(uint) * 8) + 1;
    
    bf.pMem = new uint[bf.memLen];
    for (int i = 0; i < bf.memLen; i++)
        istr >> bf.pMem[i];
    return istr;
}

std::ostream& operator<<(std::ostream& ostr, const TBitField& bf) // вывод
{


    for (int i = 0; i < bf.memLen - 1; i++)
    {


        uint temp = (uint)bf.pMem[i];
        int t = 0;
        int ans = 0;
        std::string str = "";
        int w = sizeof(uint) * 8;
        for (int i = 0; i < w; i++)
        {
            str = std::to_string(temp % 2) + str;
            temp /= 2;
        }
        ostr << str;
    }
    
    return ostr;
}
