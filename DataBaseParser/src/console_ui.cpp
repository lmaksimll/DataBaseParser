#include "console_ui.h"

string console_ui::request_input()
{
    string request_user;

    getline(cin, request_user);

    return request_user;
}

void console_ui::message_begin()
{
    cout << "-------------------------------------------------------------------\n"
                "| Запрос должен начинаться со слов:                               |\n"
                "| create,  use, drop, delete, insert, update, select, alter       |\n"
                "-------------------------------------------------------------------\n";

}

void console_ui::message_repeat()
{
    cout << "-------------------------------------------------------------------\n"
            "| Можно ввести новый запрос или закрыть программу                 |\n"
            "-------------------------------------------------------------------\n";
}

void console_ui::error_empty()
{
    cout << "Строка пустая, введите заново" << endl;
}

void console_ui::error_request_repeat()
{
    cout << "В строке ошибка, но вы можете продолжить ввод с этого места:" << endl;
}

void console_ui::output_word(request &r)
{
    vector <string> word = r.get_word();

    auto iter = word.begin();

    while (iter != word.end()) {
       cout <<  *iter << " ";
       ++iter;
    }
}

/*----------------------Парсер----------------------*/

void console_ui::error_parser_list()
{
    cout << "Нет совпадения с коректной командой" << endl;
}

void console_ui::error_db_command()
{
    cout << "Нет совпадения с database или table" << endl;
}

void console_ui::error_title_check_name()
{
    cout << "Нет совпадения с коректным именем" << endl;
}

void console_ui::error_from_command()
{
    cout << "Нет совпадения с from" << endl;
}

void console_ui::error_insert_request()
{
    cout << "Нет совпадения с into" << endl;
}

void console_ui::error_select_request_name()
{
    cout << "Нет совпадения с * или коректным именем" << endl;
}

void console_ui::error_select_request_size()
{
    cout << "Неверная длина строки" << endl;
}

void console_ui::error_set_command_set()
{
    cout << "Нет совпадения с set" << endl;
}

void console_ui::error_set_command_equal()
{
    cout << "Нет совпадения с = " << endl;
}

void console_ui::error_where_command()
{
    cout << "Нет совпадения с where" << endl;
}

void console_ui::error_alter_request_table()
{
    cout << "Нет совпадения с table" << endl;
}

void console_ui::error_alter_request_add()
{
    cout << "Нет совпадения с add" << endl;
}

void console_ui::error_alter_request_column()
{
    cout << "Нет совпадения с column" << endl;
}

/*----------------------Бд----------------------*/

void console_ui::error_exists_db()
{
    cout << "База данных с таким именем уже существует, введите запрос заново" << endl;
}

void console_ui::error_no_exists_db()
{
    cout << "База данных с таким именем не существует, введите запрос заново" << endl;
}

void console_ui::message_create_db()
{
    cout << "База данных успешно создана" << endl;
}

void console_ui::error_exists_table()
{
    cout << "Таблица с таким именем уже существует, введите запрос заново" << endl;
}

void console_ui::error_no_exists_table()
{
    cout << "Таблица с таким именем не существует, введите запрос заново" << endl;
}

void console_ui::error_before_use()
{
    cout << "Введите команду use и выберите базу данных" << endl;
}

void console_ui::message_create_table()
{
    cout << "Таблица успешно создана" << endl;
}

void console_ui::message_use_db()
{
    cout << "База данных успешно выбрана, можно передавать запросы" << endl;
}

void console_ui::message_drop_db()
{
    cout << "База данных успешно удалена" << endl;
}

void console_ui::message_drop_table()
{
    cout << "Таблица успешно удалена" << endl;
}

void console_ui::error_exists_field()
{
    cout << "Поле с таким именем уже существует, введите запрос заново" << endl;
}

void console_ui::error_no_exists_field()
{
    cout << "Поле с таким именем не существует, введите запрос заново" << endl;
}

void console_ui::message_alter_db()
{
    cout << "Поле успешно добавлено" << endl;
}

void console_ui::message_insert_db()
{
    cout << "Запись успешно добавлена" << endl;
}

void console_ui::error_no_exists_value()
{
    cout << "Поля с такими значениями не существуют, введите запрос заново" << endl;
}

void console_ui::message_delete_db()
{
    cout << "Запись успешно удалена" << endl;
}

void console_ui::error_no_change_id()
{
    cout << "Нельзя изменить поле со значением id, введите запрос заново" << endl;
}

void console_ui::message_update_db()
{
    cout << "Запись успешно изменена" << endl;
}

/*----------------------Вывод записи----------------------*/

void console_ui::output_select(vector <string> &select_data, string select_header)
{
    cout << "-----------------------------------" << endl;
    cout << select_header << endl;

    auto iter = select_data.begin();

    while (iter != select_data.end()) {
       cout <<  *iter << endl;
       ++iter;
    }
}
