//
//  postmultipart.cpp
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/23.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#include <map>
#include <fstream>

#include "clx/https.h"
#include "urlencode.h"

#include "multipartform.h"

#include "postmultipart.h"

namespace tl4cpp {
    postmultipart::postmultipart(const oauth& _authorization, const std::string _apipath, const std::string _apidomein):
    apibase(_authorization,_apipath,_apidomein),
    APIURL_uri(APIPROTOCOL_uri + APIDOMEIN_uri + APIVERSION_uri + apipath)
    {
        sessioninit();
    }
    
    postmultipart::~postmultipart(){}
    
    void postmultipart::sessioninit(){
        session = new clx::https(APIDOMEIN_uri,443);
    }
    
    std::map<std::string,std::string> postmultipart::http_head(std::string auth_head){
        std::map<std::string, std::string> _header;
        _header["Authorization"] = auth_head;
        _header["Connection"]="close";
        
        return _header;
    }
    
    void postmultipart::post(const multipartform::multipart_type& _parameters){
        std::string boundary = multipartform::strrand(32);
        std::string query = multipartform::makebody(_parameters, boundary);
        std::map<std::string,std::string> http_header = http_head(authorization.header_post(APIURL_uri, query));
        http_header["Content-Type"] = "multipart/form-data, boundary=\"" + boundary + "\"";
        
        //std::cout<<query<<std::endl;
        session->post(APIVERSION_uri + apipath, query, http_header);
        std::cout<<session->body();
    }
    
    void postmultipart::execute(const std::map<std::string, std::string>& _parameters){
        post(multipartform::maptomultiparttype(_parameters));
    }
    
    void postmultipart::execute(const std::map<std::string, std::string>& _parameters, std::string paramoffile, std::string filedata){
        multipartform::multipart_type parameters = multipartform::maptomultiparttype(_parameters);
        parameters[paramoffile] = std::pair<std::string, std::string>(filedata,"application/octet-stream");
        
        post(parameters);
    }
    
    picojson::value postmultipart::request(const std::map<std::string,std::string>& _parameter, std::string paramoffile, std::string filepath){
        //画像ファイルオープン
        std::fstream file;
        file.open((filepath), std::ios::in | std::ios::binary);
        if (! file.is_open()) {
            throw std::runtime_error("faild to open a file");
        }
        //ファイルサイズ計測
        file.seekg(0,std::fstream::beg);
        std::fstream::pos_type begin = file.tellg();
        file.seekg(0,std::fstream::end);
        std::fstream::pos_type end = file.tellg();
        size_t filesize = end - begin;
        file.seekg(std::ios::beg);
        //画像データロード
        char* mediadata = new char[filesize];
        file.read(mediadata, filesize);
        std::string datastr(mediadata,filesize);
        
        execute(_parameter, paramoffile, datastr);
        
        picojson::value result;
        std::string err;
        picojson::parse(result, session->body().begin(), session->body().end(),&err);
        
        return result;
    }
}