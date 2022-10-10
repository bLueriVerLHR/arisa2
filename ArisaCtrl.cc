#include <iostream>

#include "ArisaCtrl.h"

void ArisaCtrl::asyncHandleHttpRequest(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    bot.handle(req);
    callback(resp);
}