#pragma once

#include <vector>

typedef std::vector<std::vector<std::vector<double>>> gradient_type;

class Perlin
{
private:
    int m_maxx, m_maxy;
    gradient_type m_gradient;

public:
    Perlin();
    Perlin(int maxx, int maxy);

public:
    void init(int maxx, int maxy);
    void reload();
    double get(double x, double y);

    int get_maxx();
    int get_maxy();

private:
    double lerp(double a0, double a1, double w);
    double dot_grid_gradient(int ix, int iy, double x, double y);
};