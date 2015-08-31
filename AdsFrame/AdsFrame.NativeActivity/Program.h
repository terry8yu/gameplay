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
        INT64       m_nPrmID;       // ��ĿΨһID
        std::string m_strPrmName;   // ��Ŀ����
        int         m_nPrmVer;      // ��Ŀ�汾��
    };
    typedef std::map<INT64, CProgram>           CProgramMap;
    typedef std::map<INT64, CProgram>::iterator CProgramMapIt;
}
