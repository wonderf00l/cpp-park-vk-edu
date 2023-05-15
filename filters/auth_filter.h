/**
 *
 *  auth_filter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;

class auth_filter : public HttpFilter<auth_filter> {
   public:
    auth_filter() {}
    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) override;
};
