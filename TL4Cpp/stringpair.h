//
//  sortablemap.h
//  TL4Cpp
//
//  Created by Sayahamitt on 2015/02/12.
//  Copyright (c) 2015年 Sayahamitt. All rights reserved.
//

#ifndef __TL4Cpp__stringpair__
#define __TL4Cpp__stringpair__

#include <string>
#include <vector>
#include <map>
#include <algorithm>

namespace tl4cpp {
    namespace stringpair{
        typedef std::pair<std::string, std::string> stringpair_type;
        typedef std::vector<stringpair_type> stringpair_array;
        
        static bool compspair_dictorder(const stringpair_type &left, const stringpair_type &right){
            size_t size;
            bool left_key_is_longer;
            if(left.first.size()<right.first.size()){
                size=left.first.size();
                left_key_is_longer=false;
            }else{
                size=right.first.size();
                left_key_is_longer=true;
            }
            
            for(int i=0;i<size;i++){
                if(left.first[i]<right.first[i]){
                    return true;
                }else if(left.first[i]>right.first[i]){
                    return false;
                }
            }
            
            return !left_key_is_longer;
        }
        
        inline void sort_by_key(stringpair_array& target){
            std::sort(target.begin(),target.end(),compspair_dictorder);
        }
        
        inline std::string pair_to_string(const stringpair_type& source, const std::string& delim){
            return source.first + delim + source.second;
        }
        
        inline std::string array_to_string(const stringpair_array& container, const std::string delim_pair,const std::string delim_array){
            std::string result;
            
            for (stringpair_array::const_iterator itr = container.begin(); itr != container.end(); itr++) {
                result += pair_to_string(*itr, delim_pair);
                if (itr != container.end()-1) {
                    result += delim_array;
                }
            }
            return result;
        }
        
        inline stringpair_array parsefrommap(const std::map<std::string,std::string>& source) {
            stringpair_array result;
            
            for (std::map<std::string,std::string>::const_iterator itr = source.begin();
                 itr != source.end(); itr++) {
                    result.push_back(stringpair_type(itr->first, itr->second));
            }
            
            return result;
        }
    }
}

#endif /* defined(__TL4Cpp__sortablemap__) */
