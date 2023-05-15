/**
 *
 *  signup_filter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;

class signup_filter : public HttpFilter<signup_filter> {
   public:
    signup_filter() {}
    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) override;
};
