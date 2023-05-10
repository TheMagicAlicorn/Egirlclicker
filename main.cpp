#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "egirls.hpp"
#include "db.h"
#include "game.hpp"
#include "fonts.h"

sf::ContextSettings settings;
sf::RenderWindow window;
sf::Mutex mutex;
sf::Font markerfelt;
sf::Text fpsText;
sf::Clock frametimer;

Egirls egirls;
Daddy daddy;
CatEars catears;

Menu menu(markerfelt);

int newSave = 0;
int showMenu = 0;

void render(Game& game){
    while(window.isOpen()){
        mutex.lock();
        window.clear();

        game.draw(window, egirls, daddy, catears);

        GLfloat deltaTime = frametimer.restart().asSeconds();
        GLfloat fps = 1 / deltaTime;
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << fps;
        fpsText.setString(stream.str());
        window.draw(fpsText);

        if(showMenu == 1) menu.draw(window);

        window.display();
        mutex.unlock();
        sf::sleep(sf::microseconds(1000000 / 30));
    }
}

void saving(){
    while(window.isOpen()){
        newSave++;
        db_save(egirls.getCount(), daddy.getCount(), catears.getCount());
        if(newSave >= 1800){
            db_newsave(egirls.getCount(), daddy.getCount(), catears.getCount());
            newSave = 0;
        }
        sf::sleep(sf::milliseconds(1000));
    }
}

void egirlsPerSecond(){
    while(window.isOpen() && (catears.getCount() > 0)){
        egirls.count++;
        sf::sleep(sf::microseconds(1000000 / catears.getCount()));
    }
}

int main(){
    db_init();
    std::cout << std::to_string(savedEgirls) << std::endl;
    egirls.count = savedEgirls;
    daddy.count = savedDaddy;
    catears.count = savedCatears;

    sf::err().rdbuf(NULL);

    window.create(sf::VideoMode(800, 600), "Egirl Clicker", sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);

    markerfelt.loadFromMemory(markerfelt_data, markerfelt_len);

    Game game(markerfelt);

    fpsText.setFont(markerfelt);
    fpsText.setCharacterSize(12);
    fpsText.setPosition(0, 0);
    fpsText.setFillColor(sf::Color::White);

    window.setActive(false);

    sf::Thread savingThread(&saving);
    savingThread.launch();

    sf::Thread egirlsThread(&egirlsPerSecond);
    egirlsThread.launch();

    sf::Thread renderThread([&](){
        render(game);
    });
    renderThread.launch();
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            mutex.lock();
            switch(event.type){
            case sf::Event::Closed:
                db_close();
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape){
                    if(!showMenu) showMenu = 1;
                    else showMenu = 0;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(!showMenu) game.uwuPressed(window, egirls, daddy, catears);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left){
                    game.uwuUnpressed();
                }
                break;
            }
            mutex.unlock();
        }
        sf::sleep(sf::microseconds(1000000 / 30));
    }
    db_close();
    return 0;
}