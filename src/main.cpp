#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>

int main(int argc, char * argv[]) {
    srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(640, 480), "Brand cool title :D:D:D");
    sf::Texture test_arrow_texture;
    test_arrow_texture.loadFromFile("asset/img/test_arrow.png");
    sf::Sprite myarrow(test_arrow_texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        int r,g,b;
        r = 255; g = 255; b = 255;
        /*
        r = std::rand() % 256;
        g = std::rand() % 256;
        b = std::rand() % 256;
        */
        sf::Color bg_color(r,g,b);

        //logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            myarrow.move(0, -1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            myarrow.move(-1, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            myarrow.move(0, 1);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            myarrow.move(1, 0);
        }


        //render
        window.clear(bg_color);
        window.draw(myarrow);
        window.display();
    }
    return 0;
}
