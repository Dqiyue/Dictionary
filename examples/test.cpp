#include <dictionary.h>
#include <stdio.h>
#include <dictionary_any.h>


NetCore::CStr toBin(unsigned int in, unsigned char bits) {
    NetCore::CStr out;
    assert(bits > 0);
    //unsigned int i = 0;
    while(bits--) {
        out += ((in & (1 << bits)) == 0 ? '0' : '1');
    }
    //out += ((in & 1) == 0 ? '0' : '1');
    return out;
}

int main() {
    NetCore::dictionary<NetCore::CStr, NetCore::CStr> dict;
    dict["hello"] = "world";
    dict["lucky"] = "star";
    // printf("hello 0x%08x\n", (unsigned int)((dict["hello"]).str()));
    // printf("lucky 0x%08x\n", (unsigned int)((dict["lucky"]).str()));
    dict["my"] = "hero";
    dict["asds"] = "herasdso";
    dict["masdsady"] = "asdsdadwwf";
    dict["adww"] = "adsffe";
    dict["asff"] = "adfggg";
    dict["adwfw"] = "adwffa";
    dict["asfag"] = "asfwfg";
    dict["asfwgag"] = "gehjtiik";
    dict["bjytta"] = "rtrtry";
    dict["the one"] = "Hhyh";
    dict["Fgyh"] = "ixiywe";
    dict["wdwtseg"] = "vnnmuh";
    dict["sxzefr3"] = "hiureqw";
    dict["zxfrqq"] = "uyiyetrq";
    dict["sfgeqq"] = "uiiudgfh";
    dict["s4346ergh"] = "64gsdgb";
    dict["gxbw3"] = "vcbre456";
    dict["vdgASr3"] = "bvxbzeret7";
    dict["cxzferew5"] = "zxvsrwre5";
    dict["vger35"] = "y54ddb";
    dict.erase("the one");
    if (dict.find("the one") == dict.end()) {
        printf("success erase !\n");
    }

    dict["a/f,waf"] = "ajhfafh";
    dict.erase("hello");
    dict.erase("lucky");

    for(decltype(dict)::iterator it = dict.begin(); it != dict.end(); ++it) {
        printf("key is %s, val is %s!\n",it->getkey().str(), it->val.str());
    }


    // printf("hello 0x%08x\n", (unsigned int)((dict["hello"]).str()));
    // printf("lucky 0x%08x\n", (unsigned int)((dict["lucky"]).str()));



    NetCore::dictionary_any dict_any;
    dict_any["hello"] = "world";
    dict_any["lucky"] = "star";
    // //printf("hello 0x%08x\n", (unsigned int)((dict_any["hello"]).str()));
    // //printf("lucky 0x%08x\n", (unsigned int)((dict_any["lucky"]).str()));
    dict_any["my"] = "hero";
    dict_any["asds"] = "herasdso";
    dict_any["masdsady"] = "asdsdadwwf";
    dict_any["adww"] = "adsffe";
    dict_any["asff"] = "adfggg";
    dict_any["adwfw"] = "adwffa";
    dict_any["asfag"] = "asfwfg";
    dict_any["asfwgag"] = "gehjtiik";
    dict_any["bjytta"] = "rtrtry";
    dict_any["the one"] = "Hhyh";
    dict_any["Fgyh"] = "ixiywe";
    dict_any["wdwtseg"] = "vnnmuh";
    dict_any["sxzefr3"] = "hiureqw";
    dict_any["zxfrqq"] = "uyiyetrq";
    dict_any["sfgeqq"] = "uiiudgfh";
    dict_any["s4346ergh"] = "64gsdgb";
    dict_any["gxbw3"] = "vcbre456";
    dict_any["vdgASr3"] = "bvxbzeret7";
    dict_any["cxzferew5"] = "zxvsrwre5";
    dict_any["vger35"] = "y54ddb";
    if (dict_any.find("the one") != dict_any.end()) {
        printf("success find !\n");
    }
    dict_any.erase("the one");
    if (dict_any.find("the one") == dict_any.end()) {
        printf("success erase !\n");
    }

    dict_any["a/f,waf"] = "ajhfafh";
    dict_any.erase("hello");
    dict_any.erase("lucky");

    for(decltype(dict_any)::iterator it = dict_any.begin(); it != dict_any.end(); ++it) {
        printf("key is %s, val is %s, index is %u, hash is %s!\n",it->key.get<NetCore::CStr>().str(), it->val.get<NetCore::CStr>().str(), dict_any.indexof(it->hash), toBin(it->hash,8).str());
    }


    //printf("hello 0x%08x\n", (unsigned int)((dict_any["hello"]).str()));
    //printf("lucky 0x%08x\n", (unsigned int)((dict_any["lucky"]).str()));

    // char* p = new char [10];
    // p[0] = '1';
    // p[1] = '1';
    // p[2] = '1';
    // p[3] = '1';
    // p[4] = '1';
    // p[5] = 0;
    // NetCore::any str3;
    // str3 = p;
    // NetCore::any str2("world");
    // NetCore::any str("hello");
    // str = str2;
    // str = str3;
    // try {
    //     std::cout << (str.get<NetCore::CStr>()).str() << std::endl;
    // }catch (std::exception& e) {
    //     std::cout << __LINE__ << ": " << e.what() << std::endl;
    // }

    
    // NetCore::CStr str("hello world");
    // std::cout << str.str() << std::endl;
    return 0;
}