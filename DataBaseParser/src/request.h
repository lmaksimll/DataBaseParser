#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class request
{
    public:
        request();

        bool set_word(string request_user);   //Считывание запроса и разбиение на токены

        vector <string> get_word();           //Вернуть слова

        void clear_word(string error);  //Отчистка масива слов частично или полностью

    private:
        vector <string> word;           //Запрос разбитый на символы
};

#endif // REQUEST_H
