#include  "Notebook.hpp"
#include  "Direction.hpp"
#include <iostream>
#include <string>
#include "vector"
using namespace std;
using ariel::Direction;
const int maxValue=100;
namespace ariel {

    void Notebook::emptyRow(unsigned int Page,unsigned int Row) {
        if (notebook[Page][Row].empty()) {
            for (unsigned int i = 0; i < maxValue; ++i) {
                notebook[Page][Row + (unsigned) i].push_back('_');
        }}}


    void Notebook::write(unsigned int Page, unsigned int Row, unsigned int Column, Direction direction, string const &text) {
        if (Column > maxValue || direction != Direction::Horizontal && direction != Direction::Vertical) {
            throw std::invalid_argument("Error! Entering incorrect values to the notebook");
        }
        if ((Column + text.size()) > maxValue && direction == Direction::Horizontal) {
            throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");
        }
        for (unsigned int i = 0; i < text.size(); ++i) {
            if (notebook[Page][Row].at(Column + i) == '~') {
                throw std::invalid_argument(
                        "By notebook settings you will not be able to write where text has been deleted in the past");
            }
        }
        if (direction == Direction::Horizontal) {
            Notebook::emptyRow((unsigned int) Page, (unsigned int) Row);
            for (unsigned int i = 0; i < text.size(); ++i) {
                if (notebook[Page][Row].at(Column) != '_') {
                    throw std::invalid_argument(
                            "By notebook settings you will not be able to write where text has been written or deleted in the past");
                }
            }
            notebook[Page][Row].insert(Column, text);
        } else{
            for (unsigned int i = 0; i < text.size(); ++i) {
                Notebook::emptyRow((unsigned int) Page, (unsigned int) Row + i);
                if (notebook[Page][Row+i].at(Column)=='_'){
                    notebook[Page][Row+i].insert(Column,1,text.at(i));
                } else{
                    throw std::invalid_argument("By notebook settings you will not be able to write where text has been written or deleted in the past");
                }
    }}}

    std::string Notebook::read(unsigned int Page, unsigned int Row, unsigned int Column, Direction direction, unsigned int Length) {
        string ans_read;
        if (Column > maxValue || direction != Direction::Horizontal && direction != Direction::Vertical) {
            throw std::invalid_argument("Error! Entering incorrect values to the notebook");
        }
        if ((Length + Column) > maxValue && direction == Direction::Horizontal) {
            throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");
        }
        if (direction == Direction::Vertical) {
            for (unsigned int i = 0; i < Length; ++i) {
                if (notebook[Page][Row + i].empty()) {
                    ans_read.push_back('_');
                } else {
                    ans_read.push_back(notebook[Page][Row + i].at(Column));
                }
            }
        } else {
            if (notebook[Page][Row].empty()) {
                for (unsigned int i = 0; i < Length; ++i) {
                    ans_read += '_';
                }
            } else {
                ans_read = (notebook[Page][Row]).substr(Column, Length);
            }
        }
        return ans_read;
    }


        void Notebook::erase(unsigned int Page, unsigned int Row, unsigned int Column, Direction direction,unsigned int Length) {
            if((Length+Column)>maxValue && direction == Direction::Horizontal){
                throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");}
            if(Length < 0 || Column > maxValue || Row < maxValue || direction != Direction::Horizontal && direction != Direction::Vertical){
                throw std::invalid_argument("Error! Entering incorrect values to the notebook");}
            if(direction == Direction::Vertical) {
                for (unsigned int i = 0; i < Length; ++i) {
                    Notebook::emptyRow((unsigned int)Page,(unsigned int)Row);
                    notebook[Page][Row+i].insert(Column,1,'~');
                }

            }
            //if the Direction=Horizontal
            else{
                for (unsigned int i = 0; i < Length; ++i) {
                    Notebook::emptyRow((unsigned int)Page,(unsigned int)Row);
                    notebook[Page][Row].insert(Column+i,1,'~');}
                }
        }


        void Notebook::show(unsigned int page) {
            unsigned int i = 0;
            char space_char = ' ';
            if(notebook[page].empty()) {
                for (unsigned int j = 0; j < maxValue; ++j) {
                    string Page = notebook[page][i];
                    cout << i << ':' << space_char << Page;
                    i++;
                }
            }
            else{
                while (!notebook[page].empty()) {
                string Page = notebook[page][i];
                cout << i << ':' << space_char << Page;
                i++;
                if (i == maxValue) {
                    space_char += ' ';
                    i = 0;
                }
            }
        }
    }

}




