#pragma once

#include <drogon/HttpSimpleController.h>

#include "arisa2.h"

using namespace drogon;

class ArisaCtrl
: public drogon::HttpSimpleController<ArisaCtrl>
{
    arisa::qqbot bot;
public:
    virtual void asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/", Get, Post);
    PATH_LIST_END
};
