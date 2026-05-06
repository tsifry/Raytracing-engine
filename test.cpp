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
    const int canvasY = HEIGHT / 2;
    const int canvasX = WIDTH / 2;


    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Title");

    Canvas canvas(WIDTH, HEIGHT);
    Color black(0, 0, 0);
    Color red(1, 0, 0);

    for(int y = -canvasY; y < canvasY; y++){
      for(int x = -canvasX; x < canvasX; x++){

        float u = (x + canvasX) / float(WIDTH);
        float v= (y + canvasY) / float(HEIGHT);

        Color gradientColor(v, 0, u);

        canvas.PutPixel({x, y}, gradientColor);

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
