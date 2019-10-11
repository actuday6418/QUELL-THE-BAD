#include <SFML/Graphics.hpp>

using namespace sf;

bool am[500][500];                                              
int main()
{
        for(int i=0;i<500;i++)
                for(int j=0;j<500;j++)
                if(j%2==0)      am[i][j]=true;
    // Create a new 200x200 pixels window with a title
    RenderWindow window(VideoMode(1000, 1000), "RENDER");
    VertexArray line(Points,250000);

    // Main loop, while the window is open
    while (window.isOpen())
    {
        // Event loop
        Event event;
        while (window.pollEvent(event))
        {
            // If close is requested by user, close the window              if (event.type == sf::Event::Closed) window.close();
        }
        int place;
        // Display sequence : clear screen, draw circle and update display
        window.clear(Color::White);
                for(int i=0;i<500;i++)
                for(int j=0;j<500;j++)
                {
                place = i*500+j;
                line[place].position = Vector2f((float)i,(float)j);
                if(am[i][j]==true)
                line[place].color = Color::White;
                else 
                line[place].color = Color::White;
                }
                window.draw(line);
                window.display();
}
return 0;
}
