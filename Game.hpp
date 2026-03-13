#include <SFML/Graphics.hpp>
#include <cstddef>
#include <memory>
#include <string>
#include "EntityManager.hpp"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;};
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX;};
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
  sf::RenderWindow  m_window;
  sf::Font          m_font;
  // sf::Text          m_text;
  EntityManager     m_entities;
  size_t            m_score;
  size_t            m_currentFrame         { 0 };
  size_t            m_lastEnemySpwanFrame  { 0 };
  bool              m_paused               { false };
  bool              m_running              { true };

  PlayerConfig      m_playerConfig;
  EnemyConfig       m_enemyConfig;
  BulletConfig      m_bulletConfig;

  std::shared_ptr<Entity> m_player;

  void init(const std::string & config);
  void setPaused(bool state);

  void sMovement();
  void sUserInput();
  void sLifespan();
  void sRender();
  void sEnemySpawner();
  void sCollision();

  void spawnPlayer();
  void spawnEnemy();
  void spawnBullet();
  void spawnSpecialWeapon();

public:
  Game(const std::string & config);
  void run();
};
