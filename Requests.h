#pragma once

#include <string>
#include <map>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>


namespace requests
{
struct parameters
{
    std::map<std::string, std::string> params;
    std::string to_json();
};

struct query
{
    curlpp::Easy curl;
    std::string site{"http://127.0.0.1"};
    std::string port{"5700"};
    std::string app;
    void set_app(std::string &&_app);
    void send(parameters &params);
};
}