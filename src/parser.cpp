#include "parser.h"
#include <sstream>
#include <algorithm>

using namespace std;

void IniParser::parse(const string& content) {
    clear();

    string currentSection = "default";
    istringstream stream(content);
    string line;
    int lineNumber = 0;

    while (getline(stream, line)) {
        lineNumber++;

        // Skip empty lines and comments
        line = trim(line);
        if (line.empty() || isComment(line)) {
            continue;
        }

        // Handle section
        if (isSection(line)) {
            currentSection = extractSection(line);
            continue;
        }

        // Handle key-value pair
        if (isKeyValue(line)) {
            auto [key, value] = extractKeyValue(line);
            data[currentSection][key] = value;
            continue;
        }

        // error
        throw ParseError("Invalid format at line " + to_string(lineNumber) + ": " + line);
    }
}

string IniParser::getValue(const string& section, const string& key) const {
    if (!hasKey(section, key)) {
        throw out_of_range("Key '" + key + "' not found in section '" + section + "'");
    }
    return data.at(section).at(key);
}

bool IniParser::hasSection(const string& section) const {
    return data.find(section) != data.end();
}

bool IniParser::hasKey(const string& section, const string& key) const {
    return hasSection(section) && data.at(section).find(key) != data.at(section).end();
}

void IniParser::clear() {
    data.clear();
}

string IniParser::trim(const string& str) const {
    auto start = find_if_not(str.begin(), str.end(), [](char c) { return isspace(c); });
    auto end = find_if_not(str.rbegin(), str.rend(), [](char c) { return isspace(c); }).base();

    if (start >= end) {
        return "";
    }

    return string(start, end);
}

bool IniParser::isComment(const string& line) const {
    return !line.empty() && (line[0] == ';' || line[0] == '#');
}

bool IniParser::isSection(const string& line) const {
    return line.size() >= 3 && line.front() == '[' && line.back() == ']';
}

bool IniParser::isKeyValue(const string& line) const {
    return line.find('=') != string::npos;
}

string IniParser::extractSection(const string& line) const {
    return trim(line.substr(1, line.size() - 2));
}

pair<string, string> IniParser::extractKeyValue(const string& line) const {
    size_t pos = line.find('=');
    if (pos == string::npos) {
        throw ParseError("Invalid key-value pair: " + line);
    }

    string key = trim(line.substr(0, pos));
    string value = trim(line.substr(pos + 1));

    return {key, value};
}
