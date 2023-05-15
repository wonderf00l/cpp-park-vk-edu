#include <drogon/drogon.h>
int main() {
    drogon::app().addListener("127.0.0.1", 1026);
    drogon::app().loadConfigFile("../config.json");
    drogon::app().run();
    return 0;
}
