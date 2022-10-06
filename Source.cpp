#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <time.h>
#include <random>
#include <SFML/Audio.hpp>
#include<string>
#include<fstream>


using namespace sf;
using namespace std;

int SIZE = 30;
int vx = SIZE * SIZE;
int vy = SIZE * 15;
int direction = 2;
int num1 = 1;
int score = 0;


struct Fruit {
    int x, y;
}apple;

struct Snake {
    int x, y;
}snake[100];

void gameAction() {
    for (int i = num1; i > 0; --i) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }

    //DOWN
    if (direction == 0) {
        snake[0].y += 1;

    }
    //LEFT
    else if (direction == 1) {
        snake[0].x -= 1;
    }
    //RIGHT
    else if (direction == 2) {
        snake[0].x += 1;

    }
    //UP
    else if (direction == 3) {
        snake[0].y -= 1;
    }


}


int main()
{
    srand(time(NULL));

    RenderWindow window(sf::VideoMode(vx, vy), "Snake Game");
    const Color colorarray[5] = { Color::Cyan,Color::Blue,Color::Red,Color::Yellow,Color::Green };
    Clock clock;
    float chrono = 0;
    float delay = 0.12;

    RectangleShape snakeBlock;

    snakeBlock.setSize(Vector2f(SIZE, SIZE));
    snakeBlock.setFillColor(colorarray[rand() % 5]);
    /*snakeBlock.setOutlineThickness(1);*/
   /* snakeBlock.setOutlineColor(Color::White);*/

    apple.x = rand() % 30;
    apple.y = rand() % 15;

    RectangleShape appleBlock;

    appleBlock.setSize(Vector2f(SIZE, SIZE));
    appleBlock.setFillColor(colorarray[rand() % 5]);
    /*appleBlock.setOutlineThickness(1);*/
    /*appleBlock.setOutlineColor(Color::White);*/

    Font font;
    font.loadFromFile("ka1.ttf");

    Text text;
    text.setFont(font);
    text.setString("Score: " + std::to_string(0)); //increment score
    text.setFillColor(Color::Green);
    text.setPosition(747, 2);
    text.setCharacterSize(25);

    /* Text text2;
     text2.setFont(font);
     text2.setString("GAME OVER");
     text2.setFillColor(Color::Red);
     text2.setPosition(250, 10);
     text2.setCharacterSize(72);*/

    SoundBuffer buffer;
    buffer.loadFromFile("apple.wav");
    Sound sound;
    sound.setBuffer(buffer);

    /*SoundBuffer buffer2;
    buffer2.loadFromFile("gameOver.ogg");
    Sound sound2;
    sound2.setBuffer(buffer2);*/



    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        chrono += time;

        Event e;

        while (window.pollEvent(e))
        {

            if (e.type == Event::Closed)
            {
                window.close();

            }


        }
        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
            direction = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            direction = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            direction = 2;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
            direction = 3;
        }

        if (chrono > delay) {
            chrono = 0;
            gameAction();

        }

        window.clear();
































































































        for (int i = 0; i < num1; i++) {
            snakeBlock.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
            window.draw(snakeBlock);
        }
        if ((snake[0].x == apple.x) && (snake[0].y == apple.y)) {
            num1++;
            text.setString("Score: " + std::to_string(num1 - 1));
            apple.x = rand() % 30;
            apple.y = rand() % 15;
            appleBlock.setFillColor(colorarray[rand() % 5]);
            snakeBlock.setFillColor(colorarray[rand() % 5]);
            sound.play();
            score = num1 - 1;
            /*cout << score << endl;*/
        }

        ofstream outFile;

        outFile.open("scores.txt");

        outFile << "SCORE : " << score << endl;

        outFile.close();

        if (snake[0].x > 30) {
            snake[0].x = 0;
            num1 = 1;
            text.setString("Score: " + std::to_string(num1 - 1));
            /*window.clear();
            text2.setString("GAME OVER");*/
            /*sound2.play();*/
            window.close();
            cout << "GAME OVER" << endl;

        }

        if (snake[0].y > 15) {
            snake[0].y = 0;
            num1 = 1;
            text.setString("Score: " + std::to_string(num1 - 1));
            /*window.clear();
            text2.setString("GAME OVER");*/
            /* sound2.play();*/
            window.close();
            cout << "GAME OVER" << endl;

        }
        // lw mat y3eed el door mn el 2wel
        if (snake[0].x < 0) {

            snake[0].x = 0;
            snake[0].y = 0;
            num1 = 1;
            text.setString("Score: " + std::to_string(num1 - 1));
            /*window.clear();
            text2.setString("GAME OVER");*/
            /* sound2.play();*/
            window.close();
            cout << "GAME OVER" << endl;
        }

        if (snake[0].y < 0) {

            snake[0].x = 0;
            snake[0].y = 0;
            num1 = 1;
            text.setString("Score: " + std::to_string(num1 - 1));
            /*window.clear();
            text2.setString("GAME OVER");*/
            /*sound2.play();*/
            window.close();
            cout << "GAME OVER" << endl;
        }

        for (int i = 1; i < num1; i++) {
            if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y)) {
                {
                    snake[0].x = 0;
                    snake[0].y = 0;
                    num1 = 1;
                    text.setString("Score: " + std::to_string(num1 - 1));
                    /*window.clear();*/
                    /*text2.setString("GAME OVER");*/
                    /*sound2.play();*/
                    window.close();
                    cout << "GAME OVER" << endl;
                }

            }
        }


        appleBlock.setPosition(apple.x * SIZE, apple.y * SIZE);

        window.draw(appleBlock);
        window.draw(text);
        window.display();


    }

    return 0;
}






//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//#include <time.h>
//#include <random>
//#include <SFML/Audio.hpp>
//#include<string>
//#include<fstream>
//
//
//using namespace sf;
//using namespace std;
//
//int SIZE = 30;
//int vx = SIZE * SIZE;
//int vy = SIZE * 15;
//int direction = 2;
//int num1 = 1;
//int score = 0;
//
//
//struct Fruit {
//    int x, y;
//}apple;
//
//struct Snake {
//    int x, y;
//}snake[100];
//
//void gameAction() {
//    for (int i = num1; i > 0; --i) {
//        snake[i].x = snake[i - 1].x;
//        snake[i].y = snake[i - 1].y;
//    }
//
//    //DOWN
//    if (direction == 0) {
//        snake[0].y += 1;
//
//    }
//    //LEFT
//    else if (direction == 1) {
//        snake[0].x -= 1;
//    }
//    //RIGHT
//    else if (direction == 2) {
//        snake[0].x += 1;
//
//    }
//    //UP
//    else if (direction == 3) {
//        snake[0].y -= 1;
//    }
//
//
//}
//
//
//int main()
//{
//    srand(time(NULL));
//
//    RenderWindow window(sf::VideoMode(vx, vy), "Snake Game");
//
//    Clock clock;
//    float chrono = 0;
//    float delay = 0.15;
//
//    RectangleShape snakeBlock;
//
//    snakeBlock.setSize(Vector2f(SIZE, SIZE));
//    snakeBlock.setFillColor(Color::Green);
//    /*snakeBlock.setOutlineThickness(1);*/
//   /* snakeBlock.setOutlineColor(Color::White);*/
//
//    apple.x = rand() % 30;
//    apple.y = rand() % 15;
//
//    RectangleShape appleBlock;
//
//    appleBlock.setSize(Vector2f(SIZE, SIZE));
//    appleBlock.setFillColor(Color::Red);
//    /*appleBlock.setOutlineThickness(1);*/
//    /*appleBlock.setOutlineColor(Color::White);*/
//
//    Font font;
//    font.loadFromFile("Vonique 64 Bold.ttf");
//
//    Text text;
//    text.setFont(font);
//    text.setString("Score: " + std::to_string(0)); //increment score
//    text.setFillColor(Color::Green);
//    text.setPosition(250, 10);
//    text.setCharacterSize(72);
//
//   /* Text text2;
//    text2.setFont(font);
//    text2.setString("GAME OVER");
//    text2.setFillColor(Color::Red);
//    text2.setPosition(250, 10);
//    text2.setCharacterSize(72);*/
//
//    SoundBuffer buffer;
//    buffer.loadFromFile("apple.wav");
//    Sound sound;
//    sound.setBuffer(buffer);
//
//    /*SoundBuffer buffer2;
//    buffer2.loadFromFile("gameOver.ogg");
//    Sound sound2;
//    sound2.setBuffer(buffer2);*/
//
//
//
//    while (window.isOpen())
//    {
//
//        float time = clock.getElapsedTime().asSeconds();
//        clock.restart();
//        chrono += time;
//
//        Event e;
//
//        while (window.pollEvent(e))
//        {
//
//            if (e.type == Event::Closed)
//            {
//                window.close();
//
//            }
//
//
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
//            direction = 0;
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
//            direction = 1;
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
//            direction = 2;
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) {
//            direction = 3;
//        }
//
//        if (chrono > delay) {
//            chrono = 0;
//            gameAction();
//
//        }
//
//        window.clear();
//
//        for (int i = 0; i < num1; i++) {
//            snakeBlock.setPosition(snake[i].x * SIZE, snake[i].y * SIZE);
//            window.draw(snakeBlock);
//        }
//        if ((snake[0].x == apple.x) && (snake[0].y == apple.y)) {
//            num1++;
//            text.setString("Score: " + std::to_string(num1 - 1));
//            apple.x = rand() % 30;
//            apple.y = rand() % 15;
//            sound.play();
//            score = num1 - 1;
//            /*cout << score << endl;*/
//        }
//
//        ofstream outFile;
//
//        outFile.open("scores.txt");
//
//        outFile << "SCORE : " << score << endl;
//
//        outFile.close();
//
//        if (snake[0].x > 30) {
//            snake[0].x = 0;
//            num1 = 1;
//            text.setString("Score: " + std::to_string(num1 - 1));
//            /*window.clear();
//            text2.setString("GAME OVER");*/
//            /*sound2.play();*/
//            window.close();
//            cout << "GAME OVER" << endl;
//
//        }
//
//        if (snake[0].y > 15) {
//            snake[0].y = 0;
//            num1 = 1;
//            text.setString("Score: " + std::to_string(num1 - 1));
//            /*window.clear();
//            text2.setString("GAME OVER");*/
//            /* sound2.play();*/
//            window.close();
//            cout << "GAME OVER" << endl;
//
//        }
//        // lw mat y3eed el door mn el 2wel
//        if (snake[0].x < 0) {
//
//            snake[0].x = 0;
//            snake[0].y = 0;
//            num1 = 1;
//            text.setString("Score: " + std::to_string(num1 - 1));
//            /*window.clear();
//            text2.setString("GAME OVER");*/
//            /* sound2.play();*/
//            window.close();
//            cout << "GAME OVER" << endl;
//        }
//
//        if (snake[0].y < 0) {
//
//            snake[0].x = 0;
//            snake[0].y = 0;
//            num1 = 1;
//            text.setString("Score: " + std::to_string(num1 - 1));
//            /*window.clear();
//            text2.setString("GAME OVER");*/
//            /*sound2.play();*/
//            window.close();
//            cout << "GAME OVER" << endl;
//        }
//
//        for (int i = 1; i < num1; i++) {
//            if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y)) {
//                {
//                    snake[0].x = 0;
//                    snake[0].y = 0;
//                    num1 = 1;
//                    text.setString("Score: " + std::to_string(num1 - 1));
//                    /*window.clear();*/
//                    /*text2.setString("GAME OVER");*/
//                    /*sound2.play();*/
//                    window.close();
//                    cout << "GAME OVER" << endl;
//                }
//
//            }
//        }
//
//
//        appleBlock.setPosition(apple.x * SIZE, apple.y * SIZE);
//
//        window.draw(appleBlock);
//        window.draw(text);
//        window.display();
//
//
//    }
//
//    return 0;
//}





