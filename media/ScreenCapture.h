/*
* Author��������
* Email��phight@163.com
* QQȺ��220954528
*/

#pragma once

#include <dxgi1_2.h>

#include "Capture.h"


class ScreenCapture :
    public Capture
{
public:
    ScreenCapture();
    virtual ~ScreenCapture();

private:
    CRITICAL_SECTION        m_critsec;

    vector<VideoCaptureAttribute*> m_AttributeList;
    VideoCaptureAttribute*    m_pBestAttribute = NULL;
    VideoCaptureAttribute*    m_pCurrentAttribute = NULL;
    vector<Sink *>           m_Sinks;

    CAPTURE_STATUS_E         m_Status = CAPTURE_STATUS_STOP;

    CString                  m_CaptureName;

	IDXGIOutputDuplication* m_pScreenDuplication;

public:
    int AddSink(Sink * sink);
    int GetSupportAttribute(void* attribute);
    int SetConfig(void* attribute);
    int GetConfig(void* attribute);
    CString GetName();
    CAPTURE_STATUS_E GetStatus();
    int Start();
    int Stop();
};

