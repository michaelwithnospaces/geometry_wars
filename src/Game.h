#ifndef GAME_H
#define GAME_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include "raylib.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };
struct WindowConfig { int W, H, FL, FS; };
struct FontConfig   { int S, R, G, B; std::string F; };

class Game {
private:
    void init(const std::string& path);
    PlayerConfig    m_player;
    EnemyConfig     m_enemy;
    BulletConfig    m_bullet;
    WindowConfig    m_window;
    FontConfig      m_font;
    int             m_score = 0;
    int             m_currentFrame = 0;
    int             m_lastEnemySpawnTime = 0;
    bool            m_paused = false;
    bool            m_running = true;

public:
    Game(const std::string& config);
    void run();
};

#endif