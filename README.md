# Dictionary
a simple dictionary class imp, it can auto expand and shrink, a fast and light container

# usage
```c++
NetCore::dictionary<NetCore::CStr, NetCore::CStr> dict;
dict["hello"] = "world";
dict.erase("hello");

if (dict.find("hello") == dict.end()) {
    printf("success erase !\n");
}

for(decltype(dict)::iterator it = dict.begin(); it != dict.end(); ++it) {
    printf("key is %s, val is %s!\n",it->key.str(), it->val.str());
}
```

# attention
dict["hello"] while auto insert a ("hello","") into dict if the key "hello" is not exist 
