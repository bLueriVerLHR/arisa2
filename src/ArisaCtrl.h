#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class ArisaCtrl : public drogon::HttpSimpleController<ArisaCtrl> {
public:
  virtual void asyncHandleHttpRequest(
      const HttpRequestPtr &req,
      std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/", Get, Post);
  PATH_LIST_END
};
