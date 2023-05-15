#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class Clusters : public drogon::HttpController<Clusters>
{
  public:
    void main(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);

    METHOD_LIST_BEGIN
    METHOD_ADD(Clusters::main, "", Get);
    METHOD_ADD(Clusters::groups, "/groups", Get);
    METHOD_LIST_END
};
