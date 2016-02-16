#ifndef	ADDSPEED_HH_
#define	ADDSPEED_HH_

#include "ABonus.hh"
#include "Cube.hh"

class Addspeed : public Abonus
{
public:
  Addspeed(glm::vec3 const &);
  ~Addspeed();
};

#endif /* ADDSPEED_HH_ */
