#include "Menus.hpp"
#include "../Help/Data/Data.hpp"
#include "../Common_libs/Errors/Errors.hpp"

//!Should be replaced
#include "Main/MenusMain.hpp"

bool AnalyseWait_Text_User(sf::RenderWindow &window, std::string &text, sfC::Text_t &user_text)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::KeyPressed)
        {

            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                text.clear();
                return false;
                break;
            case sf::Keyboard::Enter:
                return false;
                break;
            case sf::Keyboard::BackSpace:
            case sf::Keyboard::Delete:
                text.pop_back();
                user_text.pop_back();
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::TextEntered)
        {

            if (sfF::IS_ASKII(event.text.unicode))
            {

                char cur_symbol = static_cast<char>(event.text.unicode);
                text.push_back(cur_symbol);
                user_text.push_back(cur_symbol);
            }
        }
    }
    return true;
}
std::string Wait_Text_User(sf::RenderWindow &window)
{
    using cur_data = data::text;

    std::string text;
    sfC::Text_t user_text("../Fonts/19413.ttf", 100, sf::Vector2f(sfCON::WindowWidth * 0.3f, sfCON::WindowHeight * 0.5f), "");
    user_text.set_color(sf::Color::Cyan);

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalyseWait_Text_User(window, text, user_text))
            break;

        window.clear(sf::Color::White);
        window.draw(cur_data::background.for_draw());
        window.draw(cur_data::main_text.for_draw());
        window.draw(cur_data::addition_text.for_draw());
        window.draw(user_text.for_draw());
        window.display();
    }

    return text;
}

bool AnalyseSetMap(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::KeyPressed)
        {

            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                ShowDoneAction(window, "Not selected");
                return false;
                break;
            case sf::Keyboard::Enter:
                if (!data::main_game::read_map(data::set_map::cur_text.get_text()))
                {
                    ShowDoneAction(window, "Not selected!");
                    return true;
                }
                else
                {
                    ShowDoneAction(window, data::set_map::cur_text.get_text(), "selected");
                    return false;
                }
                break;
            case sf::Keyboard::Right:
                if (data::set_map::cur_map + 1 < data::map_prototypes::maps.size())
                {
                    data::set_map::cur_map += 1;
                    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));
                }
                break;
            case sf::Keyboard::Left:
                if (data::set_map::cur_map > 0)
                {
                    data::set_map::cur_map--;
                    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));
                }
                break;
            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left &&
                data::set_map::direct_back.is_include(event.mouseButton.x, event.mouseButton.y))
            {

                ShowDoneAction(window, "Not selected");
                return false;
            }
        }
    }
    return true;
}
bool SetMap(sf::RenderWindow &window)
{
    using cur_data = data::text;

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalyseSetMap(window))
        {
            break;
        }

        window.clear();
        window.draw(cur_data::background.for_draw());
        window.draw(data::set_map::main_text.for_draw());
        window.draw(data::set_map::cur_text.for_draw());
        window.draw(data::set_map::direct_back.for_draw());
        window.display();
    }

    return false;
}

bool AnalysePrepareCreateMap(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::KeyPressed)
        {

            switch (event.key.code)
            {
            case sf::Keyboard::Enter:
                ShowDoneAction(window, data::set_map::cur_text.get_text(), "selected");
                return false;
                break;
            case sf::Keyboard::Right:
                if (data::set_map::cur_map + 1 < data::map_prototypes::maps.size())
                {
                    data::set_map::cur_map += 1;
                    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));
                }
                break;
            case sf::Keyboard::Left:
                if (data::set_map::cur_map > 0)
                {
                    data::set_map::cur_map--;
                    data::set_map::cur_text.set_text(data::map_prototypes::maps.at(data::set_map::cur_map));
                }
                break;
            default:
                break;
            }
        }
    }
    return true;
}
void PrepareCreateMap(sf::RenderWindow &window, sfC::Map &map)
{
    using cur_data = data::text;

    window.setView(cur_data::view);

    while (window.isOpen())
    {

        if (!AnalysePrepareCreateMap(window))
        {
            break;
        }

        window.clear();
        window.draw(cur_data::background.for_draw());
        window.draw(data::set_map::main_text.for_draw());
        window.draw(data::set_map::cur_text.for_draw());
        window.display();
    }

    data::main_game::read_map(data::set_map::cur_text.get_text(), map);
}

bool AnalyseCreateMap(sf::RenderWindow &window)
{
    using cur_data = data::create_map;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            return false;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {

                sf::Vector2f coords(event.mouseButton.x + sfF::get_view_position_x(cur_data::view),
                                    event.mouseButton.y + sfF::get_view_position_y(cur_data::view));

                if ((coords.x > sfCON::SIZE_BLOCK && coords.x < cur_data::map.GetSize().x - sfCON::SIZE_BLOCK) &&
                    (coords.y > sfCON::SIZE_BLOCK && coords.y < cur_data::map.GetSize().y - sfCON::SIZE_BLOCK))
                {
                    cur_data::update_block(
                        cur_data::map.AbsCoords(coords), cur_data::cur_block);
                }

                cur_data::keys[cur_data::data_for_keys::Button_Left] = true;
            }
        }
        if (event.type == sf::Event::MouseMoved)
        {
            if (cur_data::keys[cur_data::data_for_keys::Button_Left])
            {

                sf::Vector2f coords(event.mouseMove.x + sfF::get_view_position_x(cur_data::view),
                                    event.mouseMove.y + sfF::get_view_position_y(cur_data::view));

                if ((coords.x > sfCON::SIZE_BLOCK && coords.x < cur_data::map.GetSize().x - sfCON::SIZE_BLOCK) &&
                    (coords.y > sfCON::SIZE_BLOCK && coords.y < cur_data::map.GetSize().y - sfCON::SIZE_BLOCK))
                {
                    cur_data::update_block(
                        cur_data::map.AbsCoords(coords), cur_data::cur_block);
                }
            }

            cur_data::update_mouse(event.mouseMove.x, event.mouseMove.y);
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                cur_data::keys[cur_data::data_for_keys::Button_Left] = false;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::LControl:
                cur_data::keys[cur_data::data_for_keys::Ctrl] = true;
                break;
            case sf::Keyboard::Z:
                cur_data::keys[cur_data::data_for_keys::Z] = true;
                if (cur_data::keys[cur_data::data_for_keys::Ctrl] == true)
                    cur_data::cancel_last_update();
                break;
            case sf::Keyboard::S:
                cur_data::keys[cur_data::data_for_keys::S] = true;
                if (cur_data::keys[cur_data::data_for_keys::Ctrl] == true)
                {
                    std::string new_name = Wait_Text_User(window);

                    if (!new_name.empty())
                    {
                        ShowDoneAction(window, new_name, "created");
                        data::map_prototypes::insert_map(new_name, cur_data::map.get_map_prototype());
                    }
                    else
                    {
                        ShowDoneAction(window, "Not created!");
                    }
                }
                break;
            case sf::Keyboard::Num1:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Field;
                break;
            case sf::Keyboard::Num2:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Wall;
                break;
            case sf::Keyboard::Num3:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Target;
                break;
            case sf::Keyboard::Num4:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Sand;
                break;
            case sf::Keyboard::Num5:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Acceleration;
                break;
            case sf::Keyboard::Num6:
                cur_data::cur_block = sfC::BlockPrototype::TypeBlock::Restart;
                break;
            case sf::Keyboard::Escape:
                ShowDoneAction(window, "Not created");
                return false;
                break;
            default:
                break;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::LControl:
                cur_data::keys[cur_data::data_for_keys::Ctrl] = false;
                break;
            case sf::Keyboard::Z:
                cur_data::keys[cur_data::data_for_keys::Z] = false;
                break;
            case sf::Keyboard::S:
                cur_data::keys[cur_data::data_for_keys::S] = false;
                break;
            default:
                break;
            }
        }
    }

    cur_data::move_view();
    return true;
}
bool CreateMap(sf::RenderWindow &window)
{
    using cur_data = data::create_map;
    PrepareCreateMap(window, cur_data::map);

    while (window.isOpen())
    {
        if (!AnalyseCreateMap(window))
            break;

        window.clear();

        window.setView(cur_data::view);
        window.draw(cur_data::map);

        cur_data::info_user.set_position(
            sfF::get_view_position_x(cur_data::view),
            765.f + sfF::get_view_position_y(cur_data::view));
        window.draw(cur_data::info_user.for_draw());
        window.display();
    }

    return false;
}