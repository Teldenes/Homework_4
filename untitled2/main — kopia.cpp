#include <iostream>
#include <vector>

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

    void animate(const sf::Time &elapsed)
     {
      move(m_speed_x*elapsed.asSeconds(), m_speed_y*elapsed.asSeconds());
      rotate(m_speed_r*elapsed.asSeconds());
     }

    void setBounds(int left, int right, int top, int bottom)
     {
      bound_top = top;
      bound_bottom = bottom;
      bound_right = right;
      bound_left = left;
     }

    void bouncce()
     {
      sf::FloatRect rectangle_bounds = getGlobalBounds();

      if(rectangle_bounds.top <= bound_top)
       {
        m_speed_y = abs(m_speed_y);
        setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

      if(rectangle_bounds.left <= bound_left)
       {
        m_speed_x = abs(m_speed_x);
        setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

      if(rectangle_bounds.top + rectangle_bounds.height >= bound_bottom)
       {
        m_speed_y = abs(m_speed_y)*-1;
        setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
       }

      if(rectangle_bounds.left + rectangle_bounds.width >= bound_right)
       {
        m_speed_x = abs(m_speed_x)*-1;
        setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
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
 };

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // create some shapes
    sf::CircleShape circle(50.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    CustomRectangleShape rectangle1 (sf::Vector2f(120.0, 60.0), sf::Vector2f(220.0, 160.0));
    rectangle1.setFillColor(sf::Color(100, 150, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(2);
    triangle.setPosition(600.0, 100.0);
    sf::Clock clock;

    int rectangle_velocity_x = 5;
    int rectangle_velocity_y = 15;
    int rectangle_angular_velocity = 10;

    bool flag_y = false;
    bool flag_x = false;

    rectangle1.setBounds(0, window.getSize().x, 0, window.getSize().y);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        rectangle.move(rectangle_velocity_x*dt,rectangle_velocity_y*dt);
        rectangle.rotate(rectangle_angular_velocity*dt);

        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();
        std::cout << rectangle_bounds.top << " " << rectangle_bounds.left << " " ;
        std::cout << rectangle_bounds.width << " " << rectangle_bounds.height << std::endl;

        if(rectangle_bounds.top<=0 || rectangle_bounds.top+rectangle_bounds.height>=window.getSize().y)
            {
                if(flag_y != true)
                {
                    rectangle_velocity_y *= -1;
                    rectangle.setFillColor(sf::Color(rand() % 256,
                                                     rand() % 256,
                                                     rand() % 256));
                }
                flag_y = true;
            }
            else
                flag_y = false;



            if(rectangle_bounds.left<=0 || rectangle_bounds.left+rectangle_bounds.width>=window.getSize().x)
            {
                if(flag_x!=true)
                {
                    rectangle_velocity_x *= -1;
                    rectangle.setFillColor(sf::Color(rand() % 256,
                                                     rand() % 256,
                                                     rand() % 256));
                }
                flag_x = true;
            }
            else
                flag_x = false;


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                std::cout << "Holding up button" << std::endl;
            }

            if(sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                std::cout << "Holding middle mouse button" << std::endl;
            }


        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(rectangle);
        window.draw(rectangle1);
        window.draw(triangle);

        elapsed = clock.restart();

        rectangle1.animate(elapsed);
        rectangle1.bouncce();

        // end the current frame
        window.display();
    }

    return 0;
}
