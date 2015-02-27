//
//  getapi.cpp
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/19.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//
#include <map>

#include "clx/https.h"

#include "getapi.h"

namespace tl4cpp {
    getapi::getapi(const oauth& _authorization, const std::string _apipath):
    apibase(_authorization,_apipath){
        sessioninit();
    }
    
    getapi::~getapi(){}
    
    void getapi::execute(const std::map<std::string, std::string>& parameters){
        std::string query = stringpair::array_to_string(stringpair::parsefrommap(parameters),"=","&");
        std::map<std::string,std::string> http_header = http_head(authorization.header_get(APIURL_uri , parameters));

        session->get(APIVERSION_uri + apipath + "?" + query, http_header);
        std::cout<<session->body()<<std::endl;
    }
}