#include  "Notebook.hpp"
#include  "Direction.hpp"
using namespace std;
using namespace ariel;
using ariel::Direction;
const int maxValue=99;

    void ariel::Notebook::emptyRow( int Page, int Row) {
        /**
        This function is designed to create a new line in the notebook
         */
        if (notebook[Page][Row].empty()) {
            for ( int i = 0; i < maxValue; ++i) {
                    notebook[Page][Row].push_back('_');
                }
        }}

    void ariel::Notebook::emptyCol( int Page, int Row, int Size) {
        /**
        This function is designed to create a new column in the notebook
         */
        for ( size_t i = 0; i < Size; ++i) {
            if (notebook[Page][(unsigned long)Row + i].empty()) {
                for (int k = 0; k < maxValue + 1; k++) {
                    notebook[Page][(unsigned long)Row + i].push_back('_');
                }
            }
        }}

    void ariel::Notebook::write( int Page,  int Row,  int Column, Direction direction, string const &text) {
    /**
    Gets a position (page, row and column), direction (horizontal or vertical), and a string that represents what needs to be written, and writes the string in a notebook in the appropriate place.
    Note that if we have already written, or deleted to the specified location, the function will throw an error.
    */
        if (Page < 0 || Row < 0 || Column < 0 || Column > maxValue) {
            throw std::invalid_argument("Error! Entering incorrect values to the notebook");
        }
        //checking the correctness of the characters in the text received as input
        for (size_t i = 0; i < text.length(); ++i) {
            if (text[i] < ' ' || text[i] >= '~') {
                throw invalid_argument("Insert a character that is not in the appropriate range");
            }
        }
        if (direction == Direction::Vertical) {
            Notebook::emptyCol(Page, Row, text.size());
            for (size_t i = 0; i < text.size(); ++i) {
                //it is possible to write only where it has the character '_'
                if (notebook[Page][(unsigned int) Row + i].at((unsigned long) Column) == '_') {
                    notebook[Page][(unsigned int) Row + i].insert((unsigned long) Column, 1, text.at((unsigned long) i));

                } else {
                    throw std::invalid_argument("By notebook settings you will not be able to write where text has been written or deleted in the past");
                }
            }
        }
        //if direction == Direction::Horizontal
        else {
            if (((unsigned long) Column + text.size()) > maxValue) {
                throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");
            }
            Notebook::emptyRow(Page, Row);
            for (size_t i = 0; i < text.size(); ++i) {
                //it is possible to write only where it has the character '_'
                if (notebook[Page][(size_t) Row].at((unsigned long) Column + i) != '_') {
                    throw std::invalid_argument("By notebook settings you will not be able to write where text has been written or deleted in the past");
                }
            }
            notebook[Page][Row].replace((unsigned long) Column, text.length(), text);
        }
    }


    std::string ariel::Notebook::read( int Page,  int Row,  int Column, Direction direction,  int Length) {
    /**
      Gets position (page, row and column), direction (horizontal or vertical), and number of characters, reads what is written in the notebook at the given position and length, and returns a string.
      The letter in each box on the board is the last letter written there
    */
        if (Page<0 || Row <0 || Column<0 || Length<0 ||Column > maxValue ) {
            throw std::invalid_argument("Error! Entering incorrect values to the notebook");
        }

        string ans_read;

        if (direction == Direction::Vertical) {
            for ( size_t i = 0; i < Length; ++i) {
                if (notebook[Page][(unsigned int)Row + i].empty()) {
                    ans_read += '_';
                } else {
                    ans_read+=notebook[Page][(unsigned int)Row + i].at((unsigned long )Column);
                }}
        }
        //if direction == Direction::Horizontal
        else {
            if ((Length + Column) > maxValue+1) {
                throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");
            }
            if (notebook[Page][Row].empty()) {
                for (size_t i = 0; i < Length; ++i) {
                    ans_read += '_';
                }
            } else {
                //if the column given is the last column then we would like to read a single character,
                // of course the (length given + the column) is correct
                if (Column == maxValue) {
                    ans_read+=notebook[Page][Row].at((unsigned long) maxValue-1);
                } else{
                    ans_read = (notebook[Page][(size_t)Row]).substr((unsigned long )Column, (unsigned long )Length);

                }}}
        return ans_read;
    }


        void ariel::Notebook::erase( int Page,  int Row,  int Column, Direction direction, int Length) {
        /**
        Gets position (page, row and column), direction (horizontal or vertical), and number of characters, and deletes what is written in the relevant position and direction.
        Since we are writing with a pen, the function will not be deleted but "scribbled" in the appropriate places.
        (Place the characters in the character ~)
         */
        if(Page<0 || Row <0 || Column<0 || Column > maxValue || Length<0){
            throw std::invalid_argument("Error! Entering incorrect values to the notebook");
        }

        if(direction == Direction::Vertical) {
            for ( size_t i = 0; i < Length; ++i) {
                Notebook::emptyCol(Page, Row, Length);
                notebook[Page][(unsigned int)Row+i].insert((unsigned long )Column,1,'~');
                }

        }
        //if direction == Direction::Horizontal
        else{
            if((Length+Column)>maxValue){
                throw std::invalid_argument("Error! You have exceeded the 100-character quota in a row");}
                 Notebook::emptyRow(Page,Row);
                for ( size_t i = 0; i < Length; ++i) {
                    notebook[Page][(size_t)Row].replace((unsigned long )Column+i,1,"~");
                }
         }}


        void ariel::Notebook::show(int page) {
        /**
         Gets a page number and displays it in a convenient way to read
         */
            if(page<0){
                throw std::invalid_argument("Error! Entering incorrect value to the notebook");}
            int i = 0;
            char space_char = ' ';
            if(notebook[page].empty()) {
                for ( size_t j = 0; j < maxValue+1; ++j) {
                    emptyRow(page,j);
                    string Page = notebook[page][i];
                    cout << i << ':' << space_char << Page<<endl;
                    i++;
                }
            }
            else{
                while (!notebook[page].empty()) {
                string Page = notebook[page][i];
                cout << i << ':' << space_char << Page<<endl;
                i++;
                if (i == maxValue) {
                    space_char += ' ';
                    i = 0;
                }
            }
        } }






