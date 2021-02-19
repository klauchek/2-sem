#ifndef PROJECT_ZOO_H
#define PROJECT_ZOO_H

#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

const int ZOO_RUN = 1;
const int INFO = 2;
const int EXIT = 3;

const int RIGHT = 4;
const int LEFT = 5;
const int UP = 6;
const int DOWN = 7;

void zoo_run(RenderWindow& window);
void run_about(RenderWindow& window);


//Day_Animals: Timon, Simba, Pumba, Zazu, Bear, Hare, Fox - 7 at all
//Night Animals: Wolf, Hedgehog, Owl - 3 at all

class ANIMAL
{
protected:
    float a, b, x, y, w, h;
    float   dx = 0,
        dy = 0;
public:
    float speed = 0;
    int direction = 0;
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    SoundBuffer buffer;
    Sound sound;

    ANIMAL(String F, float X, float Y, float A, float B, float W, float H);
    ~ANIMAL();
    bool interactionWithMap(String zoo_map[], float time);
    bool update(float time, String zoo_map[]);
    bool control(ANIMAL& ANIMAL, float time, float& CurrentFrame, int dir, String zoo_map[], int sprite_num_frames);
    virtual void talk();
    virtual void feed(int cage_number);
};


class Day_Animal:: public ANIMAL
{
//оставить цвет карты таким же - двигаются. Когда меняем цвет карты на темный -  нет.
};

class Night_Animal:: public ANIMAL
{
    //поменять цвет карты на темный - двигаются. когда цвет карты светлый - нет.
};

//у всех остальных меняем только talk
class Simba:: public Day_Animal
{
    int cage_number;
};


#endif PROJECT_ZOO_H