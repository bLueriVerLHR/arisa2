#include <cstddef>
#include <regex>
#include <cstring>
#include <cstdio>
#include <string>

#include "ctre/ctre.hpp"

#include "plugin.h"

namespace arisa
{

bool Echo::match(Json::String &input) {
    static constexpr auto pattern = ctll::fixed_string{ "^/echo .*" };
    return !!ctre::match<pattern>(input);
}

Json::String Echo::act(const std::shared_ptr<Json::Value> &json) {
    auto raw_message = (*json)["raw_message"].asString();
    return raw_message.substr(6);
}

}