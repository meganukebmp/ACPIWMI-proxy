#pragma once

#define DllExport __declspec(dllexport)

#include <stdio.h>
#include <stdint.h>


DllExport char __stdcall AsWMI_Open();
DllExport void __stdcall AsWMI_Close();
DllExport char __stdcall AsWMI_CheckSupport();
DllExport void __stdcall AsWMI_NB_RegisterEvent();
DllExport char __stdcall AsWMI_NB_GetDeviceStatus(int a, int* status);
DllExport void __stdcall AsWMI_NB_GetDeviceStatus_MoreBYTE();
DllExport void __stdcall AsWMI_NB_DeviceControl(int a, int b);
DllExport char __stdcall AsWMI_NB_DeviceControl_2arg(int a, int b, int c);