#include <string>
#include <iostream>
#include "Direction.hpp"

#include "vector"
#include <map>
using namespace std;
using ariel::Direction;

namespace ariel{
    class Notebook {
        std::map<unsigned int, std::map<unsigned int, string> > notebook;
    public:
        Notebook();
        void write(unsigned int Page, unsigned int Row, unsigned int Column, Direction direction, string const &text);
        string read(unsigned int Page, unsigned int Row, unsigned int Column, Direction direction, unsigned int Length);
        void erase(unsigned int Page, unsigned int Row, unsigned int Column, Direction direction,unsigned int Length);
        void show(unsigned int Page);
        bool check_arguments(unsigned int Page, unsigned int Row, unsigned int Column, Direction direction);
        void emptyRow(unsigned int Page,unsigned int Row);
    };
}

