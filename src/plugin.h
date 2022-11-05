#pragma once

#include "arisa2.h"

namespace arisa
{
struct Echo
: public regex_function
{
    bool match(Json::String &input);
    std::string act(const std::shared_ptr<Json::Value> &json);
};
}
