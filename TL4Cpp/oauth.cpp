//
//  oauth.cpp
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/12.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <openssl/ssl.h>

#include "clx/https.h"
#include "clx/base64.h"
#include "clx/salgorithm.h"
#include "clx/uri.h"

#include "urlencode.h"
#include "oauth.h"

//OpenSSLライブラリの関数群がXcodeでは非推奨となっている為に警告が出るのを抑制
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

namespace tl4cpp {
    const std::string oauth::request_token_url = "https://api.twitter.com/oauth/request_token";
    const std::string oauth::authorize_url = "https://api.twitter.com/oauth/authorize";
    const std::string oauth::access_token_url = "https://api.twitter.com/oauth/access_token";
    const std::string oauth::c_key_key = "oauth_consumer_key";
    const std::string oauth::nonce_key = "oauth_nonce";
    const std::string oauth::sig_method_key = "oauth_signature_method";
    const std::string oauth::signature_key = "oauth_signature";
    const std::string oauth::timestamp_key = "oauth_timestamp";
    const std::string oauth::verifier_key = "oauth_verifier";
    const std::string oauth::oauth_version_key = "oauth_version";
    const std::string oauth::token_key = "oauth_token";
    const std::string oauth::sig_method = "HMAC-SHA1";
    const std::string oauth::oauth_version = "1.0";
    
    oauth::oauth(const std::string& a_c_key, const std::string& a_c_sec):
    c_key(a_c_key),
    c_sec(a_c_sec),
    isempty(false)
    {
    }
    
    oauth::oauth(const std::string& a_c_key,const std::string& a_c_sec,const std::string& token,const std::string& token_sec):
    c_key(a_c_key),
    c_sec(a_c_sec),
    access_token(token),
    access_token_sec(token_sec),
    isempty(false)
    {
    }
    
    oauth::oauth(const oauth &obj):
    c_key(obj.c_key),
    c_sec(obj.c_sec),
    request_token(obj.request_token),
    request_token_sec(obj.request_token_sec),
    access_token(obj.access_token),
    access_token_sec(obj.access_token_sec),
    m_user_id(obj.m_user_id),
    m_screen_name(obj.m_screen_name),
    isempty(obj.isempty)
    {
    }
    
    oauth::oauth():
    isempty(true)
    {
    }
    
    oauth::~oauth(){}
    
    oauth& oauth::operator=(const oauth& left){
        this->request_token = left.request_token;
        this->request_token_sec = left.request_token_sec;
        this->access_token = left.access_token;
        this->access_token_sec = left.access_token_sec;
        this->m_user_id = left.m_user_id;
        this->m_screen_name = left.m_screen_name;
        this->isempty = left.isempty;
        
        return *this;
    }
    
    bool oauth::empty() const{
        return isempty;
    }
    
    std::string oauth::create_header(const api_method_type& method,const std::string& url, const std::map<std::string,std::string>& _params) const{
        param_array params = stringpair::parsefrommap(_params);
        param_array oauth_params;
        std::string auth_header;
        std::string http_header;
        
        std::string api_url;
        
        time_t now_time;
        char co_nonce[33];
        std::stringstream out_stream;
        std::string sig_plain;
        
        std::string nonce;
        std::string signature;
        std::string timestamp;
        
        unsigned char co_signature[SHA_DIGEST_LENGTH];
        unsigned int co_siglen;
        
        //必須パラメータ生成
        oauth_params.push_back(param_type(c_key_key,c_key));
        oauth_params.push_back(param_type(sig_method_key,sig_method));
        oauth_params.push_back(param_type(oauth_version_key,oauth_version));
        if(method==access){
            oauth_params.push_back(param_type(token_key,request_token));
            oauth_params.insert(oauth_params.end(),params.begin(),params.end());
        }else if(method == post){
            oauth_params.insert(oauth_params.end(),params.begin(),params.end());
            oauth_params.push_back(param_type(token_key,access_token));
        }else if(method!=request){
            oauth_params.push_back(param_type(token_key,access_token));
        }
        
        //現在時刻取得,文字列化
        out_stream<<time(&now_time);
        timestamp=out_stream.str();
        
        oauth_params.push_back(param_type(timestamp_key, timestamp));//timeパラメータを追加
        out_stream.str("");
        
        //nonce生成,ランダムな英小文字32桁
        srand((unsigned int)now_time);
        for(int i=0;i<33;i++){
            co_nonce[i] = rand() % 25 + 97;//UTF-8専用
        }
        co_nonce[32]=0;
        nonce = co_nonce;
        
        oauth_params.push_back(param_type(nonce_key,nonce));//nonceパラメータを追加
        
        //シグニチャ作成
        param_array sig_params;
        sig_params.insert(sig_params.end(), oauth_params.begin(), oauth_params.end());
        if(method != access && method != post){
            sig_params.insert(sig_params.end(), params.begin(), params.end());
        }
        
        stringpair::sort_by_key(sig_params);
        sig_plain = stringpair::array_to_string(sig_params, "=", "&");
        
        //シグネチャ生成用鍵の作成とapi_urlの設定
        std::string sig_key;
        
        if(method==access){
            sig_key = c_sec+"&"+request_token_sec;
            api_url = access_token_url;
        }else if(method==request){
            sig_key = c_sec+"&";
            api_url = request_token_url;
        }else{
            sig_key = c_sec+"&"+access_token_sec;
            api_url = url;
        }
        
        //メソッド指定子の決定
        std::string http_type;
        switch(method){
            case get:
                http_type = "GET";break;
            case request:
                http_type = "GET";break;
            case access:
                http_type = "GET";break;
            case post:
                http_type = "POST";break;
            case post_www_form:
                http_type = "POST";break;
            default:
                std::cout<<"HTTP method type is bad!! @oauth::crete_header"
                <<std::endl;
                break;
        }
        
        //std::cout<<http_type<<"&"<<request_token_url<<"&"<<sig_plain<<std::endl;//for debug
        
        sig_plain = http_type+"&"+percentEnc(api_url)+"&"+percentEnc(sig_plain);
        
        std::cout<<sig_plain<<std::endl;//for debug
        
        //シグニチャ生成,OpenSSLのHMAC関数を利用
        HMAC(EVP_sha1(),sig_key.c_str(),(int)sig_key.length(),
             (unsigned char*)sig_plain.c_str(),sig_plain.size(),co_signature,&co_siglen);
        
        signature = clx::base64::encode((char*)co_signature, sizeof(co_signature));
        signature = percentEnc(signature);
        
        //std::cout<<signature<<std::endl;//for debug
        oauth_params.push_back(param_type(signature_key,signature));
        stringpair::sort_by_key(oauth_params);
        
        //Authorizationヘッダ作成
        auth_header = "OAuth "+
        stringpair::array_to_string(oauth_params,"=\"","\", ")+
        "\"";
        
        std::cout<<auth_header<<std::endl;
        return auth_header;
    }
    
    std::string oauth::header_get(const std::string& url,const std::map<std::string,std::string>& params) const{
        return create_header(get,url,params);
    }
    
    std::string oauth::header_post_www_form(const std::string& url,const std::map<std::string,std::string>& wwwFormDatas) const{
        return create_header(post_www_form,url,wwwFormDatas);
    }
    
    std::string oauth::header_post(const std::string &url, const std::string &postdata) const{
        std::map<std::string,std::string> params;
        unsigned char hash[SHA_DIGEST_LENGTH];
        
        SHA1((unsigned char*)postdata.c_str(),(unsigned long)postdata.size(),hash);
        std::string body_hash = clx::base64::encode((char*)hash,sizeof(hash));
        body_hash = percentEnc(body_hash);
        
        params["oauth_body_hash"]=body_hash;
        
        return create_header(post, url, params);
    }
    
    std::string oauth::Extractformbody(const std::string& holestring,const std::string& key) const{
        unsigned long pos_begin,pos_end;
        std::string KeywithEq = key + "=";
        std::string value;
        
        pos_begin = holestring.find(KeywithEq,0)+KeywithEq.length();
        pos_end = holestring.find("&",pos_begin);
        value = holestring.substr(pos_begin,pos_end - pos_begin);
        
        return value;
    }
    
    std::string oauth::get_authorize_url(){
        std::map<std::string,std::string> param;
        std::string http_header;
        std::string auth_header = create_header(request,request_token_url,param);
        std::string buffer;
        //---request_token取得---
        
        std::map<std::string,std::string> _header;
        _header["Authorization"]=auth_header;
        _header["Connection"]="close";
        
        clx::https session(clx::uri::encode("api.twitter.com"), 443);
        session.get(clx::uri::encode("/oauth/request_token"),_header);
        
        buffer = session.body();
        //得られたhttpレスポンスのbodyからrequest_tokenとrequest_token_secを抽出
        //受信文字列に"auht_token="が含まれなかったら例外を投げる
        if (buffer.find("oauth_token=",0) == std::string::npos) {
            throw std::runtime_error("Could not obtain Authrization request token");
        }
        
        request_token = Extractformbody(buffer, "oauth_token");
        request_token_sec = Extractformbody(buffer, "oauth_token_secret");
        
        //std::cout<<request_token<<std::endl;//for debug
        //std::cout<<request_token_sec<<std::endl;//for debug
        
        return authorize_url+'?'+token_key+'='+request_token;
    }
    
    bool oauth::set_access_token(const std::string& pin){
        std::map<std::string,std::string> param;
        std::string http_header;
        std::string auth_header;
        std::string buffer;
        std::string verifier;
        
        //---access_token取得---
        //ブラウザ経由でユーザーに認証,PINコードを入力してもらう
        verifier = pin;
        //std::cout<<verifier<<std::endl;//for debug
        
        param[verifier_key]=verifier;
        
        auth_header=create_header(access,access_token_url,param);
        
        std::map<std::string,std::string> _header;
        _header["Authorization"]=auth_header;
        _header["Connection"]="close";
        
        clx::https session(clx::uri::encode("api.twitter.com"), 443);
        session.get(clx::uri::encode("/oauth/access_token"),_header);
        
        buffer = session.body();
        //得られたトークンとユーザー名の文字列を記録
        //得られたhttpレスポンスのbodyからaccess_tokenとaccess_token_secを抽出
        access_token = Extractformbody(buffer, "oauth_token");
        access_token_sec = Extractformbody(buffer, "oauth_token_secret");
        m_user_id = Extractformbody(buffer, "user_id");
        m_screen_name = Extractformbody(buffer, "screen_name");
        
        return true;
    }
    
    std::string oauth::getAccessToken() const{
        return access_token;
    }
    
    std::string oauth::getAccessTokenSecret() const{
        return access_token_sec;
    }
}