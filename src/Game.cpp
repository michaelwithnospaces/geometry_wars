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

        sRender();
        sUserInput();
        
        if (!m_paused)
        {
            sMovement();
            sCollision();
            sEnemySpawner();
            sLifespan();
        }
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

    srand(static_cast<unsigned int>(time(0)));

    spawnPlayer();
    // Font font = LoadFont(m_font.F.c_str()); // TODO: Import font
}

void Game::setPaused(bool paused)
{
    if (paused)
    {
        m_paused = true;
    }
    else
    {
        m_paused = false;
    }
}

void Game::sMovement()
{
    // Player movement
    m_player->cTransform->velocity *= 0;
    float speed = m_playerc.S;
    if (m_player->cInput->up == true)
    {
        m_player->cTransform->velocity.y -= speed;
    }
    if (m_player->cInput->down == true)
    {
        m_player->cTransform->velocity.y += speed;
    }
    if (m_player->cInput->left == true)
    {
        m_player->cTransform->velocity.x -= speed;
    }
    if (m_player->cInput->right == true)
    {
        m_player->cTransform->velocity.x += speed;
    }
    m_player->cTransform->velocity.norm();
    m_player->cTransform->velocity *= speed;
    m_player->cTransform->pos += m_player->cTransform->velocity;

    for (auto e : m_entitiesManager.getEntities())
    {
        if (e->cTransform && e->tag() != "player")
        {
            e->cTransform->pos += e->cTransform->velocity;  
        }
    }
}

void Game::sUserInput()
{
    if (IsKeyPressed(KEY_P))
    {
        setPaused(!m_paused);
    }
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
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        m_player->cInput->shoot = true;
        spawnBullet(m_player, {GetMousePosition().x, GetMousePosition().y});
        // std::cout << "Mouse clicked: {" << GetMousePosition().x << ", " << GetMousePosition().y << "}" << std::endl;
    }
    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
    {
        m_player->cInput->shoot = false;
    }
}

void Game::sLifespan()
{
    for (auto e : m_entitiesManager.getEntities())
    {
        if (e->cLifespan)
        {
            if (e->cLifespan->framesAlive < 0)
            {
                e->destroy();
            }
            else
            {
                e->cLifespan->framesAlive--;
            }
        }
    }
}

void Game::sRender() {
        m_currentFrame++;

        BeginDrawing();
        ClearBackground(DARKGRAY);

        for (auto e : m_entitiesManager.getEntities())
        {
            if (e->cLifespan)
            {
                e->cShape->color.a = static_cast<unsigned char>(std::max(0.0f, (e->cLifespan->framesAlive / static_cast<float>(e->cLifespan->lifeFrames)) * 255));
            }

            if (e->cShape && e->cTransform && e->tag() != "player" && e->tag() != "bullet")
            {
                e->cTransform->angle += 5.0f;
                if (e->cTransform->angle > 360.0f)
                {
                    e->cTransform->angle -= 360.0f;
                }

                DrawPoly(toRaylibVector2(e->cTransform->pos), e->cShape->sides, e->cShape->r, e->cTransform->angle, e->cShape->color);
            }
        }

        for (auto e : m_entitiesManager.getEntities("bullet"))
        {
            if (e->cShape && e->cTransform)
            {
                DrawPoly(toRaylibVector2(e->cTransform->pos), e->cShape->sides, e->cShape->r, e->cTransform->angle, e->cShape->color);
            }
        }

        for (auto e : m_entitiesManager.getEntities("player"))
        {
            e->cTransform->angle += 5.0f;
            if (e->cTransform->angle > 360.0f)
            {
                e->cTransform->angle -= 360.0f;
            }

            DrawPoly(toRaylibVector2(e->cTransform->pos), e->cShape->sides, e->cShape->r, e->cTransform->angle, e->cShape->color);
        }

        if (m_paused)
        {
            DrawRectangle(0, 0, m_windowc.W, m_windowc.H, {255, 255, 255, 50});
                const char* pausedText = "PAUSED";
                int fontSize = 50;

                int textWidth = MeasureText(pausedText, fontSize);
                int textX = (m_windowc.W - textWidth) / 2;
                int textY = (m_windowc.H - fontSize) / 2;

                DrawText(pausedText, textX, textY, fontSize, {255, 255, 255, 200});
        }

        EndDrawing();
}

void Game::sEnemySpawner()
{
    if ((m_currentFrame - m_lastEnemySpawnTime) > m_enemyc.SI)
    {
        spawnEnemy();
        m_lastEnemySpawnTime = m_currentFrame;
    }
}

void Game::sCollision()
{
    // Player collision with boundary
    for (auto p : m_entitiesManager.getEntities("player"))
    {
        // player collision with wall
        if (p->cShape && p->cTransform && p->cCollision)
        {
            if ((p->cTransform->pos.x - p->cCollision->collissionR) < 0)
            {
                p->cTransform->pos.x = p->cCollision->collissionR;
            }
            if ((p->cTransform->pos.x + p->cCollision->collissionR) > m_windowc.W)
            {
                p->cTransform->pos.x = m_windowc.W - p->cCollision->collissionR;
            }
            if ((p->cTransform->pos.y - p->cCollision->collissionR) < 0 )
            {
                p->cTransform->pos.y = p->cCollision->collissionR;
            }
            if ((p->cTransform->pos.y + p->cCollision->collissionR) > m_windowc.H)
            {
                p->cTransform->pos.y = m_windowc.H - p->cCollision->collissionR;
            }
        }

        // enemy collission with wall
        for (auto e : m_entitiesManager.getEntities("enemy"))
        {
            if (e->cShape && e->cTransform && e->cCollision)
            {
                float sumR = p->cShape->r + e->cShape->r;
                float distanceBetween = p->cTransform->pos.dist(e->cTransform->pos);

                if (distanceBetween < sumR)
                {
                    e->destroy();
                    Vec2f center = {m_windowc.W / 2.0f, m_windowc.H / 2.0f};
                    p->cTransform->pos = center;
                }

                if ((e->cTransform->pos.x - e->cCollision->collissionR) < 0)
                {
                    e->cTransform->velocity.x = -e->cTransform->velocity.x;
                }
                if ((e->cTransform->pos.x + e->cCollision->collissionR) > m_windowc.W)
                {
                    e->cTransform->velocity.x = -e->cTransform->velocity.x;
                }
                if ((e->cTransform->pos.y - e->cCollision->collissionR) < 0 )
                {
                    e->cTransform->velocity.y = -e->cTransform->velocity.y;
                }
                if ((e->cTransform->pos.y + e->cCollision->collissionR) > m_windowc.H)
                {
                    e->cTransform->velocity.y = -e->cTransform->velocity.y;
                }
            }
        }
    }

    // Bullet collisions
    for (auto b : m_entitiesManager.getEntities("bullet"))
    {
        // Bullet out of bounds
        if (b->cShape && b->cTransform && b->cCollision)
        {
            if ((b->cTransform->pos.x + b->cCollision->collissionR) < 0)
            {
                b->destroy();
            }
            if ((b->cTransform->pos.x - b->cCollision->collissionR) > m_windowc.W)
            {
                b->destroy();
            }
            if ((b->cTransform->pos.y + b->cCollision->collissionR) < 0 )
            {
                b->destroy();
            }
            if ((b->cTransform->pos.y - b->cCollision->collissionR) > m_windowc.H)
            {
                b->destroy();
            }
        }

        // Bullet collision with entity
        for (auto e : m_entitiesManager.getEntities("enemy"))
        {
            if (e->cCollision)
            {
                float sumR = e->cShape->r + b->cShape->r;
                float distBetweenR = e->cTransform->pos.dist(b->cTransform->pos);

                if (distBetweenR < sumR && e->tag() != b->tag() && e != m_player)
                {
                    b->destroy();
                    spawnSmallEnemies(e);
                    e->destroy();
                }
            }
        }
    }
}

void Game::spawnPlayer()
{
    auto entity = m_entitiesManager.addEntity("player");

    entity->cTransform =    std::make_shared<CTransform>(Vec2f(100.0f, 100.0f), Vec2f(0.0f, 0.0f), 0.0f);
    entity->cShape =        std::make_shared<CShape>(Vec2f(100.0f, 100.0f), m_playerc.V, m_playerc.SR, Color({static_cast<unsigned char>(m_playerc.FR), static_cast<unsigned char>(m_playerc.FG), static_cast<unsigned char>(m_playerc.FB), 255}));
    entity->cInput =        std::make_shared<CInput>();
    entity->cCollision =    std::make_shared<CCollision>(m_playerc.CR);

    m_player = entity;
}

void Game::spawnEnemy()
{
    bool enemySpawned = false;
    int attempts = 0;
    int maxAttempts = 100;

    while (!enemySpawned && attempts < maxAttempts)
    {
        Vec2f spawnLocation;
        spawnLocation.x = (rand() % (m_windowc.W - 2 * m_enemyc.SR)) + m_enemyc.SR;
        spawnLocation.y = (rand() % (m_windowc.H - 2 * m_enemyc.SR)) + m_enemyc.SR;

        float distanceFromPlayer = spawnLocation.dist(m_player->cTransform->pos);
        float safeSpawnDistance = m_enemyc.CR + m_player->cShape->r + 50.0f;

        if (distanceFromPlayer > safeSpawnDistance)
        {
            auto enemy = m_entitiesManager.addEntity("enemy");

            int vertices = (rand() % m_enemyc.VMAX) + m_enemyc.VMIN;
            int speed =  m_enemyc.SMIN + (static_cast<float>(rand()) / m_enemyc.SMAX) * (m_enemyc.SMAX - m_enemyc.SMIN);

            float angleRadians = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;

            unsigned char rr = (rand() % 128) + 128;
            unsigned char rg = (rand() % 128) + 128;
            unsigned char rb = (rand() % 128) + 128;

            Vec2f v;
            v.x = speed * std::cos(angleRadians);
            v.y = speed * std::sin(angleRadians);

            enemy->cTransform =    std::make_shared<CTransform>(Vec2f(spawnLocation.x, spawnLocation.y), v, 0.0f);
            enemy->cShape =        std::make_shared<CShape>(Vec2f(100.0f, 100.0f), vertices, m_enemyc.SR, Color({rr, rg, rb, 255}));
            enemy->cCollision =    std::make_shared<CCollision>(m_enemyc.CR);

            enemySpawned = true;
        }
        else
        {
            attempts++;
        }
    }
    if (!enemySpawned)
    {
        std::cerr << "Error: Unable to find suitable spawn location for enemy." << std::endl;
    }
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity)
{
    float angleStep = 360.0f / entity->cShape->sides;
    float speed = 5.0f;

    for (int i = 0; i < entity->cShape->sides; i++)
    {
        auto enemy = m_entitiesManager.addEntity("small enemy");

        float angleRadians = (angleStep * i) * (M_PI / 180.0f);
        Vec2f v;
        v.x = speed * std::cos(angleRadians);
        v.y = speed * std::sin(angleRadians);

        Color smallEnemyColor = {entity->cShape->color.r, entity->cShape->color.g, entity->cShape->color.b, 255};
        enemy->cTransform =     std::make_shared<CTransform>(entity->cTransform->pos, v, 0.0f);
        enemy->cShape =         std::make_shared<CShape>(entity->cShape->center, entity->cShape->sides, entity->cShape->r / 2.0f, smallEnemyColor);
        enemy->cCollision =     std::make_shared<CCollision>(entity->cShape->r / 2.0f);
        enemy->cLifespan =      std::make_shared<CLifespan>(m_enemyc.L);
    }   
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2f& mousePos)
{
    auto bullet = m_entitiesManager.addEntity("bullet");

    Vec2f velocity = mousePos - entity->cTransform->pos;
    velocity.norm();
    velocity *= m_bulletc.S;

    bullet->cTransform =    std::make_shared<CTransform>(entity->cTransform->pos, velocity, 0.0f);
    bullet->cShape =        std::make_shared<CShape>(entity->cTransform->pos, m_bulletc.V, m_bulletc.SR, Color({static_cast<unsigned char>(m_bulletc.FR), static_cast<unsigned char>(m_bulletc.FG), static_cast<unsigned char>(m_bulletc.FB), 255}));
    bullet->cInput =        std::make_shared<CInput>();
    bullet->cCollision =    std::make_shared<CCollision>(m_bulletc.CR);
    bullet->cLifespan =     std::make_shared<CLifespan>(m_bulletc.L);
}