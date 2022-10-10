#include <cstddef>
#include <regex>
#include <cstring>
#include <cstdio>
#include <string>

#include "plugin.h"

namespace arisa
{

bool Echo::match(Json::String &input) {
    const std::regex rgx("^/echo .*", std::regex_constants::ECMAScript);
    return std::regex_match(input, rgx);
}

Json::String Echo::act(const std::shared_ptr<Json::Value> &json) {
    auto raw_message = (*json)["raw_message"].asString();
    return raw_message.substr(6);
}

}