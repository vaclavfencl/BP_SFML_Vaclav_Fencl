#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "APP10 View (kamera)");
    window.setFramerateLimit(60);

    sf::Texture bgTex;
    if (!bgTex.loadFromFile("../assets/textures/bg1.jpg"))
        return 1;
    sf::Sprite background(bgTex);

    sf::View view(sf::FloatRect({0.f, 0.f}, {800.f, 600.f}));
    const float moveSpeed = 6.f;

    while (window.isOpen()) {
        while (const auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();

            if (const auto* rs = ev->getIf<sf::Event::Resized>()) {
                view.setSize({
                    static_cast<float>(rs->size.x),
                    static_cast<float>(rs->size.y)
                });
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            view.move({0.f, -moveSpeed});  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            view.move({0.f,  moveSpeed});  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            view.move({-moveSpeed, 0.f});   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            view.move({ moveSpeed, 0.f});   

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            view.rotate(sf::degrees(-1.f));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            view.rotate(sf::degrees(1.f));

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Equal))  
            view.zoom(0.98f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Hyphen))  
            view.zoom(1.02f);

        window.setView(view);

        window.clear();
        window.draw(background);
        window.display();
    }
}