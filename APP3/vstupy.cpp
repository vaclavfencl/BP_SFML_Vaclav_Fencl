#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "APP3 Input a Event");
    window.setFramerateLimit(60);

    // Čtverec (100x100), start uprostřed
    sf::RectangleShape square({100.f, 100.f});
    square.setFillColor(sf::Color::Black);
    square.setOrigin(sf::Vector2f{50.f, 50.f});
    square.setPosition(sf::Vector2f{400.f, 300.f});

    const float speed = 250.f; // px/s
    sf::Clock clock;

    while (window.isOpen()) {
        // --- EVENTS: klik myší mění barvu ---
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mb->button == sf::Mouse::Button::Left) {
                    square.setFillColor(sf::Color::Blue);
                } else if (mb->button == sf::Mouse::Button::Right) {
                    square.setFillColor(sf::Color::Red);
                }
            }
        }

        // --- INPUT: šipky = plynulý pohyb (real-time) ---
        const float dt = clock.restart().asSeconds();
        sf::Vector2f delta{0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  delta.x -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) delta.x += speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    delta.y -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  delta.y += speed * dt;

        square.move(delta);

        window.clear(sf::Color::White);
        window.draw(square);
        window.display();
    }
    return 0;
}
