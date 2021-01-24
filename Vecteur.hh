#pragma once
#include <iostream>
#include "personnage.hh"
#include "humain.hh"
#include "humainNormal.hh"

template<typename T>
class Vecteur
{
protected:
  T** table; 
  std::size_t nbLine;
  std::size_t nbColumn;

public:
  Vecteur(std::size_t nbC, std::size_t nbL);
  Vecteur(const Vecteur&);
  T operator()(std::size_t C, std::size_t L)const;
  T& operator()(std::size_t C, std::size_t L);
  template<typename U>
  friend std::ostream& operator<<(std::ostream& , const Vecteur<U> &);
  //bool operator== (const Vecteur<T>& lhs) const;
  Vecteur<T>& operator=(const Vecteur<T>& m);
  virtual ~Vecteur();
};
template<typename T>
Vecteur<T>::Vecteur(std::size_t nbC, std::size_t nbL)
{
  nbLine = nbL;
  nbColumn = nbC;
  table = new T* [nbL];
  for (int i=0; i<nbL; i++)
  {
    table[i] = new T[nbC];
  } 
}

template<typename T>
Vecteur<T>::Vecteur(const Vecteur<T>& t)
{
  nbLine = t.nbLine;
  nbColumn = t.nbColumn;
  table = new T* [nbLine];
  for (int i=0; i<nbLine; i++)
  {
    table[i] = new T[nbColumn];
    for (int j = 0; j<nbColumn; j++)
    {
      table[i][j] = t.table[i][j];
    }
  } 
}
template<typename T>
Vecteur<T>::~Vecteur()
{
  for (int i = 0; i<nbLine; i++)
  {
    delete table[i];
  }
  delete table;
}
template<typename T>
T Vecteur<T>::operator()(std::size_t C, std::size_t L)const
{
  return table[L][C];
}
template<typename T>
T& Vecteur<T>::operator()(std::size_t C, std::size_t L)
{
  return table[L][C];
}
template<typename T>
std::ostream& operator<<(std::ostream& os , const Vecteur<T> & t)
{
  for (int i=0; i<t.nbLine; i++)
  {
    for (int j = 0; j<t.nbColumn; j++)
    {
      os << t.table[i][j] << " ";
    }
    os << std::endl;
  } 
  return os;
}
/*
template<typename T>
bool Vecteur<T>::operator==(const Vecteur<T>& rhs) const
{
  if (rhs.nbLine!=nbLine || rhs.nbColumn!=nbColumn)
    return false;
  for (int i=0; i<nbLine; i++)
  {
    for (int j = 0; j<nbColumn; j++)
    {
      if (table[i][j] != rhs.table[i][j])
        return false;
    }
  } 
  return true;
}*/
template<typename T>
Vecteur<T>& Vecteur<T>::operator=(const Vecteur<T>& m)
{
  if (m.nbLine!=nbLine || m.nbColumn!=nbColumn)   
  {
    for (int i=0; i<nbLine; i++)
    {
      delete table[i];
    }
    delete table; 

    nbLine = m.nbLine;
    nbColumn = m.nbColumn;
    table = new T* [nbLine];
    for (int i=0; i<nbLine; i++)
    {
      table[i] = new T[nbColumn];
    } 
  }

  for (int i=0; i<nbLine; i++)
  {
    for (int j = 0; j<nbColumn; j++)
    {
      table[i][j] = m.table[i][j];
    }
  } 
  return *this;
}








