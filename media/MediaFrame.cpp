/*
* Author��������
* Email��phight@163.com
* QQȺ��220954528
*/

#include "stdafx.h"
#include "MediaFrame.h"


MediaFrame::MediaFrame():
    m_pData(NULL),
	m_uTimestamp(0)
{
}


MediaFrame::MediaFrame(FrameType frameType, void* attribute)
{
    m_FrameType = frameType;
    if (m_FrameType == FRAME_TYPE_VIDEO)
    {
        VideoCaptureAttribute* pattr = (VideoCaptureAttribute*)attribute;
        m_subtype = pattr->format;
        m_width = pattr->width;
        m_height = pattr->height;
        m_stride = pattr->stride;
        if (m_width>0 && m_height>0 && m_stride>0)
        {
            if (m_subtype==MFVideoFormat_I420)
            {
                m_dataSize = m_stride * m_height * 3 / 2;
            }
            else {
                m_dataSize = m_stride * m_height;
            }
            m_pData = (BYTE*)malloc(m_dataSize);
        }
    }
    else if(m_FrameType == FRAME_TYPE_AUDIO)
    {
        AudioCaptureAttribute* pattr = (AudioCaptureAttribute*)attribute;
        m_subtype = pattr->format;
        m_samplesize = pattr->samplesize;
        m_samplerate = pattr->samplerate;
        m_channels = pattr->channel;
        m_bitwide = pattr->bitwide;
        if (m_samplesize>0 && m_channels>0 && m_bitwide>0)
        {
            m_dataSize = m_samplesize * m_channels * m_bitwide / 8;
            m_pData = (BYTE*)malloc(m_dataSize);
        }
    }
}


MediaFrame::MediaFrame(FrameType frameType, GUID  subtype, DWORD dataSize)
{
	m_pData = (BYTE*)malloc(dataSize);
	if (m_pData!=NULL)
	{
		m_dataSize = dataSize;
		m_FrameType = frameType;
		m_subtype = subtype;
	}
}


MediaFrame::MediaFrame(BYTE *pData, FrameType type, void* attribute)
{
	m_FrameType = type;
	if (m_FrameType == FRAME_TYPE_VIDEO)
	{
		VideoCaptureAttribute* pattr = (VideoCaptureAttribute*)attribute;
		m_subtype = pattr->format;
		m_width = pattr->width;
		m_height = pattr->height;
		m_stride = pattr->stride;
		m_dataSize = pattr->stride * pattr->height;
		m_pData = (BYTE*)malloc(m_dataSize);
		memcpy(m_pData, pData, m_dataSize);
	}else if (m_FrameType == FRAME_TYPE_AUDIO)
	{
		AudioCaptureAttribute* pattr = (AudioCaptureAttribute*)attribute;
	}
}


MediaFrame::MediaFrame(IMFMediaBuffer* pBuffer, FrameType type, void* attribute) :
	m_uTimestamp(0)
{
    this->m_FrameType = type;
	DWORD bufferSize = 0;
	BYTE* pData = NULL;
    pBuffer->GetCurrentLength(&bufferSize);
    m_dataSize = bufferSize;
	m_pData = (BYTE*)malloc(m_dataSize);

    if (this->m_FrameType == FRAME_TYPE_VIDEO)
    {
		VideoCaptureAttribute* pattr = (VideoCaptureAttribute*)attribute;
        LONG lStride = (LONG)pattr->stride;
        // Helper object to lock the video buffer.

        // Lock the video buffer. This method returns a pointer to the first scan line
		// in the image, and the stride in bytes.
		pBuffer->Lock(&pData, NULL, NULL);
		memcpy(m_pData, pData, m_dataSize);
		pBuffer->Unlock();
		m_subtype = pattr->format;
		m_width = pattr->width;
		m_height = pattr->height;
		if (lStride<0){
			m_stride = 0 - lStride;
			Inversion();
		}else{
			m_stride = lStride;
		}
    }
	else if (this->m_FrameType == FRAME_TYPE_AUDIO) {
		AudioCaptureAttribute* pattr = (AudioCaptureAttribute*)attribute;
		m_subtype = pattr->format;
        m_samplerate = pattr->samplerate;
        m_channels = pattr->channel;
        m_bitwide = pattr->bitwide;
		pBuffer->Lock(&pData, NULL, NULL);
		memcpy(m_pData, pData, m_dataSize);
		pBuffer->Unlock();
    }

}


MediaFrame::~MediaFrame()
{
	if (m_pData)
	{
		free(m_pData);
	}
}


void MediaFrame::Inversion()
{
	BYTE *pData = (BYTE*)malloc(m_dataSize);

	for (int i = 0; i < m_height; i++)
	{
		BYTE *pDst = &pData[i*m_stride];
		BYTE *pSrc = &m_pData[(m_height - i - 1)*m_stride];
		memcpy(pDst, pSrc, m_stride);
	}
	free(m_pData);
	m_pData = pData;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

uint32_t MediaFrame::CopyTo(void* pData, uint32_t dataSize) const
{
    uint32_t size = dataSize > m_dataSize ? m_dataSize : dataSize;
    if (size>0 && pData && m_pData)
    {
        memcpy(pData, m_pData, size);
        return size;
    }
    return 0;
}


uint32_t MediaFrame::CopyFrom(void* pData, uint32_t dataSize) const
{
    uint32_t size = dataSize > m_dataSize ? m_dataSize : dataSize;
    if (size > 0 && pData && m_pData)
    {
        memcpy(m_pData, pData, size);
        return size;
    }
    return 0;
}


FrameType MediaFrame::GetFrameType() const
{
    return m_FrameType;
}


uint32_t MediaFrame::GetFrameSize() const
{
    return m_dataSize;
}