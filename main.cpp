#include <SFML/Graphics.hpp>

struct Langelis
{
    sf::IntRect k;
    int tipas;
};

class Zaidimas
{
private:
    sf::RenderWindow window;
    sf::Texture Lenta, figx, figo;
    sf::Sprite PLenta, Pfigx, Pfigo, P[9];
    sf::Event ivykis;
    sf::Font sriftas;
    sf::Text zinute;
    Langelis L[9];
public:
    void Ekranas();
    bool TeksturuNuskaitymas();
    bool SriftoNuskaitymas();
    void Dalys();
    void LangeliuNustatymas();
    void LangelioKord(Langelis &lang, int x1, int y1, int x2, int y2);
    void PrTekstas();
    bool Ejimas(int ejnr);
    bool PriklausoLang(sf::Vector2i poz, int lnr);
    void KeistiTeksta(int ejnr, bool uzimtas);
    bool ArBaiges();
    void Eiga();
};

void Zaidimas::Ekranas()
{
    window.create(sf:: VideoMode(618, 700), "Kryziukai Nuliukai", sf::Style::Close | sf::Style::Titlebar);
}

bool Zaidimas::TeksturuNuskaitymas()
{
    return Lenta.loadFromFile("images/lenta.png") && figx.loadFromFile("images/figxp.png") && figo.loadFromFile("images/figop.png");
}

bool Zaidimas::SriftoNuskaitymas()
{
    return sriftas.loadFromFile("sriftai/arial.ttf");
}

void Zaidimas::LangeliuNustatymas()
{
    LangelioKord(L[0], 0, 82, 198, 198);
    LangelioKord(L[1], 214, 82, 198, 198);
    LangelioKord(L[2], 420, 82, 198, 198);
    LangelioKord(L[3], 0, 286, 198, 198);
    LangelioKord(L[4], 214, 286, 198, 198);
    LangelioKord(L[5], 420, 286, 198, 198);
    LangelioKord(L[6], 0, 504, 198, 198);
    LangelioKord(L[7], 214, 504, 198, 198);
    LangelioKord(L[8], 420, 504, 198, 198);
}

void Zaidimas::LangelioKord(Langelis &lang, int x1, int y1, int x2, int y2)
{
    lang.k.left = x1;
    lang.k.top = y1;
    lang.k.width = x2;
    lang.k.height = y2;
    lang.tipas = 0;
}

void Zaidimas::Dalys()
{
    PLenta.setTexture(Lenta);
    Pfigx.setTexture(figx);
    Pfigo.setTexture(figo);
}

void Zaidimas::PrTekstas()
{
    zinute.setString("1-o Zaidejo eile");
    zinute.setFont(sriftas);
    zinute.setCharacterSize(30);
    zinute.setFillColor(sf::Color::Black);
    zinute.move(309 - zinute.getLocalBounds().width/2, 30);
}

bool Zaidimas::PriklausoLang(sf::Vector2i poz, int lnr)
{
    return L[lnr].k.contains(poz.x, poz.y);
}

void Zaidimas::KeistiTeksta(int ejnr, bool uzimtas)
{
    std::string zaid;
    if(uzimtas)
    {
        zinute.setString("Sis langelis yra uzimtas, bandykite kita");
        zinute.setPosition(0, 0);
        zinute.move(309 - zinute.getLocalBounds().width/2, 30);
    }
    else
    {
        zaid = (ejnr % 2 == 1) ? "1-o Zaidejo eile" : "2-o Zaidejo eile";
        zinute.setString(zaid);
        zinute.setPosition(0, 0);
        zinute.move(309 - zinute.getLocalBounds().width/2, 30);
    }

}

bool Zaidimas::Ejimas(int ejnr)
{
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    for(int i = 0; i < 9; i++)
    {
        if(PriklausoLang(pos, i))
        {
            if(L[i].tipas == 0)
            {
                P[ejnr] = (ejnr%2) ? Pfigo : Pfigx;
                P[ejnr].setPosition(L[i].k.left, L[i].k.top);
                L[i].tipas = (ejnr%2 == 0) ? 1 : 2;
                KeistiTeksta(ejnr, false);
                return true;
            }
            else
            {
                KeistiTeksta(ejnr, true);
                return false;
            }
        }
    }
}

bool Zaidimas::ArBaiges()
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {

        }
    }
}

void Zaidimas::Eiga()
{
    int ejnr = 0;
    PrTekstas();
    LangeliuNustatymas();
    while(window.isOpen())
    {
        while(window.pollEvent(ivykis))
        {
            if(ivykis.type == sf::Event::Closed)
                window.close();
            if(ivykis.type == sf::Event::MouseButtonReleased && ejnr < 9)
            {
                if(Ejimas(ejnr))
                {
                    ejnr++;
                }
            }
        }
        window.clear(sf::Color::White);
        PLenta.setPosition(0, 82);
        window.draw(PLenta);
        window.draw(zinute);
        for(int i = 0; i < 9; i++)
            window.draw(P[i]);
        window.display();
    }
}

int main()
{
    Zaidimas Z;
    Z.Ekranas();
    if(!Z.TeksturuNuskaitymas())
        return EXIT_FAILURE;
    if(!Z.SriftoNuskaitymas())
        return EXIT_FAILURE;
    Z.Dalys();
    Z.Eiga();
    return EXIT_SUCCESS;
}
