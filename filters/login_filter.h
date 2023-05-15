/**
 *
 *  login_filter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;

class login_filter : public HttpFilter<login_filter> {
   public:
    login_filter() {}
    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) override;
};
