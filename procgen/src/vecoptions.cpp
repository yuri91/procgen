#include "vecoptions.h"
#include "cpp-utils.h"
#include <cstring>
#include <string>

VecOptions::VecOptions(client::Object* opts) {
    auto* keys = client::Object::keys(opts);
    auto* values = client::Object::values(opts);
    for (int i = 0; i < keys->get_length(); i++)
    {
        std::string k(*static_cast<client::String*>((*keys)[i]));
        libenv_option o;
        strcpy(o.name, k.c_str());
        bool isString = false, isNum = false, isBool = false;
        auto* v = (*values)[i];
        __asm__("typeof(%1) === 'string'" : "=r"(isString) : "r"(v));
        __asm__("typeof(%1) === 'number'" : "=r"(isNum) : "r"(v));
        __asm__("typeof(%1) === 'boolean'" : "=r"(isBool) : "r"(v));
        if (isString)
        {
            std::string s(*static_cast<client::String*>(v));
            o.count = s.size();
            o.data = new char[o.count];
            strcpy((char*)o.data, s.c_str());
            o.dtype = LIBENV_DTYPE_UINT8;
        }
        else if (isNum)
        {
            o.count = 1;
            o.data = new int(v->valueOf<int>());
            o.dtype = LIBENV_DTYPE_INT32;
        }
        else if (isBool)
        {
            o.count = 1;
            o.data = new unsigned char(v->valueOf<bool>());
            o.dtype = LIBENV_DTYPE_UINT8;
        }
        else
        {
            fatal("Option has wrong type: %s\n", o.name);
        }
        m_options.push_back(o);
    }
}

void VecOptions::consume_string(std::string name, std::string *value) {
    auto opt = find_option(name, LIBENV_DTYPE_UINT8);
    if (opt.data == nullptr) {
        return;
    }
    *value = std::string((char *)(opt.data), opt.count);
}

void VecOptions::consume_int(std::string name, int32_t *value) {
    auto opt = find_option(name, LIBENV_DTYPE_INT32);
    if (opt.data == nullptr) {
        return;
    }
    *value = *(int32_t *)(opt.data);
}

void VecOptions::consume_bool(std::string name, bool *value) {
    auto opt = find_option(name, LIBENV_DTYPE_UINT8);
    if (opt.data == nullptr) {
        return;
    }
    uint8_t v = *(uint8_t *)(opt.data);
    fassert(v == 0 || v == 1);
    *value = (bool)v;
}

void VecOptions::ensure_empty() {
    if (m_options.size() > 0) {
        fatal("unused options found, first unused option: %s\n", m_options[0].name);
    }
}

libenv_option VecOptions::find_option(std::string name, enum libenv_dtype dtype) {
    for (size_t idx = 0; idx < m_options.size(); idx++) {
        auto opt = m_options[idx];
        const std::string key(opt.name);
        if (key == name) {
            if (opt.dtype != dtype) {
                fatal("invalid dtype for option %s\n", name.c_str());
            }
            m_options.erase(m_options.begin() + idx);
            return opt;
        }
    }
    libenv_option result;
    result.data = nullptr;
    return result;
};
