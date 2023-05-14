#pragma once
#include <string>
#include <fstream>

class DatabaseMOCK //заглушка для базы данных, которая возвращает данные о соответствие переданного кода, написанному ORM
{
public:
    static std::string execute(std::string &&request);
};