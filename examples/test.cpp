#include <dictionary.h>
#include <stdio.h>

int main() {
    NetCore::dictionary<NetCore::CStr, NetCore::CStr> dict;
    dict["hello"] = "world";
    dict["lucky"] = "star";
    printf("hello 0x%08x\n", (unsigned int)((dict["hello"]).str()));
    printf("lucky 0x%08x\n", (unsigned int)((dict["lucky"]).str()));
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
        printf("key is %s, val is %s!\n",it->key.str(), it->val.str());
    }


    printf("hello 0x%08x\n", (unsigned int)((dict["hello"]).str()));
    printf("lucky 0x%08x\n", (unsigned int)((dict["lucky"]).str()));
    return 0;
}