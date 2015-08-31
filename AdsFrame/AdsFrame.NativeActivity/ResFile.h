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
        INT64       m_nResFileID;       // ��Դ�ļ�ΨһID
        std::string m_strFileName;      // ��Դ�ļ�����Ĭ�ϸ�ʽΪ��md5.ext��
        std::string m_strMD5;           // ��Դ�ļ�MD5У����
        std::string m_strSHA1;          // ��Դ�ļ�SHA1У����
        std::string m_strOrigName;      // ��Դ�ļ�ԭʼ����
        std::string m_strFlvUrl;        // ��Դ�ļ���Ӧ��Ԥ����Ƶ�ļ����ӵ�ַ
        std::string m_strThumbUrl;      // ��Դ�ļ���Ӧ��Ԥ��ͼƬ�ļ����ӵ�ַ
        int         m_nSortIndex;       // ��Դ�ļ�����˳��ֵ
        int         m_nPlaySecs;        // ��Դ�ļ�����ʱ�䳤��
        std::string m_strPlayJSON;      // ��Դ�ļ��������ò���JSON
    };
    typedef std::map<INT64, CResFile>           CResFileMap;
    typedef std::map<INT64, CResFile>::iterator CResFileMapIt;
}