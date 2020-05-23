#include "../header/image.hpp"

#include <fstream>

Image::Image(int sizex, int sizey, const std::vector<char> &list)
    : m_sizex(sizex),
      m_sizey(sizey),
      m_list(list)
{
}

void Image::save(const std::string &name)
{
    std::ofstream ofs;
    ofs.open(name + ".pgm", std::ofstream::trunc | std::ofstream::binary);

    ofs << "P5\n"
        << m_sizex << " " << m_sizey << "\n"
        << "255\n";

    for (int y = 0; y < m_sizey; y++)
    {
        for (int x = 0; x < m_sizex; x++)
        {
            ofs << m_list[m_sizex * y + x];
        }
    }

    ofs << std::flush;
    ofs.close();
}