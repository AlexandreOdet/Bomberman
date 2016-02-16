#ifndef	Exception_HPP_
#define	Exception_HPP_

#include <exception>
#include <iostream>
#include <cstdlib>

class	MenuError : public std::exception
{
private:
  std::string	msg;

public:
  MenuError(std::string const & str = "") throw() : msg(str) {}

  virtual const char *what() const throw()
  {
    return msg.c_str();
  }
  virtual ~MenuError() throw () {}
};

class	ParseError : public std::exception
{
private:
  std::string	msg;
  int		line;

public:
  ParseError(std::string const & str = "", int l = 0) throw() : msg(str), line(l) {}

  virtual const char *what() const throw()
  {
    return msg.c_str();
  }

  int	where() const throw()
  {
    return line;
  }
  virtual ~ParseError() throw () {}
};

class   GameError : public std::exception
{
private:
  std::string	msg;

public:
  GameError(std::string const &str = "") throw() : msg(str) {}

  virtual const char *what() const throw()
  {
    return msg.c_str();
  }
  virtual ~GameError() throw () {}
};

class   ResError : public std::exception
{
private:
  std::string	name;

public:
  ResError(std::string const &str = "") throw() : name(str) {}

  virtual const char *what() const throw()
  {
    return name.c_str();
  }
  virtual ~ResError() throw () {}
};

class	LoaderError : public std::exception
{
private:
  std::string msg;
public:
  LoaderError(std::string const & str = "") throw() : msg(str) {}

  virtual const char *what() const throw()
  {
    return msg.c_str();
  }
  virtual ~LoaderError() throw () {}
};

#endif /* Exception_HPP_ */
