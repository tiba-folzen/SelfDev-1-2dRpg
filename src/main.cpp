#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <rapidjson/document.h>
#include <fstream>
#include <iostream>

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

class GameEntity {
public:
    bool exist;
    bool have_keyboard;
    bool drawable;
    bool have_logic;

    virtual void draw(sf::RenderWindow & w) {
        std::cout << "base\n";
    }
    virtual void logic() {}
    virtual void logic(double timediff) {}

    GameEntity() {
        this->exist = false;
        this->drawable = false;
        this->have_keyboard = false;
        this->have_logic = false;
    }
};

//init mapdata
GameEntity * ents[100];

class Wall : public GameEntity {
public:
    sf::Sprite sprite;

    void draw(sf::RenderWindow & w) {
        w.draw(this->sprite);
    }

    Wall() {
        this->drawable = true;
    }
};

class Player : public GameEntity {
public:
    sf::Sprite sprite;
    int direction;

    void draw(sf::RenderWindow & w) {
        w.draw(this->sprite);
    }

    Player() {
        this->drawable = true;
        this->have_keyboard = true;
        this->have_logic = true;
        this->direction = 0;
    }

    void logic() {
        int xoffset, yoffset;
        xoffset = 0;
        yoffset = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            yoffset--;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            xoffset--;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            yoffset++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            xoffset++;
        }
        this->sprite.move(xoffset, yoffset);

        bool collide = false;
        for (int i = 0; i < 100; i++) {
            if ((ents[i] != NULL) & (ents[i] != this)) {
                if (ents[i]->drawable) {
                    if (check_collision(this->sprite, ((Wall *)ents[i])->sprite)) {
                        collide = true;
                    }
                }
            }
        }
        if (collide) {
            this->sprite.move(-xoffset, -yoffset);
        }
    }
};


int main(int argc, char * argv[]) {
    //init random
    srand(std::time(0));

    for (int i = 0; i < 100; i++) ents[i] = NULL;

    //init map
    rapidjson::Document config;
    std::string cfg_string;
    std::ifstream cfg_file("asset/map/mapuka.json");

    std::string buff;
    while (cfg_file >> buff) {
        cfg_string += buff;
    }

    std::cout << cfg_string << std::endl;

    config.Parse(cfg_string.c_str());

    //create window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Brand cool title :D:D:D");

    //declare textures
    sf::Texture test_arrow_texture, wall_texture;

    //init textures
    test_arrow_texture.loadFromFile("asset/img/player.png");
    wall_texture.loadFromFile("asset/img/wall2.png");

    for (int i = 0; i < config.Capacity(); i++) {
        std::cout << config[i]["type"].GetString() << std::endl;

        std::string type = config[i]["type"].GetString();

        if (type == "wall") {
            double x = config[i]["pos"]["x"].GetDouble();
            double y = config[i]["pos"]["y"].GetDouble();
            Wall * w = new Wall();
            w->sprite.setPosition(x,y);
            w->sprite.setTexture(wall_texture);
            ents[i] = w;
        } else if (type == "player") {
            double x = config[i]["pos"]["x"].GetDouble();
            double y = config[i]["pos"]["y"].GetDouble();
            Player * p = new Player();
            p->sprite.setTexture(test_arrow_texture);
            p->sprite.setPosition(x, y);
            ents[i] = p;
        } else {
            std::cout << "type unknown\n";
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        for (int i = 0; i < 100; i++) {
            if (ents[i] != NULL) {
                if (ents[i]->have_logic) {
                    ents[i]->logic();
                }
            }
        }

        //render
        window.clear(sf::Color::White);
        for (int i = 0; i < 100; i++) {
            if (ents[i] != NULL) {
                if (ents[i]->drawable) {
                    ents[i]->draw(window);
                }
            }
        }

        window.display();
    }
    return 0;
}
