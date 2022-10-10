# Arisa 2

## 简介

`Arisa2` 是一个基于 Drogon 和 curlpp 的 qq 机器人。其基础内容完全面向 go-cqhttp 的 http 模式。

## 简介

## 插件开发

目前插件开发非常的简陋。

### 对于新手

目前主要使用的机器人触发方式是满足正则表达式，然后执行函数。函数会按照加入顺序依次历遍，当满足一个正则表达式之后，就会执行函数，然后结束历遍，不再执行接下来的函数。

开发基础的聊天插件步骤如下：

1. 在 `plugin.h` 中的 `arisa` 命名空间声明一个公有继承 `regex_function` 的结构体，比如 `Test`。`regex_function` 有两个纯虚函数方法，需要在类中实现。
2. 其中 `match` 函数用于正则匹配。`act` 函数用于满足正则匹配后执行操作。

``` cpp
struct Test
: public regex_function
{
    bool match(Json::String &input);
    std::string act(const std::shared_ptr<Json::Value> &json);
};
```

3. 可以在 `plugin.cc` 文件中完成对 `Test` 结构体成员函数的定义。
4. 然后再在 `Arisa2.cc` 文件中，`arisa::qqbot::qqbot()` 这个构造函数中添加上 `ADD_PLUGIN(Test);` 插件就可以安装上了。

例如：

``` cpp
// plugin.cc
bool Test::match(Json::String &input) {
    const std::regex rgx("^早上好啊.*", std::regex_constants::ECMAScript);
    return std::regex_match(input, rgx);
}

Json::String Test::act(const std::shared_ptr<Json::Value> &json) {
    return "哦哈哟～～";
}
```

``` cpp
// Arisa2.cc
arisa::qqbot::qqbot() {
    ADD_PLUGIN(Echo);
    ADD_PLUGIN(Test);
}
```

接下来，如果 qqbot 接收到了一句以 `早上好啊` 开头的句子，就会进行回复。注意，所有的转义字符的反斜杠需要单独写出，否则会是非法 `json`。例如 `\n` 应该用 `\\n` 代替。

### 对于读得懂源代码的大佬

可以自由的配合 `go-cqhttp` 书写机器人。在写 `Arisa2` 的时候，我尽量让 `Drogon` 的网络部分使用占比保持非常小，以减少对新框架的学习成本。

## 配置说明

目前端口设置都是以硬编码形式设置。

该 `qqbot` 端口在 `main.cc` 内设置。`curlpp` 端口在 `Requests.h` 中，结构体 `query` 的初始化部分设置。