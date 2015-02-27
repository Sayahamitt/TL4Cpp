//
//  postmultipart.h
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/23.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#ifndef __TL4Cpp__postmultipart__
#define __TL4Cpp__postmultipart__

#include "apibase.h"

namespace tl4cpp {
    class postmultipart :public apibase{
    public:
        postmultipart(const oauth& _authorization, const std::string _apipath, const std::string _apidomein = "api.twitter.com");
        ~postmultipart();
        
        picojson::value request(const std::map<std::string,std::string>& _parameter, std::string paramoffile, std::string filepath);
    protected:
        const std::string APIURL_uri;
        
        void sessioninit();
        std::map<std::string,std::string> http_head(std::string auth_head);
        
        void execute(const std::map<std::string, std::string>& _parameters);
        void execute(const std::map<std::string, std::string>& _parameters, std::string paramoffile, std::string filedata);
        
        void post(const multipartform::multipart_type& _parameters);
    };
}

#endif /* defined(__TL4Cpp__postmultipart__) */