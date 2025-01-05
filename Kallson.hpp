typedef union Kallson_data
{
    int jint;
    double jdouble;
    char jchar;
    std::string jstring;
    float jfloat;
    bool jbool;
    std::vector<Kallson_data> jarr;
    std::map<std::string,Kallson_data> jobj;
};

typedef enum TokenType
{
    NONE, STRING,NUMBER,BOOLEAN,ARRAY, OBJECT
};
