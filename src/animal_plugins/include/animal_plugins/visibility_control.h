#ifndef ANIMAL_PLUGINS__VISIBILITY_CONTROL_H_
#define ANIMAL_PLUGINS__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ANIMAL_PLUGINS_EXPORT __attribute__ ((dllexport))
    #define ANIMAL_PLUGINS_IMPORT __attribute__ ((dllimport))
  #else
    #define ANIMAL_PLUGINS_EXPORT __declspec(dllexport)
    #define ANIMAL_PLUGINS_IMPORT __declspec(dllimport)
  #endif
  #ifdef ANIMAL_PLUGINS_BUILDING_LIBRARY
    #define ANIMAL_PLUGINS_PUBLIC ANIMAL_PLUGINS_EXPORT
  #else
    #define ANIMAL_PLUGINS_PUBLIC ANIMAL_PLUGINS_IMPORT
  #endif
  #define ANIMAL_PLUGINS_PUBLIC_TYPE ANIMAL_PLUGINS_PUBLIC
  #define ANIMAL_PLUGINS_LOCAL
#else
  #define ANIMAL_PLUGINS_EXPORT __attribute__ ((visibility("default")))
  #define ANIMAL_PLUGINS_IMPORT
  #if __GNUC__ >= 4
    #define ANIMAL_PLUGINS_PUBLIC __attribute__ ((visibility("default")))
    #define ANIMAL_PLUGINS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ANIMAL_PLUGINS_PUBLIC
    #define ANIMAL_PLUGINS_LOCAL
  #endif
  #define ANIMAL_PLUGINS_PUBLIC_TYPE
#endif

#endif  // ANIMAL_PLUGINS__VISIBILITY_CONTROL_H_
