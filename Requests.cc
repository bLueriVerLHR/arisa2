#include "Requests.h"

std::string requests::parameters::to_json() {
    std::string str;
    str += "{";
    for (auto &&[k, v]: params) {
        str += "\"" + k + "\":\"" + v + "\",";
    }
    str[str.size() - 1] = '}';
    return str;
}

void requests::query::set_app(std::string &&_app) {
    this->app = _app;
}

void requests::query::send(requests::parameters &params) {
    static std::list<std::string> header =
    {
        "Content-Type: application/json",
        "accept: application/json"
    }; 

    std::cout << params.to_json() << std::endl;
    std::string url = site + ":" + port + "/" + app;
    curl.setOpt(new curlpp::options::HttpHeader(header)); 
    curl.setOpt(std::make_unique<curlpp::options::Url>(url));
    curl.setOpt(std::make_unique<curlpp::options::PostFields>(params.to_json()));
    curl.perform();
    curl.reset();
}