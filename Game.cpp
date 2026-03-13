#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <string>


Game::Game(const std::string & config)
{
  init(config);
}

void Game::init(const std::string & config)
{
  std::ifstream configFile("config.txt");

  if (!configFile.is_open())
  {
    std::cout << "ERROR: config file missing." << '\n';
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
      // Player SR CR S FR FG FB OR OG OB OT V
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

  auto size = m_window.getSize();
  m_player->cTransform = std::make_shared<CTransform>(CTransform(
          Vec2(size.x / 2.0f, size.y / 2.0f)
        , Vec2(0, 0)
        , 0));

  m_player->cInput = std::make_shared<CInput>();
}

void Game::spawnEnemy()
{
  m_entities.addEntity(Tag::Enemy);
}

void Game::spawnBullet()
{
  m_entities.addEntity(Tag::Bullet);
}

void Game::spawnSpecialWeapon()
{
  m_entities.addEntity(Tag::Special);
}


void Game::sMovement() {};

void Game::sUserInput()
{
  while (const auto & event = m_window.pollEvent())
  {
    if (event->is<sf::Event::Closed>())
    {
      m_running = false;
    }
  }
};

void Game::sLifespan() {};

void Game::sRender()
{
  m_window.clear({0, 0, 0, 255});

  for (auto & e : m_entities.getEntities()) {
    e->cShape->circle.setPosition({
          e->cTransform->position.x
        , e->cTransform->position.y
    });

    m_window.draw(e->cShape->circle);
  }

  m_window.display();

};
void Game::sEnemySpawner() {};
void Game::sCollision() {};

