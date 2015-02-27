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
    postapi::postapi(const oauth& _authorization, const std::string _apipath, const std::string _apidomein):
    apibase(_authorization,_apipath,_apidomein){
        sessioninit();
    }
    
    postapi::~postapi(){}
    
    std::map<std::string,std::string> postapi::http_head(std::string auth_head){
        std::map<std::string, std::string> _header;
        _header["Authorization"] = auth_head;
        _header["Content-Type"] = "application/x-www-form-urlencoded";
        _header["Connection"]="close";
        
        return _header;
    }
    
    void postapi::execute(const std::map<std::string, std::string>& parameters){
        std::string query = stringpair::array_to_string(stringpair::parsefrommap(parameters),"=","&");
        std::map<std::string, std::string> http_header = http_head(authorization.header_post_www_form(APIURL_uri , parameters));
        
        session->post(APIVERSION_uri + apipath, query, http_header);
        std::cout<<session->body()<<std::endl;
    }
}