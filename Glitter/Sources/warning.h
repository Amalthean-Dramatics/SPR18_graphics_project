/**
 * Name: Riley Myers
 * File Name: warning.h
 * Synopsis: This file contains various macros to help output warning and error
 * messages.
 */

#pragma once
#include <string>

// Note that these are bolded.
#define RED     "\e[1;31m"
#define BLUE    "\e[1;34m"
#define GREEN   "\e[1;32m"
#define YELLOW  "\e[1;33m"
#define MAGENT  "\e[1;35m"
#define CYAN    "\e[1;36m"

#define BRED    "\e[1;91m"
#define BBLUE   "\e[1;94m"
#define BGREEN  "\e[1;92m"
#define BYELLOW "\e[1;93m"
#define BMAGENT "\e[1;95m"
#define BCYAN   "\e[1;96m"

#define END     "\e[0m"

#define ERRCOL RED
#define WRNCOL YELLOW
#define ENDCOL END
