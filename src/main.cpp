#include <SFML/Graphics.hpp>

int main(int argc, char * argv[]) {
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

        window.clear(sf::Color::Green);
        window.draw(myarrow);
        window.display();
    }
    return 0;
}
