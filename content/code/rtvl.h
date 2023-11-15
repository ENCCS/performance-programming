#ifndef RTVL_H
#ifdef RTVL
static inline long rtvl(long n) { return (n+3) & ~3LL; }
#else
static inline long rtvl(long n) { return n; }
#endif
#endif // RTVL_H
