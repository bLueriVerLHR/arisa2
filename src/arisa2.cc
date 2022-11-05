#include <drogon/HttpRequest.h>
#include <json/json.h>

#include "arisa2.h"
#include "plugin.h"
#include "selfdef.h"
#include "requests.h"

#define ADD_PLUGIN(name) plugins.push_back(std::make_unique<name>())

arisa::qqbot::qqbot() {
    ADD_PLUGIN(Echo);
}

void arisa::qqbot::handle(const drogon::HttpRequestPtr &req) {
    auto json_resp = req->getJsonObject();
    auto post_type = (*json_resp)["post_type"].asString();
    printf("post_type: %s\n", post_type.c_str());

    if (post_type == "message") {
        handleMessage(json_resp);
    } else if (post_type == "request") {
        handleRequest(json_resp);
    } else if (post_type == "notice") {
        handleNotice(json_resp);
    } else if (post_type == "meta_event") {
        handleMeta(json_resp);
    }
}

void arisa::qqbot::handleMessage(const std::shared_ptr<Json::Value> &json) {
    auto raw_message = (*json)["message"].asString();
    
    for (auto &&func: plugins) {
        if (func && func->match(raw_message)) {
            auto &&msg = func->act(json);
            std::cout << msg;
            Json::Value req_json;
            req_json["group_id"] = (*json)["group_id"].asString();
            req_json["message"] = msg;
            // std::cout << req_json.toStyledString() << std::endl;
            std::string req_addr(BOT_STRING);
            req_addr += "/send_group_msg";
            requests::post(req_addr.c_str(), req_json);
            break;
        }
    }
}

void arisa::qqbot::handleRequest(const std::shared_ptr<Json::Value> &json) {
    
}

void arisa::qqbot::handleNotice(const std::shared_ptr<Json::Value> &json) {
    auto notice_type = (*json)["notice_type"].asString();
    printf(" notice_type: %s\n", notice_type.c_str());
    if (notice_type == "group_recall") {
        handleGroupRecall(json);
    } else if (notice_type == "notify") {
        handleNotify(json);
    }
}

void arisa::qqbot::handleGroupRecall(const std::shared_ptr<Json::Value> &json) {
    static const char *answers[]
    {
        "啊咧咧，刚刚说了什么鸭？",
        "Typo了吗？",
        "别撤回鸭，多见外",
        "嘿嘿，害羞了吧？",
    };
    static const auto answer_sz = sizeof(answers) / sizeof(answers[0]);
    if (rand() % 3)
        return;

    Json::Value req_json;
    req_json["group_id"] = (*json)["group_id"].asString();
    req_json["message"] = answers[rand() % answer_sz];
    std::string req_addr(BOT_STRING);
    req_addr += "/send_group_msg";
    requests::post(req_addr.c_str(), req_json);
}

void arisa::qqbot::handleNotify(const std::shared_ptr<Json::Value> &json) {
    auto sub_type = (*json)["sub_type"].asString();
    printf("  sub_type: %s\n", sub_type.c_str());
    if (sub_type == "poke") {
        handlePoke(json);
    } else if (sub_type == "lucky_king") {
        handleLuckyKing(json);
    }
}

void arisa::qqbot::handlePoke(const std::shared_ptr<Json::Value> &json) {
    printf("Poke\n");
    auto target_id = (*json)["target_id"].asInt64();
    auto self_id = (*json)["self_id"].asInt64();
    auto sender_id = (*json)["sender_id"].asInt64();

    if (self_id == sender_id || self_id != target_id)
        return;

    Json::Value req_json;
    req_json["group_id"] = (*json)["group_id"].asString();
    req_json["message"] = "[CQ:poke,qq=" + (*json)["sender_id"].asString() + "]";
    std::string req_addr(BOT_STRING);
    req_addr += "/send_group_msg";
    requests::post(req_addr.c_str(), req_json);
}

void arisa::qqbot::handleLuckyKing(const std::shared_ptr<Json::Value> &json) {
    printf("Lucky King\n");
}

void arisa::qqbot::handleMeta(const std::shared_ptr<Json::Value> &json) {
    
}