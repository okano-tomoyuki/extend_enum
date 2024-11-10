#ifndef UTILITY_LEXIAL_ENUM_HPP
#define UTILITY_LEXIAL_ENUM_HPP

#include <string>
#include <vector>
#include <cassert>
#include <cstdint>

#define DEFINE_LEXIAL_ENUM(enum_name, underlying_type, ...)            \
    class enum_name                                                    \
    {                                                                  \
    public:                                                            \
        enum enum_name##Value : underlying_type                        \
        {                                                              \
            __VA_ARGS__                                                \
        };                                                             \
                                                                       \
        enum_name(const enum_name##Value &value)                       \
            : value_(value)                                            \
        {}                                                             \
                                                                       \
        enum_name(const enum_name &other)                              \
            : value_(other.value_)                                     \
        {}                                                             \
                                                                       \
        enum_name(const std::string& str)                              \
        {                                                              \
            from_str(str);                                             \
        }                                                              \
                                                                       \
        bool operator==(const enum_name &other)                        \
        {                                                              \
            return (value_ == other.value_);                           \
        }                                                              \
                                                                       \
        template <typename T>                                          \
        explicit operator T() const                                    \
        {                                                              \
            return static_cast<T>(value_);                             \
        }                                                              \
                                                                       \
        std::string to_str() const                                     \
        {                                                              \
            const auto &key_list = enum_list();                        \
            const auto &val_list = name_list();                        \
            assert(key_list.size() == val_list.size());                \
            for (int i = 0; i < key_list.size(); i++)                  \
            {                                                          \
                if (key_list[i] == value_)                             \
                {                                                      \
                    return val_list[i];                                \
                }                                                      \
            }                                                          \
            return std::string();                                      \
        }                                                              \
                                                                       \
        enum_name &from_str(const std::string &name)                   \
        {                                                              \
            const auto &key_list = name_list();                        \
            const auto &val_list = enum_list();                        \
            assert(key_list.size() == val_list.size());                \
            std::string base(#enum_name "::");                         \
            for (int i = 0; i < key_list.size(); i++)                  \
            {                                                          \
                if (key_list[i] == name || key_list[i] == base + name) \
                {                                                      \
                    value_ = val_list[i];                              \
                    break;                                             \
                }                                                      \
            }                                                          \
            return *this;                                              \
        }                                                              \
                                                                       \
    private:                                                           \
        enum_name##Value value_;                                       \
                                                                       \
        const std::vector<enum_name##Value> enum_list() const          \
        {                                                              \
            return {__VA_ARGS__};                                      \
        }                                                              \
                                                                       \
        const std::vector<std::string> name_list() const               \
        {                                                              \
            const char *args = #__VA_ARGS__;                           \
            std::vector<std::string> name_list;                        \
            std::string base(#enum_name "::");                         \
            std::string name;                                          \
            while (*args != '\0')                                      \
            {                                                          \
                if (*args == ',')                                      \
                {                                                      \
                    name_list.push_back(base + name);                  \
                    name.clear();                                      \
                }                                                      \
                else if (*args != ' ')                                 \
                {                                                      \
                    name.push_back(*args);                             \
                }                                                      \
                args++;                                                \
            }                                                          \
            name_list.push_back(base + name);                          \
            return name_list;                                          \
        }                                                              \
    };

#endif