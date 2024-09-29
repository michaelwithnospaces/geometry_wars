#include "Game.h"

Game::Game(const std::string& config)
{
    init(config);
}

void Game::run()
{
    while (!WindowShouldClose()) // TODO: Window closing should be a condition instead of built into game loop
    {
        m_entitiesManager.update();

        sMovement();
        sCollision();
        sRender();
        sUserInput();
    }

    CloseWindow();
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

    spawnPlayer();
    // Font font = LoadFont(m_font.F.c_str()); // TODO: Import font
}

void Game::sMovement()
{
    for (auto e : m_entitiesManager.getEntities())
    {
        if (e->cShape && e->cTransform && e->cInput)
        {
            // TODO: Moves faster in diagonal, need to fix
            e->cTransform->velocity *= 0;

            float speed = 0.2;
            if (e->cInput->up == true)
            {
                e->cTransform->velocity.y -= 60 * speed;
            }
            if (e->cInput->down == true)
            {
                e->cTransform->velocity.y += 60 * speed;
            }
            if (e->cInput->left == true)
            {
                e->cTransform->velocity.x -= 60 * speed;
            }
            if (e->cInput->right == true)
            {
                e->cTransform->velocity.x += 60 * speed;
            }

            e->cTransform->pos += e->cTransform->velocity;
        }
    }
}

void Game::sUserInput()
{
    if (IsKeyDown(KEY_W))
    {
        // std::cout << "W Key Pressed" << std::endl;
        m_player->cInput->up = true;
    }
    if (IsKeyDown(KEY_A))
    {
        // std::cout << "A Key Pressed" << std::endl;
        m_player->cInput->left = true;
    }
    if (IsKeyDown(KEY_S))
    {
        // std::cout << "S Key Pressed" << std::endl;
        m_player->cInput->down = true;
    }
    if (IsKeyDown(KEY_D))
    {
        // std::cout << "D Key Pressed" << std::endl;
        m_player->cInput->right = true;
    }
    if (IsKeyUp(KEY_W))
    {
        // std::cout << "W Key Released" << std::endl;
        m_player->cInput->up = false;
    }
    if (IsKeyUp(KEY_A))
    {
        // std::cout << "A Key Released" << std::endl;
        m_player->cInput->left = false;
    }
    if (IsKeyUp(KEY_S))
    {
        // std::cout << "S Key Released" << std::endl;
        m_player->cInput->down = false;
    }
    if (IsKeyUp(KEY_D))
    {
        // std::cout << "D Key Released" << std::endl;
        m_player->cInput->right = false;
    }
}

void Game::sRender() {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        for (auto e : m_entitiesManager.getEntities())
        {
            if (e->cShape)
            {
                DrawPoly(toRaylibVector2(e->cTransform->pos), e->cShape->sides, e->cShape->r, 0.0f, e->cShape->color);
            }
        }

        EndDrawing();
}

void Game::sCollision()
{
    for (auto e : m_entitiesManager.getEntities())
    {
        if (e->cShape && e->cTransform)
        {
            if ((e->cTransform->pos.x - e->cShape->r) < 0)
            {
                e->cTransform->pos.x = e->cShape->r;
            }
            if ((e->cTransform->pos.x + e->cShape->r) > m_windowc.W)
            {
                e->cTransform->pos.x = m_windowc.W - e->cShape->r;
            }
            if ((e->cTransform->pos.y - e->cShape->r) < 0 )
            {
                e->cTransform->pos.y = e->cShape->r;
            }
            if ((e->cTransform->pos.y + e->cShape->r) > m_windowc.H)
            {
                e->cTransform->pos.y = m_windowc.H - e->cShape->r;
            }
        }
    }
}

void Game::spawnPlayer()
{
    auto entity = m_entitiesManager.addEntity("player");

    entity->cTransform =    std::make_shared<CTransform>(Vec2f(100.0f, 100.0f), Vec2f(0.0f, 0.0f), 0.0f);
    entity->cShape =        std::make_shared<CShape>(Vec2f(100.0f, 100.0f), 8, 50.0f, Color({255, 91, 97, 255}));
    entity->cInput =        std::make_shared<CInput>();

    m_player = entity;
}