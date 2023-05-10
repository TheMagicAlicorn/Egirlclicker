#include <SFML/Graphics.hpp>
#include <iostream>
#include "sprites.h"
#include "egirls.h"

class Game{
    public:
        Game(sf::Font& font){
            bg.setSize(sf::Vector2f(800, 600));
            bgTexture.loadFromMemory(background_data, background_data_len);
            bg.setTexture(&bgTexture);

            daddyRect.setSize(sf::Vector2f(200, 30));
            daddyRect.setFillColor(sf::Color::Transparent);
            daddyRect.setOutlineColor(sf::Color::White);
            daddyRect.setOutlineThickness(2);
            daddyRect.setPosition(50, 200);

            daddyText.setFont(font);
            daddyText.setCharacterSize(20);
            daddyText.setPosition(55, 200);
            daddyText.setFillColor(sf::Color::White);
            daddyText.setString("Daddy");

            daddyCount.setFont(font);
            daddyCount.setCharacterSize(20);
            daddyCount.setPosition(240, 200);
            daddyCount.setFillColor(sf::Color::White);

            daddyPrice.setFont(font);
            daddyPrice.setCharacterSize(16);
            daddyPrice.setPosition(160, 205);
            daddyPrice.setFillColor(sf::Color::White);

            catearsRect.setSize(sf::Vector2f(200, 30));
            catearsRect.setFillColor(sf::Color::Transparent);
            catearsRect.setOutlineColor(sf::Color::White);
            catearsRect.setOutlineThickness(2);
            catearsRect.setPosition(260, 200);

            catearsText.setFont(font);
            catearsText.setCharacterSize(20);
            catearsText.setPosition(265, 200);
            catearsText.setFillColor(sf::Color::White);
            catearsText.setString("Cat Ears");

            catearsCount.setFont(font);
            catearsCount.setCharacterSize(20);
            catearsCount.setPosition(450, 200);
            catearsCount.setFillColor(sf::Color::White);

            catearsPrice.setFont(font);
            catearsPrice.setCharacterSize(16);
            catearsPrice.setPosition(370, 205);
            catearsPrice.setFillColor(sf::Color::White);

            egirlsText.setFont(font);
            egirlsText.setCharacterSize(64);
            egirlsText.setPosition(400, 50);
            egirlsText.setFillColor(sf::Color::White);
            
            uwutexturepressed.loadFromMemory(uwuButtonPressed_data, uwuButtonPressed_len);
            uwutextureunpressed.loadFromMemory(uwuButtonUnpressed_data, uwuButtonUnpressed_len);
            uwu.setTexture(uwutextureunpressed);
            sf::FloatRect uwuLocalBounds = uwu.getLocalBounds();
            uwu.setOrigin(uwuLocalBounds.width / 2, uwuLocalBounds.height / 2);
            uwu.setPosition(400, 500);
        }
        void draw(sf::RenderWindow& window, Egirls& egirls, Daddy& daddy, CatEars& catears){
            window.draw(bg);
            egirlsText.setString(std::to_string(egirls.getCount()) + " Egirls");
            sf::FloatRect egirlsBounds = egirlsText.getLocalBounds();
            egirlsText.setOrigin(egirlsBounds.width / 2, 0);
            window.draw(egirlsText);
            window.draw(uwu);
            window.draw(daddyRect);
            window.draw(daddyText);
            daddyCount.setString(std::to_string(daddy.getCount()));
            sf::FloatRect daddyCountBounds = daddyCount.getLocalBounds();
            daddyCount.setOrigin(daddyCountBounds.width, 0);
            window.draw(daddyCount);
            daddyPrice.setString(std::to_string(daddy.getPrice()));
            sf::FloatRect daddyPriceBounds = daddyPrice.getLocalBounds();
            daddyPrice.setOrigin(daddyPriceBounds.width / 2, 0);
            window.draw(daddyPrice);
            window.draw(catearsRect);
            window.draw(catearsText);
            catearsCount.setString(std::to_string(catears.getCount()));
            sf::FloatRect catearsCountBounds = catearsCount.getLocalBounds();
            catearsCount.setOrigin(catearsCountBounds.width, 0);
            window.draw(catearsCount);
            catearsPrice.setString(std::to_string(catears.getPrice()));
            sf::FloatRect catearsPriceBounds =catearsPrice.getLocalBounds();
            catearsPrice.setOrigin(catearsPriceBounds.width / 2, 0);
            window.draw(catearsPrice);
        }
        void uwuPressed(sf::RenderWindow& window, Egirls& egirls, Daddy& daddy, CatEars& catears){
            sf::FloatRect uwuBounds = uwu.getGlobalBounds();
            sf::FloatRect daddyBounds = daddyRect.getGlobalBounds();
            sf::FloatRect catearsBounds = catearsRect.getGlobalBounds();
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if(uwuBounds.contains(mousePos.x, mousePos.y)){
                egirls.increment(daddy.getCount());
                uwu.setTexture(uwutexturepressed);
            }
            if(daddyBounds.contains(mousePos.x, mousePos.y)){
                daddy.buy(egirls);
            }
            if(catearsBounds.contains(mousePos.x, mousePos.y)){
                catears.buy(egirls);
            }
        }
        void uwuUnpressed(){
            uwu.setTexture(uwutextureunpressed);
        }
    private:
        sf::Text fpsText;
        sf::Text egirlsText;
        sf::Text daddyText;
        sf::Text daddyCount;
        sf::Text daddyPrice;
        sf::Text catearsText;
        sf::Text catearsCount;
        sf::Text catearsPrice;
        sf::RectangleShape bg;
        sf::RectangleShape daddyRect;
        sf::RectangleShape catearsRect;
        sf::Sprite uwu;
        sf::Texture bgTexture;
        sf::Texture uwutextureunpressed;
        sf::Texture uwutexturepressed;
};

class Menu{
    public:
        Menu(sf::Font& font){
            menuWindow.setSize(sf::Vector2f(600, 400));
            menuWindow.setFillColor(Grey);
            menuWindow.setPosition(100, 100);
        }
        void draw(sf::RenderWindow& window){
            window.draw(menuWindow);
        }
    private:
        sf::RectangleShape menuWindow;
        sf::RectangleShape menuText;
        sf::RectangleShape quitButton;
        sf::Text quitText;
        sf::Color Grey = sf::Color(210, 215, 211, 255);
};