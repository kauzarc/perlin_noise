#include "../header/perlin.hpp"

Perlin::Perlin()
    : m_dis(0., 1.)
{
}

Perlin::Perlin(int maxx, int maxy)
    : Perlin()
{
    init(maxx, maxy);
}

void Perlin::init(int maxx, int maxy)
{
    m_maxx = maxx;
    m_maxy = maxy;

    maxx++;
    maxy++;

    m_gradient.clear();

    m_gradient.reserve(maxx);
    for (int x = 0; x < maxx; x++)
    {
        m_gradient.emplace_back();
        m_gradient[x].reserve(maxy);
        for (int y = 0; y < maxy; y++)
        {
            m_gradient[x].emplace_back();
            m_gradient[x][y].push_back(m_dis(m_re));
            m_gradient[x][y].push_back(m_dis(m_re));
        }
    }
}

void Perlin::reload()
{
    init(m_maxy, m_maxy);
}

double Perlin::get(double x, double y)
{
    int x0 = floor(x);
    int x1 = x0 + 1;
    int y0 = floor(y);
    int y1 = y0 + 1;

    double sx = x - (double)x0;
    double sy = y - (double)y0;

    double n0, n1, ix0, ix1, value;
    n0 = dot_grid_gradient(x0, y0, x, y);
    n1 = dot_grid_gradient(x1, y0, x, y);
    ix0 = lerp(n0, n1, sx);
    n0 = dot_grid_gradient(x0, y1, x, y);
    n1 = dot_grid_gradient(x1, y1, x, y);
    ix1 = lerp(n0, n1, sx);
    value = lerp(ix0, ix1, sy);

    return value;
}

int Perlin::get_maxx()
{
    return m_maxx;
}

int Perlin::get_maxy()
{
    return m_maxy;
}

double Perlin::lerp(double a0, double a1, double w)
{
    return (1.0 - w) * a0 + w * a1;
}

double Perlin::dot_grid_gradient(int ix, int iy, double x, double y)
{
    double dx = x - (double)ix;
    double dy = y - (double)iy;

    return (dx * m_gradient[ix][iy][0] + dy * m_gradient[ix][iy][1]);
}