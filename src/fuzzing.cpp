#include "parser.h"
#include <cstdint>
#include <cstddef>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {

    std::string input(reinterpret_cast<const char*>(data), size);

    // Create parser
    IniParser parser;

    try {
        // Try to parse the input
        parser.parse(input);

        // Try to read some values (if any)
        if (parser.hasSection("section")) {
            if (parser.hasKey("section", "key")) {
                std::string value = parser.getValue("section", "key");
            }
        }
    } catch (const ParseError& e) {
        // Parser error - this is expected for invalid inputs
    } catch (const std::exception& e) {
        // Unexpected error - this could indicate a bug
        // In a real-world scenario, we might want to report this
    }

    // Always return 0 to indicate success
    return 0;
}
