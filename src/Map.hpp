#pragma once
#include <vector>
#include <string>

class Map {
public:
    std::vector<std::string> data;

    Map();
    void load(int stage);
};
