#include "manager_db.h"

manager_db::manager_db()
{

}

bool manager_db::command_request(parser &p)
{
    string command = p.get_command();

    if(command == "create")
    {
        if(request_create_db(p))
        {
            return true;
        }
    }
    else if(command == "use")
    {
        if(request_use_db(p))
        {
            return true;
        }
    }
    else if(command == "drop")
    {
        if(request_drop_db(p))
        {
            return true;
        }
    }
    else if(command == "delete")
    {
        if(request_delete_db(p))
        {
            return true;
        }
    }
    else if(command == "insert")
    {
        if(request_insert_db(p))
        {
            return true;
        }
    }
    else if(command == "update")
    {
        if(request_update_db(p))
        {
            return true;
        }
    }
    else if(command == "select")
    {
        if(request_select_db(p))
        {
            return true;
        }
    }
    else if(command == "alter")
    {
        if(request_alter_db(p))
        {
            return true;
        }
    }

    return false;
}

bool manager_db::request_create_db(parser &p)
{
    string modifier = p.get_modifier();
    string name_db = p.get_name_db();

    ofstream out;

    if(modifier == "database")
    {
        if(correct_name_db(p))
        {
            console_ui::getInstance().error_exists_db();
            return false;
        }
        else
        {
            mkdir(get_path_db(p),0777);
            console_ui::getInstance().message_create_db();
            return true;
        }
    }
    else
    {
        if(!name_db.empty())
        {
            if(stat(get_path_db(p), &st) == 0)
            {
                if(correct_name_table(p))
                {
                    console_ui::getInstance().error_exists_table();
                    return false;
                }
                else
                {
                    ofstream file(get_path_db_table(p));

                    out.open(get_path_db_table(p));

                    out << 0 << endl;
                    out << "id;" << endl;
                    out.close();

                    console_ui::getInstance().message_create_table();
                    return true;
                }
            }

            console_ui::getInstance().error_no_exists_db();
            return false;
        }

        console_ui::getInstance().error_before_use();
        return false;
    }
}

bool manager_db::request_use_db(parser &p)
{
    if(!correct_name_db(p))
    {
        console_ui::getInstance().error_no_exists_db();
        return false;
    }
    else
    {
        console_ui::getInstance().message_use_db();
        return true;
    }
}

bool manager_db::request_drop_db(parser &p)
{
    string modifier = p.get_modifier();
    string name_db = p.get_name_db();

    if(modifier == "database")
    {
        if(!correct_name_db(p))
        {
            console_ui::getInstance().error_no_exists_db();
            return false;
        }
        else
        {
            std::filesystem::remove_all(get_path_db(p));
            console_ui::getInstance().message_drop_db();
            return true;
        }
    }
    else
    {
        if(!name_db.empty())
        {
            if(stat(get_path_db(p), &st) == 0)
            {
                if(!correct_name_table(p))
                {
                    console_ui::getInstance().error_no_exists_table();
                    return false;
                }
                else
                {
                    remove(get_path_db_table(p));
                    console_ui::getInstance().message_drop_table();
                    return true;
                }
            }

            console_ui::getInstance().error_no_exists_db();
            return false;
        }

        console_ui::getInstance().error_before_use();
        return false;
    }
}

bool manager_db::request_delete_db(parser &p)
{
    string name_db = p.get_name_db();
    int count_field = 0;
    int number = 0;
    ofstream out;

    if(!name_db.empty())
    {
        if(stat(get_path_db(p), &st) == 0)
        {
            if(correct_name_table(p))
            {
                if(correct_name_field(p,number))
                {
                    int index_field = search_name_field(p,count_field,number);
                    vector <int> index_data;

                    if(correct_name_value(p,index_field,index_data))
                    {
                        set_table_db(p);
                        out.open(get_path_db_table(p));

                        out << count_id << endl;
                        out << header << endl;

                        auto iter = data.begin();
                        data.erase(iter + index_data[0]);

                        for (size_t i = 0; i < data.size(); ++i)
                        {
                            out << data[i] << endl;;
                        }

                        out.close();
                        table_db_empty();

                        console_ui::getInstance().message_delete_db();
                        return true;
                    }

                    console_ui::getInstance().error_no_exists_value();
                    return false;
                }

                console_ui::getInstance().error_no_exists_field();
                return false;
            }

            console_ui::getInstance().error_no_exists_table();
            return false;
        }

        console_ui::getInstance().error_no_exists_db();
        return false;
    }

    console_ui::getInstance().error_before_use();
    return false;


}

bool manager_db::request_insert_db(parser &p)
{
    string name_db = p.get_name_db();
    vector <string> name_field = p.get_name_field();
    vector <string> value_field = p.get_value_field();

    int count_field = 0;
    int number = 0;
    int index_field;
    string tmp;

    ofstream out;

    if(!name_db.empty())
    {
        if(stat(get_path_db(p), &st) == 0)
        {
            if(correct_name_table(p))
            {
                if(correct_name_field(p,number))
                {
                    index_field = search_name_field(p,count_field,number);

                    set_table_db(p);
                    out.open(get_path_db_table(p));

                    count_id++;
                    out << count_id << endl;
                    out << header << endl;

                    tmp = to_string(count_id) + ";";
                    for (int j = 1; j < count_field; ++j)
                    {
                        if(index_field == j)
                        {
                            tmp += value_field[0] + ";";
                        }
                        else
                        {
                           tmp += ";";
                        }
                    }

                    data.push_back(tmp);

                    for (size_t i = 0; i < data.size(); ++i)
                    {
                        out << data[i] << endl;;
                    }

                    out.close();
                    table_db_empty();

                    console_ui::getInstance().message_insert_db();
                    return true;
                }

                console_ui::getInstance().error_no_exists_field();
                return false;
            }

            console_ui::getInstance().error_no_exists_table();
            return false;
        }

        console_ui::getInstance().error_no_exists_db();
        return false;
    }

    console_ui::getInstance().error_before_use();
    return false;
}

bool manager_db::request_update_db(parser &p)
{
    string name_db = p.get_name_db();
    vector <string> name_field = p.get_name_field();
    vector <string> value_field = p.get_value_field();
    int count_field;
    int number = 0;
    ofstream out;

    if(!name_db.empty())
    {
        if(stat(get_path_db(p), &st) == 0)
        {
            if(correct_name_table(p))
            {
                if(correct_name_field(p,number))    //0
                {
                    int index_field = search_name_field(p,count_field,number);
                    vector <int> index_data;
                    number++;

                    if(correct_name_value(p,index_field,index_data))
                    {
                        if(correct_name_field(p,number))    //1
                        {
                            int new_index_field = search_name_field(p,count_field,number);

                            if(new_index_field == 0)
                            {
                                console_ui::getInstance().error_no_change_id();
                                return false;
                            }

                            set_table_db(p);
                            out.open(get_path_db_table(p));

                            out << count_id << endl;
                            out << header << endl;

                            string new_data;
                            stringstream ss(data[index_data[0]]);
                            string tmp;
                            int index_value = 0;

                            while (getline(ss,tmp,';'))
                            {
                                if(index_value == new_index_field)
                                {
                                    new_data += value_field[1] + ";";
                                    index_value++;
                                }
                                else
                                {
                                    new_data += tmp + ";";
                                    index_value++;
                                }

                            }

                            data[index_data[0]] = new_data;

                            for (size_t i = 0; i < data.size(); ++i)
                            {
                                out << data[i] << endl;;
                            }

                            out.close();
                            table_db_empty();

                            console_ui::getInstance().message_update_db();
                            return true;
                        }

                        console_ui::getInstance().error_no_exists_field();
                        return false;
                    }

                    console_ui::getInstance().error_no_exists_value();
                    return false;
                }

                console_ui::getInstance().error_no_exists_field();
                return false;
            }

            console_ui::getInstance().error_no_exists_table();
            return false;
        }

        console_ui::getInstance().error_no_exists_db();
        return false;
    }

    console_ui::getInstance().error_before_use();
    return false;
}

bool manager_db::request_select_db(parser &p)
{
    string modifier = p.get_modifier();
    string name_db = p.get_name_db();
    vector <string> name_field = p.get_name_field();
    vector <string> select_data;
    string select_header;
    int count_field;
    int number = 0;

    if(!name_db.empty())
    {
        if(stat(get_path_db(p), &st) == 0)
        {
            if(correct_name_table(p))
            {
                if(modifier == "*")
                {
                    if(name_field.size() == 0)                       //Длина запроса 4, вывести всю таблицу
                    {
                        set_table_db(p);

                        select_header = header;
                        select_data = data;

                        table_db_empty();

                        console_ui::getInstance().output_select(select_data,select_header);
                        return true;
                    }
                    else                                             //Длина запроса 8, вывести записи всех полей по условию where
                    {
                        if(correct_name_field(p,number))    //0
                        {
                            int index_field = search_name_field(p,count_field,number);
                            vector <int> index_data;

                            if(correct_name_value(p,index_field,index_data))
                            {
                                set_table_db(p);

                                //Заголовок
                                select_header = header;

                                //Запись
                                auto iter = index_data.begin();

                                while (iter != index_data.end())
                                {
                                    select_data.push_back(data[*iter]);
                                    ++iter;
                                }

                                table_db_empty();

                                console_ui::getInstance().output_select(select_data,select_header);
                                return true;
                            }

                            console_ui::getInstance().error_no_exists_value();
                            return false;
                        }

                        console_ui::getInstance().error_no_exists_field();
                        return false;
                    }
                }
                else                                                //Длина запроса 8, вывести записи 1 поля по условию where
                {
                    if(correct_name_field(p,number))    //0
                    {
                        int index_field = search_name_field(p,count_field,number);
                        vector <int> index_data;
                        number++;

                        if(correct_name_value(p,index_field,index_data))
                        {
                            if(correct_name_field(p,number))    //1
                            {
                                int new_index_field = search_name_field(p,count_field,number);

                                set_table_db(p);

                                //Заголовок
                                stringstream sh(header);
                                string tmp;
                                int index_value = 0;

                                while (getline(sh,tmp,';'))
                                {
                                    if(index_value == new_index_field || index_value == 0)
                                    {
                                        select_header += tmp + ";";
                                        index_value++;
                                    }
                                    else
                                    {
                                        index_value++;
                                    }

                                }

                                //Запись
                                auto iter = index_data.begin();

                                while (iter != index_data.end())
                                {
                                    stringstream sd(data[*iter]);
                                    string tmp_data;
                                    tmp = "";
                                    index_value = 0;

                                    while (getline(sd,tmp,';'))
                                    {
                                        if(index_value == new_index_field || index_value == 0)
                                        {
                                            tmp_data += tmp + ";";
                                            index_value++;
                                        }
                                        else
                                        {
                                            index_value++;
                                        }

                                    }

                                    select_data.push_back(tmp_data);
                                    ++iter;
                                }

                                table_db_empty();

                                console_ui::getInstance().output_select(select_data,select_header);
                                return true;
                            }

                            console_ui::getInstance().error_no_exists_field();
                            return false;
                        }

                        console_ui::getInstance().error_no_exists_value();
                        return false;
                    }

                    console_ui::getInstance().error_no_exists_field();
                    return false;
                }
            }

            console_ui::getInstance().error_no_exists_table();
            return false;
        }

        console_ui::getInstance().error_no_exists_db();
        return false;
    }

    console_ui::getInstance().error_before_use();
    return false;
}

bool manager_db::request_alter_db(parser &p)
{
    string name_db = p.get_name_db();
    int number = 0;
    vector <string> name_field = p.get_name_field();
    ofstream out;

    if(!name_db.empty())
    {
        if(stat(get_path_db(p), &st) == 0)
        {
            if(correct_name_table(p))
            {
                if(!correct_name_field(p,number))
                {
                    set_table_db(p);
                    out.open(get_path_db_table(p));

                    out << count_id << endl;
                    header = header + name_field[0] + ";";
                    out << header << endl;
                    for (size_t i = 0; i < data.size(); ++i)
                    {
                        data[i] += ";";
                        out << data[i] << endl;;
                    }

                    out.close();
                    table_db_empty();

                    console_ui::getInstance().message_alter_db();
                    return true;
                }

                console_ui::getInstance().error_exists_field();
                return false;
            }

            console_ui::getInstance().error_no_exists_table();
            return false;
        }

        console_ui::getInstance().error_no_exists_db();
        return false;
    }

    console_ui::getInstance().error_before_use();
    return false;
}

//---------Коректность полей---------

bool manager_db::correct_name_db(parser &p)
{
    if(stat(get_path_db(p), &st) == -1)
    {
        return false;
    }
    return true;
}

bool manager_db::correct_name_table(parser &p)
{
    if(stat(get_path_db_table(p), &st) == -1)
    {
        return false;
    }
    return true;
}

bool manager_db::correct_name_field(parser &p, int nummber)
{
    vector <string> name_field = p.get_name_field();

    set_table_db(p);

    //---Смотрим какие есть заголовки---
    stringstream ss(header);
    string tmp;

    while (getline(ss,tmp,';'))
    {
        if(tmp == name_field[nummber])
        {
            table_db_empty();
            return true;
        }
    }

    table_db_empty();
    return false;
}

bool manager_db::correct_name_value(parser &p, int &index_field, vector <int> &index_data)
{
    vector <string> value_field = p.get_value_field();

    set_table_db(p);

    for (size_t i = 0; i < data.size(); ++i)
    {
        stringstream ss(data[i]);
        string tmp;
        int index_value = 0;

        while (getline(ss,tmp,';'))
        {
            if(index_value == index_field)
            {
                if(tmp == value_field[0])
                {
                    index_data.push_back(i);
                }
            }
            index_value++;
        }
    }

    if(index_data.size() > 0)
    {
        table_db_empty();
        return true;
    }
    else
    {
        table_db_empty();
        return false;
    }
}

int manager_db::search_name_field(parser &p, int &count_field, int nummber)
{
    vector <string> name_field = p.get_name_field();
    count_field = 0;
    int index_field = -1;

    set_table_db(p);

    //---Смотрим какие есть заголовки---
    stringstream ss(header);
    string tmp;

    while (getline(ss,tmp,';'))
    {
        if(tmp == name_field[nummber])
        {
            index_field = count_field;
        }
        count_field++;
    }

    table_db_empty();

    return index_field;
}

//---------Вернуть пути---------

char *manager_db::get_path_db(parser &p)
{
    string name_db = p.get_name_db();                                   //Название бд
    string path = "/home/maksim/parser_v2/DataBaseParser/src/db/";      //Путь к папке
    string path_db = path + name_db + "/";                              //Путь + бд

    char *path_db_char = strcpy(new char[path_db.length() + 1], path_db.c_str());

    return path_db_char;
}

char *manager_db::get_path_db_table(parser &p)
{
    string name_db = p.get_name_db();                                   //Название бд
    string name_table = p.get_name_table();                             //Название таблицы
    string path = "/home/maksim/parser_v2/DataBaseParser/src/db/";      //Путь к папке
    string path_db = path + name_db + "/" + name_table + ".txt";        //Путь + бд + таблица

    char *path_db_char = strcpy(new char[path_db.length() + 1], path_db.c_str());

    return path_db_char;
}

void manager_db::set_table_db(parser &p)
{
    ifstream in;
    string tmp;

    in.open(get_path_db_table(p));

    in >> count_id;
    in >> header;
    while(getline(in,tmp))
    {
        data.push_back(tmp);
    }

    auto iter = data.begin();
    data.erase(iter);

    in.close();
}

void manager_db::table_db_empty()
{
    count_id = 0;
    header = "";
    data.clear();
}
