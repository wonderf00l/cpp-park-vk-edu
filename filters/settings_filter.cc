/**
 *
 *  settings_filter.cc
 *
 */

#include "settings_filter.h"

using namespace drogon;

void settings_filter::doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) {
    // check validity of the settings fields
    //  check that all fields are in json
    if (1) {
        fccb();
        return;
    }
    auto res = drogon::HttpResponse::newHttpResponse();
    res->setStatusCode(k500InternalServerError);
    fcb(res);
}
