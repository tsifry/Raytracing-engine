#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Color.h"
#include "Canvas.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Ligth.h"


int main()
{
    //Propriedades do canvas
    const int WIDTH = 1920;
    const int HEIGHT = 1080;
    const int canvasY = HEIGHT / 2;
    const int canvasX = WIDTH / 2;
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Title");
    
    //Propriedades da viewport e camera
    const Vector3 cameraPosO = {0, 0, 0};
    const float ViewportH = 1;
    const float ViewportW = 1.77777;
    const float ViewportDistance = 0.8; //Fov


    //Criação do Canvas, Camera e Viewport
    Canvas canvas(WIDTH, HEIGHT);
    Camera cam(cameraPosO, ViewportW, ViewportH, WIDTH, HEIGHT, ViewportDistance);


    //TODO - Nao deixar isso aqui hardcoded.
    //Criação de Scena e objetos
    Scene scene(3);
    scene.instantiateObjects();

    //Pra cada pixel do canvas
    for(int y = -canvasY; y < canvasY; y++){
      for(int x = -canvasX; x < canvasX; x++){

        //Descobre a direção da origem até a viewport, na direção do pixel do canvas equivalente
        Vector3 D = cam.CanvasToViewportDir(x, y);
        
        //Descobre a cor traçando o ray
        Color color = cam.TraceRay(cam.posO, D, 1.f, std::numeric_limits<float>::infinity(), scene);
        color = Color::clamp(color);

        //Pinta pixel do canvas
        canvas.PutPixel(x, y, color);

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
