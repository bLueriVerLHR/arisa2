#include <curl/curl.h>
#include <json/json.h>

namespace requests {
void initRequests();

struct post_interface {
  const char *addr{nullptr};
  const Json::Value *json{nullptr};
};

Json::Value get(const char *addr);

Json::Value post(const char *addr, const Json::Value &json);
Json::Value post(const post_interface &&pinf);
}; // namespace requests