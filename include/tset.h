// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.h - Copyright (c) Гергель В.П. 07.05.2001
// Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Переработано в соответсвии с C++11 (частично) Пановым А.А. 2021
// Множество

#pragma once
#include "tbitfield.h"
class TSet
{
private:
  size_t maxPower;    // максимальная мощность множества
  TBitField bitField; // битовое поле для хранения характеристического вектора
public:
  TSet(size_t mp);
  TSet(const TSet &s);       // конструктор копирования
  TSet(const TBitField &bf); // конструктор преобразования типа
  operator TBitField();      // преобразование типа к битовому полю

  // доступ к битам
  size_t getMaxPower() const;           // максимальная мощность множества
  void insElem(const uint elem);        // включить элемент в множество
  void delElem(const uint elem);        // удалить элемент из множества
  bool isMember(const uint elem) const; // проверить наличие элемента в множестве

  // теоретико-множественные операции
  bool operator==(const TSet &s) const; // сравнение
  bool operator!=(const TSet &s) const; // сравнение
  TSet& operator=(const TSet &s);  // присваивание
  TSet operator+(const uint elem); // объединение с элементом
                                   // элемент должен быть из того же универса
  TSet operator-(const uint elem); // разность с элементом
                                   // элемент должен быть из того же универса
  TSet operator+(const TSet &s);   // объединение
  TSet operator*(const TSet &s);   // пересечение
  TSet operator~();                // дополнение

  friend std::istream &operator>>(std::istream &istr, TSet &bf);
  friend std::ostream &operator<<(std::ostream &ostr, const TSet &bf);
};
