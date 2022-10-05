#ifndef __COLOR__H__
#define __COLOR__H__
#include <iostream>
#include "library.h"
using namespace std;

class Color{
    public:
        char color;
        vector< pair<int, int> >puntos;
        vector< pair<int, int> >historial;

};
#endif