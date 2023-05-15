/**
 *
 *  settings_filter.h
 *
 */

#pragma once

#include <drogon/HttpFilter.h>
using namespace drogon;

class settings_filter : public HttpFilter<settings_filter> {
   public:
    settings_filter() {}
    void doFilter(const HttpRequestPtr &req, FilterCallback &&fcb, FilterChainCallback &&fccb) override;
};
