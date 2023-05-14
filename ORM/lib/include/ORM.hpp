#pragma once
#include <string>

class ORM
{
public:
    static void Select(std::string table);
    static void Filter(std::string table, std::string parameter);
    static void Find(std::string table, std::string object_id);
    static void Delete(std::string table, std::string object_id);
    static void Insert(std::string table, std::string object);
    static void Update(std::string table, std::string objеct);

private:
    static bool ConnectionDB(std::string connection);
};