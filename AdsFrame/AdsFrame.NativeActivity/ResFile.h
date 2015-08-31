#pragma once

#include "ads.h"

namespace ads
{
    class CResFile
    {
    public:
        CResFile();
        virtual ~CResFile();

    public:
        INT64       m_nResFileID;       // 资源文件唯一ID
        std::string m_strFileName;      // 资源文件名（默认格式为：md5.ext）
        std::string m_strMD5;           // 资源文件MD5校验码
        std::string m_strSHA1;          // 资源文件SHA1校验码
        std::string m_strOrigName;      // 资源文件原始名称
        std::string m_strFlvUrl;        // 资源文件对应的预览视频文件链接地址
        std::string m_strThumbUrl;      // 资源文件对应的预览图片文件链接地址
        int         m_nSortIndex;       // 资源文件播放顺序值
        int         m_nPlaySecs;        // 资源文件播放时间长度
        std::string m_strPlayJSON;      // 资源文件播放设置参数JSON
    };
    typedef std::map<INT64, CResFile>           CResFileMap;
    typedef std::map<INT64, CResFile>::iterator CResFileMapIt;
}