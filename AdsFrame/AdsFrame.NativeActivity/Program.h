#pragma once

#include "PrmArea.h"

namespace ads
{
    class CProgram
    {
    public:
        CProgram();
        virtual ~CProgram();

    public:
        INT64       m_nPrmID;       // 节目唯一ID
        std::string m_strPrmName;   // 节目名称
        int         m_nPrmVer;      // 节目版本号
    };
    typedef std::map<INT64, CProgram>           CProgramMap;
    typedef std::map<INT64, CProgram>::iterator CProgramMapIt;
}
