#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <pspdebug.h>
#include <pspkernel.h>
#include <memory>
#include "engine.h"

PSP_MODULE_INFO("Tutorial", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int exit_callback(int arg1, int arg2, void *common)
{
    sceKernelExitGame();
    return 0;
}

int CallbackThread(SceSize args, void *argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();

    return 0;
}

int SetupCallbacks()
{
    int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
    if (thid >= 0)
        sceKernelStartThread(thid, 0, 0);

    return thid;
}

int main()
{
    SetupCallbacks();
    SDL_SetMainReady();
    pspDebugScreenInit();

    pspDebugScreenPrintf("Launching...\n");

    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    engine->Loop();
    
    return 0;
}