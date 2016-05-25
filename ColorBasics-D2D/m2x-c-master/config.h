#ifndef M2X_CONFIG_H
#define M2X_CONFIG_H

/*
 * Long long signed integer type, which contains at least 64 bits in size,
 * is not in C89 standard.
 * As this library is conforming only to C89 standard, we cannot assume
 * that a 64-bit long long is always available. As a result, we provide
 * an option macro here, when ENABLE_LONG_LONG is defined, we will enable
 * the long long related part of the code.
 * If you are using an old compiler which does not support long long, you
 * can disable this macro.
 *
 * NOTE: long long is now only used in timestamp support. Disabling this
 * macro will still give you timestamp functions, however, those functions
 * will work with long instead of long long. On a system which long is
 * represented via 32-bit signed integer, the compiled code will only
 * work till 03:14:07 UTC on 19 January 2038.
 */
#define M2X_ENABLE_LONG_LONG

#endif  /* M2X_CONFIG_H */
