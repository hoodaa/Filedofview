#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#define PI 3.14
#define RAD PI/180

ConvexShape Player(Vector2f center, float radius, float startpoint, int rotatecon) {

    float angle = startpoint;
    float pointscount =  40 - startpoint;
    float DeltaAngle = (pointscount - angle) / 30;

    float theta = 0;
    float offset = 90 * RAD;

    ConvexShape circle;
    circle.setPointCount(41);
    for (float i = 0; i < 40; i++)
    {
        Vector2f point;
        theta = angle * RAD;
        offset = 90 * RAD;
        point.x = center.x + radius * cos(theta + rotatecon * offset);
        point.y = center.y + radius * sin(theta + rotatecon * offset);
        angle += DeltaAngle;
        circle.setPoint(i, point);
    }
    return circle;
}

int main() {
    CircleShape circle(30);
    circle.setFillColor(Color::Red);
    circle.setOrigin(-400, -400);
    Vector2f playerPos;



    RectangleShape Enemy;
    Enemy.setSize(Vector2f(30.f, 30.f));
    Enemy.setFillColor(Color::Green);
    Enemy.setOrigin(-200, -50);
    Vector2f startposition = (Vector2f(200.f, 20.f));
    Vector2f Enemyposition = startposition;
    float amp = (1400 - 100) / 2;
    float freq = 1;

    Clock clock;
    float t;

    RenderWindow window(VideoMode(800, 800), "Detection", Style::Default);

    int rotateCon = 0;
    ConvexShape shape;
    shape = Player(Vector2f(0, 0), 300, 30, rotateCon);
  
    
 
    while (window.isOpen()) {
        Event event;
      
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();

            }
            if (event.key.code == Keyboard::Right)
            {
                rotateCon = 0;       
            }
            if (event.key.code == Keyboard::Left)
            {
                rotateCon = 2;         
            } if (event.key.code == Keyboard::Down)
            {
                rotateCon = 1;
            } if (event.key.code == Keyboard::Up)
            {
                rotateCon = 3;
            }
            if (event.key.code == Keyboard::D)
            {
                playerPos.x += 10;

            }
            if (event.key.code == Keyboard::A)
            {
                playerPos.x -= 10;
            } if (event.key.code == Keyboard::S)
            {
                playerPos.y += 10;
            } if (event.key.code == Keyboard::W)
            {
                playerPos.y -= 10;
            }
          
        }

        t = clock.getElapsedTime().asSeconds();
        Enemyposition.x = startposition.x + amp * sin(freq * t) * cos(freq * t);
        if (shape.getGlobalBounds().intersects(Enemy.getGlobalBounds())) {
            cout << "TA DAAA" << endl;
            shape = Player(Vector2f(0, 0), 300, 30, rotateCon);
            shape.setOrigin(-425, -425);
            shape.setFillColor(Color::Red);
        }
        else if (!shape.getGlobalBounds().intersects(Enemy.getGlobalBounds()))
        {
            shape = Player(Vector2f(0, 0), 300, 30, rotateCon);
            shape.setOrigin(-425, -425);
            cout << "Color back" << endl;
            shape.setFillColor(Color::Yellow);
        }
    
        circle.setPosition(playerPos);
        shape.setPosition(playerPos);
        Enemy.setPosition(Enemyposition);
        window.clear();
        window.draw(shape);
        window.draw(circle);
        window.draw(Enemy);
    
        window.display();


    }
}

