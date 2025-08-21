#include <SFML/Graphics.hpp>
#include <random>

namespace rnd {
    static std::mt19937& rng() { static std::mt19937 g{std::random_device{}()}; return g; }
    static float f(float a, float b) { std::uniform_real_distribution<float> d(a,b); return d(rng()); }
}

static sf::Vector2f randomInside(const sf::RenderWindow& w, const sf::Vector2f& size) {
    const float maxX = static_cast<float>(w.getSize().x) - size.x;
    const float maxY = static_cast<float>(w.getSize().y) - size.y;
    return { rnd::f(0.f, std::max(0.f, maxX)), rnd::f(0.f, std::max(0.f, maxY)) };
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "kolize");
    window.setFramerateLimit(60);

    sf::RectangleShape player({80.f, 80.f});
    player.setFillColor(sf::Color::Black);
    player.setPosition(sf::Vector2f{360.f, 260.f});
    const float speed = 260.f;

    sf::RectangleShape box({120.f, 80.f});
    box.setFillColor(sf::Color(220, 60, 60));
    sf::CircleShape circle(45.f);
    circle.setFillColor(sf::Color(60, 120, 220));

    sf::ConvexShape tri(3);
    tri.setPoint(0, {0.f, 80.f});
    tri.setPoint(1, {60.f, 0.f});
    tri.setPoint(2, {120.f, 80.f});
    tri.setFillColor(sf::Color(60, 180, 110));

    auto randomizeObjects = [&](){
        box.setPosition(randomInside(window, box.getSize()));
        circle.setPosition(randomInside(window, {circle.getRadius()*2.f, circle.getRadius()*2.f}));
        tri.setPosition(randomInside(window, {120.f, 80.f}));
    };
    randomizeObjects();

    sf::Clock clock;
    while (window.isOpen()) {
        while (auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();
            else if (ev->is<sf::Event::KeyPressed>()) {
                const auto* kp = ev->getIf<sf::Event::KeyPressed>();
                if (kp && kp->scancode == sf::Keyboard::Scancode::Enter) {
                    randomizeObjects();
                }
            }
        }

        float dt = clock.restart().asSeconds();
        sf::Vector2f d{0.f, 0.f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  d.x -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) d.x += speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    d.y -= speed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  d.y += speed * dt;
        player.move(d);
        const auto p = player.getGlobalBounds();

        const auto iBox    = p.findIntersection(box.getGlobalBounds());
        const auto iCircle = p.findIntersection(circle.getGlobalBounds());
        const auto iTri    = p.findIntersection(tri.getGlobalBounds());

        const bool hitBox    = iBox.has_value();
        const bool hitCircle = iCircle.has_value();
        const bool hitTri    = iTri.has_value();

        auto colorize = [](sf::Shape& s, bool hit, sf::Color base){
            s.setFillColor(hit ? sf::Color::Yellow : base);
        };
        colorize(box,    hitBox,    sf::Color(220, 60, 60));
        colorize(circle, hitCircle, sf::Color(60, 120, 220));
        colorize(tri,    hitTri,    sf::Color(60, 180, 110));

        window.clear(sf::Color::White);
        window.draw(box);
        window.draw(circle);
        window.draw(tri);
        window.draw(player);
        window.display();
    }
    return 0;
}
