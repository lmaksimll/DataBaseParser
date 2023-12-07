#ifndef MANAGER_DB_H
#define MANAGER_DB_H

#include <string.h>
#include <vector>
#include <parser.h>
#include <console_ui.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <filesystem>

using namespace std;

class manager_db
{
    struct stat st = {};

    public:
        manager_db();

        bool command_request(parser &p) ;         //Проверка какую команду нужно выполнить

    private:

        bool request_create_db(parser &p);      //создания базы данных или таблицы
        bool request_use_db(parser &p);         //использования базы данных
        bool request_drop_db(parser &p);        //удаления базы данных или таблицы
        bool request_delete_db(parser &p);      //удаления записи
        bool request_insert_db(parser &p);      //вставки поля в таблицу
        bool request_update_db(parser &p);      //обновления поля в таблице
        bool request_select_db(parser &p);      //выборка значений из таблиц
        bool request_alter_db(parser &p);       //создание колонки в таблице

        bool correct_name_db(parser &p);                    //Проверка что бд с этим именем существует
        bool correct_name_table(parser &p);                 //Проверка что таблица с этим именем существует
        bool correct_name_field(parser &p,int nummber);      //Проверка что поле с этим именем существует
        bool correct_name_value(parser &p, int &index_field, vector <int> &index_data);      //Проверка что значение существует
        bool correct_used_db(parser &p);                     //Проверка что перед запросом в бд, пользователь ввел use
        int search_name_field(parser &p, int &count_field, int nummber);                     //Поиск кол-ва полей и индекс нужного

        char* get_path_db(parser &p);            //Вернуть путь папки + бд
        char* get_path_db_table(parser &p);      //Вернуть путь папки + бд + таблица

        void set_table_db(parser &p);            //Установить значения из файла
        void table_db_empty();                   //Отчистить поля

        int count_id = 0;
        string header;
        vector <string> data;

};

#endif // MANAGER_DB_H
