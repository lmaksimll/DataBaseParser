#include "request.h"

request::request()
{

}

bool request::set_word(string request_user)
{
    if(request_user == "")
    {
        return false;
    }

    istringstream iss(request_user);
    string tmp;
    while (iss >> tmp)
    {
        for (size_t i = 0; i < tmp.size(); ++i)
        {
           tmp[i] = tolower(tmp[i]);
        }
        word.push_back(tmp);
    }

    return true;
}

vector <string> request::get_word()
{
    return word;
}

void request::clear_word(string error)
{
    if(error == "")
    {
        word.clear();
    }
    else
    {
        auto iter = word.end()-1;

        do
        {
            word.erase(iter);
            --iter;
        }
        while (*iter != error);
    }
}
