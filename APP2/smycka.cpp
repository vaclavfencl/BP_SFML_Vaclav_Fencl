#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "SFML - Ukazka smycky");
    window.setFramerateLimit(60);

    sf::Clock clock;

    sf::Font font;
    font.openFromFile("../assets/fonts/Roboto-Light.ttf");

    sf::Text hud(font);
    hud.setCharacterSize(16u);
    hud.setFillColor(sf::Color::Black);
    hud.setPosition(sf::Vector2f{8.f, 8.f});
    hud.setString("dt: 0.000 s  |  FPS: 0");

    sf::RectangleShape rect({100.f, 50.f});
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(sf::Vector2f{
        window.getSize().x / 2.f - rect.getSize().x / 2.f,
        window.getSize().y / 2.f - rect.getSize().y / 2.f
    });

    const float speed = 100.f;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        sf::Time dt = clock.restart();
        float fps = (dt.asSeconds() > 0.f) ? 1.f / dt.asSeconds() : 0.f;

        std::ostringstream os;
        os << "dt: " << std::fixed << std::setprecision(3) << dt.asSeconds()
           << " s  |  FPS: " << std::setprecision(0) << fps;
        hud.setString(os.str());

        rect.move(sf::Vector2f{speed * dt.asSeconds(), 0.f});

        if (rect.getPosition().x > window.getSize().x) {
            rect.setPosition(sf::Vector2f{
                -rect.getSize().x,
                rect.getPosition().y
            });
        }

        window.clear(sf::Color::White);
        window.draw(hud);
        window.draw(rect);
        window.display();
    }
    return 0;
}
