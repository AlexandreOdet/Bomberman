#ifndef	ADDLIFE_HH_
#define	ADDLIFE_HH_

#include "ABonus.hh"
#include "Cube.hh"

class Addlife : public Abonus
{
public:
  Addlife(glm::vec3 const &pos);
  ~Addlife();
};

#endif /* ADDLIFE_HH_ */
