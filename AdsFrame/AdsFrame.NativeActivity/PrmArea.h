#pragma once

#include "ResFile.h"

namespace ads
{
    class CPrmArea
    {
    public:
        CPrmArea();
        virtual ~CPrmArea();

    public:
        INT64       m_nAreaID;      // 节目区域唯一ID
        std::string m_strAreaType;  // 节目区域类型
        int         m_nPlaySecs;    // 节目区域播放时长（单位：秒）
        int         m_nAreaVer;     // 节目区域版本
        int         m_nPosX;        // 节目区域左上角X坐标（单位：像素）
        int         m_nPosY;        // 节目区域左上角Y坐标（单位：像素）
        int         m_nWidth;       // 节目区域宽度（单位：像素）
        int         m_nHeight;      // 节目区域高度（单位：像素）
        int         m_nZIndex;      // 节目区域层叠次序（数值越小，层次越靠前）
        CResFileMap m_mapResFile;   // 节目区域内的资源文件
    };
    typedef std::map<INT64, CPrmArea>           CPrmAreaMap;
    typedef std::map<INT64, CPrmArea>::iterator CPrmAreaMapIt;
}