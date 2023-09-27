// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Битовое поле

#pragma once
#include <iosfwd>

typedef size_t uint;

class TBitField
{
private:
    size_t bitLen;   // длина битового поля - макс. к-во битов
    uint* pMem;     // память для представления битового поля
    size_t memLen;   // к-во эл-тов uint для представления бит.поля //длина массива pMem

    // методы реализации
    size_t getIndex(const size_t n) const; // индекс в pМем для бита n
    uint getMask(const size_t n) const;    // битовая маска для бита n
public:
    TBitField(size_t len);
    TBitField(const TBitField& bf);
    ~TBitField();

    // доступ к битам
    size_t getLength() const;          // получить длину (к-во битов)
    size_t getNumBytes() const;        // получить количество байт выделенной памяти
    void setBit(const size_t n);       // установить бит
    void clrBit(const size_t n);       // очистить бит
    bool getBit(const size_t n) const; // получить значение бита

    // битовые операции
    bool operator==(const TBitField& bf) const; // сравнение
    bool operator!=(const TBitField& bf) const; // сравнение
    TBitField& operator=(const TBitField& bf);  // присваивание
    TBitField  operator|(const TBitField& bf);  // операция "или"
    TBitField  operator&(const TBitField& bf);  // операция "и"
    TBitField  operator~();                     // отрицание

    friend std::istream& operator>>(std::istream& istr, TBitField& bf);
    friend std::ostream& operator<<(std::ostream& ostr, const TBitField& bf);
};
//   Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до bitLen
//   массив pМем рассматривается как последовательность uint элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
