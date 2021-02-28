#include "SDK\amx\amx.h"
#include "SDK\plugincommon.h"

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")


typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void* pAMXFunctions;


cell AMX_NATIVE_CALL CreateSocket(AMX* amx, cell* params)
{
    SOCKET sock = INVALID_SOCKET, c_sock = INVALID_SOCKET;
    cell* addr = nullptr;

    int len = 0;

    amx_GetAddr(amx, params[1], &addr);
    amx_StrLen(addr, &len);

    if (len)
    {
        len++;

        char* text = new char[len];
        amx_GetString(text, addr, 0, len);

        PCSTR port = "" + *text;

        struct addrinfo* result = nullptr;
        struct addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));

        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        getaddrinfo(NULL, port, &hints, &result);
        
        sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        
        bind(sock, result->ai_addr, (int)result->ai_addrlen);
        freeaddrinfo(result);
        listen(sock, SOMAXCONN);

        c_sock = accept(sock, NULL, NULL);

        closesocket(sock);

        int iResult, recvbuflen {}, idx;
        char recvbuf[1024];

        PCSTR str;
        while (true)
        {
            iResult = recv(c_sock, recvbuf, recvbuflen, 0);

            if (iResult > 0) 
            {
                // Pawn: forward OnDataRecieve(data[], len);
                if (!amx_FindPublic(amx, "OnDataRecieve", &idx))
                {
                    cell
                        ret,
                        addr;

                    str = "" + *recvbuf;

                    amx_Push(amx, recvbuflen);
                    amx_PushString(amx, &addr, NULL, str, NULL, NULL);

                    
                    amx_Exec(amx, &ret, idx);
                    amx_Release(amx, addr);
                }
            }
        }
    }

    return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

    char log[] = "\n * SOCKmp by Glorfin was loaded.";
    logprintf(log);
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    char log[] = "\n * SOCKmp by Glorfin was unloaded.";
    logprintf(log);
}

AMX_NATIVE_INFO PluginNatives[] =
{
    {"CreateSocket", CreateSocket},
    {0, 0}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
    return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
    return AMX_ERR_NONE;
}