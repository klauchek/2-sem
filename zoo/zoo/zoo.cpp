#include <iostream>

#include "zoo.h"
#include "zoo_map.h"


ANIMAL::ANIMAL(String F_I, String F_S, float X, float Y, float A, float B, float W, float H)
{
    File_I = F_I;
    File_S = F_S;
    image.loadFromFile("Images/" + File_I);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    buffer.loadFromFile("Sound/" + File_S);
    sound.setBuffer(buffer);
    x = X; y = Y;
    a = A; b = B;
    w = W; h = H;
    sprite.setTextureRect(IntRect(a, b, w, h));
};



void ANIMAL::feed(int cage)
{
sound.play();
}



bool ANIMAL::interactionWithMap(String zoo_map[], float time)
{
    for (int i = y / 34; i < (y + h) / 34; ++i)
        for (int j = x / 32; j < (x + w) / 32; ++j)
            switch (zoo_map[i][j])
            {
            case 'y':
            case 'b':
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

bool ANIMAL::control(float time, float& CurrentFrame, int dir, String zoo_map[], int sprite_num_frames, int mode)
{
    direction = dir;
    
    if (mode == DAY)
        speed = 0.06;
    else if (mode == NIGHT)
        speed = 0.00;

    CurrentFrame += 0.1f * time;

    CurrentFrame = CurrentFrame > sprite_num_frames ? 0 : CurrentFrame;

    switch (dir)
    {
    case UP:
    case RIGHT: sprite.setTextureRect(IntRect(w * int(CurrentFrame) + a, b, w, h));
        break;

    case DOWN:
    case LEFT: sprite.setTextureRect(IntRect(w * int(CurrentFrame + 1) + a, b, w, h));
        break;
    }

    return (update(time, zoo_map));
}


//.................DRAWING MAP......................//
void draw_map(Sprite& s_map, RenderWindow& window, Sprite& pumbasprite, Sprite& timonsprite, Sprite& zazusprite,
    Sprite& bearsprite, Sprite& simbasprite, Sprite& foxsprite,
    Sprite& owlsprite, Sprite& wolfsprite,
    Sprite& hedgehogsprite, Sprite& haresprite, String zoo_map[])
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
    window.draw(haresprite);
    window.draw(foxsprite);
    window.draw(bearsprite);
    window.draw(simbasprite);
    window.draw(zazusprite);
    window.draw(wolfsprite);
    window.draw(owlsprite);
    window.draw(hedgehogsprite);
    window.display();
}


//...........ZOO RUN................//

void zoo_run(RenderWindow& window)
{
    Image map_image;       map_image.loadFromFile("../Images/map.png");
    Texture map;          map.loadFromImage(map_image);
    Sprite s_map;         s_map.setTexture(map);

    /*ANIMAL::ANIMAL(String F_I, String F_S, float X, float Y, float A, float B, float W, float H)*/

    simba simba("characters/simba.png", "simba.ogg", 100, 200, 0, 240, 51, 51);
    pumba pumba("characters/pumba.png", "pumba.wav", 400, 200, 0, 151,  42, 41);
    timon timon("characters/timon.png", "timon.wav", 600, 200, 359, 602,  42, 52);
    
    zazu zazu("characters/zazu.png", "zazu.ogg", 830, 200, 0, 100, 44, 44);
    hare hare("characters/hare.png", "hare.ogg", 1050, 200, 80, 0,  55, 34);
    bear bear("characters/bear.png", "bear.ogg",  100, 500, 0, 17, 55, 50);
    fox fox("characters/fox.png", "fox.ogg", 350, 500, 0, 140,  51, 35);
    
    hedgehog hedgehog("characters/hedgehog.png", "hedgehog.ogg", 600, 500, 0, 100, 67, 44);
    wolf wolf("characters/wolf.png", "wolf.ogg",  1050, 500, 0, 100, 67, 44);
    owl owl("characters/owl.png", "owl.ogg",  800, 500, 0, 0, 60, 43);



   /* simba simba("../Images/characters/simba.png", "simba.ogg", 100, 200, 0, 240, 51, 51);
    pumba pumba("../Images/characters/pumba.png", "pumba.wav", 400, 200, 4, 151, 42, 41);
    timon timon("../Images/characters/timon.png", "timon.wav", 700, 200, 359, 602, 42, 52);
    zazu zazu("../Images/characters/zazu.png", "zazu.ogg", 1000, 200, 0, 100, 44, 44);
    hare hare("../Images/characters/hare.png", "hare.ogg", 1200, 200, 80, 0, 55, 34);
    bear bear("../Images/characters/bear.png", "bear.ogg", 100, 600, 0, 17, 55, 50);
    fox fox("../Images/characters/fox.png", "fox.ogg", 400, 600, 0, 140, 51, 35);
    hedgehog hedgehog("../Images/characters/hedgehog.png", "hedgehog.ogg", 700, 600, 0, 67, 34, 34);
    wolf wolf("../Images/characters/wolf.png", "wolf.ogg", 1000, 600, 0, 100, 67, 44);
    owl owl("../Images/characters/owl.png", "owl.ogg", 1200, 600, 0, 0, 51, 48);*/

    float CurrentFrame = 0;
    Clock clock;

    long long int counter = 0;
    int dir = DOWN;
    int mode = DAY;
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

        if (Keyboard::isKeyPressed(Keyboard::Num0))
            simba.feed(0);
        if (Keyboard::isKeyPressed(Keyboard::Num1))
            pumba.feed(1);
        if (Keyboard::isKeyPressed(Keyboard::Num2))
            timon.feed(2);
        if (Keyboard::isKeyPressed(Keyboard::Num3))
            zazu.feed(3);
        if (Keyboard::isKeyPressed(Keyboard::Num4))
            hare.feed(4);
        if (Keyboard::isKeyPressed(Keyboard::Num5))
            bear.feed(5);
        if (Keyboard::isKeyPressed(Keyboard::Num6))
            fox.feed(6);
        if (Keyboard::isKeyPressed(Keyboard::Num7))
            hedgehog.feed(7);
        if (Keyboard::isKeyPressed(Keyboard::Num8))
            wolf.feed(8);
        if (Keyboard::isKeyPressed(Keyboard::Num9))
            owl.feed(9);
    }

    if (counter % 700 == 0)
        dir = std::rand() % 4 + 4;

    if (counter % 9000 == 0)
    {
        if (mode == NIGHT)
        {
            mode = DAY;
            std::cout << "----------------------------------DAY NOW! MORNING EVERYONE " << std::endl;
        }
        else if (mode == DAY)
        {
            mode = NIGHT;
            std::cout << "----------------------------------NIGHT NOW " << std::endl;
        }
    }
        

    pumba.control(time, CurrentFrame, dir, zoo_map, pumba_frames, mode);
    timon.control(time, CurrentFrame, (dir + 1) % 4 + 4, zoo_map, timon_frames, mode);
    simba.control(time, CurrentFrame, (dir + 2) % 4 + 4, zoo_map, simba_frames, mode);
    zazu.control(time, CurrentFrame, (dir + 3) % 4 + 4, zoo_map, zazu_frames, mode);
    bear.control(time, CurrentFrame, (dir + 4) % 4 + 4, zoo_map, bear_frames, mode);
    fox.control(time, CurrentFrame, (dir + 5) % 4 + 4, zoo_map, fox_frames, mode);
    hare.control(time, CurrentFrame, (dir + 6) % 4 + 4, zoo_map, hare_frames, mode);

    owl.control(time, CurrentFrame, (dir + 7) % 4 + 4, zoo_map, owl_frames, !mode);
    wolf.control(time, CurrentFrame, (dir + 7) % 4 + 4, zoo_map, wolf_frames, !mode);
    hedgehog.control(time, CurrentFrame, (dir + 8) % 4 + 4, zoo_map, hedgehog_frames, !mode);

        //-------------------------------------------------------------------------------
        window.clear();
        draw_map(s_map, window, pumba.sprite, timon.sprite, zazu.sprite, bear.sprite,
            simba.sprite, fox.sprite, owl.sprite, wolf.sprite, hedgehog.sprite,
            hare.sprite, zoo_map);
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

        int menuNum = 0;
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