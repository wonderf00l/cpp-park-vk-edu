#include "Clusters.h"
#include <vector>
#include <string>

void Clusters::main(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_DEBUG << "someone is trying to get clusters list";

    Json::Value json;
    std::vector<std::string> clusters; // from db

    json["clusters"] = Json::arrayValue;

    for (const std::string& cluster : clusters) {
        json["clusters"].append(cluster);
    }

    json["status"] = "ok";
    
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    callback(resp);

    LOG_DEBUG << "got clusters list successfully";

}

void Clusters::groups(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_DEBUG << "someone is trying to get clusters groups list";

    Json::Value json;
    std::vector<std::string> groups; // from db

    json["cluster_groups"] = Json::arrayValue;

    for (const std::string& group : groups) {
        json["cluster_groups"].append(group);
    }

    json["status"] = "ok";
    
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(HttpStatusCode::k200OK);
    resp->setContentTypeCode(ContentType::CT_APPLICATION_JSON);
    callback(resp);

    LOG_DEBUG << "got clusters groups list successfully";
}
