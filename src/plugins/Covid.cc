#include <sstream>

#include "../../ext/ctre.hpp"
#include "../plugin.h"
#include "../requests.h"

Json::String arisa::Covid::act(const std::shared_ptr<Json::Value> &json) {
  auto &&resp =
      requests::get("https://c.m.163.com/ug/api/wuhan/app/data/"
                    "list-by-area-code?areaCode=210000&t=1669200042738");
  auto &&data = resp["data"];
  std::stringstream oss;
  auto &&list = data["list"];
  auto &&liaoning = list[list.size() - 1];
  oss << "辽宁今日确诊: " << liaoning["today"]["confirm"].asInt64();
  return oss.str();
}