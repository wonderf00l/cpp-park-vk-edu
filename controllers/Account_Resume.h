#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace Account {
class Resume : public drogon::HttpController<Resume> {
   public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(Resume::projects, "account/{1}/resume/projects?token={2}", Get, Post, Delete);
    METHOD_LIST_END

    void projects(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback,
                  std::string user_id, const std::string &token);
};
}  // namespace Account
