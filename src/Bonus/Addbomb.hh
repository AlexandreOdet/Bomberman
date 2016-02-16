#ifndef	ADDBOMB_HH_
#define	ADDBOMB_HH_

#include "ABonus.hh"
#include "Cube.hh"

class Addbomb : public Abonus
{
public:
  Addbomb(glm::vec3 const &pos);
  ~Addbomb();
};

#endif /* ADDBOMB_HH_ */
