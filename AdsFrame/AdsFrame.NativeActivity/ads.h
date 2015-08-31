#pragma once

#include <string>
#include <vector>
#include <map>

typedef     long long                                       INT64;
typedef     unsigned long long                              UINT64;
typedef     std::vector<int>                                CIntVector;
typedef     std::vector<INT64>                              CInt64Vector;
typedef     std::map<std::string, std::string>              CKeyValData;
typedef     std::map<std::string, std::string>::iterator    CKeyValDataIt;
typedef     std::map<INT64, std::string>                    CInt64ValData;
typedef     std::map<INT64, std::string>::iterator          CInt64ValDataIt;
typedef     std::map<std::string, INT64>                    CKeyInt64Data;
typedef     std::map<std::string, INT64>::iterator          CKeyInt64DataIt;