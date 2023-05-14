#include "TestCtrt.h"

void TestCtrt::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                      std::function<void(const HttpResponsePtr &)> &&callback) {
    auto response = HttpResponse::newHttpResponse();
    response->setStatusCode(k200OK);
    response->setContentTypeCode(CT_TEXT_HTML);
    response->setBody("Welcome to Increa!");
    callback(response);
}
