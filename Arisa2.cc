#include "Arisa2.h"
#include "plugin.h"

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
            requests::parameters pms;
            pms.params["group_id"] = (*json)["group_id"].asString();
            pms.params["message"] = msg;
            qy.set_app("send_group_msg");
            qy.send(pms);
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
    static std::vector<std::string> answers
    {
        "啊咧咧，刚刚说了什么鸭？",
        "Typo了吗？",
        "别撤回鸭，多见外",
        "嘿嘿，害羞了吧？",
    };
    if (rand() % 3)
        return;
    requests::parameters pms;
    pms.params["group_id"] = (*json)["group_id"].asString();
    pms.params["message"] = answers[rand() % answers.size()];
    qy.set_app("send_group_msg");
    qy.send(pms);
    pms.params.clear();
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

    requests::parameters pms;
    pms.params["group_id"] = (*json)["group_id"].asString();
    pms.params["message"] = "[CQ:poke,qq=" + (*json)["sender_id"].asString() + "]";
    qy.set_app("send_group_msg");
    qy.send(pms);
    pms.params.clear();
}

void arisa::qqbot::handleLuckyKing(const std::shared_ptr<Json::Value> &json) {
    printf("Lucky King\n");
}

void arisa::qqbot::handleMeta(const std::shared_ptr<Json::Value> &json) {
    
}