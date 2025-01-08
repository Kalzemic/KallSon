#ifndef _KALLSON_
#define _KALLSON_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <new> // For placement new

union kallson_data {
    int jint;
    double jdouble;
    char jchar;
    std::string jstring;
    float jfloat;
    bool jbool;
    std::vector<kallson_data> jarr;
    std::map<std::string, kallson_data> jobj;
    enum class Type { NONE, INT, DOUBLE, CHAR, STRING, FLOAT, BOOL, ARRAY, OBJECT } type;
    // Default constructor
    kallson_data() : type(Type::NONE) {}

    // Destructor
    ~kallson_data() { clear(); }

    // Copy constructor
    kallson_data(const kallson_data& other) : type(Type::NONE) {
        copyFrom(other);
    }

    // Move constructor
    kallson_data(kallson_data&& other) noexcept : type(Type::NONE) {
        moveFrom(std::move(other));
    }

    // Copy assignment operator
    kallson_data& operator=(const kallson_data& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }
    kallson_data operator=(std::string str)
    {
        type=Type::STRING;
        jstring=str;
    }
    kallson_data operator=(int num)
    {
        type=Type::INT;
        jstring=num;
    }
    
    // Move assignment operator
    kallson_data& operator=(kallson_data&& other) noexcept {
        if (this != &other) {
            clear();
            moveFrom(std::move(other));
        }
        return *this;
    }

private:
    // Helper to destroy the active member
    void clear() {
        switch (type) {
            case Type::STRING: jstring.~basic_string(); break;
            case Type::ARRAY: jarr.~vector(); break;
            case Type::OBJECT: jobj.~map(); break;
            default: break; // Trivial types need no explicit destruction
        }
        type = Type::NONE;
    }

    // Helper to copy from another kallson_data
    void copyFrom(const kallson_data& other) {
        type = other.type;
        switch (type) {
            case Type::INT: jint = other.jint; break;
            case Type::DOUBLE: jdouble = other.jdouble; break;
            case Type::CHAR: jchar = other.jchar; break;
            case Type::STRING: new (&jstring) std::string(other.jstring); break;
            case Type::FLOAT: jfloat = other.jfloat; break;
            case Type::BOOL: jbool = other.jbool; break;
            case Type::ARRAY: new (&jarr) std::vector<kallson_data>(other.jarr); break;
            case Type::OBJECT: new (&jobj) std::map<std::string, kallson_data>(other.jobj); break;
            default: break;
        }
    }

    // Helper to move from another kallson_data
    void moveFrom(kallson_data&& other) noexcept {
        type = other.type;
        switch (type) {
            case Type::INT: jint = other.jint; break;
            case Type::DOUBLE: jdouble = other.jdouble; break;
            case Type::CHAR: jchar = other.jchar; break;
            case Type::STRING: new (&jstring) std::string(std::move(other.jstring)); break;
            case Type::FLOAT: jfloat = other.jfloat; break;
            case Type::BOOL: jbool = other.jbool; break;
            case Type::ARRAY: new (&jarr) std::vector<kallson_data>(std::move(other.jarr)); break;
            case Type::OBJECT: new (&jobj) std::map<std::string, kallson_data>(std::move(other.jobj)); break;
            default: break;
        }
        other.type = Type::NONE; // Leave the source in a valid state
    }
};

kallson_data parse_string(std::string::iterator start,std::string::iterator end);
kallson_data parse_value(std::string::iterator start,std::string::iterator end);
kallson_data parse_array(std::string::iterator start,std::string::iterator end);
kallson_data parse_object(std::string::iterator start,std::string::iterator end);
kallson_data parse_num(std::string::iterator start,std::string::iterator end);




#endif //_KALLSON_
