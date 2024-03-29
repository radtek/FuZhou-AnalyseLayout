#ifndef searchthread_h
#include "ZeromqManage.h"

#ifdef __WINDOWS__
#include "frsengineV.h"
#pragma comment( lib, "frsengineV.lib" )
using namespace NeoFaceV;
#else
#include <unistd.h>
#include "st_feature_comp.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "ZBase64.h"
#endif

class CSearchThread
{
public:
    CSearchThread();
    ~CSearchThread();
public:
    bool Init(char * pServerIP, int nServerPushPort, int nServerPullPort, LPALLFEATURENODEINFO pAllFeatureNodeInfo);
    bool UnInit();
private:
    //zeromq订阅消息回调
    static void ZeromqSubMsg(LPSUBMESSAGE pSubMessage, void * pUser);
    //解析Zeromq json
    bool ParseZeromqJson(LPSUBMESSAGE pSubMessage);
    void VerifyFeatureAction(LPSUBMESSAGE pSubMessage);
    int VerifyFeature(unsigned char * pf1, unsigned char * pf2, int nLen);

    //发送回应消息
    void SendResponseMsg(LPSUBMESSAGE pSubMessage);
private:
    CZeromqManage * m_pZeromqManage;    //Zeromq管理
    static int m_nThreadNum;
    int m_nThreadID;
    LPALLFEATURENODEINFO m_pAllFeatureNodeInfo;

#ifdef __WINDOWS__
    CVerify m_FRSVerify;
#endif
};

#define searchthread_h
#endif