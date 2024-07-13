#ifndef PARSE_JSON_H_
#define PARSE_JSON_H_
#include <fstream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

using JSON_DATA=std::unordered_map<std::string,std::string>;

namespace JSON{
    inline void print(const JSON_DATA& data)noexcept
    {
        for(auto& el:data)
        {
            std::cout<<"key: "<<el.first<<" val: "<<el.second<<"\n";
        }
        std::cout<<std::flush; 
    }
    inline void print(const std::vector<JSON_DATA>& data)noexcept
    {
        for(auto& el:data)
        {
            std::cout<<"{\n";
            print(el);
            std::cout<< "}";
        }
        std::cout<<std::flush; 
    }
   
    inline std::vector<JSON_DATA> parseStr(const std::string& jsonTxt)noexcept
    {    
        std::vector<JSON_DATA> jsonList; 
        JSON_DATA json; 

        for(size_t i=0; i<jsonTxt.size();++i)
        {
            std::string key="";
            std::string value="";
            bool insideQuotes=false;
            if(i>0&&jsonTxt.at(i-1)=='{')while(i<jsonTxt.size()&&jsonTxt.at(i)!='}')
            {
                
            
                while(i<jsonTxt.size()&&jsonTxt.at(i)!=':')
                {
                    if(jsonTxt.at(i)=='"')insideQuotes=!insideQuotes;
                    if(jsonTxt.at(i)!=','&&insideQuotes&&jsonTxt.at(i)!='"')key+=jsonTxt.at(i);
                    i++;
                }
                i++;
                while(i<jsonTxt.size()&&jsonTxt.at(i)!=','&&jsonTxt.at(i)!='}')
                {
                if(jsonTxt.at(i)=='"')insideQuotes=!insideQuotes;
                if(jsonTxt.at(i)!='"'&&insideQuotes)value+=jsonTxt.at(i);
                i++;
                }
                if(key.size()>0&&value.size()>0)
                {
                    json.insert({key,value});
                    key="";value="";
                }
            }
            if(json.size()>0)
            {
                jsonList.push_back(json);
                json.erase(json.begin(),json.end());
            }
        }
        
        return jsonList; 
    }
    inline std::vector<JSON_DATA> parseFile(const std::string& path)noexcept
    {
        if(path.find(".json")==std::string::npos){std::cout<<"Files need to end in .json!!!\n"<<std::flush; exit(EXIT_FAILURE);}
        std::ifstream in{path.c_str(),std::ios::binary};
        std::string line=""; 
        std::vector<JSON_DATA> jsonList; 
        JSON_DATA json; 
        while(std::getline(in,line))
        {  
            const std::vector<JSON_DATA>& json_buffer=parseStr(line);
            jsonList.insert(jsonList.begin(),json_buffer.begin(),json_buffer.end());
            line="";
        }

        in.close();

        return jsonList; 
    }
    inline std::string parseJson(const std::vector<JSON_DATA>& data)noexcept
    {
        std::string ret=""; 
        for(auto& json:data)
        {
            ret+="{";
            for(auto& el:json)
            {
                ret+="\""+el.first+"\""+":"+"\""+el.second+"\""+",";
            }
            if(ret.size()>0)
            ret.pop_back();
            ret+="},";
        }
        if(ret.size()>0)
        ret.pop_back();
        return ret;
    }

};




#endif