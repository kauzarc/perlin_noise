#define OLC_PGE_APPLICATION
#include "header/olcPixelGameEngine.h"

#include "header/perlin.hpp"

class Application : public olc::PixelGameEngine
{
private:
    Perlin m_perlin;
    int nx = 10, ny = 10;

public:
    Application()
    {
        sAppName = "Perlin noise";
    }

public:
    bool OnUserCreate() override
    {
        m_perlin.init(nx + 1, ny + 1);
        double scalex = (double)nx / ScreenWidth();
        double scaley = (double)ny / ScreenHeight();

        for (int x = 0; x < ScreenWidth(); x++)
        {
            for (int y = 0; y < ScreenHeight(); y++)
            {
                double v = (m_perlin.get((double)x * scalex, (double)y * scaley) + 1.) * (256. / 2.);

                Draw(x, y, olc::Pixel(v, v, v));
            }
        }
        return true;
    }

    bool
    OnUserUpdate(float fElapsedTime) override
    {

        return true;
    }
};

int main()
{
    Application application;
    if (application.Construct(1000, 1000, 1, 1))
        application.Start();
    return 0;
}