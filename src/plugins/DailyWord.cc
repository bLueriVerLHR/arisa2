#include "../plugin.h"
#include "../requests.h"

Json::String arisa::DailyWord::act(const std::shared_ptr<Json::Value> &json) {
  auto &&result = requests::get(
      "https://v.api.aa1.cn/api/api-wenan-mingrenmingyan/index.php?aa1=json");
  return result[0]["mingrenmingyan"].asString();
}