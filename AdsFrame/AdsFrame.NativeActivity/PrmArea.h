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
        INT64       m_nAreaID;      // ��Ŀ����ΨһID
        std::string m_strAreaType;  // ��Ŀ��������
        int         m_nPlaySecs;    // ��Ŀ���򲥷�ʱ������λ���룩
        int         m_nAreaVer;     // ��Ŀ����汾
        int         m_nPosX;        // ��Ŀ�������Ͻ�X���꣨��λ�����أ�
        int         m_nPosY;        // ��Ŀ�������Ͻ�Y���꣨��λ�����أ�
        int         m_nWidth;       // ��Ŀ�����ȣ���λ�����أ�
        int         m_nHeight;      // ��Ŀ����߶ȣ���λ�����أ�
        int         m_nZIndex;      // ��Ŀ������������ֵԽС�����Խ��ǰ��
        CResFileMap m_mapResFile;   // ��Ŀ�����ڵ���Դ�ļ�
    };
    typedef std::map<INT64, CPrmArea>           CPrmAreaMap;
    typedef std::map<INT64, CPrmArea>::iterator CPrmAreaMapIt;
}