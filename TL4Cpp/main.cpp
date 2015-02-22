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

#include "oauth.h"
#include "getapi.h"
#include "postapi.h"

const std::string c_key ="Q6xo84MPcloXMXsbxx55kPlMi";
const std::string c_sec ="ewFfhJNd9pEFfGUzVQUTQFtNMYSaHCrcDlVFfrqTYlFZbYYK2q";
const std::string my_access_token ="2280734850-Sp8WD2JpioN17mUF4a1lIA19yqozKhyWeaoPmsA";
const std::string my_access_sec ="cZPraKMj0s98BYCTxwtTxa8omaUorwdNTlbISLVtIDcoO";

int main() {
    tl4cpp::oauth certifyer(c_key,c_sec,my_access_token,my_access_sec);
    
    std::map<std::string,std::string> param;
    param["status"]="it is test";
    
    tl4cpp::postapi statusup(certifyer,"/statuses/update.json");
    statusup.request(param);
    /*
    std::map<std::string,std::string> param_a;
    param_a["count"]="1";
    
    tl4cpp::getapi tlget(certifyer,"/statuses/home_timeline.json");
    tlget.request(param_a);
    */
    return 0;
}