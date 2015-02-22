//
//  urlencode.h
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/16.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#ifndef TL4Cpp_urlencode_h
#define TL4Cpp_urlencode_h

#include <iostream>
#include <sstream>
#include <string>

namespace tl4cpp {
    
    inline std::string percentEnc(std::string str){
        const int NUM_BEGIN_UTF8 = 48;
        const int CAPITAL_BEGIN_UTF8 = 65;
        const int LOWER_BEGIN_UTF8 = 97;
        
        int charCode=-1;
        std::string encoded;
        std::stringstream out;
        
        //for文で1byteずつストリームに入れていく
        for(int i=0;str.size()>i;i++){
            //文字列中の1byte分のデータを整数値として代入
            charCode = (int)(unsigned char)str[i];
            
            //エンコードする必要の無い文字の判定
            if((NUM_BEGIN_UTF8 <= charCode && charCode <= NUM_BEGIN_UTF8 + 9)
               || (CAPITAL_BEGIN_UTF8 <= charCode && charCode <= CAPITAL_BEGIN_UTF8 + 25)
               || (LOWER_BEGIN_UTF8 <= charCode && charCode <= LOWER_BEGIN_UTF8 + 25)
               || str[i] == '.' || str[i] == '_' || str[i] == '-' || str[i] == '~')
            {
                //エンコードの必要が無い文字はそのままストリームに入れる
                out<<str[i];
            }else{
                //エンコードする場合は%記号と文字コードの16進数表示をストリームに入れる
                out << '%' << std::hex << std::uppercase <<charCode;
            }
        }
        //ストリームの文字列をstringのインスタンスに代入
        encoded = out.str();
        
        return encoded;
    }
}

#endif
