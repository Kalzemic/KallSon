#include "Kallson.hpp"
#include <string>
#include <map>
#include <vector>
#include<cctype>
#include <pair>



    
KallSon_data parse_value(auto start, auto end, std::string buffer)
{
    KallSon_data data;
    std::string value;
    int numvalue;
    for(start;start!=end;start++)
    {
        char p=*start;
        if(p=='"')
            inString=!inString;
        else if(inString) //case for value being a string
            {
                if(current!= STRING)
                    current= STRING;    
                 value+=p;
            }
            else if(!inString && std::isdigit(p)) //case for value being a number
            {
                if(current!=NUMBER)
                    current=NUMBER;
                numvalue=numvalue*10 +(int)p;
            } 
    
        else if(p=='{') //case for value being an object
        {   
            auto tmp=start+1;
            int bracketcount=1;
            do
            {
                start++;
                p=start;
                if(p=='{')
                    bracketcount++;
                if(p=='}')
                    bracketcount--;
            }while(bracketcount>=0)
            return parse_object(tmp,start-1,buffer);
        }
        else if(p=='[') //case for value being an array
        {   
            auto tmp=start+1;
            int bracketcount=1;
            do
            {
                start++;
                p=start;
                if(p=='[')
                    bracketcount++;
                if(p==']')
                    bracketcount--;
            }while(bracketcount>=0)
        return parse_array(tmp,start-1,buffer);
        }
    }
    if(current==STRING)
        data.jstring=value;
    if(current==NUMBER)
        data.jint=numvalue;
    return data;
}

KallSon_data parse_array(auto start, auto end, std::string buffer)
{
    KallSon_data data;
    data.jarr;
    auto ref=start;
    for(start;start!=end;start++)
    {
        p=*start;
        if(p==',')
        {
            data.jarr.push_back(parse_value(ref,start-1,buffer));   //handle single value
            ref=start;
        }
        else if(p=='{') //handle case where an array value is an object
        {   
            auto tmp=start+1;
            int bracketcount=1;
            do
            {
                start++;
                p=start;
                if(p=='{')
                    bracketcount++;
                if(p=='}')
                    bracketcount--;
            }while(bracketcount>=0)
            data.jarr.push_back(parse_object(tmp,start-1,buffer)); 
        }
        else if(p=='[')  //handle case where array value is an array itself
        {   
            auto tmp=start+1;
            int bracketcount=1;
            do
            {
                start++;
                p=start;
                if(p=='[')
                    bracketcount++;
                if(p==']')
                    bracketcount--;
            }while(bracketcount>=0)
        data.jarr.push_back(parse_array(tmp,start-1,buffer));
        }

    }
        return data;
}
KallSon_data parse_object(auto start, auto end, buffer)
{   boolean isKey=true;
    boolean inString=false;
    int braces=0;
    int brackets=0;
    std::string key;
    auto temp=start;
    std::pair<std::string,KallSon_data> pair;
    std::map<std::string,KallSon_data> data;
    for(start;start!=end;start++)
    {
        p=*start;
        if(p=='"')
        {
            inString=!inString;
        }
        else if(isKey && inString)
            key+=p;
        else if(p==":")
        {
            isKey=false;
        }
        else if(!isKey)
        {   auto tmp=start++;
            while(p!=',' || braces!=0 || brackets!=0)
            {
                
                p=*start;
                if(p=='{')
                    braces++;
                else if(p=='}')
                    braces--;
                else if(p=='[')
                    brackets++;
                else if(p==']')
                    brackets--;
                start++;
            }
            pair.first=key;
            pair.second=parse_value(tmp,start-1,buffer);
            data.jobj.insert(pair);
            isKey=true;
            key="";
            

        }
        

    }
    return data;
}