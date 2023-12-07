#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <console_ui.h>
#include <request.h>

using namespace std;

class parser
{
    public:
        parser();

        bool parser_list(request &r);

        string get_command();
        string get_modifier();
        string get_name_db();
        string get_name_table();
        vector <string> get_name_field();
        vector <string> get_value_field();

    private:
        bool db_command(request &r);
        bool delete_request(request &r);
        bool from_command(request &r,int index);
        bool insert_request(request &r);
        bool select_request(request &r);
        bool set_command(request &r,int index);
        bool use_request(request &r);
        bool title_check(string name);
        bool update_request(request &r);
        bool where_command(request &r,int index);
        bool alter_request(request &r);

        void field_empty();             //Отчистка всех полей

        void set_create(request &r);
        void set_use(request &r);
        void set_drop(request &r);
        void set_delete(request &r);
        void set_insert(request &r);
        void set_update(request &r);
        void set_select(request &r);
        void set_alter(request &r);

        string command;                 //Команда db
        string modifier;                //db или table или *
        string name_db;                 //Название бд
        string name_table;              //Название таблицы
        vector <string> name_field;      //Название поля
        vector <string> value_field;     //Значие поля

};

#endif // PARSER_H
