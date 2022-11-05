#pragma once

#include <list>

#include <drogon/HttpSimpleController.h>

namespace arisa
{
struct regex_function
{
    virtual bool match(Json::String &input) = 0;
    virtual Json::String act(const std::shared_ptr<Json::Value> &json) = 0;
};

class qqbot
{
    void handleMessage(const std::shared_ptr<Json::Value> &json);

    void handleRequest(const std::shared_ptr<Json::Value> &json);

    void handleNotice(const std::shared_ptr<Json::Value> &json);
        void handleGroupRecall(const std::shared_ptr<Json::Value> &json);
        void handleNotify(const std::shared_ptr<Json::Value> &json);
            void handlePoke(const std::shared_ptr<Json::Value> &json);
            void handleLuckyKing(const std::shared_ptr<Json::Value> &json);

    void handleMeta(const std::shared_ptr<Json::Value> &json);

    std::list<std::unique_ptr<regex_function>> plugins;

public:
    qqbot();
    void handle(const drogon::HttpRequestPtr &req);
};

}
