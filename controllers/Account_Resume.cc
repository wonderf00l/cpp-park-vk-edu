#include "Account_Resume.h"

using namespace Account;

void Resume::projects(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string user_id, const std::string &token) {
    if (req->getMethod() == HttpMethod::Get) {
        LOG_DEBUG << "User " << user_id << " get list of projects";
        Json::Value json;
        json["status"] = HttpStatusCode::k200OK;
        json["projects_list"] = Json::arrayValue;
        json["projects_list"].append("proj1");
        json["projects_list"].append("proj2");
        auto resp = HttpResponse::newHttpJsonResponse(json);
        callback(resp);
    } else if (req->getMethod() == HttpMethod::Post) {
        // some logic
        LOG_DEBUG << "User " << user_id << " added some project to project list";
        Json::Value json;
        json["status"] = HttpStatusCode::k200OK;
        auto resp = HttpResponse::newHttpJsonResponse(json);
        callback(resp);
    } else if (req->getMethod() == HttpMethod::Delete) {
        // some logic
        LOG_DEBUG << "User " << user_id << " deleted some project from project list";
        Json::Value json;
        json["status"] = HttpStatusCode::k200OK;
        json["deleted project"] = "deleted project";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        callback(resp);
    }
}