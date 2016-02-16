#ifndef __PLAYER_HH__
#define __PLAYER_HH__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Game.hh>
#include <Clock.hh>
#include <Model.hh>
#include <SdlContext.hh>
#include <string>
#include <map>
#include <vector>

#include "HUD.hh"
#include "Ressource.hh"
#include "ABonus.hh"
#include "ABox.hh"
#include "Exception.hpp"

class	Bomb;

class Player
{
  class Coordinates
  {
  public:
    float	x, y, parentX, parentY;
    int		heuristic;

    Coordinates(float param_x, float param_y, float father_x, float father_y, float targetX, float targetY) : x(param_x), y(param_y), parentX(father_x), parentY(father_y)
    {
      heuristic = 10*(abs(x - targetX) + abs(y - targetY));
    }
  };

public:
  Player(glm::vec3 const &, std::string const &);
  Player(glm::vec3 const &, std::string const &, int, int, int, int);
  ~Player();


private:
  void			moveLeft(gdl::Clock const &);
  void			moveRight(gdl::Clock const &);
  void			moveUp(gdl::Clock const &);
  void			moveDown(gdl::Clock const &);
  void			wait();
  void			isRunning();
  int			putBomb(std::vector<Bomb*>*);
  void			translate(glm::vec3 const &);
  void			rotate(glm::vec3 const &, float);
  float			my_round(float) const;

  int			IA(std::vector<ABox*> const &,
			   std::vector<Bomb*> *, std::vector<Player *> *);

  void			create_map(std::vector<ABox*> const &);
  void			update_map(std::vector<ABox*> const &, std::vector<Bomb*> *,
				   std::vector<Player*> *);
  int			calc_target(std::vector<Player *> *);
  int			recalc_path();
  int			Astar_aggressif();
  void			open_add(float, float, float, float, float, float);
  bool			addable(float, float);
  void			open_to_close(float, float, float, float);
  bool			is_close(float, float);
  bool			is_open(float, float);
  int			toTarget(float, float, float, float);
  void			close_del_first();
  bool			last_heuristic();

public:
  void			lessBomb();
  std::string		getName() const;
  int			getLife() const;
  int			getPower() const;
  int			getMaxBomb() const;
  int			getSpeed() const;
  int			**getMap() const;
  glm::mat4		getTransformation() const;
  glm::vec3		getIntPosition() const;
  glm::vec3 const	&getPosition() const;

  void			BonusUpdate(int const, ABox *box);
  void			upLife();
  void			lessLife();
  void			upMs();
  void			upPower();
  void			upNumber();
  void			addScore(int const &);

  void			update(gdl::Clock const &, gdl::Input &,
			       std::vector<ABox*> const &,std::vector<Bomb*> *,
			       std::vector<Player*> *);

  void			draw(gdl::AShader &, glm::mat4 const &, double);
  void			drawHUD(gdl::AShader &, gdl::Clock const &);

private:
  gdl::Model				*_model;
  glm::vec3				_position;
  glm::vec3				_rotation;
  glm::vec3				_scale;
  std::string				_name;
  std::map<int, void (Player::*)()>	_bonusMap;
  std::vector<ABox*>			_listObj;
  std::vector<Bomb*>			*_listBomb;

  HUD					*_hud;
  bool					_running;
  float					_speed;
  int					_score;
  int					_maxbomb;
  int					_currentbomb;
  int					_life;
  int					_power;
  float					goToX;
  float					goToY;
  int					**IA_map;
  bool					hasChanged;
  std::list<Player::Coordinates *>	open_list;
  std::list<Player::Coordinates *>	close_list;
};

#endif
