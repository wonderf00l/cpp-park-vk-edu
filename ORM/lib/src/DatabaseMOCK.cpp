#include "DatabaseMOCK.hpp"

#include <iostream>
#include <string>
#include <fstream>

const std::string DIRECTORY_PATH = "../data/request.txt";

std::string DatabaseMOCK::execute(std::string &&request)
{
    std::ifstream requestSQL(DIRECTORY_PATH);

    if (requestSQL.bad())
        throw EXIT_FAILURE;

    std::string request_text = "";
    while (!requestSQL.eof())
    {
        std::string fileline;
        getline(requestSQL, fileline);
        request_text += fileline;
        if (!requestSQL.eof())
            request_text += '\n';
    }
    requestSQL.close();
    if (request == request_text)
        return "The request is correct!";
    else
        return "The request isn't correct!";
}