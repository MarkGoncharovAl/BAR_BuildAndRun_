#include "Actions/Actions.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML works!", sf::Style::Default);
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
