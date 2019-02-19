#ifndef COMPILEMESSAGE__INC
#define COMPILEMESSAGE__INC
#pragma once

#define __STR(n) __STR__EXPAND(n)
#define __STR__EXPAND(n) #n

#define __FILE_HEAD "\"" __FILE__ "\""
#define __FUNC_HEAD "<" __FUNCTION__ ">"
#define __POS_HEAD __FILE_HEAD " " __STR(__LINE__) " : " __FUNC_HEAD
#define __MESSAGE_INFO(message) __POS_HEAD  " " message

#endif