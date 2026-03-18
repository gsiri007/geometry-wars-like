#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>


Game::Game(const std::string & config)
{
  init(config);
}

void Game::init(const std::string & config)
{
  std::ifstream configFile(config);

  if (!configFile.is_open())
  {
    std::cerr << "ERROR: config file missing." << '\n';
    exit(1);
  }

  std::string entry;
  while (configFile >> entry)
  {
    if (entry == "Window")
    {
      unsigned int width, height, frameRate, style;

      configFile >> width >> height >> frameRate >> style;

      m_window.create(sf::VideoMode({width, height}), "Geometry-Wars");
      m_window.setFramerateLimit(frameRate);
    }

    if (entry == "Font")
    {
      std::string  path {};
      int          size {};

      configFile >> path;
      configFile >> size;

      m_font = sf::Font(path);
    }

    if (entry == "Player")
    {
      configFile
       >> m_playerConfig.SR
       >> m_playerConfig.CR
       >> m_playerConfig.S
       >> m_playerConfig.FR
       >> m_playerConfig.FG
       >> m_playerConfig.FB
       >> m_playerConfig.OR
       >> m_playerConfig.OG
       >> m_playerConfig.OB
       >> m_playerConfig.OT
       >> m_playerConfig.V;
    }

    if (entry == "Enemy")
    {
      configFile
       >> m_enemyConfig.SR
       >> m_enemyConfig.CR
       >> m_enemyConfig.SMIN
       >> m_enemyConfig.SMAX
       >> m_enemyConfig.OR
       >> m_enemyConfig.OG
       >> m_enemyConfig.OB
       >> m_enemyConfig.OT
       >> m_enemyConfig.VMIN
       >> m_enemyConfig.VMAX
       >> m_enemyConfig.L
       >> m_enemyConfig.SI;
    }
  }

  configFile.close();

}
void Game::setPaused(bool state)
{
  m_paused = state;
}

void Game::run()
{
  spawnPlayer();

  while (m_running) {
    m_entities.update();

    sEnemySpawner();
    sMovement();
    sCollision();
    sUserInput();
    sRender();

    entityLogger(Tag::Enemy);

    m_currentFrame++;
  }
}

void Game::spawnPlayer()
{
  m_player = m_entities.addEntity(Tag::Player);

  m_player->cShape = std::make_shared<CShape>(CShape(
          m_playerConfig.SR
        , m_playerConfig.V
        , sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB)
        , sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB)
        , m_playerConfig.OT));

  auto windowSize = m_window.getSize();

  m_player->cTransform = std::make_shared<CTransform>(CTransform(
          Vec2(windowSize.x / 2.0f, windowSize.y / 2.0f)
        , Vec2(m_playerConfig.S, m_playerConfig.S)
        , 8));

  m_player->cInput = std::make_shared<CInput>();
}

void Game::spawnEnemy()
{
  auto enemy { m_entities.addEntity(Tag::Enemy) };

  auto vertices  { getRandomNumber(m_enemyConfig.VMIN, m_enemyConfig.VMAX) };

  std::map<size_t, sf::Color> colorMap {
      { 0, sf::Color(255, 0, 0, 255) }
    , { 1, sf::Color(0, 255, 0, 255) }
    , { 2, sf::Color(0, 0, 255, 255) }
  };

  auto  colorKey  { getRandomNumber(0, 2) };
  auto  color     { colorMap[colorKey] };

  auto posX  { getRandomNumber( m_enemyConfig.SR
                              , m_window.getSize().x - m_enemyConfig.SR ) };
  auto posY  { getRandomNumber( m_enemyConfig.SR
                              , m_window.getSize().y - m_enemyConfig.SR ) };

  auto speedX  { getRandomNumber(m_enemyConfig.SMIN, m_enemyConfig.SMAX) };
  auto speedY  { getRandomNumber(m_enemyConfig.SMIN, m_enemyConfig.SMAX) };

  enemy->cShape = std::make_shared<CShape>(CShape(
          m_enemyConfig.SR
        , vertices
        , color
        , sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB)
        , m_enemyConfig.OT));

  enemy->cTransform = std::make_shared<CTransform>(CTransform(
          Vec2(posX, posY)
        , Vec2(speedX, speedY)
        , 8));
}

void Game::spawnBullet()
{
  m_entities.addEntity(Tag::Bullet);
}

void Game::spawnSpecialWeapon()
{
  m_entities.addEntity(Tag::Special);
}

int Game::getRandomNumber(const int min, const int max)
{
  std::srand(std::time(nullptr));
  int randomNumber { ( std::rand() % (max - min + 1) ) + min };
  return randomNumber;
}

void Game::entityLogger(Tag tag)
{
  auto totalEntities = m_entities.getTotalEntities(tag);
  std::cout << 0 << ": " << totalEntities << std::endl;
}

void Game::sMovement()
{
  auto windowSize = m_window.getSize();

  for (auto & e : m_entities.getEntities())
  {

    // user controlled entity (player)
    if (e->cInput)
    {

      auto radius = e->cShape->circle.getRadius();

      if (e->cInput->up)
      {
        e->cTransform->position.y -= e->cTransform->velocity.y;

        if (e->cTransform->position.y - radius <= 0)
        {
          e->cTransform->position.y += e->cShape->circle.getRadius();
        }
      }

      if (e->cInput->down)
      {
        e->cTransform->position.y += e->cTransform->velocity.y;

        if (e->cTransform->position.y + radius  >= windowSize.y)
        {
          e->cTransform->position.y -= e->cShape->circle.getRadius();
        }
      }

      if (e->cInput->left)
      {
        e->cTransform->position.x -= e->cTransform->velocity.x;

        if (e->cTransform->position.x - radius <= 0)
        {
          e->cTransform->position.x += e->cShape->circle.getRadius();
        }
      }

      if (e->cInput->right) {
        e->cTransform->position.x += e->cTransform->velocity.x;

        if (e->cTransform->position.x + radius >= windowSize.x)
        {
          e->cTransform->position.x -= e->cShape->circle.getRadius();
        }
      }
    }

    if (!(e->cInput))
    {
      e->cTransform->position.x += e->cTransform->velocity.x;
      e->cTransform->position.y += e->cTransform->velocity.y;

      if (e->cTransform->position.x >= windowSize.x ||
          e->cTransform->position.x <= 0)
      {
        e->cTransform->velocity.x *= -1;
      }

      if (e->cTransform->position.y >= windowSize.y ||
          e->cTransform->position.y <= 0)
      {
        e->cTransform->velocity.y *= -1;
      }
    }
  }
};

void Game::sUserInput()
{
  while (const auto & event = m_window.pollEvent())
  {
    if (event->is<sf::Event::Closed>())
    {
      m_running = false;
    }

    if (const auto & keyPressed = event->getIf<sf::Event::KeyPressed>())
    {

      switch (keyPressed->scancode)
      {
        case sf::Keyboard::Scancode::W :
          m_player->cInput->up = true;
          break;
        case sf::Keyboard::Scancode::A :
          m_player->cInput->left = true;
          break;
        case sf::Keyboard::Scancode::S :
          m_player->cInput->down = true;
          break;
        case sf::Keyboard::Scancode::D :
          m_player->cInput->right = true;
          break;
        default:
          break;
      }
    }

    if (const auto & keyReleased = event->getIf<sf::Event::KeyReleased>())
    {
      switch (keyReleased->scancode)
      {
        case sf::Keyboard::Scancode::W :
          m_player->cInput->up = false;
          break;
        case sf::Keyboard::Scancode::A :
          m_player->cInput->left = false;
          break;
        case sf::Keyboard::Scancode::S :
          m_player->cInput->down = false;
          break;
        case sf::Keyboard::Scancode::D :
          m_player->cInput->right = false;
          break;
        default:
          break;
      }
    }
  }

};

void Game::sLifespan() {};

void Game::sRender()
{
  m_window.clear({0, 0, 0, 255});

  for (auto & e : m_entities.getEntities())
  {
    e->cShape->circle.setPosition({
          e->cTransform->position.x
        , e->cTransform->position.y
    });

    e->cShape->circle.setRotation(sf::degrees(
          e->cTransform->angle));

    m_window.draw(e->cShape->circle);
  }

  m_window.display();

};

void Game::sEnemySpawner()
{
  if (m_currentFrame - m_lastEnemySpwanFrame > 60)
  {
    spawnEnemy();
    m_lastEnemySpwanFrame = m_currentFrame;
  }
};

void Game::sCollision() {};
