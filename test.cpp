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


int main()
{
    //Propriedades do canvas
    const int HEIGHT = 400;
    const int WIDTH = 800;
    const int canvasY = HEIGHT / 2;
    const int canvasX = WIDTH / 2;
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Title");
    
    //Propriedades da viewport e camera
    const Vector3 cameraPosO = {0, 0, 0};
    const float ViewportH = 1;
    const float ViewportW = 2;
    const float ViewportDistance = 0.5; //Fov


    //Criação do Canvas, Camera e Viewport
    Canvas canvas(WIDTH, HEIGHT);
    Camera cam(cameraPosO, ViewportW, ViewportH, WIDTH, HEIGHT, ViewportDistance);

    //Criação de Scena com objetos
    Scene scene(3);
    
    Sphere s1;
    s1.center = Vector3(0, -1, 3);
    s1.radius = 1;
    s1.color = Color(1, 0, 0, 1);
    
    Sphere s2;
    s2.center = Vector3(2, 0, 4);
    s2.radius = 1;
    s2.color = Color(0, 0, 1, 1);
    
    Sphere s3;
    s3.center = Vector3(-2, 0, 4);
    s3.radius = 1;
    s3.color = Color(0, 1, 0, 1);

    scene.AddSphere(s1);
    scene.AddSphere(s2);
    scene.AddSphere(s3);

    //Pra cada pixel do canvas
    for(int y = -canvasY; y < canvasY; y++){
      for(int x = -canvasX; x < canvasX; x++){

        //Descobre a direção da origem até a viewport, na direção do pixel do canvas equivalente
        Vector3 D = cam.CanvasToViewportDir(x, y);
        
        //Descobre a cor traçando o ray
        Color color = cam.TraceRay(cam.posO, D, 1.f, std::numeric_limits<float>::infinity(), scene);

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
