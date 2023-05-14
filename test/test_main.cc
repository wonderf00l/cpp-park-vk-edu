#define DROGON_TEST_MAIN
#include <drogon/drogon.h>
#include <drogon/drogon_test.h>
using namespace drogon;

#define PORT_NUMBER 1026

DROGON_TEST(RegisterTest) {
    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Post);
        req->setBody("");
        req->setPath("http://localhost:1026/account/signup");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            // REQUIRE(res == ReqResult::Ok);
            // REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k400BadRequest);
            // CHECK(resp->contentType() == CT_APPLICATION_JSON);
            // auto resp_body = resp->getJsonObject();
            // CHECK((*resp_body)["message"] == "body is required");
        });
    }

    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Post);
        req->setBody(
            "{'login':'hello', 'email':'nice@yandex.ru', 'password':'gen', 'repeated_password':'gen'}");
        req->setPath("/account/signup");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k200OK);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["login"] == "hello");
            CHECK((*resp_body)["email"] == "email':'nice@yandex.ru");
            CHECK((*resp_body)["password"] == "gen");
            CHECK((*resp_body)["password"] == (*resp_body)["repeated_password"]);
        });
    }

    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Post);
        req->setBody("{'login':'hello', 'password':'gen', 'repeated_password':'gen'}");
        req->setPath("/account/signup");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k400BadRequest);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["message"] == "missing login/email/password");
        });
    }

    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Post);
        req->setBody(
            "{'login':'hello', 'email': '123@yandex.ru', 'password':'gen', 'repeated_password':'_gen_'}");
        req->setPath("/account/signup");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k400BadRequest);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["message"] == "wrong data");
        });
    }
}

DROGON_TEST(AuthTest) {
    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Post);
        // req->setParameter("login", "123");
        // req->setParameter("password", "pass");
        req->setPath("/account/login?userId=123&passwd=pass");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k200OK);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["message"] == "got verification");
        });
    }
}

DROGON_TEST(SettingsTest) {
    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Get);
        req->setPath("http://localhost:1026/account/exy/settings/?token=123");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k200OK);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["username"] == "Jack");
            CHECK((*resp_body)["user_id"] == "exy");
            CHECK((*resp_body)["gender"] == 1);
        });
    }
}

DROGON_TEST(GetResumeTest) {
    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Get);
        req->setPath("/account/exy/settings?token=tok");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k200OK);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["description"] == "resume description");
            CHECK((*resp_body)["content"] == "resume content");
        });
    }
}

DROGON_TEST(GetGroupsTest) {
    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Get);
        req->setPath("/account/exy/groups");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k200OK);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["groups_list_description"] == "group's list page");
        });
    }

    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Post);
        req->setPath("/account/exy/groups");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k200OK);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["message"] == "edited group list");
        });
    }
}

DROGON_TEST(ProjectsAPI) {
    {
        auto client = HttpClient::newHttpClient("http://localhost:65536");
        auto req = HttpRequest::newHttpRequest();
        req->setMethod(HttpMethod::Get);
        req->setPath("/account/exy/resume/projects?token=123");
        client->sendRequest(req, [TEST_CTX](ReqResult res, const HttpResponsePtr& resp) {
            REQUIRE(res == ReqResult::Ok);
            REQUIRE(resp != nullptr);
            CHECK(resp->getStatusCode() == k200OK);
            CHECK(resp->contentType() == CT_APPLICATION_JSON);
            auto resp_body = resp->getJsonObject();
            CHECK((*resp_body)["message"] == "edited group list");
        });
    }
}

int main(int argc, char** argv) {
    using namespace drogon;

    std::promise<void> p1;
    std::future<void> f1 = p1.get_future();

    // Start the main loop on another thread
    std::thread thr([&]() {
        // Queues the promise to be fulfilled after starting the loop
        app().getLoop()->queueInLoop([&p1]() { p1.set_value(); });
        app().run();
    });

    // The future is only satisfied after the event loop started
    f1.get();
    int status = test::run(argc, argv);

    // Ask the event loop to shutdown and wait
    app().getLoop()->queueInLoop([]() { app().quit(); });
    thr.join();
    return status;
}