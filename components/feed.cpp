#include <iostream>
#include <vector>
#include <string>

struct User {
    int ID;
    std::string login;
    std::string password;
    std::string first_name;
    std::string second_name;
    std::string photo;
    int subscroptions;
    int subscribers;
    std::string creation_date;
    std::string birthday;
    std::string last_seen_claster;
};

struct Model {
    std::string Serialize();
    std::string Deserialize();
    void Set(std::string field, std::string value);
};

class ModelFabric {
public:
    static Model CreateModel(std::string model_name);
};

class Feed {
public:
    std::vector<Model> GetFeed(User user);
};