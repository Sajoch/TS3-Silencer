#include <windows.h>
#include "teamspeak/public_errors.h"
#include "teamspeak/public_errors_rare.h"
#include "teamspeak/public_definitions.h"
#include "teamspeak/public_rare_definitions.h"
#include "teamspeak/clientlib_publicdefinitions.h"
#include "ts3_functions.h"

extern TS3Functions ts3Functions;
UINT_PTR loop_id;

void setMuteState(bool state){
	uint64* result;
    if(ts3Functions.getServerConnectionHandlerList(&result)==ERROR_ok){
        uint64* server;
        for(server = result; *server != (uint64)NULL; ++server){
            if(ts3Functions.setClientSelfVariableAsInt(*server,CLIENT_INPUT_MUTED,(state==1?MUTEINPUT_MUTED:MUTEINPUT_NONE))==ERROR_ok){
                ts3Functions.flushClientSelfUpdates(*server, NULL);
            }
        }
        ts3Functions.freeMemory(result);
    }
}

void loop(HWND__*, unsigned int, long long unsigned int, long unsigned int){
	if(GetKeyState(VK_SCROLL)){
		setMuteState(true);
	}else{
		setMuteState(false);
	}
}

int init(){
	loop_id = SetTimer(0, 0, 50, loop);
	return 0;
}
int shutdown(){
	KillTimer(0, loop_id);
	return 0;
}