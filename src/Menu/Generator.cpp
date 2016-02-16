//
// Generator.cpp for GENERATOR in /home/odet_a/MapGenerator
// 
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
// 
// Started on  Mon Jun  1 12:58:19 2015 Alexandre Odet
// Last update Mon Jun  1 12:58:20 2015 Alexandre Odet
//

#include "Generator.hh"

GenereNumber::GenereNumber()
{
  this->_generator = new std::default_random_engine(this->_rd());
}

GenereNumber::~GenereNumber()
{
  delete (this->_generator);
}

int GenereNumber::operator()(unsigned int const min, unsigned int const max)
{
  std::uniform_int_distribution<unsigned int> distrib(min, max);
  return (distrib(*this->_generator));
}
