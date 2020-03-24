#include<stdio.h>
#include<stdint.h>


typedef enum {
  /** The SDK function succeeded. @internal Numeric code: 0 @endinternal */ IOTC_STATE_OK = 0,
  /** @cond */ IOTC_ERROR_COUNT /** @endcond */ /* Add errors above this line; this should always be last line. */
} iotc_state_t;




#define IOTC_EVTD_GENERATE_EVENT_HANDLE_TYPEDEFS(ret, arg1, arg2, arg3, arg4, \
                                                 arg5, arg6)                  \
  typedef ret iotc_event_handle_return_t;                                     \
  typedef arg1 iotc_event_handle_arg1_t;                                      \
  typedef arg2 iotc_event_handle_arg2_t;                                      \
  typedef arg3 iotc_event_handle_arg3_t;                                      \
  typedef arg4 iotc_event_handle_arg4_t;                                      \
  typedef arg5 iotc_event_handle_arg5_t;                                      \
  typedef arg6 iotc_event_handle_arg6_t;                                      \
                                                                              \
  typedef iotc_event_handle_return_t(iotc_event_handle_func_argc0)(void);     \
  typedef iotc_event_handle_func_argc0* iotc_event_handle_func_argc0_ptr;     \
                                                                              \
  typedef iotc_event_handle_return_t(iotc_event_handle_func_argc1)(           \
      iotc_event_handle_arg1_t);                                              \
  typedef iotc_event_handle_func_argc1* iotc_event_handle_func_argc1_ptr;     \
                                                                              \
  typedef iotc_event_handle_return_t(iotc_event_handle_func_argc2)(           \
      iotc_event_handle_arg1_t, iotc_event_handle_arg2_t);                    \
  typedef iotc_event_handle_func_argc2* iotc_event_handle_func_argc2_ptr;     \
                                                                              \
  typedef iotc_event_handle_return_t(iotc_event_handle_func_argc3)(           \
      iotc_event_handle_arg1_t, iotc_event_handle_arg2_t,                     \
      iotc_event_handle_arg3_t);                                              \
  typedef iotc_event_handle_func_argc3* iotc_event_handle_func_argc3_ptr;     \
                                                                              \
  typedef iotc_event_handle_return_t(iotc_event_handle_func_argc4)(           \
      iotc_event_handle_arg1_t, iotc_event_handle_arg2_t,                     \
      iotc_event_handle_arg3_t, iotc_event_handle_arg4_t);                    \
  typedef iotc_event_handle_func_argc4* iotc_event_handle_func_argc4_ptr;     \
                                                                              \
  typedef iotc_event_handle_return_t(iotc_event_handle_func_argc5)(           \
      iotc_event_handle_arg1_t, iotc_event_handle_arg2_t,                     \
      iotc_event_handle_arg3_t, iotc_event_handle_arg4_t,                     \
      iotc_event_handle_arg5_t);                                              \
  typedef iotc_event_handle_func_argc5* iotc_event_handle_func_argc5_ptr;     \
                                                                              \
  typedef iotc_event_handle_return_t(iotc_event_handle_func_argc6)(           \
      iotc_event_handle_arg1_t, iotc_event_handle_arg2_t,                     \
      iotc_event_handle_arg3_t, iotc_event_handle_arg4_t,                     \
      iotc_event_handle_arg5_t, iotc_event_handle_arg6_t);                    \
  typedef iotc_event_handle_func_argc6* iotc_event_handle_func_argc6_ptr;\



IOTC_EVTD_GENERATE_EVENT_HANDLE_TYPEDEFS(iotc_state_t, void*, void*,
                                         iotc_state_t, void*, void*, void*);

typedef enum {
  IOTC_EVENT_HANDLE_UNSET = 0,
  IOTC_EVENT_HANDLE_ARGC0,
  IOTC_EVENT_HANDLE_ARGC1,
  IOTC_EVENT_HANDLE_ARGC2,
  IOTC_EVENT_HANDLE_ARGC3,
  IOTC_EVENT_HANDLE_ARGC4,
  IOTC_EVENT_HANDLE_ARGC5,
  IOTC_EVENT_HANDLE_ARGC6,
} iotc_event_handle_argc_t;

		
typedef struct iotc_event_handle_s {
  /* type of function pointer based on argument count */
  iotc_event_handle_argc_t handle_type;
#if IOTC_DEBUG_EXTRA_INFO
  struct {
    int debug_line_init;
    const char* debug_file_init;
    /* TODO:
     * int                     debug_line_last_call;
     * const char*             debug_file_last_call;
     * int                     debug_time_last_call; */
  } debug_info;
#endif
  union {
    struct {
      /* function pointer with 0 arguments */
      iotc_event_handle_func_argc0_ptr fn_argc0;
    } h0;

    struct {
      /* function pointer with 1 argument */
      iotc_event_handle_func_argc1_ptr fn_argc1;
      iotc_event_handle_arg1_t a1;
    } h1;

    struct {
      /* function pointer with 2 arguments */
      iotc_event_handle_func_argc2_ptr fn_argc2;
      iotc_event_handle_arg1_t a1;
      iotc_event_handle_arg2_t a2;
    } h2;

    struct {
      /* function pointer with 3 arguments */
      iotc_event_handle_func_argc3_ptr fn_argc3;
      iotc_event_handle_arg1_t a1;
      iotc_event_handle_arg2_t a2;
      iotc_event_handle_arg3_t a3;
    } h3;

    struct {
      /* function pointer with 4 arguments */
      iotc_event_handle_func_argc4_ptr fn_argc4;
      iotc_event_handle_arg1_t a1;
      iotc_event_handle_arg2_t a2;
      iotc_event_handle_arg3_t a3;
      iotc_event_handle_arg4_t a4;
    } h4;

    struct {
      /* function pointer with 5 arguments */
      iotc_event_handle_func_argc5_ptr fn_argc5;
      iotc_event_handle_arg1_t a1;
      iotc_event_handle_arg2_t a2;
      iotc_event_handle_arg3_t a3;
      iotc_event_handle_arg4_t a4;
      iotc_event_handle_arg5_t a5;
    } h5;

    struct {
      /* function pointer with 6 arguments */
      iotc_event_handle_func_argc6_ptr fn_argc6;
      iotc_event_handle_arg1_t a1;
      iotc_event_handle_arg2_t a2;
      iotc_event_handle_arg3_t a3;
      iotc_event_handle_arg4_t a4;
      iotc_event_handle_arg5_t a5;
      iotc_event_handle_arg6_t a6;
    } h6;
  } handlers;

  uint8_t target_tid;
} iotc_event_handle_t;


#define iotc_make_empty_event_handle(target_tid) \
  { -1, .handlers.h0 = {0}, target_tid }

iotc_event_handle_t iotc_make_empty_handle_impl(const uint8_t target_tid) {
  return (iotc_event_handle_t)iotc_make_empty_event_handle(target_tid);
}

iotc_event_handle_t iotc_make_handle_argc0(
    const uint8_t target_tid, iotc_event_handle_func_argc0_ptr fn_ptr) {
  return (iotc_event_handle_t){IOTC_EVENT_HANDLE_ARGC0, .handlers.h0 = {fn_ptr},
                               target_tid};
}

iotc_event_handle_t iotc_make_handle_argc1(
    const uint8_t target_tid, iotc_event_handle_func_argc1_ptr fn_ptr,
    iotc_event_handle_arg1_t a1) {
  return (iotc_event_handle_t){IOTC_EVENT_HANDLE_ARGC1,
                               .handlers.h1 = {fn_ptr, a1}, target_tid};
}

iotc_event_handle_t iotc_make_handle_argc2(
    const uint8_t target_tid, iotc_event_handle_func_argc2_ptr fn_ptr,
    iotc_event_handle_arg1_t a1, iotc_event_handle_arg2_t a2) {
  return (iotc_event_handle_t){IOTC_EVENT_HANDLE_ARGC2,
                               .handlers.h2 = {fn_ptr, a1, a2}, target_tid};
}

iotc_event_handle_t iotc_make_handle_argc3(
    const uint8_t target_tid, iotc_event_handle_func_argc3_ptr fn_ptr,
    iotc_event_handle_arg1_t a1, iotc_event_handle_arg2_t a2,
    iotc_event_handle_arg3_t a3) {
  return (iotc_event_handle_t){IOTC_EVENT_HANDLE_ARGC3,
                               .handlers.h3 = {fn_ptr, a1, a2, a3}, target_tid};
}

iotc_event_handle_t iotc_make_handle_argc4(
    const uint8_t target_tid, iotc_event_handle_func_argc4_ptr fn_ptr,
    iotc_event_handle_arg1_t a1, iotc_event_handle_arg2_t a2,
    iotc_event_handle_arg3_t a3, iotc_event_handle_arg4_t a4) {
  return (iotc_event_handle_t){IOTC_EVENT_HANDLE_ARGC4,
                               .handlers.h4 = {fn_ptr, a1, a2, a3, a4},
                               target_tid};
}

iotc_event_handle_t iotc_make_handle_argc5(
    const uint8_t target_tid, iotc_event_handle_func_argc5_ptr fn_ptr,
    iotc_event_handle_arg1_t a1, iotc_event_handle_arg2_t a2,
    iotc_event_handle_arg3_t a3, iotc_event_handle_arg4_t a4,
    iotc_event_handle_arg5_t a5) {
  return (iotc_event_handle_t){IOTC_EVENT_HANDLE_ARGC5,
                               .handlers.h5 = {fn_ptr, a1, a2, a3, a4, a5},
                               target_tid};
}

iotc_event_handle_t iotc_make_handle_argc6(
    const uint8_t target_tid, iotc_event_handle_func_argc6_ptr fn_ptr,
    iotc_event_handle_arg1_t a1, iotc_event_handle_arg2_t a2,
    iotc_event_handle_arg3_t a3, iotc_event_handle_arg4_t a4,
    iotc_event_handle_arg5_t a5, iotc_event_handle_arg5_t a6) {
  return (iotc_event_handle_t){IOTC_EVENT_HANDLE_ARGC6,
                               .handlers.h6 = {fn_ptr, a1, a2, a3, a4, a5, a6},
                               target_tid};
}

//
//     impl(0, func, a1, a2, IOTC_STATE_OK, arg6(), arg5(), arg4(), arg3(), arg2(), arg1(), arg0(), 0 )
//threadid:_0,   _1, _2, _3,  _4,           _5,      _6,      _7,     N,     ...)
// result: arg3 

// impl(0, func, arg6(), arg5(), arg4(), arg3(), arg2(), arg1(), arg0(), 0 )
//     _0,  _1,   _2,    _3,      _4,    _5,      _6,     _7,       N  , ...
//result : arg0()    
#define iotc_make_handle_impl(_0, _1, _2, _3, _4, _5, _6, _7, N, ...) N


#define iotc_make_threaded_handle(...)                                        \
  iotc_make_handle_impl(__VA_ARGS__, iotc_make_handle_argc6(__VA_ARGS__),     \
                        iotc_make_handle_argc5(__VA_ARGS__),                  \
                        iotc_make_handle_argc4(__VA_ARGS__),                  \
                        iotc_make_handle_argc3(__VA_ARGS__),                  \
                        iotc_make_handle_argc2(__VA_ARGS__),                  \
                        iotc_make_handle_argc1(__VA_ARGS__),                  \
                        iotc_make_handle_argc0(__VA_ARGS__),                  \
                        0) /* the last 0 to not alow tha impl macro to not to \
                            * have last parameter in case of 1 arg passed */

/**
 * Idea for that macro trick has been taken from the other macro
 * that counts the number of arguments of variadic macro. The rule
 * and generic idea is the same. The iotc_make_handle_impl takes always
 * Nth argument and uses it for macro substitution. The N has to be const
 * and it's 6 in our case since macro 'iotc_make_handle' can be called
 * at most with 6 arguments: threadid, fnptr + 4args.
 */
#define iotc_make_handle(...) iotc_make_threaded_handle(0, __VA_ARGS__)



int iotc_evtd_execute_handle(
    iotc_event_handle_t* handle) {
  switch (handle->handle_type) {
    case IOTC_EVENT_HANDLE_ARGC0:
      return (*handle->handlers.h0.fn_argc0)();
    case IOTC_EVENT_HANDLE_ARGC1:
      return (*handle->handlers.h1.fn_argc1)(handle->handlers.h1.a1);
    case IOTC_EVENT_HANDLE_ARGC2:
      return (*handle->handlers.h2.fn_argc2)(handle->handlers.h2.a1,
                                             handle->handlers.h2.a2);
    case IOTC_EVENT_HANDLE_ARGC3:
      return (*handle->handlers.h3.fn_argc3)(handle->handlers.h3.a1,
                                             handle->handlers.h3.a2,
                                             handle->handlers.h3.a3);
    case IOTC_EVENT_HANDLE_ARGC4:
      return (*handle->handlers.h4.fn_argc4)(
          handle->handlers.h4.a1, handle->handlers.h4.a2,
          handle->handlers.h4.a3, handle->handlers.h4.a4);
    case IOTC_EVENT_HANDLE_ARGC5:
      return (*handle->handlers.h5.fn_argc5)(
          handle->handlers.h5.a1, handle->handlers.h5.a2,
          handle->handlers.h5.a3, handle->handlers.h5.a4,
          handle->handlers.h5.a5);
    case IOTC_EVENT_HANDLE_ARGC6:
      return (*handle->handlers.h6.fn_argc6)(
          handle->handlers.h6.a1, handle->handlers.h6.a2,
          handle->handlers.h6.a3, handle->handlers.h6.a4,
          handle->handlers.h6.a5, handle->handlers.h6.a6);
    case IOTC_EVENT_HANDLE_UNSET:
      printf("you are trying to call an unset handler!");
#if IOTC_DEBUG_EXTRA_INFO
      iotc_debug_format("handler created in %s:%d",
                        handle->debug_info.debug_file_init,
                        handle->debug_info.debug_line_init);
#endif
      return (iotc_event_handle_return_t)-1;
  }

  return (iotc_event_handle_return_t)IOTC_STATE_OK;
}

int function_add(int *a1, int *a2, int result)
{
  printf("result:%d", *a1 + *a2);

  return result;
}

int main()
{
  void * func = function_add;
  int a1 = 1;
  int a2 = 2;

  iotc_event_handle_t handle = iotc_make_threaded_handle(0, func, &a1, &a2, IOTC_STATE_OK);

  iotc_evtd_execute_handle( &handle );

  return 0;	
}

