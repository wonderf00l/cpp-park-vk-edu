#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Account : public drogon::HttpController<Account> {
   public:
    void signup(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
               std::string &&user_id, const std::string &password);

    void settings(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                  std::string user_id, const std::string &token);

    void resume(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                std::string user_id);

    void groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                std::string user_id);

    METHOD_LIST_BEGIN
    METHOD_ADD(Account::signup, "/signup", Post);
    METHOD_ADD(Account::login, "/login?userId={1}&passwd={2}",
               Post);  // url: /account/login
    METHOD_ADD(Account::settings, "/{1}/settings/?token={2}", Post,
               Get);  // /account/{account_id}/settings?token=tok
    METHOD_ADD(Account::resume, "/{1}/resume", Get);
    METHOD_ADD(Account::groups, "/{1}/groups", Get);
    METHOD_LIST_END
};
