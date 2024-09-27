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
            s >> m_window.W >> m_window.H >> m_window.FL >> m_window.FS;
        } 
        else if (label == "Font") 
        {
            s >> m_font.F >> m_font.S >> m_font.R >> m_font.G >> m_font.B;
            std::cout << "\tExtracting font configuration" << std::endl;
        }
        else if (label == "Player") 
        {
            s >> m_player.SR >> m_player.CR >> m_player.S >> m_player.FR >> m_player.FG >> m_player.FB >> m_player.OR >> m_player.OG >> m_player.OB >> m_player.OT >> m_player.V;
            std::cout << "\tExtracting player configuration" << std::endl;
        }
        else if (label == "Enemy") 
        {
            s >> m_enemy.SR >> m_enemy.CR >> m_enemy.SMIN >> m_enemy.SMAX >> m_enemy.OR >> m_enemy.OG >> m_enemy.OB >> m_enemy.OT >> m_enemy.VMIN >> m_enemy.VMAX >> m_enemy.L >> m_enemy.SI;
            std::cout << "\tExtracting enemy configuration" << std::endl;
        }
        else if (label == "Bullet") 
        {
            s >> m_bullet.SR >> m_bullet.CR >> m_bullet.S >> m_bullet.FR >> m_bullet.FG >> m_bullet.FB >> m_bullet.OR >> m_bullet.OG >> m_bullet.OB >> m_bullet.OT >> m_bullet.V >> m_bullet.L;
            std::cout << "\tExtracting bullet configuration" << std::endl;
        }
        else {
            std::cerr << "Error: Unknown label." << std::endl;
        }
    }
    file.close();

    InitWindow(m_window.W, m_window.H, "Geometry Wars - Michael Nguyen");

    SetTargetFPS(m_window.FL);

    Font font = LoadFont(m_font.F.c_str());
}

void Game::run()
{
    while (!WindowShouldClose) // TODO: Window closing should be a condition instead of built into game loop
    {
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
}