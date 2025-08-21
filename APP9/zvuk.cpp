#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>

int main() {
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "APP9 Zvuk");
    window.setFramerateLimit(60);

    sf::SoundBuffer clickBuf;
    clickBuf.loadFromFile("../assets/sounds/pong.wav");
    sf::Sound click(clickBuf);

    sf::Music music;
    bool musicOk = music.openFromFile("../assets/sounds/background_music.flac");

    float volume = 60.f; 
    music.setVolume(volume);
    music.play();
    click.setVolume(volume);
    bool isMusicPlaying = true;
    bool isMusicPaused = false;

    while (window.isOpen()) {
        while (const auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();

            if (const auto* mb = ev->getIf<sf::Event::MouseButtonPressed>()) {
                if (mb->button == sf::Mouse::Button::Left) click.play();
            }

            if (const auto* kp = ev->getIf<sf::Event::KeyPressed>()) {
                using Key = sf::Keyboard::Key;
                switch (kp->code) {
                    case Key::Space: 
                        if (musicOk) {
                            auto st = music.getStatus();
                            if (isMusicPlaying) music.stop();
                            else music.play();
                        }
                        break;

                    case Key::P: 
                        if (musicOk) {
                            auto st = music.getStatus();
                            if (isMusicPaused) music.play();
                            else music.pause();
                        }
                        break;

                    case Key::Add:
                        volume = std::clamp(volume + 5.f, 0.f, 100.f);
                        music.setVolume(volume);
                        click.setVolume(volume);
                        break;

                    case Key::Hyphen: 
                    case Key::Subtract:
                        volume = std::clamp(volume - 5.f, 0.f, 100.f);
                        music.setVolume(volume);
                        click.setVolume(volume);
                        break;

                    default: break;
                }
            }
        }

        window.clear(sf::Color(30,30,35));
        window.display();
    }
}
