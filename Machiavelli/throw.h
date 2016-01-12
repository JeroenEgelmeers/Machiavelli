// throw macros for OS X and other POSIX systems
// adapted for Windows as well, november 2014
// copyright © 2002-2014 Bob Polis

#ifndef __throw__
#define __throw__

// don't call these yourself; use the macros below instead
void __throw_if_min1(int x, const char* file, unsigned int line, const char* message = nullptr);
void __throw_if_null(const void* p, const char* file, unsigned int line, const char* message = nullptr);
void __throw_if_err(int err, const char* file, unsigned int line, const char* message = nullptr);

#define throw_if_min1(___x___)					__throw_if_min1((___x___), __FILE__, __LINE__)
#define throw_if_null(__ptr__)					__throw_if_null((__ptr__), __FILE__, __LINE__)
#define throw_if_err(__err__)					__throw_if_err((__err__), __FILE__, __LINE__)

#define throw_if_min1_msg(___x___, ___msg___)	__throw_if_min1((___x___), __FILE__, __LINE__, ___msg___)
#define throw_if_null_msg(__ptr__, ___msg___)	__throw_if_null((__ptr__), __FILE__, __LINE__, ___msg___)
#define throw_if_err_msg(__err__, ___msg___)		__throw_if_err((__err__), __FILE__, __LINE__, ___msg___)

#endif /* defined(__throw__) */
