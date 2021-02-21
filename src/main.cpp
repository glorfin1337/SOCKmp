#include "headers\SOCK.h"

#include "SDK\amx\amx.h"
#include "SDK\plugincommon.h"

typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void* pAMXFunctions;

SOCKET _socket;
Server sock;

cell AMX_NATIVE_CALL CreateConnection(AMX* amx, cell* params)
{
    _socket = sock.CreateConnection("7778");
    if (sock.connection == 1)
    {
        char log[64] = "Connection was successful.";
        logprintf(log);
    }
    else 
    {
        char log[64] = "Connection was not successful.";
        logprintf(log);
    }
    return 1;
}

cell AMX_NATIVE_CALL CloseConnection(AMX* amx, cell* params)
{
    sock.CloseConnection(_socket);
    return 1;
}

cell AMX_NATIVE_CALL OnDataRecieve(AMX* amx, cell* params)
{
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
    
    char notf[64] =  "\n---- * SOCKmp is loaded. Developer: Glorfin * ----\n";
    logprintf(notf);
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    char notf[64] = "\n---- * SOCKmp was unloaded. Developer: Glorfin * ----\n";
    logprintf(notf);
}

AMX_NATIVE_INFO PluginNatives[] =
{
    {"CreateConnection", CreateConnection},
    {"CloseConnection", CloseConnection},
    {"OnDataRecieve", OnDataRecieve},
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