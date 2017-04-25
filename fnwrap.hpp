/*

<scary-legal-text>

This file is licensed under the MIT Expat license:

Copyright (c) 2017 Ryan Gonzalez

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

</scary-legal-text>

*/

#ifndef FNWRAP_HPP
#define FNWRAP_HPP


#include <type_traits>
#include <functional>
#include <iostream>


#ifdef __clang__
#define FNWRAP_PRAGMA_PUSH \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wreturn-type\"") \
    _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
    _Pragma("clang diagnostic ignored \"-Wc++98-compat-pedantic\"") \
    _Pragma("clang diagnostic ignored \"-Wmissing-prototypes\"") \
    _Pragma("clang diagnostic ignored \"-Wunused-parameter\"") \
    _Pragma("clang diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"")
#define FNWRAP_PRAGMA_POP _Pragma("clang diagnostic pop")

#elif __GNUC__
#define FNWRAP_PRAGMA_PUSH \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")
#define FNWRAP_PRAGMA_POP _Pragma("GCC diagnostic pop")

#else
#define FNWRAP_PRAGMA_PUSH
#define FNWRAP_PRAGMA_POP
#endif


FNWRAP_PRAGMA_PUSH


#define FNWRAP_CONCAT2(a, b) a##b
#define FNWRAP_CONCAT(a, b) FNWRAP_CONCAT2(a, b)


#define FNWRAP_SEL_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, ...) _10

#define FNWRAP_LEN(...) \
    FNWRAP_SEL_10(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)


#define FNWRAP_IF_1(t, f) t
#define FNWRAP_IF_0(t, f) f
#define FNWRAP_IF(x, t, f) FNWRAP_CONCAT(FNWRAP_IF_, x)(t, f)

#define FNWRAP_AND(a, b) FNWRAP_IF(a, FNWRAP_IF(b, 1, 0), 0)
#define FNWRAP_NOT(x) FNWRAP_IF(x, 0, 1)


#define FNWRAP_PAREN_TRIGGER(...) ,
#define FNWRAP_HAS_COMMA(...) \
    FNWRAP_SEL_10(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#define FNWRAP_IS_TUPLE(x) FNWRAP_HAS_COMMA(FNWRAP_PAREN_TRIGGER x)

#define FNWRAP_IS_EMPTY(x) \
    FNWRAP_AND(FNWRAP_HAS_COMMA(FNWRAP_PAREN_TRIGGER x ()), \
               FNWRAP_NOT(FNWRAP_IS_TUPLE(x)))


#define FNWRAP_UNWRAP_PARENS2(...) __VA_ARGS__
#define FNWRAP_UNWRAP_PARENS(x) FNWRAP_IF(FNWRAP_IS_TUPLE(x), \
                                          FNWRAP_UNWRAP_PARENS2, ) x


#define FNWRAP_FOREACH_1(mc, d, v) mc(0, d, v)
#define FNWRAP_FOREACH_2(mc, d, v, ...) FNWRAP_FOREACH_1(mc, d, __VA_ARGS__) \
                                        mc(1, d, v)
#define FNWRAP_FOREACH_3(mc, d, v, ...) FNWRAP_FOREACH_2(mc, d, __VA_ARGS__) \
                                        mc(2, d, v)
#define FNWRAP_FOREACH_4(mc, d, v, ...) FNWRAP_FOREACH_3(mc, d, __VA_ARGS__) \
                                        mc(3, d, v)
#define FNWRAP_FOREACH_5(mc, d, v, ...) FNWRAP_FOREACH_4(mc, d, __VA_ARGS__) \
                                        mc(4, d, v)
#define FNWRAP_FOREACH_6(mc, d, v, ...) FNWRAP_FOREACH_5(mc, d, __VA_ARGS__) \
                                        mc(5, d, v)
#define FNWRAP_FOREACH_7(mc, d, v, ...) FNWRAP_FOREACH_6(mc, d, __VA_ARGS__) \
                                        mc(6, d, v)
#define FNWRAP_FOREACH_8(mc, d, v, ...) FNWRAP_FOREACH_7(mc, d, __VA_ARGS__) \
                                        mc(7, d, v)
#define FNWRAP_FOREACH_9(mc, d, v, ...) FNWRAP_FOREACH_8(mc, d, __VA_ARGS__) \
                                        mc(8, d, v)
#define FNWRAP_FOREACH_10(mc, d, v, ...) FNWRAP_FOREACH_9(mc, d, __VA_ARGS__) \
                                         mc(9, d, v)
#define FNWRAP_FOREACH(mc, d, ...) \
    FNWRAP_CONCAT(FNWRAP_FOREACH_, FNWRAP_LEN(__VA_ARGS__))(mc, d, __VA_ARGS__)


#define FNWRAP_TUPLE_GET_0(_0, ...) _0
#define FNWRAP_TUPLE_GET_1(_0, ...) FNWRAP_TUPLE_GET_0(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_2(_0, ...) FNWRAP_TUPLE_GET_1(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_3(_0, ...) FNWRAP_TUPLE_GET_2(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_4(_0, ...) FNWRAP_TUPLE_GET_3(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_5(_0, ...) FNWRAP_TUPLE_GET_4(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_6(_0, ...) FNWRAP_TUPLE_GET_5(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_7(_0, ...) FNWRAP_TUPLE_GET_6(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_8(_0, ...) FNWRAP_TUPLE_GET_7(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_9(_0, ...) FNWRAP_TUPLE_GET_8(__VA_ARGS__)
#define FNWRAP_TUPLE_GET_10(_0, ...) FNWRAP_TUPLE_GET_9(__VA_ARGS__)
#define FNWRAP_TUPLE_GET(n, t) \
    FNWRAP_CONCAT(FNWRAP_TUPLE_GET_, n) t


#define FNWRAP_TAIL2(x, ...) __VA_ARGS__
#define FNWRAP_TAIL(...) FNWRAP_TAIL2(__VA_ARGS__)


#define FNWRAP_FOREACH_N_1(mc, d) mc(0, d)
#define FNWRAP_FOREACH_N_2(mc, d) FNWRAP_FOREACH_N_1(mc, d) mc(1, d)
#define FNWRAP_FOREACH_N_3(mc, d) FNWRAP_FOREACH_N_2(mc, d) mc(2, d)
#define FNWRAP_FOREACH_N_4(mc, d) FNWRAP_FOREACH_N_3(mc, d) mc(3, d)
#define FNWRAP_FOREACH_N_5(mc, d) FNWRAP_FOREACH_N_4(mc, d) mc(4, d)
#define FNWRAP_FOREACH_N_6(mc, d) FNWRAP_FOREACH_N_5(mc, d) mc(5, d)
#define FNWRAP_FOREACH_N_7(mc, d) FNWRAP_FOREACH_N_6(mc, d) mc(6, d)
#define FNWRAP_FOREACH_N_8(mc, d) FNWRAP_FOREACH_N_7(mc, d) mc(7, d)
#define FNWRAP_FOREACH_N_9(mc, d) FNWRAP_FOREACH_N_8(mc, d) mc(8, d)
#define FNWRAP_FOREACH_N_10(mc, d) FNWRAP_FOREACH_N_9(mc, d) mc(9, d)
#define FNWRAP_FOREACH_N(mc, d, n) FNWRAP_CONCAT(FNWRAP_FOREACH_N_, n)(mc, d)


#define FNWRAP_FAIL(msg) ::fnwrap::fail(__func__, msg)


namespace fnwrap {
    void fail[[noreturn]](const char* func, const char* msg) {
        std::cerr << "fnwrap internal error:" << func << ": " << msg << '\n';
        abort();
    }


    struct null {};

    template <typename T>
    struct result { using type = T; };

    struct null_result : result<null> {};


    template <int N, typename... Args>
    struct index {};

    template <typename Arg, typename... Args>
    struct index<0, Arg, Args...> : result<Arg> {};

    template <int N, typename Arg, typename... Args>
    struct index<N, Arg, Args...> : index<N-1, Args...> {};

    template <int N>
    struct index<N> : null_result {};


    template <typename F>
    struct to_function : to_function<decltype(F::operator())> {};

    template <typename R, typename... Args>
    struct to_function<R(Args...)> : result<R(Args...)> {};

    template <typename R, typename... Args>
    struct to_function<R(*)(Args...)> : result<R(Args...)> {};

    template <typename T, typename R, typename... Args>
    struct to_function<R(T::*)(Args...)> : result<R(Args...)> {};


    template <typename T>
    struct count_args {};

    template <typename R, typename... Args>
    struct count_args<R(Args...)> {
        static constexpr int value = sizeof...(Args);
    };


    template <int N, typename F>
    struct get_narg {};

    template <int N, typename R, typename... Args>
    struct get_narg<N, R(Args...)> : index<N, Args...> {};


    template <typename F>
    struct get_return {};

    template <typename R, typename... Args>
    struct get_return<R(Args...)> : result<R> {};


    template <typename T>
    struct func2funcptr {};

    template <typename R, typename... Args>
    struct func2funcptr<R(Args...)> : result<R(*)(Args...)> {};


    class defer {
    public:
        using Func = std::function<void()>;
        defer(Func func_): func{func_} {}
        ~defer() { func(); }
    private:
        Func func;
    };


    template <typename T>
    T unsafe_declval() { return *static_cast<volatile T*>(NULL); }
    template <> void unsafe_declval<void>() {}


    struct anything {
        template <typename T>
        operator T() {
            FNWRAP_FAIL("anything was cast!");
            return unsafe_declval<T>();
        }
    };


    namespace arg_stubs {
        static anything a0, a1, a2, a3, a4, a5, a6, a7, a8, a9;
    }
}


#define FNWRAP_ARGS_ORIG 0
#define FNWRAP_ARGS_WHICH 1
#define FNWRAP_ARGS_WRAP 2
#define FNWRAP_ARGS_BEFORE 3
#define FNWRAP_ARGS_AFTER 4


#define FNWRAP_TY FNWRAP_CONCAT(__fnwrap_ty_, __LINE__)
#define FNWRAP_TY_PTR FNWRAP_CONCAT(__fnwrap_ty_ptr_, __LINE__)
#define FNWRAP_TY_RET FNWRAP_CONCAT(__fnwrap_ty_ret_, __LINE__)
#define FNWRAP_DECLS FNWRAP_CONCAT(__fnwrap_decls_, __LINE__)
#define FNWRAP_PROTO_STUBS FNWRAP_CONCAT(__fnwrap_proto_stubs_, __LINE__)


#define FNWRAP_DECLARE_ARG(index, data) \
    , ::fnwrap::get_narg<index, FNWRAP_TY>::type FNWRAP_CONCAT(a, index)
#define FNWRAP_FORWARD_ARG(index, data) , FNWRAP_CONCAT(a, index)


#define FNWRAP_PROTO(which, data, nargs) \
    FNWRAP_TUPLE_GET(which, data) \
        (FNWRAP_TAIL(FNWRAP_FOREACH_N(FNWRAP_DECLARE_ARG, data, nargs)))

#define FNWRAP_FORWARD_ARGS(data, nargs) \
    FNWRAP_TAIL(FNWRAP_FOREACH_N(FNWRAP_FORWARD_ARG, data, nargs))


#define FNWRAP_FULL_FUNCTION_NAME(which, orig) \
    FNWRAP_IF(FNWRAP_IS_EMPTY(which), orig, \
              static_cast<::fnwrap::func2funcptr< \
                                FNWRAP_UNWRAP_PARENS(which)>::type \
                          >(orig))


#define FNWRAP_DECLARE(index, data, nargs) \
    template <typename = void> \
    FNWRAP_TY_RET FNWRAP_PROTO(FNWRAP_ARGS_ORIG, data, nargs) { \
        FNWRAP_FAIL("inside proto stub! [nargs: " #nargs "]"); \
        return ::fnwrap::unsafe_declval<FNWRAP_TY_RET>(); \
    } \
    using ::FNWRAP_TUPLE_GET(FNWRAP_ARGS_ORIG, data); \
    FNWRAP_TY_RET FNWRAP_PROTO(FNWRAP_ARGS_WRAP, data, nargs) { \
        FNWRAP_TUPLE_GET(FNWRAP_ARGS_BEFORE, data); \
        ::fnwrap::defer fnwrap_deferred_expr{[&]() { \
            FNWRAP_TUPLE_GET(FNWRAP_ARGS_AFTER, data); \
        }}; \
        return FNWRAP_TUPLE_GET(FNWRAP_ARGS_ORIG, data) \
            (FNWRAP_FORWARD_ARGS(data, nargs)); \
    }


#define FNWRAP(orig, which, wrap, before, after) \
    FNWRAP_PRAGMA_PUSH \
    using FNWRAP_TY = ::fnwrap::to_function<decltype( \
        FNWRAP_FULL_FUNCTION_NAME(which, orig))>::type; \
    using FNWRAP_TY_PTR = ::fnwrap::func2funcptr<FNWRAP_TY>::type ; \
    using FNWRAP_TY_RET = ::fnwrap::get_return<FNWRAP_TY>::type; \
    namespace FNWRAP_DECLS { \
        using namespace ::fnwrap::arg_stubs; \
        FNWRAP_FOREACH(FNWRAP_DECLARE, (orig, which, wrap, before, after), \
                       0, 1, 2, 3, 4, 5, 6, 7, 8, 9) \
    } \
    constexpr FNWRAP_TY_PTR wrap = \
        static_cast<FNWRAP_TY_PTR>(FNWRAP_DECLS::wrap); \
    FNWRAP_PRAGMA_POP

FNWRAP_PRAGMA_POP

#endif
