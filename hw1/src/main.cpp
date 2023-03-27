#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>

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
                    std::cout << "NO ARTIST DATASET PATH" << std::endl;
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

int main(int argc, char* argv[]) {

    std::string artist_path;
    std::string artist_t_path;
    std::string gender_path;
    std::string name;

    if (parse_args(argc, argv, artist_path, artist_t_path, gender_path, name) == -1) {
        return -1;
    }

    //std::cout << artist_path << "---" << artist_t_path << "---" << gender_path << "---" << name << std::endl;

}