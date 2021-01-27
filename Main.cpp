#include "Actions/Actions.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Fullscreen);
    prepare_data();

    while (window.isOpen())
    {
        if (!MainMenu(window))
        {
            window.close();
            break;
        }
    }

    return 0;
}
