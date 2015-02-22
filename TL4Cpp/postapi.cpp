//
//  postapi.cpp
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/22.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#include <map>

#include "clx/https.h"
#include "urlencode.h"

#include "postapi.h"

namespace tl4cpp {
    postapi::postapi(const oauth& _authorization, const std::string _apipath):
    apibase(_authorization,_apipath){
    }
    
    postapi::~postapi(){}
    
    void postapi::execute(const std::map<std::string, std::string>& parameters){
        std::string query = stringpair::array_to_string(stringpair::parsefrommap(parameters),"=","&");
        
        http_header["Authorization"] = authorization.header_post_www_form(APIURL_uri , parameters);
        http_header["Content-Type"] = "application/x-www-form-urlencoded";
        
        session.post(APIVERSION_uri + apipath, query, http_header);
        std::cout<<session.body()<<std::endl;
    }
}