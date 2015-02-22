//
//  apibase.cpp
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/19.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#include "apibase.h"


namespace tl4cpp {
    apibase::apibase(const tl4cpp::oauth& _authorization, const std::string _apipath):
    authorization(_authorization),
    apipath(_apipath),
    APIURL_uri(APIPROTOCOL_uri + APIDOMEIN_uri + APIVERSION_uri + apipath){
        http_header["Connection"]="close";
    }
    
    const std::string apibase::APIPROTOCOL_uri = "https://";
    const std::string apibase::APIDOMEIN_uri = "api.twitter.com";
    const std::string apibase::APIVERSION_uri = "/1.1";
    
    apibase::~apibase(){}
    
    picojson::value apibase::request(const std::map<std::string, std::string>& _parameter){
        execute(_parameter);
        
        picojson::value result;
        std::string err;
        picojson::parse(result, session.body().begin(), session.body().end(),&err);

        return result;
    }
}