//
//  multipartform.h
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/23.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#ifndef TL4Cpp_multipartform_h
#define TL4Cpp_multipartform_h

#include <map>
#include <string>
#include <cstdlib>
#include <ctime>

namespace tl4cpp {
    namespace multipartform{
        /*multipart_type
         std::map<パラメータの名前,std::pair<パラメータの中身,データのHTTP Content-Type>>
         */
        typedef std::pair<std::string, std::string> data_property_type;
        typedef std::map<std::string,std::pair<std::string,std::string>> multipart_type;
        //ランダムな英小文字列生成関数
        inline std::string strrand(int length){
            char* _str = new char[length + 1];
            time_t now_time;
            time(&now_time);
            srand((unsigned int)now_time);
            for(int i=0;i<length + 1;i++){
                _str[i] = rand() % 25 + 97;//UTF-8専用
            }_str[length]=0;
            
            return std::string(_str);
        }
        
        inline std::string makebody(const multipart_type& formdatas, std::string boundary){
            //multipartform生成
            std::string query;
            
            for(multipart_type::const_iterator itr = formdatas.begin(); itr!=formdatas.end(); itr++){
                query += "--" + boundary +"\r\n";
                query += "Content-Disposition: form-data; name=\""+itr->first+"\"";
                if(itr->second.second == "application/octet-stream"){
                    query +="; filename=\""+ strrand(10) +"\"\r\n";
                    query += "Content-Type: " + itr->second.second + "\r\n";
                }else{
                    query += "\r\n";
                }
                query += "\r\n";
                query += itr->second.first + "\r\n";
            }
            query += "--" + boundary + "--\r\n";
            
            return query;
        }
        
        inline multipart_type maptomultiparttype(const std::map<std::string,std::string>& source){
            multipart_type result;
            
            for (std::map<std::string,std::string>::const_iterator itr = source.begin();
                 itr != source.end(); itr++) {
                data_property_type property(itr->second,"");
                if(itr->first == "media"){
                    property.second="application/octet-stream";
                }
                result[itr->first]=property;
            }
            return result;
        }
    }
}
#endif
