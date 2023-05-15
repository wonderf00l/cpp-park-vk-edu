#include "Account.h"

#include <trantor/utils/Date.h>

#include <unordered_map>
#include <vector>

void Account::signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    Json::Value json;

    LOG_DEBUG << "User is trying to register";

    // id ?
    std::string login = req->getParameter("login");
    std::string password = req->getParameter("password");
    std::string email = req->getParameter("email");
    trantor::Date date = trantor::Date::date();
    std::string creation_date = date.toDbString();
    bool is_logged_in = 0;

    std::unordered_map<std::string, std::string> db_field;
    db_field["login"] = login;
    db_field["password"] = password;
    db_field["email"] = email;
    db_field["creation_date"] = creation_date;
    db_field["logged_in"] = is_logged_in;
    // serialize
    // GO TO DB and register

    json["status"] = "ok";
    json["message"] = "registeted " + login;
    json["email"] = email;
    json["creation_date"] = creation_date;

    LOG_DEBUG << "User " << login << "registered successfully";

    auto response = HttpResponse::newHttpJsonResponse(json);
    response->setStatusCode(HttpStatusCode::k200OK);
    response->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    callback(response);
}

void Account::login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    // Authentication algorithm, read database, verify, identify, etc...
    //...

    auto request_body = req->getJsonObject();

    Json::Value login = (*request_body)["login"];
    Json::Value password = (*request_body)["password"];

    LOG_DEBUG << "User " << login.asString() << " trying to log in";
    Json::Value json;

    // GO TO DB AND CHECK LOGIN&PASSW

    bool is_logged_in = 1;

    json["status"] = "ok";
    json["message"] = "got verification";
    json["token"] =
        drogon::utils::base64Encode(reinterpret_cast<const unsigned char *>(login.asString().c_str()), login.asString().size());
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    LOG_DEBUG << "User " << login.asString() << " logged in successfully";
    callback(resp);
}

void Account::logout(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    
    std::string login = drogon::utils::base64Decode(req->getHeader("Authorization"));
    
    LOG_DEBUG << "User "<< login << "is trying to log out";

    bool is_logged_in = 0;

    // WRITE TO DB

    Json::Value json;
    json["status"] = "ok";
    json["message"] = "log out: successful for " + login;
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    LOG_DEBUG << "User logged out successfully";
    callback(resp);
}

void Account::settings(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    // Verify the validity of the token, etc.
    // Read the database or cache to get user information

    // also post/put/patch to edit profile settings

    Json::Value json;
    auto request_body = req->getJsonObject();
    std::string login = drogon::utils::base64Decode(req->getHeader("Authorization"));
    // now we can define what user settnigs we whould get from db
    std::string first_name, last_name, clusters, creation_date, birthday, gender;

    if (req->getMethod() == HttpMethod::Get) {
        LOG_DEBUG << "User " << login << " is getting his account settings";

        // first_name = ... , etc

        json["status"] = "ok";
        json["login"] = login;
        json["first_name"] = first_name;
        json["last_name"] = last_name;
        json["clusters"] = clusters;
        json["birthday"] = birthday;
        json["gender"] = gender;
        json["creation_date"] = creation_date;
    
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        callback(resp);
    } else if (req->getMethod() == HttpMethod::Post) {
        LOG_DEBUG << "User " << login << " is trying to define account settings";

        //std::string new_first_name = (*request_body)["first_name"].asString();
        // check if cluster is in db, birth date format

        json["message"] = "successfully defined account settings for " + login;
        json["status"] = "ok";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        callback(resp);
    } else if (req->getMethod() == HttpMethod::Patch) {
        LOG_DEBUG << "User " << login << " is trying to edit account settings";

        if (request_body->isMember("login")) {
            std::string new_login = (*request_body)["login"].asString();
            // go to db and change login
            //  ...
        }

        json["status"] = "ok";
        json["message"] = "settings fields have been edited";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(resp);
    }
}

void Account::posts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {

    std::string login = drogon::utils::base64Decode(req->getHeader("Authorization"));
    auto request_body = req->getJsonObject();
    Json::Value json;

    if (req->getMethod() == HttpMethod::Get) {

        LOG_DEBUG << "User " << login << "is trying to get his posts";

        std::vector<std::string> posts; // from db
        json["posts"] = Json::arrayValue;

        for (const std::string& post : posts) {
            json["posts"].append(post);
        }

        json["status"] = "ok";
        
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(resp);

    }
    else if (req->getMethod() == HttpMethod::Post) {
        LOG_DEBUG << "User " << login << " is trying to set some posts";

        Json::Value posts = (*request_body)["posts"];
        std::vector<std::string> posts_list(posts.size());

        for (unsigned int i = 0; i != posts.size(); ++i) {
            posts_list[i] = posts[i].asString();
        }
       
        for (const std::string& post : posts_list) {
            LOG_DEBUG << post << " ";
        }

        json["status"] = "ok";
        json["message"] = "posts have been set successfully";

        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(resp);

    }
    else if (req->getMethod() == HttpMethod::Delete) {
        LOG_DEBUG << "User " << login << " is trying to delete some posts";
        
        Json::Value posts_to_del = (*request_body)["posts"];
        std::vector<std::string> posts_list(posts_to_del.size());
        for (unsigned int i = 0; i != posts_to_del.size(); ++i) {
            posts_list[i] = posts_to_del[i].asString();
        }

        // go to db and delete

        json["status"] = "ok";
        json["message"] = "posts have been deleted successfully";

        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(resp);
    }

}

void Account::groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {

    std::string login = drogon::utils::base64Decode(req->getHeader("Authorization"));
    auto request_body = req->getJsonObject();
    Json::Value json;

    if (req->getMethod() == HttpMethod::Get) {

        LOG_DEBUG << "User " << login << "is trying to get his groups";

        std::vector<std::string> groups; // from db
        json["groups"] = Json::arrayValue;

        for (const std::string& group : groups) {
            json["groups"].append(group);
        }

        json["status"] = "ok";
        
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(resp);

    }
    else if (req->getMethod() == HttpMethod::Post) {
        LOG_DEBUG << "User " << login << " is trying to set some groups";

        Json::Value groups = (*request_body)["groups"];
        std::vector<std::string> groups_list(groups.size());

        for (unsigned int i = 0; i != groups.size(); ++i) {
            groups_list[i] = groups[i].asString();
        }
       
        for (const std::string& group : groups_list) {
            LOG_DEBUG << group << " ";
        }

        json["status"] = "ok";
        json["message"] = "groups have been set successfully";

        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(resp);

    }
    else if (req->getMethod() == HttpMethod::Delete) {
        LOG_DEBUG << "User " << login << " is trying to delete some groups";
        
        Json::Value groups_to_del = (*request_body)["groups"];
        std::vector<std::string> groups_list(groups_to_del.size());
        for (unsigned int i = 0; i != groups_to_del.size(); ++i) {
            groups_list[i] = groups_to_del[i].asString();
        }

        // go to db and delete

        json["status"] = "ok";
        json["message"] = "groups have been deleted successfully";

        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(HttpStatusCode::k200OK);
        resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
        callback(resp);
    }
}


void Account::resume(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                     std::string user_id) {
    LOG_DEBUG << "User " << user_id << " get his resume";

    Json::Value json;
    json["status"] = HttpStatusCode::k200OK;
    json["description"] = "resume description";
    json["content"] = "resume content";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
