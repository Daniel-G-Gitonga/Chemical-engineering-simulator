#pragma once

#ifdef EXPORT_ROSES
   #define CHEM_ENG_ROSE __declspec(dllexport)
#else
   #define CHEM_ENG_ROSE __declspec(dllimport)
#endif

