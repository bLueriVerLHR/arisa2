#include <cstddef>
#include <cstdio>
#include <cstring>
#include <regex>
#include <string>

#include "../ext/ctre.hpp"

#include "plugin.h"
#include "requests.h"

namespace {
  bool startwith(const char *src, const char *tgt) {
    return !strncmp(src, tgt, strlen(tgt));
  }
}

namespace arisa {

bool Echo::match(Json::String &input) {
  static constexpr auto pattern = ctll::fixed_string{"^/echo .+"};
  return !!ctre::match<pattern>(input);
}

Json::String Echo::act(const std::shared_ptr<Json::Value> &json) {
  return (*json)["raw_message"].asString().substr(6);
}

bool DailyWord::match(Json::String &input) {
  static constexpr auto pattern = ctll::fixed_string{"^/dw$"};
  return !!ctre::match<pattern>(input);
}

Json::String DailyWord::act(const std::shared_ptr<Json::Value> &json) {
  auto &&result = requests::get("https://v.api.aa1.cn/api/api-wenan-mingrenmingyan/index.php?aa1=json");
  return result[0]["mingrenmingyan"].asString();
}

} // namespace arisa