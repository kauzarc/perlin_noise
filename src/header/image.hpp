#pragma once

#include <string>
#include <vector>

class Image
{
private:
    int m_sizex;
    int m_sizey;

    std::vector<char> m_list;

public:
    Image(int sizex, int sizey, const std::vector<char> &list);

public:
    void save(const std::string &name);
};