//
//  getapi.h
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/19.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#ifndef __TL4Cpp__getapi__
#define __TL4Cpp__getapi__

#include "apibase.h"

namespace tl4cpp {
    class getapi :public apibase{
    public:
        getapi(const oauth& _authorization, const std::string _apipath, const std::string _apidomein = "api.twitter.com");
        ~getapi();
        
    protected:
        void execute(const std::map<std::string, std::string>& parameters);
    };
}

#endif /* defined(__TL4Cpp__getapi__) */
