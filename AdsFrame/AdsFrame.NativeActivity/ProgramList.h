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
        INT64       m_nPrmListID;       // 节目列表唯一ID
        std::string m_strPrmListName;   // 节目列表名称
        int         m_nPrmListVer;      // 节目列表版本
        int         m_nPrmListSecs;     // 节目列表播放长度（单位：秒）
        bool        m_bIsSynchronized;  // 节目列表是否需要多终端同步播放
        CProgramMap m_mapPrm;           // 节目列表里面的节目清单
        CIntVector  m_vectIndex;        // 节目列表中节目的播放顺序信息
    };

};