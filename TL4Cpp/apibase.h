//
//  apibase.h
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/18.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#ifndef __TL4Cpp__apibase__
#define __TL4Cpp__apibase__

#include <iostream>
#include <map>
#include <string>

#include "../picojson.h"
#include "clx/https.h"

#include "oauth.h"
#include "stringpair.h"

namespace tl4cpp {
    class apibase{
    public:
        apibase(const tl4cpp::oauth& _authorization, const std::string _apipath);
        virtual ~apibase();
        
        const static std::string APIPROTOCOL_uri;
        const static std::string APIDOMEIN_uri;
        const static std::string APIVERSION_uri;
        
        picojson::value request(const std::map<std::string, std::string>& _parameter = std::map<std::string, std::string>());
        
    protected:
        const tl4cpp::oauth authorization;
        const std::string apipath;
        const std::string APIURL_uri;
        
        std::map<std::string, std::string> http_header;
        clx::https session = clx::https(APIDOMEIN_uri,443);
        
        virtual void execute(const std::map<std::string, std::string>&) = 0;
    };
}
#endif /* defined(__TL4Cpp__apibase__) */
