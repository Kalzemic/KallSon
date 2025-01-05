# KallSon
Custom C++ implementation of a JSON parser that can handle various data types, including numbers, strings, booleans, arrays, and objects. The parser processes a JSON-like structure from a string buffer and converts it into a union-based data structure called KallSon_data.

Features:

Union-based Data Storage: The KallSon_data union can store multiple data types, including primitive types, arrays, and objects.

Recursive Parsing: The parser handles nested arrays and objects recursively.

Type Enumeration: Enumerations are used to track the type of data being parsed (e.g., string, number, boolean).

Data Structures

KallSon_data

A union type used to store different types of data.

typedef union KallSon_data {
    int jint;
    double jdouble;
    char jchar;
    std::string jstring;
    float jfloat;
    bool jbool;
    std::vector<KallSon_data> jarr;
    std::map<std::string, KallSon_data> jobj;
};

TokenType and Head

Enumerations for representing the type of token and the current parsing head.

typedef enum TokenType {
    NONE, STRING, NUMBER, BOOLEAN, ARRAY, OBJECT
};
typedef enum Head { NONE, PAIR, ARRAY, OBJECT };

Functions

KallSon_data parse_value(auto start, auto end, std::string buffer)

Parses a single value from the buffer. It can handle strings, numbers, arrays, and objects.

Parameters:

start: Iterator pointing to the beginning of the value.

end: Iterator pointing to the end of the value.

buffer: The input string containing the JSON-like structure.

Logic:

Handles quoted strings, numeric values, arrays ([ ]), and objects ({ }).

Calls parse_array or parse_object when encountering arrays or objects, respectively.

KallSon_data parse_array(auto start, auto end, std::string buffer)

Parses an array from the buffer.

Parameters:

start: Iterator pointing to the beginning of the array.

end: Iterator pointing to the end of the array.

buffer: The input string containing the JSON-like structure.

Logic:

Initializes an empty jarr vector.

Iterates through the buffer and extracts individual values, handling nested arrays and objects.

KallSon_data parse_object(auto start, auto end, std::string buffer)

Parses an object from the buffer.

Parameters:

start: Iterator pointing to the beginning of the object.

end: Iterator pointing to the end of the object.

buffer: The input string containing the JSON-like structure.

Logic:

Extracts key-value pairs by identifying keys (within quotes) and values (separated by :).

Handles nested arrays and objects by calling parse_value recursively.

Example Usage

#include <iostream>
#include "KallSonParser.hpp"

int main() {
    std::string jsonBuffer = "{\"key1\": 123, \"key2\": [true, 45.6, \"string\"]}";
    auto start = jsonBuffer.begin();
    auto end = jsonBuffer.end();

    KallSon_data result = parse_value(start, end, jsonBuffer);
    // Process the parsed result

    return 0;
}

Build Instructions

Clone the repository:

git clone <repository_url>
cd <repository_directory>

Compile the code using a C++ compiler (e.g., g++):

g++ -std=c++11 main.cpp -o KallSonParser

Run the executable:

./KallSonParser

Limitations

The parser currently does not handle escaped characters in strings.

Error handling for malformed JSON is minimal and should be improved.

Contributing

Contributions are welcome! If you encounter any issues or have suggestions for improvement, feel free to open an issue or submit a pull request.

License

This project is licensed under the MIT License.
