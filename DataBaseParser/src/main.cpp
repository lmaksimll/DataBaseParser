// Cинтаксический анализатор языка управления примитивной базой данных
#include <iostream>
#include <parser.h>
#include <request.h>
#include <manager_db.h>
#include <console_ui.h>

using namespace std;

int main()
{
    request r;          //Сторока пользователя
    parser p;           //Парсер
    manager_db mdb;     //Запрос к бд   
    string error;
    string request_user;    //Строка пользователя

    console_ui::getInstance().message_begin();

    while (1)
    {
        request_user = console_ui::getInstance().request_input();   //Вводим строку

        if(r.set_word(request_user))        //Разбиваем и приравниваем строку
        {
            if(p.parser_list(r))            //Парсер проверяет ее на ошибки и передает в бд
            {
                if(mdb.command_request(p))  //Выполнение запроса к бд
                {
                    r.clear_word(error);        //Отчистить строку для нового запроса
                    console_ui::getInstance().message_repeat();
                }
                else
                {
                    r.clear_word(error);        //Отчистить строку для нового запроса
                }
            }
            else
            {
                console_ui::getInstance().error_request_repeat();
                console_ui::getInstance().output_word(r);
            }
        }
        else
        {
            console_ui::getInstance().error_empty();
        }
    }

    return 0;
}

