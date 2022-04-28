#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CustomRectangleShape : public sf::RectangleShape
 {
  public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size)
     {
      setPosition(position);
     }

    void setSpeed(int xspeed, int yspeed, int rspeed)
     {
      m_speed_x = xspeed;
      m_speed_y = yspeed;
      m_speed_r = rspeed;
     }

//    sf::FloatRect rectangle_bounds = getGlobalBounds();


    void setBounds(int left, int right, int top, int bottom)
     {
      bound_top = top;
      bound_bottom = bottom;
      bound_right = right;
      bound_left = left;
     }

    bool isHover(sf::Vector2i &mouse_position) const
     {
      sf::FloatRect rectangle_bounds = getGlobalBounds();

      if((mouse_position.x > rectangle_bounds.left) && (mouse_position.x < (rectangle_bounds.left + rectangle_bounds.width))
      && (mouse_position.y > rectangle_bounds.top) && (mouse_position.y < (rectangle_bounds.top + rectangle_bounds.height)))
       {return true;}
      else
      {return false;}
     }

    void select()
     {
      selected = 1;
      setFillColor(sf::Color(255, 0, 0));
     }

    void deselect()
     {
      selected = 0;
      setFillColor(sf::Color(0, 255, 0));
     }

    bool selected_()
     {
      if(selected == 1)
      {return true;}
      else
      {return false;}
     }

    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key)
     {
      sf::FloatRect rectangle_bounds = getGlobalBounds();

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rectangle_bounds.top > bound_top)
       {
        move(0, -m_speed_y*elapsed.asSeconds());
       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rectangle_bounds.top+rectangle_bounds.height < bound_bottom)
       {
        move(0, m_speed_y*elapsed.asSeconds());
       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && rectangle_bounds.left + rectangle_bounds.width < bound_right)
       {
        move(m_speed_x*elapsed.asSeconds(), 0);
       }

      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && rectangle_bounds.left > bound_left)
       {
        move(-m_speed_x*elapsed.asSeconds(), 0);
       }
     }


  private:
     int m_speed_x = 4185;
     int m_speed_y = 5271;
     int m_speed_r = 121;
     int bound_top = 0;
     int bound_bottom = 0;
     int bound_left = 0;
     int bound_right = 0;
     bool selected = 0;
 };

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    std::srand(std::time(nullptr));
    sf::Clock clock;

    std::vector<CustomRectangleShape> rectangles;

    for(int i=0; i<10; i++)
    {
        sf::Vector2f size(120.0, 60.0);
        sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
        rectangles.emplace_back(CustomRectangleShape(size, position));
    }

    for(auto &rec : rectangles)
    {
        rec.setFillColor(sf::Color(0, 255, 0));
        rec.setBounds(0, window.getSize().x, 0, window.getSize().y);
        rec.setSpeed(100, 200, 10);
    }

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Vector2i m_position = sf::Mouse::getPosition(window);

            for(auto &rec : rectangles)
            {
             if(event.type == sf::Event::MouseButtonPressed && rec.isHover(m_position) == true && event.mouseButton.button == sf::Mouse::Left)
              {
                 for(auto &rec : rectangles)
                  {
                   rec.deselect();
                  }
                 rec.select();
              }
            }
        }

        window.clear(sf::Color::Black);

        for(auto &rec : rectangles)
        {
            window.draw(rec);
        }

        for(auto &rec : rectangles)
        {
         if(rec.selected_()==1)
          {
           rec.moveInDirection(elapsed, event.key.code);
          }
        }

        window.display();
    }
  return 0;
}

