// Created via CMake from template global.h.in
// WARNING! Any changes to this file will be overwritten by the next CMake run!

#ifndef LMDB_SAFE_GLOBAL
#define LMDB_SAFE_GLOBAL

#include <c++utilities/application/global.h>

#ifdef LMDB_SAFE_STATIC
#define LMDB_SAFE_EXPORT
#define LMDB_SAFE_IMPORT
#else
#define LMDB_SAFE_EXPORT CPP_UTILITIES_GENERIC_LIB_EXPORT
#define LMDB_SAFE_IMPORT CPP_UTILITIES_GENERIC_LIB_IMPORT
#endif

/*!
 * \def LMDB_SAFE_EXPORT
 * \brief Marks the symbol to be exported by the lmdb-safe library.
 */

/*!
 * \def LMDB_SAFE_IMPORT
 * \brief Marks the symbol to be imported from the lmdb-safe library.
 */

#endif // LMDB_SAFE_GLOBAL
