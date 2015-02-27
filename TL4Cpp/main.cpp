//
//  main.cpp
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/07.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#include <iostream>
#include <string>

#include "clx/https.h"
#include "clx/uri.h"

#include "multipartform.h"

#include "oauth.h"
#include "getapi.h"
#include "postapi.h"
#include "postmultipart.h"

#include "keys.h"

void postimagetest(){
    tl4cpp::oauth certifyer(c_key,c_sec,my_access_token,my_access_sec);
    tl4cpp::postmultipart mediapost(certifyer,"/media/upload.json");
    
    mediapost.request(std::map<std::string, std::string>(), "media", "/Volumes/Working Data/Gentle Sheep/CppTwiLib/testmedia.png");
}

int main() {
    //postimagetest();
    /*
    
    std::pair<std::string,std::string> _pair("this is picture","application/octet-stream");
    std::pair<std::string,std::string> _pair2("hello my status","");
    std::pair<std::string,std::string> _pair3("this is picture","application/octet-stream");
    std::map<std::string,std::pair<std::string,std::string>> test;
    test["media"]=_pair;
    test["status"]=_pair2;
    test["media2"]=_pair3;
    std::cout<<tl4cpp::multipartform::makebody(test, tl4cpp::multipartform::strrand(32));
    
    
    */
    tl4cpp::oauth certifyer(c_key,c_sec,my_access_token,my_access_sec);

    std::map<std::string,std::string> param;
    param["status"]="it is test";
    
    tl4cpp::postapi statusup(certifyer,"/statuses/update.json");
    statusup.request(param);
    
    std::map<std::string,std::string> param_a;
    param_a["count"]="1";
    
    tl4cpp::getapi tlget(certifyer,"/statuses/home_timeline.json");
    tlget.request(param_a);
    
    return 0;
}