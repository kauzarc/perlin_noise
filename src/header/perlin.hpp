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

public:
    void init(int maxx, int maxy);
    double get(double x, double y);

private:
    double lerp(double a0, double a1, double w);
    double dot_grid_gradient(int ix, int iy, double x, double y);
};