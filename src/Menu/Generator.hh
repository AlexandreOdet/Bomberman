//
// Generator.hh for Generator in /home/odet_a/MapGenerator
// 
// Made by Alexandre Odet
// Login   <odet_a@epitech.net>
// 
// Started on  Mon Jun  1 12:49:08 2015 Alexandre Odet
// Last update Mon Jun  1 12:53:09 2015 Alexandre Odet
//

#ifndef _GENERATOR_H_
# define _GENERATOR_H_

# include <random>

class GenereNumber
{
public:
	GenereNumber();
	~GenereNumber();
	int operator()(unsigned int const min, unsigned int const max);
private:
	std::default_random_engine *_generator;
	std::random_device _rd;
};

#endif /* !_GENERATOR_H_ */
