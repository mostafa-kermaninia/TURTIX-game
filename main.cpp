#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
   // Window
   RenderWindow window(VideoMode(640, 480), "TURTIX", Style::Titlebar | Style::Close);
   Event ev;

   // Game loop
   while (window.isOpen())
   {
      // Event handling
      while (window.pollEvent(ev))
      {
         switch (ev.type)
         {
         case Event::Closed:
            window.close();
            break;

         case Event::KeyPressed:
            if (ev.key.code == Keyboard::Escape)
               window.close();
            break;
            ;
         }
      }

      // Update

      // Render
      window.clear(Color(0,0,0));
      // Draw your game
      window.display();
   }

   return 0;
}