#include <SFML/Graphics.hpp>
#include <algorithm>

int main() {
    sf::RenderWindow window(sf::VideoMode({960u, 600u}), "APP5 transformace");
    window.setFramerateLimit(120);

    sf::RectangleShape rect({200.f, 120.f});
    rect.setFillColor(sf::Color(60,140,255));
    rect.setOutlineThickness(2.f);
    rect.setOutlineColor(sf::Color::White);
    rect.setOrigin(rect.getSize()*0.5f);

    sf::Transform M; 
    auto reset = [&](){
        M = sf::Transform{};
        sf::Transform T; T.translate({480.f,300.f});
        M = T * M;
    };
    reset();

    const float moveSpeed = 300.f;
    const float rotSpeed  = 90.f;
    const float dirRate   = 0.9f;
    const float uniRate   = 1.0f;

    sf::Clock clock;

    while (window.isOpen()) {
        while (const auto e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) window.close();
        }

        float dt = clock.restart().asSeconds();

        const sf::Vector2f half = rect.getSize()*0.5f;
        const sf::Vector2f O  = M.transformPoint({0.f, 0.f});
        const sf::Vector2f X1 = M.transformPoint({1.f, 0.f}) - O;
        const sf::Vector2f Y1 = M.transformPoint({0.f,-1.f}) - O;

        sf::Vector2f move{};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  move -= X1 * (moveSpeed*dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) move += X1 * (moveSpeed*dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    move += Y1 * (moveSpeed*dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  move -= Y1 * (moveSpeed*dt);
        if (move.x!=0.f || move.y!=0.f) {
            sf::Transform T; T.translate(move);
            M = T * M;
        }

        float drot = 0.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) drot -= rotSpeed*dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) drot += rotSpeed*dt;
        if (drot != 0.f) {
            sf::Transform R; R.translate(O); R.rotate(sf::degrees(drot)); R.translate(-O);
            M = R * M;
        }

        bool plus  = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Equal)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Add);
        bool minus = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Hyphen) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract);
        if (plus || minus) {
            float f = plus ? (1.f + uniRate*dt) : std::max(1.f - uniRate*dt, 0.01f);
            sf::Transform S; S.translate(O); S.scale({f,f}); S.translate(-O);
            M = S * M;
        }

        const sf::Vector2f TL = M.transformPoint({-half.x,-half.y});
        const sf::Vector2f TR = M.transformPoint({ half.x,-half.y});
        const sf::Vector2f BR = M.transformPoint({ half.x, half.y});
        const sf::Vector2f BL = M.transformPoint({-half.x, half.y});

        const sf::Vector2f midTop    = (TL+TR)*0.5f;
        const sf::Vector2f midBottom = (BL+BR)*0.5f;
        const sf::Vector2f midLeft   = (TL+BL)*0.5f;
        const sf::Vector2f midRight  = (TR+BR)*0.5f;

        float step = 1.f + dirRate*dt;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            sf::Transform S; S.translate(midBottom); S.scale({1.f, step}); S.translate(-midBottom);
            M = S * M;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            sf::Transform S; S.translate(midTop); S.scale({1.f, step}); S.translate(-midTop);
            M = S * M;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            sf::Transform S; S.translate(midLeft); S.scale({step, 1.f}); S.translate(-midLeft);
            M = S * M;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            sf::Transform S; S.translate(midRight); S.scale({step, 1.f}); S.translate(-midRight);
            M = S * M;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) reset();

        window.clear(sf::Color::White);
        window.draw(rect, sf::RenderStates(M));
        window.display();
    }
    return 0;
}