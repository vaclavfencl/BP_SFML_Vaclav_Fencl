#include <SFML/Graphics.hpp>
#include <array>

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "APP6 – Text & Fonty");
    window.setFramerateLimit(60);

    std::array<sf::Font, 3> fonts;
    fonts[0].openFromFile("../assets/fonts/Roboto-Light.ttf");
    fonts[1].openFromFile("../assets/fonts/Gameplay.ttf");
    fonts[2].openFromFile("../assets/fonts/Akira.otf");

    int currentFont = 0;

    sf::Text text(fonts[0]);
    text.setCharacterSize(24u);
    text.setString("Stiskni 1, 2 nebo 3 ke zmene fontu a Q, W, E pro zmenu textu");
    text.setFillColor(sf::Color::Black);
    text.setPosition({100.f, 250.f});

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                using Key = sf::Keyboard::Key;

                switch (key->code) {
                    case Key::Num1:
                        currentFont = 0;
                        text.setFont(fonts[0]);
                        break;
                    case Key::Num2:
                        currentFont = 1;
                        text.setFont(fonts[1]);
                        break;
                    case Key::Num3:
                        currentFont = 2;
                        text.setFont(fonts[2]);
                        break;
                    case Key::Q:
                        text.setString(U"UTB se nachazi v Zline");
                        break;
                    case Key::W:
                        text.setString(U"Toto je SFML text");
                        break;
                    case Key::E:
                        text.setString(U"Hello world");
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }

    return 0;
}
