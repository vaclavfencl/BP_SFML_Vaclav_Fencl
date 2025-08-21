#include <SFML/Graphics.hpp>
#include <array>

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "APP Obrazky");
    window.setFramerateLimit(60);

    std::array<sf::Texture, 3> bgTextures;
    std::array<sf::Texture, 3> fgTextures;
    bgTextures[0].loadFromFile("../assets/textures/bg1.jpg");
    bgTextures[1].loadFromFile("../assets/textures/bg2.jpg");
    bgTextures[2].loadFromFile("../assets/textures/bg3.jpg");
    fgTextures[0].loadFromFile("../assets/textures/fg1.png");
    fgTextures[1].loadFromFile("../assets/textures/fg2.png");
    fgTextures[2].loadFromFile("../assets/textures/fg3.png");
    
    for (auto& t : bgTextures) t.setSmooth(true);
    for (auto& t : fgTextures) t.setSmooth(true);

    sf::Sprite background(bgTextures[0]);
    sf::Sprite foreground(fgTextures[0]);
    foreground.setPosition({200.f, 150.f}); 

    int currentBg = 0;
    int currentFg = 0;
    std::uint8_t alpha = 255;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                using Key = sf::Keyboard::Key;
                switch (key->code) {
                    case Key::Num1: background.setTexture(bgTextures[0]); break;
                    case Key::Num2: background.setTexture(bgTextures[1]); break;
                    case Key::Num3: background.setTexture(bgTextures[2]); break;

                    case Key::Q: foreground.setTexture(fgTextures[0]); break;
                    case Key::W: foreground.setTexture(fgTextures[1]); break;
                    case Key::E: foreground.setTexture(fgTextures[2]); break;
                    
                    case Key::Add:      
                    case Key::Equal:   
                        if (alpha <= 240) alpha += 15; else alpha = 255;
                        foreground.setColor({255, 255, 255, alpha});
                        break;
                    case Key::Subtract:
                    case Key::Hyphen:   
                        if (alpha >= 15) alpha -= 15; else alpha = 0;
                        foreground.setColor({255, 255, 255, alpha});
                        break;
                    default: break;
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(foreground);
        window.display();
    }
}
