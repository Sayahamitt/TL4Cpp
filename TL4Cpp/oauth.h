//
//  oauth.h
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/12.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#ifndef __TL4Cpp__oauth__
#define __TL4Cpp__oauth__

#include <iostream>
#include <vector>
#include <map>

#include "stringpair.h"

namespace tl4cpp {
    class oauth{
    public:
        typedef stringpair::stringpair_type param_type;
        typedef stringpair::stringpair_array param_array;
        
    private:
        const static std::string request_token_url;
        const static std::string authorize_url;
        const static std::string access_token_url;
        
        const static std::string c_key_key;
        const static std::string nonce_key;
        const static std::string sig_method_key;
        const static std::string signature_key;
        const static std::string timestamp_key;
        const static std::string oauth_version_key;
        const static std::string verifier_key;
        const static std::string token_key;
        
        const static std::string sig_method;
        const static std::string oauth_version;
        const std::string c_key;
        const std::string c_sec;
        
        std::string request_token;
        std::string request_token_sec;
        std::string access_token;
        std::string access_token_sec;
        
        std::string m_user_id;
        std::string m_screen_name;
        
        enum api_method_type{
            get,
            post,
            post_www_form,
            request,
            access
        };
        
        std::string create_header(const api_method_type& method,const std::string& url, const std::map<std::string,std::string>& _params) const;
        std::string Extractformbody(const std::string& holestring,const std::string& key) const;
        
        bool isempty;
        
    public:
        
        oauth(const std::string& a_c_key,const std::string& a_c_sec,const std::string& token,const std::string& token_sec);
        oauth(const std::string& a_c_key, const std::string& a_c_sec);
        oauth(const oauth &obj);
        oauth();
        
        ~oauth();
        
        oauth& operator=(const oauth& left);
        
        bool empty() const;
        
        std::string get_authorize_url();
        bool set_access_token(const std::string& pin);
        
        std::string getAccessToken() const;
        std::string getAccessTokenSecret() const;
        
        std::string header_get(const std::string& url,const std::map<std::string,std::string>& params) const;
        std::string header_post_www_form(const std::string& url,const std::map<std::string,std::string>& wwwFormDatas) const;
        std::string header_post(const std::string& url,const std::string& postdata) const;
    };
}

#endif /* defined(__TL4Cpp__oauth__) */
