// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <stdio.h>
#include "acpiwmi.h"
#include "error.h"

HINSTANCE hGetProcIDDLL;

typedef char(__stdcall* AsWMI_Open_ptr)();
typedef void(__stdcall* AsWMI_Close_ptr)();
typedef char(__stdcall* AsWMI_CheckSupport_ptr)();
typedef void(__stdcall* AsWMI_NB_RegisterEvent_ptr)();
typedef char(__stdcall* AsWMI_NB_GetDeviceStatus_ptr)(int a, int* status);
typedef void(__stdcall* AsWMI_NB_GetDeviceStatus_MoreBYTE_ptr)();
typedef char(__stdcall* AsWMI_NB_DeviceControl_ptr)(int a, int b);
typedef char(__stdcall* AsWMI_NB_DeviceControl_2arg_ptr)(int a, int b, int c);

AsWMI_Open_ptr AsWMI_Open_orig;
AsWMI_Close_ptr AsWMI_Close_orig;
AsWMI_CheckSupport_ptr AsWMI_CheckSupport_orig;
AsWMI_NB_RegisterEvent_ptr AsWMI_NB_RegisterEvent_orig;
AsWMI_NB_GetDeviceStatus_ptr AsWMI_NB_GetDeviceStatus_orig;
AsWMI_NB_GetDeviceStatus_MoreBYTE_ptr AsWMI_NB_GetDeviceStatus_MoreBYTE_orig;
AsWMI_NB_DeviceControl_ptr AsWMI_NB_DeviceControl_orig;
AsWMI_NB_DeviceControl_2arg_ptr AsWMI_NB_DeviceControl_2arg_orig;

BOOL APIENTRY DllMain(IN HINSTANCE hDllHandle, IN DWORD nReason, IN LPVOID Reserved)
{
    switch (nReason) {
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        FreeLibrary(hGetProcIDDLL);
        break;
    case DLL_PROCESS_ATTACH:
        printf("LIB LOADING\n");
        fflush(stdout);
        // Load the original DLL
        hGetProcIDDLL = LoadLibraryA("ACPIWMIorig.dll");

        // Handle errors
        if (!hGetProcIDDLL) {
            printf("could not load the dynamic library\n");
            //ErrorExit(TEXT("LoadLibrary"));
            fflush(stdout);
            return 0;
        }

        // resolve function address here
        AsWMI_Open_orig =                        (AsWMI_Open_ptr)GetProcAddress(hGetProcIDDLL, "AsWMI_Open");
        AsWMI_Close_orig =                       (AsWMI_Close_ptr)GetProcAddress(hGetProcIDDLL, "AsWMI_Close");
        AsWMI_CheckSupport_orig =                (AsWMI_CheckSupport_ptr)GetProcAddress(hGetProcIDDLL, "AsWMI_CheckSupport");
        AsWMI_NB_RegisterEvent_orig =            (AsWMI_NB_RegisterEvent_ptr)GetProcAddress(hGetProcIDDLL, "AsWMI_NB_RegisterEvent");
        AsWMI_NB_GetDeviceStatus_orig =          (AsWMI_NB_GetDeviceStatus_ptr)GetProcAddress(hGetProcIDDLL, "AsWMI_NB_GetDeviceStatus");
        AsWMI_NB_GetDeviceStatus_MoreBYTE_orig = (AsWMI_NB_GetDeviceStatus_MoreBYTE_ptr)GetProcAddress(hGetProcIDDLL, "AsWMI_NB_GetDeviceStatus_MoreBYTE");
        AsWMI_NB_DeviceControl_orig =            (AsWMI_NB_DeviceControl_ptr)GetProcAddress(hGetProcIDDLL, "AsWMI_NB_DeviceControl");
        AsWMI_NB_DeviceControl_2arg_orig =       (AsWMI_NB_DeviceControl_2arg_ptr)GetProcAddress(hGetProcIDDLL, "AsWMI_NB_DeviceControl_2arg");

        if (!AsWMI_Open_orig || !AsWMI_Close_orig || !AsWMI_CheckSupport_orig || !AsWMI_NB_RegisterEvent_orig
            || !AsWMI_NB_GetDeviceStatus_orig || !AsWMI_NB_GetDeviceStatus_MoreBYTE_orig
            || !AsWMI_NB_DeviceControl_orig || !AsWMI_NB_DeviceControl_2arg_orig) {
            printf("Could not locate function\n");
            fflush(stdout);
            return 0;
        }

        printf("LIB LOAD DONE\n");
        fflush(stdout);
    }

    return 1;
}

char __stdcall AsWMI_Open() {
    char ret = AsWMI_Open_orig();
    printf("AsWMI_Open: %02x\n", ret);
    fflush(stdout);
    return ret;
}

// stub
void __stdcall AsWMI_Close() {
    printf("AsWMI_Close\n");
    fflush(stdout);
}

char __stdcall AsWMI_CheckSupport() {
    char ret = AsWMI_CheckSupport_orig();
    printf("AsWMI_CheckSupport: %02x\n", ret);
    fflush(stdout);
    return ret;
}

void __stdcall AsWMI_NB_RegisterEvent() {
    AsWMI_NB_RegisterEvent_orig();
    printf("AsWMI_NB_RegisterEvent\n");
    fflush(stdout);
}

char __stdcall AsWMI_NB_GetDeviceStatus(int a, int* status) {
    char ret = AsWMI_NB_GetDeviceStatus_orig(a, status);
    printf("AsWMI_NB_GetDeviceStatus: %02x [a: %08x, status: %08x]\n", ret, a, *status);
    fflush(stdout);
    return ret;
}

// stub
void __stdcall AsWMI_NB_GetDeviceStatus_MoreBYTE() {
    printf("AsWMI_NB_GetDeviceStatus_MoreBYTE\n");
    fflush(stdout);
}

void __stdcall AsWMI_NB_DeviceControl(int a, int b) {
    AsWMI_NB_DeviceControl_orig(a, b);
    printf("AsWMI_NB_DeviceControl [a: %08x, b: %08x]\n", a, b);
    fflush(stdout);
}

char __stdcall AsWMI_NB_DeviceControl_2arg(int a, int b, int c) {
    char ret = AsWMI_NB_DeviceControl_2arg_orig(a, b, c);
    printf("AsWMI_NB_DeviceControl_2arg %02x [a: %08x, b: %08x, c: %08x]\n", ret, a, b, c);
    fflush(stdout);
    return ret;
}