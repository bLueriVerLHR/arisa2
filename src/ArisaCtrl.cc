#include <iostream>

#include "ArisaCtrl.h"
#include "arisa2.h"

extern arisa::qqbot botarisa;

void ArisaCtrl::asyncHandleHttpRequest(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback) {
  auto resp = HttpResponse::newHttpResponse();
  resp->setStatusCode(k200OK);
  botarisa.push(req->getJsonObject());
  callback(resp);
}