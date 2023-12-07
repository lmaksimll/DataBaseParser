#ifndef CONSOLE_UI_H
#define CONSOLE_UI_H

#include <iostream>
#include <vector>
#include <request.h>

using namespace std;

//Singleton Мэйерса
class console_ui
{
private:
    console_ui() {}
    console_ui( const console_ui&);
    console_ui& operator=( console_ui& );
public:
    static console_ui& getInstance() {
        static console_ui  instance;
        return instance;
    }

    string request_input();                     //Пользователь вводит строку запрос
    void message_begin();                       //Вывод начального сообщения
    void message_repeat();                      //Повторный ввод запроса
    void error_empty();                         //Вывод ошибки если строка пустая
    void error_request_repeat();                //Вывод с просьбой повторить неверный запрос
    void output_word(request &r);               //Вывод в консоль запроса по словам

    void error_parser_list();                   //Вывод ошибки если ни одна команда не совпадает
    void error_db_command();                    //Вывод ошибки если Нет совпадения с database или table
    void error_title_check_name();              //Вывод ошибки если Нет совпадения с коректным именем
    void error_from_command();                  //Вывод ошибки если Нет совпадения с from
    void error_insert_request();                //Вывод ошибки если Нет совпадения с into
    void error_select_request_name();           //Вывод ошибки если Нет совпадения с * или коректным именем
    void error_select_request_size();           //Вывод ошибки если Неверная длина строки
    void error_set_command_set();               //Вывод ошибки если Нет совпадения с set
    void error_set_command_equal();             //Вывод ошибки если Нет совпадения с =
    void error_where_command();                 //Вывод ошибки если Нет совпадения с where
    void error_alter_request_table();           //Вывод ошибки если Нет совпадения с table
    void error_alter_request_add();             //Вывод ошибки если Нет совпадения с add
    void error_alter_request_column();          //Вывод ошибки если Нет совпадения с column

    void error_exists_db();                      //Вывод ошибки если бд c таким именем существует
    void error_no_exists_db();                   //Вывод ошибки если бд c таким именем не существует
    void message_create_db();                    //Вывод сообщения что бд успешно создана
    void error_exists_table();                   //Вывод ошибки если таблица c таким именем существует
    void error_no_exists_table();                //Вывод ошибки если таблица c таким именем не существует
    void error_before_use();                     //Вывод ошибки если use не введен заранее
    void message_create_table();                 //Вывод сообщения что таблица успешно создана
    void message_use_db();                       //Вывод сообщения что к бд можно отправлять запрос
    void message_drop_db();                      //Вывод сообщения что бд успешна удалена
    void message_drop_table();                   //Вывод сообщения что таблица успешна удалена
    void error_exists_field();                   //Вывод ошибки если поле c таким именем существует
    void error_no_exists_field();                //Вывод ошибки если поле c таким именем не существует
    void message_alter_db();                     //Вывод сообщения что поле успешно добавлено
    void message_insert_db();                    //Вывод сообщения что запись успешно добавлена
    void error_no_exists_value();                //Вывод ошибки если Запись c таким значениями не существует
    void message_delete_db();                    //Вывод сообщения что запись успешно удалена
    void error_no_change_id();                   //Вывод ошибки что нельзя изменять поле id
    void message_update_db();                    //Вывод сообщения что запись успешно изменена

    void output_select(vector <string> &select_data, string select_header);    //Вывод запроса select

};


#endif // CONSOLE_UI_H
