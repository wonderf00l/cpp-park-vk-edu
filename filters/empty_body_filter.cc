/**
 *
 *  empty_body_filter.cc
 *
 */

#include "empty_body_filter.h"

using namespace drogon;

void empty_body_filter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                                 FilterChainCallback &&fccb) {
    if (auto req_body = req->getJsonObject();
        (req->getMethod() != HttpMethod::Get && req_body) || req->getMethod() == HttpMethod::Get) {
        fccb();
        return;
    }

    Json::Value json;
    json["status"] = "error";
    json["message"] = "body is required";
    auto response = HttpResponse::newHttpJsonResponse(json);
    response->setStatusCode(HttpStatusCode::k400BadRequest);
    fcb(response);
    return;
}
