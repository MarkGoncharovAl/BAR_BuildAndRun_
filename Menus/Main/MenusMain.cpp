#include "MenusMain.hpp"
#include "../../Help/Help.hpp"

//!SHOULD BE DELETED
//////////////!

#include "../Menus.hpp"
//////////////!

//sfDATA::MainMenu
////////////////////////////////////////
sfC::Picture_t sfDATA::MainMenu::main_pic_("../Images/menu.png", sf::IntRect(0, 0, sfCON::WindowWidth, sfCON::WindowHeight), sf::Vector2f(0, 0));

sf::IntRect sfDATA::MainMenu::released_(301, 377, 199, 64);
sf::IntRect sfDATA::MainMenu::pressed_(570, 377, 199, 64);
int sfDATA::MainMenu::cur_press_ = 0;

std::array<sfC::Picture_t, sfDATA::MainMenu::count_buttons_> sfDATA::MainMenu::buttons_ = {
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu::pressed_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f)),
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu::released_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 170), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f)),
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu::released_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 340), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f)),
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu::released_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 510), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f)),
    sfC::Picture_t("../Images/buttons2.png", sfDATA::MainMenu::released_, sf::Vector2f(sfCON::WindowWidth / 3, sfCON::WindowHeight / 10 + 680), sf::Color(255, 255, 255), sf::Vector2f(1.2f, 1.2f))};

std::array<sfC::Text_t, sfDATA::MainMenu::count_buttons_> sfDATA::MainMenu::texts_ = {
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 40, sf::Vector2f(sfCON::WindowWidth / 3 + 49, sfCON::WindowHeight / 10 + 13), "PLAY"),
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f(sfCON::WindowWidth / 3 + 46, sfCON::WindowHeight / 10 + 196), "Restart"),
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f(sfCON::WindowWidth / 3 + 23, sfCON::WindowHeight / 10 + 368), "Downaload"),
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f(sfCON::WindowWidth / 3 + 56, sfCON::WindowHeight / 10 + 536), "Create"),
    sfC::Text_t("../Fonts/baltimore-nouveau.ttf", 22, sf::Vector2f(sfCON::WindowWidth / 3 + 83, sfCON::WindowHeight / 10 + 707), "Exit")};
////////////////////////////////////////

bool sfDATA::MainMenu::AnalyseMenu(sf::RenderWindow &window)
{
    //CHANGE STATIC
    //  sfDATA::MainMenu::buttons
    //  sfDATA::MainMenu::cur_press

    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            return false;

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                return false;

            case sf::Keyboard::Enter:
                if (!ActionPress(window, cur_press_))
                    return false;
                break;

            case sf::Keyboard::Up:
                if (cur_press_ > 0)
                {
                    buttons_[cur_press_].set_texture(released_);
                    cur_press_--;
                    buttons_[cur_press_].set_texture(pressed_);
                }
                break;

            case sf::Keyboard::Down:
                if (cur_press_ < count_buttons_ - 1)
                {
                    buttons_[cur_press_].set_texture(released_);
                    cur_press_++;
                    buttons_[cur_press_].set_texture(pressed_);
                }
                break;

            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f cur_coord(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));

            for (int i = 0; i < count_buttons_; ++i)
            {
                if (buttons_[i].get_glob_bounds().contains(cur_coord))
                {
                    buttons_[cur_press_].set_texture(released_);
                    cur_press_ = i;
                    buttons_[cur_press_].set_texture(pressed_);
                    break;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left &&
                buttons_[cur_press_].get_glob_bounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
            {
                if (!ActionPress(window, cur_press_))
                    return false;
            }
        }
    }

    return true;
}

bool sfDATA::MainMenu::ActionPress(sf::RenderWindow &window, int press)
{
    switch (press)
    {
    case type_button_::GAME:
        MenuCars::CheckMenuCars(window);
        return false;

    case type_button_::RESTART:
        MainMenu::Full_Restart();
        ShowDoneAction(window, "Restarted");
        return true;

    case type_button_::SET:
        SetMap(window);
        return true;

    case type_button_::CREATE:
        CreateMap(window);
        return true;

    case type_button_::EXIT:
        return false;

    default:
        WARNING("Existing not done action!\n");
    }
    return false;
}

bool sfDATA::MainMenu::ChechMainMenu(sf::RenderWindow &window)
{
    sf::View main_view(sf::FloatRect(0.f, 0.f, sfCON::WindowWidth, sfCON::WindowHeight));
    while (window.isOpen())
    {
        if (!AnalyseMenu(window))
            return false;

        window.clear();
        window.draw(main_pic_.for_draw());

        for (const auto &button : buttons_)
            window.draw(button.for_draw());

        for (const auto &text : texts_)
            window.draw(text.for_draw());

        window.setView(main_view);
        window.display();
    }

    return false;
}

void sfDATA::MainMenu::prepare_data_main_menu()
{
    for (auto &text : texts_)
        text.set_color(sf::Color::Blue);
}

void sfDATA::MainMenu::Full_Restart()
{
    sfDATA::MenuCars::Restart();
    sfDATA::Full_Restart();
}