/**
 * @file kernel/sys/version.c
 * @brief Kernel version macros.
 *
 * @copyright
 * This file is part of SiriusOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2011-2021 K. Lange
 * Copyright (C) 2024 Gamma Microsystems
 */

#include <kernel/version.h>

#define STR(x) #x
#define STRSTR(x) STR(x)

/* Kernel name. If you change this, you're not
 * my friend any more. - K. Lange */
const char * __kernel_name = "Misaka";

/* This really shouldn't change, and if it does,
 * always ensure it still has the correct arguments
 * when used as a vsprintf() format. */
const char * __kernel_version_format = "%d.%d.%d-%s";

/* Version numbers X.Y.Z */
int    __kernel_version_major = 0;
int    __kernel_version_minor = 0;
int    __kernel_version_lower = 1;

/* Kernel build suffix, which doesn't necessarily
 * mean anything, but can be used to distinguish
 * between different features included while
 * building multiple kernels. */
#ifdef KERNEL_GIT_TAG
# define KERNEL_VERSION_SUFFIX STRSTR(KERNEL_GIT_TAG)
#else
# define KERNEL_VERSION_SUFFIX "B"
#endif
const char * __kernel_version_suffix   = KERNEL_VERSION_SUFFIX;

/* The release codename. */
const char * __kernel_version_codename = "\"Bright Aurora\"";

/* Build architecture */
const char * __kernel_arch = STRSTR(KERNEL_ARCH);

/* Rebuild from clean to reset these. */
const char * __kernel_build_date = __DATE__;
const char * __kernel_build_time = __TIME__;

#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
# define COMPILER_VERSION "gcc " __VERSION__
#elif (defined(__clang__))
# define COMPILER_VERSION "clang " __clang_version__
#else
# define COMPILER_VERSION "alien-C-collection 14390KSF"
#endif

const char * __kernel_compiler_version = COMPILER_VERSION;
