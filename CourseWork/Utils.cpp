#define _CRT_SECURE_NO_WARNINGS 1

#include <string>
#include "Utils.h"

const char* ws = " \t\n";

std::string& rtrim(std::string& s)
{
    s.erase(s.find_last_not_of(ws) + 1);
    return s;
}

std::string& ltrim(std::string& s)
{
    s.erase(0, s.find_first_not_of(ws));
    return s;
}

std::string& trim(std::string& s)
{
    return ltrim(rtrim(s));
}

std::string timeToString(time_t time) {
    tm tmTime = *localtime(&time);
    std::string s = std::to_string(tmTime.tm_hour);
    s += ":";
    s += std::to_string(tmTime.tm_min);
    s += ":";
    s += std::to_string(tmTime.tm_sec);
    s += " ";
    s += std::to_string(tmTime.tm_mday);
    s += "/";
    s += std::to_string(tmTime.tm_mon + 1);
    s += "/";
    s += std::to_string(tmTime.tm_year + 1900);
    return s;
}