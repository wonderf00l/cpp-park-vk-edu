#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <string>

struct date {
    std::string year;
    std::string month;
    std::string day;
};

int parse_args(int argc, char* argv[], std::string& art_path, std::string& art_t_path, std::string& gen_path, std::string& name) {
    
    if (argc == 2 && std::string_view{argv[1]} == "--help") {
        std::cout << "-a\tartist dataset path" << std::endl;
        std::cout << "-t\tartist_type dataset path" << std::endl;
        std::cout << "-g\tgender dataset path" << std::endl;
        return 0;
    }

    int arg = 0, error = 0;

    while ((arg = getopt(argc, argv, "a:t:g:n:")) != -1) {
        switch (arg) {
            case 'a': {
                if ((art_path = optarg) == "") {
                    std::cout << "NO ARTIST DATASET PATH!!!!!" << std::endl;
                    error = -1;
                }
                break;
            }
            case 't': {
                if ((art_t_path=optarg) == "") {
                    std::cout << "NO ARTIST TYPE DATASET PATH" << std::endl;
                    error = -1;
                }
                break;
            }
            case 'g': {
                if ((gen_path=optarg) == "") {
                    std::cout << "NO GENDER DATASET PATH" << std::endl;
                    error = -1;
                }
                break;
            }
            case 'n': {
                if ((name=optarg) == "") {
                    std::cout << "NO ARTIST NAME" << std::endl;
                    error = -1;
                }
                break;
            }
            case '?': {
                std::cout << "GOT UNKNOWN OPTION" << std::endl;
                error = -1;
                break;
            }
            default: {
                std::cout << (char)arg << std::endl;
                std::cout << "SMTH WENT WRONG WHILE PROCESSING COMMAND LINE ARGS" << std::endl;
                error = -1;
            }
        }
    }
    return error;
}

char* str_tokenize(const std::string& row, char** tok) {
    *tok = new char[row.length() + 1];
    std::strcpy(*tok, row.c_str());
    return std::strtok(*tok, "\t");
}


int main(int argc, char* argv[]) {

    setlocale(0, ".UTF8");

    std::string artist_path;
    std::string artist_t_path;
    std::string gender_path;
    std::string name;

    if (parse_args(argc, argv, artist_path, artist_t_path, gender_path, name) == -1) {
        return -1;
    }

    //std::cout << artist_path << "---" << artist_t_path << "---" << gender_path << "---" << name << std::endl;

    std::ifstream artist_dataset(artist_path);

    std::string row;

    bool was_found = 0;

    while (getline(artist_dataset, row)) {
        char* token = nullptr;

        token = str_tokenize(row, &token);
        
        for (int i = 0; token && i != 2; ++i) {
            token = std::strtok(nullptr, "\t");
        }

        std::cout << token << std::endl;
        //Abigale Undead

        date date_of_birth = {};

        date_of_birth.year = std::string(std::strtok(nullptr, "\t"));
        date_of_birth.month = std::string(std::strtok(nullptr, "\t"));
        date_of_birth.day = std::string(std::strtok(nullptr, "\t"));

        if (name == token) {

            std::cout << "??" << token << "??" << std::endl;


            for (int i = 0; token && i != 8; ++i) {
                token = std::strtok(nullptr, "\t");
            }
            std::cout << "??" << token << "??" << std::endl;

            if (std::stoi(token) == 1 || std::string(token) == "person" || std::string(token) == "Person") {
                
                std::cout << date_of_birth.year << "!!" << date_of_birth.month << "!!" << date_of_birth.day << std::endl;
            }

            was_found = 1;

            return 0;

            //std::ifstream artist_type_dataset(artist_t_path);


            // char* token_ = nullptr;

            // token_ = str_tokenize(row,);

        }
    }

    if (!was_found) {
        std::cout << "NO ARTIST" << std::endl;
    }

    artist_dataset.close();

}