#include  "Notebook.hpp"
#include  "Direction.hpp"
#include <iostream>
#include <string>
#include "vector"
using namespace std;
using ariel::Direction;
const int maxValue=100;
namespace ariel {

    void Notebook::emptyRow( int Page, int Row) {
        if(Page<0 || Row <0 ) {
            throw std::invalid_argument("Error! Entering incorrect values to the notebook");
        }
        if (notebook[Page][Row].empty()) {
            for ( int i = 0; i < maxValue; ++i) {
                notebook[Page][Row + i].push_back('_');
        }}}


    void Notebook::write( int Page,  int Row,  int Column, Direction direction, string const &text) {
        if (Page<0 || Row <0 || Column<0 || Column > maxValue || direction != Direction::Horizontal && direction != Direction::Vertical) {
            throw std::invalid_argument("Error! Entering incorrect values to the notebook");
        }
        if ((Column + text.size()) > maxValue && direction == Direction::Horizontal) {
            throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");
        }
        for ( int i = 0; i < text.size(); ++i) {
            if (notebook[Page][Row].at(Column + i) == '~') {
                throw std::invalid_argument(
                        "By notebook settings you will not be able to write where text has been deleted in the past");
            }
        }
        if (direction == Direction::Horizontal) {
            Notebook::emptyRow( Page, Row);
            for ( int i = 0; i < text.size(); ++i) {
                if (notebook[Page][Row].at(Column) != '_') {
                    throw std::invalid_argument(
                            "By notebook settings you will not be able to write where text has been written or deleted in the past");
                }
            }
            notebook[Page][Row].insert(Column, text);
        } else{
            for ( int i = 0; i < text.size(); ++i) {
                Notebook::emptyRow( Page, Row + i);
                if (notebook[Page][Row+i].at(Column)=='_'){
                    notebook[Page][Row+i].insert(Column,1,text.at(i));
                } else{
                    throw std::invalid_argument("By notebook settings you will not be able to write where text has been written or deleted in the past");
                }
    }}}

    std::string Notebook::read( int Page,  int Row,  int Column, Direction direction,  int Length) {
        string ans_read;
        if (Page<0 || Row <0 || Column<0 || Length<0||Column > maxValue || direction != Direction::Horizontal && direction != Direction::Vertical) {
            throw std::invalid_argument("Error! Entering incorrect values to the notebook");
        }
        if ((Length + Column) > maxValue && direction == Direction::Horizontal) {
            throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");
        }
        if (direction == Direction::Vertical) {
            for ( int i = 0; i < Length; ++i) {
                if (notebook[Page][Row + i].empty()) {
                    ans_read.push_back('_');
                } else {
                    ans_read.push_back(notebook[Page][Row + i].at(Column));
                }
            }
        } else {
            if (notebook[Page][Row].empty()) {
                for ( int i = 0; i < Length; ++i) {
                    ans_read += '_';
                }
            } else {
                ans_read = (notebook[Page][Row]).substr(Column, Length);
            }
        }
        return ans_read;
    }


        void Notebook::erase( int Page,  int Row,  int Column, Direction direction, int Length) {
        if(Page<0 || Row <0 || Column<0 || Length<0){
            throw std::invalid_argument("Entering a negative number! The following numbers must be positive: row, column, page");
        }
            if((Length+Column)>maxValue && direction == Direction::Horizontal){
                throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");}
            if(Length < 0 || Column > maxValue || Row < maxValue || direction != Direction::Horizontal && direction != Direction::Vertical){
                throw std::invalid_argument("Error! Entering incorrect values to the notebook");}
            if(direction == Direction::Vertical) {
                for ( int i = 0; i < Length; ++i) {
                    Notebook::emptyRow(Page,Row);
                    notebook[Page][Row+i].insert(Column,1,'~');
                }

            }
            //if the Direction=Horizontal
            else{
                for ( int i = 0; i < Length; ++i) {
                    Notebook::emptyRow(Page,Row);
                    notebook[Page][Row].insert(Column+i,1,'~');}
                }
        }


        void Notebook::show(int page) {
            if(page<0){
                throw std::invalid_argument("Error! Entering incorrect value to the notebook");}
            int i = 0;
            char space_char = ' ';
            if(notebook[page].empty()) {
                for ( int j = 0; j < maxValue; ++j) {
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




