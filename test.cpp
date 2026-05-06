#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Color.h"
#include "Canvas.h"
#include "Vec2.h"


int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 400;
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Title");

    Canvas canvas(WIDTH, HEIGHT);
    Color red(255, 0, 0);
    Color black(0, 0, 0);

    for(unsigned y = 0; y < HEIGHT; y++){
      for(unsigned x = 0; x < WIDTH; x++){

        if(x > 400 && y > 200)
        {
          canvas.PutPixel({x, y}, red);
        }
        else
        {
          canvas.PutPixel({x, y}, black);
        }

      };
    };


    //Cria textura
    sf::Texture texture(sf::Vector2u{WIDTH, HEIGHT});

    //Cria sprite com textura de REFRENCIA.
    sf::Sprite sprite (texture);


    while(window.isOpen()){

        while (std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>()){
                window.close();
            }

        }
        
        //Atualia textura com imagem criada
        texture.update(canvas.pixels);
        window.clear();
        window.draw(sprite);
        window.display();
        
    }
    return 0;
}
