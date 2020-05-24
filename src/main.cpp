#define OLC_PGE_APPLICATION
#include "header/olcPixelGameEngine.h"

#include "header/perlin.hpp"
#include "header/image.hpp"

class Application : public olc::PixelGameEngine
{
private:
    Perlin m_perlin;
    std::vector<char> m_noise;
    int nx = 10, ny = 10;
    int n_saved = 0;

public:
    Application()
    {
        sAppName = "Perlin noise";
    }

public:
    bool OnUserCreate() override
    {
        draw_noise();
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        if (GetKey(olc::Key::UP).bHeld)
        {
            nx++;
            ny++;
            draw_noise();
        }

        if (GetKey(olc::Key::DOWN).bHeld && nx > 2 && ny > 2)
        {
            nx--;
            ny--;
            draw_noise();
        }

        if (GetKey(olc::Key::R).bHeld)
        {
            draw_noise();
        }

        if (GetKey(olc::Key::S).bPressed)
        {
            save();
        }

        return true;
    }

    void draw_noise()
    {
        m_perlin.init(nx, ny);
        m_noise.clear();
        m_noise.reserve(nx * ny);
        double scalex = (double)nx / (double)ScreenWidth();
        double scaley = (double)ny / (double)ScreenHeight();

        for (int x = 0; x < ScreenWidth(); x++)
        {
            for (int y = 0; y < ScreenHeight(); y++)
            {
                u_int8_t v = (m_perlin.get((double)x * scalex, (double)y * scaley) + 1.) * (256. / 2.);
                m_noise.push_back(v);
                Draw(x, y, olc::Pixel(v, v, v));
            }
        }
    }

    void save()
    {
        Image img(ScreenWidth(), ScreenHeight(), m_noise);
        std::stringstream name;
        name << "noise_" << n_saved << "_n" << nx;
        img.save(name.str());
        n_saved++;
    }
};

int main()
{
    Application application;
    if (application.Construct(1000, 1000, 1, 1))
        application.Start();
    return 0;
}