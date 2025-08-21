#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "APP8 Animace");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("../assets/textures/anim.png")) {
        return -1;
    }

    const int frameWidth = 128;   
    const int frameHeight = 128;  
    const int frameCount = 6;     
    float frameTime = 0.15f;      

    std::vector<sf::IntRect> frames;
    for (int i = 0; i < frameCount; i++) {
        frames.emplace_back(sf::IntRect({ i * frameWidth, 0 }, { frameWidth, frameHeight }));
    }

    sf::Sprite sprite(texture);
    sprite.setTextureRect(frames[0]);
    sprite.setPosition({300.f, 200.f});

    bool playing = false;
    int currentFrame = 0;
    float elapsed = 0.f;

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                using Key = sf::Keyboard::Key;

                switch (key->code) {
                    case Key::Space: 
                        playing = !playing;
                        break;
                    case Key::Period: 
                        playing = false;
                        currentFrame = (currentFrame + 1) % frameCount;
                        sprite.setTextureRect(frames[currentFrame]);
                        break;
                    case Key::Comma: 
                        playing = false;
                        currentFrame = (currentFrame - 1 + frameCount) % frameCount;
                        sprite.setTextureRect(frames[currentFrame]);
                        break;
                    default:
                        break;
                }
            }
        }

        if (playing) {
            elapsed += dt;
            if (elapsed >= frameTime) {
                elapsed = 0.f;
                currentFrame = (currentFrame + 1) % frameCount;
                sprite.setTextureRect(frames[currentFrame]);
            }
        }

        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
