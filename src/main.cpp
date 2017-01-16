#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>


sf::Vector2f get_sprite_size(sf::Sprite &s1) {
    sf::Vector2f result;
    sf::IntRect texture_size = s1.getTextureRect();
    sf::Vector2f scale = s1.getScale();
    result.x = texture_size.width * scale.x;
    result.y = texture_size.height * scale.y;
    return result;
}


bool check_collision(sf::Sprite &s1, sf::Sprite &s2) {
    sf::Vector2f s1_size = get_sprite_size(s1);
    sf::Vector2f s2_size = get_sprite_size(s2);

    sf::Vector2f s1_pos = s1.getPosition();
    sf::Vector2f s2_pos = s2.getPosition();

    return (
       ((s1_pos.x + s1_size.x / 2) >= (s2_pos.x - s2_size.x / 2))
      &((s1_pos.x - s1_size.x / 2) <= (s2_pos.x + s2_size.x / 2))
      &((s1_pos.y + s1_size.y / 2) >= (s2_pos.y - s2_size.y / 2))
      &((s1_pos.y - s1_size.y / 2) <= (s2_pos.y + s2_size.y / 2))
    );
}

int main(int argc, char * argv[]) {
    srand(std::time(0));

    //create window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Brand cool title :D:D:D");

    //declare textures
    sf::Texture test_arrow_texture, wall_texture;

    //init textures
    test_arrow_texture.loadFromFile("asset/img/test_arrow.png");
    wall_texture.loadFromFile("asset/img/wall.png");

    //create sprites
    sf::Sprite myarrow(test_arrow_texture);
    myarrow.setOrigin(0,0);

    int wall_count = 5;
    sf::Sprite mywalls[wall_count];

    for (int i = 0; i < wall_count; i++) {
        mywalls[i].setTexture(wall_texture);
        mywalls[i].setOrigin(0,0);

        int x,y;
        x = std::rand() % 600;
        y = std::rand() % 400;
        mywalls[i].setPosition(x, y);
    }

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
        int myarrow_xoffset, myarrow_yoffset;
        myarrow_xoffset = 0;
        myarrow_yoffset = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            myarrow_yoffset--;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            myarrow_xoffset--;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            myarrow_yoffset++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            myarrow_xoffset++;
        }
        myarrow.move(myarrow_xoffset, myarrow_yoffset);

        bool collide = false;
        for (int i = 0; i < wall_count; i++) {
            if (check_collision(myarrow, mywalls[i])) {
                collide = true;
            }
        }
        if (collide) {
            myarrow.move(-myarrow_xoffset, -myarrow_yoffset);
        }

        //render
        window.clear(bg_color);
        for (int i = 0; i < wall_count; i++) {
            window.draw(mywalls[i]);
        }
        window.draw(myarrow);
        window.display();
    }
    return 0;
}
