#include "../../ext/ctre.hpp"
#include "../plugin.h"

Json::String arisa::Echo::act(const std::shared_ptr<Json::Value> &json) {
  return (*json)["raw_message"].asString().substr(6);
}