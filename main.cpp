#include <SFML/Graphics.hpp>


class Zaidimas
{
    private:
        sf::RenderWindow window;
        sf::Texture Lenta, figx, figy;
    public:
        void Ekranas();
        void TeksturuNuskaitymas();
};

void Zaidimas::Ekranas()
{
    window.create(sf:: VideoMode(650, 650), "Kryžiukai Nuliukai", sf::Style::Close | sf::Style::Titlebar)
}

void TeksturuNuskaitymas()
{

}

int main()
{
    sf::Texture  drac;
    drac.loadFromFile("dragon.png");
    sf::Sprite drakonas(drac);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(drakonas);
        window.display();
    }
    return 0;
}
