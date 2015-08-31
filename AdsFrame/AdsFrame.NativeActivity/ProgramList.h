#pragma once

#include "Program.h"

namespace ads
{
    class CProgramList
    {
    public:
        CProgramList();
        virtual ~CProgramList();

    public:
        INT64       m_nPrmListID;       // ��Ŀ�б�ΨһID
        std::string m_strPrmListName;   // ��Ŀ�б�����
        int         m_nPrmListVer;      // ��Ŀ�б�汾
        int         m_nPrmListSecs;     // ��Ŀ�б��ų��ȣ���λ���룩
        bool        m_bIsSynchronized;  // ��Ŀ�б��Ƿ���Ҫ���ն�ͬ������
        CProgramMap m_mapPrm;           // ��Ŀ�б�����Ľ�Ŀ�嵥
        CIntVector  m_vectIndex;        // ��Ŀ�б��н�Ŀ�Ĳ���˳����Ϣ
    };

};