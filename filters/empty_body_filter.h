/**
 *
 *  empty_body_filter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;

class empty_body_filter : public HttpFilter<empty_body_filter> {
   public:
    empty_body_filter() {}
    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) override;
};
