#include <cassert>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>

#include "requests.h"

#define val const auto &&
#define var auto &&

// static CURLM *curlm;

// static void _curl_multi_cleanup_()
// {
//     curl_multi_cleanup(curlm);
// }

void requests::initRequests()
{
    assert(!curl_global_init(CURL_GLOBAL_ALL) && "Failed to initialize curl_multi_init.\n");
    atexit(curl_global_cleanup);
    // curlm = curl_multi_init();
    // assert(curlm && "Failed to initialize curl_multi_init.\n");
    // atexit(_curl_multi_cleanup_);
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) 
{
    std::string data((const char*) ptr, (size_t) size * nmemb);

    *((std::stringstream*) stream) << data << std::endl;

    return size * nmemb;
}

Json::Value requests::post(const char *addr, const Json::Value &json) {
    var curl = curl_easy_init();
    std::stringstream out;

    std::cout << addr << std::endl;
    std::cout << json.toStyledString() << std::endl;
    if (!curl) {
        fprintf(stderr, "curl_easy_init failed.\n");
        return Json::Value{ };
    }
    curl_easy_setopt(curl, CURLOPT_URL, addr);
    
    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type:application/json;charset=UTF-8");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    var jstr = json.toStyledString();
    // curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jstr.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(jstr.c_str()));

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

    val resCode = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    std::string str_json = out.str();
    printf("%s", str_json.c_str());
    curl_easy_cleanup(curl);
    curl = nullptr;

    return Json::Value(out.str().c_str());
}

Json::Value requests::post(const post_interface &&pinf) {
    const auto &addr = pinf.addr;
    const auto &json = *(pinf.json);
    return post(addr, json);
}