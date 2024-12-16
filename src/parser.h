#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class ParseError : public runtime_error {
public:
    explicit ParseError(const string& message) : runtime_error(message) {}
};

class IniParser {
public:

    void parse(const string& content);

    string getValue(const string& section, const string& key) const;

    bool hasSection(const string& section) const;

    bool hasKey(const string& section, const string& key) const;

    void clear();

private:

    unordered_map<string, unordered_map<string, string>> data;

    string trim(const string& str) const;
    bool isComment(const string& line) const;
    bool isSection(const string& line) const;
    bool isKeyValue(const string& line) const;
    string extractSection(const string& line) const;
    pair<string, string> extractKeyValue(const string& line) const;
};

#endif
