#include "Game.h"

Game::Game(const std::string& config)
{
    init(config);
}

void Game::init(const std::string& path) 
{
    std::ifstream   file(path);
    std::string     line;

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file." << std::endl;
        return;
    }

    std::cout << "Opening configutation file: " << path << std::endl;
    while(std::getline(file, line))
    {
        std::string         label;
        std::stringstream   s(line);

        s >> label;

        if (label == "Window") 
        {
            std::cout << "\tExtracting window configuration" << std::endl;
            s >> m_windowc.W >> m_windowc.H >> m_windowc.FL >> m_windowc.FS;
        } 
        else if (label == "Font") 
        {
            s >> m_fontc.F >> m_fontc.S >> m_fontc.R >> m_fontc.G >> m_fontc.B;
            std::cout << "\tExtracting font configuration" << std::endl;
        }
        else if (label == "Player") 
        {
            s >> m_playerc.SR >> m_playerc.CR >> m_playerc.S >> m_playerc.FR >> m_playerc.FG >> m_playerc.FB >> m_playerc.OR >> m_playerc.OG >> m_playerc.OB >> m_playerc.OT >> m_playerc.V;
            std::cout << "\tExtracting player configuration" << std::endl;
        }
        else if (label == "Enemy") 
        {
            s >> m_enemyc.SR >> m_enemyc.CR >> m_enemyc.SMIN >> m_enemyc.SMAX >> m_enemyc.OR >> m_enemyc.OG >> m_enemyc.OB >> m_enemyc.OT >> m_enemyc.VMIN >> m_enemyc.VMAX >> m_enemyc.L >> m_enemyc.SI;
            std::cout << "\tExtracting enemy configuration" << std::endl;
        }
        else if (label == "Bullet") 
        {
            s >> m_bulletc.SR >> m_bulletc.CR >> m_bulletc.S >> m_bulletc.FR >> m_bulletc.FG >> m_bulletc.FB >> m_bulletc.OR >> m_bulletc.OG >> m_bulletc.OB >> m_bulletc.OT >> m_bulletc.V >> m_bulletc.L;
            std::cout << "\tExtracting bullet configuration" << std::endl;
        }
        else {
            std::cerr << "Error: Unknown label." << std::endl;
        }
    }
    file.close();

    InitWindow(m_windowc.W, m_windowc.H, "Geometry Wars - Michael Nguyen");

    SetTargetFPS(m_windowc.FL);

    // Font font = LoadFont(m_font.F.c_str()); // TODO: Import font
}

void Game::run()
{
    while (!WindowShouldClose()) // TODO: Window closing should be a condition instead of built into game loop
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}