#ifndef GAME_H
#define GAME_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "raylib.h"
#include "Entity.h"
#include "Vec2.h"
#include "Vec2ToRaylib.h"
#include "EntityManager.h"
#include "Components.h"

struct PlayerConfig { int SR, CR, V, OT, FR, FG, FB, OR, OG, OB; float S; };
struct EnemyConfig  { int SR, CR, VMIN, VMAX, L, SI, OR, OG, OB, OT; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, OT, V, L, FR, FG, FB, OR, OG, OB; float S; };
struct WindowConfig { int W, H, FL, FS; };
struct FontConfig   { int S, R, G, B; std::string F; };

class Game 
{
private:
    PlayerConfig    m_playerc;
    EntityManager   m_entitiesManager;
    EnemyConfig     m_enemyc;
    BulletConfig    m_bulletc;
    WindowConfig    m_windowc;
    FontConfig      m_fontc;
    int             m_score = 0;
    int             m_currentFrame = 0;
    int             m_lastEnemySpawnTime = 0;
    bool            m_paused = false;
    bool            m_running = true;

    std::shared_ptr<Entity> m_player;

    void init(const std::string& path); // initialize game state
    void setPaused(bool paused);        // pause game

    void sMovement();                   // System: Entity position / movement update
    void sUserInput();                  // System: User input
    void sLifespan();                   // System: Entity lifespan
    void sRender();                     // System: Render and drawing
    void sEnemySpawner();               // System: Spawn enemies
    void sCollision();                  // System: Collisions

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2f& mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    Game(const std::string& config);
    void run();
};

#endif