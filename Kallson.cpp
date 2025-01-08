#include "Kallson.hpp"





kallson_data parse_string(std::string::iterator start, std::string::iterator  end)
{
    union kallson_data data;
    data.jstring="";
    char p=*start;
    while(p!= '"' && start!=end)
    {
        data.jstring+=p;
        start++;
        p=*start;
    }
    if(start==end)
    {
        std::cerr<<"Invalid Json" <<std::endl;
        return;
    }
    return data;
}
kallson_data parse_num(std::string::iterator  start, std::string::iterator  end)
{
    kallson_data data;
    data.jint=0;
    char p=*start;
    while(isdigit(p) && start!= end)
    {
        data.jint*=10;
        data.jint+=(int)(p-'0');
        start++;
        p=*start;
    }
   
    return data;
}

    
kallson_data parse_value(std::string::iterator start, std::string::iterator end, std::string buffer)
{
    if(start==end)
        {
            std::cout<< "End of File \n";
            return;
        }
    kallson_data data;
    std::string value;
    int numvalue;
    char p=*start;
    while(p==' ' ||p=='\n' || p=='\r')
    {
        start++;
        p=*start;
    }
    if(p=='"') // case s
    {
        data.jstring=parse_string(start,end).jstring;
    }
    else if( std::isdigit(p)) //case for value being a number
    {
        data.jint=parse_num(start,end).jint;
    }   
    
    else if(p=='{') //case for value being an object
    {   
       data.jobj=parse_object(start,end).jobj;
    }
    else if(p=='[') //case for value being an array
    {   
        data.jarr= parse_array(start,end).jarr;
    }
    while(p!=',' && p!=':' && start!= end)
    {
        start++;
        p=*start;
    }
    if(start==end)
    {
        std::cout<< "End of File \n";
        return;
    }
    return data;
    }
    

kallson_data parse_array(std::string::iterator start,std::string::iterator end)
{
    if (start == end || *start != '[') {
        std::cerr << "Error: Expected '[' to start an array." << std::endl;
        return;
    }
    start++;
    kallson_data data;
    data.jarr;
    data.type= kallson_data::Type::ARRAY;
    int bracketcounter=1;
    char p=*start;
    while(bracketcounter>0 || start!=end)
    {   
        switch(p)
        {
        case '[':
            bracketcounter++;
            break;
        case ']':
            bracketcounter--;
            break;
        case ',':
            break;
        default:
            data.jarr.push_back(parse_value(start,end));
            break;
        }
        start++;
        p=*start; 
    }
    return data;
}




kallson_data parse_object(std::string::iterator start, std::string::iterator end)
{
    
    start++;
    char p=*start;
    int bracescounter=1;
    kallson_data data;
    data.jobj;
    data.type=kallson_data::Type::OBJECT;
    std::pair<std::string,kallson_data> pair;
    std::string key;
    kallson_data temp;
    while(bracescounter>0 || start==end)
    {
        switch(p)
        {
            case '{':
                bracescounter++;
                break;
            case '}':
                bracescounter--;
                break;
            case ',':
                temp.jobj=parse_string(start,end).jobj;
                key=temp.jstring;
                break;
            case ':':
                temp=parse_value(start,end);
                data.jobj[key]=temp;
                break;
        }
        start++;
        p=*start;
    }
    if(start==end)
        {
            std::cout<< "End of File \n";
            return;
        }
    return data;
}

std::string fileToString(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return "";
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();  // Read file contents into buffer
    return buffer.str();     // Return the buffer as a string
}

kallson_data parse_json(const std::string& jsonpath)
{
    std::string jsonSTR= fileToString(jsonpath);
    auto start=jsonSTR.begin();
    auto end=jsonSTR.end();
    kallson_data kdata= parse_object(start, end);
}