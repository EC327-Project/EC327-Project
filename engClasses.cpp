#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>

using namespace sf;

struct platform{
    int px, py;
};

int main() {


    // initiate the game frame
    RenderWindow game(VideoMode(400, 533), "Jumping Through BU ENG");
    game.setFramerateLimit(60);

    // load images into texture object and use as Sprite
    Texture t1, t2, c1, c2, c3, c4, c5, c6, c7, c8, c9;
    Texture d1, d2, d3, d4, d5, d6, d7;

    t1.loadFromFile("images/avatar.PNG");
    t2.loadFromFile("images/tryAgain.jpg");
    c1.loadFromFile("images/ek103.jpg");
    c2.loadFromFile("images/ek131.jpg");
    c3.loadFromFile("images/ek125.jpg");
    c4.loadFromFile("images/ek210.jpg");
    c5.loadFromFile("images/ek301.jpg");
    c6.loadFromFile("images/ek307.jpg");
    c7.loadFromFile("images/ek381.jpg");
    c8.loadFromFile("images/winning.jpg");
    c9.loadFromFile("images/loseScreen.jpg");
    d1.loadFromFile("images/ek103plat.png");
    d2.loadFromFile("images/ek131plat.png");
    d3.loadFromFile("images/ek125plat.png");
    d4.loadFromFile("images/ek210plat.png");
    d5.loadFromFile("images/ek301plat.png");
    d6.loadFromFile("images/ek307plat.png");
    d7.loadFromFile("images/ek381plat.png");

    Sprite sAvatar(t1), stryAgain(t2);
    Sprite sBackground1(c1), sBackground2(c2), sBackground3(c3), sBackground4(c4), sBackground5(c5), sBackground6(c6), sBackground7(c7), sWinning(c8), sLosing(c9);
    Sprite sPlat1(d1), sPlat2(d2), sPlat3(d3), sPlat4(d4), sPlat5(d5), sPlat6(d6), sPlat7(d7);


    // initial starting variables for Avaar and movenemt
    int x = 100, y = 200,  scr = 0, level = 1, jumpcount = 1, highscr = 0;
    float accy = 0, speed = 2, acc = 0.15;

    // initiate a printable score on screen
    Text score, highLevel;
    Font font;
    font.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf");
    score.setFont(font);
    score.setFillColor(Color::Black);
    score.setCharacterSize(30);
    highLevel.setFont(font);
    highLevel.setCharacterSize(30);
    

    // create platform starting poing structure array
    platform plat[10];

    // generate 10 platforms at random locations
    plat[0].px = 90;
    plat[0].py = 285;
    for (int i = 1; i < 10; i++) {
       plat[i].px = rand()%400;
       plat[i].py = rand()%533;
    }

    // Start Game Loop
    while (game.isOpen()) {
        
        Event e;
        while (game.pollEvent(e)) {
            if (e.type == Event::Closed)
                game.close();
        }

        // avator movement by keypress
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            x += 4;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            x -= 4;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space) && jumpcount == 1) {
            if (accy < 5) {
            accy -= 6;
            } else if (accy > 5) {
                accy -= 13;
            }

            // ensure only one jume after touching platform
            jumpcount = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::E))
            scr = 7001;



        // define how avatar moves with increasing drop speed
        accy += acc;
        y += accy;

        // socre by the distance moved by little guy
        scr += accy / 1.5;
        score.setString(std::to_string(scr));

        // highest score
        if (scr > highscr)
            highscr = scr;
        
        highLevel.setString(std::to_string(highscr));
        if (highscr < 1000)
            highLevel.setString("Passed: None");
        else if (highscr >= 1000 && highscr < 2000)
            highLevel.setString("Passed: EK 103");
        else if (highscr >= 2000 && highscr < 3000)
            highLevel.setString("Passed: EK 131");
        else if (highscr >= 3000 && highscr < 4000)
            highLevel.setString("Passed: EK 125");
        else if (highscr >= 4000 && highscr < 5000)
            highLevel.setString("Passed: EK 210");
        else if (highscr >= 5000 && highscr < 6000)
            highLevel.setString("Passed: EK 301");
        else if (highscr >= 6000 && highscr < 7000)
            highLevel.setString("Passed: EK 307");


        // Change to different levels by current score
        if (scr < 1000) {
            level = 1;
            speed = 2;
        } else if (scr > 1000 && scr < 2000) {
            level = 2;
            speed = 2.3;
        } else if (scr > 2000 && scr < 3000) {
            level = 3;
            speed = 2.6;
            acc = 0.18;
        } else if (scr > 3000 && scr < 4000) {
            level = 4;
            speed = 3;
            acc =0.18;
        } else if (scr > 4000 && scr < 5000) {
            level = 5;
            speed = 3.3;
        } else if (scr > 5000 && scr < 6000) {
            level = 6;
            speed = 3.5;
            acc = 0.2;
        } else if (scr > 6000 && scr < 7000) {
            level = 7;
            speed = 3.8;
        } else if(scr > 7000) {
            level = 8;
        }

        // basic platform move upward function
        for (int i = 0; i < 10; i++) {
             
            plat[i].py = plat[i].py - speed;

            // if platform out of image, create a new one on top
            if (plat[i].py < 0) {
                plat[i].py = 533; plat[i].px = rand() % 400;
            }
        }


        // to check if avator is on platform and move alone if so
        for (int i = 0; i < 10; i++) {
            if ((x + 40 > plat[i].px) && (x + 15 < plat[i].px + 68)
             && (y + 78 > plat[i].py) && (y + 78 < plat[i].py + 14) ) {
              y = y - speed - accy;
              accy = 0;
              jumpcount = 1;
            }     
        }

        // check weather to draw game or win/lose screen
        if (y < 500 && y > 5 && level != 8) {

            // draw everything out based on lavel
            sAvatar.setPosition(x, y);
            score.setPosition(10, 10);
            highLevel.setPosition(100, 10);
            highLevel.setFillColor(Color::Black);
            if (level == 1) {
                game.draw(sBackground1);
                for (int i = 0; i < 10; i++) {
                    sPlat1.setPosition(plat[i].px, plat[i].py);
                    game.draw(sPlat1);
                }  
            } else if (level == 2) {
                game.draw(sBackground2);
                for (int i = 0; i < 10; i++) {
                    sPlat2.setPosition(plat[i].px, plat[i].py);
                    game.draw(sPlat2);
                }  
            } else if (level == 3) {
                game.draw(sBackground3);
                for (int i = 0; i < 10; i++) {
                    sPlat3.setPosition(plat[i].px, plat[i].py);
                    game.draw(sPlat3);
                }  
            } else if (level == 4) {
                game.draw(sBackground4);
                for (int i = 0; i < 10; i++) {
                    sPlat4.setPosition(plat[i].px, plat[i].py);
                    game.draw(sPlat4);
                }  
            } else if (level == 5) {
                game.draw(sBackground5);
                for (int i = 0; i < 10; i++) {
                    sPlat5.setPosition(plat[i].px, plat[i].py);
                    game.draw(sPlat5);
                }  
            } else if (level == 6) {
                game.draw(sBackground6);
                for (int i = 0; i < 10; i++) {
                    sPlat6.setPosition(plat[i].px, plat[i].py);
                    game.draw(sPlat6);
                }  
            } else if (level == 7) {
                game.draw(sBackground7);
                for (int i = 0; i < 10; i++) {
                    sPlat7.setPosition(plat[i].px, plat[i].py);
                    game.draw(sPlat7);
                }  
            } 

            game.draw(sAvatar);
            game.draw(score);
            game.draw(highLevel);

        } else if (level == 8) {

            // winning screen
            score.setPosition(10, 10);
            sAvatar.setPosition(260, 200);
            game.draw(sWinning);
            game.draw(sAvatar);

        } else {

            // losing screen
            game.draw(sLosing);
            stryAgain.setPosition(100, 200);
            game.draw(stryAgain);
            highLevel.setPosition(100, 120);
            highLevel.setFillColor(Color::White);
            game.draw(highLevel);
            accy = 0;
            acc = 0;

            // detect for mouse
            if (e.type == sf::Event::MouseButtonReleased &&
                e.mouseButton.button == sf::Mouse::Left) {
                
                // on the try again button - reset everything
                if (e.mouseButton.x > 100 && e.mouseButton.x < 100 + 200 &&
                    e.mouseButton.y > 200 && e.mouseButton.y < 200 + 100) {
                    x = 200;
                    y = 200;
                    accy = 0;
                    acc = 0.15;
                    scr = 0;
                    level = 1;
                }
            }
        }
 
        game.display();

    }

    return 0;
}


