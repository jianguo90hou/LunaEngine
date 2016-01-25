
#pragma once

#ifdef RENDERER_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif // RENDERER_EXPORT






