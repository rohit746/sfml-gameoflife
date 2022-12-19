#include <SFML/Graphics.hpp>

class Cell {
public:
    Cell(int i, int j, int w);
    ~Cell();
    bool isAlive() const;
    void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f pos);
    void born();
    void kill();
    void update(sf::RenderWindow& window, sf::Clock &clockActivating, sf::Time &elapsedActivated);
    int getX() const;
    int getY() const;
private:
    bool alive;
    sf::RectangleShape shape;
    int x, y;
    int cellSize;
};