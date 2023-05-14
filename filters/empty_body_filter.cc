/**
 *
 *  empty_body_filter.cc
 *
 */

#include "empty_body_filter.h"

using namespace drogon;

void empty_body_filter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb,
                                 FilterChainCallback &&fccb) {
    if (auto req_body = req->getJsonObject(); req_body) {
        fccb();
        return;
    }

    Json::Value json_body;
    json_body["status"] = "error";
    json_body["message"] = "body is required";
    auto response = HttpResponse::newHttpJsonResponse(json_body);
    response->setStatusCode(HttpStatusCode::k400BadRequest);
    fcb(response);
    return;
}
