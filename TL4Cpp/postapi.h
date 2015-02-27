//
//  postapi.h
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/22.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#ifndef __TL4Cpp__postapi__
#define __TL4Cpp__postapi__

#include "apibase.h"

namespace tl4cpp {
    class postapi :public apibase{
    public:
        postapi(const oauth& _authorization, const std::string _apipath);
        ~postapi();
        
    protected:
        void execute(const std::map<std::string, std::string>& parameters);
        std::map<std::string,std::string> http_head(std::string auth_head);
    };
}

#endif /* defined(__TL4Cpp__postapi__) */
