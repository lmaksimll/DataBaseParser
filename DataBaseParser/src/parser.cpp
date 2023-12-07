#include "parser.h"

parser::parser()
{

}

bool parser::parser_list(request &r)
{
    vector <string> word = r.get_word();

    if(word[0] == "create" && word.size() == 3)
    {
        if(db_command(r))
        {
            set_create(r);
            return true;
        }
        return false;
    }
    else if(word[0] == "use" && word.size() == 2)
    {
        if(use_request(r))
        {
            set_use(r);
            return true;
        }
        return false;
    }
    else if(word[0] == "drop" && word.size() == 3)
    {
        if(db_command(r))
        {
            set_drop(r);
            return true;
        }
        return false;
    }
    else if(word[0] == "delete" && word.size() == 7)
    {
        if(delete_request(r))
        {
            set_delete(r);
            return true;
        }
        return false;
    }
    else if(word[0] == "insert" && word.size() == 7)
    {
        if(insert_request(r))
        {
            set_insert(r);
            return true;
        }
        return false;
    }
    else if(word[0] == "update" && word.size() == 10)
    {
        if(update_request(r))
        {
            set_update(r);
            return true;
        }
        return false;
    }
    else if(word[0] == "select" && (word.size() == 4 || word.size() == 8))
    {
        if(select_request(r))
        {
            set_select(r);
            return true;
        }
        return false;
    }
    else if(word[0] == "alter" && word.size() == 6)
    {
        if(alter_request(r))
        {
            set_alter(r);
            return true;
        }
        return false;
    }
    else
    {
       string error;

       r.clear_word(error);
       console_ui::getInstance().error_parser_list();

       return false;
    }
    return false;
}

bool parser::db_command(request &r)
{
    vector <string> word = r.get_word();

    if(word[1] == "database" || word[1] == "table")
    {
        if(title_check(word[2]))
        {
            return true;
        }

        r.clear_word(word[1]);
        return false;
    }

    r.clear_word(word[0]);
    console_ui::getInstance().error_db_command();
    return false;
}

bool parser::delete_request(request &r)
{
    vector <string> word = r.get_word();

    if(from_command(r,1))
    {
        if(where_command(r,3))
        {
            return true;
        }

        r.clear_word(word[2]);
        return false;
    }

    r.clear_word(word[0]);
    return false;
}

bool parser::from_command(request &r, int index)
{
    vector <string> word = r.get_word();

    if(word[index] == "from")
    {
        if(title_check(word[index+1]))
        {
            return true;
        }

        r.clear_word(word[index]);
        return false;
    }

    r.clear_word(word[index-1]);
    console_ui::getInstance().error_from_command();

    return false;
}

bool parser::insert_request(request &r)
{
    vector <string> word = r.get_word();

    if(word[1] == "into")
    {
        if(title_check(word[2]))
        {
            if(set_command(r,3))
            {
                return true;
            }

            r.clear_word(word[2]);
            return false;
        }

        r.clear_word(word[1]);
        return false;
    }

    r.clear_word(word[0]);
    console_ui::getInstance().error_insert_request();

    return false;
}

bool parser::select_request(request &r)
{
    vector <string> word = r.get_word();

    if(word[1] == "*" || title_check(word[1]))
    {
        if(from_command(r,2))
        {
            if(word.size() == 4)
            {
                return true;
            }
            else if(word.size() == 8)
            {
                if(where_command(r,4))
                {
                    return true;
                }

                r.clear_word(word[3]);
                return false;
            }

            r.clear_word(word[2]);
            console_ui::getInstance().error_select_request_size();
            return false;
        }

        r.clear_word(word[1]);
        return false;
    }

    r.clear_word(word[0]);
    console_ui::getInstance().error_select_request_name();
    return false;
}

bool parser::set_command(request &r, int index)
{
    vector <string> word = r.get_word();

    if(word[index] == "set")
    {
        if(title_check(word[index+1]))
        {
            if(word[index+2] == "=")
            {
                if(title_check(word[index+3]))
                {
                    return true;
                }

                r.clear_word(word[index+2]);
                return false;
            }

            r.clear_word(word[index+1]);
            console_ui::getInstance().error_set_command_equal();
            return false;
        }

        r.clear_word(word[index]);
        return false;
    }

    r.clear_word(word[index-1]);
    console_ui::getInstance().error_set_command_set();
    return false;
}

bool parser::use_request(request &r)
{
    vector <string> word = r.get_word();

    if(title_check(word[1]))
    {
        return true;
    }

    r.clear_word(word[0]);
    return false;
}

bool parser::title_check(string name)
{
    for (size_t i = 0; i < name.size(); ++i)
    {
        if(!isalnum(name[i]))
        {
            console_ui::getInstance().error_title_check_name();
            return false;
        }
    }
    return true;
}

bool parser::update_request(request &r)
{
    vector <string> word = r.get_word();

    if(title_check(word[1]))
    {
        if(set_command(r,2))
        {
            if(where_command(r,6))
            {
                return true;
            }

            r.clear_word(word[5]);
            return false;
        }

        r.clear_word(word[1]);
        return false;
    }

    r.clear_word(word[0]);
    return false;
}

bool parser::where_command(request &r, int index)
{
    vector <string> word = r.get_word();

    if(word[index] == "where")
    {
        if(title_check(word[index+1]))
        {
            if(word[index+2] == "=")
            {
                if(title_check(word[index+3]))
                {
                    return true;
                }

                r.clear_word(word[index+2]);
                return false;
            }

            r.clear_word(word[index+1]);
            console_ui::getInstance().error_set_command_equal();
            return false;
        }

        r.clear_word(word[index]);
        return false;
    }

    r.clear_word(word[index-1]);
    console_ui::getInstance().error_where_command();
    return false;
}

bool parser::alter_request(request &r)
{
    vector <string> word = r.get_word();

    if(word[1] == "table")
    {
        if(title_check(word[2]))
        {
            if(word[3] == "add")
            {
                if(word[4] == "column")
                {
                    if(title_check(word[5]))
                    {
                        return true;
                    }

                    r.clear_word(word[4]);
                    return false;
                }

                r.clear_word(word[3]);
                console_ui::getInstance().error_alter_request_column();
                return false;
            }

            r.clear_word(word[2]);
            console_ui::getInstance().error_alter_request_add();
            return false;
        }

        r.clear_word(word[1]);
        return false;
    }

    r.clear_word(word[0]);
    console_ui::getInstance().error_alter_request_table();
    return false;
}

//------------Методы хранения данных------------

void parser::field_empty()
{
    command = "";
    modifier = "";
    //name_db = "";
    name_table = "";
    name_field.clear();
    value_field.clear();
}

void parser::set_create(request &r)
{
    vector <string> word = r.get_word();
    field_empty();

    command = word[0];
    modifier = word[1];
    if(word[1] == "table")
    {
        name_table = word[2];
    }
    else
    {
        name_db = "";
        name_db = word[2];
    }
}

void parser::set_use(request &r)
{
    vector <string> word = r.get_word();
    field_empty();
    name_db = "";

    command = word[0];
    name_db = word[1];
}

void parser::set_drop(request &r)
{
    vector <string> word = r.get_word();
    field_empty();

    command = word[0];
    modifier = word[1];
    if(word[1] == "table")
    {
        name_table = word[2];
    }
    else
    {
        name_db = "";
        name_db = word[2];
    }
}

void parser::set_delete(request &r)
{
    vector <string> word = r.get_word();
    field_empty();

    command = word[0];
    name_table = word[2];
    name_field.push_back(word[4]);
    value_field.push_back(word[6]);
}

void parser::set_insert(request &r)
{
    vector <string> word = r.get_word();
    field_empty();

    command = word[0];
    name_table = word[2];
    name_field.push_back(word[4]);
    value_field.push_back(word[6]);
}

void parser::set_update(request &r)
{
    vector <string> word = r.get_word();
    field_empty();

    command = word[0];
    name_table = word[1];

    //Какие значения проверяем
    name_field.push_back(word[7]);
    value_field.push_back(word[9]);

    //На что меняем
    name_field.push_back(word[3]);
    value_field.push_back(word[5]);
}

void parser::set_select(request &r)
{
    vector <string> word = r.get_word();
    field_empty();

    command = word[0];
    if(word.size() == 4)
    {
        modifier = word[1];
        name_table = word[3];
    }
    else
    {
        modifier = word[1];
        name_table = word[3];
        name_field.push_back(word[5]);
        value_field.push_back(word[7]);
        name_field.push_back(word[1]);
    }
}

void parser::set_alter(request &r)
{
    vector <string> word = r.get_word();
    field_empty();

    command = word[0];
    name_table = word[2];
    name_field.push_back(word[5]);
}

//------------Методы возврата данных------------

string parser::get_command()
{
    return command;
}

string parser::get_modifier()
{
    return modifier;
}

string parser::get_name_db()
{
    return name_db;
}

string parser::get_name_table()
{
    return name_table;
}

vector <string> parser::get_name_field()
{
    return name_field;
}

vector <string> parser::get_value_field()
{
    return value_field;
}

