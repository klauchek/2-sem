#include <iostream>

#include "zoo.h"
#include "zoo_map.h"

ANIMAL::ANIMAL(String F, float X, float Y, float A, float B, float W, float H)
{
    File = F;
    image.loadFromFile("Images/" + File);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    buffer.loadFromFile("Sound/" + File);
    sound.setBuffer(buffer);
    x = X; y = Y;
    a = A; b = B;
    w = W; h = H;
    sprite.setTextureRect(IntRect(a, b, w, h));
};

ANIMAL::~ANIMAL()
{

}

void ANIMAL::talk()
{
sound.play();
}

//void ANIMAL:: feed(int cage_number)
//{
//    if ((Keyboard::isKeyPressed(Keyboard:: )))
//}


bool ANIMAL::interactionWithMap(String zoo_map[], float time)
{
    for (int i = y / 34; i < (y + h) / 34; ++i)
        for (int j = x / 32; j < (x + w) / 32; ++j)
            switch (zoo_map[i][j])
            {
            case 'y':
            case 'x':
                x -= dx * time;
                y -= dy * time;
                sprite.setPosition(x, y);
                break;

            default:
                break;
            }
    return false;
}

bool ANIMAL::update(float time, String zoo_map[])
{
    switch (direction)
    {
    case DOWN: dx = 0;
        dy = speed;
        break;

    case UP:   dx = 0;
        dy = -speed;
        break;

    case RIGHT:dx = speed;
        dy = 0;
        break;

    case LEFT: dx = -speed;
        dy = 0;
        break;
    }

    x += dx * time;
    y += dy * time;

    speed = 0;
    sprite.setPosition(x, y);
    return interactionWithMap(zoo_map, time);
}

bool control(ANIMAL& ANIMAL, float time, float& CurrentFrame, int dir, String zoo_map[], int sprite_num_frames)
{
    ANIMAL.direction = dir;
    ANIMAL.speed = 0.00;
    CurrentFrame += 0.1f * time;

    CurrentFrame = CurrentFrame > sprite_num_frames ? 0 : CurrentFrame;

    switch (dir)
    {
    case UP:
    case RIGHT: ANIMAL.sprite.setTextureRect(IntRect(38 * int(CurrentFrame) + 6, 150, 40, 40));
        break;

    case DOWN:
    case LEFT: ANIMAL.sprite.setTextureRect(IntRect(38 * int(CurrentFrame + 1) + 6, 150, -40, 40));
        break;
    }

    return (ANIMAL.update(time, zoo_map));
}


//-------------------------------------------------------------! MOVING SIMBA!
bool control_pumba(ANIMAL& ANIMAL, float time, float& CurrentFrame, int dir, String zoo_map[])
{
    ANIMAL.direction = dir;
    ANIMAL.speed = 0.00;
    CurrentFrame += 0.1f * time;

    CurrentFrame = CurrentFrame > 5 ? 0 : CurrentFrame;

    switch (dir)
    {
    case UP:
    case RIGHT: ANIMAL.sprite.setTextureRect(IntRect(38 * int(CurrentFrame) + 6, 150, 40, 40));
        break;

    case DOWN:
    case LEFT: ANIMAL.sprite.setTextureRect(IntRect(38 * int(CurrentFrame + 1) + 6, 150, -40, 40));
        break;
    }

    return (ANIMAL.update(time, zoo_map));
}

bool control_timon(ANIMAL& ANIMAL, float time, float& CurrentFrame, int dir, String zoo_map[])
{
    ANIMAL.direction = dir;
    ANIMAL.speed = 0.00;
    CurrentFrame += 0.1f * time;

    CurrentFrame = CurrentFrame > 9 ? 0 : CurrentFrame;

    switch (dir)
    {
    case UP:
    case RIGHT: ANIMAL.sprite.setTextureRect(IntRect(37 * int(CurrentFrame) + 360, 600, 37, 51));
        break;
    case DOWN:
    case LEFT:  ANIMAL.sprite.setTextureRect(IntRect(37 * int(CurrentFrame + 1) + 360, 600, -37, 51));
        break;
    default:    break;
    }

    return (ANIMAL.update(time, zoo_map));
}


//.................DRAWING MAP......................//
void draw_map(Sprite& s_map, RenderWindow& window, Sprite& pumbasprite,
    Sprite& timonsprite, String zoo_map[])
{
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++)
        {
            switch (zoo_map[i][j])
            {
            case ' ':s_map.setTextureRect(IntRect(143, 35, 33, 34)); break;
            case 'l':s_map.setTextureRect(IntRect(0, 35, 33, 34)); break;
            case 'p':s_map.setTextureRect(IntRect(243, 3, 33, 34)); break;
            case 'w':s_map.setTextureRect(IntRect(210, 3, 33, 34)); break;
            case 'd':s_map.setTextureRect(IntRect(108, 35, 33, 34)); break;
            case 'e':s_map.setTextureRect(IntRect(174, 35, 33, 34)); break;
            case 'a':s_map.setTextureRect(IntRect(242, 35, 33, 34)); break;
            case 'h':
            case 'y':s_map.setTextureRect(IntRect(74, 35, 33, 34)); break;
            case 'b':
            case 'x':s_map.setTextureRect(IntRect(208, 35, 33, 34)); break;
            }
            s_map.setPosition((float)j * 32, (float)i * 32);
            window.draw(s_map);
        }

    window.draw(pumbasprite);
    window.draw(timonsprite);
    window.display();
}


//...........ZOO RUN................//

void zoo_run(RenderWindow& window)
{
    Image map_image;      map_image.loadFromFile("Images/map.png");
    Texture map;          map.loadFromImage(map_image);
    Sprite s_map;         s_map.setTexture(map);

    ANIMAL pumba("characters/pumba.png", 100, 200, 0, 500, 42, 58);
    ANIMAL timon("characters/timon.png", 300, 560, 0, 500, 4, 66);

    float CurrentFrame = 0;
    Clock clock;

    int counter = 0;
    int dir_pumba = DOWN;
    int dir_timon = UP;
    while (window.isOpen())
    {
        ++counter;
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();

        if (counter % 700 == 0)
        {
            dir_pumba = std::rand() % 4 + 4;
            dir_timon = std::rand() % 4 + 4;
        }
        control_pumba(pumba, time, CurrentFrame, dir_pumba, zoo_map);
        control_timon(timon, time, CurrentFrame, dir_timon, zoo_map);

        //-------------------------------------------------------------------------------
        window.clear();
        draw_map(s_map, window, pumba.sprite, timon.sprite, zoo_map);
    }
}


//......................ABOUT.......................//
void run_about(RenderWindow& window)
{
    Image     back;             back.loadFromFile("Images/info/back.jpg");
    Texture   backtexture;      backtexture.loadFromImage(back);
    Sprite    backsprite;       backsprite.setTexture(backtexture);
    backsprite.setPosition(0, 0);

    //------------------------------------------------------background

    Image     text;             text.loadFromFile("Images/info/Text.jpg");
    Texture   texttexture;      texttexture.loadFromImage(text);
    Sprite    textsprite;       textsprite.setTexture(texttexture);
    textsprite.setPosition(70, 50);

    //-------------------------------------------------------text

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        window.clear();
        window.draw(backsprite);
        window.draw(textsprite);
        window.display();
    }
}

//.......................MENU.......................//
void menu(RenderWindow& window)
{

    Image     icon;
    icon.loadFromFile("Images/icon.jpg");
    window.setIcon(100, 70, icon.getPixelsPtr());

    //-----------------------------------------------------icon made

    Image     menubackground;     menubackground.loadFromFile("Images/menu/menu.jpg");
    Texture   menutexture;        menutexture.loadFromImage(menubackground);
    Sprite    menusprite;         menusprite.setTexture(menutexture);
    menusprite.setPosition(0, 0);

    //-------------------------------------------------background made

    Image     run;             run.loadFromFile("Images/menu/run.png");
    Texture   runtexture;      runtexture.loadFromImage(run);
    Sprite    runsprite;       runsprite.setTexture(runtexture);
    runsprite.setPosition(275, 250);

    //-------------------------------------------------------level made

    Image     exitgame;           exitgame.loadFromFile("Images/menu/exit.png");
    Texture   exitgametexture;    exitgametexture.loadFromImage(exitgame);
    Sprite    exitgamesprite;     exitgamesprite.setTexture(exitgametexture);
    exitgamesprite.setPosition(275, 450);

    //-------------------------------------------------exit made

    Image     info;           info.loadFromFile("Images/menu/about.png");
    Texture   infotexture;    infotexture.loadFromImage(info);
    Sprite    infosprite;     infosprite.setTexture(infotexture);
    infosprite.setPosition(1100, 10);

    //-------------------------------------------------about made

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
            if (event.type == Event::Closed)
                window.close();

        int menuNum = 0;

        //--------------------------------------------making color when aiming

        if (IntRect(275, 250, 235, 129).contains(Mouse::getPosition(window))) { runsprite.setColor(Color::Green); menuNum = ZOO_RUN; }
        if (IntRect(1100, 10, 90, 76).contains(Mouse::getPosition(window))) { infosprite.setColor(Color::Blue); menuNum = INFO; }
        if (IntRect(275, 450, 231, 126).contains(Mouse::getPosition(window))) { exitgamesprite.setColor(Color::Red); menuNum = EXIT; }

        //-------------------------------------------clearing color when out
        if (!IntRect(275, 250, 235, 129).contains(Mouse::getPosition(window))) { runsprite.setColor(Color::White); }
        if (!IntRect(1100, 10, 90, 76).contains(Mouse::getPosition(window))) { infosprite.setColor(Color::White); }
        if (!IntRect(275, 450, 231, 126).contains(Mouse::getPosition(window))) { exitgamesprite.setColor(Color::White); }


        if (Mouse::isButtonPressed(Mouse::Left))
        {
            switch (menuNum)
            {
            case ZOO_RUN: {
                RenderWindow new_window(VideoMode(1200, 675), "ZOO");
                window.close();
                zoo_run(new_window);
                break;                                                                           }

            case INFO: {
                RenderWindow new_window(VideoMode(1600, 900), "ZOO INFO");
                window.close();
                run_about(new_window);
                break;                                                                           }

            case EXIT: {
                window.close();
                break;                                                                           }

            default:
                break;
            }
            if (menuNum >= ZOO_RUN && menuNum <= INFO)
            {
                RenderWindow after_window(VideoMode(1200, 745), "ZOO HOME");
                menu(after_window);
            }
        }

        window.clear();
        window.draw(menusprite);
        window.draw(runsprite);
        window.draw(exitgamesprite);
        window.draw(infosprite);
        window.display();
    }
}


int main()
{
    RenderWindow window(VideoMode(1200, 745), "ZOO HOME");
    menu(window);

    return 0;
}