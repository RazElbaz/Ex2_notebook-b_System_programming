#include <string>
#include <iostream>
#include "Direction.hpp"
#include "vector"
#include <map>
using namespace std;
using ariel::Direction;

namespace ariel{
    class Notebook {
        std::map< int, std::map< int, string> > notebook;
    public:
        void write(int Page,  int Row,  int Column, Direction direction, string const &text);
        string read(int Page,  int Row,  int Column, Direction direction,  int Length);
        void erase(int Page,  int Row,  int Column, Direction direction, int Length);
        void show(int Page);
        void emptyRow(int Page, int Row);
        void emptyCol(int Page, int Row, int Size);
    };
}

