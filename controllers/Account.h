#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Account : public drogon::HttpController<Account> {
   public:
    void signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void logout(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    
    void posts(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    
    void settings(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    
    void resume(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                std::string user_id);

    void groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    METHOD_LIST_BEGIN
    METHOD_ADD(Account::signup, "/signup", Post, "empty_body_filter", "signup_filter");
    METHOD_ADD(Account::login, "/login", Post, "empty_body_filter", "login_filter");  // url: /account/login
    METHOD_ADD(Account::logout, "/logout", Delete, "auth_filter");
    METHOD_ADD(Account::settings, "/settings", Post, Get, Patch, "empty_body_filter", "auth_filter");
    METHOD_ADD(Account::posts, "/posts", Post, Get, Delete, "empty_body_filter", "auth_filter");
    METHOD_ADD(Account::groups, "/groups", Get, Post, Delete, "empty_body_filter", 
               "auth_filter");  // post: group_id - patch, delete; get - groups list; post - list of user_id
    METHOD_ADD(Account::resume, "/{1}/resume", Get, "auth_filter");
    METHOD_LIST_END
};
