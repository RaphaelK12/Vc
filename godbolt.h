#ifndef VC_VECTOR_H_
#define VC_VECTOR_H_ 
#ifndef VC_SCALAR_VECTOR_H_
#define VC_SCALAR_VECTOR_H_ 
#include <assert.h>
#include <algorithm>
#include <cmath>
#ifdef _MSC_VER
#include <float.h>
#endif
#ifndef VC_COMMON_TYPES_H_
#define VC_COMMON_TYPES_H_ 
#ifdef Vc_CHECK_ALIGNMENT
#include <cstdlib>
#include <cstdio>
#endif
#ifndef VC_GLOBAL_H_
#define VC_GLOBAL_H_ 
#include <cstdint>
#ifndef VC_FWDDECL_H_
#define VC_FWDDECL_H_ 
#define Vc_VERSIONED_NAMESPACE Vc_1
namespace Vc_VERSIONED_NAMESPACE
{
namespace VectorAbi
{
struct Scalar {};
struct Sse {};
struct Avx {};
struct Mic {};
template <class T> struct DeduceCompatible;
template <class T> struct DeduceBest;
}
namespace Common
{
template <class T, std::size_t N> struct select_best_vector_type;
}
template <class T, class Abi> class Mask;
template <class T, class Abi> class Vector;
template <class T, std::size_t N,
class V = typename Common::select_best_vector_type<T, N>::type,
std::size_t Wt = V::Size>
class SimdArray;
template <class T, std::size_t N,
class V = typename Common::select_best_vector_type<T, N>::type,
std::size_t Wt = V::Size>
class SimdMaskArray;
namespace simd_abi
{
using scalar = VectorAbi::Scalar;
template <int N> struct fixed_size;
template <class T> using compatible = typename VectorAbi::DeduceCompatible<T>::type;
template <class T> using native = typename VectorAbi::DeduceBest<T>::type;
using __sse = VectorAbi::Sse;
using __avx = VectorAbi::Avx;
struct __avx512;
struct __neon;
}
template <class T, class Abi = simd_abi::compatible<T>> using simd = Vector<T, Abi>;
template <class T, class Abi = simd_abi::compatible<T>> using simd_mask = Mask<T, Abi>;
template <class T> using native_simd = simd<T, simd_abi::native<T>>;
template <class T> using native_simd_mask = simd_mask<T, simd_abi::native<T>>;
template <class T, int N> using fixed_size_simd = simd<T, simd_abi::fixed_size<N>>;
template <class T, int N>
using fixed_size_simd_mask = simd_mask<T, simd_abi::fixed_size<N>>;
}
#ifndef DOXYGEN
namespace Vc = Vc_VERSIONED_NAMESPACE;
#endif
#endif
#ifdef DOXYGEN
#define Vc_ICC __INTEL_COMPILER_BUILD_DATE
#undef Vc_ICC
#define Vc_CLANG (__clang_major__ * 0x10000 + __clang_minor__ * 0x100 + __clang_patchlevel__)
#undef Vc_CLANG
#define Vc_APPLECLANG (__clang_major__ * 0x10000 + __clang_minor__ * 0x100 + __clang_patchlevel__)
#undef Vc_APPLECLANG
#define Vc_GCC (__GNUC__ * 0x10000 + __GNUC_MINOR__ * 0x100 + __GNUC_PATCHLEVEL__)
#define Vc_MSVC _MSC_FULL_VER
#undef Vc_MSVC
#else
#ifdef __INTEL_COMPILER
#define Vc_ICC __INTEL_COMPILER_BUILD_DATE
#elif defined(__clang__) && defined(__APPLE__) && __clang_major__ >= 6
#define Vc_APPLECLANG (__clang_major__ * 0x10000 + __clang_minor__ * 0x100 + __clang_patchlevel__)
#elif defined(__clang__)
#define Vc_CLANG (__clang_major__ * 0x10000 + __clang_minor__ * 0x100 + __clang_patchlevel__)
#elif defined(__GNUC__)
#define Vc_GCC (__GNUC__ * 0x10000 + __GNUC_MINOR__ * 0x100 + __GNUC_PATCHLEVEL__)
#elif defined(_MSC_VER)
#define Vc_MSVC _MSC_FULL_VER
#else
#define Vc_UNSUPPORTED_COMPILER 1
#endif
#if defined Vc_GCC && Vc_GCC >= 0x60000
#define Vc_RESET_DIAGNOSTICS _Pragma("GCC diagnostic pop")
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#else
#define Vc_RESET_DIAGNOSTICS 
#endif
#if defined Vc_ICC
#pragma warning disable 2922
#endif
#if __cplusplus < 201103 && (!defined Vc_MSVC || _MSC_VER < 1900)
# error "Vc requires support for C++11."
#elif __cplusplus >= 201402L
#define Vc_CXX14 1
# if __cplusplus > 201700L
#define Vc_CXX17 1
# endif
#endif
#if defined(__GNUC__) && !defined(Vc_NO_INLINE_ASM)
#define Vc_GNU_ASM 1
#endif
#ifdef Vc_GCC
#define Vc_HAVE_MAX_ALIGN_T 1
#elif !defined(Vc_CLANG) && !defined(Vc_ICC)
#define Vc_HAVE_STD_MAX_ALIGN_T 1
#endif
#if defined(Vc_GCC) || defined(Vc_CLANG) || defined Vc_APPLECLANG
#define Vc_USE_BUILTIN_VECTOR_TYPES 1
#endif
#ifdef Vc_MSVC
#define Vc_CDECL __cdecl
#define Vc_VDECL __vectorcall
#else
#define Vc_CDECL 
#define Vc_VDECL 
#endif
#define Scalar 0x00100000
#define SSE 0x00200000
#define SSE2 0x00300000
#define SSE3 0x00400000
#define SSSE3 0x00500000
#define SSE4_1 0x00600000
#define SSE4_2 0x00700000
#define AVX 0x00800000
#define AVX2 0x00900000
#define XOP 0x00000001
#define FMA4 0x00000002
#define F16C 0x00000004
#define POPCNT 0x00000008
#define SSE4a 0x00000010
#define FMA 0x00000020
#define BMI2 0x00000040
#define IMPL_MASK 0xFFF00000
#define EXT_MASK 0x000FFFFF
#ifdef Vc_MSVC
# ifdef _M_IX86_FP
# if _M_IX86_FP >= 1
# ifndef __SSE__
#define __SSE__ 1
# endif
# endif
# if _M_IX86_FP >= 2
# ifndef __SSE2__
#define __SSE2__ 1
# endif
# endif
# elif defined(_M_AMD64)
# ifndef __SSE__
#define __SSE__ 1
# endif
# ifndef __SSE2__
#define __SSE2__ 1
# endif
# endif
#endif
#if defined Vc_ICC && !defined __POPCNT__
# if defined __SSE4_2__ || defined __SSE4A__
#define __POPCNT__ 1
# endif
#endif
#ifdef VC_IMPL
#error "You are using the old VC_IMPL macro. Since Vc 1.0 all Vc macros start with Vc_, i.e. a lower-case 'c'"
#endif
#ifndef Vc_IMPL
# if defined(__AVX2__)
#define Vc_IMPL_AVX2 1
#define Vc_IMPL_AVX 1
# elif defined(__AVX__)
#define Vc_IMPL_AVX 1
# else
# if defined(__SSE4_2__)
#define Vc_IMPL_SSE 1
#define Vc_IMPL_SSE4_2 1
# endif
# if defined(__SSE4_1__)
#define Vc_IMPL_SSE 1
#define Vc_IMPL_SSE4_1 1
# endif
# if defined(__SSE3__)
#define Vc_IMPL_SSE 1
#define Vc_IMPL_SSE3 1
# endif
# if defined(__SSSE3__)
#define Vc_IMPL_SSE 1
#define Vc_IMPL_SSSE3 1
# endif
# if defined(__SSE2__)
#define Vc_IMPL_SSE 1
#define Vc_IMPL_SSE2 1
# endif
# if defined(Vc_IMPL_SSE)
# else
#define Vc_IMPL_Scalar 1
# endif
# endif
# if !defined(Vc_IMPL_Scalar)
# ifdef __FMA4__
#define Vc_IMPL_FMA4 1
# endif
# ifdef __XOP__
#define Vc_IMPL_XOP 1
# endif
# ifdef __F16C__
#define Vc_IMPL_F16C 1
# endif
# ifdef __POPCNT__
#define Vc_IMPL_POPCNT 1
# endif
# ifdef __SSE4A__
#define Vc_IMPL_SSE4a 1
# endif
# ifdef __FMA__
#define Vc_IMPL_FMA 1
# endif
# ifdef __BMI2__
#define Vc_IMPL_BMI2 1
# endif
# endif
#else
# if (Vc_IMPL & IMPL_MASK) == AVX2
#define Vc_IMPL_AVX2 1
#define Vc_IMPL_AVX 1
# elif (Vc_IMPL & IMPL_MASK) == AVX
#define Vc_IMPL_AVX 1
# elif (Vc_IMPL & IMPL_MASK) == Scalar
#define Vc_IMPL_Scalar 1
# elif (Vc_IMPL & IMPL_MASK) == SSE4_2
#define Vc_IMPL_SSE4_2 1
#define Vc_IMPL_SSE4_1 1
#define Vc_IMPL_SSSE3 1
#define Vc_IMPL_SSE3 1
#define Vc_IMPL_SSE2 1
#define Vc_IMPL_SSE 1
# elif (Vc_IMPL & IMPL_MASK) == SSE4_1
#define Vc_IMPL_SSE4_1 1
#define Vc_IMPL_SSSE3 1
#define Vc_IMPL_SSE3 1
#define Vc_IMPL_SSE2 1
#define Vc_IMPL_SSE 1
# elif (Vc_IMPL & IMPL_MASK) == SSSE3
#define Vc_IMPL_SSSE3 1
#define Vc_IMPL_SSE3 1
#define Vc_IMPL_SSE2 1
#define Vc_IMPL_SSE 1
# elif (Vc_IMPL & IMPL_MASK) == SSE3
#define Vc_IMPL_SSE3 1
#define Vc_IMPL_SSE2 1
#define Vc_IMPL_SSE 1
# elif (Vc_IMPL & IMPL_MASK) == SSE2
#define Vc_IMPL_SSE2 1
#define Vc_IMPL_SSE 1
# elif (Vc_IMPL & IMPL_MASK) == SSE
#define Vc_IMPL_SSE 1
# if defined(__SSE4_2__)
#define Vc_IMPL_SSE4_2 1
# endif
# if defined(__SSE4_1__)
#define Vc_IMPL_SSE4_1 1
# endif
# if defined(__SSE3__)
#define Vc_IMPL_SSE3 1
# endif
# if defined(__SSSE3__)
#define Vc_IMPL_SSSE3 1
# endif
# if defined(__SSE2__)
#define Vc_IMPL_SSE2 1
# endif
# elif (Vc_IMPL & IMPL_MASK) == 0 && (Vc_IMPL & SSE4a)
#define Vc_IMPL_SSE3 1
#define Vc_IMPL_SSE2 1
#define Vc_IMPL_SSE 1
# endif
# if (Vc_IMPL & XOP)
#define Vc_IMPL_XOP 1
# endif
# if (Vc_IMPL & FMA4)
#define Vc_IMPL_FMA4 1
# endif
# if (Vc_IMPL & F16C)
#define Vc_IMPL_F16C 1
# endif
# if (!defined(Vc_IMPL_Scalar) && defined(__POPCNT__)) || (Vc_IMPL & POPCNT)
#define Vc_IMPL_POPCNT 1
# endif
# if (Vc_IMPL & SSE4a)
#define Vc_IMPL_SSE4a 1
# endif
# if (Vc_IMPL & FMA)
#define Vc_IMPL_FMA 1
# endif
# if (Vc_IMPL & BMI2)
#define Vc_IMPL_BMI2 1
# endif
#undef Vc_IMPL
#endif
#ifdef __AVX__
#define Vc_USE_VEX_CODING 1
#endif
#ifdef Vc_IMPL_AVX
#define Vc_IMPL_SSE4_2 1
#define Vc_IMPL_SSE4_1 1
#define Vc_IMPL_SSSE3 1
#define Vc_IMPL_SSE3 1
#define Vc_IMPL_SSE2 1
#define Vc_IMPL_SSE 1
#endif
#if defined(Vc_CLANG) && Vc_CLANG >= 0x30600 && Vc_CLANG < 0x30700
# if defined(Vc_IMPL_AVX)
# warning "clang 3.6.x miscompiles AVX code, frequently losing 50% of the data. Vc will fall back to SSE4 instead."
#undef Vc_IMPL_AVX
# if defined(Vc_IMPL_AVX2)
#undef Vc_IMPL_AVX2
# endif
# endif
#endif
# if !defined(Vc_IMPL_Scalar) && !defined(Vc_IMPL_SSE) && !defined(Vc_IMPL_AVX)
# error "No suitable Vc implementation was selected! Probably Vc_IMPL was set to an invalid value."
# elif defined(Vc_IMPL_SSE) && !defined(Vc_IMPL_SSE2)
# error "SSE requested but no SSE2 support. Vc needs at least SSE2!"
# endif
#undef Scalar
#undef SSE
#undef SSE2
#undef SSE3
#undef SSSE3
#undef SSE4_1
#undef SSE4_2
#undef AVX
#undef AVX2
#undef XOP
#undef FMA4
#undef F16C
#undef POPCNT
#undef SSE4a
#undef FMA
#undef BMI2
#undef IMPL_MASK
#undef EXT_MASK
#if defined Vc_IMPL_AVX2
#define Vc_DEFAULT_IMPL_AVX2 
#elif defined Vc_IMPL_AVX
#define Vc_DEFAULT_IMPL_AVX 
#elif defined Vc_IMPL_SSE
#define Vc_DEFAULT_IMPL_SSE 
#elif defined Vc_IMPL_Scalar
#define Vc_DEFAULT_IMPL_Scalar 
#else
#error "Preprocessor logic broken. Please report a bug."
#endif
#endif
namespace Vc_VERSIONED_NAMESPACE
{
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
enum MallocAlignment {
AlignOnVector,
AlignOnCacheline,
AlignOnPage
};
enum Implementation : std::uint_least32_t {
ScalarImpl,
SSE2Impl,
SSE3Impl,
SSSE3Impl,
SSE41Impl,
SSE42Impl,
AVXImpl,
AVX2Impl,
MICImpl,
ImplementationMask = 0xfff
};
enum ExtraInstructions : std::uint_least32_t {
Float16cInstructions = 0x01000,
Fma4Instructions = 0x02000,
XopInstructions = 0x04000,
PopcntInstructions = 0x08000,
Sse4aInstructions = 0x10000,
FmaInstructions = 0x20000,
VexInstructions = 0x40000,
Bmi2Instructions = 0x80000,
ExtraInstructionsMask = 0xfffff000u
};
template <unsigned int Features> struct ImplementationT {
static constexpr Implementation current()
{
return static_cast<Implementation>(Features & ImplementationMask);
}
static constexpr bool is(Implementation impl)
{
return static_cast<unsigned int>(impl) == current();
}
static constexpr bool is_between(Implementation low, Implementation high)
{
return static_cast<unsigned int>(low) <= current() &&
static_cast<unsigned int>(high) >= current();
}
static constexpr bool runs_on(unsigned int extraInstructions)
{
return (extraInstructions & Features & ExtraInstructionsMask) ==
(Features & ExtraInstructionsMask);
}
};
using CurrentImplementation = ImplementationT<
#ifdef Vc_IMPL_Scalar
ScalarImpl
#elif defined(Vc_IMPL_AVX2)
AVX2Impl
#elif defined(Vc_IMPL_AVX)
AVXImpl
#elif defined(Vc_IMPL_SSE4_2)
SSE42Impl
#elif defined(Vc_IMPL_SSE4_1)
SSE41Impl
#elif defined(Vc_IMPL_SSSE3)
SSSE3Impl
#elif defined(Vc_IMPL_SSE3)
SSE3Impl
#elif defined(Vc_IMPL_SSE2)
SSE2Impl
#endif
#ifdef Vc_IMPL_SSE4a
+ Vc::Sse4aInstructions
#ifdef Vc_IMPL_XOP
+ Vc::XopInstructions
#ifdef Vc_IMPL_FMA4
+ Vc::Fma4Instructions
#endif
#endif
#endif
#ifdef Vc_IMPL_POPCNT
+ Vc::PopcntInstructions
#endif
#ifdef Vc_IMPL_FMA
+ Vc::FmaInstructions
#endif
#ifdef Vc_IMPL_BMI2
+ Vc::Bmi2Instructions
#endif
#ifdef Vc_USE_VEX_CODING
+ Vc::VexInstructions
#endif
>;
}
#ifndef VC_VERSION_H_
#define VC_VERSION_H_ 
#define Vc_VERSION_STRING "1.3.80-dev"
#define Vc_VERSION_NUMBER 0x0103a1
#define Vc_VERSION_CHECK(major,minor,patch) ((major << 16) | (minor << 8) | (patch << 1))
#define Vc_LIBRARY_ABI_VERSION 5
#define Vc_IS_VERSION_2 (Vc_VERSION_NUMBER >= Vc_VERSION_CHECK(1, 70, 0))
#define Vc_IS_VERSION_1 (Vc_VERSION_NUMBER < Vc_VERSION_CHECK(1, 70, 0))
namespace Vc_VERSIONED_NAMESPACE
{
inline const char *versionString() { return Vc_VERSION_STRING; }
constexpr unsigned int versionNumber() { return Vc_VERSION_NUMBER; }
}
#endif
#endif
#ifndef VC_TRAITS_TYPE_TRAITS_H_
#define VC_TRAITS_TYPE_TRAITS_H_ 
#include <type_traits>
#ifndef VC_TRAITS_DECAY_H_
#define VC_TRAITS_DECAY_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
template <typename T> using decay = typename std::decay<T>::type;
}
}
#endif
#ifndef VC_TRAITS_HAS_NO_ALLOCATED_DATA_H_
#define VC_TRAITS_HAS_NO_ALLOCATED_DATA_H_ 
#include <array>
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
template<typename T> struct has_no_allocated_data_impl : public std::false_type {};
template <typename T>
struct has_no_allocated_data
: public has_no_allocated_data_impl<
typename std::remove_cv<typename std::remove_reference<T>::type>::type>
{
};
template<typename T, std::size_t N> struct has_no_allocated_data_impl<std::array<T, N>> : public std::true_type {};
template<typename T, std::size_t N> struct has_no_allocated_data_impl<T[N]> : public std::true_type {};
template<typename T> struct has_no_allocated_data_impl<T[]> : public std::true_type {};
static_assert(has_no_allocated_data<int[256]>::value, "");
static_assert(has_no_allocated_data<const int[256]>::value, "");
static_assert(has_no_allocated_data<volatile int[256]>::value, "");
static_assert(has_no_allocated_data<const volatile int[256]>::value, "");
static_assert(has_no_allocated_data<int[]>::value, "");
static_assert(has_no_allocated_data<int[2][2]>::value, "");
static_assert(has_no_allocated_data<const volatile std::array<int, 256> &>::value, "");
static_assert(has_no_allocated_data<const volatile std::array<int, 256>>::value, "");
static_assert(has_no_allocated_data<volatile std::array<int, 256> &>::value, "");
static_assert(has_no_allocated_data<volatile std::array<int, 256>>::value, "");
static_assert(has_no_allocated_data<const std::array<int, 256> &>::value, "");
static_assert(has_no_allocated_data<const std::array<int, 256>>::value, "");
static_assert(has_no_allocated_data<std::array<int, 256>>::value, "");
static_assert(has_no_allocated_data<std::array<int, 256> &&>::value, "");
static_assert(!has_no_allocated_data<int*>::value, "");
static_assert(!has_no_allocated_data<const int*>::value, "");
static_assert(!has_no_allocated_data<const int *const>::value, "");
static_assert(!has_no_allocated_data<int *const>::value, "");
}
}
#endif
#ifndef VC_TRAITS_HAS_CONTIGUOUS_STORAGE_H_
#define VC_TRAITS_HAS_CONTIGUOUS_STORAGE_H_ 
#include <initializer_list>
#include <memory>
#ifdef _LIBCPP_BEGIN_NAMESPACE_STD
_LIBCPP_BEGIN_NAMESPACE_STD
#else
namespace std
{
#endif
#ifdef _WIN32
template <typename T, size_t N> class array;
#else
template <typename T, size_t N> struct array;
#endif
template <typename T, typename Allocator> class vector;
#ifdef _LIBCPP_END_NAMESPACE_STD
_LIBCPP_END_NAMESPACE_STD
#else
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
namespace has_contiguous_storage_detail
{
template <typename T, typename It = typename T::iterator>
std::is_base_of<std::random_access_iterator_tag,
typename It::iterator_category>
test(int);
template <typename T>
std::is_base_of<std::random_access_iterator_tag,
typename T::iterator_category>
test(long);
template <typename T> std::false_type test(...);
}
template <typename T>
struct has_contiguous_storage_impl
: public decltype(has_contiguous_storage_detail::test<T>(int())) {
};
template <typename T>
struct has_contiguous_storage
: public has_contiguous_storage_impl<
typename std::remove_cv<typename std::remove_reference<T>::type>::type>
{
};
template <typename T> struct has_contiguous_storage_impl<const T *> : public std::true_type {};
template <typename T> struct has_contiguous_storage_impl<T *> : public std::true_type {};
template <typename T> struct has_contiguous_storage_impl<std::unique_ptr<T[]>> : public std::true_type {};
template <typename T> struct has_contiguous_storage_impl<std::initializer_list<T>> : public std::true_type {};
template <typename T, std::size_t N> struct has_contiguous_storage_impl<T[N]> : public std::true_type {};
template <typename T, std::size_t N> struct has_contiguous_storage_impl<std::array<T, N>> : public std::true_type {};
template <typename T, typename A> struct has_contiguous_storage_impl<std::vector<T, A>> : public std::true_type {};
}
}
#endif
#ifndef VC_TRAITS_IS_INITIALIZER_LIST_H_
#define VC_TRAITS_IS_INITIALIZER_LIST_H_ 
#include <initializer_list>
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
namespace is_initializer_list_impl
{
template <typename... Args> struct test : public std::false_type {};
template <typename I> struct test<std::initializer_list<I>> : public std::true_type {};
}
template <typename... Args>
struct is_initializer_list
: public is_initializer_list_impl::test<decay<Args>...>
{
};
}
}
#endif
#ifndef VC_TRAITS_IS_LOAD_ARGUMENTS_H_
#define VC_TRAITS_IS_LOAD_ARGUMENTS_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
template <typename T> struct is_load_store_flag;
template <typename... Args> struct is_load_arguments : public std::false_type {};
template <typename U> struct is_load_arguments<U> : public std::is_pointer<U> {};
template <typename U, typename F>
struct is_load_arguments<U, F> : public std::integral_constant<
bool,
std::is_pointer<U>::value&& is_load_store_flag<F>::value>
{
};
}
}
#endif
#ifndef VC_TRAITS_IS_FUNCTOR_ARGUMENT_IMMUTABLE_H_
#define VC_TRAITS_IS_FUNCTOR_ARGUMENT_IMMUTABLE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
namespace is_functor_argument_immutable_impl
{
template <typename F, typename A> std::true_type test(void (F::*)(A));
template <typename F, typename A> std::true_type test(void (F::*)(A) const);
template <typename F, typename A> std::is_const<A> test(void (F::*)(A &));
template <typename F, typename A> std::is_const<A> test(void (F::*)(A &) const);
template <typename F, typename A> std::is_const<A> test(void (F::*)(A &&));
template <typename F, typename A> std::is_const<A> test(void (F::*)(A &&) const);
struct dummy {};
template <
typename F, typename A
#ifdef Vc_ICC
,
typename = decltype(std::declval<F &>()(std::declval<dummy &>()))
#endif
,
#ifdef Vc_MSVC
#define Vc_TEMPLATE_ 
#else
#define Vc_TEMPLATE_ template
#endif
typename MemberPtr = decltype(&F::Vc_TEMPLATE_ operator()<A>)>
decltype(is_functor_argument_immutable_impl::test(std::declval<MemberPtr>())) test2(int);
#undef Vc_TEMPLATE_
template <typename F, typename A>
decltype(
is_functor_argument_immutable_impl::test(std::declval<decltype(&F::operator())>()))
test2(float);
template <typename A> std::true_type test3(void(*)(A));
template <typename A> std::is_const<A> test3(void(*)(A &));
template <typename A> std::is_const<A> test3(void(*)(A &&));
}
template <typename F, typename A, bool = std::is_function<F>::value>
struct is_functor_argument_immutable;
template <typename F, typename A>
struct is_functor_argument_immutable<F, A, false>
: public decltype(is_functor_argument_immutable_impl::test2<
typename std::remove_reference<F>::type, A>(int())) {
};
template <typename F, typename A>
struct is_functor_argument_immutable<F, A, true>
: public decltype(is_functor_argument_immutable_impl::test3(std::declval<F>())) {
};
}
}
#endif
#ifndef VC_TRAITS_IS_OUTPUT_ITERATOR_H_
#define VC_TRAITS_IS_OUTPUT_ITERATOR_H_ 
#include <iterator>
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
namespace is_output_iterator_impl
{
template <typename T, typename ValueType = typename std::iterator_traits<T>::value_type,
typename = decltype(*std::declval<T &>() = std::declval<
ValueType>())
>
std::true_type test(int);
template <typename T> std::false_type test(...);
}
template <typename T>
struct is_output_iterator
: public std::conditional<
std::is_void<typename std::iterator_traits<T>::value_type>::value,
std::true_type, decltype(is_output_iterator_impl::test<T>(int()))>::type
{
};
static_assert(!std::is_void<std::iterator_traits<int *>::value_type>::value, "");
static_assert(is_output_iterator<int *>::value, "");
static_assert(!is_output_iterator<const int *>::value, "");
}
}
#endif
#ifndef VC_IS_INDEX_SEQUENCE_H_
#define VC_IS_INDEX_SEQUENCE_H_ 
#ifndef VC_COMMON_INDEXSEQUENCE_H_
#define VC_COMMON_INDEXSEQUENCE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
template <std::size_t... I> struct index_sequence
{
static constexpr std::size_t size() noexcept { return sizeof...(I); }
};
template <std::size_t N> struct make_index_sequence_impl {
template <std::size_t Offset, std::size_t... Ns>
static index_sequence<Ns..., (Ns + Offset)...> join(std::false_type,
index_sequence<Ns...>);
template <std::size_t Offset, std::size_t... Ns>
static index_sequence<Ns..., Offset - 1, (Ns + Offset)...> join(
std::true_type, index_sequence<Ns...>);
using is_odd = std::integral_constant<bool, N & 1>;
using half = typename make_index_sequence_impl<N / 2>::type;
using type = decltype(join<(N + 1) / 2>(is_odd(), half()));
};
template <> struct make_index_sequence_impl<0> {
using type = index_sequence<>;
};
template <> struct make_index_sequence_impl<1> {
using type = index_sequence<0>;
};
template <> struct make_index_sequence_impl<2> {
using type = index_sequence<0, 1>;
};
template <std::size_t N>
using make_index_sequence = typename make_index_sequence_impl<N>::type;
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
template <typename T> struct is_index_sequence : public std::false_type {};
template <std::size_t... I>
struct is_index_sequence<Vc::index_sequence<I...>> : public std::true_type {};
static_assert(!is_index_sequence<int>::value, "");
static_assert(is_index_sequence<make_index_sequence<2>>::value, "");
}
}
#endif
#ifndef VC_TRAITS_IS_IMPLICIT_CAST_ALLOWED_H_
#define VC_TRAITS_IS_IMPLICIT_CAST_ALLOWED_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
template <typename From, typename To, bool = std::is_integral<From>::value>
struct is_implicit_cast_allowed
: public std::integral_constant<
bool, std::is_same<From, To>::value ||
(std::is_integral<To>::value &&
(std::is_same<typename std::make_unsigned<From>::type, To>::value ||
std::is_same<typename std::make_signed<From>::type, To>::value))> {
};
template <typename From, typename To>
struct is_implicit_cast_allowed<From, To, false> : public std::is_same<From, To>::type {
};
template <typename From, typename To>
struct is_implicit_cast_allowed_mask : public is_implicit_cast_allowed<From, To> {
};
static_assert(is_implicit_cast_allowed<float, float>::value, "");
static_assert(!is_implicit_cast_allowed<float, double>::value, "");
static_assert(is_implicit_cast_allowed< int64_t, uint64_t>::value, "");
static_assert(is_implicit_cast_allowed<uint64_t, int64_t>::value, "");
static_assert(is_implicit_cast_allowed< int32_t, uint32_t>::value, "");
static_assert(is_implicit_cast_allowed<uint32_t, int32_t>::value, "");
static_assert(is_implicit_cast_allowed< int16_t, uint16_t>::value, "");
static_assert(is_implicit_cast_allowed<uint16_t, int16_t>::value, "");
static_assert(is_implicit_cast_allowed< int8_t, uint8_t>::value, "");
static_assert(is_implicit_cast_allowed< uint8_t, int8_t>::value, "");
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
struct enable_if_default_type
{
constexpr enable_if_default_type() {}
};
static constexpr enable_if_default_type nullarg;
template <bool Test, typename T = enable_if_default_type> using enable_if = typename std::enable_if<Test, T>::type;
namespace Traits
{
#ifndef VC_TRAITS_HAS_SUBSCRIPT_OPERATOR_H_
#define VC_TRAITS_HAS_SUBSCRIPT_OPERATOR_H_ 
namespace has_subscript_operator_impl
{
template <typename T, typename I, typename = decltype(std::declval<T &>()[std::declval<I>()])> std::true_type test(int);
template <typename T, typename I> std::false_type test(float);
}
template <typename T, typename I = std::size_t>
struct has_subscript_operator : public decltype(has_subscript_operator_impl::test<T, I>(1))
{
};
static_assert(has_subscript_operator<int[]>::value, "");
static_assert(has_subscript_operator<int[], int>::value, "");
static_assert(!has_subscript_operator<int[], void *>::value, "");
#endif
#ifndef VC_TRAITS_HAS_MULTIPLY_OPERATOR_H_
#define VC_TRAITS_HAS_MULTIPLY_OPERATOR_H_ 
namespace has_multiply_operator_impl
{
template <typename T, typename U, typename = decltype(std::declval<T>() * std::declval<U>())> std::true_type test(int);
template <typename T, typename U> std::false_type test(...);
}
template <typename T, typename U = T>
struct has_multiply_operator : public decltype(has_multiply_operator_impl::test<T, U>(1))
{
};
#endif
#ifndef VC_TRAITS_HAS_ADDITION_OPERATOR_H_
#define VC_TRAITS_HAS_ADDITION_OPERATOR_H_ 
namespace has_addition_operator_impl
{
template <typename T, typename U, typename = decltype(std::declval<T>() + std::declval<U>())> std::true_type test(int);
template <typename T, typename U> std::false_type test(...);
}
template <typename T, typename U = T>
struct has_addition_operator : public decltype(has_addition_operator_impl::test<T, U>(1))
{
};
#endif
#ifndef VC_TRAITS_HAS_EQUALITY_OPERATOR_H_
#define VC_TRAITS_HAS_EQUALITY_OPERATOR_H_ 
namespace has_equality_operator_impl
{
template <typename T, typename U,
typename = enable_if<!std::is_same<void, decltype(std::declval<T>() == std::declval<U>())>::value>>
std::true_type test(int);
template <typename T, typename U> std::false_type test(...);
}
template <typename T, typename U = T>
struct has_equality_operator : public decltype(has_equality_operator_impl::test<T, U>(1))
{
};
static_assert(has_equality_operator<int>::value, "has_equality_operator fails");
namespace
{
class Foobar {};
static_assert(!has_equality_operator<Foobar>::value, "has_equality_operator fails");
}
#endif
template<typename T> struct is_valid_vector_argument : public std::false_type {};
template <> struct is_valid_vector_argument<double> : public std::true_type {};
template <> struct is_valid_vector_argument<float> : public std::true_type {};
template <> struct is_valid_vector_argument<int> : public std::true_type {};
template <> struct is_valid_vector_argument<unsigned int> : public std::true_type {};
template <> struct is_valid_vector_argument<short> : public std::true_type {};
template <> struct is_valid_vector_argument<unsigned short> : public std::true_type {};
template<typename T> struct is_simd_mask_internal : public std::false_type {};
template<typename T> struct is_simd_vector_internal : public std::false_type {};
template<typename T> struct is_subscript_operation_internal : public std::false_type {};
template<typename T> struct is_simdarray_internal : public std::false_type {};
template<typename T> struct is_simd_mask_array_internal : public std::false_type {};
template<typename T> struct is_loadstoreflag_internal : public std::false_type {};
template <std::size_t, typename... Args> struct is_gather_signature_impl;
template <std::size_t N_, typename Arg0, typename Arg1, typename... MoreArguments>
struct is_gather_signature_impl<N_, Arg0, Arg1, MoreArguments...>
: public std::integral_constant<bool, has_subscript_operator<Arg0>::value &&
!is_loadstoreflag_internal<Arg1>::value &&
has_subscript_operator<Arg1>::value> {
};
template<typename... Args> struct is_gather_signature_impl<0, Args...> : public std::false_type {};
template<typename... Args> struct is_gather_signature_impl<1, Args...> : public std::false_type {};
template <typename... Args> struct is_gather_signature : public is_gather_signature_impl<sizeof...(Args), decay<Args>...> {};
template <std::size_t, typename... Args> struct is_cast_arguments_internal : public std::false_type {};
template <typename Arg>
struct is_cast_arguments_internal<1, Arg> : public std::integral_constant<
bool,
is_simdarray_internal<Arg>::value ||
is_simd_vector_internal<Arg>::value>
{
};
template <typename T, bool = is_simd_vector_internal<T>::value> struct is_integral_internal;
template <typename T, bool = is_simd_vector_internal<T>::value> struct is_floating_point_internal;
template <typename T, bool = is_simd_vector_internal<T>::value> struct is_signed_internal;
template <typename T, bool = is_simd_vector_internal<T>::value> struct is_unsigned_internal;
template <typename T> struct is_integral_internal <T, false> : public std::is_integral <T> {};
template <typename T> struct is_floating_point_internal<T, false> : public std::is_floating_point<T> {};
template <typename T> struct is_signed_internal <T, false> : public std::is_signed <T> {};
template <typename T> struct is_unsigned_internal <T, false> : public std::is_unsigned <T> {};
template <typename V> struct is_integral_internal <V, true> : public std::is_integral <typename V::EntryType> {};
template <typename V> struct is_floating_point_internal<V, true> : public std::is_floating_point<typename V::EntryType> {};
template <typename V> struct is_signed_internal <V, true> : public std::is_signed <typename V::EntryType> {};
template <typename V> struct is_unsigned_internal <V, true> : public std::is_unsigned <typename V::EntryType> {};
template <typename T>
struct is_arithmetic_internal
: public std::integral_constant<
bool,
(is_floating_point_internal<T>::value || is_integral_internal<T>::value)>
{
};
template <typename T,
bool = (is_simd_vector_internal<T>::value || is_simd_mask_internal<T>::value ||
is_simdarray_internal<T>::value ||
is_simd_mask_array_internal<T>::value)>
struct vector_size_internal;
template <typename T>
struct vector_size_internal<T, true> : public std::integral_constant<std::size_t, T::Size>
{
};
template <typename T>
struct vector_size_internal<T, false> : public std::integral_constant<std::size_t, 0>
{
};
template <typename T>
struct is_simd_mask : public std::integral_constant<bool,
(is_simd_mask_internal<decay<T>>::value ||
is_simd_mask_array_internal<decay<T>>::value)>
{
};
template <typename T>
struct is_simd_vector
: public std::integral_constant<bool,
(is_simd_vector_internal<decay<T>>::value ||
is_simdarray_internal<decay<T>>::value)>
{
};
template <typename T>
struct isSimdArray : public is_simdarray_internal<decay<T>>
{
};
template <typename T>
struct isSimdMaskArray : public is_simd_mask_array_internal<decay<T>>
{
};
template <typename T> struct is_subscript_operation : public is_subscript_operation_internal<decay<T>> {};
template <typename T> struct is_load_store_flag : public is_loadstoreflag_internal<decay<T>> {};
template <typename... Args> struct is_cast_arguments : public is_cast_arguments_internal<sizeof...(Args), decay<Args>...> {};
template <typename T> struct is_atomic_simdarray_internal : public std::false_type {};
template <typename T> using isAtomicSimdArray = is_atomic_simdarray_internal<decay<T>>;
template <typename T> struct is_atomic_simd_mask_array_internal : public std::false_type {};
template <typename T> using isAtomicSimdMaskArray = is_atomic_simd_mask_array_internal<decay<T>>;
template <typename T> struct simd_vector_size : public vector_size_internal<decay<T>> {};
template <typename T> struct is_integral : public is_integral_internal<decay<T>> {};
template <typename T> struct is_floating_point : public is_floating_point_internal<decay<T>> {};
template <typename T> struct is_arithmetic : public is_arithmetic_internal<decay<T>> {};
template <typename T> struct is_signed : public is_signed_internal<decay<T>> {};
template <typename T> struct is_unsigned : public is_unsigned_internal<decay<T>> {};
template <typename T, bool IsSimdVector> struct scalar_type_internal { using type = T; };
template <typename T> struct scalar_type_internal<T, true> { using type = typename T::EntryType; };
template <typename T> using scalar_type = typename scalar_type_internal<decay<T>, is_simd_vector<T>::value>::type;
}
}
#ifndef VC_TRAITS_ENTRY_TYPE_OF_H_
#define VC_TRAITS_ENTRY_TYPE_OF_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Traits
{
namespace entry_type_of_internal
{
template <typename T, bool = Traits::is_simd_vector<T>::value> struct entry_type;
template <typename T> struct entry_type<T, true>
{
using type = typename decay<T>::EntryType;
};
template <typename T> struct entry_type<T, false>
{
using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
};
}
template <typename T> using entry_type_of = typename entry_type_of_internal::entry_type<T>::type;
}
}
#endif
#endif
#ifndef VC_COMMON_PERMUTATION_H_
#define VC_COMMON_PERMUTATION_H_ 
#ifndef VC_COMMON_MACROS_H_
#define VC_COMMON_MACROS_H_ 
#ifdef Vc_MSVC
#define Vc_ALIGNED_TYPEDEF(n_,type_,new_type_) \
typedef __declspec(align(n_)) type_ new_type_
#elif __GNUC__
#define Vc_ALIGNED_TYPEDEF(n_,type_,new_type_) \
typedef type_ new_type_[[gnu::aligned(n_)]]
#else
#define Vc_ALIGNED_TYPEDEF(n_,type_,new_type_) \
using new_type_ alignas(sizeof(n_)) = type_
#endif
#ifdef WIN32
#define NOMINMAX 1
#if defined min
#undef min
#endif
#if defined max
#undef max
#endif
#endif
#if defined Vc_GCC && Vc_GCC >= 0x60000
#define Vc_TEMPLATES_DROP_ATTRIBUTES 1
#endif
#if Vc_IS_VERSION_2 || (defined Vc_GCC && Vc_GCC >= 0x60000)
#define Vc_RECURSIVE_MEMORY 1
#endif
#if defined Vc_CLANG || defined Vc_APPLECLANG
#define Vc_UNREACHABLE __builtin_unreachable
#define Vc_NEVER_INLINE [[gnu::noinline]]
#define Vc_INTRINSIC_L inline
#define Vc_INTRINSIC_R __attribute__((always_inline))
#define Vc_INTRINSIC Vc_INTRINSIC_L Vc_INTRINSIC_R
#define Vc_FLATTEN 
#define Vc_CONST __attribute__((const))
#define Vc_CONST_L 
#define Vc_CONST_R Vc_CONST
#define Vc_PURE __attribute__((pure))
#define Vc_PURE_L 
#define Vc_PURE_R Vc_PURE
#define Vc_MAY_ALIAS __attribute__((may_alias))
#define Vc_ALWAYS_INLINE_L inline
#define Vc_ALWAYS_INLINE_R __attribute__((always_inline))
#define Vc_ALWAYS_INLINE Vc_ALWAYS_INLINE_L Vc_ALWAYS_INLINE_R
#define Vc_IS_UNLIKELY(x) __builtin_expect(x, 0)
#define Vc_IS_LIKELY(x) __builtin_expect(x, 1)
#define Vc_RESTRICT __restrict__
#define Vc_DEPRECATED(msg) 
#define Vc_DEPRECATED_ALIAS(msg) 
#define Vc_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#elif defined(__GNUC__)
#define Vc_UNREACHABLE __builtin_unreachable
# if defined Vc_GCC && !defined __OPTIMIZE__
#define Vc_MAY_ALIAS 
# else
#define Vc_MAY_ALIAS __attribute__((__may_alias__))
# endif
#define Vc_INTRINSIC_R __attribute__((__always_inline__, __artificial__))
#define Vc_INTRINSIC_L inline
#define Vc_INTRINSIC Vc_INTRINSIC_L Vc_INTRINSIC_R
#define Vc_FLATTEN __attribute__((__flatten__))
#define Vc_ALWAYS_INLINE_L inline
#define Vc_ALWAYS_INLINE_R __attribute__((__always_inline__))
#define Vc_ALWAYS_INLINE Vc_ALWAYS_INLINE_L Vc_ALWAYS_INLINE_R
# ifdef Vc_ICC
#define Vc_PURE 
#define Vc_CONST 
#define Vc_NEVER_INLINE 
# else
#define Vc_NEVER_INLINE [[gnu::noinline]]
#define Vc_PURE __attribute__((__pure__))
#define Vc_CONST __attribute__((__const__))
# endif
#define Vc_CONST_L 
#define Vc_CONST_R Vc_CONST
#define Vc_PURE_L 
#define Vc_PURE_R Vc_PURE
#define Vc_IS_UNLIKELY(x) __builtin_expect(x, 0)
#define Vc_IS_LIKELY(x) __builtin_expect(x, 1)
#define Vc_RESTRICT __restrict__
# ifdef Vc_ICC
#define Vc_DEPRECATED(msg) 
#define Vc_DEPRECATED_ALIAS(msg) 
# else
#define Vc_DEPRECATED(msg) __attribute__((__deprecated__(msg)))
#define Vc_DEPRECATED_ALIAS(msg) __attribute__((__deprecated__(msg)))
# endif
#define Vc_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#else
#define Vc_NEVER_INLINE 
#define Vc_FLATTEN 
# ifdef Vc_PURE
#undef Vc_PURE
# endif
#define Vc_MAY_ALIAS 
# ifdef Vc_MSVC
#define Vc_ALWAYS_INLINE inline __forceinline
#define Vc_ALWAYS_INLINE_L Vc_ALWAYS_INLINE
#define Vc_ALWAYS_INLINE_R 
#define Vc_CONST __declspec(noalias)
#define Vc_CONST_L Vc_CONST
#define Vc_CONST_R 
#define Vc_PURE 
#define Vc_PURE_L Vc_PURE
#define Vc_PURE_R 
#define Vc_INTRINSIC inline __forceinline
#define Vc_INTRINSIC_L Vc_INTRINSIC
#define Vc_INTRINSIC_R 
namespace Vc_VERSIONED_NAMESPACE {
namespace detail
{
static Vc_INTRINSIC void unreachable() { __assume(0); }
}
}
#define Vc_UNREACHABLE Vc::detail::unreachable
# else
#define Vc_ALWAYS_INLINE 
#define Vc_ALWAYS_INLINE_L 
#define Vc_ALWAYS_INLINE_R 
#define Vc_CONST 
#define Vc_CONST_L 
#define Vc_CONST_R 
#define Vc_PURE 
#define Vc_PURE_L 
#define Vc_PURE_R 
#define Vc_INTRINSIC 
#define Vc_INTRINSIC_L 
#define Vc_INTRINSIC_R 
#define Vc_UNREACHABLE std::abort
# endif
#define Vc_IS_UNLIKELY(x) x
#define Vc_IS_LIKELY(x) x
#define Vc_RESTRICT __restrict
#define Vc_DEPRECATED(msg) __declspec(deprecated(msg))
#define Vc_DEPRECATED_ALIAS(msg) 
#define Vc_WARN_UNUSED_RESULT 
#endif
#ifdef Vc_CXX14
#undef Vc_DEPRECATED
#define Vc_DEPRECATED(msg_) [[deprecated(msg_)]]
#endif
#define Vc_NOTHING_EXPECTING_SEMICOLON static_assert(true, "")
#define Vc_FREE_STORE_OPERATORS_ALIGNED(align_) \
\
\
\
Vc_ALWAYS_INLINE void *operator new(size_t size) \
{ \
return Vc::Common::aligned_malloc<align_>(size); \
} \
\
Vc_ALWAYS_INLINE void *operator new(size_t, void *p) { return p; } \
\
Vc_ALWAYS_INLINE void *operator new[](size_t size) \
{ \
return Vc::Common::aligned_malloc<align_>(size); \
} \
\
Vc_ALWAYS_INLINE void *operator new[](size_t, void *p) { return p; } \
\
Vc_ALWAYS_INLINE void operator delete(void *ptr, size_t) { Vc::Common::free(ptr); } \
\
Vc_ALWAYS_INLINE void operator delete(void *, void *) {} \
\
Vc_ALWAYS_INLINE void operator delete[](void *ptr, size_t) \
{ \
Vc::Common::free(ptr); \
} \
\
Vc_ALWAYS_INLINE void operator delete[](void *, void *) {} \
\
Vc_NOTHING_EXPECTING_SEMICOLON
#ifdef Vc_ASSERT
#define Vc_EXTERNAL_ASSERT 1
#else
#ifdef NDEBUG
#define Vc_ASSERT(x) 
#else
#include <assert.h>
#define Vc_ASSERT(x) assert(x);
#endif
#endif
#if defined Vc_CLANG || defined Vc_APPLECLANG
#define Vc_HAS_BUILTIN(x) __has_builtin(x)
#else
#define Vc_HAS_BUILTIN(x) 0
#endif
#define Vc_CAT_HELPER_(a,b,c,d) a ##b ##c ##d
#define Vc_CAT(a,b,c,d) Vc_CAT_HELPER_(a, b, c, d)
#define Vc_CAT_IMPL(a,b) a ##b
#define Vc_CAT2(a,b) Vc_CAT_IMPL(a, b)
#define Vc_APPLY_IMPL_1_(macro,a,b,c,d,e) macro(a)
#define Vc_APPLY_IMPL_2_(macro,a,b,c,d,e) macro(a, b)
#define Vc_APPLY_IMPL_3_(macro,a,b,c,d,e) macro(a, b, c)
#define Vc_APPLY_IMPL_4_(macro,a,b,c,d,e) macro(a, b, c, d)
#define Vc_APPLY_IMPL_5_(macro,a,b,c,d,e) macro(a, b, c, d, e)
#define Vc_LIST_FLOAT_VECTOR_TYPES(size,macro,a,b,c,d) \
size(macro, double_v, a, b, c, d) \
size(macro, float_v, a, b, c, d)
#define Vc_LIST_INT_VECTOR_TYPES(size,macro,a,b,c,d) \
size(macro, int_v, a, b, c, d) \
size(macro, uint_v, a, b, c, d) \
size(macro, short_v, a, b, c, d) \
size(macro, ushort_v, a, b, c, d)
#define Vc_LIST_VECTOR_TYPES(size,macro,a,b,c,d) \
Vc_LIST_FLOAT_VECTOR_TYPES(size, macro, a, b, c, d) \
Vc_LIST_INT_VECTOR_TYPES(size, macro, a, b, c, d)
#define Vc_LIST_COMPARES(size,macro,a,b,c,d) \
size(macro, ==, a, b, c, d) \
size(macro, !=, a, b, c, d) \
size(macro, <=, a, b, c, d) \
size(macro, >=, a, b, c, d) \
size(macro, < , a, b, c, d) \
size(macro, > , a, b, c, d)
#define Vc_LIST_LOGICAL(size,macro,a,b,c,d) \
size(macro, &&, a, b, c, d) \
size(macro, ||, a, b, c, d)
#define Vc_LIST_BINARY(size,macro,a,b,c,d) \
size(macro, |, a, b, c, d) \
size(macro, &, a, b, c, d) \
size(macro, ^, a, b, c, d)
#define Vc_LIST_SHIFTS(size,macro,a,b,c,d) \
size(macro, <<, a, b, c, d) \
size(macro, >>, a, b, c, d)
#define Vc_LIST_ARITHMETICS(size,macro,a,b,c,d) \
size(macro, +, a, b, c, d) \
size(macro, -, a, b, c, d) \
size(macro, *, a, b, c, d) \
size(macro, /, a, b, c, d) \
size(macro, %, a, b, c, d)
#define Vc_APPLY_0(_list,macro) _list(Vc_APPLY_IMPL_1_, macro, 0, 0, 0, 0) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_APPLY_1(_list,macro,a) _list(Vc_APPLY_IMPL_2_, macro, a, 0, 0, 0) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_APPLY_2(_list,macro,a,b) _list(Vc_APPLY_IMPL_3_, macro, a, b, 0, 0) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_APPLY_3(_list,macro,a,b,c) _list(Vc_APPLY_IMPL_4_, macro, a, b, c, 0) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_APPLY_4(_list,macro,a,b,c,d) _list(Vc_APPLY_IMPL_5_, macro, a, b, c, d) Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_ALL_COMPARES(macro) Vc_APPLY_0(Vc_LIST_COMPARES, macro)
#define Vc_ALL_LOGICAL(macro) Vc_APPLY_0(Vc_LIST_LOGICAL, macro)
#define Vc_ALL_BINARY(macro) Vc_APPLY_0(Vc_LIST_BINARY, macro)
#define Vc_ALL_SHIFTS(macro) Vc_APPLY_0(Vc_LIST_SHIFTS, macro)
#define Vc_ALL_ARITHMETICS(macro) Vc_APPLY_0(Vc_LIST_ARITHMETICS, macro)
#define Vc_ALL_FLOAT_VECTOR_TYPES(macro) Vc_APPLY_0(Vc_LIST_FLOAT_VECTOR_TYPES, macro)
#define Vc_ALL_VECTOR_TYPES(macro) Vc_APPLY_0(Vc_LIST_VECTOR_TYPES, macro)
#define Vc_EXACT_TYPE(_test,_reference,_type) \
typename std::enable_if<std::is_same<_test, _reference>::value, _type>::type
#define Vc_make_unique(name) Vc_CAT(Vc_,name,_,__LINE__)
#if defined(Vc_ICC) || defined(Vc_CLANG) || defined Vc_APPLECLANG
#define Vc_OFFSETOF(Type,member) (reinterpret_cast<const char *>(&reinterpret_cast<const Type *>(0)->member) - reinterpret_cast<const char *>(0))
#else
#define Vc_OFFSETOF(Type,member) offsetof(Type, member)
#endif
#if defined(Vc_NO_NOEXCEPT)
#define Vc_NOEXCEPT throw()
#else
#define Vc_NOEXCEPT noexcept
#endif
#ifdef Vc_NO_ALWAYS_INLINE
#undef Vc_ALWAYS_INLINE
#undef Vc_ALWAYS_INLINE_L
#undef Vc_ALWAYS_INLINE_R
#define Vc_ALWAYS_INLINE inline
#define Vc_ALWAYS_INLINE_L inline
#define Vc_ALWAYS_INLINE_R 
#undef Vc_INTRINSIC
#undef Vc_INTRINSIC_L
#undef Vc_INTRINSIC_R
#define Vc_INTRINSIC inline
#define Vc_INTRINSIC_L inline
#define Vc_INTRINSIC_R 
#endif
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Permutation
{
struct ReversedTag {};
constexpr ReversedTag Reversed{};
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
using std::size_t;
using llong = long long;
using ullong = unsigned long long;
using ulong = unsigned long;
using uint = unsigned int;
using ushort = unsigned short;
using uchar = unsigned char;
using schar = signed char;
struct VectorSpecialInitializerZero {};
struct VectorSpecialInitializerOne {};
struct VectorSpecialInitializerIndexesFromZero {};
constexpr VectorSpecialInitializerZero Zero = {};
constexpr VectorSpecialInitializerOne One = {};
constexpr VectorSpecialInitializerIndexesFromZero IndexesFromZero = {};
namespace Detail
{
template<typename T> struct MayAliasImpl {
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif
typedef T type Vc_MAY_ALIAS;
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
};
}
#ifdef Vc_ICC
template <typename T> using MayAlias [[gnu::may_alias]] = T;
#else
template <typename T> using MayAlias = typename Detail::MayAliasImpl<T>::type;
#endif
template <class To, class From> MayAlias<To> &aliasing_cast(From &x)
{
return *reinterpret_cast<MayAlias<To> *>(&x);
}
template <class To, class From> const MayAlias<To> &aliasing_cast(const From &x)
{
return *reinterpret_cast<const MayAlias<To> *>(&x);
}
template <class To, class From> MayAlias<To> *aliasing_cast(From *x)
{
return reinterpret_cast<MayAlias<To> *>(x);
}
template <class To, class From> const MayAlias<To> *aliasing_cast(const From *x)
{
return reinterpret_cast<const MayAlias<To> *>(x);
}
enum class Operator : char {
Assign,
Multiply,
MultiplyAssign,
Divide,
DivideAssign,
Remainder,
RemainderAssign,
Plus,
PlusAssign,
Minus,
MinusAssign,
RightShift,
RightShiftAssign,
LeftShift,
LeftShiftAssign,
And,
AndAssign,
Xor,
XorAssign,
Or,
OrAssign,
PreIncrement,
PostIncrement,
PreDecrement,
PostDecrement,
LogicalAnd,
LogicalOr,
Comma,
UnaryPlus,
UnaryMinus,
UnaryNot,
UnaryOnesComplement,
CompareEqual,
CompareNotEqual,
CompareLess,
CompareGreater,
CompareLessEqual,
CompareGreaterEqual
};
template <typename T, std::size_t N> struct array;
#ifndef Vc_CHECK_ALIGNMENT
template<typename _T> static Vc_ALWAYS_INLINE void assertCorrectAlignment(const _T *){}
#else
template<typename _T> static Vc_ALWAYS_INLINE void assertCorrectAlignment(const _T *ptr)
{
const size_t s = alignof(_T);
if((reinterpret_cast<size_t>(ptr) & ((s ^ (s & (s - 1))) - 1)) != 0) {
fprintf(stderr, "A vector with incorrect alignment has just been created. Look at the stacktrace to find the guilty object.\n");
abort();
}
}
#endif
namespace Common
{
template <typename T, std::size_t Pieces, std::size_t Index> struct Segment;
template<size_t StructSize> class SuccessiveEntries
{
#ifdef Vc_MSVC
using size_type = unsigned;
#else
using size_type = size_t;
#endif
const size_type m_first;
public:
typedef SuccessiveEntries AsArg;
Vc_INTRINSIC SuccessiveEntries(size_type first) : m_first(first) {}
Vc_INTRINSIC Vc_PURE size_type operator[](size_type offset) const
{
return m_first + offset * StructSize;
}
Vc_INTRINSIC Vc_PURE size_type data() const { return m_first; }
Vc_INTRINSIC Vc_PURE SuccessiveEntries operator+(const SuccessiveEntries &rhs) const
{
return SuccessiveEntries(m_first + rhs.m_first);
}
Vc_INTRINSIC Vc_PURE SuccessiveEntries operator*(const SuccessiveEntries &rhs) const
{
return SuccessiveEntries(m_first * rhs.m_first);
}
Vc_INTRINSIC Vc_PURE SuccessiveEntries operator<<(size_type x) const
{
return {m_first << x};
}
friend Vc_INTRINSIC SuccessiveEntries &internal_data(SuccessiveEntries &x)
{
return x;
}
friend Vc_INTRINSIC const SuccessiveEntries &internal_data(const SuccessiveEntries &x)
{
return x;
}
};
template <std::size_t alignment>
Vc_INTRINSIC_L void *aligned_malloc(std::size_t n) Vc_INTRINSIC_R;
Vc_ALWAYS_INLINE_L void free(void *p) Vc_ALWAYS_INLINE_R;
template <typename Mask, typename T, typename U>
using enable_if_mask_converts_implicitly =
enable_if<(!std::is_same<Mask, Traits::decay<U>>::value &&
Traits::is_simd_mask<U>::value && !Traits::isSimdMaskArray<U>::value &&
Traits::is_implicit_cast_allowed_mask<
Traits::entry_type_of<typename Traits::decay<U>::Vector>, T>::value)>;
template <typename T, typename U>
using enable_if_mask_converts_explicitly = enable_if<(
Traits::isSimdMaskArray<U>::value ||
(Traits::is_simd_mask<U>::value &&
!Traits::is_implicit_cast_allowed_mask<
Traits::entry_type_of<typename Traits::decay<U>::Vector>, T>::value))>;
template <typename T> using WidthT = std::integral_constant<std::size_t, sizeof(T)>;
template <std::size_t Bytes> class MaskBool;
template <typename T, typename IndexVector, typename Scale, bool>
class SubscriptOperation;
template <typename T, typename IndexVector> struct GatherArguments
{
const IndexVector indexes;
const T *const address;
};
template <typename T, typename IndexVector> struct ScatterArguments
{
const IndexVector indexes;
T *const address;
};
template <typename I, I Begin, I End, typename F>
Vc_INTRINSIC enable_if<(Begin >= End), void> unrolled_loop(F &&)
{
}
template <typename I, I Begin, I End, typename F>
Vc_INTRINSIC Vc_FLATTEN enable_if<(Begin < End), void> unrolled_loop(F &&f)
{
f(Begin);
unrolled_loop<I, Begin + 1, End>(f);
}
template <std::size_t Size, typename F> Vc_INTRINSIC void for_all_vector_entries(F &&f)
{
unrolled_loop<std::size_t, 0u, Size>(std::forward<F>(f));
}
template <class T, std::size_t Size = sizeof(T), std::size_t Alignment = alignof(T)>
struct ensure_alignment_equals_sizeof {
Vc_ALIGNED_TYPEDEF(Size, T, type);
};
template <class T, std::size_t Size>
struct ensure_alignment_equals_sizeof<T, Size, Size> {
using type = T;
};
}
}
#ifndef VC_COMMON_VECTOR_H_
#define VC_COMMON_VECTOR_H_ 
#include <ratio>
#ifndef VC_COMMON_ELEMENTREFERENCE_H_
#define VC_COMMON_ELEMENTREFERENCE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename U, typename Accessor = U> class ElementReference
{
friend U;
friend Accessor;
Vc_INTRINSIC ElementReference(U &o, int i) noexcept : index(i), obj(o) {}
static constexpr bool get_noexcept =
noexcept(Accessor::get(std::declval<U &>(), int()));
template <typename T> static constexpr bool set_noexcept()
{
return noexcept(Accessor::set(std::declval<U &>(), int(), std::declval<T>()));
}
public:
using value_type = typename U::value_type;
Vc_INTRINSIC ElementReference(const ElementReference &) = delete;
Vc_INTRINSIC ElementReference(ElementReference &&) = default;
Vc_INTRINSIC operator value_type() const noexcept(get_noexcept)
{
return Accessor::get(obj, index);
}
template <typename T>
Vc_INTRINSIC ElementReference &operator=(T &&x) &&
noexcept(noexcept(Accessor::set(std::declval<U &>(), int(), std::declval<T>())))
{
Accessor::set(obj, index, std::forward<T>(x));
return *this;
}
#define Vc_OP_(op_) \
template <typename T, typename R = decltype(std::declval<const value_type &>() \
op_ std::declval<T>())> \
Vc_INTRINSIC ElementReference &operator op_##=(T &&x) && \
noexcept(get_noexcept && noexcept(Accessor::set(std::declval<U &>(), int(), \
std::declval<R &&>()))) \
{ \
const value_type &lhs = Accessor::get(obj, index); \
Accessor::set(obj, index, lhs op_ std::forward<T>(x)); \
return *this; \
}
Vc_ALL_ARITHMETICS(Vc_OP_);
Vc_ALL_SHIFTS(Vc_OP_);
Vc_ALL_BINARY(Vc_OP_);
#undef Vc_OP_
template <typename = void>
Vc_INTRINSIC ElementReference &operator++() &&
noexcept(noexcept(std::declval<value_type &>() =
Accessor::get(std::declval<U &>(), int())) &&
set_noexcept<decltype(++std::declval<value_type &>())>())
{
value_type x = Accessor::get(obj, index);
Accessor::set(obj, index, ++x);
return *this;
}
template <typename = void>
Vc_INTRINSIC value_type operator++(int) &&
noexcept(noexcept(std::declval<value_type &>() =
Accessor::get(std::declval<U &>(), int())) &&
set_noexcept<decltype(std::declval<value_type &>()++)>())
{
const value_type r = Accessor::get(obj, index);
value_type x = r;
Accessor::set(obj, index, ++x);
return r;
}
template <typename = void>
Vc_INTRINSIC ElementReference &operator--() &&
noexcept(noexcept(std::declval<value_type &>() =
Accessor::get(std::declval<U &>(), int())) &&
set_noexcept<decltype(--std::declval<value_type &>())>())
{
value_type x = Accessor::get(obj, index);
Accessor::set(obj, index, --x);
return *this;
}
template <typename = void>
Vc_INTRINSIC value_type operator--(int) &&
noexcept(noexcept(std::declval<value_type &>() =
Accessor::get(std::declval<U &>(), int())) &&
set_noexcept<decltype(std::declval<value_type &>()--)>())
{
const value_type r = Accessor::get(obj, index);
value_type x = r;
Accessor::set(obj, index, --x);
return r;
}
friend void swap(ElementReference &&a, ElementReference &&b) {
value_type tmp(a);
static_cast<ElementReference &&>(a) = static_cast<value_type>(b);
static_cast<ElementReference &&>(b) = tmp;
}
friend void swap(value_type &a, ElementReference &&b) {
value_type tmp(a);
a = static_cast<value_type>(b);
static_cast<ElementReference &&>(b) = tmp;
}
friend void swap(ElementReference &&a, value_type &b) {
value_type tmp(a);
static_cast<ElementReference &&>(a) = b;
b = tmp;
}
private:
int index;
U &obj;
};
}
}
#endif
#ifndef VC_COMMON_VECTORABI_H_
#define VC_COMMON_VECTORABI_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace VectorAbi
{
template <typename T>
using Avx1Abi = typename std::conditional<std::is_integral<T>::value, VectorAbi::Sse,
VectorAbi::Avx>::type;
template <typename T> struct DeduceCompatible {
#ifdef __x86_64__
using type = Sse;
#else
using type = Scalar;
#endif
};
template <typename T>
struct DeduceBest {
using type = typename std::conditional<
CurrentImplementation::is(ScalarImpl), Scalar,
typename std::conditional<
CurrentImplementation::is_between(SSE2Impl, SSE42Impl), Sse,
typename std::conditional<
CurrentImplementation::is(AVXImpl), Avx1Abi<T>,
typename std::conditional<CurrentImplementation::is(AVX2Impl), Avx,
void>::type>::type>::type>::type;
};
template <typename T> using Best = typename DeduceBest<T>::type;
#ifdef Vc_IMPL_AVX2
static_assert(std::is_same<Best<float>, Avx>::value, "");
static_assert(std::is_same<Best<int>, Avx>::value, "");
#elif defined Vc_IMPL_AVX
static_assert(std::is_same<Best<float>, Avx>::value, "");
static_assert(std::is_same<Best<int>, Sse>::value, "");
#elif defined Vc_IMPL_SSE
static_assert(CurrentImplementation::is_between(SSE2Impl, SSE42Impl), "");
static_assert(std::is_same<Best<float>, Sse>::value, "");
static_assert(std::is_same<Best<int>, Sse>::value, "");
#elif defined Vc_IMPL_Scalar
static_assert(std::is_same<Best<float>, Scalar>::value, "");
static_assert(std::is_same<Best<int>, Scalar>::value, "");
#endif
}
}
#ifndef VC_COMMON_SIMDARRAYFWD_H_
#define VC_COMMON_SIMDARRAYFWD_H_ 
#ifndef VC_SSE_TYPES_H_
#define VC_SSE_TYPES_H_ 
#ifdef Vc_DEFAULT_IMPL_SSE
#define Vc_DOUBLE_V_SIZE 2
#define Vc_FLOAT_V_SIZE 4
#define Vc_INT_V_SIZE 4
#define Vc_UINT_V_SIZE 4
#define Vc_SHORT_V_SIZE 8
#define Vc_USHORT_V_SIZE 8
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace SSE
{
template <typename T> using Vector = Vc::Vector<T, VectorAbi::Sse>;
typedef Vector<double> double_v;
typedef Vector<float> float_v;
typedef Vector<int> int_v;
typedef Vector<unsigned int> uint_v;
typedef Vector<short> short_v;
typedef Vector<unsigned short> ushort_v;
template <typename T> using Mask = Vc::Mask<T, VectorAbi::Sse>;
typedef Mask<double> double_m;
typedef Mask<float> float_m;
typedef Mask<int> int_m;
typedef Mask<unsigned int> uint_m;
typedef Mask<short> short_m;
typedef Mask<unsigned short> ushort_m;
template <typename T> struct Const;
template <typename T> struct is_vector : public std::false_type {};
template <typename T> struct is_vector<Vector<T>> : public std::true_type {};
template <typename T> struct is_mask : public std::false_type {};
template <typename T> struct is_mask<Mask<T>> : public std::true_type {};
}
namespace Traits
{
template <class T> struct
is_simd_vector_internal<Vector<T, VectorAbi::Sse>>
: public is_valid_vector_argument<T> {};
template<typename T> struct is_simd_mask_internal<Mask<T, VectorAbi::Sse>>
: public std::true_type {};
}
}
#endif
#ifndef VC_AVX_TYPES_H_
#define VC_AVX_TYPES_H_ 
#ifndef VC_AVX_MACROS_H_
#define VC_AVX_MACROS_H_ 
#endif
#ifdef Vc_DEFAULT_IMPL_AVX2
#define Vc_DOUBLE_V_SIZE 4
#define Vc_FLOAT_V_SIZE 8
#define Vc_INT_V_SIZE 8
#define Vc_UINT_V_SIZE 8
#define Vc_SHORT_V_SIZE 16
#define Vc_USHORT_V_SIZE 16
#elif defined Vc_DEFAULT_IMPL_AVX
#define Vc_DOUBLE_V_SIZE 4
#define Vc_FLOAT_V_SIZE 8
#define Vc_INT_V_SIZE 4
#define Vc_UINT_V_SIZE 4
#define Vc_SHORT_V_SIZE 8
#define Vc_USHORT_V_SIZE 8
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace AVX
{
template <typename T> using Vector = Vc::Vector<T, VectorAbi::Avx1Abi<T>>;
typedef Vector<double> double_v;
typedef Vector<float> float_v;
typedef Vector<int> int_v;
typedef Vector<unsigned int> uint_v;
typedef Vector<short> short_v;
typedef Vector<unsigned short> ushort_v;
template <typename T> using Mask = Vc::Mask<T, VectorAbi::Avx1Abi<T>>;
typedef Mask<double> double_m;
typedef Mask<float> float_m;
typedef Mask<int> int_m;
typedef Mask<unsigned int> uint_m;
typedef Mask<short> short_m;
typedef Mask<unsigned short> ushort_m;
template <typename T> struct Const;
template <typename T> struct is_vector : public std::false_type {};
template <typename T> struct is_vector<Vector<T>> : public std::true_type {};
template <typename T> struct is_mask : public std::false_type {};
template <typename T> struct is_mask<Mask<T>> : public std::true_type {};
}
namespace AVX2
{
template <typename T> using Vector = Vc::Vector<T, VectorAbi::Avx>;
using double_v = Vector<double>;
using float_v = Vector< float>;
using int_v = Vector< int>;
using uint_v = Vector< uint>;
using short_v = Vector< short>;
using ushort_v = Vector<ushort>;
template <typename T> using Mask = Vc::Mask<T, VectorAbi::Avx>;
using double_m = Mask<double>;
using float_m = Mask< float>;
using llong_m = Mask< llong>;
using ullong_m = Mask<ullong>;
using long_m = Mask< long>;
using ulong_m = Mask< ulong>;
using int_m = Mask< int>;
using uint_m = Mask< uint>;
using short_m = Mask< short>;
using ushort_m = Mask<ushort>;
using schar_m = Mask< schar>;
using uchar_m = Mask< uchar>;
template <typename T> struct is_vector : public std::false_type {};
template <typename T> struct is_vector<Vector<T>> : public std::true_type {};
template <typename T> struct is_mask : public std::false_type {};
template <typename T> struct is_mask<Mask<T>> : public std::true_type {};
}
namespace Traits
{
template <class T> struct
is_simd_vector_internal<Vector<T, VectorAbi::Avx>>
: public is_valid_vector_argument<T> {};
template<typename T> struct is_simd_mask_internal<Mask<T, VectorAbi::Avx>>
: public std::true_type {};
}
}
#endif
#ifndef VC_COMMON_UTILITY_H_
#define VC_COMMON_UTILITY_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template <size_t x, bool = (x & (x - 1)) == 0> struct NextPowerOfTwo;
template <size_t x>
struct NextPowerOfTwo<x, true> : public std::integral_constant<size_t, x> {
};
template <size_t x>
struct NextPowerOfTwo<x, false>
: public std::integral_constant<
size_t, NextPowerOfTwo<(x | (x >> 1) | (x >> 2) | (x >> 5)) + 1>::value> {
};
template <size_t A>
struct BoundedAlignment : public std::integral_constant<size_t,
#if defined Vc_MSVC || defined Vc_GCC
((A - 1) &
#ifdef Vc_MSVC
31
#elif defined __AVX__
255
#else
127
#endif
) + 1
#else
A
#endif
> {
};
template <std::size_t N> static constexpr std::size_t left_size()
{
return Common::NextPowerOfTwo<(N + 1) / 2>::value;
}
template <std::size_t N> static constexpr std::size_t right_size()
{
return N - left_size<N>();
}
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
template <class T, int N>
class Vector<T, simd_abi::fixed_size<N>> : public SimdArray<T, N>
{
using SimdArray<T, N>::SimdArray;
public:
Vc_DEPRECATED("use Vector([](int n) { return n; }) instead of "
"Vector::IndexesFromZero()") static Vector IndexesFromZero()
{
return Vector([](size_t i) -> T { return i; });
}
Vc_DEPRECATED("use 0 instead of Vector::Zero()") static Vector Zero() { return 0; }
Vc_DEPRECATED("use 1 instead of Vector::One()") static Vector One() { return 1; }
};
template <class T, int N>
class Mask<T, simd_abi::fixed_size<N>> : public SimdMaskArray<T, N>
{
using SimdMaskArray<T, N>::SimdMaskArray;
};
template <typename T, std::size_t N> struct SimdArrayTraits {
static constexpr std::size_t N0 = Common::left_size<N>();
static constexpr std::size_t N1 = Common::right_size<N>();
using storage_type0 = SimdArray<T, N0>;
using storage_type1 = SimdArray<T, N1>;
};
template <typename T, std::size_t N, typename VectorType, std::size_t VectorSize>
Vc_INTRINSIC_L typename SimdArrayTraits<T, N>::storage_type0 &internal_data0(
SimdArray<T, N, VectorType, VectorSize> &x) Vc_INTRINSIC_R;
template <typename T, std::size_t N, typename VectorType, std::size_t VectorSize>
Vc_INTRINSIC_L typename SimdArrayTraits<T, N>::storage_type1 &internal_data1(
SimdArray<T, N, VectorType, VectorSize> &x) Vc_INTRINSIC_R;
template <typename T, std::size_t N, typename VectorType, std::size_t VectorSize>
Vc_INTRINSIC_L const typename SimdArrayTraits<T, N>::storage_type0 &internal_data0(
const SimdArray<T, N, VectorType, VectorSize> &x) Vc_INTRINSIC_R;
template <typename T, std::size_t N, typename VectorType, std::size_t VectorSize>
Vc_INTRINSIC_L const typename SimdArrayTraits<T, N>::storage_type1 &internal_data1(
const SimdArray<T, N, VectorType, VectorSize> &x) Vc_INTRINSIC_R;
template <typename T, std::size_t N, typename V>
Vc_INTRINSIC_L V &internal_data(SimdArray<T, N, V, N> &x) Vc_INTRINSIC_R;
template <typename T, std::size_t N, typename V>
Vc_INTRINSIC_L const V &internal_data(const SimdArray<T, N, V, N> &x) Vc_INTRINSIC_R;
namespace Traits
{
template <typename T, std::size_t N, typename V>
struct is_atomic_simdarray_internal<SimdArray<T, N, V, N>> : std::true_type {
};
template <typename T, int N>
struct is_atomic_simdarray_internal<fixed_size_simd<T, N>>
: is_atomic_simdarray_internal<SimdArray<T, N>> {
};
template <typename T, std::size_t N, typename V>
struct is_atomic_simd_mask_array_internal<SimdMaskArray<T, N, V, N>> : std::true_type {
};
template <typename T, int N>
struct is_atomic_simd_mask_array_internal<fixed_size_simd_mask<T, N>>
: is_atomic_simd_mask_array_internal<SimdMaskArray<T, N>> {
};
template <typename T, std::size_t N, typename VectorType, std::size_t M>
struct is_simdarray_internal<SimdArray<T, N, VectorType, M>> : public std::true_type {
};
template <typename T, int N>
struct is_simdarray_internal<fixed_size_simd<T, N>> : std::true_type {
};
template <typename T, std::size_t N, typename VectorType, std::size_t M>
struct is_simd_mask_array_internal<SimdMaskArray<T, N, VectorType, M>>
: public std::true_type {
};
template <typename T, int N>
struct is_simd_mask_array_internal<fixed_size_simd_mask<T, N>> : std::true_type {
};
template <typename T, std::size_t N, typename V, std::size_t M>
struct is_integral_internal<SimdArray<T, N, V, M>, false> : public std::is_integral<T> {
};
template <typename T, std::size_t N, typename V, std::size_t M>
struct is_floating_point_internal<SimdArray<T, N, V, M>, false>
: public std::is_floating_point<T> {
};
template <typename T, std::size_t N, typename V, std::size_t M>
struct is_signed_internal<SimdArray<T, N, V, M>, false> : public std::is_signed<T> {
};
template <typename T, std::size_t N, typename V, std::size_t M>
struct is_unsigned_internal<SimdArray<T, N, V, M>, false> : public std::is_unsigned<T> {
};
template <typename T, std::size_t N>
struct has_no_allocated_data_impl<Vc::SimdArray<T, N>> : public std::true_type {
};
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace detail
{
template <class T> struct is_fixed_size_abi : std::false_type {
};
template <int N> struct is_fixed_size_abi<simd_abi::fixed_size<N>> : std::true_type {
};
template <class T>
using not_fixed_size_abi = typename std::enable_if<!is_fixed_size_abi<T>::value, T>::type;
}
}
#endif
#ifndef VC_COMMON_VECTORTRAITS_H_
#define VC_COMMON_VECTORTRAITS_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
template <typename T, typename Abi> struct VectorTraits;
}
#endif
#ifndef VC_COMMON_LOADSTOREFLAGS_H_
#define VC_COMMON_LOADSTOREFLAGS_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
struct Exclusive {};
struct Shared {};
namespace LoadStoreFlags
{
struct StreamingFlag {};
struct UnalignedFlag {};
struct PrefetchFlagBase {};
template <size_t L1 = 16 * 64, size_t L2 = 128 * 64, typename ExclusiveOrShared_ = void>
struct PrefetchFlag : public PrefetchFlagBase {
typedef ExclusiveOrShared_ ExclusiveOrShared;
static constexpr size_t L1Stride = L1;
static constexpr size_t L2Stride = L2;
static constexpr bool IsExclusive = std::is_same<ExclusiveOrShared, Exclusive>::value;
static constexpr bool IsShared = std::is_same<ExclusiveOrShared, Shared>::value;
};
template<typename Base, typename Default, typename... LoadStoreFlags> struct ExtractType
{
typedef Default type;
};
template<typename Base, typename Default, typename T, typename... LoadStoreFlags> struct ExtractType<Base, Default, T, LoadStoreFlags...>
{
typedef typename std::conditional<std::is_base_of<Base, T>::value, T, typename ExtractType<Base, Default, LoadStoreFlags...>::type>::type type;
};
#ifdef Vc_ICC
#pragma warning(disable: 177)
#endif
template<typename... Flags> struct LoadStoreFlags
{
private:
typedef typename ExtractType<PrefetchFlagBase, PrefetchFlag<0, 0>, Flags...>::type Prefetch;
public:
constexpr LoadStoreFlags() {}
static constexpr bool IsStreaming = !std::is_same<typename ExtractType<StreamingFlag, void, Flags...>::type, void>::value;
static constexpr bool IsUnaligned = !std::is_same<typename ExtractType<UnalignedFlag, void, Flags...>::type, void>::value;
static constexpr bool IsAligned = !IsUnaligned;
static constexpr bool IsPrefetch = !std::is_same<typename ExtractType<PrefetchFlagBase, void, Flags...>::type, void>::value;
static constexpr bool IsExclusivePrefetch = Prefetch::IsExclusive;
static constexpr bool IsSharedPrefetch = Prefetch::IsShared;
static constexpr size_t L1Stride = Prefetch::L1Stride;
static constexpr size_t L2Stride = Prefetch::L2Stride;
typedef LoadStoreFlags<typename std::conditional<std::is_same<Flags, UnalignedFlag>::value, void, Flags>::type...> UnalignedRemoved;
typedef typename std::conditional<IsAligned && !IsStreaming, void *, void>::type EnableIfAligned;
typedef typename std::conditional<IsAligned && IsStreaming, void *, void>::type EnableIfStreaming;
typedef typename std::conditional<IsUnaligned && !IsStreaming, void *, void>::type EnableIfUnalignedNotStreaming;
typedef typename std::conditional<IsUnaligned && IsStreaming, void *, void>::type EnableIfUnalignedAndStreaming;
typedef typename std::conditional<IsUnaligned , void *, void>::type EnableIfUnaligned;
typedef typename std::conditional<!IsUnaligned , void *, void>::type EnableIfNotUnaligned;
typedef typename std::conditional<IsPrefetch , void *, void>::type EnableIfPrefetch;
typedef typename std::conditional<!IsPrefetch , void *, void>::type EnableIfNotPrefetch;
};
template<> struct LoadStoreFlags<>
{
constexpr LoadStoreFlags() {}
static constexpr bool IsStreaming = false;
static constexpr bool IsUnaligned = false;
static constexpr bool IsAligned = !IsUnaligned;
static constexpr bool IsPrefetch = false;
static constexpr bool IsExclusivePrefetch = false;
static constexpr bool IsSharedPrefetch = false;
static constexpr size_t L1Stride = 0;
static constexpr size_t L2Stride = 0;
typedef void* EnableIfAligned;
typedef void* EnableIfNotUnaligned;
typedef void* EnableIfNotPrefetch;
};
template<typename... LFlags, typename... RFlags>
constexpr LoadStoreFlags<LFlags..., RFlags...> operator|(LoadStoreFlags<LFlags...>, LoadStoreFlags<RFlags...>)
{
return LoadStoreFlags<LFlags..., RFlags...>();
}
}
using LoadStoreFlags::PrefetchFlag;
typedef LoadStoreFlags::LoadStoreFlags<> AlignedTag;
typedef LoadStoreFlags::LoadStoreFlags<LoadStoreFlags::StreamingFlag> StreamingTag;
typedef LoadStoreFlags::LoadStoreFlags<LoadStoreFlags::UnalignedFlag> UnalignedTag;
typedef UnalignedTag DefaultLoadTag;
typedef UnalignedTag DefaultStoreTag;
constexpr AlignedTag Aligned;
constexpr UnalignedTag Unaligned;
constexpr StreamingTag Streaming;
constexpr LoadStoreFlags::LoadStoreFlags<PrefetchFlag<>> PrefetchDefault;
template <size_t L1 = PrefetchFlag<>::L1Stride,
size_t L2 = PrefetchFlag<>::L2Stride,
typename ExclusiveOrShared = PrefetchFlag<>::ExclusiveOrShared>
struct Prefetch : public LoadStoreFlags::LoadStoreFlags<PrefetchFlag<L1, L2, ExclusiveOrShared>>
{
};
namespace Traits
{
template <typename... Ts>
struct is_loadstoreflag_internal<LoadStoreFlags::LoadStoreFlags<Ts...>> : public std::true_type
{
};
template <size_t L1, size_t L2, typename ExclusiveOrShared>
struct is_loadstoreflag_internal<Prefetch<L1, L2, ExclusiveOrShared>> : public std::true_type
{
};
}
}
#endif
#ifndef VC_COMMON_WRITEMASKEDVECTOR_H_
#define VC_COMMON_WRITEMASKEDVECTOR_H_ 
#include <utility>
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template <typename V, typename M = typename V::Mask> class WriteMaskedVector
{
static_assert(
V::Size == M::Size,
"incorrect use of Vc::Common::WriteMaskedVector<V, M>. V and M must have the same «Size».");
public:
typedef M Mask;
static constexpr size_t Size = V::Size;
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(Mask));
Vc_INTRINSIC WriteMaskedVector(V &v, const Mask &k) : mask(k), vec(v)
{
}
Vc_INTRINSIC V &operator++()
{
V one = V::One();
one.setZeroInverted(mask);
return vec += one;
}
Vc_INTRINSIC V &operator--()
{
V one = V::One();
one.setZeroInverted(mask);
return vec -= one;
}
Vc_INTRINSIC V operator++(int)
{
V ret(vec);
operator++();
return ret;
}
Vc_INTRINSIC V operator--(int)
{
V ret(vec);
operator--();
return ret;
}
#define Vc_OPERATOR_(op) \
template <typename U> Vc_ALWAYS_INLINE void operator op##=(U &&x) \
{ \
operator=(static_cast<V>(vec op std::forward<U>(x))); \
}
Vc_ALL_BINARY(Vc_OPERATOR_);
Vc_ALL_ARITHMETICS(Vc_OPERATOR_);
Vc_ALL_SHIFTS(Vc_OPERATOR_);
#undef Vc_OPERATOR_
Vc_ALWAYS_INLINE void operator=(const V &x)
{
vec.assign(x, mask);
}
template <typename T, typename I, typename S>
Vc_ALWAYS_INLINE void operator=(SubscriptOperation<T, I, S, true> &&x)
{
vec.gather(x.gatherArguments(), mask);
}
template <typename F> Vc_INTRINSIC void call(const F &f) const
{
return vec.call(f, mask);
}
template <typename F> Vc_INTRINSIC V apply(const F &f) const
{
return vec.apply(f, mask);
}
template <typename F> Vc_INTRINSIC void call(F &&f) const
{
return vec.call(std::forward<F>(f), mask);
}
template <typename F> Vc_INTRINSIC V apply(F &&f) const
{
return vec.apply(std::forward<F>(f), mask);
}
private:
#ifdef Vc_ICC
const Mask &mask;
#else
const Mask mask;
#endif
V &vec;
};
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
template <typename T, typename Abi,
typename = enable_if<std::is_floating_point<T>::value &&
!detail::is_fixed_size_abi<Abi>::value>>
inline Vector<T, Abi> copysign(Vector<T, Abi> magnitude, Vector<T, Abi> sign);
template <typename T, typename Abi,
typename = enable_if<std::is_floating_point<T>::value &&
!detail::is_fixed_size_abi<Abi>::value>>
inline Vector<T, Abi> exponent(Vector<T, Abi> x);
template <typename T, typename Abi>
Vc_INTRINSIC Vc_CONST typename Vector<T, detail::not_fixed_size_abi<Abi>>::MaskType
isnegative(Vector<T, Abi> x)
{
return x < Vector<T, Abi>::Zero();
}
template<typename T, typename Abi = VectorAbi::Best<T>> class Vector
{
public:
static constexpr size_t size() { return VectorTraits<T, Abi>::size(); }
static constexpr size_t MemoryAlignment = VectorTraits<T, Abi>::memoryAlignment();
using abi = Abi;
using EntryType = typename VectorTraits<T, Abi>::EntryType;
using value_type = EntryType;
using VectorEntryType = typename VectorTraits<T, Abi>::VectorEntryType;
using VectorType = typename VectorTraits<T, Abi>::VectorType;
using vector_type = VectorType;
using MaskType = Vc::Mask<T, Abi>;
using mask_type = MaskType;
using MaskArgument = MaskType;
using VectorArgument = Vector;
using IndexType = Vc::SimdArray<int, VectorTraits<T, Abi>::size()>;
using index_type = IndexType;
using reference = Detail::ElementReference<Vector>;
static inline Vector Zero();
static inline Vector One();
static inline Vector IndexesFromZero();
static inline Vector Random();
template <typename G> static inline Vector generate(G gen);
inline Vector() = default;
explicit inline Vector(VectorSpecialInitializerZero);
explicit inline Vector(VectorSpecialInitializerOne);
explicit inline Vector(VectorSpecialInitializerIndexesFromZero);
template <typename U>
inline Vector(Vector<U, abi> x,
enable_if<Traits::is_implicit_cast_allowed<U, T>::value> = nullarg);
#if Vc_IS_VERSION_1
template <typename U>
Vc_DEPRECATED("use simd_cast instead of explicit type casting to convert between "
"vector types") inline explicit Vector(
Vector<U, abi> x,
enable_if<!Traits::is_implicit_cast_allowed<U, T>::value> = nullarg);
#endif
inline Vector(EntryType a);
template <typename U>
inline Vector(U a, enable_if<std::is_same<U, int>::value &&
!std::is_same<U, EntryType>::value> = nullarg);
explicit Vc_INTRINSIC Vector(const EntryType *mem)
{
load(mem);
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const EntryType *mem, Flags flags)
{
load(mem, flags);
}
template <typename U, typename Flags = DefaultLoadTag,
typename = enable_if<
(!std::is_integral<U>::value || !std::is_integral<EntryType>::value ||
sizeof(EntryType) >= sizeof(U)) &&
std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const U *x, Flags flags = Flags())
{
load<U, Flags>(x, flags);
}
Vc_INTRINSIC void load(const EntryType *mem)
{
load(mem, DefaultLoadTag());
}
template <typename Flags>
Vc_INTRINSIC enable_if<Traits::is_load_store_flag<Flags>::value, void>
load(const EntryType *mem, Flags flags)
{
load<EntryType, Flags>(mem, flags);
}
private:
template <typename U, typename Flags>
struct load_concept : public std::enable_if<
(!std::is_integral<U>::value || !std::is_integral<EntryType>::value ||
sizeof(EntryType) >= sizeof(U)) &&
std::is_arithmetic<U>::value && Traits::is_load_store_flag<Flags>::value, void>
{};
public:
template <typename U, typename Flags = DefaultLoadTag>
Vc_INTRINSIC_L typename load_concept<U, Flags>::type load(const U *mem, Flags = Flags()) Vc_INTRINSIC_R;
template <
typename U,
typename Flags = DefaultStoreTag,
typename = enable_if<std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC_L void store(U *mem, Flags flags = Flags()) const Vc_INTRINSIC_R;
template <
typename U,
typename Flags = DefaultStoreTag,
typename = enable_if<std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC_L void Vc_VDECL store(U *mem, MaskType mask, Flags flags = Flags()) const Vc_INTRINSIC_R;
Vc_INTRINSIC void store(EntryType *mem) const
{
store<EntryType, DefaultStoreTag>(mem, DefaultStoreTag());
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC void store(EntryType *mem, Flags flags) const
{
store<EntryType, Flags>(mem, flags);
}
Vc_INTRINSIC void Vc_VDECL store(EntryType *mem, MaskType mask) const
{
store<EntryType, DefaultStoreTag>(mem, mask, DefaultStoreTag());
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC void Vc_VDECL store(EntryType *mem, MaskType mask, Flags flags) const
{
store<EntryType, Flags>(mem, mask, flags);
}
inline void setZero();
inline void setZero(MaskType mask);
inline void setZeroInverted(MaskType mask);
inline void setQnan();
inline void setQnan(MaskType mask);
#define Vc_CURRENT_CLASS_NAME Vector
#ifndef Vc_CURRENT_CLASS_NAME
#error "incorrect use of common/gatherinterface.h: Vc_CURRENT_CLASS_NAME must be defined to the current class name for declaring constructors."
#endif
private:
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes);
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes, MaskArgument mask);
template <typename IT, typename = enable_if<std::is_pointer<IT>::value ||
Traits::is_simd_vector<IT>::value>>
static Vc_INTRINSIC const IT &adjustIndexParameter(const IT &indexes)
{
return indexes;
}
template <
typename IT,
typename = enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value>>
static Vc_INTRINSIC decltype(std::addressof(std::declval<const IT &>()[0]))
adjustIndexParameter(const IT &i)
{
return std::addressof(i[0]);
}
template <typename IT>
static Vc_INTRINSIC enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
!std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value,
IT>
adjustIndexParameter(const IT &i)
{
return i;
}
public:
#define Vc_ASSERT_GATHER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<MT, EntryType>::value, \
"The memory pointer needs to point to a type that can be converted to the " \
"EntryType of this SIMD vector type."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT, typename IT,
typename = enable_if<Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes,
MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes, MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args)
{
gather(args.address, adjustIndexParameter(args.indexes));
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args, MaskArgument mask)
{
gather(args.address, adjustIndexParameter(args.indexes), mask);
}
#undef Vc_ASSERT_GATHER_PARAMETER_TYPES_
private:
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes) const;
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes, MaskArgument mask) const;
public:
#define Vc_ASSERT_SCATTER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<EntryType, MT>::value, \
"The memory pointer needs to point to a type that the EntryType of this " \
"SIMD vector type can be converted to."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes));
}
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes, MaskArgument mask) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args) const
{
scatter(args.address, args.indexes);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args, MaskArgument mask) const
{
scatter(args.address, args.indexes, mask);
}
#undef Vc_ASSERT_SCATTER_PARAMETER_TYPES_
#undef Vc_CURRENT_CLASS_NAME
inline reference operator[](size_t index) noexcept;
inline EntryType operator[](size_t index) const noexcept;
inline MaskType operator!() const;
inline Vector operator~() const;
inline Vector operator-() const;
inline Vector operator+() const;
inline Vector &operator++();
inline Vector operator++(int);
inline Vector &operator--();
inline Vector operator--(int);
#define Vc_OP(symbol) \
inline Vc_PURE Vector operator symbol(const Vector &x) const;
Vc_ALL_ARITHMETICS(Vc_OP);
Vc_ALL_BINARY(Vc_OP);
Vc_ALL_SHIFTS(Vc_OP);
#undef Vc_OP
#define Vc_CMP_OP(symbol) inline Vc_PURE MaskType operator symbol(const Vector &x) const;
Vc_ALL_COMPARES(Vc_CMP_OP);
#undef Vc_CMP_OP
inline Common::WriteMaskedVector<Vector, MaskType> operator()(MaskType mask);
inline EntryType min() const;
inline EntryType max() const;
inline EntryType product() const;
inline EntryType sum() const;
inline Vector partialSum() const;
inline EntryType min(MaskType mask) const;
inline EntryType max(MaskType mask) const;
inline EntryType product(MaskType mask) const;
inline EntryType sum(MaskType mask) const;
inline Vector shifted(int amount) const;
inline Vector shifted(int amount, Vector shiftIn) const;
inline Vector rotated(int amount) const;
inline Vector reversed() const;
inline Vector sorted() const;
template <typename F> void callWithValuesSorted(F &&f);
template <typename F> inline void call(F &&f) const;
template <typename F> inline void call(F &&f, MaskType mask) const;
template <typename F> inline Vector apply(F &&f) const;
template <typename F> inline Vector apply(F &&f, MaskType mask) const;
template <typename IndexT> inline void fill(EntryType(&f)(IndexT));
inline void fill(EntryType(&f)());
inline Vector interleaveLow(Vector x) const;
inline Vector interleaveHigh(Vector x) const;
inline void assign(const Vector &v, const MaskType &m);
inline VectorType &data();
inline const VectorType &data() const;
Vc_DEPRECATED("use exponent(x) instead") inline Vector exponent() const;
Vc_DEPRECATED("use isnegative(x) instead") inline MaskType isNegative() const;
static constexpr size_t Size = VectorTraits<T, Abi>::size();
template <typename V2> inline V2 staticCast() const;
template <typename V2>
Vc_DEPRECATED("use reinterpret_components_cast instead") inline V2
reinterpretCast() const;
Vc_DEPRECATED("use copysign(x, y) instead") inline Vector
copySign(Vector reference) const;
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(Vector));
private:
VectorType d;
};
template <typename V, typename T, typename Abi>
Vc_ALWAYS_INLINE Vc_CONST enable_if<
(V::size() == Vector<T, Abi>::size() &&
sizeof(typename V::VectorEntryType) ==
sizeof(typename Vector<T, Abi>::VectorEntryType) &&
sizeof(V) == sizeof(Vector<T, Abi>) && alignof(V) <= alignof(Vector<T, Abi>)),
V>
reinterpret_components_cast(const Vector<T, Abi> &x)
{
return reinterpret_cast<const V &>(x);
}
#define Vc_OP(symbol) \
template <typename T, typename Abi> \
inline Vector<T, Abi> &operator symbol##=(Vector<T, Abi> &, \
const Vector<T, Abi> &x);
#undef Vc_OP
}
#endif
#ifndef VC_COMMON_MASK_H_
#define VC_COMMON_MASK_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
template <typename T, typename Abi = VectorAbi::Best<T>> class Mask
{
public:
static constexpr size_t size() { return VectorTraits<T, Abi>::size(); }
static constexpr size_t Size = VectorTraits<T, Abi>::size();
static constexpr size_t MemoryAlignment = VectorTraits<T, Abi>::maskMemoryAlignment();
using abi = Abi;
using EntryType = bool;
using value_type = EntryType;
using EntryReference = typename VectorTraits<T, Abi>::EntryReference;
using value_reference = EntryReference;
using VectorEntryType = typename VectorTraits<T, Abi>::VectorEntryType;
using VectorType = typename VectorTraits<T, Abi>::VectorType;
using vector_type = VectorType;
Vc_INTRINSIC static Mask Zero();
Vc_INTRINSIC static Mask One();
template <typename G> static Vc_INTRINSIC Mask generate(G &&gen);
Vc_INTRINSIC Mask() = default;
Vc_INTRINSIC explicit Mask(VectorSpecialInitializerZero);
Vc_INTRINSIC explicit Mask(VectorSpecialInitializerOne);
Vc_INTRINSIC explicit Mask(bool b);
template <typename U>
Vc_INTRINSIC Mask(U &&otherMask,
Common::enable_if_mask_converts_implicitly<Mask, T, U> = nullarg);
#if Vc_IS_VERSION_1
template <typename U>
Vc_DEPRECATED(
"use simd_cast instead of explicit type casting to convert between mask types")
Vc_INTRINSIC_L
explicit Mask(U &&otherMask, Common::enable_if_mask_converts_explicitly<T, U> =
nullarg) Vc_INTRINSIC_R;
#endif
Vc_ALWAYS_INLINE explicit Mask(const bool *mem);
template <typename Flags> Vc_ALWAYS_INLINE explicit Mask(const bool *mem, Flags flags);
Vc_ALWAYS_INLINE void load(const bool *mem);
template <typename Flags> Vc_ALWAYS_INLINE void load(const bool *mem, Flags flags);
Vc_ALWAYS_INLINE void store(bool *mem) const;
template <typename Flags> Vc_ALWAYS_INLINE void store(bool *mem, Flags flags) const;
Vc_ALWAYS_INLINE bool operator==(const Mask &mask) const;
Vc_ALWAYS_INLINE bool operator!=(const Mask &mask) const;
Vc_ALWAYS_INLINE Mask operator&&(const Mask &mask) const;
Vc_ALWAYS_INLINE Mask operator&(const Mask &mask) const;
Vc_ALWAYS_INLINE Mask operator||(const Mask &mask) const;
Vc_ALWAYS_INLINE Mask operator|(const Mask &mask) const;
Vc_ALWAYS_INLINE Mask operator^(const Mask &mask) const;
Vc_ALWAYS_INLINE Mask operator!() const;
Vc_ALWAYS_INLINE Mask &operator&=(const Mask &mask);
Vc_ALWAYS_INLINE Mask &operator|=(const Mask &mask);
Vc_ALWAYS_INLINE Mask &operator^=(const Mask &mask);
Vc_ALWAYS_INLINE bool isFull() const;
Vc_ALWAYS_INLINE bool isNotEmpty() const;
Vc_ALWAYS_INLINE bool isEmpty() const;
Vc_ALWAYS_INLINE bool isMix() const;
Vc_ALWAYS_INLINE bool data() const;
Vc_ALWAYS_INLINE bool dataI() const;
Vc_ALWAYS_INLINE bool dataD() const;
Vc_ALWAYS_INLINE EntryReference operator[](size_t index);
Vc_ALWAYS_INLINE EntryType operator[](size_t index) const;
Vc_ALWAYS_INLINE int count() const;
Vc_ALWAYS_INLINE int firstOne() const;
Vc_ALWAYS_INLINE int toInt() const;
Vc_INTRINSIC Vc_PURE Mask shifted(int amount) const;
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(Mask));
private:
VectorType d;
};
}
#endif
#ifndef VC_COMMON_MEMORYFWD_H_
#define VC_COMMON_MEMORYFWD_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template <typename V, std::size_t Size1 = 0, std::size_t Size2 = 0,
bool InitPadding = true>
class Memory;
template <typename V, typename Parent, int Dimension, typename RowMemory>
class MemoryBase;
}
using Common::Memory;
}
#endif
#endif
#ifndef VC_SCALAR_TYPES_H_
#define VC_SCALAR_TYPES_H_ 
#ifdef Vc_DEFAULT_IMPL_Scalar
#define Vc_DOUBLE_V_SIZE 1
#define Vc_FLOAT_V_SIZE 1
#define Vc_INT_V_SIZE 1
#define Vc_UINT_V_SIZE 1
#define Vc_SHORT_V_SIZE 1
#define Vc_USHORT_V_SIZE 1
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Scalar
{
template <typename T> using Vector = Vc::Vector<T, VectorAbi::Scalar>;
typedef Vector<double> double_v;
typedef Vector<float> float_v;
typedef Vector<int> int_v;
typedef Vector<unsigned int> uint_v;
typedef Vector<short> short_v;
typedef Vector<unsigned short> ushort_v;
template <typename T> using Mask = Vc::Mask<T, VectorAbi::Scalar>;
typedef Mask<double> double_m;
typedef Mask<float> float_m;
typedef Mask<int> int_m;
typedef Mask<unsigned int> uint_m;
typedef Mask<short> short_m;
typedef Mask<unsigned short> ushort_m;
template <typename T> struct is_vector : public std::false_type {};
template <typename T> struct is_vector<Vector<T>> : public std::true_type {};
template <typename T> struct is_mask : public std::false_type {};
template <typename T> struct is_mask<Mask<T>> : public std::true_type {};
}
namespace Traits
{
template <typename T> struct is_simd_mask_internal<Scalar::Mask<T>>
: public std::true_type {};
template <class T> struct
is_simd_vector_internal<Vector<T, VectorAbi::Scalar>>
: public is_valid_vector_argument<T> {};
}
}
#endif
#ifndef VC_SCALAR_DETAIL_H_
#define VC_SCALAR_DETAIL_H_ 
#ifndef VC_SCALAR_MACROS_H_
#define VC_SCALAR_MACROS_H_ 
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template<typename V, size_t Size, size_t VSize> struct InterleaveImpl;
template<typename V, size_t VSize> struct InterleaveImpl<V, 1, VSize> {
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
data[i[0] + 0] = v0.data();
data[i[0] + 1] = v1.data();
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2)
{
data[i[0] + 0] = v0.data();
data[i[0] + 1] = v1.data();
data[i[0] + 2] = v2.data();
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
data[i[0] + 0] = v0.data();
data[i[0] + 1] = v1.data();
data[i[0] + 2] = v2.data();
data[i[0] + 3] = v3.data();
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4)
{
interleave(data, i, v0, v1, v2, v3);
data[i[0] + 4] = v4.data();
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6, const typename V::AsArg v7)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6, v7);
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1)
{
v0.data() = data[i[0] + 0];
v1.data() = data[i[0] + 1];
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1, V &v2)
{
v0.data() = data[i[0] + 0];
v1.data() = data[i[0] + 1];
v2.data() = data[i[0] + 2];
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1, V &v2, V &v3)
{
v0.data() = data[i[0] + 0];
v1.data() = data[i[0] + 1];
v2.data() = data[i[0] + 2];
v3.data() = data[i[0] + 3];
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1, V &v2, V &v3, V &v4)
{
deinterleave(data, i, v0, v1, v2, v3);
v4.data() = data[i[0] + 4];
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1, V &v2, V &v3, V &v4, V &v5)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5);
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5, v6);
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6,
V &v7)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5, v6, v7);
}
};
}
}
#endif
#ifndef VC_SCALAR_MASK_H_
#define VC_SCALAR_MASK_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
template <typename T> class Mask<T, VectorAbi::Scalar>
{
friend class Mask< double, VectorAbi::Scalar>;
friend class Mask< float, VectorAbi::Scalar>;
friend class Mask< int32_t, VectorAbi::Scalar>;
friend class Mask<uint32_t, VectorAbi::Scalar>;
friend class Mask< int16_t, VectorAbi::Scalar>;
friend class Mask<uint16_t, VectorAbi::Scalar>;
public:
using abi = VectorAbi::Scalar;
static constexpr size_t Size = 1;
static constexpr size_t MemoryAlignment = 1;
static constexpr std::size_t size() { return 1; }
typedef bool EntryType;
using value_type = EntryType;
using EntryReference = Vc::Detail::ElementReference<Mask>;
using reference = EntryReference;
typedef bool VectorEntryType;
using VectorType = bool;
using Vector = Scalar::Vector<T>;
Vc_INTRINSIC Mask() = default;
Vc_INTRINSIC explicit Mask(bool b) : m(b) {}
Vc_INTRINSIC explicit Mask(VectorSpecialInitializerZero) : m(false) {}
Vc_INTRINSIC explicit Mask(VectorSpecialInitializerOne) : m(true) {}
Vc_INTRINSIC static Mask Zero() { return Mask(false); }
Vc_INTRINSIC static Mask One() { return Mask(true); }
template <typename U>
Vc_INTRINSIC Mask(U &&rhs, Common::enable_if_mask_converts_implicitly<Mask, T, U> = nullarg)
: m(rhs.m) {}
#if Vc_IS_VERSION_1
template <typename U>
Vc_DEPRECATED(
"use simd_cast instead of explicit type casting to convert between mask types")
Vc_INTRINSIC_L
explicit Mask(U &&rhs, Common::enable_if_mask_converts_explicitly<T, U> = nullarg)
Vc_INTRINSIC_R;
#endif
Vc_ALWAYS_INLINE explicit Mask(const bool *mem) : m(mem[0]) {}
template<typename Flags> Vc_ALWAYS_INLINE explicit Mask(const bool *mem, Flags) : m(mem[0]) {}
Vc_ALWAYS_INLINE void load(const bool *mem) { m = mem[0]; }
template<typename Flags> Vc_ALWAYS_INLINE void load(const bool *mem, Flags) { m = mem[0]; }
Vc_ALWAYS_INLINE void store(bool *mem) const { *mem = m; }
template<typename Flags> Vc_ALWAYS_INLINE void store(bool *mem, Flags) const { *mem = m; }
Vc_ALWAYS_INLINE bool operator==(const Mask &rhs) const { return m == rhs.m; }
Vc_ALWAYS_INLINE bool operator!=(const Mask &rhs) const { return m != rhs.m; }
Vc_ALWAYS_INLINE Mask operator&&(const Mask &rhs) const { return Mask(m && rhs.m); }
Vc_ALWAYS_INLINE Mask operator& (const Mask &rhs) const { return Mask(m && rhs.m); }
Vc_ALWAYS_INLINE Mask operator||(const Mask &rhs) const { return Mask(m || rhs.m); }
Vc_ALWAYS_INLINE Mask operator| (const Mask &rhs) const { return Mask(m || rhs.m); }
Vc_ALWAYS_INLINE Mask operator^ (const Mask &rhs) const { return Mask(m ^ rhs.m); }
Vc_ALWAYS_INLINE Mask operator!() const { return Mask(!m); }
Vc_ALWAYS_INLINE Mask &operator&=(const Mask &rhs) { m &= rhs.m; return *this; }
Vc_ALWAYS_INLINE Mask &operator|=(const Mask &rhs) { m |= rhs.m; return *this; }
Vc_ALWAYS_INLINE Mask &operator^=(const Mask &rhs) { m ^= rhs.m; return *this; }
Vc_ALWAYS_INLINE bool isFull () const { return m; }
Vc_ALWAYS_INLINE bool isNotEmpty() const { return m; }
Vc_ALWAYS_INLINE bool isEmpty() const { return !m; }
Vc_ALWAYS_INLINE bool isMix () const { return false; }
Vc_ALWAYS_INLINE bool data () const { return m; }
Vc_ALWAYS_INLINE bool dataI() const { return m; }
Vc_ALWAYS_INLINE bool dataD() const { return m; }
private:
friend reference;
static Vc_INTRINSIC bool get(const Mask &o, int) noexcept { return o.m; }
template <typename U>
static Vc_INTRINSIC void set(Mask &o, int, U &&v) noexcept(
noexcept(std::declval<bool &>() = std::declval<U>()))
{
o.m = std::forward<U>(v);
}
public:
Vc_ALWAYS_INLINE reference operator[](size_t i) noexcept
{
Vc_ASSERT(i == 0); if (i) {}
return {*this, 0};
}
Vc_ALWAYS_INLINE value_type operator[](size_t i) const noexcept
{
Vc_ASSERT(i == 0); if (i) {}
return m;
}
Vc_ALWAYS_INLINE int count() const { return m ? 1 : 0; }
Vc_ALWAYS_INLINE int firstOne() const { return 0; }
Vc_ALWAYS_INLINE int toInt() const { return m ? 1 : 0; }
template <typename G> static Vc_INTRINSIC Mask generate(G &&gen)
{
return Mask(gen(0));
}
Vc_INTRINSIC Vc_PURE Mask shifted(int amount) const
{
if (amount == 0) {
return *this;
} else {
return Zero();
}
}
private:
bool m;
};
template <typename T> constexpr size_t Mask<T, VectorAbi::Scalar>::Size;
template <typename T> constexpr size_t Mask<T, VectorAbi::Scalar>::MemoryAlignment;
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
#define Vc_CURRENT_CLASS_NAME Vector
template <typename T> class Vector<T, VectorAbi::Scalar>
{
static_assert(std::is_arithmetic<T>::value,
"Vector<T> only accepts arithmetic builtin types as template parameter T.");
public:
using abi = VectorAbi::Scalar;
using EntryType = typename Common::ensure_alignment_equals_sizeof<T>::type;
using VectorEntryType = EntryType;
using value_type = EntryType;
using VectorType = EntryType;
using vector_type = VectorType;
using reference = Detail::ElementReference<Vector>;
protected:
VectorType m_data = VectorType();
template <typename U> using V = Vector<U, abi>;
public:
typedef Scalar::Mask<T> Mask;
using MaskType = Mask;
using mask_type = Mask;
typedef Mask MaskArgument;
typedef Vector AsArg;
Vc_ALWAYS_INLINE VectorType &data() { return m_data; }
Vc_ALWAYS_INLINE const VectorType &data() const { return m_data; }
static constexpr size_t Size = 1;
static constexpr size_t MemoryAlignment = alignof(VectorType);
typedef SimdArray<int, Size, Scalar::int_v, 1> IndexType;
public:
Vc_INTRINSIC Vector() = default;
static constexpr std::size_t size() { return Size; }
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerZero) Vc_INTRINSIC_R;
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerOne) Vc_INTRINSIC_R;
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerIndexesFromZero) Vc_INTRINSIC_R;
static Vc_INTRINSIC Vc_CONST Vector Zero() { return Vector(Vc::Zero); }
static Vc_INTRINSIC Vc_CONST Vector One() { return Vector(Vc::One); }
static Vc_INTRINSIC Vc_CONST Vector IndexesFromZero()
{
return Vector(Vc::IndexesFromZero);
}
template <class G, class...,
class = typename std::enable_if<std::is_convertible<
decltype(std::declval<G>()(size_t())), value_type>::value>::type>
explicit Vector(G &&g) : Vector(generate(std::forward<G>(g)))
{
}
static Vc_INTRINSIC_L Vector Random() Vc_INTRINSIC_R;
template <typename U>
Vc_INTRINSIC Vector(
V<U> x, typename std::enable_if<Traits::is_implicit_cast_allowed<U, T>::value,
void *>::type = nullptr)
: m_data(static_cast<EntryType>(x.data()))
{
}
#if Vc_IS_VERSION_1
template <typename U>
Vc_DEPRECATED("use simd_cast instead of explicit type casting to convert between "
"vector types") Vc_INTRINSIC
explicit Vector(
V<U> x,
typename std::enable_if<!Traits::is_implicit_cast_allowed<U, T>::value,
void *>::type = nullptr)
: m_data(static_cast<EntryType>(x.data()))
{
}
#endif
Vc_INTRINSIC Vector(EntryType a) : m_data(a) {}
template <typename U>
Vc_INTRINSIC Vector(U a,
typename std::enable_if<std::is_same<U, int>::value &&
!std::is_same<U, EntryType>::value,
void *>::type = nullptr)
: Vector(static_cast<EntryType>(a))
{
}
explicit Vc_INTRINSIC Vector(const EntryType *mem)
{
load(mem);
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const EntryType *mem, Flags flags)
{
load(mem, flags);
}
template <typename U, typename Flags = DefaultLoadTag,
typename = enable_if<
(!std::is_integral<U>::value || !std::is_integral<EntryType>::value ||
sizeof(EntryType) >= sizeof(U)) &&
std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const U *x, Flags flags = Flags())
{
load<U, Flags>(x, flags);
}
Vc_INTRINSIC void load(const EntryType *mem)
{
load(mem, DefaultLoadTag());
}
template <typename Flags>
Vc_INTRINSIC enable_if<Traits::is_load_store_flag<Flags>::value, void>
load(const EntryType *mem, Flags flags)
{
load<EntryType, Flags>(mem, flags);
}
private:
template <typename U, typename Flags>
struct load_concept : public std::enable_if<
(!std::is_integral<U>::value || !std::is_integral<EntryType>::value ||
sizeof(EntryType) >= sizeof(U)) &&
std::is_arithmetic<U>::value && Traits::is_load_store_flag<Flags>::value, void>
{};
public:
template <typename U, typename Flags = DefaultLoadTag>
Vc_INTRINSIC_L typename load_concept<U, Flags>::type load(const U *mem, Flags = Flags()) Vc_INTRINSIC_R;
template <
typename U,
typename Flags = DefaultStoreTag,
typename = enable_if<std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC_L void store(U *mem, Flags flags = Flags()) const Vc_INTRINSIC_R;
template <
typename U,
typename Flags = DefaultStoreTag,
typename = enable_if<std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC_L void Vc_VDECL store(U *mem, MaskType mask, Flags flags = Flags()) const Vc_INTRINSIC_R;
Vc_INTRINSIC void store(EntryType *mem) const
{
store<EntryType, DefaultStoreTag>(mem, DefaultStoreTag());
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC void store(EntryType *mem, Flags flags) const
{
store<EntryType, Flags>(mem, flags);
}
Vc_INTRINSIC void Vc_VDECL store(EntryType *mem, MaskType mask) const
{
store<EntryType, DefaultStoreTag>(mem, mask, DefaultStoreTag());
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC void Vc_VDECL store(EntryType *mem, MaskType mask, Flags flags) const
{
store<EntryType, Flags>(mem, mask, flags);
}
Vc_ALWAYS_INLINE void setZero() { m_data = 0; }
Vc_ALWAYS_INLINE void setZero(Mask k) { if (k.data()) m_data = 0; }
Vc_ALWAYS_INLINE void setZeroInverted(Mask k) { if (!k.data()) m_data = 0; }
Vc_INTRINSIC_L void setQnan() Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setQnan(Mask m) Vc_INTRINSIC_R;
#ifndef Vc_CURRENT_CLASS_NAME
#error "incorrect use of common/gatherinterface.h: Vc_CURRENT_CLASS_NAME must be defined to the current class name for declaring constructors."
#endif
private:
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes);
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes, MaskArgument mask);
template <typename IT, typename = enable_if<std::is_pointer<IT>::value ||
Traits::is_simd_vector<IT>::value>>
static Vc_INTRINSIC const IT &adjustIndexParameter(const IT &indexes)
{
return indexes;
}
template <
typename IT,
typename = enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value>>
static Vc_INTRINSIC decltype(std::addressof(std::declval<const IT &>()[0]))
adjustIndexParameter(const IT &i)
{
return std::addressof(i[0]);
}
template <typename IT>
static Vc_INTRINSIC enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
!std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value,
IT>
adjustIndexParameter(const IT &i)
{
return i;
}
public:
#define Vc_ASSERT_GATHER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<MT, EntryType>::value, \
"The memory pointer needs to point to a type that can be converted to the " \
"EntryType of this SIMD vector type."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT, typename IT,
typename = enable_if<Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes,
MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes, MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args)
{
gather(args.address, adjustIndexParameter(args.indexes));
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args, MaskArgument mask)
{
gather(args.address, adjustIndexParameter(args.indexes), mask);
}
#undef Vc_ASSERT_GATHER_PARAMETER_TYPES_
private:
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes) const;
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes, MaskArgument mask) const;
public:
#define Vc_ASSERT_SCATTER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<EntryType, MT>::value, \
"The memory pointer needs to point to a type that the EntryType of this " \
"SIMD vector type can be converted to."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes));
}
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes, MaskArgument mask) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args) const
{
scatter(args.address, args.indexes);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args, MaskArgument mask) const
{
scatter(args.address, args.indexes, mask);
}
#undef Vc_ASSERT_SCATTER_PARAMETER_TYPES_
Vc_ALWAYS_INLINE Vector &operator++() { ++m_data; return *this; }
Vc_ALWAYS_INLINE Vector &operator--() { --m_data; return *this; }
Vc_ALWAYS_INLINE Vector operator++(int) { return m_data++; }
Vc_ALWAYS_INLINE Vector operator--(int) { return m_data--; }
private:
friend reference;
Vc_INTRINSIC static value_type get(const Vector &o, int i) noexcept
{
Vc_ASSERT(i == 0); if (i) {}
return o.m_data;
}
template <typename U>
Vc_INTRINSIC static void set(Vector &o, int i, U &&v) noexcept(
noexcept(std::declval<value_type &>() = v))
{
Vc_ASSERT(i == 0); if (i) {}
o.m_data = v;
}
public:
Vc_ALWAYS_INLINE reference operator[](size_t index) noexcept
{
static_assert(noexcept(reference{std::declval<Vector &>(), int()}), "");
return {*this, int(index)};
}
Vc_ALWAYS_INLINE value_type operator[](size_t index) const noexcept
{
Vc_ASSERT(index == 0); if (index) {}
return m_data;
}
Vc_ALWAYS_INLINE Mask operator!() const
{
return Mask(!m_data);
}
Vc_ALWAYS_INLINE Vector operator~() const
{
#ifndef Vc_ENABLE_FLOAT_BIT_OPERATORS
static_assert(std::is_integral<T>::value, "bit-complement can only be used with Vectors of integral type");
#endif
return Vector(~m_data);
}
Vc_ALWAYS_INLINE Vector operator-() const
{
return -m_data;
}
Vc_INTRINSIC Vector Vc_PURE operator+() const { return *this; }
#define Vc_OP(symbol) \
Vc_ALWAYS_INLINE Vc_PURE Vector operator symbol(const Vector &x) const { return Vector(m_data symbol x.m_data); }
Vc_ALL_SHIFTS(Vc_OP);
#undef Vc_OP
Vc_DEPRECATED("use isnegative(x) instead") Vc_INTRINSIC Vc_PURE Mask
isNegative() const
{
return Vc::isnegative(*this);
}
Vc_ALWAYS_INLINE void assign(const Vector &v, const Mask &m) {
if (m.data()) m_data = v.m_data;
}
template <typename V2>
Vc_DEPRECATED("Use simd_cast instead of Vector::staticCast") Vc_ALWAYS_INLINE V2
staticCast() const
{
return V2(static_cast<typename V2::EntryType>(m_data));
}
template <typename V2>
Vc_DEPRECATED("use reinterpret_components_cast instead") Vc_ALWAYS_INLINE V2
reinterpretCast() const
{
typedef typename V2::EntryType AliasT2 Vc_MAY_ALIAS;
return V2(*reinterpret_cast<const AliasT2 *>(&m_data));
}
Vc_ALWAYS_INLINE Common::WriteMaskedVector<Vector, Mask> operator()(Mask m)
{
return {*this, m};
}
Vc_ALWAYS_INLINE EntryType min() const { return m_data; }
Vc_ALWAYS_INLINE EntryType max() const { return m_data; }
Vc_ALWAYS_INLINE EntryType product() const { return m_data; }
Vc_ALWAYS_INLINE EntryType sum() const { return m_data; }
Vc_ALWAYS_INLINE Vector partialSum() const { return *this; }
Vc_ALWAYS_INLINE EntryType min(Mask) const { return m_data; }
Vc_ALWAYS_INLINE EntryType max(Mask) const { return m_data; }
Vc_ALWAYS_INLINE EntryType product(Mask m) const
{
if (m.data()) {
return m_data;
} else {
return EntryType(1);
}
}
Vc_ALWAYS_INLINE EntryType sum(Mask m) const { if (m.data()) return m_data; return static_cast<EntryType>(0); }
Vc_INTRINSIC Vector Vc_VDECL shifted(int amount, Vector shiftIn) const {
Vc_ASSERT(amount >= -1 && amount <= 1);
return amount == 0 ? *this : shiftIn;
}
Vc_INTRINSIC Vector shifted(int amount) const { return amount == 0 ? *this : Zero(); }
Vc_INTRINSIC Vector rotated(int) const { return *this; }
Vc_INTRINSIC Vector reversed() const { return *this; }
Vc_INTRINSIC Vector sorted() const { return *this; }
template <typename F> void callWithValuesSorted(F &&f) { f(m_data); }
template <typename F> Vc_INTRINSIC void call(F &&f) const { f(m_data); }
template <typename F> Vc_INTRINSIC void call(F &&f, Mask mask) const
{
if (mask.data()) {
f(m_data);
}
}
template <typename F> Vc_INTRINSIC Vector apply(F &&f) const { return Vector(f(m_data)); }
template <typename F> Vc_INTRINSIC Vector apply(F &&f, Mask mask) const
{
if (mask.data()) {
return Vector(f(m_data));
} else {
return *this;
}
}
template<typename IndexT> Vc_INTRINSIC void fill(EntryType (&f)(IndexT)) {
m_data = f(0);
}
Vc_INTRINSIC void fill(EntryType (&f)()) {
m_data = f();
}
template <typename G> static Vc_INTRINSIC Vector generate(G gen)
{
return gen(0);
}
Vc_DEPRECATED("use copysign(x, y) instead") Vc_INTRINSIC Vector Vc_VDECL
copySign(Vector x) const
{
return Vc::copysign(*this, x);
}
Vc_DEPRECATED("use exponent(x) instead") Vc_INTRINSIC Vector exponent() const
{
return Vc::exponent(*this);
}
Vc_INTRINSIC Vector Vc_VDECL interleaveLow(Vector) const { return *this; }
Vc_INTRINSIC Vector Vc_VDECL interleaveHigh(Vector x) const { return x; }
};
#undef Vc_CURRENT_CLASS_NAME
template <typename T> constexpr size_t Vector<T, VectorAbi::Scalar>::Size;
template <typename T> constexpr size_t Vector<T, VectorAbi::Scalar>::MemoryAlignment;
#define Vc_OP(symbol) \
template <typename T, typename U, \
typename = decltype(std::declval<T &>() symbol## = std::declval<T>())> \
Vc_INTRINSIC enable_if<std::is_convertible<U, Vector<T, VectorAbi::Scalar>>::value, \
Vector<T, VectorAbi::Scalar>> \
&operator symbol##=(Vector<T, VectorAbi::Scalar> &lhs, U &&rhs) \
{ \
lhs.data() symbol## = Vector<T, VectorAbi::Scalar>(std::forward<U>(rhs)).data(); \
return lhs; \
}
Vc_ALL_SHIFTS(Vc_OP);
#undef Vc_OP
#define Vc_CONDITIONAL_ASSIGN(name_,op_) \
template <Operator O, typename T, typename M, typename U> \
Vc_INTRINSIC enable_if<O == Operator::name_, void> conditional_assign( \
Vector<T, VectorAbi::Scalar> &lhs, M &&mask, U &&rhs) \
{ \
if (mask.isFull()) { \
lhs op_ std::forward<U>(rhs); \
} \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_CONDITIONAL_ASSIGN( Assign, =);
Vc_CONDITIONAL_ASSIGN( PlusAssign, +=);
Vc_CONDITIONAL_ASSIGN( MinusAssign, -=);
Vc_CONDITIONAL_ASSIGN( MultiplyAssign, *=);
Vc_CONDITIONAL_ASSIGN( DivideAssign, /=);
Vc_CONDITIONAL_ASSIGN( RemainderAssign, %=);
Vc_CONDITIONAL_ASSIGN( XorAssign, ^=);
Vc_CONDITIONAL_ASSIGN( AndAssign, &=);
Vc_CONDITIONAL_ASSIGN( OrAssign, |=);
Vc_CONDITIONAL_ASSIGN( LeftShiftAssign,<<=);
Vc_CONDITIONAL_ASSIGN(RightShiftAssign,>>=);
#undef Vc_CONDITIONAL_ASSIGN
#define Vc_CONDITIONAL_ASSIGN(name_,expr_) \
template <Operator O, typename T, typename M> \
Vc_INTRINSIC enable_if<O == Operator::name_, Vector<T, VectorAbi::Scalar>> \
conditional_assign(Vector<T, VectorAbi::Scalar> &lhs, M &&mask) \
{ \
return mask.isFull() ? (expr_) : lhs; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_CONDITIONAL_ASSIGN(PostIncrement, lhs++);
Vc_CONDITIONAL_ASSIGN( PreIncrement, ++lhs);
Vc_CONDITIONAL_ASSIGN(PostDecrement, lhs--);
Vc_CONDITIONAL_ASSIGN( PreDecrement, --lhs);
#undef Vc_CONDITIONAL_ASSIGN
}
#include <cmath>
#ifndef VC_COMMON_CONST_DATA_H_
#define VC_COMMON_CONST_DATA_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
alignas(64) extern unsigned int RandomState[];
alignas(32) extern const unsigned int AllBitsSet[8];
}
}
#endif
#ifndef VC_COMMON_WHERE_H_
#define VC_COMMON_WHERE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace WhereImpl
{
template<typename _Mask, typename _LValue> struct MaskedLValue
{
typedef _Mask Mask;
typedef _LValue LValue;
const Mask &mask;
LValue &lhs;
constexpr MaskedLValue(const Mask &m, LValue &l) : mask(m), lhs(l) {}
MaskedLValue(const MaskedLValue &) = delete;
constexpr MaskedLValue(MaskedLValue &&) = default;
template<typename T> Vc_ALWAYS_INLINE void operator =(T &&rhs) { conditional_assign<Operator:: Assign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator +=(T &&rhs) { conditional_assign<Operator:: PlusAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator -=(T &&rhs) { conditional_assign<Operator:: MinusAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator *=(T &&rhs) { conditional_assign<Operator:: MultiplyAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator /=(T &&rhs) { conditional_assign<Operator:: DivideAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator %=(T &&rhs) { conditional_assign<Operator:: RemainderAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator ^=(T &&rhs) { conditional_assign<Operator:: XorAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator &=(T &&rhs) { conditional_assign<Operator:: AndAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator |=(T &&rhs) { conditional_assign<Operator:: OrAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator<<=(T &&rhs) { conditional_assign<Operator:: LeftShiftAssign>(lhs, mask, std::forward<T>(rhs)); }
template<typename T> Vc_ALWAYS_INLINE void operator>>=(T &&rhs) { conditional_assign<Operator::RightShiftAssign>(lhs, mask, std::forward<T>(rhs)); }
Vc_ALWAYS_INLINE void operator++() { conditional_assign<Operator:: PreIncrement>(lhs, mask); }
Vc_ALWAYS_INLINE void operator++(int) { conditional_assign<Operator::PostIncrement>(lhs, mask); }
Vc_ALWAYS_INLINE void operator--() { conditional_assign<Operator:: PreDecrement>(lhs, mask); }
Vc_ALWAYS_INLINE void operator--(int) { conditional_assign<Operator::PostDecrement>(lhs, mask); }
};
template <typename _Mask, typename T_, typename I_, typename S_>
struct MaskedLValue<_Mask, Common::SubscriptOperation<T_, I_, S_, true>>
{
typedef _Mask Mask;
typedef Common::SubscriptOperation<T_, I_, S_, true> SO;
const Mask &mask;
const SO lhs;
template <typename T> using Decay = typename std::decay<T>::type;
constexpr MaskedLValue(const Mask &m, SO &&l) : mask(m), lhs(l) {}
MaskedLValue(const MaskedLValue &) = delete;
constexpr MaskedLValue(MaskedLValue &&) = default;
template<typename T> Vc_ALWAYS_INLINE void operator =(T &&rhs) { std::forward<T>(rhs).scatter(lhs.scatterArguments(), mask); }
};
template<typename _LValue> struct MaskedLValue<bool, _LValue>
{
typedef bool Mask;
typedef _LValue LValue;
const Mask &mask;
LValue &lhs;
constexpr MaskedLValue(const Mask &m, LValue &l) : mask(m), lhs(l) {}
MaskedLValue(const MaskedLValue &) = delete;
constexpr MaskedLValue(MaskedLValue &&) = default;
template<typename T> Vc_ALWAYS_INLINE void operator =(T &&rhs) { if (mask) lhs = std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator +=(T &&rhs) { if (mask) lhs += std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator -=(T &&rhs) { if (mask) lhs -= std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator *=(T &&rhs) { if (mask) lhs *= std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator /=(T &&rhs) { if (mask) lhs /= std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator %=(T &&rhs) { if (mask) lhs %= std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator ^=(T &&rhs) { if (mask) lhs ^= std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator &=(T &&rhs) { if (mask) lhs &= std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator |=(T &&rhs) { if (mask) lhs |= std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator<<=(T &&rhs) { if (mask) lhs <<= std::forward<T>(rhs); }
template<typename T> Vc_ALWAYS_INLINE void operator>>=(T &&rhs) { if (mask) lhs >>= std::forward<T>(rhs); }
Vc_ALWAYS_INLINE void operator++() { if (mask) ++lhs; }
Vc_ALWAYS_INLINE void operator++(int) { if (mask) lhs++; }
Vc_ALWAYS_INLINE void operator--() { if (mask) --lhs; }
Vc_ALWAYS_INLINE void operator--(int) { if (mask) lhs--; }
};
template<typename _Mask> struct WhereMask
{
typedef _Mask Mask;
const Mask &mask;
constexpr WhereMask(const Mask &m) : mask(m) {}
WhereMask(const WhereMask &) = delete;
template <typename T, typename I, typename S>
constexpr Vc_WARN_UNUSED_RESULT
MaskedLValue<Mask, Common::SubscriptOperation<T, I, S, true>>
operator|(Common::SubscriptOperation<T, I, S, true> &&lhs) const
{
static_assert(!std::is_const<T>::value,
"masked scatter to constant memory not possible.");
return {mask, std::move(lhs)};
}
template<typename T> constexpr Vc_WARN_UNUSED_RESULT MaskedLValue<Mask, T> operator|(T &&lhs) const
{
static_assert(std::is_lvalue_reference<T>::value, "Syntax error: Incorrect use of Vc::where. Maybe operator precedence got you by surprise. Examples of correct usage:\n"
"  Vc::where(x < 2) | x += 1;\n"
"  (Vc::where(x < 2) | x)++;\n"
"  Vc::where(x < 2)(x) += 1;\n"
"  Vc::where(x < 2)(x)++;\n"
);
return { mask, lhs };
}
template <class T,
class = decltype(std::declval<T>() = std::declval<const T &>())>
constexpr Vc_WARN_UNUSED_RESULT MaskedLValue<Mask, T> operator()(T &&lhs) const
{
return operator|(std::forward<T>(lhs));
}
};
}
template<typename M> constexpr Vc_WARN_UNUSED_RESULT WhereImpl::WhereMask<M> where(const M &mask)
{
return { mask };
}
template <class M, class V>
constexpr Vc_WARN_UNUSED_RESULT WhereImpl::MaskedLValue<M, V> where(const M &mask,
V &value)
{
return {mask, value};
}
template<typename M> constexpr Vc_WARN_UNUSED_RESULT WhereImpl::WhereMask<M> _if(const M &m)
{
return { m };
}
}
#endif
#ifndef VC_COMMON_TRANSPOSE_H_
#define VC_COMMON_TRANSPOSE_H_ 
#include <tuple>
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template <typename... Inputs> struct TransposeProxy
{
TransposeProxy(const Inputs &... inputs) : in{inputs...} {}
std::tuple<const Inputs &...> in;
};
template <int LhsLength, size_t RhsLength> struct TransposeTag {
};
}
template <typename... Vs> Common::TransposeProxy<Vs...> transpose(Vs... vs)
{
return {vs...};
}
}
#endif
#ifndef VC_SCALAR_OPERATORS_H_
#define VC_SCALAR_OPERATORS_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
#define Vc_OP(op_) \
template <typename T> \
Vc_INTRINSIC Scalar::Mask<T> operator op_(Scalar::Vector<T> a, Scalar::Vector<T> b) \
{ \
return Scalar::Mask<T>(a.data() op_ b.data()); \
}
Vc_ALL_COMPARES(Vc_OP);
#undef Vc_OP
#define Vc_OP(symbol) \
template <typename T> \
Vc_INTRINSIC enable_if<std::is_integral<T>::value, Scalar::Vector<T>> \
operator symbol(Scalar::Vector<T> a, Scalar::Vector<T> b) \
{ \
return a.data() symbol b.data(); \
} \
template <typename T> \
Vc_INTRINSIC enable_if<std::is_floating_point<T>::value, Scalar::Vector<T>> \
operator symbol(Scalar::Vector<T> &lhs, Scalar::Vector<T> rhs) \
{ \
using uinta = \
MayAlias<typename std::conditional<sizeof(T) == sizeof(int), unsigned int, \
unsigned long long>::type>; \
uinta *left = reinterpret_cast<uinta *>(&lhs.data()); \
const uinta *right = reinterpret_cast<const uinta *>(&rhs.data()); \
*left symbol## = *right; \
return lhs; \
}
Vc_ALL_BINARY(Vc_OP);
#undef Vc_OP
template <typename T>
Vc_INTRINSIC Scalar::Vector<T> operator+(Scalar::Vector<T> a, Scalar::Vector<T> b)
{
return a.data() + b.data();
}
template <typename T>
Vc_INTRINSIC Scalar::Vector<T> operator-(Scalar::Vector<T> a, Scalar::Vector<T> b)
{
return a.data() - b.data();
}
template <typename T>
Vc_INTRINSIC Scalar::Vector<T> operator*(Scalar::Vector<T> a, Scalar::Vector<T> b)
{
return a.data() * b.data();
}
template <typename T>
Vc_INTRINSIC Scalar::Vector<T> operator/(Scalar::Vector<T> a, Scalar::Vector<T> b)
{
return a.data() / b.data();
}
template <typename T>
Vc_INTRINSIC Scalar::Vector<T> operator%(Scalar::Vector<T> a, Scalar::Vector<T> b)
{
return a.data() % b.data();
}
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
template <typename T>
Vc_INTRINSIC Vector<T, VectorAbi::Scalar>::Vector(VectorSpecialInitializerZero)
: m_data(0)
{
}
template <typename T>
Vc_INTRINSIC Vector<T, VectorAbi::Scalar>::Vector(VectorSpecialInitializerOne)
: m_data(1)
{
}
template <typename T>
Vc_INTRINSIC Vector<T, VectorAbi::Scalar>::Vector(VectorSpecialInitializerIndexesFromZero)
: m_data(0)
{
}
template <typename T>
template <typename U, typename Flags>
Vc_INTRINSIC typename Vector<T, VectorAbi::Scalar>::
#ifndef Vc_MSVC
template
#endif
load_concept<U, Flags>::type Vector<T, VectorAbi::Scalar>::load(const U *mem, Flags)
{
m_data = mem[0];
}
template <typename T>
template <typename U, typename Flags, typename>
Vc_INTRINSIC void Vector<T, VectorAbi::Scalar>::store(U *mem, Flags) const
{
mem[0] = m_data;
}
template <typename T>
template <typename U, typename Flags, typename>
Vc_INTRINSIC void Vector<T, VectorAbi::Scalar>::store(U *mem, Mask mask, Flags) const
{
if (mask.data())
mem[0] = m_data;
}
template <typename T>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void Vector<T, VectorAbi::Scalar>::gatherImplementation(
const MT *mem, const IT &indexes)
{
m_data = mem[indexes[0]];
}
template <typename T>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void Vector<T, VectorAbi::Scalar>::gatherImplementation(
const MT *mem, const IT &indexes, MaskArgument mask)
{
if (mask.data()) {
m_data = mem[indexes[0]];
}
}
template <typename T>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void Vector<T, VectorAbi::Scalar>::scatterImplementation(MT *mem,
IT &&indexes)
const
{
mem[indexes[0]] = m_data;
}
template <typename T>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void Vector<T, VectorAbi::Scalar>::scatterImplementation(
MT *mem, IT &&indexes, MaskArgument mask) const
{
if (mask.data()) {
mem[indexes[0]] = m_data;
}
}
Vc_INTRINSIC Vc_CONST Scalar::float_v exponent(Scalar::float_v x)
{
Vc_ASSERT(x.data() >= 0.f);
union { float f; int i; } value;
value.f = x.data();
return Scalar::float_v(static_cast<float>((value.i >> 23) - 0x7f));
}
Vc_INTRINSIC Vc_CONST Scalar::double_v Vc_VDECL exponent(Scalar::double_v x)
{
Vc_ASSERT(x.data() >= 0.);
union { double f; long long i; } value;
value.f = x.data();
return Scalar::double_v(static_cast<double>((value.i >> 52) - 0x3ff));
}
static Vc_ALWAYS_INLINE void _doRandomStep(Scalar::uint_v &state0, Scalar::uint_v &state1)
{
using Scalar::uint_v;
state0.load(&Common::RandomState[0]);
state1.load(&Common::RandomState[uint_v::Size]);
Detail::operator+(Detail::operator*(state1, uint_v(0xdeece66du)),
uint_v(11))
.store(&Common::RandomState[uint_v::Size]);
uint_v(Detail::operator+(Detail::operator*(state0, uint_v(0xdeece66du)), uint_v(11))
.data() ^
(state1.data() >> 16))
.store(&Common::RandomState[0]);
}
template<typename T> Vc_INTRINSIC Vector<T, VectorAbi::Scalar> Vector<T, VectorAbi::Scalar>::Random()
{
Scalar::uint_v state0, state1;
_doRandomStep(state0, state1);
return Vector<T, VectorAbi::Scalar>(static_cast<EntryType>(state0.data()));
}
template<> Vc_INTRINSIC Scalar::float_v Scalar::float_v::Random()
{
Scalar::uint_v state0, state1;
_doRandomStep(state0, state1);
union { unsigned int i; float f; } x;
x.i = (state0.data() & 0x0fffffffu) | 0x3f800000u;
return Scalar::float_v(x.f - 1.f);
}
template<> Vc_INTRINSIC Scalar::double_v Scalar::double_v::Random()
{
typedef unsigned long long uint64 Vc_MAY_ALIAS;
uint64 state0 = *reinterpret_cast<const uint64 *>(&Common::RandomState[8]);
state0 = (state0 * 0x5deece66dull + 11) & 0x000fffffffffffffull;
*reinterpret_cast<uint64 *>(&Common::RandomState[8]) = state0;
union { unsigned long long i; double f; } x;
x.i = state0 | 0x3ff0000000000000ull;
return Scalar::double_v(x.f - 1.);
}
Vc_INTRINSIC Vc_CONST Scalar::float_m isnegative(Scalar::float_v x)
{
static_assert(sizeof(float) == sizeof(unsigned int),
"This code assumes float and unsigned int have the same number of "
"Bytes. Please file a bug report if this is a problem.");
union { float f; unsigned int i; } u;
u.f = x.data();
return Scalar::float_m(0u != (u.i & 0x80000000u));
}
Vc_INTRINSIC Vc_CONST Scalar::double_m Vc_VDECL isnegative(Scalar::double_v x)
{
static_assert(sizeof(double) == sizeof(unsigned long long),
"This code assumes double and unsigned long long have the same number "
"of Bytes. Please file a bug report if this is a problem.");
union { double d; unsigned long long l; } u;
u.d = x.data();
return Scalar::double_m(0ull != (u.l & 0x8000000000000000ull));
}
template<typename T> Vc_INTRINSIC void Vector<T, VectorAbi::Scalar>::setQnan()
{
union { float f; unsigned int i; } u;
u.i = 0xffffffffu;
m_data = u.f;
}
template<> Vc_INTRINSIC void Scalar::double_v::setQnan()
{
union { double d; unsigned long long l; } u;
u.l = 0xffffffffffffffffull;
m_data = u.d;
}
template<typename T> Vc_INTRINSIC void Vector<T, VectorAbi::Scalar>::setQnan(Mask m)
{
if (m.data()) {
setQnan();
}
}
template<> Vc_INTRINSIC void Scalar::double_v::setQnan(Scalar::double_v::Mask m)
{
if (m.data()) {
setQnan();
}
}
namespace Common
{
Vc_ALWAYS_INLINE void transpose_impl(TransposeTag<1, 1>, Scalar::float_v *Vc_RESTRICT r[],
const TransposeProxy<Scalar::float_v> &proxy)
{
*r[0] = std::get<0>(proxy.in).data();
}
}
}
#ifndef VC_SCALAR_SIMD_CAST_H_
#define VC_SCALAR_SIMD_CAST_H_ 
#ifndef VC_COMMON_SIMD_CAST_H_
#define VC_COMMON_SIMD_CAST_H_ 
#include <type_traits>
template <class> void simd_cast();
namespace Vc_VERSIONED_NAMESPACE
{
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(From &&x, enable_if<std::is_same<To, Traits::decay<From>>::value> = nullarg)
{
return std::forward<From>(x);
}
template <typename To> Vc_INTRINSIC Vc_CONST To simd_cast() { return To(); }
}
#endif
#ifndef VC_SCALAR_TYPE_TRAITS_H_
#define VC_SCALAR_TYPE_TRAITS_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Scalar
{
namespace Traits
{
template <typename T> struct is_vector : public std::false_type {};
template <typename T> struct is_vector<Vector<T>> : public std::true_type {};
template <typename T> struct is_mask : public std::false_type {};
template <typename T> struct is_mask<Mask<T>> : public std::true_type {};
}
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(Scalar::Vector<From> x, enable_if<Scalar::is_vector<To>::value> = nullarg)
{
return static_cast<To>(x.data());
}
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(Scalar::Mask<From> x, enable_if<Scalar::is_mask<To>::value> = nullarg)
{
return static_cast<To>(x.data());
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(
T &&x,
enable_if<Traits::is_simd_vector<T>::value && Scalar::is_vector<Return>::value> = nullarg)
{
return Return(x[offset]);
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<offset == 0 && Traits::is_simd_vector<Return>::value &&
!Scalar::is_vector<Return>::value,
Return>
simd_cast(Scalar::Vector<T> x)
{
Return r{};
r[0] = static_cast<typename Return::EntryType>(x.data());
return r;
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(
T &&x,
enable_if<Traits::is_simd_mask<T>::value && Scalar::is_mask<Return>::value> = nullarg)
{
return Return(bool(x[offset]));
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<
offset == 0 && Traits::is_simd_mask<Return>::value && !Scalar::is_mask<Return>::value,
Return>
simd_cast(Scalar::Mask<T> x)
{
Return r(false);
r[0] = x[0];
return r;
}
}
#endif
#endif
#if defined(Vc_IMPL_SSE)
#ifndef VC_SSE_VECTOR_H_
#define VC_SSE_VECTOR_H_ 
#ifndef VC_SSE_INTRINSICS_H_
#define VC_SSE_INTRINSICS_H_ 
#ifdef Vc_MSVC
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
#ifndef VC_COMMON_STORAGE_H_
#define VC_COMMON_STORAGE_H_ 
#ifndef VC_COMMON_ALIASINGENTRYHELPER_H_
#define VC_COMMON_ALIASINGENTRYHELPER_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template<class StorageType> class AliasingEntryHelper
{
private:
typedef typename StorageType::EntryType T;
#ifdef Vc_ICC
StorageType *const m_storage;
const int m_index;
public:
Vc_ALWAYS_INLINE AliasingEntryHelper(StorageType *d, int index) : m_storage(d), m_index(index) {}
Vc_ALWAYS_INLINE AliasingEntryHelper(const AliasingEntryHelper &) = default;
Vc_ALWAYS_INLINE AliasingEntryHelper(AliasingEntryHelper &&) = default;
Vc_ALWAYS_INLINE AliasingEntryHelper &operator=(const AliasingEntryHelper &rhs) {
m_storage->assign(m_index, rhs);
return *this;
}
Vc_ALWAYS_INLINE AliasingEntryHelper &operator =(T x) { m_storage->assign(m_index, x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator +=(T x) { m_storage->assign(m_index, m_storage->m(m_index) + x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator -=(T x) { m_storage->assign(m_index, m_storage->m(m_index) - x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator /=(T x) { m_storage->assign(m_index, m_storage->m(m_index) / x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator *=(T x) { m_storage->assign(m_index, m_storage->m(m_index) * x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator |=(T x) { m_storage->assign(m_index, m_storage->m(m_index) | x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator &=(T x) { m_storage->assign(m_index, m_storage->m(m_index) & x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator ^=(T x) { m_storage->assign(m_index, m_storage->m(m_index) ^ x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator %=(T x) { m_storage->assign(m_index, m_storage->m(m_index) % x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator<<=(T x) { m_storage->assign(m_index, m_storage->m(m_index)<< x); return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator>>=(T x) { m_storage->assign(m_index, m_storage->m(m_index)>> x); return *this; }
#define m_data m_storage->read(m_index)
#else
typedef T A Vc_MAY_ALIAS;
A &m_data;
public:
template<typename T2>
Vc_ALWAYS_INLINE AliasingEntryHelper(T2 &d) : m_data(reinterpret_cast<A &>(d)) {}
Vc_ALWAYS_INLINE AliasingEntryHelper(A &d) : m_data(d) {}
Vc_ALWAYS_INLINE AliasingEntryHelper &operator=(const AliasingEntryHelper &rhs) {
m_data = rhs.m_data;
return *this;
}
Vc_ALWAYS_INLINE AliasingEntryHelper &operator =(T x) { m_data = x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator+=(T x) { m_data += x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator-=(T x) { m_data -= x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator/=(T x) { m_data /= x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator*=(T x) { m_data *= x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator|=(T x) { m_data |= x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator&=(T x) { m_data &= x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator^=(T x) { m_data ^= x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator%=(T x) { m_data %= x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator<<=(T x) { m_data <<= x; return *this; }
Vc_ALWAYS_INLINE AliasingEntryHelper &operator>>=(T x) { m_data >>= x; return *this; }
#endif
Vc_ALWAYS_INLINE Vc_PURE operator const T() const { return m_data; }
Vc_ALWAYS_INLINE Vc_PURE bool operator==(T x) const { return static_cast<T>(m_data) == x; }
Vc_ALWAYS_INLINE Vc_PURE bool operator!=(T x) const { return static_cast<T>(m_data) != x; }
Vc_ALWAYS_INLINE Vc_PURE bool operator<=(T x) const { return static_cast<T>(m_data) <= x; }
Vc_ALWAYS_INLINE Vc_PURE bool operator>=(T x) const { return static_cast<T>(m_data) >= x; }
Vc_ALWAYS_INLINE Vc_PURE bool operator< (T x) const { return static_cast<T>(m_data) < x; }
Vc_ALWAYS_INLINE Vc_PURE bool operator> (T x) const { return static_cast<T>(m_data) > x; }
Vc_ALWAYS_INLINE Vc_PURE T operator-() const { return -static_cast<T>(m_data); }
Vc_ALWAYS_INLINE Vc_PURE T operator~() const { return ~static_cast<T>(m_data); }
Vc_ALWAYS_INLINE Vc_PURE T operator+(T x) const { return static_cast<T>(m_data) + x; }
Vc_ALWAYS_INLINE Vc_PURE T operator-(T x) const { return static_cast<T>(m_data) - x; }
Vc_ALWAYS_INLINE Vc_PURE T operator/(T x) const { return static_cast<T>(m_data) / x; }
Vc_ALWAYS_INLINE Vc_PURE T operator*(T x) const { return static_cast<T>(m_data) * x; }
Vc_ALWAYS_INLINE Vc_PURE T operator|(T x) const { return static_cast<T>(m_data) | x; }
Vc_ALWAYS_INLINE Vc_PURE T operator&(T x) const { return static_cast<T>(m_data) & x; }
Vc_ALWAYS_INLINE Vc_PURE T operator^(T x) const { return static_cast<T>(m_data) ^ x; }
Vc_ALWAYS_INLINE Vc_PURE T operator%(T x) const { return static_cast<T>(m_data) % x; }
#ifdef m_data
#undef m_data
#endif
};
}
}
#endif
#ifndef VC_COMMON_MASKENTRY_H_
#define VC_COMMON_MASKENTRY_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
namespace
{
template<size_t Bytes> struct MaskBoolStorage;
template<> struct MaskBoolStorage<1> { typedef std::int8_t type; };
template<> struct MaskBoolStorage<2> { typedef std::int16_t type; };
template<> struct MaskBoolStorage<4> { typedef std::int32_t type; };
template<> struct MaskBoolStorage<8> { typedef std::int64_t type; };
}
template<size_t Bytes> class MaskBool
{
typedef typename MaskBoolStorage<Bytes>::type storage_type Vc_MAY_ALIAS;
storage_type data;
public:
constexpr MaskBool(bool x) noexcept : data(x ? -1 : 0) {}
Vc_ALWAYS_INLINE MaskBool &operator=(bool x) noexcept { data = x ? -1 : 0; return *this; }
template <typename T, typename = enable_if<(!std::is_same<T, bool>::value &&
std::is_fundamental<T>::value)>>
Vc_ALWAYS_INLINE MaskBool &operator=(T x) noexcept
{
data = reinterpret_cast<const storage_type &>(x);
return *this;
}
Vc_ALWAYS_INLINE MaskBool(const MaskBool &) noexcept = default;
Vc_ALWAYS_INLINE MaskBool &operator=(const MaskBool &) noexcept = default;
template <typename T, typename = enable_if<(std::is_same<T, bool>::value ||
(std::is_fundamental<T>::value &&
sizeof(storage_type) == sizeof(T)))>>
constexpr operator T() const noexcept
{
return std::is_same<T, bool>::value ? T((data & 1) != 0) : aliasing_cast<T>(data);
}
} Vc_MAY_ALIAS;
template <typename A,
typename B,
typename std::enable_if<
std::is_convertible<A, bool>::value &&std::is_convertible<B, bool>::value,
int>::type = 0>
constexpr bool operator==(A &&a, B &&b)
{
return static_cast<bool>(a) == static_cast<bool>(b);
}
template <typename A,
typename B,
typename std::enable_if<
std::is_convertible<A, bool>::value &&std::is_convertible<B, bool>::value,
int>::type = 0>
constexpr bool operator!=(A &&a, B &&b)
{
return static_cast<bool>(a) != static_cast<bool>(b);
}
static_assert(true == MaskBool<4>(true), "true == MaskBool<4>(true)");
static_assert(true != MaskBool<4>(false), "true != MaskBool<4>(false)");
}
}
#endif
#ifdef Vc_IMPL_AVX
#ifndef VC_AVX_INTRINSICS_H_
#define VC_AVX_INTRINSICS_H_ 
extern "C" {
#include <immintrin.h>
#if (defined(Vc_IMPL_XOP) || defined(Vc_IMPL_FMA4)) && !defined(Vc_MSVC)
#include <x86intrin.h>
#endif
}
#ifndef VC_COMMON_FIX_CLANG_EMMINTRIN_H_
#define VC_COMMON_FIX_CLANG_EMMINTRIN_H_ 
#if (defined Vc_CLANG && Vc_CLANG < 0x30700) || (defined Vc_APPLECLANG && Vc_APPLECLANG < 0x70000)
#ifdef _mm_slli_si128
#undef _mm_slli_si128
#define _mm_slli_si128(a,count) __extension__ ({ \
(__m128i)__builtin_ia32_pslldqi128((__m128i)(a), (count)*8); })
#endif
#ifdef _mm_srli_si128
#undef _mm_srli_si128
#define _mm_srli_si128(a,count) __extension__ ({ \
(__m128i)__builtin_ia32_psrldqi128((__m128i)(a), (count)*8); })
#endif
#ifdef _mm_shuffle_epi32
#undef _mm_shuffle_epi32
#define _mm_shuffle_epi32(a,imm) __extension__ ({ \
(__m128i)__builtin_shufflevector((__v4si)(__m128i)(a), (__v4si) _mm_set1_epi32(0), \
(imm) & 0x3, ((imm) & 0xc) >> 2, \
((imm) & 0x30) >> 4, ((imm) & 0xc0) >> 6); })
#endif
#ifdef _mm_shufflelo_epi16
#undef _mm_shufflelo_epi16
#define _mm_shufflelo_epi16(a,imm) __extension__ ({ \
(__m128i)__builtin_shufflevector((__v8hi)(__m128i)(a), (__v8hi) _mm_set1_epi16(0), \
(imm) & 0x3, ((imm) & 0xc) >> 2, \
((imm) & 0x30) >> 4, ((imm) & 0xc0) >> 6, \
4, 5, 6, 7); })
#endif
#ifdef _mm_shufflehi_epi16
#undef _mm_shufflehi_epi16
#define _mm_shufflehi_epi16(a,imm) __extension__ ({ \
(__m128i)__builtin_shufflevector((__v8hi)(__m128i)(a), (__v8hi) _mm_set1_epi16(0), \
0, 1, 2, 3, \
4 + (((imm) & 0x03) >> 0), \
4 + (((imm) & 0x0c) >> 2), \
4 + (((imm) & 0x30) >> 4), \
4 + (((imm) & 0xc0) >> 6)); })
#endif
#ifdef _mm_shuffle_pd
#undef _mm_shuffle_pd
#define _mm_shuffle_pd(a,b,i) __extension__ ({ \
__builtin_shufflevector((__m128d)(a), (__m128d)(b), (i) & 1, (((i) & 2) >> 1) + 2); })
#endif
#endif
#endif
#ifndef VC_AVX_CONST_DATA_H_
#define VC_AVX_CONST_DATA_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace AVX
{
alignas(64) extern const unsigned int _IndexesFromZero32[ 8];
alignas(16) extern const unsigned short _IndexesFromZero16[16];
alignas(16) extern const unsigned char _IndexesFromZero8 [32];
struct alignas(64) c_general
{
static const float oneFloat;
static const unsigned int absMaskFloat[2];
static const unsigned int signMaskFloat[2];
static const unsigned int highMaskFloat;
static const unsigned short minShort[2];
static const unsigned short one16[2];
static const float _2power31;
static const double oneDouble;
static const unsigned long long frexpMask;
static const unsigned long long highMaskDouble;
};
template<typename T> struct c_trig
{
alignas(64) static const T data[];
};
#ifndef Vc_MSVC
template <> alignas(64) const float c_trig<float>::data[];
template <> alignas(64) const double c_trig<double>::data[];
#endif
template<typename T> struct c_log
{
typedef float floatAlias Vc_MAY_ALIAS;
static Vc_ALWAYS_INLINE float d(int i) { return *reinterpret_cast<const floatAlias *>(&data[i]); }
alignas(64) static const unsigned int data[21];
};
#ifndef Vc_MSVC
template<> alignas(64) const unsigned int c_log<float>::data[21];
#endif
template<> struct c_log<double>
{
enum VectorSize { Size = 16 / sizeof(double) };
typedef double doubleAlias Vc_MAY_ALIAS;
static Vc_ALWAYS_INLINE double d(int i) { return *reinterpret_cast<const doubleAlias *>(&data[i]); }
alignas(64) static const unsigned long long data[21];
};
}
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace AVX2
{
using AVX::_IndexesFromZero8;
using AVX::_IndexesFromZero16;
using AVX::_IndexesFromZero32;
using AVX::c_general;
using AVX::c_trig;
using AVX::c_log;
}
}
#endif
#include <cstdlib>
#if (defined Vc_CLANG && Vc_CLANG >= 0x30900)
#ifdef _mm256_permute2f128_si256
#undef _mm256_permute2f128_si256
#define _mm256_permute2f128_si256(V1,V2,M) __extension__ ({ \
(__m256i)__builtin_ia32_vperm2f128_si256((__v8si)(__m256i)(V1), \
(__v8si)(__m256i)(V2), (char)(M)); })
#endif
#ifdef _mm256_permute2f128_ps
#undef _mm256_permute2f128_ps
#define _mm256_permute2f128_ps(V1,V2,M) __extension__ ({ \
(__m256)__builtin_ia32_vperm2f128_ps256((__v8sf)(__m256)(V1), \
(__v8sf)(__m256)(V2), (char)(M)); })
#endif
#ifdef _mm256_permute2x128_si256
#undef _mm256_permute2x128_si256
#define _mm256_permute2x128_si256(V1,V2,M) __extension__ ({ \
(__m256i)__builtin_ia32_permti256((__m256i)(V1), (__m256i)(V2), (char)(M)); })
#endif
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace AvxIntrinsics
{
using AVX::c_general;
using AVX::_IndexesFromZero32;
using AVX::_IndexesFromZero16;
using AVX::_IndexesFromZero8;
typedef __m128 m128 ;
typedef __m128d m128d;
typedef __m128i m128i;
typedef __m256 m256 ;
typedef __m256d m256d;
typedef __m256i m256i;
typedef const m128 param128 ;
typedef const m128d param128d;
typedef const m128i param128i;
typedef const m256 param256 ;
typedef const m256d param256d;
typedef const m256i param256i;
#ifdef Vc_GCC
static Vc_INTRINSIC Vc_CONST m256d _mm256_mul_pd(m256d a, m256d b) { return static_cast<m256d>(static_cast<__v4df>(a) * static_cast<__v4df>(b)); }
static Vc_INTRINSIC Vc_CONST m256d _mm256_add_pd(m256d a, m256d b) { return static_cast<m256d>(static_cast<__v4df>(a) + static_cast<__v4df>(b)); }
static Vc_INTRINSIC Vc_CONST m256d _mm256_sub_pd(m256d a, m256d b) { return static_cast<m256d>(static_cast<__v4df>(a) - static_cast<__v4df>(b)); }
static Vc_INTRINSIC Vc_CONST m256 _mm256_mul_ps(m256 a, m256 b) { return static_cast<m256>(static_cast<__v8sf>(a) * static_cast<__v8sf>(b)); }
static Vc_INTRINSIC Vc_CONST m256 _mm256_add_ps(m256 a, m256 b) { return static_cast<m256>(static_cast<__v8sf>(a) + static_cast<__v8sf>(b)); }
static Vc_INTRINSIC Vc_CONST m256 _mm256_sub_ps(m256 a, m256 b) { return static_cast<m256>(static_cast<__v8sf>(a) - static_cast<__v8sf>(b)); }
#endif
static Vc_INTRINSIC m256 Vc_CONST set1_ps (float a) { return _mm256_set1_ps (a); }
static Vc_INTRINSIC m256d Vc_CONST set1_pd (double a) { return _mm256_set1_pd (a); }
static Vc_INTRINSIC m256i Vc_CONST set1_epi32(int a) { return _mm256_set1_epi32(a); }
static Vc_INTRINSIC Vc_CONST m128i _mm_setallone_si128() { return _mm_load_si128(reinterpret_cast<const __m128i *>(Common::AllBitsSet)); }
static Vc_INTRINSIC Vc_CONST m128 _mm_setallone_ps() { return _mm_load_ps(reinterpret_cast<const float *>(Common::AllBitsSet)); }
static Vc_INTRINSIC Vc_CONST m128d _mm_setallone_pd() { return _mm_load_pd(reinterpret_cast<const double *>(Common::AllBitsSet)); }
static Vc_INTRINSIC Vc_CONST m256i setallone_si256() { return _mm256_castps_si256(_mm256_load_ps(reinterpret_cast<const float *>(Common::AllBitsSet))); }
static Vc_INTRINSIC Vc_CONST m256d setallone_pd() { return _mm256_load_pd(reinterpret_cast<const double *>(Common::AllBitsSet)); }
static Vc_INTRINSIC Vc_CONST m256 setallone_ps() { return _mm256_load_ps(reinterpret_cast<const float *>(Common::AllBitsSet)); }
static Vc_INTRINSIC m128i Vc_CONST _mm_setone_epi8 () { return _mm_set1_epi8(1); }
static Vc_INTRINSIC m128i Vc_CONST _mm_setone_epu8 () { return _mm_setone_epi8(); }
static Vc_INTRINSIC m128i Vc_CONST _mm_setone_epi16() { return _mm_castps_si128(_mm_broadcast_ss(reinterpret_cast<const float *>(c_general::one16))); }
static Vc_INTRINSIC m128i Vc_CONST _mm_setone_epu16() { return _mm_setone_epi16(); }
static Vc_INTRINSIC m128i Vc_CONST _mm_setone_epi32() { return _mm_castps_si128(_mm_broadcast_ss(reinterpret_cast<const float *>(&_IndexesFromZero32[1]))); }
static Vc_INTRINSIC m128i Vc_CONST _mm_setone_epu32() { return _mm_setone_epi32(); }
static Vc_INTRINSIC m256i Vc_CONST setone_epi8 () { return _mm256_set1_epi8(1); }
static Vc_INTRINSIC m256i Vc_CONST setone_epu8 () { return setone_epi8(); }
static Vc_INTRINSIC m256i Vc_CONST setone_epi16() { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(c_general::one16))); }
static Vc_INTRINSIC m256i Vc_CONST setone_epu16() { return setone_epi16(); }
static Vc_INTRINSIC m256i Vc_CONST setone_epi32() { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(&_IndexesFromZero32[1]))); }
static Vc_INTRINSIC m256i Vc_CONST setone_epu32() { return setone_epi32(); }
static Vc_INTRINSIC m256 Vc_CONST setone_ps() { return _mm256_broadcast_ss(&c_general::oneFloat); }
static Vc_INTRINSIC m256d Vc_CONST setone_pd() { return _mm256_broadcast_sd(&c_general::oneDouble); }
static Vc_INTRINSIC m256d Vc_CONST setabsmask_pd() { return _mm256_broadcast_sd(reinterpret_cast<const double *>(&c_general::absMaskFloat[0])); }
static Vc_INTRINSIC m256 Vc_CONST setabsmask_ps() { return _mm256_broadcast_ss(reinterpret_cast<const float *>(&c_general::absMaskFloat[1])); }
static Vc_INTRINSIC m256d Vc_CONST setsignmask_pd(){ return _mm256_broadcast_sd(reinterpret_cast<const double *>(&c_general::signMaskFloat[0])); }
static Vc_INTRINSIC m256 Vc_CONST setsignmask_ps(){ return _mm256_broadcast_ss(reinterpret_cast<const float *>(&c_general::signMaskFloat[1])); }
static Vc_INTRINSIC m256 Vc_CONST set2power31_ps() { return _mm256_broadcast_ss(&c_general::_2power31); }
static Vc_INTRINSIC m128 Vc_CONST _mm_set2power31_ps() { return _mm_broadcast_ss(&c_general::_2power31); }
static Vc_INTRINSIC m256i Vc_CONST set2power31_epu32() { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(&c_general::signMaskFloat[1]))); }
static Vc_INTRINSIC m128i Vc_CONST _mm_set2power31_epu32() { return _mm_castps_si128(_mm_broadcast_ss(reinterpret_cast<const float *>(&c_general::signMaskFloat[1]))); }
static Vc_INTRINSIC m256i Vc_CONST setmin_epi8 () { return _mm256_set1_epi8(-0x80); }
static Vc_INTRINSIC m128i Vc_CONST _mm_setmin_epi16() { return _mm_castps_si128(_mm_broadcast_ss(reinterpret_cast<const float *>(c_general::minShort))); }
static Vc_INTRINSIC m128i Vc_CONST _mm_setmin_epi32() { return _mm_castps_si128(_mm_broadcast_ss(reinterpret_cast<const float *>(&c_general::signMaskFloat[1]))); }
static Vc_INTRINSIC m256i Vc_CONST setmin_epi16() { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(c_general::minShort))); }
static Vc_INTRINSIC m256i Vc_CONST setmin_epi32() { return _mm256_castps_si256(_mm256_broadcast_ss(reinterpret_cast<const float *>(&c_general::signMaskFloat[1]))); }
template <int i>
static Vc_INTRINSIC Vc_CONST unsigned char extract_epu8(__m128i x)
{
return _mm_extract_epi8(x, i);
}
template <int i>
static Vc_INTRINSIC Vc_CONST unsigned short extract_epu16(__m128i x)
{
return _mm_extract_epi16(x, i);
}
template <int i>
static Vc_INTRINSIC Vc_CONST unsigned int extract_epu32(__m128i x)
{
return _mm_extract_epi32(x, i);
}
template <int offset> Vc_INTRINSIC __m256 insert128(__m256 a, __m128 b) { return _mm256_insertf128_ps(a, b, offset); }
template <int offset> Vc_INTRINSIC __m256d insert128(__m256d a, __m128d b) { return _mm256_insertf128_pd(a, b, offset); }
template <int offset> Vc_INTRINSIC __m256i insert128(__m256i a, __m128i b) {
#ifdef Vc_IMPL_AVX2
return _mm256_inserti128_si256(a, b, offset);
#else
return _mm256_insertf128_si256(a, b, offset);
#endif
}
template <int offset> Vc_INTRINSIC __m128 extract128(__m256 a) { return _mm256_extractf128_ps(a, offset); }
template <int offset> Vc_INTRINSIC __m128d extract128(__m256d a) { return _mm256_extractf128_pd(a, offset); }
template <int offset> Vc_INTRINSIC __m128i extract128(__m256i a) {
#ifdef Vc_IMPL_AVX2
return _mm256_extracti128_si256(a, offset);
#else
return _mm256_extractf128_si256(a, offset);
#endif
}
static Vc_INTRINSIC m256d Vc_CONST cmpeq_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_EQ_OQ); }
static Vc_INTRINSIC m256d Vc_CONST cmpneq_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_NEQ_UQ); }
static Vc_INTRINSIC m256d Vc_CONST cmplt_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_LT_OS); }
static Vc_INTRINSIC m256d Vc_CONST cmpnlt_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_NLT_US); }
static Vc_INTRINSIC m256d Vc_CONST cmpge_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_NLT_US); }
static Vc_INTRINSIC m256d Vc_CONST cmple_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_LE_OS); }
static Vc_INTRINSIC m256d Vc_CONST cmpnle_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_NLE_US); }
static Vc_INTRINSIC m256d Vc_CONST cmpgt_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_NLE_US); }
static Vc_INTRINSIC m256d Vc_CONST cmpord_pd (__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_ORD_Q); }
static Vc_INTRINSIC m256d Vc_CONST cmpunord_pd(__m256d a, __m256d b) { return _mm256_cmp_pd(a, b, _CMP_UNORD_Q); }
static Vc_INTRINSIC m256 Vc_CONST cmpeq_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_EQ_OQ); }
static Vc_INTRINSIC m256 Vc_CONST cmpneq_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_NEQ_UQ); }
static Vc_INTRINSIC m256 Vc_CONST cmplt_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_LT_OS); }
static Vc_INTRINSIC m256 Vc_CONST cmpnlt_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_NLT_US); }
static Vc_INTRINSIC m256 Vc_CONST cmpge_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_NLT_US); }
static Vc_INTRINSIC m256 Vc_CONST cmple_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_LE_OS); }
static Vc_INTRINSIC m256 Vc_CONST cmpnle_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_NLE_US); }
static Vc_INTRINSIC m256 Vc_CONST cmpgt_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_NLE_US); }
static Vc_INTRINSIC m256 Vc_CONST cmpord_ps (__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_ORD_Q); }
static Vc_INTRINSIC m256 Vc_CONST cmpunord_ps(__m256 a, __m256 b) { return _mm256_cmp_ps(a, b, _CMP_UNORD_Q); }
#if defined(Vc_IMPL_XOP)
static Vc_INTRINSIC m128i cmplt_epu16(__m128i a, __m128i b) {
return _mm_comlt_epu16(a, b);
}
static Vc_INTRINSIC m128i cmpgt_epu16(__m128i a, __m128i b) {
return _mm_comgt_epu16(a, b);
}
#else
static Vc_INTRINSIC m128i cmplt_epu16(__m128i a, __m128i b) {
return _mm_cmplt_epi16(_mm_xor_si128(a, _mm_setmin_epi16()), _mm_xor_si128(b, _mm_setmin_epi16()));
}
static Vc_INTRINSIC m128i cmpgt_epu16(__m128i a, __m128i b) {
return _mm_cmpgt_epi16(_mm_xor_si128(a, _mm_setmin_epi16()), _mm_xor_si128(b, _mm_setmin_epi16()));
}
#endif
#ifdef Vc_IMPL_AVX2
template <int shift> Vc_INTRINSIC Vc_CONST m256i alignr(__m256i s1, __m256i s2)
{
return _mm256_alignr_epi8(s1, s2, shift);
}
#else
template <int shift> Vc_INTRINSIC Vc_CONST m256i alignr(__m256i s1, __m256i s2)
{
return insert128<1>(
_mm256_castsi128_si256(_mm_alignr_epi8(_mm256_castsi256_si128(s1),
_mm256_castsi256_si128(s2), shift)),
_mm_alignr_epi8(extract128<1>(s1), extract128<1>(s2), shift));
}
#endif
#ifdef Vc_IMPL_AVX2
#define Vc_AVX_TO_SSE_2_NEW(name) \
Vc_INTRINSIC Vc_CONST m256i name(__m256i a0, __m256i b0) \
{ \
return _mm256_##name(a0, b0); \
}
#define Vc_AVX_TO_SSE_256_128(name) \
Vc_INTRINSIC Vc_CONST m256i name(__m256i a0, __m128i b0) \
{ \
return _mm256_##name(a0, b0); \
}
#define Vc_AVX_TO_SSE_1i(name) \
template <int i> Vc_INTRINSIC Vc_CONST m256i name(__m256i a0) \
{ \
return _mm256_##name(a0, i); \
}
#define Vc_AVX_TO_SSE_1(name) \
Vc_INTRINSIC Vc_CONST __m256i name(__m256i a0) { return _mm256_##name(a0); }
#define Vc_AVX_TO_SSE_1_128(name,shift__) \
Vc_INTRINSIC Vc_CONST __m256i name(__m128i a0) { return _mm256_##name(a0); }
#else
#define Vc_AVX_TO_SSE_1(name) \
Vc_INTRINSIC Vc_CONST __m256i name(__m256i a0) \
{ \
__m128i a1 = extract128<1>(a0); \
__m128i r0 = _mm_##name(_mm256_castsi256_si128(a0)); \
__m128i r1 = _mm_##name(a1); \
return insert128<1>(_mm256_castsi128_si256(r0), r1); \
}
#define Vc_AVX_TO_SSE_1_128(name,shift__) \
Vc_INTRINSIC Vc_CONST __m256i name(__m128i a0) \
{ \
__m128i r0 = _mm_##name(a0); \
__m128i r1 = _mm_##name(_mm_srli_si128(a0, shift__)); \
return insert128<1>(_mm256_castsi128_si256(r0), r1); \
}
#define Vc_AVX_TO_SSE_2_NEW(name) \
Vc_INTRINSIC Vc_CONST m256i name(__m256i a0, __m256i b0) \
{ \
m128i a1 = extract128<1>(a0); \
m128i b1 = extract128<1>(b0); \
m128i r0 = _mm_##name(_mm256_castsi256_si128(a0), _mm256_castsi256_si128(b0)); \
m128i r1 = _mm_##name(a1, b1); \
return insert128<1>(_mm256_castsi128_si256(r0), r1); \
}
#define Vc_AVX_TO_SSE_256_128(name) \
Vc_INTRINSIC Vc_CONST m256i name(__m256i a0, __m128i b0) \
{ \
m128i a1 = extract128<1>(a0); \
m128i r0 = _mm_##name(_mm256_castsi256_si128(a0), b0); \
m128i r1 = _mm_##name(a1, b0); \
return insert128<1>(_mm256_castsi128_si256(r0), r1); \
}
#define Vc_AVX_TO_SSE_1i(name) \
template <int i> Vc_INTRINSIC Vc_CONST m256i name(__m256i a0) \
{ \
m128i a1 = extract128<1>(a0); \
m128i r0 = _mm_##name(_mm256_castsi256_si128(a0), i); \
m128i r1 = _mm_##name(a1, i); \
return insert128<1>(_mm256_castsi128_si256(r0), r1); \
}
#endif
Vc_INTRINSIC Vc_CONST __m128i sll_epi16(__m128i a, __m128i b) { return _mm_sll_epi16(a, b); }
Vc_INTRINSIC Vc_CONST __m128i sll_epi32(__m128i a, __m128i b) { return _mm_sll_epi32(a, b); }
Vc_INTRINSIC Vc_CONST __m128i sll_epi64(__m128i a, __m128i b) { return _mm_sll_epi64(a, b); }
Vc_INTRINSIC Vc_CONST __m128i srl_epi16(__m128i a, __m128i b) { return _mm_srl_epi16(a, b); }
Vc_INTRINSIC Vc_CONST __m128i srl_epi32(__m128i a, __m128i b) { return _mm_srl_epi32(a, b); }
Vc_INTRINSIC Vc_CONST __m128i srl_epi64(__m128i a, __m128i b) { return _mm_srl_epi64(a, b); }
Vc_INTRINSIC Vc_CONST __m128i sra_epi16(__m128i a, __m128i b) { return _mm_sra_epi16(a, b); }
Vc_INTRINSIC Vc_CONST __m128i sra_epi32(__m128i a, __m128i b) { return _mm_sra_epi32(a, b); }
Vc_AVX_TO_SSE_1i(slli_epi16)
Vc_AVX_TO_SSE_1i(slli_epi32)
Vc_AVX_TO_SSE_1i(slli_epi64)
Vc_AVX_TO_SSE_1i(srai_epi16)
Vc_AVX_TO_SSE_1i(srai_epi32)
Vc_AVX_TO_SSE_1i(srli_epi16)
Vc_AVX_TO_SSE_1i(srli_epi32)
Vc_AVX_TO_SSE_1i(srli_epi64)
Vc_AVX_TO_SSE_256_128(sll_epi16)
Vc_AVX_TO_SSE_256_128(sll_epi32)
Vc_AVX_TO_SSE_256_128(sll_epi64)
Vc_AVX_TO_SSE_256_128(srl_epi16)
Vc_AVX_TO_SSE_256_128(srl_epi32)
Vc_AVX_TO_SSE_256_128(srl_epi64)
Vc_AVX_TO_SSE_256_128(sra_epi16)
Vc_AVX_TO_SSE_256_128(sra_epi32)
Vc_AVX_TO_SSE_2_NEW(cmpeq_epi8)
Vc_AVX_TO_SSE_2_NEW(cmpeq_epi16)
Vc_AVX_TO_SSE_2_NEW(cmpeq_epi32)
Vc_AVX_TO_SSE_2_NEW(cmpeq_epi64)
Vc_AVX_TO_SSE_2_NEW(cmpgt_epi8)
Vc_AVX_TO_SSE_2_NEW(cmpgt_epi16)
Vc_AVX_TO_SSE_2_NEW(cmpgt_epi32)
Vc_AVX_TO_SSE_2_NEW(cmpgt_epi64)
Vc_AVX_TO_SSE_2_NEW(packs_epi16)
Vc_AVX_TO_SSE_2_NEW(packs_epi32)
Vc_AVX_TO_SSE_2_NEW(packus_epi16)
Vc_AVX_TO_SSE_2_NEW(unpackhi_epi8)
Vc_AVX_TO_SSE_2_NEW(unpackhi_epi16)
Vc_AVX_TO_SSE_2_NEW(unpackhi_epi32)
Vc_AVX_TO_SSE_2_NEW(unpackhi_epi64)
Vc_AVX_TO_SSE_2_NEW(unpacklo_epi8)
Vc_AVX_TO_SSE_2_NEW(unpacklo_epi16)
Vc_AVX_TO_SSE_2_NEW(unpacklo_epi32)
Vc_AVX_TO_SSE_2_NEW(unpacklo_epi64)
Vc_AVX_TO_SSE_2_NEW(add_epi8)
Vc_AVX_TO_SSE_2_NEW(add_epi16)
Vc_AVX_TO_SSE_2_NEW(add_epi32)
Vc_AVX_TO_SSE_2_NEW(add_epi64)
Vc_AVX_TO_SSE_2_NEW(adds_epi8)
Vc_AVX_TO_SSE_2_NEW(adds_epi16)
Vc_AVX_TO_SSE_2_NEW(adds_epu8)
Vc_AVX_TO_SSE_2_NEW(adds_epu16)
Vc_AVX_TO_SSE_2_NEW(sub_epi8)
Vc_AVX_TO_SSE_2_NEW(sub_epi16)
Vc_AVX_TO_SSE_2_NEW(sub_epi32)
Vc_AVX_TO_SSE_2_NEW(sub_epi64)
Vc_AVX_TO_SSE_2_NEW(subs_epi8)
Vc_AVX_TO_SSE_2_NEW(subs_epi16)
Vc_AVX_TO_SSE_2_NEW(subs_epu8)
Vc_AVX_TO_SSE_2_NEW(subs_epu16)
Vc_AVX_TO_SSE_2_NEW(madd_epi16)
Vc_AVX_TO_SSE_2_NEW(mulhi_epi16)
Vc_AVX_TO_SSE_2_NEW(mullo_epi16)
Vc_AVX_TO_SSE_2_NEW(mul_epu32)
Vc_AVX_TO_SSE_2_NEW(max_epi16)
Vc_AVX_TO_SSE_2_NEW(max_epu8)
Vc_AVX_TO_SSE_2_NEW(min_epi16)
Vc_AVX_TO_SSE_2_NEW(min_epu8)
Vc_AVX_TO_SSE_2_NEW(mulhi_epu16)
Vc_AVX_TO_SSE_2_NEW(avg_epu8)
Vc_AVX_TO_SSE_2_NEW(avg_epu16)
Vc_AVX_TO_SSE_2_NEW(sad_epu8)
Vc_AVX_TO_SSE_2_NEW(hadd_epi16)
Vc_AVX_TO_SSE_2_NEW(hadd_epi32)
Vc_AVX_TO_SSE_2_NEW(hadds_epi16)
Vc_AVX_TO_SSE_2_NEW(hsub_epi16)
Vc_AVX_TO_SSE_2_NEW(hsub_epi32)
Vc_AVX_TO_SSE_2_NEW(hsubs_epi16)
Vc_AVX_TO_SSE_2_NEW(maddubs_epi16)
Vc_AVX_TO_SSE_2_NEW(mulhrs_epi16)
Vc_AVX_TO_SSE_2_NEW(shuffle_epi8)
Vc_AVX_TO_SSE_2_NEW(sign_epi8)
Vc_AVX_TO_SSE_2_NEW(sign_epi16)
Vc_AVX_TO_SSE_2_NEW(sign_epi32)
Vc_AVX_TO_SSE_2_NEW(min_epi8)
Vc_AVX_TO_SSE_2_NEW(max_epi8)
Vc_AVX_TO_SSE_2_NEW(min_epu16)
Vc_AVX_TO_SSE_2_NEW(max_epu16)
Vc_AVX_TO_SSE_2_NEW(min_epi32)
Vc_AVX_TO_SSE_2_NEW(max_epi32)
Vc_AVX_TO_SSE_2_NEW(min_epu32)
Vc_AVX_TO_SSE_2_NEW(max_epu32)
Vc_AVX_TO_SSE_2_NEW(mullo_epi32)
Vc_AVX_TO_SSE_2_NEW(mul_epi32)
Vc_AVX_TO_SSE_1(abs_epi8)
Vc_AVX_TO_SSE_1(abs_epi16)
Vc_AVX_TO_SSE_1(abs_epi32)
Vc_AVX_TO_SSE_1_128(cvtepi8_epi16, 8)
Vc_AVX_TO_SSE_1_128(cvtepi8_epi32, 4)
Vc_AVX_TO_SSE_1_128(cvtepi8_epi64, 2)
Vc_AVX_TO_SSE_1_128(cvtepi16_epi32, 8)
Vc_AVX_TO_SSE_1_128(cvtepi16_epi64, 4)
Vc_AVX_TO_SSE_1_128(cvtepi32_epi64, 8)
Vc_AVX_TO_SSE_1_128(cvtepu8_epi16, 8)
Vc_AVX_TO_SSE_1_128(cvtepu8_epi32, 4)
Vc_AVX_TO_SSE_1_128(cvtepu8_epi64, 2)
Vc_AVX_TO_SSE_1_128(cvtepu16_epi32, 8)
Vc_AVX_TO_SSE_1_128(cvtepu16_epi64, 4)
Vc_AVX_TO_SSE_1_128(cvtepu32_epi64, 8)
Vc_AVX_TO_SSE_2_NEW(packus_epi32)
#ifndef Vc_IMPL_AVX2
template <int i> Vc_INTRINSIC Vc_CONST __m256i srli_si256(__m256i a0) {
const __m128i vLo = _mm256_castsi256_si128(a0);
const __m128i vHi = extract128<1>(a0);
return insert128<1>(_mm256_castsi128_si256(_mm_srli_si128(vLo, i)), _mm_srli_si128(vHi, i));
}
template <int i> Vc_INTRINSIC Vc_CONST __m256i slli_si256(__m256i a0) {
const __m128i vLo = _mm256_castsi256_si128(a0);
const __m128i vHi = extract128<1>(a0);
return insert128<1>(_mm256_castsi128_si256(_mm_slli_si128(vLo, i)), _mm_slli_si128(vHi, i));
}
static Vc_INTRINSIC m256i Vc_CONST and_si256(__m256i x, __m256i y) {
return _mm256_castps_si256(_mm256_and_ps(_mm256_castsi256_ps(x), _mm256_castsi256_ps(y)));
}
static Vc_INTRINSIC m256i Vc_CONST andnot_si256(__m256i x, __m256i y) {
return _mm256_castps_si256(_mm256_andnot_ps(_mm256_castsi256_ps(x), _mm256_castsi256_ps(y)));
}
static Vc_INTRINSIC m256i Vc_CONST or_si256(__m256i x, __m256i y) {
return _mm256_castps_si256(_mm256_or_ps(_mm256_castsi256_ps(x), _mm256_castsi256_ps(y)));
}
static Vc_INTRINSIC m256i Vc_CONST xor_si256(__m256i x, __m256i y) {
return _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(x), _mm256_castsi256_ps(y)));
}
Vc_INTRINSIC Vc_CONST int movemask_epi8(__m256i a0)
{
m128i a1 = extract128<1>(a0);
return (_mm_movemask_epi8(a1) << 16) | _mm_movemask_epi8(_mm256_castsi256_si128(a0));
}
template <int m> Vc_INTRINSIC Vc_CONST m256i blend_epi16(param256i a0, param256i b0)
{
m128i a1 = extract128<1>(a0);
m128i b1 = extract128<1>(b0);
m128i r0 = _mm_blend_epi16(_mm256_castsi256_si128(a0), _mm256_castsi256_si128(b0), m & 0xff);
m128i r1 = _mm_blend_epi16(a1, b1, m >> 8);
return insert128<1>(_mm256_castsi128_si256(r0), r1);
}
Vc_INTRINSIC Vc_CONST m256i blendv_epi8(param256i a0, param256i b0, param256i m0) {
m128i a1 = extract128<1>(a0);
m128i b1 = extract128<1>(b0);
m128i m1 = extract128<1>(m0);
m128i r0 = _mm_blendv_epi8(_mm256_castsi256_si128(a0), _mm256_castsi256_si128(b0), _mm256_castsi256_si128(m0));
m128i r1 = _mm_blendv_epi8(a1, b1, m1);
return insert128<1>(_mm256_castsi128_si256(r0), r1);
}
#else
static Vc_INTRINSIC Vc_CONST m256i xor_si256(__m256i x, __m256i y) { return _mm256_xor_si256(x, y); }
static Vc_INTRINSIC Vc_CONST m256i or_si256(__m256i x, __m256i y) { return _mm256_or_si256(x, y); }
static Vc_INTRINSIC Vc_CONST m256i and_si256(__m256i x, __m256i y) { return _mm256_and_si256(x, y); }
static Vc_INTRINSIC Vc_CONST m256i andnot_si256(__m256i x, __m256i y) { return _mm256_andnot_si256(x, y); }
template <int i> Vc_INTRINSIC Vc_CONST __m256i srli_si256(__m256i a0)
{
return _mm256_srli_si256(a0, i);
}
template <int i> Vc_INTRINSIC Vc_CONST __m256i slli_si256(__m256i a0)
{
return _mm256_slli_si256(a0, i);
}
Vc_INTRINSIC Vc_CONST m256i blendv_epi8(__m256i a0, __m256i b0, __m256i m0)
{
return _mm256_blendv_epi8(a0, b0, m0);
}
Vc_INTRINSIC Vc_CONST int movemask_epi8(__m256i a0)
{
return _mm256_movemask_epi8(a0);
}
#endif
static Vc_INTRINSIC m256i cmplt_epi64(__m256i a, __m256i b) {
return cmpgt_epi64(b, a);
}
static Vc_INTRINSIC m256i cmplt_epi32(__m256i a, __m256i b) {
return cmpgt_epi32(b, a);
}
static Vc_INTRINSIC m256i cmplt_epi16(__m256i a, __m256i b) {
return cmpgt_epi16(b, a);
}
static Vc_INTRINSIC m256i cmplt_epi8(__m256i a, __m256i b) {
return cmpgt_epi8(b, a);
}
static Vc_INTRINSIC m256i cmplt_epu8(__m256i a, __m256i b) {
return cmplt_epi8(xor_si256(a, setmin_epi8()), xor_si256(b, setmin_epi8()));
}
static Vc_INTRINSIC m256i cmpgt_epu8(__m256i a, __m256i b) {
return cmpgt_epi8(xor_si256(a, setmin_epi8()), xor_si256(b, setmin_epi8()));
}
#if defined(Vc_IMPL_XOP)
Vc_AVX_TO_SSE_2_NEW(comlt_epu32)
Vc_AVX_TO_SSE_2_NEW(comgt_epu32)
Vc_AVX_TO_SSE_2_NEW(comlt_epu16)
Vc_AVX_TO_SSE_2_NEW(comgt_epu16)
static Vc_INTRINSIC m256i Vc_CONST cmplt_epu32(__m256i a, __m256i b) { return comlt_epu32(a, b); }
static Vc_INTRINSIC m256i Vc_CONST cmpgt_epu32(__m256i a, __m256i b) { return comgt_epu32(a, b); }
static Vc_INTRINSIC m256i Vc_CONST cmplt_epu16(__m256i a, __m256i b) { return comlt_epu16(a, b); }
static Vc_INTRINSIC m256i Vc_CONST cmpgt_epu16(__m256i a, __m256i b) { return comgt_epu16(a, b); }
#else
static Vc_INTRINSIC m256i Vc_CONST cmplt_epu32(__m256i _a, __m256i _b) {
m256i a = _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(_a), _mm256_castsi256_ps(setmin_epi32())));
m256i b = _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(_b), _mm256_castsi256_ps(setmin_epi32())));
return cmplt_epi32(a, b);
}
static Vc_INTRINSIC m256i Vc_CONST cmpgt_epu32(__m256i _a, __m256i _b) {
m256i a = _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(_a), _mm256_castsi256_ps(setmin_epi32())));
m256i b = _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(_b), _mm256_castsi256_ps(setmin_epi32())));
return cmpgt_epi32(a, b);
}
static Vc_INTRINSIC m256i Vc_CONST cmplt_epu16(__m256i _a, __m256i _b) {
m256i a = _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(_a), _mm256_castsi256_ps(setmin_epi16())));
m256i b = _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(_b), _mm256_castsi256_ps(setmin_epi16())));
return cmplt_epi16(a, b);
}
static Vc_INTRINSIC m256i Vc_CONST cmpgt_epu16(__m256i _a, __m256i _b) {
m256i a = _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(_a), _mm256_castsi256_ps(setmin_epi16())));
m256i b = _mm256_castps_si256(_mm256_xor_ps(_mm256_castsi256_ps(_b), _mm256_castsi256_ps(setmin_epi16())));
return cmpgt_epi16(a, b);
}
#endif
static Vc_INTRINSIC void _mm256_maskstore(float *mem, const __m256 mask, const __m256 v) {
_mm256_maskstore_ps(mem, _mm256_castps_si256(mask), v);
}
static Vc_INTRINSIC void _mm256_maskstore(double *mem, const __m256d mask, const __m256d v) {
_mm256_maskstore_pd(mem, _mm256_castpd_si256(mask), v);
}
static Vc_INTRINSIC void _mm256_maskstore(int *mem, const __m256i mask, const __m256i v) {
#ifdef Vc_IMPL_AVX2
_mm256_maskstore_epi32(mem, mask, v);
#else
_mm256_maskstore_ps(reinterpret_cast<float *>(mem), mask, _mm256_castsi256_ps(v));
#endif
}
static Vc_INTRINSIC void _mm256_maskstore(unsigned int *mem, const __m256i mask, const __m256i v) {
_mm256_maskstore(reinterpret_cast<int *>(mem), mask, v);
}
static Vc_INTRINSIC void _mm256_maskstore(short *mem, const __m256i mask, const __m256i v) {
using namespace AVX;
_mm_maskmoveu_si128(_mm256_castsi256_si128(v), _mm256_castsi256_si128(mask), reinterpret_cast<char *>(&mem[0]));
_mm_maskmoveu_si128(extract128<1>(v), extract128<1>(mask), reinterpret_cast<char *>(&mem[8]));
}
static Vc_INTRINSIC void _mm256_maskstore(unsigned short *mem, const __m256i mask, const __m256i v) {
_mm256_maskstore(reinterpret_cast<short *>(mem), mask, v);
}
#undef Vc_AVX_TO_SSE_1
#undef Vc_AVX_TO_SSE_1_128
#undef Vc_AVX_TO_SSE_2_NEW
#undef Vc_AVX_TO_SSE_256_128
#undef Vc_AVX_TO_SSE_1i
template<typename R> Vc_INTRINSIC_L R stream_load(const float *mem) Vc_INTRINSIC_R;
template<> Vc_INTRINSIC m128 stream_load<m128>(const float *mem)
{
return _mm_castsi128_ps(_mm_stream_load_si128(reinterpret_cast<__m128i *>(const_cast<float *>(mem))));
}
template<> Vc_INTRINSIC m256 stream_load<m256>(const float *mem)
{
return insert128<1>(_mm256_castps128_ps256(stream_load<m128>(mem)),
stream_load<m128>(mem + 4));
}
template<typename R> Vc_INTRINSIC_L R stream_load(const double *mem) Vc_INTRINSIC_R;
template<> Vc_INTRINSIC m128d stream_load<m128d>(const double *mem)
{
return _mm_castsi128_pd(_mm_stream_load_si128(reinterpret_cast<__m128i *>(const_cast<double *>(mem))));
}
template<> Vc_INTRINSIC m256d stream_load<m256d>(const double *mem)
{
return insert128<1>(_mm256_castpd128_pd256(stream_load<m128d>(mem)),
stream_load<m128d>(mem + 2));
}
template<typename R> Vc_INTRINSIC_L R stream_load(const void *mem) Vc_INTRINSIC_R;
template<> Vc_INTRINSIC m128i stream_load<m128i>(const void *mem)
{
return _mm_stream_load_si128(reinterpret_cast<__m128i *>(const_cast<void *>(mem)));
}
template<> Vc_INTRINSIC m256i stream_load<m256i>(const void *mem)
{
return insert128<1>(_mm256_castsi128_si256(stream_load<m128i>(mem)),
stream_load<m128i>(static_cast<const __m128i *>(mem) + 1));
}
Vc_INTRINSIC void stream_store(float *mem, __m128 value, __m128 mask)
{
_mm_maskmoveu_si128(_mm_castps_si128(value), _mm_castps_si128(mask), reinterpret_cast<char *>(mem));
}
Vc_INTRINSIC void stream_store(float *mem, __m256 value, __m256 mask)
{
stream_store(mem, _mm256_castps256_ps128(value), _mm256_castps256_ps128(mask));
stream_store(mem + 4, extract128<1>(value), extract128<1>(mask));
}
Vc_INTRINSIC void stream_store(double *mem, __m128d value, __m128d mask)
{
_mm_maskmoveu_si128(_mm_castpd_si128(value), _mm_castpd_si128(mask), reinterpret_cast<char *>(mem));
}
Vc_INTRINSIC void stream_store(double *mem, __m256d value, __m256d mask)
{
stream_store(mem, _mm256_castpd256_pd128(value), _mm256_castpd256_pd128(mask));
stream_store(mem + 2, extract128<1>(value), extract128<1>(mask));
}
Vc_INTRINSIC void stream_store(void *mem, __m128i value, __m128i mask)
{
_mm_maskmoveu_si128(value, mask, reinterpret_cast<char *>(mem));
}
Vc_INTRINSIC void stream_store(void *mem, __m256i value, __m256i mask)
{
stream_store(mem, _mm256_castsi256_si128(value), _mm256_castsi256_si128(mask));
stream_store(static_cast<__m128i *>(mem) + 1, extract128<1>(value), extract128<1>(mask));
}
#ifndef __x86_64__
Vc_INTRINSIC Vc_PURE __m128i _mm_cvtsi64_si128(int64_t x) {
return _mm_castpd_si128(_mm_load_sd(reinterpret_cast<const double *>(&x)));
}
#endif
}
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace AVX
{
using namespace AvxIntrinsics;
}
namespace AVX2
{
using namespace AvxIntrinsics;
}
namespace AVX
{
template<typename T> struct VectorTypeHelper;
template<> struct VectorTypeHelper< char > { typedef __m256i Type; };
template<> struct VectorTypeHelper< signed char > { typedef __m256i Type; };
template<> struct VectorTypeHelper<unsigned char > { typedef __m256i Type; };
template<> struct VectorTypeHelper< short> { typedef __m256i Type; };
template<> struct VectorTypeHelper<unsigned short> { typedef __m256i Type; };
template<> struct VectorTypeHelper< int > { typedef __m256i Type; };
template<> struct VectorTypeHelper<unsigned int > { typedef __m256i Type; };
template<> struct VectorTypeHelper< long > { typedef __m256i Type; };
template<> struct VectorTypeHelper<unsigned long > { typedef __m256i Type; };
template<> struct VectorTypeHelper< long long> { typedef __m256i Type; };
template<> struct VectorTypeHelper<unsigned long long> { typedef __m256i Type; };
template<> struct VectorTypeHelper< float> { typedef __m256 Type; };
template<> struct VectorTypeHelper< double> { typedef __m256d Type; };
template<typename T> struct SseVectorType;
template<> struct SseVectorType<__m256 > { typedef __m128 Type; };
template<> struct SseVectorType<__m256i> { typedef __m128i Type; };
template<> struct SseVectorType<__m256d> { typedef __m128d Type; };
template<> struct SseVectorType<__m128 > { typedef __m128 Type; };
template<> struct SseVectorType<__m128i> { typedef __m128i Type; };
template<> struct SseVectorType<__m128d> { typedef __m128d Type; };
template <typename T>
using IntegerVectorType =
typename std::conditional<sizeof(T) == 16, __m128i, __m256i>::type;
template <typename T>
using DoubleVectorType =
typename std::conditional<sizeof(T) == 16, __m128d, __m256d>::type;
template <typename T>
using FloatVectorType =
typename std::conditional<sizeof(T) == 16, __m128, __m256>::type;
template<typename T> struct VectorHelper {};
template<typename T> struct GatherHelper;
template<typename T> struct ScatterHelper;
template<typename T> struct HasVectorDivisionHelper { enum { Value = 1 }; };
template<typename T> struct VectorHelperSize;
}
}
#endif
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename V> inline V zero();
}
namespace Common
{
namespace Detail
{
#ifdef Vc_IMPL_AVX
template <typename ValueType, size_t Size> struct IntrinsicType {
using type = typename std::conditional<
std::is_integral<ValueType>::value,
typename std::conditional<sizeof(ValueType) * Size == 16, __m128i, __m256i>::type,
typename std::conditional<
std::is_same<ValueType, double>::value,
typename std::conditional<sizeof(ValueType) * Size == 16, __m128d,
__m256d>::type,
typename std::conditional<sizeof(ValueType) * Size == 16, __m128,
__m256>::type>::type>::type;
};
#elif defined Vc_IMPL_SSE
template <typename ValueType, size_t Size> struct IntrinsicType {
using type = typename std::conditional<
std::is_integral<ValueType>::value, __m128i,
typename std::conditional<std::is_same<ValueType, double>::value, __m128d,
__m128>::type>::type;
};
#else
template <typename ValueType, size_t Size> struct IntrinsicType {
static_assert(Size == 1,
"IntrinsicType without SIMD target support may only have Size = 1");
using type = ValueType;
};
#endif
template <typename ValueType, size_t Size, size_t Bytes = sizeof(ValueType) * Size>
struct BuiltinType;
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
#define Vc_VECBUILTIN __attribute__((__vector_size__(16)))
template <size_t Size> struct BuiltinType< double , Size, 16> { typedef double type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< float , Size, 16> { typedef float type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< long long, Size, 16> { typedef long long type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned long long, Size, 16> { typedef unsigned long long type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< long , Size, 16> { typedef long type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned long , Size, 16> { typedef unsigned long type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< int , Size, 16> { typedef int type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned int , Size, 16> { typedef unsigned int type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< short , Size, 16> { typedef short type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned short , Size, 16> { typedef unsigned short type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< char , Size, 16> { typedef char type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned char , Size, 16> { typedef unsigned char type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< signed char , Size, 16> { typedef signed char type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< bool , Size, 16> { typedef unsigned char type Vc_VECBUILTIN; };
#undef Vc_VECBUILTIN
#define Vc_VECBUILTIN __attribute__((__vector_size__(32)))
template <size_t Size> struct BuiltinType< double , Size, 32> { typedef double type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< float , Size, 32> { typedef float type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< long long, Size, 32> { typedef long long type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned long long, Size, 32> { typedef unsigned long long type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< long , Size, 32> { typedef long type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned long , Size, 32> { typedef unsigned long type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< int , Size, 32> { typedef int type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned int , Size, 32> { typedef unsigned int type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< short , Size, 32> { typedef short type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned short , Size, 32> { typedef unsigned short type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< char , Size, 32> { typedef char type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType<unsigned char , Size, 32> { typedef unsigned char type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< signed char , Size, 32> { typedef signed char type Vc_VECBUILTIN; };
template <size_t Size> struct BuiltinType< bool , Size, 32> { typedef unsigned char type Vc_VECBUILTIN; };
#undef Vc_VECBUILTIN
#endif
}
template <typename ValueType, size_t Size>
using IntrinsicType = typename Detail::IntrinsicType<ValueType, Size>::type;
template <typename ValueType, size_t Size>
using BuiltinType = typename Detail::BuiltinType<ValueType, Size>::type;
namespace AliasStrategy
{
struct Union {};
struct MayAlias {};
struct VectorBuiltin {};
struct UnionMembers {};
}
using DefaultStrategy =
#if defined Vc_USE_BUILTIN_VECTOR_TYPES
AliasStrategy::VectorBuiltin;
#elif defined Vc_MSVC
AliasStrategy::UnionMembers;
#elif defined Vc_ICC
AliasStrategy::Union;
#elif defined __GNUC__
AliasStrategy::MayAlias;
#else
AliasStrategy::Union;
#endif
template <typename ValueType, size_t Size, typename Strategy = DefaultStrategy>
class Storage;
template <typename ValueType, size_t Size>
class Storage<ValueType, Size, AliasStrategy::Union>
{
static_assert(std::is_fundamental<ValueType>::value &&
std::is_arithmetic<ValueType>::value,
"Only works for fundamental arithmetic types.");
public:
using VectorType = IntrinsicType<ValueType, Size>;
using EntryType = ValueType;
union Alias {
Vc_INTRINSIC Alias(VectorType vv) : v(vv) {}
VectorType v;
EntryType m[Size];
};
Vc_INTRINSIC Storage() : data(Vc::Detail::zero<VectorType>()) {}
Vc_INTRINSIC Storage(const VectorType &x) : data(x) { assertCorrectAlignment(&data); }
template <typename U>
Vc_INTRINSIC explicit Storage(const U &x,
enable_if<sizeof(U) == sizeof(VectorType)> = nullarg)
: data(reinterpret_cast<VectorType>(x))
{
assertCorrectAlignment(&data);
}
Vc_INTRINSIC Storage(const Storage &) = default;
Vc_INTRINSIC Storage &operator=(const Storage &) = default;
Vc_INTRINSIC operator const VectorType &() const { return data; }
Vc_INTRINSIC Vc_PURE VectorType &v() { return data; }
Vc_INTRINSIC Vc_PURE const VectorType &v() const { return data; }
Vc_INTRINSIC Vc_PURE EntryType m(size_t i) const { return Alias(data).m[i]; }
Vc_INTRINSIC void set(size_t i, EntryType x)
{
Alias a(data);
a.m[i] = x;
data = a.v;
}
private:
VectorType data;
};
template <typename ValueType, size_t Size>
class Storage<ValueType, Size, AliasStrategy::MayAlias>
{
static_assert(std::is_fundamental<ValueType>::value &&
std::is_arithmetic<ValueType>::value,
"Only works for fundamental arithmetic types.");
public:
using VectorType = IntrinsicType<ValueType, Size>;
using EntryType = ValueType;
Vc_INTRINSIC Storage() : data() { assertCorrectAlignment(&data); }
Vc_INTRINSIC Storage(const VectorType &x) : data(x)
{
assertCorrectAlignment(&data);
}
template <typename U>
Vc_INTRINSIC explicit Storage(const U &x,
enable_if<sizeof(U) == sizeof(VectorType)> = nullarg)
: data(reinterpret_cast<const VectorType &>(x))
{
assertCorrectAlignment(&data);
}
Vc_INTRINSIC Storage &operator=(const VectorType &x)
{
data = x;
return *this;
}
Vc_INTRINSIC Storage(const Storage &) = default;
Vc_INTRINSIC Storage &operator=(const Storage &) = default;
Vc_INTRINSIC operator const VectorType &() const { return v(); }
Vc_INTRINSIC Vc_PURE VectorType &v() { return data; }
Vc_INTRINSIC Vc_PURE const VectorType &v() const { return data; }
Vc_INTRINSIC Vc_PURE EntryType m(size_t i) const
{
return aliasing_cast<EntryType>(&data)[i];
}
Vc_INTRINSIC void set(size_t i, EntryType x)
{
aliasing_cast<EntryType>(&data)[i] = x;
}
private:
VectorType data;
};
template <typename ValueType, size_t Size>
class Storage<ValueType, Size, AliasStrategy::VectorBuiltin>
{
static_assert(std::is_fundamental<ValueType>::value &&
std::is_arithmetic<ValueType>::value,
"Only works for fundamental arithmetic types.");
using Builtin = BuiltinType<ValueType, Size>;
public:
using VectorType =
#ifdef Vc_TEMPLATES_DROP_ATTRIBUTES
MayAlias<IntrinsicType<ValueType, Size>>;
#else
IntrinsicType<ValueType, Size>;
#endif
using EntryType = ValueType;
Vc_INTRINSIC Storage() : data() { assertCorrectAlignment(&data); }
Vc_INTRINSIC Storage(const Storage &) = default;
Vc_INTRINSIC Storage &operator=(const Storage &) = default;
Vc_INTRINSIC Storage(const VectorType &x)
: data(aliasing_cast<Builtin>(x))
{
assertCorrectAlignment(&data);
}
template <typename U>
Vc_INTRINSIC explicit Storage(const U &x,
enable_if<sizeof(U) == sizeof(VectorType)> = nullarg)
: data(aliasing_cast<Builtin>(x))
{
assertCorrectAlignment(&data);
}
Vc_INTRINSIC Storage &operator=(const VectorType &x)
{
data = aliasing_cast<Builtin>(x);
return *this;
}
Vc_INTRINSIC operator const VectorType &() const { return v(); }
Vc_INTRINSIC Vc_PURE VectorType &v() { return reinterpret_cast<VectorType &>(data); }
Vc_INTRINSIC Vc_PURE const VectorType &v() const { return reinterpret_cast<const VectorType &>(data); }
Vc_INTRINSIC Vc_PURE EntryType m(size_t i) const { return data[i]; }
Vc_INTRINSIC void set(size_t i, EntryType x) { data[i] = x; }
Vc_INTRINSIC Builtin &builtin() { return data; }
Vc_INTRINSIC const Builtin &builtin() const { return data; }
private:
Builtin data;
};
template <typename ValueType, size_t Size>
class Storage<ValueType, Size, AliasStrategy::UnionMembers>
{
static_assert(std::is_fundamental<ValueType>::value &&
std::is_arithmetic<ValueType>::value,
"Only works for fundamental arithmetic types.");
public:
using VectorType = IntrinsicType<ValueType, Size>;
using EntryType = ValueType;
Vc_INTRINSIC Storage() : data() { assertCorrectAlignment(&data); }
Vc_INTRINSIC Storage(const VectorType &x) : data(x)
{
assertCorrectAlignment(&data);
}
template <typename U>
Vc_INTRINSIC explicit Storage(const U &x,
enable_if<sizeof(U) == sizeof(VectorType)> = nullarg)
: data(reinterpret_cast<const VectorType &>(x))
{
assertCorrectAlignment(&data);
}
Vc_INTRINSIC Storage &operator=(const VectorType &x)
{
data = x;
return *this;
}
Vc_INTRINSIC Storage(const Storage &) = default;
Vc_INTRINSIC Storage &operator=(const Storage &) = default;
Vc_INTRINSIC Vc_PURE VectorType &v() { return data; }
Vc_INTRINSIC Vc_PURE const VectorType &v() const { return data; }
Vc_INTRINSIC_L Vc_PURE_L EntryType m(size_t i) const Vc_INTRINSIC_R Vc_PURE_R;
Vc_INTRINSIC void set(size_t i, EntryType x) { ref(i) = x; }
private:
Vc_INTRINSIC_L Vc_PURE_L EntryType &ref(size_t i) Vc_INTRINSIC_R Vc_PURE_R;
VectorType data;
};
#ifdef Vc_MSVC
template <> Vc_INTRINSIC Vc_PURE double Storage< double, 2, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128d_f64[i]; }
template <> Vc_INTRINSIC Vc_PURE float Storage< float , 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128_f32[i]; }
template <> Vc_INTRINSIC Vc_PURE signed int Storage< signed int , 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE signed short Storage< signed short , 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_i16[i]; }
template <> Vc_INTRINSIC Vc_PURE signed char Storage< signed char ,16, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_i8[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned int Storage<unsigned int , 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned short Storage<unsigned short , 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_u16[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned char Storage<unsigned char ,16, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m128i_u8[i]; }
template <> Vc_INTRINSIC Vc_PURE double &Storage< double, 2, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128d_f64[i]; }
template <> Vc_INTRINSIC Vc_PURE float &Storage< float , 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128_f32[i]; }
template <> Vc_INTRINSIC Vc_PURE signed int &Storage< signed int , 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE signed short &Storage< signed short , 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_i16[i]; }
template <> Vc_INTRINSIC Vc_PURE signed char &Storage< signed char ,16, AliasStrategy::UnionMembers>::ref(size_t i) { return reinterpret_cast<signed char &>(data.m128i_i8[i]); }
template <> Vc_INTRINSIC Vc_PURE unsigned int &Storage<unsigned int , 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned short &Storage<unsigned short , 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_u16[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned char &Storage<unsigned char ,16, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m128i_u8[i]; }
#ifdef Vc_IMPL_AVX
template <> Vc_INTRINSIC Vc_PURE double Storage< double, 4, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256d_f64[i]; }
template <> Vc_INTRINSIC Vc_PURE float Storage< float , 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256_f32[i]; }
template <> Vc_INTRINSIC Vc_PURE signed int Storage< signed int , 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE signed short Storage< signed short ,16, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_i16[i]; }
template <> Vc_INTRINSIC Vc_PURE signed char Storage< signed char ,32, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_i8[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned int Storage<unsigned int , 8, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned short Storage<unsigned short ,16, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_u16[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned char Storage<unsigned char ,32, AliasStrategy::UnionMembers>::m(size_t i) const { return data.m256i_u8[i]; }
template <> Vc_INTRINSIC Vc_PURE double &Storage< double, 4, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256d_f64[i]; }
template <> Vc_INTRINSIC Vc_PURE float &Storage< float , 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256_f32[i]; }
template <> Vc_INTRINSIC Vc_PURE signed int &Storage< signed int , 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_i32[i]; }
template <> Vc_INTRINSIC Vc_PURE signed short &Storage< signed short ,16, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_i16[i]; }
template <> Vc_INTRINSIC Vc_PURE signed char &Storage< signed char ,32, AliasStrategy::UnionMembers>::ref(size_t i) { return reinterpret_cast<signed char &>(data.m256i_i8[i]); }
template <> Vc_INTRINSIC Vc_PURE unsigned int &Storage<unsigned int , 8, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_u32[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned short &Storage<unsigned short ,16, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_u16[i]; }
template <> Vc_INTRINSIC Vc_PURE unsigned char &Storage<unsigned char ,32, AliasStrategy::UnionMembers>::ref(size_t i) { return data.m256i_u8[i]; }
#endif
#endif
template <typename VectorType, typename EntryType>
using VectorMemoryUnion = Storage<EntryType, sizeof(VectorType) / sizeof(EntryType)>;
}
}
#endif
#ifndef VC_SSE_CONST_DATA_H_
#define VC_SSE_CONST_DATA_H_ 
#ifndef VC_SSE_MACROS_H_
#define VC_SSE_MACROS_H_ 
#ifndef _M128
#define _M128 __m128
#endif
#ifndef _M128I
#define _M128I __m128i
#endif
#ifndef _M128D
#define _M128D __m128d
#endif
#if defined(Vc_IMPL_SSE4_1) && !defined(Vc_DISABLE_PTEST)
#define Vc_USE_PTEST 
#endif
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace SSE
{
alignas(16) extern const unsigned int _IndexesFromZero4[4];
alignas(16) extern const unsigned short _IndexesFromZero8[8];
alignas(16) extern const unsigned char _IndexesFromZero16[16];
struct c_general
{
alignas(64) static const int absMaskFloat[4];
alignas(16) static const unsigned int signMaskFloat[4];
alignas(16) static const unsigned int highMaskFloat[4];
alignas(16) static const short minShort[8];
alignas(16) static const unsigned short one16[8];
alignas(16) static const unsigned int one32[4];
alignas(16) static const float oneFloat[4];
alignas(16) static const unsigned long long highMaskDouble[2];
alignas(16) static const double oneDouble[2];
alignas(16) static const long long absMaskDouble[2];
alignas(16) static const unsigned long long signMaskDouble[2];
alignas(16) static const unsigned long long frexpMask[2];
};
template<typename T> struct c_trig
{
alignas(64) static const T data[];
};
#ifndef Vc_MSVC
template <> alignas(64) const float c_trig<float>::data[];
template <> alignas(64) const double c_trig<double>::data[];
#endif
template<typename T> struct c_log
{
enum VectorSize { Size = 16 / sizeof(T) };
static Vc_ALWAYS_INLINE Vc_CONST const float *d(int i) { return reinterpret_cast<const float *>(&data[i * Size]); }
alignas(64) static const unsigned int data[21 * Size];
};
#ifndef Vc_MSVC
template<> alignas(64) const unsigned int c_log<float>::data[21 * 4];
#endif
template<> struct c_log<double>
{
enum VectorSize { Size = 16 / sizeof(double) };
static Vc_ALWAYS_INLINE Vc_CONST const double *d(int i) { return reinterpret_cast<const double *>(&data[i * Size]); }
alignas(64) static const unsigned long long data[21 * Size];
};
}
}
#endif
#include <cstdlib>
#if defined(Vc_GCC) && !defined(__OPTIMIZE__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace SseIntrinsics
{
using SSE::c_general;
constexpr std::size_t VectorAlignment = 16;
#if defined(Vc_GCC) && Vc_GCC < 0x40600 && !defined(Vc_DONT_FIX_SSE_SHIFT)
static Vc_INTRINSIC Vc_CONST __m128i _mm_sll_epi16(__m128i a, __m128i count) { __asm__("psllw %1,%0" : "+x"(a) : "x"(count)); return a; }
static Vc_INTRINSIC Vc_CONST __m128i _mm_sll_epi32(__m128i a, __m128i count) { __asm__("pslld %1,%0" : "+x"(a) : "x"(count)); return a; }
static Vc_INTRINSIC Vc_CONST __m128i _mm_sll_epi64(__m128i a, __m128i count) { __asm__("psllq %1,%0" : "+x"(a) : "x"(count)); return a; }
static Vc_INTRINSIC Vc_CONST __m128i _mm_srl_epi16(__m128i a, __m128i count) { __asm__("psrlw %1,%0" : "+x"(a) : "x"(count)); return a; }
static Vc_INTRINSIC Vc_CONST __m128i _mm_srl_epi32(__m128i a, __m128i count) { __asm__("psrld %1,%0" : "+x"(a) : "x"(count)); return a; }
static Vc_INTRINSIC Vc_CONST __m128i _mm_srl_epi64(__m128i a, __m128i count) { __asm__("psrlq %1,%0" : "+x"(a) : "x"(count)); return a; }
#endif
#ifdef Vc_GCC
static Vc_INTRINSIC Vc_CONST __m128d _mm_mul_pd(__m128d a, __m128d b) { return static_cast<__m128d>(static_cast<__v2df>(a) * static_cast<__v2df>(b)); }
static Vc_INTRINSIC Vc_CONST __m128d _mm_add_pd(__m128d a, __m128d b) { return static_cast<__m128d>(static_cast<__v2df>(a) + static_cast<__v2df>(b)); }
static Vc_INTRINSIC Vc_CONST __m128d _mm_sub_pd(__m128d a, __m128d b) { return static_cast<__m128d>(static_cast<__v2df>(a) - static_cast<__v2df>(b)); }
static Vc_INTRINSIC Vc_CONST __m128 _mm_mul_ps(__m128 a, __m128 b) { return static_cast<__m128 >(static_cast<__v4sf>(a) * static_cast<__v4sf>(b)); }
static Vc_INTRINSIC Vc_CONST __m128 _mm_add_ps(__m128 a, __m128 b) { return static_cast<__m128 >(static_cast<__v4sf>(a) + static_cast<__v4sf>(b)); }
static Vc_INTRINSIC Vc_CONST __m128 _mm_sub_ps(__m128 a, __m128 b) { return static_cast<__m128 >(static_cast<__v4sf>(a) - static_cast<__v4sf>(b)); }
#endif
static Vc_INTRINSIC Vc_CONST __m128i _mm_setallone_si128() { return _mm_load_si128(reinterpret_cast<const __m128i *>(Common::AllBitsSet)); }
static Vc_INTRINSIC Vc_CONST __m128d _mm_setallone_pd() { return _mm_load_pd(reinterpret_cast<const double *>(Common::AllBitsSet)); }
static Vc_INTRINSIC Vc_CONST __m128 _mm_setallone_ps() { return _mm_load_ps(reinterpret_cast<const float *>(Common::AllBitsSet)); }
static Vc_INTRINSIC __m128i Vc_CONST _mm_setone_epi8 () { return _mm_set1_epi8(1); }
static Vc_INTRINSIC __m128i Vc_CONST _mm_setone_epu8 () { return _mm_setone_epi8(); }
static Vc_INTRINSIC __m128i Vc_CONST _mm_setone_epi16() { return _mm_load_si128(reinterpret_cast<const __m128i *>(c_general::one16)); }
static Vc_INTRINSIC __m128i Vc_CONST _mm_setone_epu16() { return _mm_setone_epi16(); }
static Vc_INTRINSIC __m128i Vc_CONST _mm_setone_epi32() { return _mm_load_si128(reinterpret_cast<const __m128i *>(c_general::one32)); }
static Vc_INTRINSIC __m128i Vc_CONST _mm_setone_epu32() { return _mm_setone_epi32(); }
static Vc_INTRINSIC __m128 Vc_CONST _mm_setone_ps() { return _mm_load_ps(c_general::oneFloat); }
static Vc_INTRINSIC __m128d Vc_CONST _mm_setone_pd() { return _mm_load_pd(c_general::oneDouble); }
static Vc_INTRINSIC __m128d Vc_CONST _mm_setabsmask_pd() { return _mm_load_pd(reinterpret_cast<const double *>(c_general::absMaskDouble)); }
static Vc_INTRINSIC __m128 Vc_CONST _mm_setabsmask_ps() { return _mm_load_ps(reinterpret_cast<const float *>(c_general::absMaskFloat)); }
static Vc_INTRINSIC __m128d Vc_CONST _mm_setsignmask_pd(){ return _mm_load_pd(reinterpret_cast<const double *>(c_general::signMaskDouble)); }
static Vc_INTRINSIC __m128 Vc_CONST _mm_setsignmask_ps(){ return _mm_load_ps(reinterpret_cast<const float *>(c_general::signMaskFloat)); }
static Vc_INTRINSIC __m128i Vc_CONST setmin_epi8 () { return _mm_set1_epi8(-0x80); }
static Vc_INTRINSIC __m128i Vc_CONST setmin_epi16() { return _mm_load_si128(reinterpret_cast<const __m128i *>(c_general::minShort)); }
static Vc_INTRINSIC __m128i Vc_CONST setmin_epi32() { return _mm_load_si128(reinterpret_cast<const __m128i *>(c_general::signMaskFloat)); }
static Vc_INTRINSIC __m128i Vc_CONST setmin_epi64() { return _mm_load_si128(reinterpret_cast<const __m128i *>(c_general::signMaskDouble)); }
#if defined(Vc_IMPL_XOP)
static Vc_INTRINSIC __m128i Vc_CONST cmplt_epu8(__m128i a, __m128i b) { return _mm_comlt_epu8(a, b); }
static Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu8(__m128i a, __m128i b) { return _mm_comgt_epu8(a, b); }
static Vc_INTRINSIC __m128i Vc_CONST cmplt_epu16(__m128i a, __m128i b) { return _mm_comlt_epu16(a, b); }
static Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu16(__m128i a, __m128i b) { return _mm_comgt_epu16(a, b); }
static Vc_INTRINSIC __m128i Vc_CONST cmplt_epu32(__m128i a, __m128i b) { return _mm_comlt_epu32(a, b); }
static Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu32(__m128i a, __m128i b) { return _mm_comgt_epu32(a, b); }
static Vc_INTRINSIC __m128i Vc_CONST cmplt_epu64(__m128i a, __m128i b) { return _mm_comlt_epu64(a, b); }
static Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu64(__m128i a, __m128i b) { return _mm_comgt_epu64(a, b); }
#else
static Vc_INTRINSIC __m128i Vc_CONST cmplt_epu8(__m128i a, __m128i b)
{
return _mm_cmplt_epi8(_mm_xor_si128(a, setmin_epi8()),
_mm_xor_si128(b, setmin_epi8()));
}
static Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu8(__m128i a, __m128i b)
{
return _mm_cmpgt_epi8(_mm_xor_si128(a, setmin_epi8()),
_mm_xor_si128(b, setmin_epi8()));
}
static Vc_INTRINSIC __m128i Vc_CONST cmplt_epu16(__m128i a, __m128i b)
{
return _mm_cmplt_epi16(_mm_xor_si128(a, setmin_epi16()),
_mm_xor_si128(b, setmin_epi16()));
}
static Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu16(__m128i a, __m128i b)
{
return _mm_cmpgt_epi16(_mm_xor_si128(a, setmin_epi16()),
_mm_xor_si128(b, setmin_epi16()));
}
static Vc_INTRINSIC __m128i Vc_CONST cmplt_epu32(__m128i a, __m128i b)
{
return _mm_cmplt_epi32(_mm_xor_si128(a, setmin_epi32()),
_mm_xor_si128(b, setmin_epi32()));
}
static Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu32(__m128i a, __m128i b)
{
return _mm_cmpgt_epi32(_mm_xor_si128(a, setmin_epi32()),
_mm_xor_si128(b, setmin_epi32()));
}
Vc_INTRINSIC __m128i Vc_CONST cmpgt_epi64(__m128i a, __m128i b)
{
#ifdef Vc_IMPL_SSE4_2
return _mm_cmpgt_epi64(a, b);
#else
const auto aa = _mm_xor_si128(a, _mm_srli_epi64(setmin_epi32(),32));
const auto bb = _mm_xor_si128(b, _mm_srli_epi64(setmin_epi32(),32));
const auto gt = _mm_cmpgt_epi32(aa, bb);
const auto eq = _mm_cmpeq_epi32(aa, bb);
const auto gt2 =
_mm_shuffle_epi32(gt, 0xf5);
const auto lo =
_mm_shuffle_epi32(_mm_and_si128(_mm_srli_epi64(eq, 32), gt), 0xa0);
return _mm_or_si128(gt2, lo);
#endif
}
static Vc_INTRINSIC __m128i Vc_CONST cmpgt_epu64(__m128i a, __m128i b)
{
return cmpgt_epi64(_mm_xor_si128(a, setmin_epi64()),
_mm_xor_si128(b, setmin_epi64()));
}
#endif
}
}
#ifdef Vc_IMPL_SSSE3
namespace Vc_VERSIONED_NAMESPACE
{
namespace SseIntrinsics
{
Vc_INTRINSIC Vc_CONST __m128i abs_epi8(__m128i a) { return _mm_abs_epi8(a); }
Vc_INTRINSIC Vc_CONST __m128i abs_epi16(__m128i a) { return _mm_abs_epi16(a); }
Vc_INTRINSIC Vc_CONST __m128i abs_epi32(__m128i a) { return _mm_abs_epi32(a); }
template <int s> Vc_INTRINSIC Vc_CONST __m128i alignr_epi8(__m128i a, __m128i b)
{
return _mm_alignr_epi8(a, b, s & 0x1fu);
}
}
}
#else
namespace Vc_VERSIONED_NAMESPACE
{
namespace SseIntrinsics
{
Vc_INTRINSIC Vc_CONST __m128i abs_epi8 (__m128i a) {
__m128i negative = _mm_cmplt_epi8 (a, _mm_setzero_si128());
return _mm_add_epi8 (_mm_xor_si128(a, negative), _mm_and_si128(negative, _mm_setone_epi8()));
}
Vc_INTRINSIC Vc_CONST __m128i abs_epi16(__m128i a) {
__m128i negative = _mm_cmplt_epi16(a, _mm_setzero_si128());
return _mm_add_epi16(_mm_xor_si128(a, negative), _mm_srli_epi16(negative, 15));
}
Vc_INTRINSIC Vc_CONST __m128i abs_epi32(__m128i a) {
__m128i negative = _mm_cmplt_epi32(a, _mm_setzero_si128());
return _mm_add_epi32(_mm_xor_si128(a, negative), _mm_srli_epi32(negative, 31));
}
template <int s> Vc_INTRINSIC Vc_CONST __m128i alignr_epi8(__m128i a, __m128i b)
{
switch (s & 0x1fu) {
case 0: return b;
case 1: return _mm_or_si128(_mm_slli_si128(a, 15), _mm_srli_si128(b, 1));
case 2: return _mm_or_si128(_mm_slli_si128(a, 14), _mm_srli_si128(b, 2));
case 3: return _mm_or_si128(_mm_slli_si128(a, 13), _mm_srli_si128(b, 3));
case 4: return _mm_or_si128(_mm_slli_si128(a, 12), _mm_srli_si128(b, 4));
case 5: return _mm_or_si128(_mm_slli_si128(a, 11), _mm_srli_si128(b, 5));
case 6: return _mm_or_si128(_mm_slli_si128(a, 10), _mm_srli_si128(b, 6));
case 7: return _mm_or_si128(_mm_slli_si128(a, 9), _mm_srli_si128(b, 7));
case 8: return _mm_or_si128(_mm_slli_si128(a, 8), _mm_srli_si128(b, 8));
case 9: return _mm_or_si128(_mm_slli_si128(a, 7), _mm_srli_si128(b, 9));
case 10: return _mm_or_si128(_mm_slli_si128(a, 6), _mm_srli_si128(b, 10));
case 11: return _mm_or_si128(_mm_slli_si128(a, 5), _mm_srli_si128(b, 11));
case 12: return _mm_or_si128(_mm_slli_si128(a, 4), _mm_srli_si128(b, 12));
case 13: return _mm_or_si128(_mm_slli_si128(a, 3), _mm_srli_si128(b, 13));
case 14: return _mm_or_si128(_mm_slli_si128(a, 2), _mm_srli_si128(b, 14));
case 15: return _mm_or_si128(_mm_slli_si128(a, 1), _mm_srli_si128(b, 15));
case 16: return a;
case 17: return _mm_srli_si128(a, 1);
case 18: return _mm_srli_si128(a, 2);
case 19: return _mm_srli_si128(a, 3);
case 20: return _mm_srli_si128(a, 4);
case 21: return _mm_srli_si128(a, 5);
case 22: return _mm_srli_si128(a, 6);
case 23: return _mm_srli_si128(a, 7);
case 24: return _mm_srli_si128(a, 8);
case 25: return _mm_srli_si128(a, 9);
case 26: return _mm_srli_si128(a, 10);
case 27: return _mm_srli_si128(a, 11);
case 28: return _mm_srli_si128(a, 12);
case 29: return _mm_srli_si128(a, 13);
case 30: return _mm_srli_si128(a, 14);
case 31: return _mm_srli_si128(a, 15);
}
return _mm_setzero_si128();
}
}
}
#endif
#ifdef Vc_IMPL_SSE4_1
namespace Vc_VERSIONED_NAMESPACE
{
namespace SseIntrinsics
{
Vc_INTRINSIC Vc_CONST __m128i cmpeq_epi64(__m128i a, __m128i b)
{
return _mm_cmpeq_epi64(a, b);
}
template <int index> Vc_INTRINSIC Vc_CONST int extract_epi32(__m128i v)
{
return _mm_extract_epi32(v, index);
}
Vc_INTRINSIC Vc_CONST __m128d blendv_pd(__m128d a, __m128d b, __m128d c)
{
return _mm_blendv_pd(a, b, c);
}
Vc_INTRINSIC Vc_CONST __m128 blendv_ps(__m128 a, __m128 b, __m128 c)
{
return _mm_blendv_ps(a, b, c);
}
Vc_INTRINSIC Vc_CONST __m128i blendv_epi8(__m128i a, __m128i b, __m128i c)
{
return _mm_blendv_epi8(a, b, c);
}
template <int mask> Vc_INTRINSIC Vc_CONST __m128d blend_pd(__m128d a, __m128d b)
{
return _mm_blend_pd(a, b, mask);
}
template <int mask> Vc_INTRINSIC Vc_CONST __m128 blend_ps(__m128 a, __m128 b)
{
return _mm_blend_ps(a, b, mask);
}
template <int mask> Vc_INTRINSIC Vc_CONST __m128i blend_epi16(__m128i a, __m128i b)
{
return _mm_blend_epi16(a, b, mask);
}
Vc_INTRINSIC Vc_CONST __m128i max_epi8(__m128i a, __m128i b)
{
return _mm_max_epi8(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i max_epi32(__m128i a, __m128i b)
{
return _mm_max_epi32(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i max_epu16(__m128i a, __m128i b)
{
return _mm_max_epu16(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i max_epu32(__m128i a, __m128i b)
{
return _mm_max_epu32(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i min_epu16(__m128i a, __m128i b)
{
return _mm_min_epu16(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i min_epu32(__m128i a, __m128i b)
{
return _mm_min_epu32(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i min_epi8(__m128i a, __m128i b)
{
return _mm_min_epi8(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i min_epi32(__m128i a, __m128i b)
{
return _mm_min_epi32(a, b);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu8_epi16(__m128i epu8)
{
return _mm_cvtepu8_epi16(epu8);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi8_epi16(__m128i epi8)
{
return _mm_cvtepi8_epi16(epi8);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu16_epi32(__m128i epu16)
{
return _mm_cvtepu16_epi32(epu16);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi16_epi32(__m128i epu16)
{
return _mm_cvtepi16_epi32(epu16);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu8_epi32(__m128i epu8)
{
return _mm_cvtepu8_epi32(epu8);
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi8_epi32(__m128i epi8)
{
return _mm_cvtepi8_epi32(epi8);
}
Vc_INTRINSIC Vc_PURE __m128i stream_load_si128(__m128i *mem)
{
return _mm_stream_load_si128(mem);
}
}
}
#else
namespace Vc_VERSIONED_NAMESPACE
{
namespace SseIntrinsics
{
Vc_INTRINSIC Vc_CONST __m128i cmpeq_epi64(__m128i a, __m128i b) {
auto tmp = _mm_cmpeq_epi32(a, b);
return _mm_and_si128(tmp, _mm_shuffle_epi32(tmp, 1*1 + 0*4 + 3*16 + 2*64));
}
template <int index> Vc_INTRINSIC Vc_CONST int extract_epi32(__m128i v)
{
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
typedef int int32v4 __attribute__((__vector_size__(16)));
return aliasing_cast<int32v4>(v)[index];
#else
return _mm_cvtsi128_si32(_mm_srli_si128(v, index * 4));
#endif
}
Vc_INTRINSIC Vc_CONST __m128d blendv_pd(__m128d a, __m128d b, __m128d c) {
#ifdef Vc_GCC
return reinterpret_cast<__m128d>(
(~reinterpret_cast<__m128i>(c) & reinterpret_cast<__m128i>(a)) |
(reinterpret_cast<__m128i>(c) & reinterpret_cast<__m128i>(b)));
#else
return _mm_or_pd(_mm_andnot_pd(c, a), _mm_and_pd(c, b));
#endif
}
Vc_INTRINSIC Vc_CONST __m128 blendv_ps(__m128 a, __m128 b, __m128 c) {
#ifdef Vc_GCC
return reinterpret_cast<__m128>(
(~reinterpret_cast<__m128i>(c) & reinterpret_cast<__m128i>(a)) |
(reinterpret_cast<__m128i>(c) & reinterpret_cast<__m128i>(b)));
#else
return _mm_or_ps(_mm_andnot_ps(c, a), _mm_and_ps(c, b));
#endif
}
Vc_INTRINSIC Vc_CONST __m128i blendv_epi8(__m128i a, __m128i b, __m128i c) {
#ifdef Vc_GCC
return (~c & a) | (c & b);
#else
return _mm_or_si128(_mm_andnot_si128(c, a), _mm_and_si128(c, b));
#endif
}
template <int mask> Vc_INTRINSIC Vc_CONST __m128d blend_pd(__m128d a, __m128d b)
{
switch (mask) {
case 0x0:
return a;
case 0x1:
return _mm_shuffle_pd(b, a, 2);
case 0x2:
return _mm_shuffle_pd(a, b, 2);
case 0x3:
return b;
default:
abort();
return a;
}
}
template <int mask> Vc_INTRINSIC Vc_CONST __m128 blend_ps(__m128 a, __m128 b)
{
__m128i c;
switch (mask) {
case 0x0:
return a;
case 0x1:
c = _mm_srli_si128(_mm_setallone_si128(), 12);
break;
case 0x2:
c = _mm_slli_si128(_mm_srli_si128(_mm_setallone_si128(), 12), 4);
break;
case 0x3:
c = _mm_srli_si128(_mm_setallone_si128(), 8);
break;
case 0x4:
c = _mm_slli_si128(_mm_srli_si128(_mm_setallone_si128(), 12), 8);
break;
case 0x5:
c = _mm_set_epi32(0, -1, 0, -1);
break;
case 0x6:
c = _mm_slli_si128(_mm_srli_si128(_mm_setallone_si128(), 8), 4);
break;
case 0x7:
c = _mm_srli_si128(_mm_setallone_si128(), 4);
break;
case 0x8:
c = _mm_slli_si128(_mm_setallone_si128(), 12);
break;
case 0x9:
c = _mm_set_epi32(-1, 0, 0, -1);
break;
case 0xa:
c = _mm_set_epi32(-1, 0, -1, 0);
break;
case 0xb:
c = _mm_set_epi32(-1, 0, -1, -1);
break;
case 0xc:
c = _mm_slli_si128(_mm_setallone_si128(), 8);
break;
case 0xd:
c = _mm_set_epi32(-1, -1, 0, -1);
break;
case 0xe:
c = _mm_slli_si128(_mm_setallone_si128(), 4);
break;
case 0xf:
return b;
default:
abort();
c = _mm_setzero_si128();
break;
}
__m128 _c = _mm_castsi128_ps(c);
return _mm_or_ps(_mm_andnot_ps(_c, a), _mm_and_ps(_c, b));
}
template <int mask> Vc_INTRINSIC Vc_CONST __m128i blend_epi16(__m128i a, __m128i b)
{
__m128i c;
switch (mask) {
case 0x00:
return a;
case 0x01:
c = _mm_srli_si128(_mm_setallone_si128(), 14);
break;
case 0x03:
c = _mm_srli_si128(_mm_setallone_si128(), 12);
break;
case 0x07:
c = _mm_srli_si128(_mm_setallone_si128(), 10);
break;
case 0x0f:
return _mm_unpackhi_epi64(_mm_slli_si128(b, 8), a);
case 0x1f:
c = _mm_srli_si128(_mm_setallone_si128(), 6);
break;
case 0x3f:
c = _mm_srli_si128(_mm_setallone_si128(), 4);
break;
case 0x7f:
c = _mm_srli_si128(_mm_setallone_si128(), 2);
break;
case 0x80:
c = _mm_slli_si128(_mm_setallone_si128(), 14);
break;
case 0xc0:
c = _mm_slli_si128(_mm_setallone_si128(), 12);
break;
case 0xe0:
c = _mm_slli_si128(_mm_setallone_si128(), 10);
break;
case 0xf0:
c = _mm_slli_si128(_mm_setallone_si128(), 8);
break;
case 0xf8:
c = _mm_slli_si128(_mm_setallone_si128(), 6);
break;
case 0xfc:
c = _mm_slli_si128(_mm_setallone_si128(), 4);
break;
case 0xfe:
c = _mm_slli_si128(_mm_setallone_si128(), 2);
break;
case 0xff:
return b;
case 0xcc:
return _mm_unpacklo_epi32(_mm_shuffle_epi32(a, _MM_SHUFFLE(2, 0, 2, 0)), _mm_shuffle_epi32(b, _MM_SHUFFLE(3, 1, 3, 1)));
case 0x33:
return _mm_unpacklo_epi32(_mm_shuffle_epi32(b, _MM_SHUFFLE(2, 0, 2, 0)), _mm_shuffle_epi32(a, _MM_SHUFFLE(3, 1, 3, 1)));
default:
const __m128i shift = _mm_set_epi16(0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, -0x7fff);
c = _mm_srai_epi16(_mm_mullo_epi16(_mm_set1_epi16(mask), shift), 15);
break;
}
return _mm_or_si128(_mm_andnot_si128(c, a), _mm_and_si128(c, b));
}
Vc_INTRINSIC Vc_CONST __m128i max_epi8 (__m128i a, __m128i b) {
return blendv_epi8(b, a, _mm_cmpgt_epi8 (a, b));
}
Vc_INTRINSIC Vc_CONST __m128i max_epi32(__m128i a, __m128i b) {
return blendv_epi8(b, a, _mm_cmpgt_epi32(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i max_epu16(__m128i a, __m128i b) {
return blendv_epi8(b, a, cmpgt_epu16(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i max_epu32(__m128i a, __m128i b) {
return blendv_epi8(b, a, cmpgt_epu32(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i min_epu16(__m128i a, __m128i b) {
return blendv_epi8(a, b, cmpgt_epu16(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i min_epu32(__m128i a, __m128i b) {
return blendv_epi8(a, b, cmpgt_epu32(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i min_epi8 (__m128i a, __m128i b) {
return blendv_epi8(a, b, _mm_cmpgt_epi8 (a, b));
}
Vc_INTRINSIC Vc_CONST __m128i min_epi32(__m128i a, __m128i b) {
return blendv_epi8(a, b, _mm_cmpgt_epi32(a, b));
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu8_epi16(__m128i epu8) {
return _mm_unpacklo_epi8(epu8, _mm_setzero_si128());
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi8_epi16(__m128i epi8) {
return _mm_unpacklo_epi8(epi8, _mm_cmplt_epi8(epi8, _mm_setzero_si128()));
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu16_epi32(__m128i epu16) {
return _mm_unpacklo_epi16(epu16, _mm_setzero_si128());
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi16_epi32(__m128i epu16) {
return _mm_unpacklo_epi16(epu16, _mm_cmplt_epi16(epu16, _mm_setzero_si128()));
}
Vc_INTRINSIC Vc_CONST __m128i cvtepu8_epi32(__m128i epu8) {
return cvtepu16_epi32(cvtepu8_epi16(epu8));
}
Vc_INTRINSIC Vc_CONST __m128i cvtepi8_epi32(__m128i epi8) {
const __m128i neg = _mm_cmplt_epi8(epi8, _mm_setzero_si128());
const __m128i epi16 = _mm_unpacklo_epi8(epi8, neg);
return _mm_unpacklo_epi16(epi16, _mm_unpacklo_epi8(neg, neg));
}
Vc_INTRINSIC Vc_PURE __m128i stream_load_si128(__m128i *mem) {
return _mm_load_si128(mem);
}
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace SseIntrinsics
{
static Vc_INTRINSIC Vc_CONST float extract_float_imm(const __m128 v, const size_t i) {
float f;
switch (i) {
case 0:
f = _mm_cvtss_f32(v);
break;
#if defined Vc_IMPL_SSE4_1 && !defined Vc_MSVC
default:
#ifdef Vc_GCC
f = __builtin_ia32_vec_ext_v4sf(static_cast<__v4sf>(v), (i));
#else
_MM_EXTRACT_FLOAT(f, v, i);
#endif
break;
#else
case 1:
f = _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(v), 4)));
break;
case 2:
f = _mm_cvtss_f32(_mm_movehl_ps(v, v));
break;
case 3:
f = _mm_cvtss_f32(_mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(v), 12)));
break;
#endif
}
return f;
}
static Vc_INTRINSIC Vc_CONST double extract_double_imm(const __m128d v, const size_t i) {
if (i == 0) {
return _mm_cvtsd_f64(v);
}
return _mm_cvtsd_f64(_mm_castps_pd(_mm_movehl_ps(_mm_castpd_ps(v), _mm_castpd_ps(v))));
}
static Vc_INTRINSIC Vc_CONST float extract_float(const __m128 v, const size_t i) {
#ifdef Vc_GCC
if (__builtin_constant_p(i)) {
return extract_float_imm(v, i);
} else {
typedef float float4[4] Vc_MAY_ALIAS;
const float4 &data = reinterpret_cast<const float4 &>(v);
return data[i];
}
#else
union { __m128 v; float m[4]; } u;
u.v = v;
return u.m[i];
#endif
}
static Vc_INTRINSIC Vc_PURE __m128 _mm_stream_load(const float *mem) {
#ifdef Vc_IMPL_SSE4_1
return _mm_castsi128_ps(_mm_stream_load_si128(reinterpret_cast<__m128i *>(const_cast<float *>(mem))));
#else
return _mm_load_ps(mem);
#endif
}
static Vc_INTRINSIC Vc_PURE __m128d _mm_stream_load(const double *mem) {
#ifdef Vc_IMPL_SSE4_1
return _mm_castsi128_pd(_mm_stream_load_si128(reinterpret_cast<__m128i *>(const_cast<double *>(mem))));
#else
return _mm_load_pd(mem);
#endif
}
static Vc_INTRINSIC Vc_PURE __m128i _mm_stream_load(const int *mem) {
#ifdef Vc_IMPL_SSE4_1
return _mm_stream_load_si128(reinterpret_cast<__m128i *>(const_cast<int *>(mem)));
#else
return _mm_load_si128(reinterpret_cast<const __m128i *>(mem));
#endif
}
static Vc_INTRINSIC Vc_PURE __m128i _mm_stream_load(const unsigned int *mem) {
return _mm_stream_load(reinterpret_cast<const int *>(mem));
}
static Vc_INTRINSIC Vc_PURE __m128i _mm_stream_load(const short *mem) {
return _mm_stream_load(reinterpret_cast<const int *>(mem));
}
static Vc_INTRINSIC Vc_PURE __m128i _mm_stream_load(const unsigned short *mem) {
return _mm_stream_load(reinterpret_cast<const int *>(mem));
}
static Vc_INTRINSIC Vc_PURE __m128i _mm_stream_load(const signed char *mem) {
return _mm_stream_load(reinterpret_cast<const int *>(mem));
}
static Vc_INTRINSIC Vc_PURE __m128i _mm_stream_load(const unsigned char *mem) {
return _mm_stream_load(reinterpret_cast<const int *>(mem));
}
#ifndef __x86_64__
Vc_INTRINSIC Vc_PURE __m128i _mm_cvtsi64_si128(int64_t x) {
return _mm_castpd_si128(_mm_load_sd(reinterpret_cast<const double *>(&x)));
}
#endif
}
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace SSE
{
using namespace SseIntrinsics;
template <typename T> struct ParameterHelper
{
typedef T ByValue;
typedef T &Reference;
typedef const T &ConstRef;
};
template <typename T> struct VectorHelper
{
};
template <typename T> struct VectorTypeHelper
{
typedef __m128i Type;
};
template <> struct VectorTypeHelper<double>
{
typedef __m128d Type;
};
template <> struct VectorTypeHelper<float>
{
typedef __m128 Type;
};
template <typename T> struct DetermineGatherMask
{
typedef T Type;
};
template <typename T> struct VectorTraits
{
typedef typename VectorTypeHelper<T>::Type VectorType;
using EntryType = typename Common::ensure_alignment_equals_sizeof<T>::type;
static constexpr size_t Size = sizeof(VectorType) / sizeof(EntryType);
enum Constants { HasVectorDivision = !std::is_integral<T>::value };
typedef Mask<T> MaskType;
typedef typename DetermineGatherMask<MaskType>::Type GatherMaskType;
typedef Common::VectorMemoryUnion<VectorType, EntryType> StorageType;
};
template <typename T> struct VectorHelperSize;
}
}
#if defined(Vc_GCC) && !defined(__OPTIMIZE__)
#pragma GCC diagnostic pop
#endif
#ifndef VC_SSE_SHUFFLE_H_
#define VC_SSE_SHUFFLE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
enum VecPos {
X0, X1, X2, X3, X4, X5, X6, X7,
Y0, Y1, Y2, Y3, Y4, Y5, Y6, Y7,
Const0
};
namespace Mem
{
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m128 Vc_CONST shuffle(__m128 x, __m128 y) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= Y0 && Dst3 >= Y0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= Y3 && Dst3 <= Y3, "Incorrect_Range");
return _mm_shuffle_ps(x, y, Dst0 + Dst1 * 4 + (Dst2 - Y0) * 16 + (Dst3 - Y0) * 64);
}
template<VecPos Dst0, VecPos Dst1> static Vc_ALWAYS_INLINE __m128d Vc_CONST shuffle(__m128d x, __m128d y) {
static_assert(Dst0 >= X0 && Dst1 >= Y0, "Incorrect_Range");
static_assert(Dst0 <= X1 && Dst1 <= Y1, "Incorrect_Range");
return _mm_shuffle_pd(x, y, Dst0 + (Dst1 - Y0) * 2);
}
template <VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3>
Vc_INTRINSIC Vc_CONST __m128i shuffle(__m128i x, __m128i y)
{
return _mm_castps_si128(shuffle<Dst0, Dst1, Dst2, Dst3>(_mm_castsi128_ps(x),
_mm_castsi128_ps(y)));
}
template<VecPos Dst0, VecPos Dst1> static Vc_ALWAYS_INLINE __m128d Vc_CONST blend(__m128d x, __m128d y) {
static_assert(Dst0 == X0 || Dst0 == Y0, "Incorrect_Range");
static_assert(Dst1 == X1 || Dst1 == Y1, "Incorrect_Range");
return Vc::SseIntrinsics::blend_pd<(Dst0 / Y0) + (Dst1 / Y0) * 2>(x, y);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m128 Vc_CONST blend(__m128 x, __m128 y) {
static_assert(Dst0 == X0 || Dst0 == Y0, "Incorrect_Range");
static_assert(Dst1 == X1 || Dst1 == Y1, "Incorrect_Range");
static_assert(Dst2 == X2 || Dst2 == Y2, "Incorrect_Range");
static_assert(Dst3 == X3 || Dst3 == Y3, "Incorrect_Range");
return Vc::SseIntrinsics::blend_ps<(Dst0 / Y0) * 1 + (Dst1 / Y1) * 2 +
(Dst2 / Y2) * 4 + (Dst3 / Y3) * 8>(x, y);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3, VecPos Dst4, VecPos Dst5, VecPos Dst6, VecPos Dst7>
static Vc_ALWAYS_INLINE __m128i Vc_CONST blend(__m128i x, __m128i y) {
static_assert(Dst0 == X0 || Dst0 == Y0, "Incorrect_Range");
static_assert(Dst1 == X1 || Dst1 == Y1, "Incorrect_Range");
static_assert(Dst2 == X2 || Dst2 == Y2, "Incorrect_Range");
static_assert(Dst3 == X3 || Dst3 == Y3, "Incorrect_Range");
static_assert(Dst4 == X4 || Dst4 == Y4, "Incorrect_Range");
static_assert(Dst5 == X5 || Dst5 == Y5, "Incorrect_Range");
static_assert(Dst6 == X6 || Dst6 == Y6, "Incorrect_Range");
static_assert(Dst7 == X7 || Dst7 == Y7, "Incorrect_Range");
return Vc::SseIntrinsics::blend_epi16<
(Dst0 / Y0) * 1 + (Dst1 / Y1) * 2 + (Dst2 / Y2) * 4 + (Dst3 / Y3) * 8 +
(Dst4 / Y4) * 16 + (Dst5 / Y5) * 32 + (Dst6 / Y6) * 64 +
(Dst7 / Y7) * 128>(x, y);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m128 Vc_CONST permute(__m128 x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm_shuffle_ps(x, x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
template<VecPos Dst0, VecPos Dst1> static Vc_ALWAYS_INLINE Vc_CONST __m128d permute(__m128d x) {
static_assert(Dst0 >= X0 && Dst1 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X1 && Dst1 <= X1, "Incorrect_Range");
return _mm_shuffle_pd(x, x, Dst0 + Dst1 * 4);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m128i Vc_CONST permute(__m128i x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm_shuffle_epi32(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m128i Vc_CONST permuteLo(__m128i x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm_shufflelo_epi16(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m128i Vc_CONST permuteHi(__m128i x) {
static_assert(Dst0 >= X4 && Dst1 >= X4 && Dst2 >= X4 && Dst3 >= X4, "Incorrect_Range");
static_assert(Dst0 <= X7 && Dst1 <= X7 && Dst2 <= X7 && Dst3 <= X7, "Incorrect_Range");
return _mm_shufflehi_epi16(x, (Dst0 - X4) + (Dst1 - X4) * 4 + (Dst2 - X4) * 16 + (Dst3 - X4) * 64);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3, VecPos Dst4, VecPos Dst5, VecPos Dst6, VecPos Dst7>
static Vc_ALWAYS_INLINE __m128i Vc_CONST permute(__m128i x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
static_assert(Dst4 >= X4 && Dst5 >= X4 && Dst6 >= X4 && Dst7 >= X4, "Incorrect_Range");
static_assert(Dst4 <= X7 && Dst5 <= X7 && Dst6 <= X7 && Dst7 <= X7, "Incorrect_Range");
if (Dst0 != X0 || Dst1 != X1 || Dst2 != X2 || Dst3 != X3) {
x = _mm_shufflelo_epi16(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
if (Dst4 != X4 || Dst5 != X5 || Dst6 != X6 || Dst7 != X7) {
x = _mm_shufflehi_epi16(x, (Dst4 - X4) + (Dst5 - X4) * 4 + (Dst6 - X4) * 16 + (Dst7 - X4) * 64);
}
return x;
}
}
namespace Reg
{
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m128 Vc_CONST shuffle(__m128 x, __m128 y) {
return Mem::shuffle<Dst0, Dst1, Dst2, Dst3>(x, y);
}
template<VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m128d Vc_CONST shuffle(__m128d x, __m128d y) {
return Mem::shuffle<Dst0, Dst1>(x, y);
}
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m128i Vc_CONST permute(__m128i x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm_shuffle_epi32(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m128i Vc_CONST shuffle(__m128i x, __m128i y) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= Y0 && Dst3 >= Y0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= Y3 && Dst3 <= Y3, "Incorrect_Range");
return _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(x), _mm_castsi128_ps(y), Dst0 + Dst1 * 4 + (Dst2 - Y0) * 16 + (Dst3 - Y0) * 64));
}
template<VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m128d Vc_CONST blend(__m128d x, __m128d y) {
return Mem::blend<Dst0, Dst1>(x, y);
}
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m128 Vc_CONST blend(__m128 x, __m128 y) {
return Mem::blend<Dst0, Dst1, Dst2, Dst3>(x, y);
}
}
}
#endif
#endif
#ifndef VC_SSE_VECTORHELPER_H_
#define VC_SSE_VECTORHELPER_H_ 
#include <limits>
namespace Vc_VERSIONED_NAMESPACE
{
namespace SSE
{
#define Vc_OP0(name,code) static Vc_ALWAYS_INLINE Vc_CONST VectorType name() { return code; }
#define Vc_OP1(name,code) static Vc_ALWAYS_INLINE Vc_CONST VectorType name(const VectorType a) { return code; }
#define Vc_OP2(name,code) static Vc_ALWAYS_INLINE Vc_CONST VectorType name(const VectorType a, const VectorType b) { return code; }
#define Vc_OP3(name,code) static Vc_ALWAYS_INLINE Vc_CONST VectorType name(const VectorType a, const VectorType b, const VectorType c) { return code; }
template<> struct VectorHelper<_M128>
{
typedef _M128 VectorType;
template<typename Flags> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const float *x, typename Flags::EnableIfAligned = nullptr) { return _mm_load_ps(x); }
template<typename Flags> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const float *x, typename Flags::EnableIfUnaligned = nullptr) { return _mm_loadu_ps(x); }
template<typename Flags> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const float *x, typename Flags::EnableIfStreaming = nullptr) { return _mm_stream_load(x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VectorType x, typename Flags::EnableIfAligned = nullptr) { _mm_store_ps(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VectorType x, typename Flags::EnableIfUnalignedNotStreaming = nullptr) { _mm_storeu_ps(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VectorType x, typename Flags::EnableIfStreaming = nullptr) { _mm_stream_ps(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VectorType x, typename Flags::EnableIfUnalignedAndStreaming = nullptr) { _mm_maskmoveu_si128(_mm_castps_si128(x), _mm_setallone_si128(), reinterpret_cast<char *>(mem)); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VectorType x, VectorType m) { _mm_maskmoveu_si128(_mm_castps_si128(x), _mm_castps_si128(m), reinterpret_cast<char *>(mem)); }
Vc_OP0(allone, _mm_setallone_ps())
Vc_OP0(zero, _mm_setzero_ps())
Vc_OP3(blend, blendv_ps(a, b, c))
};
template<> struct VectorHelper<_M128D>
{
typedef _M128D VectorType;
template<typename Flags> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const double *x, typename Flags::EnableIfAligned = nullptr) { return _mm_load_pd(x); }
template<typename Flags> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const double *x, typename Flags::EnableIfUnaligned = nullptr) { return _mm_loadu_pd(x); }
template<typename Flags> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const double *x, typename Flags::EnableIfStreaming = nullptr) { return _mm_stream_load(x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VectorType x, typename Flags::EnableIfAligned = nullptr) { _mm_store_pd(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VectorType x, typename Flags::EnableIfUnalignedNotStreaming = nullptr) { _mm_storeu_pd(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VectorType x, typename Flags::EnableIfStreaming = nullptr) { _mm_stream_pd(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VectorType x, typename Flags::EnableIfUnalignedAndStreaming = nullptr) { _mm_maskmoveu_si128(_mm_castpd_si128(x), _mm_setallone_si128(), reinterpret_cast<char *>(mem)); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VectorType x, VectorType m) { _mm_maskmoveu_si128(_mm_castpd_si128(x), _mm_castpd_si128(m), reinterpret_cast<char *>(mem)); }
Vc_OP0(allone, _mm_setallone_pd())
Vc_OP0(zero, _mm_setzero_pd())
Vc_OP3(blend, blendv_pd(a, b, c))
};
template<> struct VectorHelper<_M128I>
{
typedef _M128I VectorType;
template<typename Flags, typename T> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const T *x, typename Flags::EnableIfAligned = nullptr) { return _mm_load_si128(reinterpret_cast<const VectorType *>(x)); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const T *x, typename Flags::EnableIfUnaligned = nullptr) { return _mm_loadu_si128(reinterpret_cast<const VectorType *>(x)); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE Vc_PURE VectorType load(const T *x, typename Flags::EnableIfStreaming = nullptr) { return _mm_stream_load(x); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VectorType x, typename Flags::EnableIfAligned = nullptr) { _mm_store_si128(reinterpret_cast<VectorType *>(mem), x); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VectorType x, typename Flags::EnableIfUnalignedNotStreaming = nullptr) { _mm_storeu_si128(reinterpret_cast<VectorType *>(mem), x); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VectorType x, typename Flags::EnableIfStreaming = nullptr) { _mm_stream_si128(reinterpret_cast<VectorType *>(mem), x); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VectorType x, typename Flags::EnableIfUnalignedAndStreaming = nullptr) { _mm_maskmoveu_si128(x, _mm_setallone_si128(), reinterpret_cast<char *>(mem)); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VectorType x, VectorType m) { _mm_maskmoveu_si128(x, m, reinterpret_cast<char *>(mem)); }
Vc_OP0(allone, _mm_setallone_si128())
Vc_OP0(zero, _mm_setzero_si128())
Vc_OP3(blend, blendv_epi8(a, b, c))
};
#undef Vc_OP1
#undef Vc_OP2
#undef Vc_OP3
#define Vc_OP1(op) \
static Vc_ALWAYS_INLINE Vc_CONST VectorType op(const VectorType a) { return Vc_CAT2(_mm_##op##_, Vc_SUFFIX)(a); }
#define Vc_OP(op) \
static Vc_ALWAYS_INLINE Vc_CONST VectorType op(const VectorType a, const VectorType b) { return Vc_CAT2(_mm_##op##_ , Vc_SUFFIX)(a, b); }
#define Vc_OP_(op) \
static Vc_ALWAYS_INLINE Vc_CONST VectorType op(const VectorType a, const VectorType b) { return Vc_CAT2(_mm_##op , Vc_SUFFIX)(a, b); }
#define Vc_OPx(op,op2) \
static Vc_ALWAYS_INLINE Vc_CONST VectorType op(const VectorType a, const VectorType b) { return Vc_CAT2(_mm_##op2##_, Vc_SUFFIX)(a, b); }
#define Vc_OP_CAST_(op) \
static Vc_ALWAYS_INLINE Vc_CONST VectorType op(const VectorType a, const VectorType b) { return Vc_CAT2(_mm_castps_, Vc_SUFFIX)( \
_mm_##op##ps(Vc_CAT2(Vc_CAT2(_mm_cast, Vc_SUFFIX), _ps)(a), \
Vc_CAT2(Vc_CAT2(_mm_cast, Vc_SUFFIX), _ps)(b))); \
}
#define Vc_MINMAX \
static Vc_ALWAYS_INLINE Vc_CONST VectorType min(VectorType a, VectorType b) { return Vc_CAT2(_mm_min_, Vc_SUFFIX)(a, b); } \
static Vc_ALWAYS_INLINE Vc_CONST VectorType max(VectorType a, VectorType b) { return Vc_CAT2(_mm_max_, Vc_SUFFIX)(a, b); }
template<> struct VectorHelper<double> {
typedef _M128D VectorType;
typedef double EntryType;
#define Vc_SUFFIX pd
Vc_OP_(or_) Vc_OP_(and_) Vc_OP_(xor_)
static Vc_ALWAYS_INLINE Vc_CONST VectorType notMaskedToZero(VectorType a, _M128 mask) { return Vc_CAT2(_mm_and_, Vc_SUFFIX)(_mm_castps_pd(mask), a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const double a) { return Vc_CAT2(_mm_set1_, Vc_SUFFIX)(a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const double a, const double b) { return Vc_CAT2(_mm_set_, Vc_SUFFIX)(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType zero() { return Vc_CAT2(_mm_setzero_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType one() { return Vc_CAT2(_mm_setone_, Vc_SUFFIX)(); }
#ifdef Vc_IMPL_FMA4
static Vc_ALWAYS_INLINE void fma(VectorType &v1, VectorType v2, VectorType v3) {
v1 = _mm_macc_pd(v1, v2, v3);
}
#else
static inline void fma(VectorType &v1, VectorType v2, VectorType v3) {
VectorType h1 = _mm_and_pd(v1, _mm_load_pd(reinterpret_cast<const double *>(&c_general::highMaskDouble)));
VectorType h2 = _mm_and_pd(v2, _mm_load_pd(reinterpret_cast<const double *>(&c_general::highMaskDouble)));
#if defined(Vc_GCC) && Vc_GCC < 0x40703
asm("":"+x"(h1), "+x"(h2));
#endif
const VectorType l1 = _mm_sub_pd(v1, h1);
const VectorType l2 = _mm_sub_pd(v2, h2);
const VectorType ll = mul(l1, l2);
const VectorType lh = add(mul(l1, h2), mul(h1, l2));
const VectorType hh = mul(h1, h2);
const VectorType lh_lt_v3 = _mm_cmplt_pd(abs(lh), abs(v3));
const VectorType b = blendv_pd(v3, lh, lh_lt_v3);
const VectorType c = blendv_pd(lh, v3, lh_lt_v3);
v1 = add(add(ll, b), add(c, hh));
}
#endif
Vc_OP(add) Vc_OP(sub) Vc_OP(mul)
Vc_OP1(sqrt)
static Vc_ALWAYS_INLINE Vc_CONST VectorType rsqrt(VectorType x) {
return _mm_div_pd(one(), sqrt(x));
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType reciprocal(VectorType x) {
return _mm_div_pd(one(), x);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType isNaN(VectorType x) {
return _mm_cmpunord_pd(x, x);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType isFinite(VectorType x) {
return _mm_cmpord_pd(x, _mm_mul_pd(zero(), x));
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType isInfinite(VectorType x) {
return _mm_castsi128_pd(cmpeq_epi64(_mm_castpd_si128(abs(x)), _mm_castpd_si128(_mm_load_pd(c_log<double>::d(1)))));
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType abs(const VectorType a) {
return Vc_CAT2(_mm_and_, Vc_SUFFIX)(a, _mm_setabsmask_pd());
}
Vc_MINMAX
static Vc_ALWAYS_INLINE Vc_CONST EntryType min(VectorType a) {
a = _mm_min_sd(a, _mm_unpackhi_pd(a, a));
return _mm_cvtsd_f64(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType max(VectorType a) {
a = _mm_max_sd(a, _mm_unpackhi_pd(a, a));
return _mm_cvtsd_f64(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType mul(VectorType a) {
a = _mm_mul_sd(a, _mm_shuffle_pd(a, a, _MM_SHUFFLE2(0, 1)));
return _mm_cvtsd_f64(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType add(VectorType a) {
a = _mm_add_sd(a, _mm_shuffle_pd(a, a, _MM_SHUFFLE2(0, 1)));
return _mm_cvtsd_f64(a);
}
#undef Vc_SUFFIX
static Vc_ALWAYS_INLINE Vc_CONST VectorType round(VectorType a) {
#ifdef Vc_IMPL_SSE4_1
return _mm_round_pd(a, _MM_FROUND_NINT);
#else
return _mm_cvtepi32_pd(_mm_cvtpd_epi32(a));
#endif
}
};
template<> struct VectorHelper<float> {
typedef float EntryType;
typedef _M128 VectorType;
#define Vc_SUFFIX ps
Vc_OP_(or_) Vc_OP_(and_) Vc_OP_(xor_)
static Vc_ALWAYS_INLINE Vc_CONST VectorType notMaskedToZero(VectorType a, _M128 mask) { return Vc_CAT2(_mm_and_, Vc_SUFFIX)(mask, a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const float a) { return Vc_CAT2(_mm_set1_, Vc_SUFFIX)(a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const float a, const float b, const float c, const float d) { return Vc_CAT2(_mm_set_, Vc_SUFFIX)(a, b, c, d); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType zero() { return Vc_CAT2(_mm_setzero_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType one() { return Vc_CAT2(_mm_setone_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST _M128 concat(_M128D a, _M128D b) { return _mm_movelh_ps(_mm_cvtpd_ps(a), _mm_cvtpd_ps(b)); }
#ifdef Vc_IMPL_FMA4
static Vc_ALWAYS_INLINE void fma(VectorType &v1, VectorType v2, VectorType v3) {
v1 = _mm_macc_ps(v1, v2, v3);
}
#else
static inline void fma(VectorType &v1, VectorType v2, VectorType v3) {
__m128d v1_0 = _mm_cvtps_pd(v1);
__m128d v1_1 = _mm_cvtps_pd(_mm_movehl_ps(v1, v1));
__m128d v2_0 = _mm_cvtps_pd(v2);
__m128d v2_1 = _mm_cvtps_pd(_mm_movehl_ps(v2, v2));
__m128d v3_0 = _mm_cvtps_pd(v3);
__m128d v3_1 = _mm_cvtps_pd(_mm_movehl_ps(v3, v3));
v1 = _mm_movelh_ps(
_mm_cvtpd_ps(_mm_add_pd(_mm_mul_pd(v1_0, v2_0), v3_0)),
_mm_cvtpd_ps(_mm_add_pd(_mm_mul_pd(v1_1, v2_1), v3_1)));
}
#endif
Vc_OP(add) Vc_OP(sub) Vc_OP(mul)
Vc_OP1(sqrt) Vc_OP1(rsqrt)
static Vc_ALWAYS_INLINE Vc_CONST VectorType isNaN(VectorType x) {
return _mm_cmpunord_ps(x, x);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType isFinite(VectorType x) {
return _mm_cmpord_ps(x, _mm_mul_ps(zero(), x));
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType isInfinite(VectorType x) {
return _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_castps_si128(abs(x)), _mm_castps_si128(_mm_load_ps(c_log<float>::d(1)))));
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType reciprocal(VectorType x) {
return _mm_rcp_ps(x);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType abs(const VectorType a) {
return Vc_CAT2(_mm_and_, Vc_SUFFIX)(a, _mm_setabsmask_ps());
}
Vc_MINMAX
static Vc_ALWAYS_INLINE Vc_CONST EntryType min(VectorType a) {
a = _mm_min_ps(a, _mm_movehl_ps(a, a));
a = _mm_min_ss(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtss_f32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType max(VectorType a) {
a = _mm_max_ps(a, _mm_movehl_ps(a, a));
a = _mm_max_ss(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtss_f32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType mul(VectorType a) {
a = _mm_mul_ps(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 1, 2, 3)));
a = _mm_mul_ss(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 2, 0, 1)));
return _mm_cvtss_f32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType add(VectorType a) {
a = _mm_add_ps(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 1, 2, 3)));
a = _mm_add_ss(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 2, 0, 1)));
return _mm_cvtss_f32(a);
}
#undef Vc_SUFFIX
static Vc_ALWAYS_INLINE Vc_CONST VectorType round(VectorType a) {
#ifdef Vc_IMPL_SSE4_1
return _mm_round_ps(a, _MM_FROUND_NINT);
#else
return _mm_cvtepi32_ps(_mm_cvtps_epi32(a));
#endif
}
};
template<> struct VectorHelper<int> {
typedef int EntryType;
typedef _M128I VectorType;
#define Vc_SUFFIX si128
Vc_OP_(or_) Vc_OP_(and_) Vc_OP_(xor_)
static Vc_ALWAYS_INLINE Vc_CONST VectorType zero() { return Vc_CAT2(_mm_setzero_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType notMaskedToZero(VectorType a, _M128 mask) { return Vc_CAT2(_mm_and_, Vc_SUFFIX)(_mm_castps_si128(mask), a); }
#undef Vc_SUFFIX
#define Vc_SUFFIX epi32
static Vc_ALWAYS_INLINE Vc_CONST VectorType one() { return Vc_CAT2(_mm_setone_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const int a) { return Vc_CAT2(_mm_set1_, Vc_SUFFIX)(a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const int a, const int b, const int c, const int d) { return Vc_CAT2(_mm_set_, Vc_SUFFIX)(a, b, c, d); }
static Vc_ALWAYS_INLINE void fma(VectorType &v1, VectorType v2, VectorType v3) { v1 = add(mul(v1, v2), v3); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType shiftLeft(VectorType a, int shift) {
return Vc_CAT2(_mm_slli_, Vc_SUFFIX)(a, shift);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType shiftRight(VectorType a, int shift) {
return Vc_CAT2(_mm_srai_, Vc_SUFFIX)(a, shift);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType abs(const VectorType a) { return abs_epi32(a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType min(VectorType a, VectorType b) { return min_epi32(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType max(VectorType a, VectorType b) { return max_epi32(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST EntryType min(VectorType a) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType max(VectorType a) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType add(VectorType a) {
a = add(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = add(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(a);
}
#ifdef Vc_IMPL_SSE4_1
static Vc_ALWAYS_INLINE Vc_CONST VectorType mul(VectorType a, VectorType b) { return _mm_mullo_epi32(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST EntryType mul(VectorType a) {
a = mul(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = mul(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(a);
}
#else
static inline Vc_CONST VectorType mul(const VectorType a, const VectorType b) {
const VectorType aShift = _mm_srli_si128(a, 4);
const VectorType ab02 = _mm_mul_epu32(a, b);
const VectorType bShift = _mm_srli_si128(b, 4);
const VectorType ab13 = _mm_mul_epu32(aShift, bShift);
return _mm_unpacklo_epi32(_mm_shuffle_epi32(ab02, 8), _mm_shuffle_epi32(ab13, 8));
}
#endif
Vc_OP(add) Vc_OP(sub)
#undef Vc_SUFFIX
static Vc_ALWAYS_INLINE Vc_CONST VectorType round(VectorType a) { return a; }
};
template<> struct VectorHelper<unsigned int> {
typedef unsigned int EntryType;
typedef _M128I VectorType;
#define Vc_SUFFIX si128
Vc_OP_CAST_(or_) Vc_OP_CAST_(and_) Vc_OP_CAST_(xor_)
static Vc_ALWAYS_INLINE Vc_CONST VectorType zero() { return Vc_CAT2(_mm_setzero_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType notMaskedToZero(VectorType a, _M128 mask) { return Vc_CAT2(_mm_and_, Vc_SUFFIX)(_mm_castps_si128(mask), a); }
#undef Vc_SUFFIX
#define Vc_SUFFIX epu32
static Vc_ALWAYS_INLINE Vc_CONST VectorType one() { return Vc_CAT2(_mm_setone_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType min(VectorType a, VectorType b) { return min_epu32(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType max(VectorType a, VectorType b) { return max_epu32(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST EntryType min(VectorType a) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType max(VectorType a) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType mul(VectorType a) {
a = mul(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = mul(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType add(VectorType a) {
a = add(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = add(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE void fma(VectorType &v1, VectorType v2, VectorType v3) { v1 = add(mul(v1, v2), v3); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType mul(const VectorType a, const VectorType b) {
return VectorHelper<int>::mul(a, b);
}
#undef Vc_SUFFIX
#define Vc_SUFFIX epi32
static Vc_ALWAYS_INLINE Vc_CONST VectorType shiftLeft(VectorType a, int shift) {
return Vc_CAT2(_mm_slli_, Vc_SUFFIX)(a, shift);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType shiftRight(VectorType a, int shift) {
return Vc_CAT2(_mm_srli_, Vc_SUFFIX)(a, shift);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const unsigned int a) { return Vc_CAT2(_mm_set1_, Vc_SUFFIX)(a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d) { return Vc_CAT2(_mm_set_, Vc_SUFFIX)(a, b, c, d); }
Vc_OP(add) Vc_OP(sub)
#undef Vc_SUFFIX
static Vc_ALWAYS_INLINE Vc_CONST VectorType round(VectorType a) { return a; }
};
template<> struct VectorHelper<signed short> {
typedef _M128I VectorType;
typedef signed short EntryType;
#define Vc_SUFFIX si128
Vc_OP_(or_) Vc_OP_(and_) Vc_OP_(xor_)
static Vc_ALWAYS_INLINE Vc_CONST VectorType zero() { return Vc_CAT2(_mm_setzero_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType notMaskedToZero(VectorType a, _M128 mask) { return Vc_CAT2(_mm_and_, Vc_SUFFIX)(_mm_castps_si128(mask), a); }
static Vc_ALWAYS_INLINE Vc_CONST _M128I concat(_M128I a, _M128I b) { return _mm_packs_epi32(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST _M128I expand0(_M128I x) { return _mm_srai_epi32(_mm_unpacklo_epi16(x, x), 16); }
static Vc_ALWAYS_INLINE Vc_CONST _M128I expand1(_M128I x) { return _mm_srai_epi32(_mm_unpackhi_epi16(x, x), 16); }
#undef Vc_SUFFIX
#define Vc_SUFFIX epi16
static Vc_ALWAYS_INLINE Vc_CONST VectorType one() { return Vc_CAT2(_mm_setone_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType shiftLeft(VectorType a, int shift) {
return Vc_CAT2(_mm_slli_, Vc_SUFFIX)(a, shift);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType shiftRight(VectorType a, int shift) {
return Vc_CAT2(_mm_srai_, Vc_SUFFIX)(a, shift);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const EntryType a) { return Vc_CAT2(_mm_set1_, Vc_SUFFIX)(a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const EntryType a, const EntryType b, const EntryType c, const EntryType d,
const EntryType e, const EntryType f, const EntryType g, const EntryType h) {
return Vc_CAT2(_mm_set_, Vc_SUFFIX)(a, b, c, d, e, f, g, h);
}
static Vc_ALWAYS_INLINE void fma(VectorType &v1, VectorType v2, VectorType v3) {
v1 = add(mul(v1, v2), v3); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType abs(const VectorType a) { return abs_epi16(a); }
Vc_OPx(mul, mullo)
Vc_OP(min) Vc_OP(max)
static Vc_ALWAYS_INLINE Vc_CONST EntryType min(VectorType a) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType max(VectorType a) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType mul(VectorType a) {
a = mul(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = mul(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = mul(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType add(VectorType a) {
a = add(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = add(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = add(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtsi128_si32(a);
}
Vc_OP(add) Vc_OP(sub)
#undef Vc_SUFFIX
static Vc_ALWAYS_INLINE Vc_CONST VectorType round(VectorType a) { return a; }
};
template<> struct VectorHelper<unsigned short> {
typedef _M128I VectorType;
typedef unsigned short EntryType;
#define Vc_SUFFIX si128
Vc_OP_CAST_(or_) Vc_OP_CAST_(and_) Vc_OP_CAST_(xor_)
static Vc_ALWAYS_INLINE Vc_CONST VectorType zero() { return Vc_CAT2(_mm_setzero_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType notMaskedToZero(VectorType a, _M128 mask) { return Vc_CAT2(_mm_and_, Vc_SUFFIX)(_mm_castps_si128(mask), a); }
#ifdef Vc_IMPL_SSE4_1
static Vc_ALWAYS_INLINE Vc_CONST _M128I concat(_M128I a, _M128I b) { return _mm_packus_epi32(a, b); }
#else
static Vc_ALWAYS_INLINE Vc_CONST _M128I concat(_M128I a, _M128I b) {
auto tmp0 = _mm_unpacklo_epi16(a, b);
auto tmp1 = _mm_unpackhi_epi16(a, b);
auto tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
return _mm_unpacklo_epi16(tmp2, tmp3);
}
#endif
static Vc_ALWAYS_INLINE Vc_CONST _M128I expand0(_M128I x) { return _mm_unpacklo_epi16(x, _mm_setzero_si128()); }
static Vc_ALWAYS_INLINE Vc_CONST _M128I expand1(_M128I x) { return _mm_unpackhi_epi16(x, _mm_setzero_si128()); }
#undef Vc_SUFFIX
#define Vc_SUFFIX epu16
static Vc_ALWAYS_INLINE Vc_CONST VectorType one() { return Vc_CAT2(_mm_setone_, Vc_SUFFIX)(); }
#if !defined(USE_INCORRECT_UNSIGNED_COMPARE) || Vc_IMPL_SSE4_1
static Vc_ALWAYS_INLINE Vc_CONST VectorType min(VectorType a, VectorType b) { return min_epu16(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType max(VectorType a, VectorType b) { return max_epu16(a, b); }
#endif
#undef Vc_SUFFIX
#define Vc_SUFFIX epi16
static Vc_ALWAYS_INLINE Vc_CONST VectorType shiftLeft(VectorType a, int shift) {
return Vc_CAT2(_mm_slli_, Vc_SUFFIX)(a, shift);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType shiftRight(VectorType a, int shift) {
return Vc_CAT2(_mm_srli_, Vc_SUFFIX)(a, shift);
}
static Vc_ALWAYS_INLINE void fma(VectorType &v1, VectorType v2, VectorType v3) { v1 = add(mul(v1, v2), v3); }
Vc_OPx(mul, mullo)
#if defined(USE_INCORRECT_UNSIGNED_COMPARE) && !defined(Vc_IMPL_SSE4_1)
Vc_OP(min) Vc_OP(max)
#endif
static Vc_ALWAYS_INLINE Vc_CONST EntryType min(VectorType a) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType max(VectorType a) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType mul(VectorType a) {
a = mul(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = mul(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = mul(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType add(VectorType a) {
a = add(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = add(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)));
a = add(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtsi128_si32(a);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const EntryType a) { return Vc_CAT2(_mm_set1_, Vc_SUFFIX)(a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const EntryType a, const EntryType b, const EntryType c,
const EntryType d, const EntryType e, const EntryType f,
const EntryType g, const EntryType h) {
return Vc_CAT2(_mm_set_, Vc_SUFFIX)(a, b, c, d, e, f, g, h);
}
Vc_OP(add) Vc_OP(sub)
#undef Vc_SUFFIX
static Vc_ALWAYS_INLINE Vc_CONST VectorType round(VectorType a) { return a; }
};
#undef Vc_OP1
#undef Vc_OP
#undef Vc_OP_
#undef Vc_OPx
#undef Vc_OP_CAST_
#undef Vc_MINMAX
}
}
#endif
#ifndef VC_SSE_MASK_H_
#define VC_SSE_MASK_H_ 
#ifndef VC_SSE_DETAIL_H_
#define VC_SSE_DETAIL_H_ 
#ifndef VC_SSE_CASTS_H_
#define VC_SSE_CASTS_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace SSE
{
using uint = unsigned int;
using ushort = unsigned short;
using uchar = unsigned char;
using schar = signed char;
template <typename To, typename From> Vc_ALWAYS_INLINE Vc_CONST To sse_cast(From v)
{
return v;
}
template<> Vc_ALWAYS_INLINE Vc_CONST __m128i sse_cast<__m128i, __m128 >(__m128 v) { return _mm_castps_si128(v); }
template<> Vc_ALWAYS_INLINE Vc_CONST __m128i sse_cast<__m128i, __m128d>(__m128d v) { return _mm_castpd_si128(v); }
template<> Vc_ALWAYS_INLINE Vc_CONST __m128 sse_cast<__m128 , __m128d>(__m128d v) { return _mm_castpd_ps(v); }
template<> Vc_ALWAYS_INLINE Vc_CONST __m128 sse_cast<__m128 , __m128i>(__m128i v) { return _mm_castsi128_ps(v); }
template<> Vc_ALWAYS_INLINE Vc_CONST __m128d sse_cast<__m128d, __m128i>(__m128i v) { return _mm_castsi128_pd(v); }
template<> Vc_ALWAYS_INLINE Vc_CONST __m128d sse_cast<__m128d, __m128 >(__m128 v) { return _mm_castps_pd(v); }
template <typename From, typename To> struct ConvertTag
{
};
template <typename From, typename To>
Vc_INTRINSIC typename VectorTraits<To>::VectorType convert(
typename VectorTraits<From>::VectorType v)
{
return convert(v, ConvertTag<From, To>());
}
Vc_INTRINSIC __m128i convert(__m128 v, ConvertTag<float , int >) { return _mm_cvttps_epi32(v); }
Vc_INTRINSIC __m128i convert(__m128d v, ConvertTag<double, int >) { return _mm_cvttpd_epi32(v); }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<int , int >) { return v; }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<uint , int >) { return v; }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<short , int >) { return _mm_srai_epi32(_mm_unpacklo_epi16(v, v), 16); }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<ushort, int >) { return _mm_srli_epi32(_mm_unpacklo_epi16(v, v), 16); }
Vc_INTRINSIC __m128i convert(__m128 v, ConvertTag<float , uint >) {
return _mm_castps_si128(
blendv_ps(_mm_castsi128_ps(_mm_cvttps_epi32(v)),
_mm_castsi128_ps(_mm_xor_si128(
_mm_cvttps_epi32(_mm_sub_ps(v, _mm_set1_ps(1u << 31))),
_mm_set1_epi32(1 << 31))),
_mm_cmpge_ps(v, _mm_set1_ps(1u << 31))));
}
Vc_INTRINSIC __m128i convert(__m128d v, ConvertTag<double, uint >) {
#ifdef Vc_IMPL_SSE4_1
return _mm_xor_si128(_mm_cvttpd_epi32(_mm_sub_pd(_mm_floor_pd(v), _mm_set1_pd(0x80000000u))),
_mm_cvtsi64_si128(0x8000000080000000ull));
#else
return blendv_epi8(_mm_cvttpd_epi32(v),
_mm_xor_si128(_mm_cvttpd_epi32(_mm_sub_pd(v, _mm_set1_pd(0x80000000u))),
_mm_cvtsi64_si128(0x8000000080000000ull)),
_mm_castpd_si128(_mm_cmpge_pd(v, _mm_set1_pd(0x80000000u))));
#endif
}
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<int , uint >) { return v; }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<uint , uint >) { return v; }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<short , uint >) { return _mm_srai_epi32(_mm_unpacklo_epi16(v, v), 16); }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<ushort, uint >) { return _mm_srli_epi32(_mm_unpacklo_epi16(v, v), 16); }
Vc_INTRINSIC __m128 convert(__m128 v, ConvertTag<float , float >) { return v; }
Vc_INTRINSIC __m128 convert(__m128d v, ConvertTag<double, float >) { return _mm_cvtpd_ps(v); }
Vc_INTRINSIC __m128 convert(__m128i v, ConvertTag<int , float >) { return _mm_cvtepi32_ps(v); }
Vc_INTRINSIC __m128 convert(__m128i v, ConvertTag<uint , float >) {
using namespace SSE;
return blendv_ps(_mm_cvtepi32_ps(v),
_mm_add_ps(_mm_cvtepi32_ps(_mm_and_si128(v, _mm_set1_epi32(0x7ffffe00))),
_mm_add_ps(_mm_set1_ps(1u << 31), _mm_cvtepi32_ps(_mm_and_si128(
v, _mm_set1_epi32(0x000001ff))))),
_mm_castsi128_ps(_mm_cmplt_epi32(v, _mm_setzero_si128())));
}
Vc_INTRINSIC __m128 convert(__m128i v, ConvertTag<short , float >) { return convert(convert(v, ConvertTag<short, int>()), ConvertTag<int, float>()); }
Vc_INTRINSIC __m128 convert(__m128i v, ConvertTag<ushort, float >) { return convert(convert(v, ConvertTag<ushort, int>()), ConvertTag<int, float>()); }
Vc_INTRINSIC __m128d convert(__m128 v, ConvertTag<float , double>) { return _mm_cvtps_pd(v); }
Vc_INTRINSIC __m128d convert(__m128d v, ConvertTag<double, double>) { return v; }
Vc_INTRINSIC __m128d convert(__m128i v, ConvertTag<int , double>) { return _mm_cvtepi32_pd(v); }
Vc_INTRINSIC __m128d convert(__m128i v, ConvertTag<uint , double>) { return _mm_add_pd(_mm_cvtepi32_pd(_mm_xor_si128(v, setmin_epi32())), _mm_set1_pd(1u << 31)); }
Vc_INTRINSIC __m128d convert(__m128i v, ConvertTag<short , double>) { return convert(convert(v, ConvertTag<short, int>()), ConvertTag<int, double>()); }
Vc_INTRINSIC __m128d convert(__m128i v, ConvertTag<ushort, double>) { return convert(convert(v, ConvertTag<ushort, int>()), ConvertTag<int, double>()); }
Vc_INTRINSIC __m128i convert(__m128 v, ConvertTag<float , short >) { return _mm_packs_epi32(_mm_cvttps_epi32(v), _mm_setzero_si128()); }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<int , short >) { return _mm_packs_epi32(v, _mm_setzero_si128()); }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<uint , short >) { return _mm_packs_epi32(v, _mm_setzero_si128()); }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<short , short >) { return v; }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<ushort, short >) { return v; }
Vc_INTRINSIC __m128i convert(__m128d v, ConvertTag<double, short >) { return convert(convert(v, ConvertTag<double, int>()), ConvertTag<int, short>()); }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<int , ushort>) {
auto tmp0 = _mm_unpacklo_epi16(v, _mm_setzero_si128());
auto tmp1 = _mm_unpackhi_epi16(v, _mm_setzero_si128());
auto tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
return _mm_unpacklo_epi16(tmp2, tmp3);
}
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<uint , ushort>) {
auto tmp0 = _mm_unpacklo_epi16(v, _mm_setzero_si128());
auto tmp1 = _mm_unpackhi_epi16(v, _mm_setzero_si128());
auto tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
return _mm_unpacklo_epi16(tmp2, tmp3);
}
Vc_INTRINSIC __m128i convert(__m128 v, ConvertTag<float , ushort>) { return convert(_mm_cvttps_epi32(v), ConvertTag<int, ushort>()); }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<short , ushort>) { return v; }
Vc_INTRINSIC __m128i convert(__m128i v, ConvertTag<ushort, ushort>) { return v; }
Vc_INTRINSIC __m128i convert(__m128d v, ConvertTag<double, ushort>) { return convert(convert(v, ConvertTag<double, int>()), ConvertTag<int, ushort>()); }
}
}
#endif
#ifdef Vc_IMPL_AVX
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename V, typename DstT> struct LoadTag
{
};
class when_aligned
{
public:
template <typename F> constexpr when_aligned(F, typename F::EnableIfAligned = nullptr)
{
}
};
class when_unaligned
{
public:
template <typename F>
constexpr when_unaligned(F, typename F::EnableIfUnaligned = nullptr)
{
}
};
class when_streaming
{
public:
template <typename F>
constexpr when_streaming(F, typename F::EnableIfStreaming = nullptr)
{
}
};
Vc_INTRINSIC __m128 load16(const float *mem, when_aligned)
{
return _mm_load_ps(mem);
}
Vc_INTRINSIC __m128 load16(const float *mem, when_unaligned)
{
return _mm_loadu_ps(mem);
}
Vc_INTRINSIC __m128 load16(const float *mem, when_streaming)
{
return SseIntrinsics::_mm_stream_load(mem);
}
Vc_INTRINSIC __m128d load16(const double *mem, when_aligned)
{
return _mm_load_pd(mem);
}
Vc_INTRINSIC __m128d load16(const double *mem, when_unaligned)
{
return _mm_loadu_pd(mem);
}
Vc_INTRINSIC __m128d load16(const double *mem, when_streaming)
{
return SseIntrinsics::_mm_stream_load(mem);
}
template <class T> Vc_INTRINSIC __m128i load16(const T *mem, when_aligned)
{
static_assert(std::is_integral<T>::value, "load16<T> is only intended for integral T");
return _mm_load_si128(reinterpret_cast<const __m128i *>(mem));
}
template <class T> Vc_INTRINSIC __m128i load16(const T *mem, when_unaligned)
{
static_assert(std::is_integral<T>::value, "load16<T> is only intended for integral T");
return _mm_loadu_si128(reinterpret_cast<const __m128i *>(mem));
}
template <class T> Vc_INTRINSIC __m128i load16(const T *mem, when_streaming)
{
static_assert(std::is_integral<T>::value, "load16<T> is only intended for integral T");
return SseIntrinsics::_mm_stream_load(mem);
}
#ifdef Vc_MSVC
template <typename V, typename DstT, typename F>
Vc_INTRINSIC __m128d load(const double *mem, F f,
enable_if<(std::is_same<DstT, double>::value &&
std::is_same<V, __m128d>::value)> = nullarg)
{
return load16(mem, f);
}
template <typename V, typename DstT, typename F>
Vc_INTRINSIC __m128 load(const float *mem, F f,
enable_if<(std::is_same<DstT, float>::value &&
std::is_same<V, __m128>::value)> = nullarg)
{
return load16(mem, f);
}
template <typename V, typename DstT, typename F>
Vc_INTRINSIC __m128i load(const uint *mem, F f,
enable_if<(std::is_same<DstT, uint>::value &&
std::is_same<V, __m128i>::value)> = nullarg)
{
return load16(mem, f);
}
template <typename V, typename DstT, typename F>
Vc_INTRINSIC __m128i load(const int *mem, F f,
enable_if<(std::is_same<DstT, int>::value &&
std::is_same<V, __m128i>::value)> = nullarg)
{
return load16(mem, f);
}
template <typename V, typename DstT, typename F>
Vc_INTRINSIC __m128i load(const short *mem, F f,
enable_if<(std::is_same<DstT, short>::value &&
std::is_same<V, __m128i>::value)> = nullarg)
{
return load16(mem, f);
}
template <typename V, typename DstT, typename F>
Vc_INTRINSIC __m128i load(const ushort *mem, F f,
enable_if<(std::is_same<DstT, ushort>::value &&
std::is_same<V, __m128i>::value)> = nullarg)
{
return load16(mem, f);
}
#endif
template <typename V, typename DstT, typename SrcT, typename Flags,
typename = enable_if<
#ifdef Vc_MSVC
!std::is_same<DstT, SrcT>::value &&
#endif
(!std::is_integral<DstT>::value || !std::is_integral<SrcT>::value ||
sizeof(DstT) >= sizeof(SrcT))>>
Vc_INTRINSIC V load(const SrcT *mem, Flags flags)
{
return load(mem, flags, LoadTag<V, DstT>());
}
template <typename V, typename T, typename Flags>
Vc_INTRINSIC V
load(const T *mem, Flags, LoadTag<V, T>, enable_if<sizeof(V) == 16> = nullarg)
{
return SSE::VectorHelper<V>::template load<Flags>(mem);
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const ushort *mem, Flags, LoadTag<__m128i, short>)
{
return SSE::VectorHelper<__m128i>::load<Flags>(mem);
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const uchar *mem, Flags, LoadTag<__m128i, short>)
{
return SSE::cvtepu8_epi16(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const schar *mem, Flags, LoadTag<__m128i, short>)
{
return SSE::cvtepi8_epi16(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const uchar *mem, Flags, LoadTag<__m128i, ushort>)
{
return SSE::cvtepu8_epi16(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const uint *mem, Flags, LoadTag<__m128i, int>)
{
return SSE::VectorHelper<__m128i>::load<Flags>(mem);
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const ushort *mem, Flags, LoadTag<__m128i, int>)
{
return SSE::cvtepu16_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const short *mem, Flags, LoadTag<__m128i, int>)
{
return SSE::cvtepi16_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const uchar *mem, Flags, LoadTag<__m128i, int>)
{
return SSE::cvtepu8_epi32(_mm_cvtsi32_si128(*aliasing_cast<int>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const schar *mem, Flags, LoadTag<__m128i, int>)
{
return SSE::cvtepi8_epi32(_mm_cvtsi32_si128(*aliasing_cast<int>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const ushort *mem, Flags, LoadTag<__m128i, uint>)
{
return SSE::cvtepu16_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128i load(const uchar *mem, Flags, LoadTag<__m128i, uint>)
{
return SSE::cvtepu8_epi32(_mm_cvtsi32_si128(*aliasing_cast<int>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128d load(const float *mem, Flags, LoadTag<__m128d, double>)
{
return SSE::convert<float, double>(
_mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<const __m64 *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128d load(const uint *mem, Flags, LoadTag<__m128d, double>)
{
return SSE::convert<uint, double>(
_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128d load(const int *mem, Flags, LoadTag<__m128d, double>)
{
return SSE::convert<int, double>(
_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128d load(const ushort *mem, Flags, LoadTag<__m128d, double>)
{
return SSE::convert<ushort, double>(
_mm_cvtsi32_si128(*aliasing_cast<int>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128d load(const short *mem, Flags, LoadTag<__m128d, double>)
{
return SSE::convert<short, double>(
_mm_cvtsi32_si128(*aliasing_cast<int>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128d load(const uchar *mem, Flags, LoadTag<__m128d, double>)
{
return SSE::convert<uchar, double>(
_mm_set1_epi16(*aliasing_cast<short>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128d load(const schar *mem, Flags, LoadTag<__m128d, double>)
{
return SSE::convert<char, double>(
_mm_set1_epi16(*aliasing_cast<short>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m128 load(const double *mem, Flags, LoadTag<__m128, float>)
{
#ifdef Vc_IMPL_AVX
if (Flags::IsUnaligned) {
return _mm256_cvtpd_ps(_mm256_loadu_pd(mem));
} else if (Flags::IsStreaming) {
return _mm256_cvtpd_ps(AvxIntrinsics::stream_load<__m256d>(mem));
} else {
return _mm256_cvtpd_ps(_mm256_load_pd(mem));
}
#else
return _mm_movelh_ps(_mm_cvtpd_ps(SSE::VectorHelper<__m128d>::load<Flags>(&mem[0])),
_mm_cvtpd_ps(SSE::VectorHelper<__m128d>::load<Flags>(&mem[2])));
#endif
}
template <typename Flags>
Vc_INTRINSIC __m128 load(const uint *mem, Flags f, LoadTag<__m128, float>)
{
return SSE::convert<uint, float>(load<__m128i, uint>(mem, f));
}
template <typename T, typename Flags,
typename = enable_if<!std::is_same<T, float>::value>>
Vc_INTRINSIC __m128 load(const T *mem, Flags f, LoadTag<__m128, float>)
{
return _mm_cvtepi32_ps(load<__m128i, int>(mem, f));
}
template <int amount, typename T>
Vc_INTRINSIC Vc_CONST enable_if<amount == 0, T> shifted(T k)
{
return k;
}
template <int amount, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(sizeof(T) == 16 && amount > 0), T> shifted(T k)
{
return _mm_srli_si128(k, amount);
}
template <int amount, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(sizeof(T) == 16 && amount < 0), T> shifted(T k)
{
return _mm_slli_si128(k, -amount);
}
template <typename T, int Size> Vc_INTRINSIC Vc_CONST const T *IndexesFromZero()
{
if (Size == 4) {
return reinterpret_cast<const T *>(SSE::_IndexesFromZero4);
} else if (Size == 8) {
return reinterpret_cast<const T *>(SSE::_IndexesFromZero8);
} else if (Size == 16) {
return reinterpret_cast<const T *>(SSE::_IndexesFromZero16);
}
return 0;
}
Vc_INTRINSIC Vc_CONST unsigned int popcnt4(unsigned int n)
{
#ifdef Vc_IMPL_POPCNT
return _mm_popcnt_u32(n);
#else
n = (n & 0x5U) + ((n >> 1) & 0x5U);
n = (n & 0x3U) + ((n >> 2) & 0x3U);
return n;
#endif
}
Vc_INTRINSIC Vc_CONST unsigned int popcnt8(unsigned int n)
{
#ifdef Vc_IMPL_POPCNT
return _mm_popcnt_u32(n);
#else
n = (n & 0x55U) + ((n >> 1) & 0x55U);
n = (n & 0x33U) + ((n >> 2) & 0x33U);
n = (n & 0x0fU) + ((n >> 4) & 0x0fU);
return n;
#endif
}
Vc_INTRINSIC Vc_CONST unsigned int popcnt16(unsigned int n)
{
#ifdef Vc_IMPL_POPCNT
return _mm_popcnt_u32(n);
#else
n = (n & 0x5555U) + ((n >> 1) & 0x5555U);
n = (n & 0x3333U) + ((n >> 2) & 0x3333U);
n = (n & 0x0f0fU) + ((n >> 4) & 0x0f0fU);
n = (n & 0x00ffU) + ((n >> 8) & 0x00ffU);
return n;
#endif
}
Vc_INTRINSIC Vc_CONST unsigned int popcnt32(unsigned int n)
{
#ifdef Vc_IMPL_POPCNT
return _mm_popcnt_u32(n);
#else
n = (n & 0x55555555U) + ((n >> 1) & 0x55555555U);
n = (n & 0x33333333U) + ((n >> 2) & 0x33333333U);
n = (n & 0x0f0f0f0fU) + ((n >> 4) & 0x0f0f0f0fU);
n = (n & 0x00ff00ffU) + ((n >> 8) & 0x00ff00ffU);
n = (n & 0x0000ffffU) + ((n >>16) & 0x0000ffffU);
return n;
#endif
}
template<size_t From, size_t To, typename R> Vc_INTRINSIC Vc_CONST R mask_cast(__m128i k)
{
static_assert(From == To, "Incorrect mask cast.");
static_assert(std::is_same<R, __m128>::value, "Incorrect mask cast.");
return SSE::sse_cast<__m128>(k);
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<2, 4, __m128>(__m128i k)
{
return SSE::sse_cast<__m128>(_mm_packs_epi16(k, _mm_setzero_si128()));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<2, 8, __m128>(__m128i k)
{
return SSE::sse_cast<__m128>(
_mm_packs_epi16(_mm_packs_epi16(k, _mm_setzero_si128()), _mm_setzero_si128()));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<4, 2, __m128>(__m128i k)
{
return SSE::sse_cast<__m128>(_mm_unpacklo_epi32(k, k));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<4, 8, __m128>(__m128i k)
{
return SSE::sse_cast<__m128>(_mm_packs_epi16(k, _mm_setzero_si128()));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<8, 2, __m128>(__m128i k)
{
const auto tmp = _mm_unpacklo_epi16(k, k);
return SSE::sse_cast<__m128>(_mm_unpacklo_epi32(tmp, tmp));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<8, 4, __m128>(__m128i k)
{
return SSE::sse_cast<__m128>(_mm_unpacklo_epi16(k, k));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<16, 8, __m128>(__m128i k)
{
return SSE::sse_cast<__m128>(_mm_unpacklo_epi8(k, k));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<16, 4, __m128>(__m128i k)
{
const auto tmp = SSE::sse_cast<__m128i>(mask_cast<16, 8, __m128>(k));
return SSE::sse_cast<__m128>(_mm_unpacklo_epi16(tmp, tmp));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<16, 2, __m128>(__m128i k)
{
const auto tmp = SSE::sse_cast<__m128i>(mask_cast<16, 4, __m128>(k));
return SSE::sse_cast<__m128>(_mm_unpacklo_epi32(tmp, tmp));
}
template <typename V> Vc_INTRINSIC_L Vc_CONST_L V allone() Vc_INTRINSIC_R Vc_CONST_R;
template<> Vc_INTRINSIC Vc_CONST __m128 allone<__m128 >() { return SSE::_mm_setallone_ps(); }
template<> Vc_INTRINSIC Vc_CONST __m128i allone<__m128i>() { return SSE::_mm_setallone_si128(); }
template<> Vc_INTRINSIC Vc_CONST __m128d allone<__m128d>() { return SSE::_mm_setallone_pd(); }
template <typename V> inline V zero();
template<> Vc_INTRINSIC Vc_CONST __m128 zero<__m128 >() { return _mm_setzero_ps(); }
template<> Vc_INTRINSIC Vc_CONST __m128i zero<__m128i>() { return _mm_setzero_si128(); }
template<> Vc_INTRINSIC Vc_CONST __m128d zero<__m128d>() { return _mm_setzero_pd(); }
Vc_ALWAYS_INLINE Vc_CONST __m128 negate(__m128 v, std::integral_constant<std::size_t, 4>)
{
return _mm_xor_ps(v, SSE::_mm_setsignmask_ps());
}
Vc_ALWAYS_INLINE Vc_CONST __m128d negate(__m128d v, std::integral_constant<std::size_t, 8>)
{
return _mm_xor_pd(v, SSE::_mm_setsignmask_pd());
}
Vc_ALWAYS_INLINE Vc_CONST __m128i negate(__m128i v, std::integral_constant<std::size_t, 4>)
{
#ifdef Vc_IMPL_SSSE3
return _mm_sign_epi32(v, allone<__m128i>());
#else
return _mm_sub_epi32(_mm_setzero_si128(), v);
#endif
}
Vc_ALWAYS_INLINE Vc_CONST __m128i negate(__m128i v, std::integral_constant<std::size_t, 2>)
{
#ifdef Vc_IMPL_SSSE3
return _mm_sign_epi16(v, allone<__m128i>());
#else
return _mm_sub_epi16(_mm_setzero_si128(), v);
#endif
}
Vc_INTRINSIC __m128 xor_(__m128 a, __m128 b) { return _mm_xor_ps(a, b); }
Vc_INTRINSIC __m128d xor_(__m128d a, __m128d b) { return _mm_xor_pd(a, b); }
Vc_INTRINSIC __m128i xor_(__m128i a, __m128i b) { return _mm_xor_si128(a, b); }
Vc_INTRINSIC __m128 or_(__m128 a, __m128 b) { return _mm_or_ps(a, b); }
Vc_INTRINSIC __m128d or_(__m128d a, __m128d b) { return _mm_or_pd(a, b); }
Vc_INTRINSIC __m128i or_(__m128i a, __m128i b) { return _mm_or_si128(a, b); }
Vc_INTRINSIC __m128 and_(__m128 a, __m128 b) { return _mm_and_ps(a, b); }
Vc_INTRINSIC __m128d and_(__m128d a, __m128d b) { return _mm_and_pd(a, b); }
Vc_INTRINSIC __m128i and_(__m128i a, __m128i b) { return _mm_and_si128(a, b); }
Vc_INTRINSIC __m128 andnot_(__m128 a, __m128 b) { return _mm_andnot_ps(a, b); }
Vc_INTRINSIC __m128d andnot_(__m128d a, __m128d b) { return _mm_andnot_pd(a, b); }
Vc_INTRINSIC __m128i andnot_(__m128i a, __m128i b) { return _mm_andnot_si128(a, b); }
Vc_INTRINSIC __m128 not_(__m128 a) { return andnot_(a, allone<__m128 >()); }
Vc_INTRINSIC __m128d not_(__m128d a) { return andnot_(a, allone<__m128d>()); }
Vc_INTRINSIC __m128i not_(__m128i a) { return andnot_(a, allone<__m128i>()); }
Vc_INTRINSIC __m128 add(__m128 a, __m128 b, float) { return _mm_add_ps(a, b); }
Vc_INTRINSIC __m128d add(__m128d a, __m128d b, double) { return _mm_add_pd(a, b); }
Vc_INTRINSIC __m128i add(__m128i a, __m128i b, int) { return _mm_add_epi32(a, b); }
Vc_INTRINSIC __m128i add(__m128i a, __m128i b, uint) { return _mm_add_epi32(a, b); }
Vc_INTRINSIC __m128i add(__m128i a, __m128i b, short) { return _mm_add_epi16(a, b); }
Vc_INTRINSIC __m128i add(__m128i a, __m128i b, ushort) { return _mm_add_epi16(a, b); }
Vc_INTRINSIC __m128i add(__m128i a, __m128i b, schar) { return _mm_add_epi8 (a, b); }
Vc_INTRINSIC __m128i add(__m128i a, __m128i b, uchar) { return _mm_add_epi8 (a, b); }
Vc_INTRINSIC __m128 sub(__m128 a, __m128 b, float) { return _mm_sub_ps(a, b); }
Vc_INTRINSIC __m128d sub(__m128d a, __m128d b, double) { return _mm_sub_pd(a, b); }
Vc_INTRINSIC __m128i sub(__m128i a, __m128i b, int) { return _mm_sub_epi32(a, b); }
Vc_INTRINSIC __m128i sub(__m128i a, __m128i b, uint) { return _mm_sub_epi32(a, b); }
Vc_INTRINSIC __m128i sub(__m128i a, __m128i b, short) { return _mm_sub_epi16(a, b); }
Vc_INTRINSIC __m128i sub(__m128i a, __m128i b, ushort) { return _mm_sub_epi16(a, b); }
Vc_INTRINSIC __m128i sub(__m128i a, __m128i b, schar) { return _mm_sub_epi8 (a, b); }
Vc_INTRINSIC __m128i sub(__m128i a, __m128i b, uchar) { return _mm_sub_epi8 (a, b); }
Vc_INTRINSIC __m128 mul(__m128 a, __m128 b, float) { return _mm_mul_ps(a, b); }
Vc_INTRINSIC __m128d mul(__m128d a, __m128d b, double) { return _mm_mul_pd(a, b); }
Vc_INTRINSIC __m128i mul(__m128i a, __m128i b, int) {
#ifdef Vc_IMPL_SSE4_1
return _mm_mullo_epi32(a, b);
#else
const __m128i aShift = _mm_srli_si128(a, 4);
const __m128i ab02 = _mm_mul_epu32(a, b);
const __m128i bShift = _mm_srli_si128(b, 4);
const __m128i ab13 = _mm_mul_epu32(aShift, bShift);
return _mm_unpacklo_epi32(_mm_shuffle_epi32(ab02, 8), _mm_shuffle_epi32(ab13, 8));
#endif
}
Vc_INTRINSIC __m128i mul(__m128i a, __m128i b, uint) { return mul(a, b, int()); }
Vc_INTRINSIC __m128i mul(__m128i a, __m128i b, short) { return _mm_mullo_epi16(a, b); }
Vc_INTRINSIC __m128i mul(__m128i a, __m128i b, ushort) { return _mm_mullo_epi16(a, b); }
Vc_INTRINSIC __m128i mul(__m128i a, __m128i b, schar) {
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
using B = Common::BuiltinType<schar, 16>;
const auto x = aliasing_cast<B>(a) * aliasing_cast<B>(b);
return reinterpret_cast<const __m128i &>(x);
#else
return or_(
and_(_mm_mullo_epi16(a, b), _mm_slli_epi16(allone<__m128i>(), 8)),
_mm_slli_epi16(_mm_mullo_epi16(_mm_srli_si128(a, 1), _mm_srli_si128(b, 1)), 8));
#endif
}
Vc_INTRINSIC __m128i mul(__m128i a, __m128i b, uchar) {
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
using B = Common::BuiltinType<uchar, 16>;
const auto x = aliasing_cast<B>(a) * aliasing_cast<B>(b);
return reinterpret_cast<const __m128i &>(x);
#else
return or_(
and_(_mm_mullo_epi16(a, b), _mm_slli_epi16(allone<__m128i>(), 8)),
_mm_slli_epi16(_mm_mullo_epi16(_mm_srli_si128(a, 1), _mm_srli_si128(b, 1)), 8));
#endif
}
Vc_INTRINSIC __m128 div(__m128 a, __m128 b, float) { return _mm_div_ps(a, b); }
Vc_INTRINSIC __m128d div(__m128d a, __m128d b, double) { return _mm_div_pd(a, b); }
Vc_INTRINSIC __m128 min(__m128 a, __m128 b, float) { return _mm_min_ps(a, b); }
Vc_INTRINSIC __m128d min(__m128d a, __m128d b, double) { return _mm_min_pd(a, b); }
Vc_INTRINSIC __m128i min(__m128i a, __m128i b, int) { return SSE::min_epi32(a, b); }
Vc_INTRINSIC __m128i min(__m128i a, __m128i b, uint) { return SSE::min_epu32(a, b); }
Vc_INTRINSIC __m128i min(__m128i a, __m128i b, short) { return _mm_min_epi16(a, b); }
Vc_INTRINSIC __m128i min(__m128i a, __m128i b, ushort) { return SSE::min_epu16(a, b); }
Vc_INTRINSIC __m128i min(__m128i a, __m128i b, schar) { return SSE::min_epi8 (a, b); }
Vc_INTRINSIC __m128i min(__m128i a, __m128i b, uchar) { return _mm_min_epu8 (a, b); }
Vc_INTRINSIC __m128 max(__m128 a, __m128 b, float) { return _mm_max_ps(a, b); }
Vc_INTRINSIC __m128d max(__m128d a, __m128d b, double) { return _mm_max_pd(a, b); }
Vc_INTRINSIC __m128i max(__m128i a, __m128i b, int) { return SSE::max_epi32(a, b); }
Vc_INTRINSIC __m128i max(__m128i a, __m128i b, uint) { return SSE::max_epu32(a, b); }
Vc_INTRINSIC __m128i max(__m128i a, __m128i b, short) { return _mm_max_epi16(a, b); }
Vc_INTRINSIC __m128i max(__m128i a, __m128i b, ushort) { return SSE::max_epu16(a, b); }
Vc_INTRINSIC __m128i max(__m128i a, __m128i b, schar) { return SSE::max_epi8 (a, b); }
Vc_INTRINSIC __m128i max(__m128i a, __m128i b, uchar) { return _mm_max_epu8 (a, b); }
Vc_INTRINSIC float add(__m128 a, float) {
a = _mm_add_ps(a, _mm_movehl_ps(a, a));
a = _mm_add_ss(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtss_f32(a);
}
Vc_INTRINSIC double add(__m128d a, double) {
a = _mm_add_sd(a, _mm_unpackhi_pd(a, a));
return _mm_cvtsd_f64(a);
}
Vc_INTRINSIC int add(__m128i a, int) {
a = add(a, _mm_srli_si128(a, 8), int());
a = add(a, _mm_srli_si128(a, 4), int());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC uint add(__m128i a, uint) { return add(a, int()); }
Vc_INTRINSIC short add(__m128i a, short) {
a = add(a, _mm_srli_si128(a, 8), short());
a = add(a, _mm_srli_si128(a, 4), short());
a = add(a, _mm_srli_si128(a, 2), short());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC ushort add(__m128i a, ushort) { return add(a, short()); }
Vc_INTRINSIC schar add(__m128i a, schar) {
a = add(a, _mm_srli_si128(a, 8), schar());
a = add(a, _mm_srli_si128(a, 4), schar());
a = add(a, _mm_srli_si128(a, 2), schar());
a = add(a, _mm_srli_si128(a, 1), schar());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC uchar add(__m128i a, uchar) { return add(a, schar()); }
Vc_INTRINSIC float mul(__m128 a, float) {
a = _mm_mul_ps(a, _mm_movehl_ps(a, a));
a = _mm_mul_ss(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtss_f32(a);
}
Vc_INTRINSIC double mul(__m128d a, double) {
a = _mm_mul_sd(a, _mm_unpackhi_pd(a, a));
return _mm_cvtsd_f64(a);
}
Vc_INTRINSIC int mul(__m128i a, int) {
a = mul(a, _mm_srli_si128(a, 8), int());
a = mul(a, _mm_srli_si128(a, 4), int());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC uint mul(__m128i a, uint) { return mul(a, int()); }
Vc_INTRINSIC short mul(__m128i a, short) {
a = mul(a, _mm_srli_si128(a, 8), short());
a = mul(a, _mm_srli_si128(a, 4), short());
a = mul(a, _mm_srli_si128(a, 2), short());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC ushort mul(__m128i a, ushort) { return mul(a, short()); }
Vc_INTRINSIC schar mul(__m128i a, schar) {
const __m128i s0 = _mm_srai_epi16(a, 1);
const __m128i s1 = Detail::and_(a, _mm_set1_epi32(0x0f0f0f0f));
return mul(mul(s0, s1, short()), short());
}
Vc_INTRINSIC uchar mul(__m128i a, uchar) { return mul(a, schar()); }
Vc_INTRINSIC float min(__m128 a, float) {
a = _mm_min_ps(a, _mm_movehl_ps(a, a));
a = _mm_min_ss(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtss_f32(a);
}
Vc_INTRINSIC double min(__m128d a, double) {
a = _mm_min_sd(a, _mm_unpackhi_pd(a, a));
return _mm_cvtsd_f64(a);
}
Vc_INTRINSIC int min(__m128i a, int) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), int());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), int());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC uint min(__m128i a, uint) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), uint());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), uint());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC short min(__m128i a, short) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), short());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), short());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)), short());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC ushort min(__m128i a, ushort) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), ushort());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), ushort());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)), ushort());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC schar min(__m128i a, schar) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), schar());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), schar());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)), schar());
return std::min(schar(_mm_cvtsi128_si32(a) >> 8), schar(_mm_cvtsi128_si32(a)));
}
Vc_INTRINSIC uchar min(__m128i a, uchar) {
a = min(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), schar());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), schar());
a = min(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)), schar());
return std::min((_mm_cvtsi128_si32(a) >> 8) & 0xff, _mm_cvtsi128_si32(a) & 0xff);
}
Vc_INTRINSIC float max(__m128 a, float) {
a = _mm_max_ps(a, _mm_movehl_ps(a, a));
a = _mm_max_ss(a, _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtss_f32(a);
}
Vc_INTRINSIC double max(__m128d a, double) {
a = _mm_max_sd(a, _mm_unpackhi_pd(a, a));
return _mm_cvtsd_f64(a);
}
Vc_INTRINSIC int max(__m128i a, int) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), int());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), int());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC uint max(__m128i a, uint) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), uint());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), uint());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC short max(__m128i a, short) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), short());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), short());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)), short());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC ushort max(__m128i a, ushort) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), ushort());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), ushort());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)), ushort());
return _mm_cvtsi128_si32(a);
}
Vc_INTRINSIC schar max(__m128i a, schar) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), schar());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), schar());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)), schar());
return std::max(schar(_mm_cvtsi128_si32(a) >> 8), schar(_mm_cvtsi128_si32(a)));
}
Vc_INTRINSIC uchar max(__m128i a, uchar) {
a = max(a, _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 0, 3, 2)), schar());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 0, 3, 2)), schar());
a = max(a, _mm_shufflelo_epi16(a, _MM_SHUFFLE(1, 1, 1, 1)), schar());
return std::max((_mm_cvtsi128_si32(a) >> 8) & 0xff, _mm_cvtsi128_si32(a) & 0xff);
}
template <Vc::Implementation, typename T>
Vc_CONST_L SSE::Vector<T> sorted(SSE::Vector<T> x) Vc_CONST_R;
template <typename T> Vc_INTRINSIC Vc_CONST SSE::Vector<T> sorted(SSE::Vector<T> x)
{
static_assert(!CurrentImplementation::is(ScalarImpl),
"Detail::sorted can only be instantiated if a non-Scalar "
"implementation is selected.");
return sorted < CurrentImplementation::is_between(SSE2Impl, SSSE3Impl)
? SSE2Impl
: CurrentImplementation::is_between(SSE41Impl, SSE42Impl)
? SSE41Impl
: CurrentImplementation::current() > (x);
}
template <typename V> constexpr int sanitize(int n)
{
return (n >= int(sizeof(V)) || n <= -int(sizeof(V))) ? 0 : n;
}
template <typename T, size_t N, typename V>
static Vc_INTRINSIC Vc_CONST enable_if<(sizeof(V) == 16), V> rotated(V v, int amount)
{
using namespace SSE;
switch (static_cast<unsigned int>(amount) % N) {
case 0:
return v;
case 1:
return sse_cast<V>(_mm_alignr_epi8(v, v, sanitize<V>(1 * sizeof(T))));
case 2:
return sse_cast<V>(_mm_alignr_epi8(v, v, sanitize<V>(2 * sizeof(T))));
case 3:
return sse_cast<V>(_mm_alignr_epi8(v, v, sanitize<V>(3 * sizeof(T))));
case 4:
return sse_cast<V>(_mm_alignr_epi8(v, v, sanitize<V>(4 * sizeof(T))));
case 5:
return sse_cast<V>(_mm_alignr_epi8(v, v, sanitize<V>(5 * sizeof(T))));
case 6:
return sse_cast<V>(_mm_alignr_epi8(v, v, sanitize<V>(6 * sizeof(T))));
case 7:
return sse_cast<V>(_mm_alignr_epi8(v, v, sanitize<V>(7 * sizeof(T))));
}
return sse_cast<V>(_mm_setzero_si128());
}
template<typename V, size_t Size, size_t VSize> struct InterleaveImpl;
template<typename V> struct InterleaveImpl<V, 8, 16> {
template<typename I> static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
const __m128i tmp0 = _mm_unpacklo_epi16(v0.data(), v1.data());
const __m128i tmp1 = _mm_unpackhi_epi16(v0.data(), v1.data());
#ifdef __x86_64__
const long long tmp00 = _mm_cvtsi128_si64(tmp0);
const long long tmp01 = _mm_cvtsi128_si64(_mm_unpackhi_epi64(tmp0, tmp0));
const long long tmp10 = _mm_cvtsi128_si64(tmp1);
const long long tmp11 = _mm_cvtsi128_si64(_mm_unpackhi_epi64(tmp1, tmp1));
aliasing_cast<int>(data[i[0]]) = tmp00;
aliasing_cast<int>(data[i[1]]) = tmp00 >> 32;
aliasing_cast<int>(data[i[2]]) = tmp01;
aliasing_cast<int>(data[i[3]]) = tmp01 >> 32;
aliasing_cast<int>(data[i[4]]) = tmp10;
aliasing_cast<int>(data[i[5]]) = tmp10 >> 32;
aliasing_cast<int>(data[i[6]]) = tmp11;
aliasing_cast<int>(data[i[7]]) = tmp11 >> 32;
#elif defined(Vc_IMPL_SSE4_1)
using namespace SseIntrinsics;
aliasing_cast<int>(data[i[0]]) = _mm_cvtsi128_si32(tmp0);
aliasing_cast<int>(data[i[1]]) = extract_epi32<1>(tmp0);
aliasing_cast<int>(data[i[2]]) = extract_epi32<2>(tmp0);
aliasing_cast<int>(data[i[3]]) = extract_epi32<3>(tmp0);
aliasing_cast<int>(data[i[4]]) = _mm_cvtsi128_si32(tmp1);
aliasing_cast<int>(data[i[5]]) = extract_epi32<1>(tmp1);
aliasing_cast<int>(data[i[6]]) = extract_epi32<2>(tmp1);
aliasing_cast<int>(data[i[7]]) = extract_epi32<3>(tmp1);
#else
aliasing_cast<int>(data[i[0]]) = _mm_cvtsi128_si32(tmp0);
aliasing_cast<int>(data[i[1]]) = _mm_cvtsi128_si32(_mm_srli_si128(tmp0, 4));
aliasing_cast<int>(data[i[2]]) = _mm_cvtsi128_si32(_mm_srli_si128(tmp0, 8));
aliasing_cast<int>(data[i[3]]) = _mm_cvtsi128_si32(_mm_srli_si128(tmp0, 12));
aliasing_cast<int>(data[i[4]]) = _mm_cvtsi128_si32(tmp1);
aliasing_cast<int>(data[i[5]]) = _mm_cvtsi128_si32(_mm_srli_si128(tmp1, 4));
aliasing_cast<int>(data[i[6]]) = _mm_cvtsi128_si32(_mm_srli_si128(tmp1, 8));
aliasing_cast<int>(data[i[7]]) = _mm_cvtsi128_si32(_mm_srli_si128(tmp1, 12));
#endif
}
static inline void interleave(typename V::EntryType *const data, const Common::SuccessiveEntries<2> &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
const __m128i tmp0 = _mm_unpacklo_epi16(v0.data(), v1.data());
const __m128i tmp1 = _mm_unpackhi_epi16(v0.data(), v1.data());
V(tmp0).store(&data[i[0]], Vc::Unaligned);
V(tmp1).store(&data[i[4]], Vc::Unaligned);
}
template<typename I> static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1, const typename V::AsArg v2)
{
#if defined Vc_USE_MASKMOV_SCATTER && !defined Vc_MSVC
const __m64 mask = _mm_set_pi16(0, -1, -1, -1);
const __m128i tmp0 = _mm_unpacklo_epi16(v0.data(), v2.data());
const __m128i tmp1 = _mm_unpackhi_epi16(v0.data(), v2.data());
const __m128i tmp2 = _mm_unpacklo_epi16(v1.data(), v1.data());
const __m128i tmp3 = _mm_unpackhi_epi16(v1.data(), v1.data());
const __m128i tmp4 = _mm_unpacklo_epi16(tmp0, tmp2);
const __m128i tmp5 = _mm_unpackhi_epi16(tmp0, tmp2);
const __m128i tmp6 = _mm_unpacklo_epi16(tmp1, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp1, tmp3);
_mm_maskmove_si64(_mm_movepi64_pi64(tmp4), mask, reinterpret_cast<char *>(&data[i[0]]));
_mm_maskmove_si64(_mm_movepi64_pi64(_mm_srli_si128(tmp4, 8)), mask, reinterpret_cast<char *>(&data[i[1]]));
_mm_maskmove_si64(_mm_movepi64_pi64(tmp5), mask, reinterpret_cast<char *>(&data[i[2]]));
_mm_maskmove_si64(_mm_movepi64_pi64(_mm_srli_si128(tmp5, 8)), mask, reinterpret_cast<char *>(&data[i[3]]));
_mm_maskmove_si64(_mm_movepi64_pi64(tmp6), mask, reinterpret_cast<char *>(&data[i[4]]));
_mm_maskmove_si64(_mm_movepi64_pi64(_mm_srli_si128(tmp6, 8)), mask, reinterpret_cast<char *>(&data[i[5]]));
_mm_maskmove_si64(_mm_movepi64_pi64(tmp7), mask, reinterpret_cast<char *>(&data[i[6]]));
_mm_maskmove_si64(_mm_movepi64_pi64(_mm_srli_si128(tmp7, 8)), mask, reinterpret_cast<char *>(&data[i[7]]));
_mm_empty();
#else
interleave(data, i, v0, v1);
v2.scatter(data + 2, i);
#endif
}
template<typename I> static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
const __m128i tmp0 = _mm_unpacklo_epi16(v0.data(), v2.data());
const __m128i tmp1 = _mm_unpackhi_epi16(v0.data(), v2.data());
const __m128i tmp2 = _mm_unpacklo_epi16(v1.data(), v3.data());
const __m128i tmp3 = _mm_unpackhi_epi16(v1.data(), v3.data());
const __m128i tmp4 = _mm_unpacklo_epi16(tmp0, tmp2);
const __m128i tmp5 = _mm_unpackhi_epi16(tmp0, tmp2);
const __m128i tmp6 = _mm_unpacklo_epi16(tmp1, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp1, tmp3);
_mm_storel_epi64(reinterpret_cast<__m128i *>(&data[i[0]]), tmp4);
_mm_storel_epi64(reinterpret_cast<__m128i *>(&data[i[2]]), tmp5);
_mm_storel_epi64(reinterpret_cast<__m128i *>(&data[i[4]]), tmp6);
_mm_storel_epi64(reinterpret_cast<__m128i *>(&data[i[6]]), tmp7);
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[1]]), _mm_castsi128_ps(tmp4));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[3]]), _mm_castsi128_ps(tmp5));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[5]]), _mm_castsi128_ps(tmp6));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[7]]), _mm_castsi128_ps(tmp7));
}
static inline void interleave(typename V::EntryType *const data, const Common::SuccessiveEntries<4> &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
const __m128i tmp0 = _mm_unpacklo_epi16(v0.data(), v2.data());
const __m128i tmp1 = _mm_unpackhi_epi16(v0.data(), v2.data());
const __m128i tmp2 = _mm_unpacklo_epi16(v1.data(), v3.data());
const __m128i tmp3 = _mm_unpackhi_epi16(v1.data(), v3.data());
const __m128i tmp4 = _mm_unpacklo_epi16(tmp0, tmp2);
const __m128i tmp5 = _mm_unpackhi_epi16(tmp0, tmp2);
const __m128i tmp6 = _mm_unpacklo_epi16(tmp1, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp1, tmp3);
V(tmp4).store(&data[i[0]], ::Vc::Unaligned);
V(tmp5).store(&data[i[2]], ::Vc::Unaligned);
V(tmp6).store(&data[i[4]], ::Vc::Unaligned);
V(tmp7).store(&data[i[6]], ::Vc::Unaligned);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4)
{
interleave(data, i, v0, v1, v2, v3);
v4.scatter(data + 4, i);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6, const typename V::AsArg v7)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6, v7);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1)
{
const __m128i a = _mm_cvtsi32_si128(*aliasing_cast<int>(&data[i[0]]));
const __m128i b = _mm_cvtsi32_si128(*aliasing_cast<int>(&data[i[1]]));
const __m128i c = _mm_cvtsi32_si128(*aliasing_cast<int>(&data[i[2]]));
const __m128i d = _mm_cvtsi32_si128(*aliasing_cast<int>(&data[i[3]]));
const __m128i e = _mm_cvtsi32_si128(*aliasing_cast<int>(&data[i[4]]));
const __m128i f = _mm_cvtsi32_si128(*aliasing_cast<int>(&data[i[5]]));
const __m128i g = _mm_cvtsi32_si128(*aliasing_cast<int>(&data[i[6]]));
const __m128i h = _mm_cvtsi32_si128(*aliasing_cast<int>(&data[i[7]]));
const __m128i tmp2 = _mm_unpacklo_epi16(a, e);
const __m128i tmp3 = _mm_unpacklo_epi16(c, g);
const __m128i tmp4 = _mm_unpacklo_epi16(b, f);
const __m128i tmp5 = _mm_unpacklo_epi16(d, h);
const __m128i tmp0 = _mm_unpacklo_epi16(tmp2, tmp3);
const __m128i tmp1 = _mm_unpacklo_epi16(tmp4, tmp5);
v0.data() = _mm_unpacklo_epi16(tmp0, tmp1);
v1.data() = _mm_unpackhi_epi16(tmp0, tmp1);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2)
{
const __m128i a = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[0]]));
const __m128i b = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[1]]));
const __m128i c = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[2]]));
const __m128i d = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[3]]));
const __m128i e = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[4]]));
const __m128i f = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[5]]));
const __m128i g = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[6]]));
const __m128i h = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[7]]));
const __m128i tmp2 = _mm_unpacklo_epi16(a, e);
const __m128i tmp4 = _mm_unpacklo_epi16(b, f);
const __m128i tmp3 = _mm_unpacklo_epi16(c, g);
const __m128i tmp5 = _mm_unpacklo_epi16(d, h);
const __m128i tmp0 = _mm_unpacklo_epi16(tmp2, tmp3);
const __m128i tmp1 = _mm_unpacklo_epi16(tmp4, tmp5);
const __m128i tmp6 = _mm_unpackhi_epi16(tmp2, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp4, tmp5);
v0.data() = _mm_unpacklo_epi16(tmp0, tmp1);
v1.data() = _mm_unpackhi_epi16(tmp0, tmp1);
v2.data() = _mm_unpacklo_epi16(tmp6, tmp7);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3)
{
const __m128i a = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[0]]));
const __m128i b = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[1]]));
const __m128i c = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[2]]));
const __m128i d = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[3]]));
const __m128i e = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[4]]));
const __m128i f = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[5]]));
const __m128i g = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[6]]));
const __m128i h = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&data[i[7]]));
const __m128i tmp2 = _mm_unpacklo_epi16(a, e);
const __m128i tmp4 = _mm_unpacklo_epi16(b, f);
const __m128i tmp3 = _mm_unpacklo_epi16(c, g);
const __m128i tmp5 = _mm_unpacklo_epi16(d, h);
const __m128i tmp0 = _mm_unpacklo_epi16(tmp2, tmp3);
const __m128i tmp1 = _mm_unpacklo_epi16(tmp4, tmp5);
const __m128i tmp6 = _mm_unpackhi_epi16(tmp2, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp4, tmp5);
v0.data() = _mm_unpacklo_epi16(tmp0, tmp1);
v1.data() = _mm_unpackhi_epi16(tmp0, tmp1);
v2.data() = _mm_unpacklo_epi16(tmp6, tmp7);
v3.data() = _mm_unpackhi_epi16(tmp6, tmp7);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4)
{
const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[0]]));
const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[1]]));
const __m128i c = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[2]]));
const __m128i d = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[3]]));
const __m128i e = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[4]]));
const __m128i f = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[5]]));
const __m128i g = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[6]]));
const __m128i h = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[7]]));
const __m128i tmp2 = _mm_unpacklo_epi16(a, e);
const __m128i tmp4 = _mm_unpacklo_epi16(b, f);
const __m128i tmp3 = _mm_unpacklo_epi16(c, g);
const __m128i tmp5 = _mm_unpacklo_epi16(d, h);
const __m128i tmp10 = _mm_unpackhi_epi16(a, e);
const __m128i tmp11 = _mm_unpackhi_epi16(c, g);
const __m128i tmp12 = _mm_unpackhi_epi16(b, f);
const __m128i tmp13 = _mm_unpackhi_epi16(d, h);
const __m128i tmp0 = _mm_unpacklo_epi16(tmp2, tmp3);
const __m128i tmp1 = _mm_unpacklo_epi16(tmp4, tmp5);
const __m128i tmp6 = _mm_unpackhi_epi16(tmp2, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp4, tmp5);
const __m128i tmp8 = _mm_unpacklo_epi16(tmp10, tmp11);
const __m128i tmp9 = _mm_unpacklo_epi16(tmp12, tmp13);
v0.data() = _mm_unpacklo_epi16(tmp0, tmp1);
v1.data() = _mm_unpackhi_epi16(tmp0, tmp1);
v2.data() = _mm_unpacklo_epi16(tmp6, tmp7);
v3.data() = _mm_unpackhi_epi16(tmp6, tmp7);
v4.data() = _mm_unpacklo_epi16(tmp8, tmp9);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5)
{
const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[0]]));
const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[1]]));
const __m128i c = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[2]]));
const __m128i d = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[3]]));
const __m128i e = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[4]]));
const __m128i f = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[5]]));
const __m128i g = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[6]]));
const __m128i h = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[7]]));
const __m128i tmp2 = _mm_unpacklo_epi16(a, e);
const __m128i tmp4 = _mm_unpacklo_epi16(b, f);
const __m128i tmp3 = _mm_unpacklo_epi16(c, g);
const __m128i tmp5 = _mm_unpacklo_epi16(d, h);
const __m128i tmp10 = _mm_unpackhi_epi16(a, e);
const __m128i tmp11 = _mm_unpackhi_epi16(c, g);
const __m128i tmp12 = _mm_unpackhi_epi16(b, f);
const __m128i tmp13 = _mm_unpackhi_epi16(d, h);
const __m128i tmp0 = _mm_unpacklo_epi16(tmp2, tmp3);
const __m128i tmp1 = _mm_unpacklo_epi16(tmp4, tmp5);
const __m128i tmp6 = _mm_unpackhi_epi16(tmp2, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp4, tmp5);
const __m128i tmp8 = _mm_unpacklo_epi16(tmp10, tmp11);
const __m128i tmp9 = _mm_unpacklo_epi16(tmp12, tmp13);
v0.data() = _mm_unpacklo_epi16(tmp0, tmp1);
v1.data() = _mm_unpackhi_epi16(tmp0, tmp1);
v2.data() = _mm_unpacklo_epi16(tmp6, tmp7);
v3.data() = _mm_unpackhi_epi16(tmp6, tmp7);
v4.data() = _mm_unpacklo_epi16(tmp8, tmp9);
v5.data() = _mm_unpackhi_epi16(tmp8, tmp9);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6)
{
const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[0]]));
const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[1]]));
const __m128i c = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[2]]));
const __m128i d = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[3]]));
const __m128i e = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[4]]));
const __m128i f = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[5]]));
const __m128i g = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[6]]));
const __m128i h = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[7]]));
const __m128i tmp2 = _mm_unpacklo_epi16(a, e);
const __m128i tmp4 = _mm_unpacklo_epi16(b, f);
const __m128i tmp3 = _mm_unpacklo_epi16(c, g);
const __m128i tmp5 = _mm_unpacklo_epi16(d, h);
const __m128i tmp10 = _mm_unpackhi_epi16(a, e);
const __m128i tmp11 = _mm_unpackhi_epi16(c, g);
const __m128i tmp12 = _mm_unpackhi_epi16(b, f);
const __m128i tmp13 = _mm_unpackhi_epi16(d, h);
const __m128i tmp0 = _mm_unpacklo_epi16(tmp2, tmp3);
const __m128i tmp1 = _mm_unpacklo_epi16(tmp4, tmp5);
const __m128i tmp6 = _mm_unpackhi_epi16(tmp2, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp4, tmp5);
const __m128i tmp8 = _mm_unpacklo_epi16(tmp10, tmp11);
const __m128i tmp9 = _mm_unpacklo_epi16(tmp12, tmp13);
const __m128i tmp14 = _mm_unpackhi_epi16(tmp10, tmp11);
const __m128i tmp15 = _mm_unpackhi_epi16(tmp12, tmp13);
v0.data() = _mm_unpacklo_epi16(tmp0, tmp1);
v1.data() = _mm_unpackhi_epi16(tmp0, tmp1);
v2.data() = _mm_unpacklo_epi16(tmp6, tmp7);
v3.data() = _mm_unpackhi_epi16(tmp6, tmp7);
v4.data() = _mm_unpacklo_epi16(tmp8, tmp9);
v5.data() = _mm_unpackhi_epi16(tmp8, tmp9);
v6.data() = _mm_unpacklo_epi16(tmp14, tmp15);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6, V &v7)
{
const __m128i a = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[0]]));
const __m128i b = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[1]]));
const __m128i c = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[2]]));
const __m128i d = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[3]]));
const __m128i e = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[4]]));
const __m128i f = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[5]]));
const __m128i g = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[6]]));
const __m128i h = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[7]]));
const __m128i tmp2 = _mm_unpacklo_epi16(a, e);
const __m128i tmp4 = _mm_unpacklo_epi16(b, f);
const __m128i tmp3 = _mm_unpacklo_epi16(c, g);
const __m128i tmp5 = _mm_unpacklo_epi16(d, h);
const __m128i tmp10 = _mm_unpackhi_epi16(a, e);
const __m128i tmp11 = _mm_unpackhi_epi16(c, g);
const __m128i tmp12 = _mm_unpackhi_epi16(b, f);
const __m128i tmp13 = _mm_unpackhi_epi16(d, h);
const __m128i tmp0 = _mm_unpacklo_epi16(tmp2, tmp3);
const __m128i tmp1 = _mm_unpacklo_epi16(tmp4, tmp5);
const __m128i tmp6 = _mm_unpackhi_epi16(tmp2, tmp3);
const __m128i tmp7 = _mm_unpackhi_epi16(tmp4, tmp5);
const __m128i tmp8 = _mm_unpacklo_epi16(tmp10, tmp11);
const __m128i tmp9 = _mm_unpacklo_epi16(tmp12, tmp13);
const __m128i tmp14 = _mm_unpackhi_epi16(tmp10, tmp11);
const __m128i tmp15 = _mm_unpackhi_epi16(tmp12, tmp13);
v0.data() = _mm_unpacklo_epi16(tmp0, tmp1);
v1.data() = _mm_unpackhi_epi16(tmp0, tmp1);
v2.data() = _mm_unpacklo_epi16(tmp6, tmp7);
v3.data() = _mm_unpackhi_epi16(tmp6, tmp7);
v4.data() = _mm_unpacklo_epi16(tmp8, tmp9);
v5.data() = _mm_unpackhi_epi16(tmp8, tmp9);
v6.data() = _mm_unpacklo_epi16(tmp14, tmp15);
v7.data() = _mm_unpackhi_epi16(tmp14, tmp15);
}
};
template<typename V> struct InterleaveImpl<V, 4, 16> {
static inline void interleave(typename V::EntryType *const data, const Common::SuccessiveEntries<2> &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
const __m128 tmp0 = _mm_unpacklo_ps(SSE::sse_cast<__m128>(v0.data()),SSE::sse_cast<__m128>(v1.data()));
const __m128 tmp1 = _mm_unpackhi_ps(SSE::sse_cast<__m128>(v0.data()),SSE::sse_cast<__m128>(v1.data()));
_mm_storeu_ps(aliasing_cast<float>(&data[i[0]]), tmp0);
_mm_storeu_ps(aliasing_cast<float>(&data[i[2]]), tmp1);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
const __m128 tmp0 = _mm_unpacklo_ps(SSE::sse_cast<__m128>(v0.data()),SSE::sse_cast<__m128>(v1.data()));
const __m128 tmp1 = _mm_unpackhi_ps(SSE::sse_cast<__m128>(v0.data()),SSE::sse_cast<__m128>(v1.data()));
_mm_storel_pi(reinterpret_cast<__m64 *>(&data[i[0]]), tmp0);
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[1]]), tmp0);
_mm_storel_pi(reinterpret_cast<__m64 *>(&data[i[2]]), tmp1);
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[3]]), tmp1);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2)
{
#ifdef Vc_USE_MASKMOV_SCATTER
const __m128 tmp0 = _mm_unpacklo_ps(SSE::sse_cast<__m128>(v0.data()), SSE::sse_cast<__m128>(v1.data()));
const __m128 tmp1 = _mm_unpackhi_ps(SSE::sse_cast<__m128>(v0.data()), SSE::sse_cast<__m128>(v1.data()));
const __m128 tmp2 = _mm_unpacklo_ps(SSE::sse_cast<__m128>(v2.data()), SSE::sse_cast<__m128>(v2.data()));
const __m128 tmp3 = _mm_unpackhi_ps(SSE::sse_cast<__m128>(v2.data()), SSE::sse_cast<__m128>(v2.data()));
const __m128i mask = _mm_set_epi32(0, -1, -1, -1);
_mm_maskmoveu_si128(_mm_castps_si128(_mm_movelh_ps(tmp0, tmp2)), mask, reinterpret_cast<char *>(&data[i[0]]));
_mm_maskmoveu_si128(_mm_castps_si128(_mm_movehl_ps(tmp2, tmp0)), mask, reinterpret_cast<char *>(&data[i[1]]));
_mm_maskmoveu_si128(_mm_castps_si128(_mm_movelh_ps(tmp1, tmp3)), mask, reinterpret_cast<char *>(&data[i[2]]));
_mm_maskmoveu_si128(_mm_castps_si128(_mm_movehl_ps(tmp3, tmp1)), mask, reinterpret_cast<char *>(&data[i[3]]));
#else
const __m128 tmp0 = _mm_unpacklo_ps(SSE::sse_cast<__m128>(v0.data()),SSE::sse_cast<__m128>(v1.data()));
const __m128 tmp1 = _mm_unpackhi_ps(SSE::sse_cast<__m128>(v0.data()),SSE::sse_cast<__m128>(v1.data()));
_mm_storel_pi(reinterpret_cast<__m64 *>(&data[i[0]]), tmp0);
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[1]]), tmp0);
_mm_storel_pi(reinterpret_cast<__m64 *>(&data[i[2]]), tmp1);
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[3]]), tmp1);
v2.scatter(data + 2, i);
#endif
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
const __m128 tmp0 = _mm_unpacklo_ps(SSE::sse_cast<__m128>(v0.data()),SSE::sse_cast<__m128>(v1.data()));
const __m128 tmp1 = _mm_unpackhi_ps(SSE::sse_cast<__m128>(v0.data()),SSE::sse_cast<__m128>(v1.data()));
const __m128 tmp2 = _mm_unpacklo_ps(SSE::sse_cast<__m128>(v2.data()),SSE::sse_cast<__m128>(v3.data()));
const __m128 tmp3 = _mm_unpackhi_ps(SSE::sse_cast<__m128>(v2.data()),SSE::sse_cast<__m128>(v3.data()));
_mm_storeu_ps(aliasing_cast<float>(&data[i[0]]), _mm_movelh_ps(tmp0, tmp2));
_mm_storeu_ps(aliasing_cast<float>(&data[i[1]]), _mm_movehl_ps(tmp2, tmp0));
_mm_storeu_ps(aliasing_cast<float>(&data[i[2]]), _mm_movelh_ps(tmp1, tmp3));
_mm_storeu_ps(aliasing_cast<float>(&data[i[3]]), _mm_movehl_ps(tmp3, tmp1));
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4)
{
interleave(data, i, v0, v1, v2, v3);
v4.scatter(data + 4, i);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6, const typename V::AsArg v7)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6, v7);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1)
{
const __m128 a = _mm_castpd_ps(_mm_load_sd(aliasing_cast<double>(&data[i[0]])));
const __m128 b = _mm_castpd_ps(_mm_load_sd(aliasing_cast<double>(&data[i[1]])));
const __m128 c = _mm_castpd_ps(_mm_load_sd(aliasing_cast<double>(&data[i[2]])));
const __m128 d = _mm_castpd_ps(_mm_load_sd(aliasing_cast<double>(&data[i[3]])));
const __m128 tmp0 = _mm_unpacklo_ps(a, b);
const __m128 tmp1 = _mm_unpacklo_ps(c, d);
v0.data() = SSE::sse_cast<typename V::VectorType>(_mm_movelh_ps(tmp0, tmp1));
v1.data() = SSE::sse_cast<typename V::VectorType>(_mm_movehl_ps(tmp1, tmp0));
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2)
{
const __m128 a = _mm_loadu_ps(aliasing_cast<float>(&data[i[0]]));
const __m128 b = _mm_loadu_ps(aliasing_cast<float>(&data[i[1]]));
const __m128 c = _mm_loadu_ps(aliasing_cast<float>(&data[i[2]]));
const __m128 d = _mm_loadu_ps(aliasing_cast<float>(&data[i[3]]));
const __m128 tmp0 = _mm_unpacklo_ps(a, b);
const __m128 tmp1 = _mm_unpacklo_ps(c, d);
const __m128 tmp2 = _mm_unpackhi_ps(a, b);
const __m128 tmp3 = _mm_unpackhi_ps(c, d);
v0.data() = SSE::sse_cast<typename V::VectorType>(_mm_movelh_ps(tmp0, tmp1));
v1.data() = SSE::sse_cast<typename V::VectorType>(_mm_movehl_ps(tmp1, tmp0));
v2.data() = SSE::sse_cast<typename V::VectorType>(_mm_movelh_ps(tmp2, tmp3));
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3)
{
const __m128 a = _mm_loadu_ps(aliasing_cast<float>(&data[i[0]]));
const __m128 b = _mm_loadu_ps(aliasing_cast<float>(&data[i[1]]));
const __m128 c = _mm_loadu_ps(aliasing_cast<float>(&data[i[2]]));
const __m128 d = _mm_loadu_ps(aliasing_cast<float>(&data[i[3]]));
const __m128 tmp0 = _mm_unpacklo_ps(a, b);
const __m128 tmp1 = _mm_unpacklo_ps(c, d);
const __m128 tmp2 = _mm_unpackhi_ps(a, b);
const __m128 tmp3 = _mm_unpackhi_ps(c, d);
v0.data() = SSE::sse_cast<typename V::VectorType>(_mm_movelh_ps(tmp0, tmp1));
v1.data() = SSE::sse_cast<typename V::VectorType>(_mm_movehl_ps(tmp1, tmp0));
v2.data() = SSE::sse_cast<typename V::VectorType>(_mm_movelh_ps(tmp2, tmp3));
v3.data() = SSE::sse_cast<typename V::VectorType>(_mm_movehl_ps(tmp3, tmp2));
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4)
{
deinterleave(data, i, v0, v1, v2, v3);
v4.gather(data + 4, i);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5, v6);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6, V &v7)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5, v6, v7);
}
};
template<typename V> struct InterleaveImpl<V, 2, 16> {
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
const __m128d tmp0 = _mm_unpacklo_pd(v0.data(), v1.data());
const __m128d tmp1 = _mm_unpackhi_pd(v0.data(), v1.data());
_mm_storeu_pd(&data[i[0]], tmp0);
_mm_storeu_pd(&data[i[1]], tmp1);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2)
{
interleave(data, i, v0, v1);
v2.scatter(data + 2, i);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
interleave(data, i, v0, v1);
interleave(data + 2, i, v2, v3);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4)
{
interleave(data, i, v0, v1, v2, v3);
v4.scatter(data + 4, i);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6, const typename V::AsArg v7)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6, v7);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1)
{
const __m128d a = _mm_loadu_pd(&data[i[0]]);
const __m128d b = _mm_loadu_pd(&data[i[1]]);
v0.data() = _mm_unpacklo_pd(a, b);
v1.data() = _mm_unpackhi_pd(a, b);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2)
{
v2.gather(data + 2, i);
deinterleave(data, i, v0, v1);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3)
{
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4)
{
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
v4.gather(data + 4, i);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5)
{
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
deinterleave(data + 4, i, v4, v5);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6)
{
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
deinterleave(data + 4, i, v4, v5);
v6.gather(data + 6, i);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6, V &v7)
{
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
deinterleave(data + 4, i, v4, v5);
deinterleave(data + 6, i, v6, v7);
}
};
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <size_t Size>
Vc_INTRINSIC_L Vc_CONST_L int mask_count(__m128i) Vc_INTRINSIC_R Vc_CONST_R;
template <size_t Size>
Vc_INTRINSIC_L Vc_CONST_L int mask_to_int(__m128i) Vc_INTRINSIC_R Vc_CONST_R;
template <size_t Size>
Vc_INTRINSIC_L Vc_CONST_L bool is_equal(__m128, __m128) Vc_INTRINSIC_R Vc_CONST_R;
template <size_t Size>
Vc_INTRINSIC_L Vc_CONST_L bool is_not_equal(__m128, __m128) Vc_INTRINSIC_R Vc_CONST_R;
}
using SSE::sse_cast;
template <typename T> class Mask<T, VectorAbi::Sse>
{
using abi = VectorAbi::Sse;
friend class Mask< double, abi>;
friend class Mask< float, abi>;
friend class Mask< int32_t, abi>;
friend class Mask<uint32_t, abi>;
friend class Mask< int16_t, abi>;
friend class Mask<uint16_t, abi>;
typedef Common::MaskBool<sizeof(T)> MaskBool;
typedef Common::Storage<T, SSE::VectorTraits<T>::Size> Storage;
public:
typedef bool EntryType;
using value_type = EntryType;
using EntryReference = Detail::ElementReference<Mask>;
using reference = EntryReference;
typedef MaskBool VectorEntryType;
using VectorType = typename Storage::VectorType;
using Vector = SSE::Vector<T>;
public:
Vc_FREE_STORE_OPERATORS_ALIGNED(16);
static constexpr size_t Size = SSE::VectorTraits<T>::Size;
static constexpr size_t MemoryAlignment = Size;
static constexpr std::size_t size() { return Size; }
#if defined Vc_MSVC && defined _WIN32
typedef const Mask &Argument;
#else
typedef Mask Argument;
#endif
Vc_INTRINSIC Mask() = default;
Vc_INTRINSIC Mask(const Mask &) = default;
Vc_INTRINSIC Mask &operator=(const Mask &) = default;
Vc_INTRINSIC Mask(const __m128 &x) : d(sse_cast<VectorType>(x)) {}
Vc_INTRINSIC Mask(const __m128d &x) : d(sse_cast<VectorType>(x)) {}
Vc_INTRINSIC Mask(const __m128i &x) : d(sse_cast<VectorType>(x)) {}
Vc_INTRINSIC explicit Mask(VectorSpecialInitializerZero) : Mask(_mm_setzero_ps()) {}
Vc_INTRINSIC explicit Mask(VectorSpecialInitializerOne) : Mask(SSE::_mm_setallone_ps()) {}
Vc_INTRINSIC explicit Mask(bool b) : Mask(b ? SSE::_mm_setallone_ps() : _mm_setzero_ps()) {}
Vc_INTRINSIC static Mask Zero() { return Mask{Vc::Zero}; }
Vc_INTRINSIC static Mask One() { return Mask{Vc::One}; }
template <typename U>
Vc_INTRINSIC Mask(
U &&rhs, Common::enable_if_mask_converts_implicitly<Mask, T, U> = nullarg)
: d(sse_cast<VectorType>(
Detail::mask_cast<Traits::simd_vector_size<U>::value, Size, __m128>(
rhs.dataI())))
{
}
#if Vc_IS_VERSION_1
template <typename U>
Vc_DEPRECATED("use simd_cast instead of explicit type casting to convert between "
"mask types") Vc_INTRINSIC
explicit Mask(U &&rhs,
Common::enable_if_mask_converts_explicitly<T, U> = nullarg);
#endif
Vc_ALWAYS_INLINE explicit Mask(const bool *mem) { load(mem); }
template<typename Flags> Vc_ALWAYS_INLINE explicit Mask(const bool *mem, Flags f) { load(mem, f); }
Vc_ALWAYS_INLINE_L void load(const bool *mem) Vc_ALWAYS_INLINE_R;
template<typename Flags> Vc_ALWAYS_INLINE void load(const bool *mem, Flags) { load(mem); }
Vc_ALWAYS_INLINE_L void store(bool *) const Vc_ALWAYS_INLINE_R;
template<typename Flags> Vc_ALWAYS_INLINE void store(bool *mem, Flags) const { store(mem); }
Vc_ALWAYS_INLINE Vc_PURE bool operator==(const Mask &rhs) const
{
return Detail::is_equal<Size>(data(), rhs.data());
}
Vc_ALWAYS_INLINE Vc_PURE bool operator!=(const Mask &rhs) const
{
return Detail::is_not_equal<Size>(data(), rhs.data());
}
Vc_ALWAYS_INLINE Vc_PURE Mask operator!() const
{
#ifdef Vc_GCC
return ~dataI();
#else
return _mm_andnot_si128(dataI(), SSE::_mm_setallone_si128());
#endif
}
Vc_ALWAYS_INLINE Mask &operator&=(const Mask &rhs) { d.v() = SSE::sse_cast<VectorType>(_mm_and_ps(data(), rhs.data())); return *this; }
Vc_ALWAYS_INLINE Mask &operator|=(const Mask &rhs) { d.v() = SSE::sse_cast<VectorType>(_mm_or_ps (data(), rhs.data())); return *this; }
Vc_ALWAYS_INLINE Mask &operator^=(const Mask &rhs) { d.v() = SSE::sse_cast<VectorType>(_mm_xor_ps(data(), rhs.data())); return *this; }
Vc_ALWAYS_INLINE Vc_PURE Mask operator&(const Mask &rhs) const { return _mm_and_ps(data(), rhs.data()); }
Vc_ALWAYS_INLINE Vc_PURE Mask operator|(const Mask &rhs) const { return _mm_or_ps (data(), rhs.data()); }
Vc_ALWAYS_INLINE Vc_PURE Mask operator^(const Mask &rhs) const { return _mm_xor_ps(data(), rhs.data()); }
Vc_ALWAYS_INLINE Vc_PURE Mask operator&&(const Mask &rhs) const { return _mm_and_ps(data(), rhs.data()); }
Vc_ALWAYS_INLINE Vc_PURE Mask operator||(const Mask &rhs) const { return _mm_or_ps (data(), rhs.data()); }
Vc_ALWAYS_INLINE Vc_PURE bool isFull () const { return
#ifdef Vc_USE_PTEST
_mm_testc_si128(dataI(), SSE::_mm_setallone_si128());
#else
_mm_movemask_epi8(dataI()) == 0xffff;
#endif
}
Vc_ALWAYS_INLINE Vc_PURE bool isNotEmpty() const { return
#ifdef Vc_USE_PTEST
0 == _mm_testz_si128(dataI(), dataI());
#else
_mm_movemask_epi8(dataI()) != 0x0000;
#endif
}
Vc_ALWAYS_INLINE Vc_PURE bool isEmpty() const { return
#ifdef Vc_USE_PTEST
0 != _mm_testz_si128(dataI(), dataI());
#else
_mm_movemask_epi8(dataI()) == 0x0000;
#endif
}
Vc_ALWAYS_INLINE Vc_PURE bool isMix() const {
#ifdef Vc_USE_PTEST
return _mm_test_mix_ones_zeros(dataI(), SSE::_mm_setallone_si128());
#else
const int tmp = _mm_movemask_epi8(dataI());
return tmp != 0 && (tmp ^ 0xffff) != 0;
#endif
}
Vc_ALWAYS_INLINE Vc_PURE int shiftMask() const { return _mm_movemask_epi8(dataI()); }
Vc_ALWAYS_INLINE Vc_PURE int toInt() const { return Detail::mask_to_int<Size>(dataI()); }
Vc_ALWAYS_INLINE Vc_PURE __m128 data () const { return SSE::sse_cast<__m128 >(d.v()); }
Vc_ALWAYS_INLINE Vc_PURE __m128i dataI() const { return SSE::sse_cast<__m128i>(d.v()); }
Vc_ALWAYS_INLINE Vc_PURE __m128d dataD() const { return SSE::sse_cast<__m128d>(d.v()); }
private:
friend reference;
static Vc_INTRINSIC Vc_PURE value_type get(const Mask &m, int i) noexcept
{
return MaskBool(m.d.m(i));
}
template <typename U>
static Vc_INTRINSIC void set(Mask &m, int i,
U &&v) noexcept(noexcept(MaskBool(std::declval<U>())))
{
m.d.set(i, MaskBool(std::forward<U>(v)));
}
public:
Vc_ALWAYS_INLINE reference operator[](size_t index) noexcept
{
return {*this, int(index)};
}
Vc_ALWAYS_INLINE Vc_PURE value_type operator[](size_t index) const noexcept
{
return get(*this, index);
}
Vc_ALWAYS_INLINE Vc_PURE int count() const
{
return Detail::mask_count<Size>(dataI());
}
Vc_ALWAYS_INLINE_L Vc_PURE_L int firstOne() const Vc_ALWAYS_INLINE_R Vc_PURE_R;
template <typename G> static Vc_INTRINSIC_L Mask generate(G &&gen) Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vc_PURE_L Mask shifted(int amount) const Vc_INTRINSIC_R Vc_PURE_R;
private:
#ifdef Vc_COMPILE_BENCHMARKS
public:
#endif
Storage d;
};
template <typename T> constexpr size_t Mask<T, VectorAbi::Sse>::Size;
template <typename T> constexpr size_t Mask<T, VectorAbi::Sse>::MemoryAlignment;
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template<> Vc_INTRINSIC Vc_CONST int mask_count<2>(__m128i k)
{
int mask = _mm_movemask_pd(_mm_castsi128_pd(k));
return (mask & 1) + (mask >> 1);
}
template<> Vc_INTRINSIC Vc_CONST int mask_count<4>(__m128i k)
{
#ifdef Vc_IMPL_POPCNT
return _mm_popcnt_u32(_mm_movemask_ps(_mm_castsi128_ps(k)));
#else
auto x = _mm_srli_epi32(k, 31);
x = _mm_add_epi32(x, _mm_shuffle_epi32(x, _MM_SHUFFLE(0, 1, 2, 3)));
x = _mm_add_epi32(x, _mm_shufflelo_epi16(x, _MM_SHUFFLE(1, 0, 3, 2)));
return _mm_cvtsi128_si32(x);
#endif
}
template<> Vc_INTRINSIC Vc_CONST int mask_count<8>(__m128i k)
{
#ifdef Vc_IMPL_POPCNT
return _mm_popcnt_u32(_mm_movemask_epi8(k)) / 2;
#else
auto x = _mm_srli_epi16(k, 15);
x = _mm_add_epi16(x, _mm_shuffle_epi32(x, _MM_SHUFFLE(0, 1, 2, 3)));
x = _mm_add_epi16(x, _mm_shufflelo_epi16(x, _MM_SHUFFLE(0, 1, 2, 3)));
x = _mm_add_epi16(x, _mm_shufflelo_epi16(x, _MM_SHUFFLE(2, 3, 0, 1)));
return _mm_extract_epi16(x, 0);
#endif
}
template<> Vc_INTRINSIC Vc_CONST int mask_count<16>(__m128i k)
{
return Detail::popcnt16(_mm_movemask_epi8(k));
}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<2>(__m128i k)
{
return _mm_movemask_pd(_mm_castsi128_pd(k));
}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<4>(__m128i k)
{
return _mm_movemask_ps(_mm_castsi128_ps(k));
}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<8>(__m128i k)
{
return _mm_movemask_epi8(_mm_packs_epi16(k, _mm_setzero_si128()));
}
template<> Vc_INTRINSIC Vc_CONST int mask_to_int<16>(__m128i k)
{
return _mm_movemask_epi8(k);
}
template <size_t> Vc_ALWAYS_INLINE void mask_store(__m128i k, bool *mem);
template <> Vc_ALWAYS_INLINE void mask_store<16>(__m128i k, bool *mem)
{
_mm_store_si128(reinterpret_cast<__m128i *>(mem), _mm_and_si128(k, _mm_set1_epi8(1)));
}
template <> Vc_ALWAYS_INLINE void mask_store<8>(__m128i k, bool *mem)
{
k = _mm_srli_epi16(k, 15);
const auto k2 = _mm_packs_epi16(k, _mm_setzero_si128());
#ifdef __x86_64__
*aliasing_cast<int64_t>(mem) = _mm_cvtsi128_si64(k2);
#else
_mm_store_sd(aliasing_cast<double>(mem), _mm_castsi128_pd(k2));
#endif
}
template <> Vc_ALWAYS_INLINE void mask_store<4>(__m128i k, bool *mem)
{
*aliasing_cast<int32_t>(mem) = _mm_cvtsi128_si32(
_mm_packs_epi16(_mm_srli_epi16(_mm_packs_epi32(k, _mm_setzero_si128()), 15),
_mm_setzero_si128()));
}
template <> Vc_ALWAYS_INLINE void mask_store<2>(__m128i k, bool *mem)
{
mem[0] = -SseIntrinsics::extract_epi32<1>(k);
mem[1] = -SseIntrinsics::extract_epi32<3>(k);
}
template<size_t> Vc_ALWAYS_INLINE __m128 mask_load(const bool *mem);
template<> Vc_ALWAYS_INLINE __m128 mask_load<16>(const bool *mem)
{
return sse_cast<__m128>(_mm_cmpgt_epi8(
_mm_load_si128(reinterpret_cast<const __m128i *>(mem)), _mm_setzero_si128()));
}
template<> Vc_ALWAYS_INLINE __m128 mask_load<8>(const bool *mem)
{
#ifdef __x86_64__
__m128i k = _mm_cvtsi64_si128(*reinterpret_cast<const int64_t *>(mem));
#else
__m128i k = _mm_castpd_si128(_mm_load_sd(reinterpret_cast<const double *>(mem)));
#endif
return sse_cast<__m128>(_mm_cmpgt_epi16(_mm_unpacklo_epi8(k, k), _mm_setzero_si128()));
}
template<> Vc_ALWAYS_INLINE __m128 mask_load<4>(const bool *mem)
{
__m128i k = _mm_cvtsi32_si128(*reinterpret_cast<const int *>(mem));
k = _mm_cmpgt_epi16(_mm_unpacklo_epi8(k, k), _mm_setzero_si128());
return sse_cast<__m128>(_mm_unpacklo_epi16(k, k));
}
template<> Vc_ALWAYS_INLINE __m128 mask_load<2>(const bool *mem)
{
return sse_cast<__m128>(
_mm_set_epi32(-int(mem[1]), -int(mem[1]), -int(mem[0]), -int(mem[0])));
}
template <> Vc_INTRINSIC Vc_CONST bool is_equal<2>(__m128 k1, __m128 k2)
{
return _mm_movemask_pd(_mm_castps_pd(k1)) == _mm_movemask_pd(_mm_castps_pd(k2));
}
template <> Vc_INTRINSIC Vc_CONST bool is_not_equal<2>(__m128 k1, __m128 k2)
{
return _mm_movemask_pd(_mm_castps_pd(k1)) != _mm_movemask_pd(_mm_castps_pd(k2));
}
template <> Vc_INTRINSIC Vc_CONST bool is_equal<4>(__m128 k1, __m128 k2)
{
return _mm_movemask_ps(k1) == _mm_movemask_ps(k2);
}
template <> Vc_INTRINSIC Vc_CONST bool is_not_equal<4>(__m128 k1, __m128 k2)
{
return _mm_movemask_ps(k1) != _mm_movemask_ps(k2);
}
template <> Vc_INTRINSIC Vc_CONST bool is_equal<8>(__m128 k1, __m128 k2)
{
return _mm_movemask_epi8(_mm_castps_si128(k1)) ==
_mm_movemask_epi8(_mm_castps_si128(k2));
}
template <> Vc_INTRINSIC Vc_CONST bool is_not_equal<8>(__m128 k1, __m128 k2)
{
return _mm_movemask_epi8(_mm_castps_si128(k1)) !=
_mm_movemask_epi8(_mm_castps_si128(k2));
}
template <> Vc_INTRINSIC Vc_CONST bool is_equal<16>(__m128 k1, __m128 k2)
{
return _mm_movemask_epi8(_mm_castps_si128(k1)) ==
_mm_movemask_epi8(_mm_castps_si128(k2));
}
template <> Vc_INTRINSIC Vc_CONST bool is_not_equal<16>(__m128 k1, __m128 k2)
{
return _mm_movemask_epi8(_mm_castps_si128(k1)) !=
_mm_movemask_epi8(_mm_castps_si128(k2));
}
}
template<> Vc_ALWAYS_INLINE void SSE::double_m::store(bool *mem) const
{
*aliasing_cast<uint16_t>(mem) = _mm_movemask_epi8(dataI()) & 0x0101;
}
template<typename T> Vc_ALWAYS_INLINE void Mask<T, VectorAbi::Sse>::store(bool *mem) const
{
Detail::mask_store<Size>(dataI(), mem);
}
template<> Vc_ALWAYS_INLINE void SSE::double_m::load(const bool *mem)
{
d.set(0, MaskBool(mem[0]));
d.set(1, MaskBool(mem[1]));
}
template <typename T> Vc_ALWAYS_INLINE void Mask<T, VectorAbi::Sse>::load(const bool *mem)
{
d.v() = sse_cast<VectorType>(Detail::mask_load<Size>(mem));
}
template <>
Vc_INTRINSIC Vc_PURE bool SSE::short_m::get(const SSE::short_m &m, int index) noexcept
{
return m.shiftMask() & (1 << 2 * index);
}
template <>
Vc_INTRINSIC Vc_PURE bool SSE::ushort_m::get(const SSE::ushort_m &m, int index) noexcept
{
return m.shiftMask() & (1 << 2 * index);
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE int Mask<T, VectorAbi::Sse>::firstOne() const
{
const int mask = toInt();
#ifdef _MSC_VER
unsigned long bit;
_BitScanForward(&bit, mask);
#else
int bit;
__asm__("bsf %1,%0" : "=&r"(bit) : "r"(mask));
#endif
return bit;
}
template <typename M, typename G>
Vc_INTRINSIC M generate_impl(G &&gen, std::integral_constant<int, 2>)
{
return _mm_set_epi64x(gen(1) ? 0xffffffffffffffffull : 0,
gen(0) ? 0xffffffffffffffffull : 0);
}
template <typename M, typename G>
Vc_INTRINSIC M generate_impl(G &&gen, std::integral_constant<int, 4>)
{
return _mm_setr_epi32(gen(0) ? 0xfffffffful : 0, gen(1) ? 0xfffffffful : 0,
gen(2) ? 0xfffffffful : 0, gen(3) ? 0xfffffffful : 0);
}
template <typename M, typename G>
Vc_INTRINSIC M generate_impl(G &&gen, std::integral_constant<int, 8>)
{
return _mm_setr_epi16(gen(0) ? 0xffffu : 0, gen(1) ? 0xffffu : 0,
gen(2) ? 0xffffu : 0, gen(3) ? 0xffffu : 0,
gen(4) ? 0xffffu : 0, gen(5) ? 0xffffu : 0,
gen(6) ? 0xffffu : 0, gen(7) ? 0xffffu : 0);
}
template <typename T>
template <typename G>
Vc_INTRINSIC Mask<T, VectorAbi::Sse> Mask<T, VectorAbi::Sse>::generate(G &&gen)
{
return generate_impl<Mask<T, VectorAbi::Sse>>(std::forward<G>(gen),
std::integral_constant<int, Size>());
}
template <typename T> Vc_INTRINSIC Vc_PURE Mask<T, VectorAbi::Sse> Mask<T, VectorAbi::Sse>::shifted(int amount) const
{
switch (amount * int(sizeof(VectorEntryType))) {
case 0: return *this;
case 1: return Detail::shifted< 1>(dataI());
case 2: return Detail::shifted< 2>(dataI());
case 3: return Detail::shifted< 3>(dataI());
case 4: return Detail::shifted< 4>(dataI());
case 5: return Detail::shifted< 5>(dataI());
case 6: return Detail::shifted< 6>(dataI());
case 7: return Detail::shifted< 7>(dataI());
case 8: return Detail::shifted< 8>(dataI());
case 9: return Detail::shifted< 9>(dataI());
case 10: return Detail::shifted< 10>(dataI());
case 11: return Detail::shifted< 11>(dataI());
case 12: return Detail::shifted< 12>(dataI());
case 13: return Detail::shifted< 13>(dataI());
case 14: return Detail::shifted< 14>(dataI());
case 15: return Detail::shifted< 15>(dataI());
case 16: return Detail::shifted< 16>(dataI());
case -1: return Detail::shifted< -1>(dataI());
case -2: return Detail::shifted< -2>(dataI());
case -3: return Detail::shifted< -3>(dataI());
case -4: return Detail::shifted< -4>(dataI());
case -5: return Detail::shifted< -5>(dataI());
case -6: return Detail::shifted< -6>(dataI());
case -7: return Detail::shifted< -7>(dataI());
case -8: return Detail::shifted< -8>(dataI());
case -9: return Detail::shifted< -9>(dataI());
case -10: return Detail::shifted<-10>(dataI());
case -11: return Detail::shifted<-11>(dataI());
case -12: return Detail::shifted<-12>(dataI());
case -13: return Detail::shifted<-13>(dataI());
case -14: return Detail::shifted<-14>(dataI());
case -15: return Detail::shifted<-15>(dataI());
case -16: return Detail::shifted<-16>(dataI());
}
return Zero();
}
}
#endif
#include <algorithm>
#include <cmath>
#ifdef isfinite
#undef isfinite
#endif
#ifdef isnan
#undef isnan
#endif
namespace Vc_VERSIONED_NAMESPACE
{
#define Vc_CURRENT_CLASS_NAME Vector
template <typename T> class Vector<T, VectorAbi::Sse>
{
static_assert(std::is_arithmetic<T>::value,
"Vector<T> only accepts arithmetic builtin types as template parameter T.");
protected:
#ifdef Vc_COMPILE_BENCHMARKS
public:
#endif
typedef typename SSE::VectorTraits<T>::StorageType StorageType;
StorageType d;
typedef typename SSE::VectorTraits<T>::GatherMaskType GatherMask;
typedef SSE::VectorHelper<typename SSE::VectorTraits<T>::VectorType> HV;
typedef SSE::VectorHelper<T> HT;
public:
Vc_FREE_STORE_OPERATORS_ALIGNED(16);
typedef typename SSE::VectorTraits<T>::VectorType VectorType;
using vector_type = VectorType;
static constexpr size_t Size = SSE::VectorTraits<T>::Size;
static constexpr size_t MemoryAlignment = alignof(VectorType);
typedef typename SSE::VectorTraits<T>::EntryType EntryType;
using value_type = EntryType;
using VectorEntryType = EntryType;
typedef typename std::conditional<(Size >= 4),
SimdArray<int, Size, SSE::int_v, 4>,
SimdArray<int, Size, Scalar::int_v, 1>>::type IndexType;
typedef typename SSE::VectorTraits<T>::MaskType Mask;
using MaskType = Mask;
using mask_type = Mask;
typedef typename Mask::Argument MaskArg;
typedef typename Mask::Argument MaskArgument;
typedef const Vector AsArg;
using abi = VectorAbi::Sse;
using WriteMaskedVector = Common::WriteMaskedVector<Vector, Mask>;
template <typename U> using V = Vector<U, abi>;
using reference = Detail::ElementReference<Vector>;
public:
Vc_INTRINSIC Vector() = default;
static constexpr std::size_t size() { return Size; }
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerZero) Vc_INTRINSIC_R;
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerOne) Vc_INTRINSIC_R;
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerIndexesFromZero) Vc_INTRINSIC_R;
static Vc_INTRINSIC Vc_CONST Vector Zero() { return Vector(Vc::Zero); }
static Vc_INTRINSIC Vc_CONST Vector One() { return Vector(Vc::One); }
static Vc_INTRINSIC Vc_CONST Vector IndexesFromZero()
{
return Vector(Vc::IndexesFromZero);
}
template <class G, class...,
class = typename std::enable_if<std::is_convertible<
decltype(std::declval<G>()(size_t())), value_type>::value>::type>
explicit Vector(G &&g) : Vector(generate(std::forward<G>(g)))
{
}
static Vc_INTRINSIC_L Vector Random() Vc_INTRINSIC_R;
Vc_ALWAYS_INLINE Vector(VectorType x) : d(x) {}
template <typename U>
Vc_INTRINSIC Vector(
V<U> x, typename std::enable_if<Traits::is_implicit_cast_allowed<U, T>::value,
void *>::type = nullptr)
: d(SSE::convert<U, T>(x.data()))
{
}
#if Vc_IS_VERSION_1
template <typename U>
Vc_DEPRECATED("use simd_cast instead of explicit type casting to convert between "
"vector types") Vc_INTRINSIC
explicit Vector(
V<U> x,
typename std::enable_if<!Traits::is_implicit_cast_allowed<U, T>::value,
void *>::type = nullptr)
: d(SSE::convert<U, T>(x.data()))
{
}
#endif
Vc_INTRINSIC Vector(EntryType a) : d(HT::set(a)) {}
template <typename U>
Vc_INTRINSIC Vector(U a,
typename std::enable_if<std::is_same<U, int>::value &&
!std::is_same<U, EntryType>::value,
void *>::type = nullptr)
: Vector(static_cast<EntryType>(a))
{
}
explicit Vc_INTRINSIC Vector(const EntryType *mem)
{
load(mem);
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const EntryType *mem, Flags flags)
{
load(mem, flags);
}
template <typename U, typename Flags = DefaultLoadTag,
typename = enable_if<
(!std::is_integral<U>::value || !std::is_integral<EntryType>::value ||
sizeof(EntryType) >= sizeof(U)) &&
std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const U *x, Flags flags = Flags())
{
load<U, Flags>(x, flags);
}
Vc_INTRINSIC void load(const EntryType *mem)
{
load(mem, DefaultLoadTag());
}
template <typename Flags>
Vc_INTRINSIC enable_if<Traits::is_load_store_flag<Flags>::value, void>
load(const EntryType *mem, Flags flags)
{
load<EntryType, Flags>(mem, flags);
}
private:
template <typename U, typename Flags>
struct load_concept : public std::enable_if<
(!std::is_integral<U>::value || !std::is_integral<EntryType>::value ||
sizeof(EntryType) >= sizeof(U)) &&
std::is_arithmetic<U>::value && Traits::is_load_store_flag<Flags>::value, void>
{};
public:
template <typename U, typename Flags = DefaultLoadTag>
Vc_INTRINSIC_L typename load_concept<U, Flags>::type load(const U *mem, Flags = Flags()) Vc_INTRINSIC_R;
template <
typename U,
typename Flags = DefaultStoreTag,
typename = enable_if<std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC_L void store(U *mem, Flags flags = Flags()) const Vc_INTRINSIC_R;
template <
typename U,
typename Flags = DefaultStoreTag,
typename = enable_if<std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC_L void Vc_VDECL store(U *mem, MaskType mask, Flags flags = Flags()) const Vc_INTRINSIC_R;
Vc_INTRINSIC void store(EntryType *mem) const
{
store<EntryType, DefaultStoreTag>(mem, DefaultStoreTag());
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC void store(EntryType *mem, Flags flags) const
{
store<EntryType, Flags>(mem, flags);
}
Vc_INTRINSIC void Vc_VDECL store(EntryType *mem, MaskType mask) const
{
store<EntryType, DefaultStoreTag>(mem, mask, DefaultStoreTag());
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC void Vc_VDECL store(EntryType *mem, MaskType mask, Flags flags) const
{
store<EntryType, Flags>(mem, mask, flags);
}
Vc_INTRINSIC_L void setZero() Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setZero(const Mask &k) Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setZeroInverted(const Mask &k) Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setQnan() Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setQnan(const Mask &k) Vc_INTRINSIC_R;
#ifndef Vc_CURRENT_CLASS_NAME
#error "incorrect use of common/gatherinterface.h: Vc_CURRENT_CLASS_NAME must be defined to the current class name for declaring constructors."
#endif
private:
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes);
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes, MaskArgument mask);
template <typename IT, typename = enable_if<std::is_pointer<IT>::value ||
Traits::is_simd_vector<IT>::value>>
static Vc_INTRINSIC const IT &adjustIndexParameter(const IT &indexes)
{
return indexes;
}
template <
typename IT,
typename = enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value>>
static Vc_INTRINSIC decltype(std::addressof(std::declval<const IT &>()[0]))
adjustIndexParameter(const IT &i)
{
return std::addressof(i[0]);
}
template <typename IT>
static Vc_INTRINSIC enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
!std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value,
IT>
adjustIndexParameter(const IT &i)
{
return i;
}
public:
#define Vc_ASSERT_GATHER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<MT, EntryType>::value, \
"The memory pointer needs to point to a type that can be converted to the " \
"EntryType of this SIMD vector type."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT, typename IT,
typename = enable_if<Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes,
MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes, MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args)
{
gather(args.address, adjustIndexParameter(args.indexes));
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args, MaskArgument mask)
{
gather(args.address, adjustIndexParameter(args.indexes), mask);
}
#undef Vc_ASSERT_GATHER_PARAMETER_TYPES_
private:
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes) const;
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes, MaskArgument mask) const;
public:
#define Vc_ASSERT_SCATTER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<EntryType, MT>::value, \
"The memory pointer needs to point to a type that the EntryType of this " \
"SIMD vector type can be converted to."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes));
}
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes, MaskArgument mask) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args) const
{
scatter(args.address, args.indexes);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args, MaskArgument mask) const
{
scatter(args.address, args.indexes, mask);
}
#undef Vc_ASSERT_SCATTER_PARAMETER_TYPES_
Vc_INTRINSIC Vector &operator++() { data() = HT::add(data(), HT::one()); return *this; }
Vc_INTRINSIC Vector &operator--() { data() = HT::sub(data(), HT::one()); return *this; }
Vc_INTRINSIC Vector operator++(int) { const Vector r = *this; data() = HT::add(data(), HT::one()); return r; }
Vc_INTRINSIC Vector operator--(int) { const Vector r = *this; data() = HT::sub(data(), HT::one()); return r; }
private:
friend reference;
Vc_INTRINSIC static value_type get(const Vector &o, int i) noexcept
{
return o.d.m(i);
}
template <typename U>
Vc_INTRINSIC static void set(Vector &o, int i, U &&v) noexcept(
noexcept(std::declval<value_type &>() = v))
{
o.d.set(i, v);
}
public:
Vc_ALWAYS_INLINE reference operator[](size_t index) noexcept
{
static_assert(noexcept(reference{std::declval<Vector &>(), int()}), "");
return {*this, int(index)};
}
Vc_ALWAYS_INLINE value_type operator[](size_t index) const noexcept
{
return d.m(index);
}
Vc_INTRINSIC_L Vector Vc_VDECL operator[](const SSE::int_v &perm) const Vc_INTRINSIC_R;
Vc_INTRINSIC Vc_PURE Mask operator!() const
{
return *this == Zero();
}
Vc_INTRINSIC Vc_PURE Vector operator~() const
{
#ifndef Vc_ENABLE_FLOAT_BIT_OPERATORS
static_assert(std::is_integral<T>::value,
"bit-complement can only be used with Vectors of integral type");
#endif
return Detail::andnot_(data(), HV::allone());
}
Vc_ALWAYS_INLINE_L Vc_PURE_L Vector operator-() const Vc_ALWAYS_INLINE_R Vc_PURE_R;
Vc_INTRINSIC Vc_PURE Vector operator+() const { return *this; }
Vc_ALWAYS_INLINE Vector Vc_VDECL operator<< (AsArg shift) const { return generate([&](int i) { return get(*this, i) << get(shift, i); }); }
Vc_ALWAYS_INLINE Vector Vc_VDECL operator>> (AsArg shift) const { return generate([&](int i) { return get(*this, i) >> get(shift, i); }); }
Vc_ALWAYS_INLINE Vector &Vc_VDECL operator<<=(AsArg shift) { return *this = *this << shift; }
Vc_ALWAYS_INLINE Vector &Vc_VDECL operator>>=(AsArg shift) { return *this = *this >> shift; }
Vc_INTRINSIC_L Vector &Vc_VDECL operator<<=( int shift) Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector Vc_VDECL operator<< ( int shift) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector &Vc_VDECL operator>>=( int shift) Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector Vc_VDECL operator>> ( int shift) const Vc_INTRINSIC_R;
Vc_DEPRECATED("use isnegative(x) instead") Vc_INTRINSIC Vc_PURE Mask
isNegative() const
{
return Vc::isnegative(*this);
}
Vc_ALWAYS_INLINE void assign(const Vector &v, const Mask &mask)
{
const VectorType k = SSE::sse_cast<VectorType>(mask.data());
data() = HV::blend(data(), v.data(), k);
}
template <typename V2>
Vc_DEPRECATED("Use simd_cast instead of Vector::staticCast")
Vc_ALWAYS_INLINE Vc_PURE V2 staticCast() const
{
return SSE::convert<T, typename V2::EntryType>(data());
}
template <typename V2>
Vc_DEPRECATED("use reinterpret_components_cast instead")
Vc_ALWAYS_INLINE Vc_PURE V2 reinterpretCast() const
{
return SSE::sse_cast<typename V2::VectorType>(data());
}
Vc_INTRINSIC WriteMaskedVector operator()(const Mask &k) { return {*this, k}; }
Vc_ALWAYS_INLINE Vc_PURE VectorType &data() { return d.v(); }
Vc_ALWAYS_INLINE Vc_PURE const VectorType &data() const { return d.v(); }
template<int Index>
Vc_INTRINSIC_L Vector broadcast() const Vc_INTRINSIC_R;
Vc_INTRINSIC EntryType min() const { return HT::min(data()); }
Vc_INTRINSIC EntryType max() const { return HT::max(data()); }
Vc_INTRINSIC EntryType product() const { return HT::mul(data()); }
Vc_INTRINSIC EntryType sum() const { return HT::add(data()); }
Vc_INTRINSIC_L Vector partialSum() const Vc_INTRINSIC_R;
Vc_INTRINSIC_L EntryType min(MaskArg m) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L EntryType max(MaskArg m) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L EntryType product(MaskArg m) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L EntryType sum(MaskArg m) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector shifted(int amount, Vector shiftIn) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector shifted(int amount) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector rotated(int amount) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vc_PURE_L Vector reversed() const Vc_INTRINSIC_R Vc_PURE_R;
Vc_ALWAYS_INLINE_L Vc_PURE_L Vector sorted() const Vc_ALWAYS_INLINE_R Vc_PURE_R;
template <typename F> void callWithValuesSorted(F &&f)
{
EntryType value = d.m(0);
f(value);
for (std::size_t i = 1; i < Size; ++i) {
if (d.m(i) != value) {
value = d.m(i);
f(value);
}
}
}
template <typename F> Vc_INTRINSIC void call(F &&f) const
{
Common::for_all_vector_entries<Size>([&](size_t i) { f(EntryType(d.m(i))); });
}
template <typename F> Vc_INTRINSIC void call(F &&f, const Mask &mask) const
{
for(size_t i : where(mask)) {
f(EntryType(d.m(i)));
}
}
template <typename F> Vc_INTRINSIC Vector apply(F &&f) const
{
Vector r;
Common::for_all_vector_entries<Size>(
[&](size_t i) { r.d.set(i, f(EntryType(d.m(i)))); });
return r;
}
template <typename F> Vc_INTRINSIC Vector apply(F &&f, const Mask &mask) const
{
Vector r(*this);
for (size_t i : where(mask)) {
r.d.set(i, f(EntryType(r.d.m(i))));
}
return r;
}
template<typename IndexT> Vc_INTRINSIC void fill(EntryType (&f)(IndexT)) {
Common::for_all_vector_entries<Size>([&](size_t i) { d.set(i, f(i)); });
}
Vc_INTRINSIC void fill(EntryType (&f)()) {
Common::for_all_vector_entries<Size>([&](size_t i) { d.set(i, f()); });
}
template <typename G> static Vc_INTRINSIC_L Vector generate(G gen) Vc_INTRINSIC_R;
Vc_DEPRECATED("use copysign(x, y) instead") Vc_INTRINSIC Vector
copySign(AsArg x) const
{
return Vc::copysign(*this, x);
}
Vc_DEPRECATED("use exponent(x) instead") Vc_INTRINSIC Vector exponent() const
{
return Vc::exponent(*this);
}
Vc_INTRINSIC_L Vector interleaveLow(Vector x) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector interleaveHigh(Vector x) const Vc_INTRINSIC_R;
};
#undef Vc_CURRENT_CLASS_NAME
template <typename T> constexpr size_t Vector<T, VectorAbi::Sse>::Size;
template <typename T> constexpr size_t Vector<T, VectorAbi::Sse>::MemoryAlignment;
static Vc_ALWAYS_INLINE Vc_PURE SSE::int_v min(const SSE::int_v &x, const SSE::int_v &y) { return SSE::min_epi32(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::uint_v min(const SSE::uint_v &x, const SSE::uint_v &y) { return SSE::min_epu32(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::short_v min(const SSE::short_v &x, const SSE::short_v &y) { return _mm_min_epi16(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::ushort_v min(const SSE::ushort_v &x, const SSE::ushort_v &y) { return SSE::min_epu16(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::float_v min(const SSE::float_v &x, const SSE::float_v &y) { return _mm_min_ps(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::double_v min(const SSE::double_v &x, const SSE::double_v &y) { return _mm_min_pd(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::int_v max(const SSE::int_v &x, const SSE::int_v &y) { return SSE::max_epi32(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::uint_v max(const SSE::uint_v &x, const SSE::uint_v &y) { return SSE::max_epu32(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::short_v max(const SSE::short_v &x, const SSE::short_v &y) { return _mm_max_epi16(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::ushort_v max(const SSE::ushort_v &x, const SSE::ushort_v &y) { return SSE::max_epu16(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::float_v max(const SSE::float_v &x, const SSE::float_v &y) { return _mm_max_ps(x.data(), y.data()); }
static Vc_ALWAYS_INLINE Vc_PURE SSE::double_v max(const SSE::double_v &x, const SSE::double_v &y) { return _mm_max_pd(x.data(), y.data()); }
template <typename T,
typename = enable_if<std::is_same<T, double>::value || std::is_same<T, float>::value ||
std::is_same<T, short>::value ||
std::is_same<T, int>::value>>
Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> abs(Vector<T, VectorAbi::Sse> x)
{
return SSE::VectorHelper<T>::abs(x.data());
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> sqrt (const Vector<T, VectorAbi::Sse> &x) { return SSE::VectorHelper<T>::sqrt(x.data()); }
template<typename T> Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> rsqrt(const Vector<T, VectorAbi::Sse> &x) { return SSE::VectorHelper<T>::rsqrt(x.data()); }
template<typename T> Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> reciprocal(const Vector<T, VectorAbi::Sse> &x) { return SSE::VectorHelper<T>::reciprocal(x.data()); }
template<typename T> Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> round(const Vector<T, VectorAbi::Sse> &x) { return SSE::VectorHelper<T>::round(x.data()); }
template<typename T> Vc_ALWAYS_INLINE Vc_PURE typename Vector<T, VectorAbi::Sse>::Mask isfinite(const Vector<T, VectorAbi::Sse> &x) { return SSE::VectorHelper<T>::isFinite(x.data()); }
template<typename T> Vc_ALWAYS_INLINE Vc_PURE typename Vector<T, VectorAbi::Sse>::Mask isinf(const Vector<T, VectorAbi::Sse> &x) { return SSE::VectorHelper<T>::isInfinite(x.data()); }
template<typename T> Vc_ALWAYS_INLINE Vc_PURE typename Vector<T, VectorAbi::Sse>::Mask isnan(const Vector<T, VectorAbi::Sse> &x) { return SSE::VectorHelper<T>::isNaN(x.data()); }
#define Vc_CONDITIONAL_ASSIGN(name_,op_) \
template <Operator O, typename T, typename M, typename U> \
Vc_INTRINSIC enable_if<O == Operator::name_, void> conditional_assign( \
Vector<T, VectorAbi::Sse> &lhs, M &&mask, U &&rhs) \
{ \
lhs(mask) op_ rhs; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_CONDITIONAL_ASSIGN( Assign, =);
Vc_CONDITIONAL_ASSIGN( PlusAssign, +=);
Vc_CONDITIONAL_ASSIGN( MinusAssign, -=);
Vc_CONDITIONAL_ASSIGN( MultiplyAssign, *=);
Vc_CONDITIONAL_ASSIGN( DivideAssign, /=);
Vc_CONDITIONAL_ASSIGN( RemainderAssign, %=);
Vc_CONDITIONAL_ASSIGN( XorAssign, ^=);
Vc_CONDITIONAL_ASSIGN( AndAssign, &=);
Vc_CONDITIONAL_ASSIGN( OrAssign, |=);
Vc_CONDITIONAL_ASSIGN( LeftShiftAssign,<<=);
Vc_CONDITIONAL_ASSIGN(RightShiftAssign,>>=);
#undef Vc_CONDITIONAL_ASSIGN
#define Vc_CONDITIONAL_ASSIGN(name_,expr_) \
template <Operator O, typename T, typename M> \
Vc_INTRINSIC enable_if<O == Operator::name_, Vector<T, VectorAbi::Sse>> \
conditional_assign(Vector<T, VectorAbi::Sse> &lhs, M &&mask) \
{ \
return expr_; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_CONDITIONAL_ASSIGN(PostIncrement, lhs(mask)++);
Vc_CONDITIONAL_ASSIGN( PreIncrement, ++lhs(mask));
Vc_CONDITIONAL_ASSIGN(PostDecrement, lhs(mask)--);
Vc_CONDITIONAL_ASSIGN( PreDecrement, --lhs(mask));
#undef Vc_CONDITIONAL_ASSIGN
}
#ifndef VC_COMMON_X86_PREFETCHES_H_
#define VC_COMMON_X86_PREFETCHES_H_ 
#include <xmmintrin.h>
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
static constexpr int exclusive_hint = 0;
template <typename ExclusiveOrShared = Vc::Shared>
Vc_INTRINSIC void prefetchForOneRead(const void *addr)
{
if (std::is_same<ExclusiveOrShared, Vc::Shared>::value) {
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_NTA);
} else {
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)),
static_cast<decltype(_MM_HINT_NTA)>(_MM_HINT_NTA | exclusive_hint));
}
}
template <typename ExclusiveOrShared = Vc::Shared>
Vc_INTRINSIC void prefetchClose(const void *addr)
{
if (std::is_same<ExclusiveOrShared, Vc::Shared>::value) {
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_T0);
} else {
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)),
static_cast<decltype(_MM_HINT_T0)>(_MM_HINT_T0 | exclusive_hint));
}
}
template <typename ExclusiveOrShared = Vc::Shared>
Vc_INTRINSIC void prefetchMid(const void *addr)
{
if (std::is_same<ExclusiveOrShared, Vc::Shared>::value) {
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_T1);
} else {
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)),
static_cast<decltype(_MM_HINT_T1)>(_MM_HINT_T1 | exclusive_hint));
}
}
template <typename ExclusiveOrShared = Vc::Shared>
Vc_INTRINSIC void prefetchFar(const void *addr)
{
if (std::is_same<ExclusiveOrShared, Vc::Shared>::value) {
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_T2);
} else {
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)),
static_cast<decltype(_MM_HINT_T2)>(_MM_HINT_T2 | exclusive_hint));
}
}
namespace
{
template<size_t L1, size_t L2, bool UseExclusivePrefetch> Vc_INTRINSIC void handlePrefetch(const void *addr_, typename std::enable_if<L1 != 0 && L2 != 0, void *>::type = nullptr)
{
const char *addr = static_cast<const char *>(addr_);
prefetchClose<typename std::conditional<UseExclusivePrefetch, Vc::Exclusive, Vc::Shared>::type>(addr + L1);
prefetchMid <typename std::conditional<UseExclusivePrefetch, Vc::Exclusive, Vc::Shared>::type>(addr + L2);
}
template<size_t L1, size_t L2, bool UseExclusivePrefetch> Vc_INTRINSIC void handlePrefetch(const void *addr_, typename std::enable_if<L1 == 0 && L2 != 0, void *>::type = nullptr)
{
const char *addr = static_cast<const char *>(addr_);
prefetchMid <typename std::conditional<UseExclusivePrefetch, Vc::Exclusive, Vc::Shared>::type>(addr + L2);
}
template<size_t L1, size_t L2, bool UseExclusivePrefetch> Vc_INTRINSIC void handlePrefetch(const void *addr_, typename std::enable_if<L1 != 0 && L2 == 0, void *>::type = nullptr)
{
const char *addr = static_cast<const char *>(addr_);
prefetchClose<typename std::conditional<UseExclusivePrefetch, Vc::Exclusive, Vc::Shared>::type>(addr + L1);
}
template<size_t L1, size_t L2, bool UseExclusivePrefetch> Vc_INTRINSIC void handlePrefetch(const void *, typename std::enable_if<L1 == 0 && L2 == 0, void *>::type = nullptr)
{
}
template<typename Flags> Vc_INTRINSIC void handleLoadPrefetches(const void * , Flags, typename Flags::EnableIfNotPrefetch = nullptr) {}
template<typename Flags> Vc_INTRINSIC void handleLoadPrefetches(const void *addr, Flags, typename Flags::EnableIfPrefetch = nullptr)
{
handlePrefetch<Flags::L1Stride, Flags::L2Stride, Flags::IsExclusivePrefetch>(addr);
}
template<typename Flags> Vc_INTRINSIC void handleStorePrefetches(const void * , Flags, typename Flags::EnableIfNotPrefetch = nullptr) {}
template<typename Flags> Vc_INTRINSIC void handleStorePrefetches(const void *addr, Flags, typename Flags::EnableIfPrefetch = nullptr)
{
handlePrefetch<Flags::L1Stride, Flags::L2Stride, !Flags::IsSharedPrefetch>(addr);
}
}
}
using Common::prefetchForOneRead;
using Common::prefetchClose;
using Common::prefetchMid;
using Common::prefetchFar;
}
#endif
#ifndef VC_SSE_LIMITS_H_
#define VC_SSE_LIMITS_H_ 
namespace std
{
template<> struct numeric_limits< ::Vc::SSE::ushort_v> : public numeric_limits<unsigned short>
{
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v max() Vc_NOEXCEPT { return ::Vc::SSE::_mm_setallone_si128(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v min() Vc_NOEXCEPT { return ::Vc::SSE::ushort_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v lowest() Vc_NOEXCEPT { return min(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v epsilon() Vc_NOEXCEPT { return ::Vc::SSE::ushort_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v round_error() Vc_NOEXCEPT { return ::Vc::SSE::ushort_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v infinity() Vc_NOEXCEPT { return ::Vc::SSE::ushort_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v quiet_NaN() Vc_NOEXCEPT { return ::Vc::SSE::ushort_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v signaling_NaN() Vc_NOEXCEPT { return ::Vc::SSE::ushort_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::ushort_v denorm_min() Vc_NOEXCEPT { return ::Vc::SSE::ushort_v::Zero(); }
};
template<> struct numeric_limits< ::Vc::SSE::short_v> : public numeric_limits<short>
{
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v max() Vc_NOEXCEPT { return _mm_srli_epi16(::Vc::SSE::_mm_setallone_si128(), 1); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v min() Vc_NOEXCEPT { return ::Vc::SSE::setmin_epi16(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v lowest() Vc_NOEXCEPT { return min(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v epsilon() Vc_NOEXCEPT { return ::Vc::SSE::short_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v round_error() Vc_NOEXCEPT { return ::Vc::SSE::short_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v infinity() Vc_NOEXCEPT { return ::Vc::SSE::short_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v quiet_NaN() Vc_NOEXCEPT { return ::Vc::SSE::short_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v signaling_NaN() Vc_NOEXCEPT { return ::Vc::SSE::short_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::short_v denorm_min() Vc_NOEXCEPT { return ::Vc::SSE::short_v::Zero(); }
};
template<> struct numeric_limits< ::Vc::SSE::uint_v> : public numeric_limits<unsigned int>
{
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v max() Vc_NOEXCEPT { return ::Vc::SSE::_mm_setallone_si128(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v min() Vc_NOEXCEPT { return ::Vc::SSE::uint_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v lowest() Vc_NOEXCEPT { return min(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v epsilon() Vc_NOEXCEPT { return ::Vc::SSE::uint_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v round_error() Vc_NOEXCEPT { return ::Vc::SSE::uint_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v infinity() Vc_NOEXCEPT { return ::Vc::SSE::uint_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v quiet_NaN() Vc_NOEXCEPT { return ::Vc::SSE::uint_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v signaling_NaN() Vc_NOEXCEPT { return ::Vc::SSE::uint_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::uint_v denorm_min() Vc_NOEXCEPT { return ::Vc::SSE::uint_v::Zero(); }
};
template<> struct numeric_limits< ::Vc::SSE::int_v> : public numeric_limits<int>
{
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v max() Vc_NOEXCEPT { return _mm_srli_epi32(::Vc::SSE::_mm_setallone_si128(), 1); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v min() Vc_NOEXCEPT { return ::Vc::SSE::setmin_epi32(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v lowest() Vc_NOEXCEPT { return min(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v epsilon() Vc_NOEXCEPT { return ::Vc::SSE::int_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v round_error() Vc_NOEXCEPT { return ::Vc::SSE::int_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v infinity() Vc_NOEXCEPT { return ::Vc::SSE::int_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v quiet_NaN() Vc_NOEXCEPT { return ::Vc::SSE::int_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v signaling_NaN() Vc_NOEXCEPT { return ::Vc::SSE::int_v::Zero(); }
static Vc_INTRINSIC Vc_CONST ::Vc::SSE::int_v denorm_min() Vc_NOEXCEPT { return ::Vc::SSE::int_v::Zero(); }
};
}
#endif
#ifndef VC_COMMON_BITSCANINTRINSICS_H_
#define VC_COMMON_BITSCANINTRINSICS_H_ 
#if defined(Vc_GCC) || defined(Vc_CLANG) || defined(Vc_APPLECLANG)
# if Vc_GCC >= 0x40500
# include <x86intrin.h>
# else
#define _bit_scan_forward(x) __builtin_ctz(x)
static Vc_ALWAYS_INLINE Vc_CONST int _Vc_bit_scan_reverse_asm(unsigned int x) {
int r;
__asm__("bsr %1,%0" : "=r"(r) : "X"(x));
return r;
}
#define _bit_scan_reverse(x) _Vc_bit_scan_reverse_asm(x)
# endif
#elif defined(_WIN32)
#include <intrin.h>
static inline __forceinline unsigned long _bit_scan_forward(unsigned long x) {
unsigned long index;
_BitScanForward(&index, x);
return index;
}
static inline __forceinline unsigned long _bit_scan_reverse(unsigned long x) {
unsigned long index;
_BitScanReverse(&index, x);
return index;
}
#elif defined(Vc_ICC)
#else
#endif
#endif
#ifndef VC_COMMON_SET_H_
#define VC_COMMON_SET_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace
{
static Vc_INTRINSIC Vc_CONST __m128i set(unsigned short x0, unsigned short x1, unsigned short x2, unsigned short x3,
unsigned short x4, unsigned short x5, unsigned short x6, unsigned short x7)
{
#if defined(Vc_GNU_ASM)
#if 0
__m128i r;
unsigned long long tmp0 = x3; tmp0 = (tmp0 << 16) | x2;
unsigned long long tmp1 = x1; tmp1 = (tmp1 << 16) | x0;
asm("vmovq %1,%0" : "=x"(r) : "r"((tmp0 << 32) | tmp1));
unsigned long long tmp2 = x7; tmp2 = (tmp2 << 16) | x6;
unsigned long long tmp3 = x5; tmp3 = (tmp3 << 16) | x4;
asm("vpinsrq $1,%1,%0,%0" : "+x"(r) : "r"((tmp2 << 32) | tmp3));
return r;
#elif defined(Vc_USE_VEX_CODING)
__m128i r0, r1;
unsigned int tmp0 = x1; tmp0 = (tmp0 << 16) | x0;
unsigned int tmp1 = x3; tmp1 = (tmp1 << 16) | x2;
unsigned int tmp2 = x5; tmp2 = (tmp2 << 16) | x4;
unsigned int tmp3 = x7; tmp3 = (tmp3 << 16) | x6;
asm("vmovd %1,%0" : "=x"(r0) : "r"(tmp0));
asm("vpinsrd $1,%1,%0,%0" : "+x"(r0) : "r"(tmp1));
asm("vmovd %1,%0" : "=x"(r1) : "r"(tmp2));
asm("vpinsrd $1,%1,%0,%0" : "+x"(r1) : "r"(tmp3));
asm("vpunpcklqdq %1,%0,%0" : "+x"(r0) : "x"(r1));
return r0;
#else
__m128i r0, r1;
unsigned int tmp0 = x1; tmp0 = (tmp0 << 16) | x0;
unsigned int tmp1 = x3; tmp1 = (tmp1 << 16) | x2;
unsigned int tmp2 = x5; tmp2 = (tmp2 << 16) | x4;
unsigned int tmp3 = x7; tmp3 = (tmp3 << 16) | x6;
asm("movd %1,%0" : "=x"(r0) : "r"(tmp0));
asm("pinsrd $1,%1,%0" : "+x"(r0) : "r"(tmp1));
asm("movd %1,%0" : "=x"(r1) : "r"(tmp2));
asm("pinsrd $1,%1,%0" : "+x"(r1) : "r"(tmp3));
asm("punpcklqdq %1,%0" : "+x"(r0) : "x"(r1));
return r0;
#endif
#else
unsigned int tmp0 = x1; tmp0 = (tmp0 << 16) | x0;
unsigned int tmp1 = x3; tmp1 = (tmp1 << 16) | x2;
unsigned int tmp2 = x5; tmp2 = (tmp2 << 16) | x4;
unsigned int tmp3 = x7; tmp3 = (tmp3 << 16) | x6;
return _mm_setr_epi32(tmp0, tmp1, tmp2, tmp3);
#endif
}
static Vc_INTRINSIC Vc_CONST __m128i set(short x0, short x1, short x2, short x3, short x4, short x5, short x6, short x7)
{
return set(static_cast<unsigned short>(x0), static_cast<unsigned short>(x1), static_cast<unsigned short>(x2),
static_cast<unsigned short>(x3), static_cast<unsigned short>(x4), static_cast<unsigned short>(x5),
static_cast<unsigned short>(x6), static_cast<unsigned short>(x7));
}
}
}
#endif
#ifndef VC_COMMON_GATHERIMPLEMENTATION_H_
#define VC_COMMON_GATHERIMPLEMENTATION_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
enum class GatherScatterImplementation : int {
SimpleLoop,
SetIndexZero,
BitScanLoop,
PopcntSwitch
};
using SimpleLoopT = std::integral_constant<GatherScatterImplementation, GatherScatterImplementation::SimpleLoop>;
using SetIndexZeroT = std::integral_constant<GatherScatterImplementation, GatherScatterImplementation::SetIndexZero>;
using BitScanLoopT = std::integral_constant<GatherScatterImplementation, GatherScatterImplementation::BitScanLoop>;
using PopcntSwitchT = std::integral_constant<GatherScatterImplementation, GatherScatterImplementation::PopcntSwitch>;
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeGather(SetIndexZeroT,
V &v,
const MT *mem,
IT &&indexes_,
typename V::MaskArgument mask)
{
auto indexes = std::forward<IT>(indexes_);
indexes.setZeroInverted(static_cast<decltype(!indexes)>(mask));
const V tmp(mem, indexes);
where(mask) | v = tmp;
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeGather(SimpleLoopT, V &v, const MT *mem, const IT &indexes,
const typename V::MaskArgument mask)
{
if (Vc_IS_UNLIKELY(mask.isEmpty())) {
return;
}
#if defined Vc_GCC && Vc_GCC >= 0x40900
constexpr std::size_t Sizeof = sizeof(V);
using Builtin [[gnu::vector_size(Sizeof)]] = typename V::value_type;
Builtin tmp = reinterpret_cast<Builtin>(v.data());
Common::unrolled_loop<std::size_t, 0, V::Size>([&](std::size_t i) {
if (mask[i]) {
tmp[i] = mem[indexes[i]];
}
});
v.data() = reinterpret_cast<typename V::VectorType>(tmp);
#else
Common::unrolled_loop<std::size_t, 0, V::Size>([&](std::size_t i) {
if (mask[i])
v[i] = mem[indexes[i]];
});
#endif
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeGather(BitScanLoopT,
V &v,
const MT *mem,
const IT &indexes,
typename V::MaskArgument mask)
{
#ifdef Vc_GNU_ASM
size_t bits = mask.toInt();
while (Vc_IS_LIKELY(bits > 0)) {
size_t i, j;
asm("bsf %[bits],%[i]\n\t"
"bsr %[bits],%[j]\n\t"
"btr %[i],%[bits]\n\t"
"btr %[j],%[bits]\n\t"
: [i] "=r"(i), [j] "=r"(j), [bits] "+r"(bits));
v[i] = mem[indexes[i]];
v[j] = mem[indexes[j]];
}
#else
int bits = mask.toInt();
while (bits) {
const int i = _bit_scan_forward(bits);
bits &= bits - 1;
v[i] = mem[indexes[i]];
}
#endif
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeGather(PopcntSwitchT,
V &v,
const MT *mem,
const IT &indexes,
typename V::MaskArgument mask,
enable_if<V::Size == 16> = nullarg)
{
unsigned int bits = mask.toInt();
unsigned int low, high = 0;
switch (Vc::Detail::popcnt16(bits)) {
case 16:
v.gather(mem, indexes);
break;
case 15:
low = _bit_scan_forward(bits);
bits ^= 1 << low;
v[low] = mem[indexes[low]];
case 14:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
high = (1 << high);
case 13:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
v[low] = mem[indexes[low]];
case 12:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
high = (1 << high);
case 11:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
v[low] = mem[indexes[low]];
case 10:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
high = (1 << high);
case 9:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
v[low] = mem[indexes[low]];
case 8:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
high = (1 << high);
case 7:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
v[low] = mem[indexes[low]];
case 6:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
high = (1 << high);
case 5:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
v[low] = mem[indexes[low]];
case 4:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
high = (1 << high);
case 3:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
v[low] = mem[indexes[low]];
case 2:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
case 1:
low = _bit_scan_forward(bits);
v[low] = mem[indexes[low]];
case 0:
break;
}
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeGather(PopcntSwitchT,
V &v,
const MT *mem,
const IT &indexes,
typename V::MaskArgument mask,
enable_if<V::Size == 8> = nullarg)
{
unsigned int bits = mask.toInt();
unsigned int low, high = 0;
switch (Vc::Detail::popcnt8(bits)) {
case 8:
v.gather(mem, indexes);
break;
case 7:
low = _bit_scan_forward(bits);
bits ^= 1 << low;
v[low] = mem[indexes[low]];
case 6:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
high = (1 << high);
case 5:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
v[low] = mem[indexes[low]];
case 4:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
high = (1 << high);
case 3:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
v[low] = mem[indexes[low]];
case 2:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
case 1:
low = _bit_scan_forward(bits);
v[low] = mem[indexes[low]];
case 0:
break;
}
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeGather(PopcntSwitchT,
V &v,
const MT *mem,
const IT &indexes,
typename V::MaskArgument mask,
enable_if<V::Size == 4> = nullarg)
{
unsigned int bits = mask.toInt();
unsigned int low, high = 0;
switch (Vc::Detail::popcnt4(bits)) {
case 4:
v.gather(mem, indexes);
break;
case 3:
low = _bit_scan_forward(bits);
bits ^= 1 << low;
v[low] = mem[indexes[low]];
case 2:
high = _bit_scan_reverse(bits);
v[high] = mem[indexes[high]];
case 1:
low = _bit_scan_forward(bits);
v[low] = mem[indexes[low]];
case 0:
break;
}
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeGather(PopcntSwitchT,
V &v,
const MT *mem,
const IT &indexes,
typename V::MaskArgument mask,
enable_if<V::Size == 2> = nullarg)
{
unsigned int bits = mask.toInt();
unsigned int low;
switch (Vc::Detail::popcnt4(bits)) {
case 2:
v.gather(mem, indexes);
break;
case 1:
low = _bit_scan_forward(bits);
v[low] = mem[indexes[low]];
case 0:
break;
}
}
}
}
#endif
#ifndef VC_COMMON_SCATTERIMPLEMENTATION_H_
#define VC_COMMON_SCATTERIMPLEMENTATION_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeScatter(SetIndexZeroT,
V &v,
MT *mem,
IT indexes,
typename V::MaskArgument mask)
{
indexes.setZeroInverted(static_cast<typename IT::Mask>(mask));
const V tmp(mem, indexes);
where(mask) | v = tmp;
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeScatter(SimpleLoopT,
V &v,
MT *mem,
const IT &indexes,
typename V::MaskArgument mask)
{
if (Vc_IS_UNLIKELY(mask.isEmpty())) {
return;
}
Common::unrolled_loop<std::size_t, 0, V::Size>([&](std::size_t i) {
if (mask[i])
mem[indexes[i]] = v[i];
});
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeScatter(BitScanLoopT,
V &v,
MT *mem,
const IT &indexes,
typename V::MaskArgument mask)
{
size_t bits = mask.toInt();
while (Vc_IS_LIKELY(bits > 0)) {
size_t i, j;
asm("bsf %[bits],%[i]\n\t"
"bsr %[bits],%[j]\n\t"
"btr %[i],%[bits]\n\t"
"btr %[j],%[bits]\n\t"
: [i] "=r"(i), [j] "=r"(j), [bits] "+r"(bits));
mem[indexes[i]] = v[i];
mem[indexes[j]] = v[j];
}
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeScatter(PopcntSwitchT,
V &v,
MT *mem,
const IT &indexes,
typename V::MaskArgument mask,
enable_if<V::Size == 16> = nullarg)
{
unsigned int bits = mask.toInt();
unsigned int low, high = 0;
switch (Vc::Detail::popcnt16(bits)) {
case 16:
v.scatter(mem, indexes);
break;
case 15:
low = _bit_scan_forward(bits);
bits ^= 1 << low;
mem[indexes[low]] = v[low];
case 14:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
high = (1 << high);
case 13:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
mem[indexes[low]] = v[low];
case 12:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
high = (1 << high);
case 11:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
mem[indexes[low]] = v[low];
case 10:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
high = (1 << high);
case 9:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
mem[indexes[low]] = v[low];
case 8:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
high = (1 << high);
case 7:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
mem[indexes[low]] = v[low];
case 6:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
high = (1 << high);
case 5:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
mem[indexes[low]] = v[low];
case 4:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
high = (1 << high);
case 3:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
mem[indexes[low]] = v[low];
case 2:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
case 1:
low = _bit_scan_forward(bits);
mem[indexes[low]] = v[low];
case 0:
break;
}
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeScatter(PopcntSwitchT,
V &v,
MT *mem,
const IT &indexes,
typename V::MaskArgument mask,
enable_if<V::Size == 8> = nullarg)
{
unsigned int bits = mask.toInt();
unsigned int low, high = 0;
switch (Vc::Detail::popcnt8(bits)) {
case 8:
v.scatter(mem, indexes);
break;
case 7:
low = _bit_scan_forward(bits);
bits ^= 1 << low;
mem[indexes[low]] = v[low];
case 6:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
high = (1 << high);
case 5:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
mem[indexes[low]] = v[low];
case 4:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
high = (1 << high);
case 3:
low = _bit_scan_forward(bits);
bits ^= high | (1 << low);
mem[indexes[low]] = v[low];
case 2:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
case 1:
low = _bit_scan_forward(bits);
mem[indexes[low]] = v[low];
case 0:
break;
}
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeScatter(PopcntSwitchT,
V &v,
MT *mem,
const IT &indexes,
typename V::MaskArgument mask,
enable_if<V::Size == 4> = nullarg)
{
unsigned int bits = mask.toInt();
unsigned int low, high = 0;
switch (Vc::Detail::popcnt4(bits)) {
case 4:
v.scatter(mem, indexes);
break;
case 3:
low = _bit_scan_forward(bits);
bits ^= 1 << low;
mem[indexes[low]] = v[low];
case 2:
high = _bit_scan_reverse(bits);
mem[indexes[high]] = v[high];
case 1:
low = _bit_scan_forward(bits);
mem[indexes[low]] = v[low];
case 0:
break;
}
}
template <typename V, typename MT, typename IT>
Vc_ALWAYS_INLINE void executeScatter(PopcntSwitchT,
V &v,
MT *mem,
const IT &indexes,
typename V::MaskArgument mask,
enable_if<V::Size == 2> = nullarg)
{
unsigned int bits = mask.toInt();
unsigned int low;
switch (Vc::Detail::popcnt4(bits)) {
case 2:
v.scatter(mem, indexes);
break;
case 1:
low = _bit_scan_forward(bits);
mem[indexes[low]] = v[low];
case 0:
break;
}
}
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
Vc_INTRINSIC SSE::double_m operator==(SSE::double_v a, SSE::double_v b) { return _mm_cmpeq_pd(a.data(), b.data()); }
Vc_INTRINSIC SSE:: float_m operator==(SSE:: float_v a, SSE:: float_v b) { return _mm_cmpeq_ps(a.data(), b.data()); }
Vc_INTRINSIC SSE:: int_m operator==(SSE:: int_v a, SSE:: int_v b) { return _mm_cmpeq_epi32(a.data(), b.data()); }
Vc_INTRINSIC SSE:: uint_m operator==(SSE:: uint_v a, SSE:: uint_v b) { return _mm_cmpeq_epi32(a.data(), b.data()); }
Vc_INTRINSIC SSE:: short_m operator==(SSE:: short_v a, SSE:: short_v b) { return _mm_cmpeq_epi16(a.data(), b.data()); }
Vc_INTRINSIC SSE::ushort_m operator==(SSE::ushort_v a, SSE::ushort_v b) { return _mm_cmpeq_epi16(a.data(), b.data()); }
Vc_INTRINSIC SSE::double_m operator!=(SSE::double_v a, SSE::double_v b) { return _mm_cmpneq_pd(a.data(), b.data()); }
Vc_INTRINSIC SSE:: float_m operator!=(SSE:: float_v a, SSE:: float_v b) { return _mm_cmpneq_ps(a.data(), b.data()); }
Vc_INTRINSIC SSE:: int_m operator!=(SSE:: int_v a, SSE:: int_v b) { return not_(_mm_cmpeq_epi32(a.data(), b.data())); }
Vc_INTRINSIC SSE:: uint_m operator!=(SSE:: uint_v a, SSE:: uint_v b) { return not_(_mm_cmpeq_epi32(a.data(), b.data())); }
Vc_INTRINSIC SSE:: short_m operator!=(SSE:: short_v a, SSE:: short_v b) { return not_(_mm_cmpeq_epi16(a.data(), b.data())); }
Vc_INTRINSIC SSE::ushort_m operator!=(SSE::ushort_v a, SSE::ushort_v b) { return not_(_mm_cmpeq_epi16(a.data(), b.data())); }
Vc_INTRINSIC SSE::double_m operator> (SSE::double_v a, SSE::double_v b) { return _mm_cmpgt_pd(a.data(), b.data()); }
Vc_INTRINSIC SSE:: float_m operator> (SSE:: float_v a, SSE:: float_v b) { return _mm_cmpgt_ps(a.data(), b.data()); }
Vc_INTRINSIC SSE:: int_m operator> (SSE:: int_v a, SSE:: int_v b) { return _mm_cmpgt_epi32(a.data(), b.data()); }
Vc_INTRINSIC SSE:: uint_m operator> (SSE:: uint_v a, SSE:: uint_v b) {
#ifndef USE_INCORRECT_UNSIGNED_COMPARE
return SSE::cmpgt_epu32(a.data(), b.data());
#else
return _mm_cmpgt_epi32(a.data(), b.data());
#endif
}
Vc_INTRINSIC SSE:: short_m operator> (SSE:: short_v a, SSE:: short_v b) { return _mm_cmpgt_epi16(a.data(), b.data()); }
Vc_INTRINSIC SSE::ushort_m operator> (SSE::ushort_v a, SSE::ushort_v b) {
#ifndef USE_INCORRECT_UNSIGNED_COMPARE
return SSE::cmpgt_epu16(a.data(), b.data());
#else
return _mm_cmpgt_epi16(a.data(), b.data());
#endif
}
Vc_INTRINSIC SSE::double_m operator< (SSE::double_v a, SSE::double_v b) { return _mm_cmplt_pd(a.data(), b.data()); }
Vc_INTRINSIC SSE:: float_m operator< (SSE:: float_v a, SSE:: float_v b) { return _mm_cmplt_ps(a.data(), b.data()); }
Vc_INTRINSIC SSE:: int_m operator< (SSE:: int_v a, SSE:: int_v b) { return _mm_cmplt_epi32(a.data(), b.data()); }
Vc_INTRINSIC SSE:: uint_m operator< (SSE:: uint_v a, SSE:: uint_v b) {
#ifndef USE_INCORRECT_UNSIGNED_COMPARE
return SSE::cmplt_epu32(a.data(), b.data());
#else
return _mm_cmplt_epi32(a.data(), b.data());
#endif
}
Vc_INTRINSIC SSE:: short_m operator< (SSE:: short_v a, SSE:: short_v b) { return _mm_cmplt_epi16(a.data(), b.data()); }
Vc_INTRINSIC SSE::ushort_m operator< (SSE::ushort_v a, SSE::ushort_v b) {
#ifndef USE_INCORRECT_UNSIGNED_COMPARE
return SSE::cmplt_epu16(a.data(), b.data());
#else
return _mm_cmplt_epi16(a.data(), b.data());
#endif
}
Vc_INTRINSIC SSE::double_m operator>=(SSE::double_v a, SSE::double_v b) { return _mm_cmpnlt_pd(a.data(), b.data()); }
Vc_INTRINSIC SSE:: float_m operator>=(SSE:: float_v a, SSE:: float_v b) { return _mm_cmpnlt_ps(a.data(), b.data()); }
Vc_INTRINSIC SSE:: int_m operator>=(SSE:: int_v a, SSE:: int_v b) { return !(a < b); }
Vc_INTRINSIC SSE:: uint_m operator>=(SSE:: uint_v a, SSE:: uint_v b) { return !(a < b); }
Vc_INTRINSIC SSE:: short_m operator>=(SSE:: short_v a, SSE:: short_v b) { return !(a < b); }
Vc_INTRINSIC SSE::ushort_m operator>=(SSE::ushort_v a, SSE::ushort_v b) { return !(a < b); }
Vc_INTRINSIC SSE::double_m operator<=(SSE::double_v a, SSE::double_v b) { return _mm_cmple_pd(a.data(), b.data()); }
Vc_INTRINSIC SSE:: float_m operator<=(SSE:: float_v a, SSE:: float_v b) { return _mm_cmple_ps(a.data(), b.data()); }
Vc_INTRINSIC SSE:: int_m operator<=(SSE:: int_v a, SSE:: int_v b) { return !(a > b); }
Vc_INTRINSIC SSE:: uint_m operator<=(SSE:: uint_v a, SSE:: uint_v b) { return !(a > b); }
Vc_INTRINSIC SSE:: short_m operator<=(SSE:: short_v a, SSE:: short_v b) { return !(a > b); }
Vc_INTRINSIC SSE::ushort_m operator<=(SSE::ushort_v a, SSE::ushort_v b) { return !(a > b); }
template <typename T>
Vc_INTRINSIC SSE::Vector<T> operator^(SSE::Vector<T> a, SSE::Vector<T> b)
{
return xor_(a.data(), b.data());
}
template <typename T>
Vc_INTRINSIC SSE::Vector<T> operator&(SSE::Vector<T> a, SSE::Vector<T> b)
{
return and_(a.data(), b.data());
}
template <typename T>
Vc_INTRINSIC SSE::Vector<T> operator|(SSE::Vector<T> a, SSE::Vector<T> b)
{
return or_(a.data(), b.data());
}
template <typename T>
Vc_INTRINSIC SSE::Vector<T> operator+(SSE::Vector<T> a, SSE::Vector<T> b)
{
return add(a.data(), b.data(), T());
}
template <typename T>
Vc_INTRINSIC SSE::Vector<T> operator-(SSE::Vector<T> a, SSE::Vector<T> b)
{
return sub(a.data(), b.data(), T());
}
template <typename T>
Vc_INTRINSIC SSE::Vector<T> operator*(SSE::Vector<T> a, SSE::Vector<T> b)
{
return mul(a.data(), b.data(), T());
}
template <typename T>
Vc_INTRINSIC enable_if<std::is_floating_point<T>::value, SSE::Vector<T>> operator/(
SSE::Vector<T> a, SSE::Vector<T> b)
{
return div(a.data(), b.data(), T());
}
template <typename T>
Vc_INTRINSIC
enable_if<std::is_same<int, T>::value || std::is_same<uint, T>::value, SSE::Vector<T>>
operator/(SSE::Vector<T> a, SSE::Vector<T> b)
{
return SSE::Vector<T>::generate([&](int i) { return a[i] / b[i]; });
}
template <typename T>
Vc_INTRINSIC enable_if<std::is_same<short, T>::value || std::is_same<ushort, T>::value,
SSE::Vector<T>>
operator/(SSE::Vector<T> a, SSE::Vector<T> b)
{
using HT = SSE::VectorHelper<T>;
__m128 lo = _mm_cvtepi32_ps(HT::expand0(a.data()));
__m128 hi = _mm_cvtepi32_ps(HT::expand1(a.data()));
lo = _mm_div_ps(lo, _mm_cvtepi32_ps(HT::expand0(b.data())));
hi = _mm_div_ps(hi, _mm_cvtepi32_ps(HT::expand1(b.data())));
return HT::concat(_mm_cvttps_epi32(lo), _mm_cvttps_epi32(hi));
}
template <typename T>
Vc_INTRINSIC enable_if<std::is_integral<T>::value, SSE::Vector<T>> operator%(
SSE::Vector<T> a, SSE::Vector<T> b)
{
return a - a / b * b;
}
}
template<typename T> Vc_INTRINSIC Vector<T, VectorAbi::Sse>::Vector(VectorSpecialInitializerZero)
: d(HV::zero())
{
}
template<typename T> Vc_INTRINSIC Vector<T, VectorAbi::Sse>::Vector(VectorSpecialInitializerOne)
: d(HT::one())
{
}
template <typename T>
Vc_INTRINSIC Vector<T, VectorAbi::Sse>::Vector(VectorSpecialInitializerIndexesFromZero)
: d(Detail::load16(Detail::IndexesFromZero<EntryType, Size>(), Aligned))
{
#if defined Vc_GCC && Vc_GCC < 0x40903 && defined Vc_IMPL_AVX2
if (std::is_same<T, short>::value) {
asm("" ::"x"(d.v()));
}
#endif
}
template <>
Vc_INTRINSIC Vector<float, VectorAbi::Sse>::Vector(VectorSpecialInitializerIndexesFromZero)
: d(SSE::convert<int, float>(SSE::int_v::IndexesFromZero().data()))
{
}
template <>
Vc_INTRINSIC Vector<double, VectorAbi::Sse>::Vector(VectorSpecialInitializerIndexesFromZero)
: d(SSE::convert<int, double>(SSE::int_v::IndexesFromZero().data()))
{
}
template <typename DstT>
template <typename SrcT, typename Flags>
Vc_INTRINSIC typename Vector<DstT, VectorAbi::Sse>::
#ifndef Vc_MSVC
template
#endif
load_concept<SrcT, Flags>::type Vector<DstT, VectorAbi::Sse>::load(const SrcT *mem, Flags flags)
{
Common::handleLoadPrefetches(mem, flags);
d.v() = Detail::load<VectorType, DstT>(mem, flags);
}
template<typename T> Vc_INTRINSIC void Vector<T, VectorAbi::Sse>::setZero()
{
data() = HV::zero();
}
template<typename T> Vc_INTRINSIC void Vector<T, VectorAbi::Sse>::setZero(const Mask &k)
{
data() = Detail::andnot_(SSE::sse_cast<VectorType>(k.data()), data());
}
template<typename T> Vc_INTRINSIC void Vector<T, VectorAbi::Sse>::setZeroInverted(const Mask &k)
{
data() = Detail::and_(SSE::sse_cast<VectorType>(k.data()), data());
}
template<> Vc_INTRINSIC void SSE::double_v::setQnan()
{
data() = SSE::_mm_setallone_pd();
}
template<> Vc_INTRINSIC void Vector<double, VectorAbi::Sse>::setQnan(const Mask &k)
{
data() = _mm_or_pd(data(), k.dataD());
}
template<> Vc_INTRINSIC void SSE::float_v::setQnan()
{
data() = SSE::_mm_setallone_ps();
}
template<> Vc_INTRINSIC void Vector<float, VectorAbi::Sse>::setQnan(const Mask &k)
{
data() = _mm_or_ps(data(), k.data());
}
template <typename T>
template <typename U, typename Flags, typename>
Vc_INTRINSIC void Vector<T, VectorAbi::Sse>::store(U *mem, Flags flags) const
{
Common::handleStorePrefetches(mem, flags);
HV::template store<Flags>(mem, data());
}
template <typename T>
template <typename U, typename Flags, typename>
Vc_INTRINSIC void Vector<T, VectorAbi::Sse>::store(U *mem, Mask mask, Flags flags) const
{
Common::handleStorePrefetches(mem, flags);
HV::template store<Flags>(mem, data(), sse_cast<VectorType>(mask.data()));
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::operator-() const
{
return Detail::negate(d.v(), std::integral_constant<std::size_t, sizeof(T)>());
}
#ifdef Vc_IMPL_XOP
template <> Vc_ALWAYS_INLINE SSE::int_v SSE::int_v::operator<<(const SSE::int_v shift) const { return _mm_sha_epi32(d.v(), shift.d.v()); }
template <> Vc_ALWAYS_INLINE SSE::uint_v SSE::uint_v::operator<<(const SSE::uint_v shift) const { return _mm_shl_epi32(d.v(), shift.d.v()); }
template <> Vc_ALWAYS_INLINE SSE::short_v SSE::short_v::operator<<(const SSE::short_v shift) const { return _mm_sha_epi16(d.v(), shift.d.v()); }
template <> Vc_ALWAYS_INLINE SSE::ushort_v SSE::ushort_v::operator<<(const SSE::ushort_v shift) const { return _mm_shl_epi16(d.v(), shift.d.v()); }
template <> Vc_ALWAYS_INLINE SSE::int_v SSE::int_v::operator>>(const SSE::int_v shift) const { return operator<<(-shift); }
template <> Vc_ALWAYS_INLINE SSE::uint_v SSE::uint_v::operator>>(const SSE::uint_v shift) const { return operator<<(-shift); }
template <> Vc_ALWAYS_INLINE SSE::short_v SSE::short_v::operator>>(const SSE::short_v shift) const { return operator<<(-shift); }
template <> Vc_ALWAYS_INLINE SSE::ushort_v SSE::ushort_v::operator>>(const SSE::ushort_v shift) const { return operator<<(-shift); }
#elif defined Vc_IMPL_AVX2
template <> Vc_ALWAYS_INLINE SSE::Vector< int> Vector< int, VectorAbi::Sse>::operator<<(const SSE::Vector< int> x) const { return _mm_sllv_epi32(d.v(), x.d.v()); }
template <> Vc_ALWAYS_INLINE SSE::Vector< uint> Vector< uint, VectorAbi::Sse>::operator<<(const SSE::Vector< uint> x) const { return _mm_sllv_epi32(d.v(), x.d.v()); }
template <> Vc_ALWAYS_INLINE SSE::Vector< int> Vector< int, VectorAbi::Sse>::operator>>(const SSE::Vector< int> x) const { return _mm_srav_epi32(d.v(), x.d.v()); }
template <> Vc_ALWAYS_INLINE SSE::Vector< uint> Vector< uint, VectorAbi::Sse>::operator>>(const SSE::Vector< uint> x) const { return _mm_srlv_epi32(d.v(), x.d.v()); }
#endif
template<typename T> Vc_ALWAYS_INLINE Vector<T, VectorAbi::Sse> &Vector<T, VectorAbi::Sse>::operator>>=(int shift) {
d.v() = HT::shiftRight(d.v(), shift);
return *this;
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::operator>>(int shift) const {
return HT::shiftRight(d.v(), shift);
}
template<typename T> Vc_ALWAYS_INLINE Vector<T, VectorAbi::Sse> &Vector<T, VectorAbi::Sse>::operator<<=(int shift) {
d.v() = HT::shiftLeft(d.v(), shift);
return *this;
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::operator<<(int shift) const {
return HT::shiftLeft(d.v(), shift);
}
Vc_INTRINSIC Vc_CONST SSE::float_m isnegative(SSE::float_v x)
{
return sse_cast<__m128>(_mm_srai_epi32(
sse_cast<__m128i>(_mm_and_ps(SSE::_mm_setsignmask_ps(), x.data())), 31));
}
Vc_INTRINSIC Vc_CONST SSE::double_m isnegative(SSE::double_v x)
{
return Mem::permute<X1, X1, X3, X3>(sse_cast<__m128>(_mm_srai_epi32(
sse_cast<__m128i>(_mm_and_pd(SSE::_mm_setsignmask_pd(), x.data())), 31)));
}
template <>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void SSE::double_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm_setr_pd(mem[indexes[0]], mem[indexes[1]]);
}
template <>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void SSE::float_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm_setr_ps(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]], mem[indexes[3]]);
}
template <>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void SSE::int_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm_setr_epi32(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]], mem[indexes[3]]);
}
template <>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void SSE::uint_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm_setr_epi32(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]], mem[indexes[3]]);
}
template <>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void SSE::short_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = Vc::set(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]], mem[indexes[3]],
mem[indexes[4]], mem[indexes[5]], mem[indexes[6]], mem[indexes[7]]);
}
template <>
template <typename MT, typename IT>
Vc_ALWAYS_INLINE void SSE::ushort_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = Vc::set(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]], mem[indexes[3]],
mem[indexes[4]], mem[indexes[5]], mem[indexes[6]], mem[indexes[7]]);
}
template <typename T>
template <typename MT, typename IT>
inline void Vector<T, VectorAbi::Sse>::gatherImplementation(const MT *mem,
const IT &indexes,
MaskArgument mask)
{
using Selector = std::integral_constant < Common::GatherScatterImplementation,
#ifdef Vc_USE_SET_GATHERS
Traits::is_simd_vector<IT>::value ? Common::GatherScatterImplementation::SetIndexZero :
#endif
#ifdef Vc_USE_BSF_GATHERS
Common::GatherScatterImplementation::BitScanLoop
#elif defined Vc_USE_POPCNT_BSF_GATHERS
Common::GatherScatterImplementation::PopcntSwitch
#else
Common::GatherScatterImplementation::SimpleLoop
#endif
> ;
Common::executeGather(Selector(), *this, mem, indexes, mask);
}
template <typename T>
template <typename MT, typename IT>
inline void Vector<T, VectorAbi::Sse>::scatterImplementation(MT *mem, IT &&indexes) const
{
Common::unrolled_loop<std::size_t, 0, Size>([&](std::size_t i) { mem[indexes[i]] = d.m(i); });
}
template <typename T>
template <typename MT, typename IT>
inline void Vector<T, VectorAbi::Sse>::scatterImplementation(MT *mem, IT &&indexes, MaskArgument mask) const
{
using Selector = std::integral_constant < Common::GatherScatterImplementation,
#ifdef Vc_USE_SET_GATHERS
Traits::is_simd_vector<IT>::value ? Common::GatherScatterImplementation::SetIndexZero :
#endif
#ifdef Vc_USE_BSF_GATHERS
Common::GatherScatterImplementation::BitScanLoop
#elif defined Vc_USE_POPCNT_BSF_GATHERS
Common::GatherScatterImplementation::PopcntSwitch
#else
Common::GatherScatterImplementation::SimpleLoop
#endif
> ;
Common::executeScatter(Selector(), *this, mem, indexes, mask);
}
template<typename T> Vc_ALWAYS_INLINE Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::partialSum() const
{
Vector<T, VectorAbi::Sse> tmp = *this;
if (Size > 1) tmp += tmp.shifted(-1);
if (Size > 2) tmp += tmp.shifted(-2);
if (Size > 4) tmp += tmp.shifted(-4);
if (Size > 8) tmp += tmp.shifted(-8);
if (Size > 16) tmp += tmp.shifted(-16);
return tmp;
}
#ifndef Vc_IMPL_SSE4_1
template<> Vc_INTRINSIC Vc_PURE int SSE::int_v::product() const
{
return (d.m(0) * d.m(1)) * (d.m(2) * d.m(3));
}
template<> Vc_INTRINSIC Vc_PURE unsigned int SSE::uint_v::product() const
{
return (d.m(0) * d.m(1)) * (d.m(2) * d.m(3));
}
#endif
template<typename T> Vc_ALWAYS_INLINE Vc_PURE typename Vector<T, VectorAbi::Sse>::EntryType Vector<T, VectorAbi::Sse>::min(MaskArg m) const
{
Vector<T, VectorAbi::Sse> tmp = std::numeric_limits<Vector<T, VectorAbi::Sse> >::max();
tmp(m) = *this;
return tmp.min();
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE typename Vector<T, VectorAbi::Sse>::EntryType Vector<T, VectorAbi::Sse>::max(MaskArg m) const
{
Vector<T, VectorAbi::Sse> tmp = std::numeric_limits<Vector<T, VectorAbi::Sse> >::min();
tmp(m) = *this;
return tmp.max();
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE typename Vector<T, VectorAbi::Sse>::EntryType Vector<T, VectorAbi::Sse>::product(MaskArg m) const
{
Vector<T, VectorAbi::Sse> tmp(Vc::One);
tmp(m) = *this;
return tmp.product();
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE typename Vector<T, VectorAbi::Sse>::EntryType Vector<T, VectorAbi::Sse>::sum(MaskArg m) const
{
Vector<T, VectorAbi::Sse> tmp(Vc::Zero);
tmp(m) = *this;
return tmp.sum();
}
namespace Detail
{
Vc_INTRINSIC Vc_CONST __m128 exponent(__m128 v)
{
__m128i tmp = _mm_srli_epi32(_mm_castps_si128(v), 23);
tmp = _mm_sub_epi32(tmp, _mm_set1_epi32(0x7f));
return _mm_cvtepi32_ps(tmp);
}
Vc_INTRINSIC Vc_CONST __m128d exponent(__m128d v)
{
__m128i tmp = _mm_srli_epi64(_mm_castpd_si128(v), 52);
tmp = _mm_sub_epi32(tmp, _mm_set1_epi32(0x3ff));
return _mm_cvtepi32_pd(_mm_shuffle_epi32(tmp, 0x08));
}
}
Vc_INTRINSIC Vc_CONST SSE::float_v exponent(SSE::float_v x)
{
using Detail::operator>=;
Vc_ASSERT((x >= x.Zero()).isFull());
return Detail::exponent(x.data());
}
Vc_INTRINSIC Vc_CONST SSE::double_v exponent(SSE::double_v x)
{
using Detail::operator>=;
Vc_ASSERT((x >= x.Zero()).isFull());
return Detail::exponent(x.data());
}
static void _doRandomStep(SSE::uint_v &state0,
SSE::uint_v &state1)
{
using SSE::uint_v;
using Detail::operator+;
using Detail::operator*;
state0.load(&Common::RandomState[0]);
state1.load(&Common::RandomState[uint_v::Size]);
(state1 * uint_v(0xdeece66du) + uint_v(11)).store(&Common::RandomState[uint_v::Size]);
uint_v(_mm_xor_si128((state0 * uint_v(0xdeece66du) + uint_v(11)).data(),
_mm_srli_epi32(state1.data(), 16)))
.store(&Common::RandomState[0]);
}
template<typename T> Vc_ALWAYS_INLINE Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::Random()
{
SSE::uint_v state0, state1;
_doRandomStep(state0, state1);
return state0.data();
}
template<> Vc_ALWAYS_INLINE SSE::float_v SSE::float_v::Random()
{
SSE::uint_v state0, state1;
_doRandomStep(state0, state1);
return _mm_sub_ps(_mm_or_ps(_mm_castsi128_ps(_mm_srli_epi32(state0.data(), 2)), HT::one()), HT::one());
}
template<> Vc_ALWAYS_INLINE SSE::double_v SSE::double_v::Random()
{
typedef unsigned long long uint64 Vc_MAY_ALIAS;
uint64 state0 = *reinterpret_cast<const uint64 *>(&Common::RandomState[8]);
uint64 state1 = *reinterpret_cast<const uint64 *>(&Common::RandomState[10]);
const __m128i state = _mm_load_si128(reinterpret_cast<const __m128i *>(&Common::RandomState[8]));
*reinterpret_cast<uint64 *>(&Common::RandomState[ 8]) = (state0 * 0x5deece66dull + 11);
*reinterpret_cast<uint64 *>(&Common::RandomState[10]) = (state1 * 0x5deece66dull + 11);
return _mm_sub_pd(_mm_or_pd(_mm_castsi128_pd(_mm_srli_epi64(state, 12)), HT::one()), HT::one());
}
template<typename T> Vc_INTRINSIC Vc_PURE Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::shifted(int amount) const
{
enum {
EntryTypeSizeof = sizeof(EntryType)
};
switch (amount) {
case 0: return *this;
case 1: return SSE::sse_cast<VectorType>(_mm_srli_si128(SSE::sse_cast<__m128i>(d.v()), 1 * EntryTypeSizeof));
case 2: return SSE::sse_cast<VectorType>(_mm_srli_si128(SSE::sse_cast<__m128i>(d.v()), 2 * EntryTypeSizeof));
case 3: return SSE::sse_cast<VectorType>(_mm_srli_si128(SSE::sse_cast<__m128i>(d.v()), 3 * EntryTypeSizeof));
case 4: return SSE::sse_cast<VectorType>(_mm_srli_si128(SSE::sse_cast<__m128i>(d.v()), 4 * EntryTypeSizeof));
case 5: return SSE::sse_cast<VectorType>(_mm_srli_si128(SSE::sse_cast<__m128i>(d.v()), 5 * EntryTypeSizeof));
case 6: return SSE::sse_cast<VectorType>(_mm_srli_si128(SSE::sse_cast<__m128i>(d.v()), 6 * EntryTypeSizeof));
case 7: return SSE::sse_cast<VectorType>(_mm_srli_si128(SSE::sse_cast<__m128i>(d.v()), 7 * EntryTypeSizeof));
case 8: return SSE::sse_cast<VectorType>(_mm_srli_si128(SSE::sse_cast<__m128i>(d.v()), 8 * EntryTypeSizeof));
case -1: return SSE::sse_cast<VectorType>(_mm_slli_si128(SSE::sse_cast<__m128i>(d.v()), 1 * EntryTypeSizeof));
case -2: return SSE::sse_cast<VectorType>(_mm_slli_si128(SSE::sse_cast<__m128i>(d.v()), 2 * EntryTypeSizeof));
case -3: return SSE::sse_cast<VectorType>(_mm_slli_si128(SSE::sse_cast<__m128i>(d.v()), 3 * EntryTypeSizeof));
case -4: return SSE::sse_cast<VectorType>(_mm_slli_si128(SSE::sse_cast<__m128i>(d.v()), 4 * EntryTypeSizeof));
case -5: return SSE::sse_cast<VectorType>(_mm_slli_si128(SSE::sse_cast<__m128i>(d.v()), 5 * EntryTypeSizeof));
case -6: return SSE::sse_cast<VectorType>(_mm_slli_si128(SSE::sse_cast<__m128i>(d.v()), 6 * EntryTypeSizeof));
case -7: return SSE::sse_cast<VectorType>(_mm_slli_si128(SSE::sse_cast<__m128i>(d.v()), 7 * EntryTypeSizeof));
case -8: return SSE::sse_cast<VectorType>(_mm_slli_si128(SSE::sse_cast<__m128i>(d.v()), 8 * EntryTypeSizeof));
}
return Zero();
}
template<typename T> Vc_INTRINSIC Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::shifted(int amount, Vector shiftIn) const
{
if (amount >= -int(size())) {
constexpr int VectorWidth = int(size());
constexpr int EntryTypeSizeof = sizeof(EntryType);
const __m128i v0 = sse_cast<__m128i>(d.v());
const __m128i v1 = sse_cast<__m128i>(shiftIn.d.v());
auto &&fixup = sse_cast<VectorType, __m128i>;
switch (amount) {
case 0: return *this;
case -1: return fixup(SSE::alignr_epi8<(VectorWidth - 1) * EntryTypeSizeof>(v0, v1));
case -2: return fixup(SSE::alignr_epi8<(VectorWidth - 2) * EntryTypeSizeof>(v0, v1));
case -3: return fixup(SSE::alignr_epi8<(VectorWidth - 3) * EntryTypeSizeof>(v0, v1));
case -4: return fixup(SSE::alignr_epi8<(VectorWidth - 4) * EntryTypeSizeof>(v0, v1));
case -5: return fixup(SSE::alignr_epi8<(VectorWidth - 5) * EntryTypeSizeof>(v0, v1));
case -6: return fixup(SSE::alignr_epi8<(VectorWidth - 6) * EntryTypeSizeof>(v0, v1));
case -7: return fixup(SSE::alignr_epi8<(VectorWidth - 7) * EntryTypeSizeof>(v0, v1));
case -8: return fixup(SSE::alignr_epi8<(VectorWidth - 8) * EntryTypeSizeof>(v0, v1));
case -9: return fixup(SSE::alignr_epi8<(VectorWidth - 9) * EntryTypeSizeof>(v0, v1));
case-10: return fixup(SSE::alignr_epi8<(VectorWidth -10) * EntryTypeSizeof>(v0, v1));
case-11: return fixup(SSE::alignr_epi8<(VectorWidth -11) * EntryTypeSizeof>(v0, v1));
case-12: return fixup(SSE::alignr_epi8<(VectorWidth -12) * EntryTypeSizeof>(v0, v1));
case-13: return fixup(SSE::alignr_epi8<(VectorWidth -13) * EntryTypeSizeof>(v0, v1));
case-14: return fixup(SSE::alignr_epi8<(VectorWidth -14) * EntryTypeSizeof>(v0, v1));
case-15: return fixup(SSE::alignr_epi8<(VectorWidth -15) * EntryTypeSizeof>(v0, v1));
case 1: return fixup(SSE::alignr_epi8< 1 * EntryTypeSizeof>(v1, v0));
case 2: return fixup(SSE::alignr_epi8< 2 * EntryTypeSizeof>(v1, v0));
case 3: return fixup(SSE::alignr_epi8< 3 * EntryTypeSizeof>(v1, v0));
case 4: return fixup(SSE::alignr_epi8< 4 * EntryTypeSizeof>(v1, v0));
case 5: return fixup(SSE::alignr_epi8< 5 * EntryTypeSizeof>(v1, v0));
case 6: return fixup(SSE::alignr_epi8< 6 * EntryTypeSizeof>(v1, v0));
case 7: return fixup(SSE::alignr_epi8< 7 * EntryTypeSizeof>(v1, v0));
case 8: return fixup(SSE::alignr_epi8< 8 * EntryTypeSizeof>(v1, v0));
case 9: return fixup(SSE::alignr_epi8< 9 * EntryTypeSizeof>(v1, v0));
case 10: return fixup(SSE::alignr_epi8<10 * EntryTypeSizeof>(v1, v0));
case 11: return fixup(SSE::alignr_epi8<11 * EntryTypeSizeof>(v1, v0));
case 12: return fixup(SSE::alignr_epi8<12 * EntryTypeSizeof>(v1, v0));
case 13: return fixup(SSE::alignr_epi8<13 * EntryTypeSizeof>(v1, v0));
case 14: return fixup(SSE::alignr_epi8<14 * EntryTypeSizeof>(v1, v0));
case 15: return fixup(SSE::alignr_epi8<15 * EntryTypeSizeof>(v1, v0));
}
}
return shiftIn.shifted(int(size()) + amount);
}
template<typename T> Vc_INTRINSIC Vc_PURE Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::rotated(int amount) const
{
enum {
EntryTypeSizeof = sizeof(EntryType)
};
const __m128i v = SSE::sse_cast<__m128i>(d.v());
switch (static_cast<unsigned int>(amount) % Size) {
case 0: return *this;
case 1: return SSE::sse_cast<VectorType>(SSE::alignr_epi8<1 * EntryTypeSizeof>(v, v));
case 2: return SSE::sse_cast<VectorType>(SSE::alignr_epi8<2 * EntryTypeSizeof>(v, v));
case 3: return SSE::sse_cast<VectorType>(SSE::alignr_epi8<3 * EntryTypeSizeof>(v, v));
case 4: return SSE::sse_cast<VectorType>(SSE::alignr_epi8<4 * EntryTypeSizeof>(v, v));
case 5: return SSE::sse_cast<VectorType>(SSE::alignr_epi8<5 * EntryTypeSizeof>(v, v));
case 6: return SSE::sse_cast<VectorType>(SSE::alignr_epi8<6 * EntryTypeSizeof>(v, v));
case 7: return SSE::sse_cast<VectorType>(SSE::alignr_epi8<7 * EntryTypeSizeof>(v, v));
}
return Zero();
}
namespace Detail
{
inline Vc_CONST SSE::double_v sorted(SSE::double_v x_)
{
const __m128d x = x_.data();
const __m128d y = _mm_shuffle_pd(x, x, _MM_SHUFFLE2(0, 1));
return _mm_unpacklo_pd(_mm_min_sd(x, y), _mm_max_sd(x, y));
}
}
template <typename T>
Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Sse> Vector<T, VectorAbi::Sse>::sorted()
const
{
return Detail::sorted(*this);
}
template <> Vc_INTRINSIC SSE::double_v SSE::double_v::interleaveLow (SSE::double_v x) const { return _mm_unpacklo_pd(data(), x.data()); }
template <> Vc_INTRINSIC SSE::double_v SSE::double_v::interleaveHigh(SSE::double_v x) const { return _mm_unpackhi_pd(data(), x.data()); }
template <> Vc_INTRINSIC SSE::float_v SSE::float_v::interleaveLow ( SSE::float_v x) const { return _mm_unpacklo_ps(data(), x.data()); }
template <> Vc_INTRINSIC SSE::float_v SSE::float_v::interleaveHigh( SSE::float_v x) const { return _mm_unpackhi_ps(data(), x.data()); }
template <> Vc_INTRINSIC SSE::int_v SSE::int_v::interleaveLow ( SSE::int_v x) const { return _mm_unpacklo_epi32(data(), x.data()); }
template <> Vc_INTRINSIC SSE::int_v SSE::int_v::interleaveHigh( SSE::int_v x) const { return _mm_unpackhi_epi32(data(), x.data()); }
template <> Vc_INTRINSIC SSE::uint_v SSE::uint_v::interleaveLow ( SSE::uint_v x) const { return _mm_unpacklo_epi32(data(), x.data()); }
template <> Vc_INTRINSIC SSE::uint_v SSE::uint_v::interleaveHigh( SSE::uint_v x) const { return _mm_unpackhi_epi32(data(), x.data()); }
template <> Vc_INTRINSIC SSE::short_v SSE::short_v::interleaveLow ( SSE::short_v x) const { return _mm_unpacklo_epi16(data(), x.data()); }
template <> Vc_INTRINSIC SSE::short_v SSE::short_v::interleaveHigh( SSE::short_v x) const { return _mm_unpackhi_epi16(data(), x.data()); }
template <> Vc_INTRINSIC SSE::ushort_v SSE::ushort_v::interleaveLow (SSE::ushort_v x) const { return _mm_unpacklo_epi16(data(), x.data()); }
template <> Vc_INTRINSIC SSE::ushort_v SSE::ushort_v::interleaveHigh(SSE::ushort_v x) const { return _mm_unpackhi_epi16(data(), x.data()); }
template <> template <typename G> Vc_INTRINSIC SSE::double_v SSE::double_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
return _mm_setr_pd(tmp0, tmp1);
}
template <> template <typename G> Vc_INTRINSIC SSE::float_v SSE::float_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
return _mm_setr_ps(tmp0, tmp1, tmp2, tmp3);
}
template <> template <typename G> Vc_INTRINSIC SSE::int_v SSE::int_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
return _mm_setr_epi32(tmp0, tmp1, tmp2, tmp3);
}
template <> template <typename G> Vc_INTRINSIC SSE::uint_v SSE::uint_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
return _mm_setr_epi32(tmp0, tmp1, tmp2, tmp3);
}
template <> template <typename G> Vc_INTRINSIC SSE::short_v SSE::short_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
const auto tmp4 = gen(4);
const auto tmp5 = gen(5);
const auto tmp6 = gen(6);
const auto tmp7 = gen(7);
return _mm_setr_epi16(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7);
}
template <> template <typename G> Vc_INTRINSIC SSE::ushort_v SSE::ushort_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
const auto tmp4 = gen(4);
const auto tmp5 = gen(5);
const auto tmp6 = gen(6);
const auto tmp7 = gen(7);
return _mm_setr_epi16(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7);
}
template <> Vc_INTRINSIC Vc_PURE SSE::double_v SSE::double_v::reversed() const
{
return Mem::permute<X1, X0>(d.v());
}
template <> Vc_INTRINSIC Vc_PURE SSE::float_v SSE::float_v::reversed() const
{
return Mem::permute<X3, X2, X1, X0>(d.v());
}
template <> Vc_INTRINSIC Vc_PURE SSE::int_v SSE::int_v::reversed() const
{
return Mem::permute<X3, X2, X1, X0>(d.v());
}
template <> Vc_INTRINSIC Vc_PURE SSE::uint_v SSE::uint_v::reversed() const
{
return Mem::permute<X3, X2, X1, X0>(d.v());
}
template <> Vc_INTRINSIC Vc_PURE SSE::short_v SSE::short_v::reversed() const
{
return sse_cast<__m128i>(
Mem::shuffle<X1, Y0>(sse_cast<__m128d>(Mem::permuteHi<X7, X6, X5, X4>(d.v())),
sse_cast<__m128d>(Mem::permuteLo<X3, X2, X1, X0>(d.v()))));
}
template <> Vc_INTRINSIC Vc_PURE SSE::ushort_v SSE::ushort_v::reversed() const
{
return sse_cast<__m128i>(
Mem::shuffle<X1, Y0>(sse_cast<__m128d>(Mem::permuteHi<X7, X6, X5, X4>(d.v())),
sse_cast<__m128d>(Mem::permuteLo<X3, X2, X1, X0>(d.v()))));
}
template <>
Vc_INTRINSIC SSE::float_v SSE::float_v::operator[](const SSE::int_v &
#ifdef Vc_IMPL_AVX
perm
#endif
) const
{
#ifdef Vc_IMPL_AVX
return _mm_permutevar_ps(d.v(), perm.data());
#else
return *this;
#endif
}
template <> template <int Index> Vc_INTRINSIC SSE::float_v SSE::float_v::broadcast() const
{
constexpr VecPos Inner = static_cast<VecPos>(Index & 0x3);
return Mem::permute<Inner, Inner, Inner, Inner>(d.v());
}
template <> template <int Index> Vc_INTRINSIC SSE::double_v SSE::double_v::broadcast() const
{
constexpr VecPos Inner = static_cast<VecPos>(Index & 0x1);
return Mem::permute<Inner, Inner>(d.v());
}
namespace Common
{
Vc_ALWAYS_INLINE void transpose_impl(
TransposeTag<4, 4>, SSE::float_v *Vc_RESTRICT r[],
const TransposeProxy<SSE::float_v, SSE::float_v, SSE::float_v, SSE::float_v> &proxy)
{
const auto in0 = std::get<0>(proxy.in).data();
const auto in1 = std::get<1>(proxy.in).data();
const auto in2 = std::get<2>(proxy.in).data();
const auto in3 = std::get<3>(proxy.in).data();
const auto tmp0 = _mm_unpacklo_ps(in0, in2);
const auto tmp1 = _mm_unpacklo_ps(in1, in3);
const auto tmp2 = _mm_unpackhi_ps(in0, in2);
const auto tmp3 = _mm_unpackhi_ps(in1, in3);
*r[0] = _mm_unpacklo_ps(tmp0, tmp1);
*r[1] = _mm_unpackhi_ps(tmp0, tmp1);
*r[2] = _mm_unpacklo_ps(tmp2, tmp3);
*r[3] = _mm_unpackhi_ps(tmp2, tmp3);
}
}
}
#ifndef VC_SSE_SIMD_CAST_H_
#define VC_SSE_SIMD_CAST_H_ 
#ifdef Vc_IMPL_AVX
#ifndef VC_AVX_CASTS_H_
#define VC_AVX_CASTS_H_ 
#ifndef VC_AVX_SHUFFLE_H_
#define VC_AVX_SHUFFLE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <int... Dst> struct Permutation {};
template <uint8_t... Sel> struct Mask {};
#ifdef Vc_IMPL_AVX2
template <uint8_t Sel0, uint8_t Sel1, uint8_t Sel2, uint8_t Sel3, uint8_t Sel4,
uint8_t Sel5, uint8_t Sel6, uint8_t Sel7, uint8_t Sel8, uint8_t Sel9,
uint8_t Sel10, uint8_t Sel11, uint8_t Sel12, uint8_t Sel13, uint8_t Sel14,
uint8_t Sel15>
Vc_INTRINSIC Vc_CONST __m256i
blend(__m256i a, __m256i b, Mask<Sel0, Sel1, Sel2, Sel3, Sel4, Sel5, Sel6, Sel7, Sel8,
Sel9, Sel10, Sel11, Sel12, Sel13, Sel14, Sel15>)
{
static_assert((Sel0 == 0 || Sel0 == 1) && (Sel1 == 0 || Sel1 == 1) &&
(Sel2 == 0 || Sel2 == 1) && (Sel3 == 0 || Sel3 == 1) &&
(Sel4 == 0 || Sel4 == 1) && (Sel5 == 0 || Sel5 == 1) &&
(Sel6 == 0 || Sel6 == 1) && (Sel7 == 0 || Sel7 == 1) &&
(Sel8 == 0 || Sel8 == 1) && (Sel9 == 0 || Sel9 == 1) &&
(Sel10 == 0 || Sel10 == 1) && (Sel11 == 0 || Sel11 == 1) &&
(Sel12 == 0 || Sel12 == 1) && (Sel13 == 0 || Sel13 == 1) &&
(Sel14 == 0 || Sel14 == 1) && (Sel15 == 0 || Sel15 == 1),
"Selectors must be 0 or 1 to select the value from a or b");
constexpr uint8_t mask = static_cast<uint8_t>(
(Sel0 << 0 ) | (Sel1 << 1 ) | (Sel2 << 2 ) | (Sel3 << 3 ) |
(Sel4 << 4 ) | (Sel5 << 5 ) | (Sel6 << 6 ) | (Sel7 << 7 ) |
(Sel8 << 8 ) | (Sel9 << 9 ) | (Sel10 << 10) | (Sel11 << 11) |
(Sel12 << 12) | (Sel13 << 13) | (Sel14 << 14) | (Sel15 << 15));
return _mm256_blend_epi16(a, b, mask);
}
#endif
}
namespace Mem
{
#ifdef Vc_IMPL_AVX2
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m256i Vc_CONST permuteLo(__m256i x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm256_shufflelo_epi16(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m256i Vc_CONST permuteHi(__m256i x) {
static_assert(Dst0 >= X4 && Dst1 >= X4 && Dst2 >= X4 && Dst3 >= X4, "Incorrect_Range");
static_assert(Dst0 <= X7 && Dst1 <= X7 && Dst2 <= X7 && Dst3 <= X7, "Incorrect_Range");
return _mm256_shufflehi_epi16(x, (Dst0 - X4) + (Dst1 - X4) * 4 + (Dst2 - X4) * 16 + (Dst3 - X4) * 64);
}
#endif
template<VecPos L, VecPos H> static Vc_ALWAYS_INLINE __m256 Vc_CONST permute128(__m256 x) {
static_assert((L >= X0 && L <= X1) || L == Const0, "Incorrect_Range");
static_assert((H >= X0 && H <= X1) || H == Const0, "Incorrect_Range");
return _mm256_permute2f128_ps(
x, x, (L == Const0 ? 0x8 : L) + (H == Const0 ? 0x80 : H * (1 << 4)));
}
template<VecPos L, VecPos H> static Vc_ALWAYS_INLINE __m256d Vc_CONST permute128(__m256d x) {
static_assert((L >= X0 && L <= X1) || L == Const0, "Incorrect_Range");
static_assert((H >= X0 && H <= X1) || H == Const0, "Incorrect_Range");
return _mm256_permute2f128_pd(
x, x, (L == Const0 ? 0x8 : L) + (H == Const0 ? 0x80 : H * (1 << 4)));
}
template<VecPos L, VecPos H> static Vc_ALWAYS_INLINE __m256i Vc_CONST permute128(__m256i x) {
static_assert((L >= X0 && L <= X1) || L == Const0, "Incorrect_Range");
static_assert((H >= X0 && H <= X1) || H == Const0, "Incorrect_Range");
#ifdef Vc_IMPL_AVX2
return _mm256_permute2x128_si256(
x, x, (L == Const0 ? 0x8 : L) + (H == Const0 ? 0x80 : H * (1 << 4)));
#else
return _mm256_permute2f128_si256(
x, x, (L == Const0 ? 0x8 : L) + (H == Const0 ? 0x80 : H * (1 << 4)));
#endif
}
template<VecPos L, VecPos H> static Vc_ALWAYS_INLINE __m256 Vc_CONST shuffle128(__m256 x, __m256 y) {
static_assert(L >= X0 && H >= X0, "Incorrect_Range");
static_assert(L <= Y1 && H <= Y1, "Incorrect_Range");
return _mm256_permute2f128_ps(x, y, (L < Y0 ? L : L - Y0 + 2) + (H < Y0 ? H : H - Y0 + 2) * (1 << 4));
}
template<VecPos L, VecPos H> static Vc_ALWAYS_INLINE __m256i Vc_CONST shuffle128(__m256i x, __m256i y) {
static_assert(L >= X0 && H >= X0, "Incorrect_Range");
static_assert(L <= Y1 && H <= Y1, "Incorrect_Range");
#ifdef Vc_IMPL_AVX2
return _mm256_permute2x128_si256(
x, y, (L < Y0 ? L : L - Y0 + 2) + (H < Y0 ? H : H - Y0 + 2) * (1 << 4));
#else
return _mm256_permute2f128_si256(
x, y, (L < Y0 ? L : L - Y0 + 2) + (H < Y0 ? H : H - Y0 + 2) * (1 << 4));
#endif
}
template<VecPos L, VecPos H> static Vc_ALWAYS_INLINE __m256d Vc_CONST shuffle128(__m256d x, __m256d y) {
static_assert(L >= X0 && H >= X0, "Incorrect_Range");
static_assert(L <= Y1 && H <= Y1, "Incorrect_Range");
return _mm256_permute2f128_pd(x, y, (L < Y0 ? L : L - Y0 + 2) + (H < Y0 ? H : H - Y0 + 2) * (1 << 4));
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m256d Vc_CONST permute(__m256d x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X2 && Dst3 >= X2, "Incorrect_Range");
static_assert(Dst0 <= X1 && Dst1 <= X1 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm256_permute_pd(x, Dst0 + Dst1 * 2 + (Dst2 - X2) * 4 + (Dst3 - X2) * 8);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m256 Vc_CONST permute(__m256 x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm256_permute_ps(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m256i Vc_CONST permute(__m256i x) {
return _mm256_castps_si256(permute<Dst0, Dst1, Dst2, Dst3>(_mm256_castsi256_ps(x)));
}
#ifdef Vc_IMPL_AVX2
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m256i Vc_CONST permute4x64(__m256i x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm256_permute4x64_epi64(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
#endif
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m256d Vc_CONST shuffle(__m256d x, __m256d y) {
static_assert(Dst0 >= X0 && Dst1 >= Y0 && Dst2 >= X2 && Dst3 >= Y2, "Incorrect_Range");
static_assert(Dst0 <= X1 && Dst1 <= Y1 && Dst2 <= X3 && Dst3 <= Y3, "Incorrect_Range");
return _mm256_shuffle_pd(x, y, Dst0 + (Dst1 - Y0) * 2 + (Dst2 - X2) * 4 + (Dst3 - Y2) * 8);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3> static Vc_ALWAYS_INLINE __m256 Vc_CONST shuffle(__m256 x, __m256 y) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= Y0 && Dst3 >= Y0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= Y3 && Dst3 <= Y3, "Incorrect_Range");
return _mm256_shuffle_ps(x, y, Dst0 + Dst1 * 4 + (Dst2 - Y0) * 16 + (Dst3 - Y0) * 64);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3, VecPos Dst4, VecPos Dst5, VecPos Dst6, VecPos Dst7>
static Vc_ALWAYS_INLINE __m256 Vc_CONST blend(__m256 x, __m256 y) {
static_assert(Dst0 == X0 || Dst0 == Y0, "Incorrect_Range");
static_assert(Dst1 == X1 || Dst1 == Y1, "Incorrect_Range");
static_assert(Dst2 == X2 || Dst2 == Y2, "Incorrect_Range");
static_assert(Dst3 == X3 || Dst3 == Y3, "Incorrect_Range");
static_assert(Dst4 == X4 || Dst4 == Y4, "Incorrect_Range");
static_assert(Dst5 == X5 || Dst5 == Y5, "Incorrect_Range");
static_assert(Dst6 == X6 || Dst6 == Y6, "Incorrect_Range");
static_assert(Dst7 == X7 || Dst7 == Y7, "Incorrect_Range");
return _mm256_blend_ps(x, y,
(Dst0 / Y0) * 1 + (Dst1 / Y1) * 2 +
(Dst2 / Y2) * 4 + (Dst3 / Y3) * 8 +
(Dst4 / Y4) * 16 + (Dst5 / Y5) * 32 +
(Dst6 / Y6) * 64 + (Dst7 / Y7) *128
);
}
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3, VecPos Dst4, VecPos Dst5, VecPos Dst6, VecPos Dst7>
static Vc_ALWAYS_INLINE __m256i Vc_CONST blend(__m256i x, __m256i y) {
return _mm256_castps_si256(blend<Dst0, Dst1, Dst2, Dst3, Dst4, Dst5, Dst6, Dst7>(_mm256_castsi256_ps(x), _mm256_castsi256_ps(y)));
}
template<VecPos Dst> struct ScaleForBlend { enum { Value = Dst >= X4 ? Dst - X4 + Y0 : Dst }; };
template<VecPos Dst0, VecPos Dst1, VecPos Dst2, VecPos Dst3, VecPos Dst4, VecPos Dst5, VecPos Dst6, VecPos Dst7>
static Vc_ALWAYS_INLINE __m256 Vc_CONST permute(__m256 x) {
static_assert(Dst0 >= X0 && Dst0 <= X7, "Incorrect_Range");
static_assert(Dst1 >= X0 && Dst1 <= X7, "Incorrect_Range");
static_assert(Dst2 >= X0 && Dst2 <= X7, "Incorrect_Range");
static_assert(Dst3 >= X0 && Dst3 <= X7, "Incorrect_Range");
static_assert(Dst4 >= X0 && Dst4 <= X7, "Incorrect_Range");
static_assert(Dst5 >= X0 && Dst5 <= X7, "Incorrect_Range");
static_assert(Dst6 >= X0 && Dst6 <= X7, "Incorrect_Range");
static_assert(Dst7 >= X0 && Dst7 <= X7, "Incorrect_Range");
if (Dst0 + X4 == Dst4 && Dst1 + X4 == Dst5 && Dst2 + X4 == Dst6 && Dst3 + X4 == Dst7) {
return permute<Dst0, Dst1, Dst2, Dst3>(x);
}
const __m128 loIn = _mm256_castps256_ps128(x);
const __m128 hiIn = _mm256_extractf128_ps(x, 1);
__m128 lo, hi;
if (Dst0 < X4 && Dst1 < X4 && Dst2 < X4 && Dst3 < X4) {
lo = _mm_permute_ps(loIn, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
} else if (Dst0 >= X4 && Dst1 >= X4 && Dst2 >= X4 && Dst3 >= X4) {
lo = _mm_permute_ps(hiIn, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
} else if (Dst0 < X4 && Dst1 < X4 && Dst2 >= X4 && Dst3 >= X4) {
lo = shuffle<Dst0, Dst1, Dst2 - X4 + Y0, Dst3 - X4 + Y0>(loIn, hiIn);
} else if (Dst0 >= X4 && Dst1 >= X4 && Dst2 < X4 && Dst3 < X4) {
lo = shuffle<Dst0 - X4, Dst1 - X4, Dst2 + Y0, Dst3 + Y0>(hiIn, loIn);
} else if (Dst0 == X0 && Dst1 == X4 && Dst2 == X1 && Dst3 == X5) {
lo = _mm_unpacklo_ps(loIn, hiIn);
} else if (Dst0 == X4 && Dst1 == X0 && Dst2 == X5 && Dst3 == X1) {
lo = _mm_unpacklo_ps(hiIn, loIn);
} else if (Dst0 == X2 && Dst1 == X6 && Dst2 == X3 && Dst3 == X7) {
lo = _mm_unpackhi_ps(loIn, hiIn);
} else if (Dst0 == X6 && Dst1 == X2 && Dst2 == X7 && Dst3 == X3) {
lo = _mm_unpackhi_ps(hiIn, loIn);
} else if (Dst0 % X4 == 0 && Dst1 % X4 == 1 && Dst2 % X4 == 2 && Dst3 % X4 == 3) {
lo = blend<ScaleForBlend<Dst0>::Value, ScaleForBlend<Dst1>::Value,
ScaleForBlend<Dst2>::Value, ScaleForBlend<Dst3>::Value>(loIn, hiIn);
}
if (Dst4 >= X4 && Dst5 >= X4 && Dst6 >= X4 && Dst7 >= X4) {
hi = _mm_permute_ps(hiIn, (Dst4 - X4) + (Dst5 - X4) * 4 + (Dst6 - X4) * 16 + (Dst7 - X4) * 64);
} else if (Dst4 < X4 && Dst5 < X4 && Dst6 < X4 && Dst7 < X4) {
hi = _mm_permute_ps(loIn, (Dst4 - X4) + (Dst5 - X4) * 4 + (Dst6 - X4) * 16 + (Dst7 - X4) * 64);
} else if (Dst4 < X4 && Dst5 < X4 && Dst6 >= X4 && Dst7 >= X4) {
hi = shuffle<Dst4, Dst5, Dst6 - X4 + Y0, Dst7 - X4 + Y0>(loIn, hiIn);
} else if (Dst4 >= X4 && Dst5 >= X4 && Dst6 < X4 && Dst7 < X4) {
hi = shuffle<Dst4 - X4, Dst5 - X4, Dst6 + Y0, Dst7 + Y0>(hiIn, loIn);
} else if (Dst4 == X0 && Dst5 == X4 && Dst6 == X1 && Dst7 == X5) {
hi = _mm_unpacklo_ps(loIn, hiIn);
} else if (Dst4 == X4 && Dst5 == X0 && Dst6 == X5 && Dst7 == X1) {
hi = _mm_unpacklo_ps(hiIn, loIn);
} else if (Dst4 == X2 && Dst5 == X6 && Dst6 == X3 && Dst7 == X7) {
hi = _mm_unpackhi_ps(loIn, hiIn);
} else if (Dst4 == X6 && Dst5 == X2 && Dst6 == X7 && Dst7 == X3) {
hi = _mm_unpackhi_ps(hiIn, loIn);
} else if (Dst4 % X4 == 0 && Dst5 % X4 == 1 && Dst6 % X4 == 2 && Dst7 % X4 == 3) {
hi = blend<ScaleForBlend<Dst4>::Value, ScaleForBlend<Dst5>::Value,
ScaleForBlend<Dst6>::Value, ScaleForBlend<Dst7>::Value>(loIn, hiIn);
}
return _mm256_insertf128_ps(_mm256_castps128_ps256(lo), hi, 1);
}
}
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace Reg
{
template<VecPos H, VecPos L> static Vc_ALWAYS_INLINE __m256 Vc_CONST permute128(__m256 x, __m256 y) {
static_assert(L >= X0 && H >= X0, "Incorrect_Range");
static_assert(L <= Y1 && H <= Y1, "Incorrect_Range");
return _mm256_permute2f128_ps(x, y, (L < Y0 ? L : L - Y0 + 2) + (H < Y0 ? H : H - Y0 + 2) * (1 << 4));
}
template<VecPos H, VecPos L> static Vc_ALWAYS_INLINE __m256i Vc_CONST permute128(__m256i x, __m256i y) {
static_assert(L >= X0 && H >= X0, "Incorrect_Range");
static_assert(L <= Y1 && H <= Y1, "Incorrect_Range");
#ifdef Vc_IMPL_AVX2
return _mm256_permute2x128_si256(
x, y, (L < Y0 ? L : L - Y0 + 2) + (H < Y0 ? H : H - Y0 + 2) * (1 << 4));
#else
return _mm256_permute2f128_si256(
x, y, (L < Y0 ? L : L - Y0 + 2) + (H < Y0 ? H : H - Y0 + 2) * (1 << 4));
#endif
}
template<VecPos H, VecPos L> static Vc_ALWAYS_INLINE __m256d Vc_CONST permute128(__m256d x, __m256d y) {
static_assert(L >= X0 && H >= X0, "Incorrect_Range");
static_assert(L <= Y1 && H <= Y1, "Incorrect_Range");
return _mm256_permute2f128_pd(x, y, (L < Y0 ? L : L - Y0 + 2) + (H < Y0 ? H : H - Y0 + 2) * (1 << 4));
}
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m256d Vc_CONST permute(__m256d x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X2 && Dst3 >= X2, "Incorrect_Range");
static_assert(Dst0 <= X1 && Dst1 <= X1 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm256_permute_pd(x, Dst0 + Dst1 * 2 + (Dst2 - X2) * 4 + (Dst3 - X2) * 8);
}
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m256 Vc_CONST permute(__m256 x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm256_permute_ps(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
template<VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m128d Vc_CONST permute(__m128d x) {
static_assert(Dst0 >= X0 && Dst1 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X1 && Dst1 <= X1, "Incorrect_Range");
return _mm_permute_pd(x, Dst0 + Dst1 * 2);
}
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m128 Vc_CONST permute(__m128 x) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= X0 && Dst3 >= X0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= X3 && Dst3 <= X3, "Incorrect_Range");
return _mm_permute_ps(x, Dst0 + Dst1 * 4 + Dst2 * 16 + Dst3 * 64);
}
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m256d Vc_CONST shuffle(__m256d x, __m256d y) {
static_assert(Dst0 >= X0 && Dst1 >= Y0 && Dst2 >= X2 && Dst3 >= Y2, "Incorrect_Range");
static_assert(Dst0 <= X1 && Dst1 <= Y1 && Dst2 <= X3 && Dst3 <= Y3, "Incorrect_Range");
return _mm256_shuffle_pd(x, y, Dst0 + (Dst1 - Y0) * 2 + (Dst2 - X2) * 4 + (Dst3 - Y2) * 8);
}
template<VecPos Dst3, VecPos Dst2, VecPos Dst1, VecPos Dst0> static Vc_ALWAYS_INLINE __m256 Vc_CONST shuffle(__m256 x, __m256 y) {
static_assert(Dst0 >= X0 && Dst1 >= X0 && Dst2 >= Y0 && Dst3 >= Y0, "Incorrect_Range");
static_assert(Dst0 <= X3 && Dst1 <= X3 && Dst2 <= Y3 && Dst3 <= Y3, "Incorrect_Range");
return _mm256_shuffle_ps(x, y, Dst0 + Dst1 * 4 + (Dst2 - Y0) * 16 + (Dst3 - Y0) * 64);
}
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace AVX
{
namespace Casts
{
template<typename T> Vc_INTRINSIC_L T avx_cast(__m128 v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T avx_cast(__m128i v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T avx_cast(__m128d v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T avx_cast(__m256 v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T avx_cast(__m256i v) Vc_INTRINSIC_R;
template<typename T> Vc_INTRINSIC_L T avx_cast(__m256d v) Vc_INTRINSIC_R;
template<> Vc_INTRINSIC __m128 avx_cast(__m128 v) { return v; }
template<> Vc_INTRINSIC __m128 avx_cast(__m128i v) { return _mm_castsi128_ps(v); }
template<> Vc_INTRINSIC __m128 avx_cast(__m128d v) { return _mm_castpd_ps(v); }
template<> Vc_INTRINSIC __m128i avx_cast(__m128 v) { return _mm_castps_si128(v); }
template<> Vc_INTRINSIC __m128i avx_cast(__m128i v) { return v; }
template<> Vc_INTRINSIC __m128i avx_cast(__m128d v) { return _mm_castpd_si128(v); }
template<> Vc_INTRINSIC __m128d avx_cast(__m128 v) { return _mm_castps_pd(v); }
template<> Vc_INTRINSIC __m128d avx_cast(__m128i v) { return _mm_castsi128_pd(v); }
template<> Vc_INTRINSIC __m128d avx_cast(__m128d v) { return v; }
template<> Vc_INTRINSIC __m256 avx_cast(__m128 v) { return _mm256_castps128_ps256(v); }
template<> Vc_INTRINSIC __m256 avx_cast(__m128i v) { return _mm256_castps128_ps256(_mm_castsi128_ps(v)); }
template<> Vc_INTRINSIC __m256 avx_cast(__m128d v) { return _mm256_castps128_ps256(_mm_castpd_ps(v)); }
template<> Vc_INTRINSIC __m256i avx_cast(__m128 v) { return _mm256_castsi128_si256(_mm_castps_si128(v)); }
template<> Vc_INTRINSIC __m256i avx_cast(__m128i v) { return _mm256_castsi128_si256(v); }
template<> Vc_INTRINSIC __m256i avx_cast(__m128d v) { return _mm256_castsi128_si256(_mm_castpd_si128(v)); }
template<> Vc_INTRINSIC __m256d avx_cast(__m128 v) { return _mm256_castpd128_pd256(_mm_castps_pd(v)); }
template<> Vc_INTRINSIC __m256d avx_cast(__m128i v) { return _mm256_castpd128_pd256(_mm_castsi128_pd(v)); }
template<> Vc_INTRINSIC __m256d avx_cast(__m128d v) { return _mm256_castpd128_pd256(v); }
#if defined Vc_MSVC || defined Vc_CLANG || defined Vc_APPLECLANG
static Vc_INTRINSIC Vc_CONST __m256 zeroExtend(__m128 v) { return _mm256_permute2f128_ps (_mm256_castps128_ps256(v), _mm256_castps128_ps256(v), 0x80); }
static Vc_INTRINSIC Vc_CONST __m256i zeroExtend(__m128i v) { return _mm256_permute2f128_si256(_mm256_castsi128_si256(v), _mm256_castsi128_si256(v), 0x80); }
static Vc_INTRINSIC Vc_CONST __m256d zeroExtend(__m128d v) { return _mm256_permute2f128_pd (_mm256_castpd128_pd256(v), _mm256_castpd128_pd256(v), 0x80); }
#else
static Vc_INTRINSIC Vc_CONST __m256 zeroExtend(__m128 v) { return _mm256_castps128_ps256(v); }
static Vc_INTRINSIC Vc_CONST __m256i zeroExtend(__m128i v) { return _mm256_castsi128_si256(v); }
static Vc_INTRINSIC Vc_CONST __m256d zeroExtend(__m128d v) { return _mm256_castpd128_pd256(v); }
#endif
template<> Vc_INTRINSIC __m128 avx_cast(__m256 v) { return _mm256_castps256_ps128(v); }
template<> Vc_INTRINSIC __m128 avx_cast(__m256i v) { return _mm256_castps256_ps128(_mm256_castsi256_ps(v)); }
template<> Vc_INTRINSIC __m128 avx_cast(__m256d v) { return _mm256_castps256_ps128(_mm256_castpd_ps(v)); }
template<> Vc_INTRINSIC __m128i avx_cast(__m256 v) { return _mm256_castsi256_si128(_mm256_castps_si256(v)); }
template<> Vc_INTRINSIC __m128i avx_cast(__m256i v) { return _mm256_castsi256_si128(v); }
template<> Vc_INTRINSIC __m128i avx_cast(__m256d v) { return _mm256_castsi256_si128(_mm256_castpd_si256(v)); }
template<> Vc_INTRINSIC __m128d avx_cast(__m256 v) { return _mm256_castpd256_pd128(_mm256_castps_pd(v)); }
template<> Vc_INTRINSIC __m128d avx_cast(__m256i v) { return _mm256_castpd256_pd128(_mm256_castsi256_pd(v)); }
template<> Vc_INTRINSIC __m128d avx_cast(__m256d v) { return _mm256_castpd256_pd128(v); }
template<> Vc_INTRINSIC __m256 avx_cast(__m256 v) { return v; }
template<> Vc_INTRINSIC __m256 avx_cast(__m256i v) { return _mm256_castsi256_ps(v); }
template<> Vc_INTRINSIC __m256 avx_cast(__m256d v) { return _mm256_castpd_ps(v); }
template<> Vc_INTRINSIC __m256i avx_cast(__m256 v) { return _mm256_castps_si256(v); }
template<> Vc_INTRINSIC __m256i avx_cast(__m256i v) { return v; }
template<> Vc_INTRINSIC __m256i avx_cast(__m256d v) { return _mm256_castpd_si256(v); }
template<> Vc_INTRINSIC __m256d avx_cast(__m256 v) { return _mm256_castps_pd(v); }
template<> Vc_INTRINSIC __m256d avx_cast(__m256i v) { return _mm256_castsi256_pd(v); }
template<> Vc_INTRINSIC __m256d avx_cast(__m256d v) { return v; }
Vc_INTRINSIC Vc_CONST __m128 lo128(__m256 v) { return avx_cast<__m128>(v); }
Vc_INTRINSIC Vc_CONST __m128d lo128(__m256d v) { return avx_cast<__m128d>(v); }
Vc_INTRINSIC Vc_CONST __m128i lo128(__m256i v) { return avx_cast<__m128i>(v); }
Vc_INTRINSIC Vc_CONST __m128 hi128(__m256 v) { return extract128<1>(v); }
Vc_INTRINSIC Vc_CONST __m128d hi128(__m256d v) { return extract128<1>(v); }
Vc_INTRINSIC Vc_CONST __m128i hi128(__m256i v) { return extract128<1>(v); }
Vc_INTRINSIC Vc_CONST __m256 concat(__m128 a, __m128 b) { return insert128<1>(avx_cast<__m256 >(a), b); }
Vc_INTRINSIC Vc_CONST __m256d concat(__m128d a, __m128d b) { return insert128<1>(avx_cast<__m256d>(a), b); }
Vc_INTRINSIC Vc_CONST __m256i concat(__m128i a, __m128i b) { return insert128<1>(avx_cast<__m256i>(a), b); }
}
using namespace Casts;
}
namespace AVX2
{
using namespace AVX::Casts;
}
namespace AVX
{
template <typename From, typename To> struct ConvertTag {};
Vc_INTRINSIC __m256i convert(__m256 v, ConvertTag<float , int>) { return _mm256_cvttps_epi32(v); }
Vc_INTRINSIC __m128i convert(__m256d v, ConvertTag<double, int>) { return _mm256_cvttpd_epi32(v); }
Vc_INTRINSIC __m256i convert(__m256i v, ConvertTag<int , int>) { return v; }
Vc_INTRINSIC __m256i convert(__m256i v, ConvertTag<uint , int>) { return v; }
Vc_INTRINSIC __m256i convert(__m128i v, ConvertTag<short , int>) {
#ifdef Vc_IMPL_AVX2
return _mm256_cvtepi16_epi32(v);
#else
return AVX::srai_epi32<16>(
concat(_mm_unpacklo_epi16(v, v), _mm_unpackhi_epi16(v, v)));
#endif
}
Vc_INTRINSIC __m256i convert(__m128i v, ConvertTag<ushort, int>) {
#ifdef Vc_IMPL_AVX2
return _mm256_cvtepu16_epi32(v);
#else
return AVX::srli_epi32<16>(
concat(_mm_unpacklo_epi16(v, v), _mm_unpackhi_epi16(v, v)));
#endif
}
Vc_INTRINSIC __m256i convert(__m256 v, ConvertTag<float , uint>) {
using namespace AVX;
return _mm256_castps_si256(_mm256_blendv_ps(
_mm256_castsi256_ps(_mm256_cvttps_epi32(v)),
_mm256_castsi256_ps(add_epi32(_mm256_cvttps_epi32(_mm256_sub_ps(v, set2power31_ps())),
set2power31_epu32())),
cmpge_ps(v, set2power31_ps())));
}
Vc_INTRINSIC __m128i convert(__m256d v, ConvertTag<double, uint>) {
using namespace AVX;
return _mm_xor_si128(
_mm256_cvttpd_epi32(_mm256_sub_pd(_mm256_floor_pd(v), set1_pd(0x80000000u))),
_mm_set2power31_epu32());
}
Vc_INTRINSIC __m256i convert(__m256i v, ConvertTag<int , uint>) { return v; }
Vc_INTRINSIC __m256i convert(__m256i v, ConvertTag<uint , uint>) { return v; }
Vc_INTRINSIC __m256i convert(__m128i v, ConvertTag<short , uint>) {
#ifdef Vc_IMPL_AVX2
return _mm256_cvtepi16_epi32(v);
#else
return AVX::srai_epi32<16>(
concat(_mm_unpacklo_epi16(v, v), _mm_unpackhi_epi16(v, v)));
#endif
}
Vc_INTRINSIC __m256i convert(__m128i v, ConvertTag<ushort, uint>) {
#ifdef Vc_IMPL_AVX2
return _mm256_cvtepu16_epi32(v);
#else
return AVX::srli_epi32<16>(
concat(_mm_unpacklo_epi16(v, v), _mm_unpackhi_epi16(v, v)));
#endif
}
Vc_INTRINSIC __m256 convert(__m256 v, ConvertTag<float , float>) { return v; }
Vc_INTRINSIC __m128 convert(__m256d v, ConvertTag<double, float>) { return _mm256_cvtpd_ps(v); }
Vc_INTRINSIC __m256 convert(__m256i v, ConvertTag<int , float>) { return _mm256_cvtepi32_ps(v); }
Vc_INTRINSIC __m256 convert(__m256i v, ConvertTag<uint , float>) {
using namespace AVX;
return _mm256_blendv_ps(
_mm256_cvtepi32_ps(v),
_mm256_add_ps(_mm256_cvtepi32_ps(and_si256(v, set1_epi32(0x7ffffe00))),
_mm256_add_ps(set2power31_ps(), _mm256_cvtepi32_ps(and_si256(
v, set1_epi32(0x000001ff))))),
_mm256_castsi256_ps(cmplt_epi32(v, _mm256_setzero_si256())));
}
Vc_INTRINSIC __m256 convert(__m128i v, ConvertTag<short , float>) { return _mm256_cvtepi32_ps(convert(v, ConvertTag< short, int>())); }
Vc_INTRINSIC __m256 convert(__m128i v, ConvertTag<ushort, float>) { return _mm256_cvtepi32_ps(convert(v, ConvertTag<ushort, int>())); }
Vc_INTRINSIC __m256d convert(__m128 v, ConvertTag<float , double>) { return _mm256_cvtps_pd(v); }
Vc_INTRINSIC __m256d convert(__m256d v, ConvertTag<double, double>) { return v; }
Vc_INTRINSIC __m256d convert(__m128i v, ConvertTag<int , double>) { return _mm256_cvtepi32_pd(v); }
Vc_INTRINSIC __m256d convert(__m128i v, ConvertTag<uint , double>) {
using namespace AVX;
return _mm256_add_pd(
_mm256_cvtepi32_pd(_mm_xor_si128(v, _mm_setmin_epi32())),
set1_pd(1u << 31)); }
Vc_INTRINSIC __m256d convert(__m128i v, ConvertTag<short , double>) { return convert(convert(v, SSE::ConvertTag< short, int>()), ConvertTag<int, double>()); }
Vc_INTRINSIC __m256d convert(__m128i v, ConvertTag<ushort, double>) { return convert(convert(v, SSE::ConvertTag<ushort, int>()), ConvertTag<int, double>()); }
Vc_INTRINSIC __m128i convert(__m256i v, ConvertTag<int , short>) {
const auto tmp0 = _mm_unpacklo_epi16(lo128(v), hi128(v));
const auto tmp1 = _mm_unpackhi_epi16(lo128(v), hi128(v));
const auto tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
const auto tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
return _mm_unpacklo_epi16(tmp2, tmp3);
}
Vc_INTRINSIC __m128i convert(__m256i v, ConvertTag<uint , short>) {
const auto tmp0 = _mm_unpacklo_epi16(lo128(v), hi128(v));
const auto tmp1 = _mm_unpackhi_epi16(lo128(v), hi128(v));
const auto tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
const auto tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
return _mm_unpacklo_epi16(tmp2, tmp3);
}
Vc_INTRINSIC __m128i convert(__m256 v, ConvertTag<float , short>) { return convert(convert(v, ConvertTag<float, int>()), ConvertTag<int, short>()); }
Vc_INTRINSIC __m128i convert(__m256d v, ConvertTag<double, short>) { return convert(convert(v, ConvertTag<double, int>()), SSE::ConvertTag<int, short>()); }
Vc_INTRINSIC __m256i convert(__m256i v, ConvertTag<short , short>) { return v; }
Vc_INTRINSIC __m256i convert(__m256i v, ConvertTag<ushort, short>) { return v; }
Vc_INTRINSIC __m128i convert(__m256i v, ConvertTag<int , ushort>) {
auto tmp0 = _mm_unpacklo_epi16(lo128(v), hi128(v));
auto tmp1 = _mm_unpackhi_epi16(lo128(v), hi128(v));
auto tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
return _mm_unpacklo_epi16(tmp2, tmp3);
}
Vc_INTRINSIC __m128i convert(__m256i v, ConvertTag<uint , ushort>) {
auto tmp0 = _mm_unpacklo_epi16(lo128(v), hi128(v));
auto tmp1 = _mm_unpackhi_epi16(lo128(v), hi128(v));
auto tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
return _mm_unpacklo_epi16(tmp2, tmp3);
}
Vc_INTRINSIC __m128i convert(__m256 v, ConvertTag<float , ushort>) { return convert(convert(v, ConvertTag<float, uint>()), ConvertTag<uint, ushort>()); }
Vc_INTRINSIC __m128i convert(__m256d v, ConvertTag<double, ushort>) { return convert(convert(v, ConvertTag<double, uint>()), SSE::ConvertTag<uint, ushort>()); }
Vc_INTRINSIC __m256i convert(__m256i v, ConvertTag<short , ushort>) { return v; }
Vc_INTRINSIC __m256i convert(__m256i v, ConvertTag<ushort, ushort>) { return v; }
template <typename From, typename To>
Vc_INTRINSIC auto convert(
typename std::conditional<(sizeof(From) < sizeof(To)),
typename SSE::VectorTraits<From>::VectorType,
typename AVX::VectorTypeHelper<From>::Type>::type v)
-> decltype(convert(v, ConvertTag<From, To>()))
{
return convert(v, ConvertTag<From, To>());
}
template <typename From, typename To, typename = enable_if<(sizeof(From) < sizeof(To))>>
Vc_INTRINSIC auto convert(typename AVX::VectorTypeHelper<From>::Type v)
-> decltype(convert(lo128(v), ConvertTag<From, To>()))
{
return convert(lo128(v), ConvertTag<From, To>());
}
}
}
#endif
#endif
#ifndef VC_SSE_VECTOR_H_
#error "Vc/sse/vector.h needs to be included before Vc/sse/simd_cast.h"
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace SSE
{
#define Vc_SIMD_CAST_1(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x, enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_2(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_4(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, from_ x2, from_ x3, \
enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_8(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, from_ x5, from_ x6, from_ x7, \
enable_if<std::is_same<To, to_>::value> = nullarg)
Vc_SIMD_CAST_1( float_v, int_v);
Vc_SIMD_CAST_1(double_v, int_v);
Vc_SIMD_CAST_1( uint_v, int_v);
Vc_SIMD_CAST_1( short_v, int_v);
Vc_SIMD_CAST_1(ushort_v, int_v);
Vc_SIMD_CAST_1( float_v, uint_v);
Vc_SIMD_CAST_1(double_v, uint_v);
Vc_SIMD_CAST_1( int_v, uint_v);
Vc_SIMD_CAST_1( short_v, uint_v);
Vc_SIMD_CAST_1(ushort_v, uint_v);
Vc_SIMD_CAST_1(double_v, float_v);
Vc_SIMD_CAST_1( int_v, float_v);
Vc_SIMD_CAST_1( uint_v, float_v);
Vc_SIMD_CAST_1( short_v, float_v);
Vc_SIMD_CAST_1(ushort_v, float_v);
Vc_SIMD_CAST_1( float_v, double_v);
Vc_SIMD_CAST_1( int_v, double_v);
Vc_SIMD_CAST_1( uint_v, double_v);
Vc_SIMD_CAST_1( short_v, double_v);
Vc_SIMD_CAST_1(ushort_v, double_v);
Vc_SIMD_CAST_1( int_v, short_v);
Vc_SIMD_CAST_1( uint_v, short_v);
Vc_SIMD_CAST_1( float_v, short_v);
Vc_SIMD_CAST_1(double_v, short_v);
Vc_SIMD_CAST_1(ushort_v, short_v);
Vc_SIMD_CAST_1( int_v, ushort_v);
Vc_SIMD_CAST_1( uint_v, ushort_v);
Vc_SIMD_CAST_1( float_v, ushort_v);
Vc_SIMD_CAST_1(double_v, ushort_v);
Vc_SIMD_CAST_1( short_v, ushort_v);
Vc_SIMD_CAST_2(double_v, int_v);
Vc_SIMD_CAST_2(double_v, uint_v);
Vc_SIMD_CAST_2(double_v, float_v);
Vc_SIMD_CAST_2( int_v, short_v);
Vc_SIMD_CAST_2( uint_v, short_v);
Vc_SIMD_CAST_2( float_v, short_v);
Vc_SIMD_CAST_2(double_v, short_v);
Vc_SIMD_CAST_2( int_v, ushort_v);
Vc_SIMD_CAST_2( uint_v, ushort_v);
Vc_SIMD_CAST_2( float_v, ushort_v);
Vc_SIMD_CAST_2(double_v, ushort_v);
#define Vc_CAST_(To_) \
template <typename Return> \
Vc_INTRINSIC Vc_CONST enable_if<std::is_same<Return, To_>::value, Return>
Vc_CAST_(short_v) simd_cast(double_v a, double_v b, double_v c);
Vc_CAST_(ushort_v) simd_cast(double_v a, double_v b, double_v c);
Vc_SIMD_CAST_4(double_v, short_v);
Vc_SIMD_CAST_4(double_v, ushort_v);
}
using SSE::simd_cast;
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::double_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::float_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::ushort_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::double_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::float_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::ushort_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::float_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::ushort_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::float_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::ushort_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, SSE::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, SSE::ushort_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, SSE::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, SSE::ushort_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, SSE::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, SSE::ushort_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, SSE::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, SSE::ushort_v>::value> = nullarg);
template <typename To, typename FromT>
Vc_INTRINSIC Vc_CONST To
simd_cast(SSE::Vector<FromT> x, enable_if<Scalar::is_vector<To>::value> = nullarg);
#undef Vc_SIMD_CAST_1
#undef Vc_SIMD_CAST_2
#undef Vc_SIMD_CAST_4
#undef Vc_SIMD_CAST_8
#define Vc_SIMD_CAST_1(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x, enable_if<std::is_same<To, to_>::value>)
#define Vc_SIMD_CAST_2(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, \
enable_if<std::is_same<To, to_>::value>)
#define Vc_SIMD_CAST_4(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, from_ x2, from_ x3, \
enable_if<std::is_same<To, to_>::value>)
#define Vc_SIMD_CAST_8(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, \
from_ x5, from_ x6, from_ x7, \
enable_if<std::is_same<To, to_>::value>)
namespace SSE
{
Vc_INTRINSIC __m128i convert_int32_to_int16(__m128i a, __m128i b)
{
auto tmp0 = _mm_unpacklo_epi16(a, b);
auto tmp1 = _mm_unpackhi_epi16(a, b);
auto tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
return _mm_unpacklo_epi16(tmp2, tmp3);
}
Vc_SIMD_CAST_1( float_v, int_v) { return convert< float, int>(x.data()); }
Vc_SIMD_CAST_1(double_v, int_v) { return convert<double, int>(x.data()); }
Vc_SIMD_CAST_1( uint_v, int_v) { return convert< uint, int>(x.data()); }
Vc_SIMD_CAST_1( short_v, int_v) { return convert< short, int>(x.data()); }
Vc_SIMD_CAST_1(ushort_v, int_v) { return convert<ushort, int>(x.data()); }
Vc_SIMD_CAST_1( float_v, uint_v) { return convert< float, uint>(x.data()); }
Vc_SIMD_CAST_1(double_v, uint_v) { return convert<double, uint>(x.data()); }
Vc_SIMD_CAST_1( int_v, uint_v) { return convert< int, uint>(x.data()); }
Vc_SIMD_CAST_1( short_v, uint_v) { return convert< short, uint>(x.data()); }
Vc_SIMD_CAST_1(ushort_v, uint_v) { return convert<ushort, uint>(x.data()); }
Vc_SIMD_CAST_1(double_v, float_v) { return convert<double, float>(x.data()); }
Vc_SIMD_CAST_1( int_v, float_v) { return convert< int, float>(x.data()); }
Vc_SIMD_CAST_1( uint_v, float_v) { return convert< uint, float>(x.data()); }
Vc_SIMD_CAST_1( short_v, float_v) { return convert< short, float>(x.data()); }
Vc_SIMD_CAST_1(ushort_v, float_v) { return convert<ushort, float>(x.data()); }
Vc_SIMD_CAST_1( float_v, double_v) { return convert< float, double>(x.data()); }
Vc_SIMD_CAST_1( int_v, double_v) { return convert< int, double>(x.data()); }
Vc_SIMD_CAST_1( uint_v, double_v) { return convert< uint, double>(x.data()); }
Vc_SIMD_CAST_1( short_v, double_v) { return convert< short, double>(x.data()); }
Vc_SIMD_CAST_1(ushort_v, double_v) { return convert<ushort, double>(x.data()); }
Vc_SIMD_CAST_1( int_v, short_v) { return SSE::convert_int32_to_int16(x.data(), _mm_setzero_si128()); }
Vc_SIMD_CAST_1( uint_v, short_v) { return SSE::convert_int32_to_int16(x.data(), _mm_setzero_si128()); }
Vc_SIMD_CAST_1( float_v, short_v) { return _mm_packs_epi32(simd_cast<SSE::int_v>(x).data(), _mm_setzero_si128()); }
Vc_SIMD_CAST_1(double_v, short_v) { return _mm_packs_epi32(simd_cast<SSE::int_v>(x).data(), _mm_setzero_si128()); }
Vc_SIMD_CAST_1(ushort_v, short_v) { return x.data(); }
Vc_SIMD_CAST_1( int_v, ushort_v) { return SSE::convert_int32_to_int16(x.data(), _mm_setzero_si128()); }
Vc_SIMD_CAST_1( uint_v, ushort_v) { return SSE::convert_int32_to_int16(x.data(), _mm_setzero_si128()); }
Vc_SIMD_CAST_1( float_v, ushort_v) { return simd_cast<SSE::ushort_v>(simd_cast<SSE::int_v>(x)); }
Vc_SIMD_CAST_1(double_v, ushort_v) { return simd_cast<SSE::ushort_v>(simd_cast<SSE::int_v>(x)); }
Vc_SIMD_CAST_1( short_v, ushort_v) { return x.data(); }
Vc_SIMD_CAST_2(double_v, int_v) {
#ifdef Vc_IMPL_AVX
return AVX::convert<double, int>(AVX::concat(x0.data(), x1.data()));
#else
return _mm_unpacklo_epi64(convert<double, int>(x0.data()), convert<double, int>(x1.data()));
#endif
}
Vc_SIMD_CAST_2(double_v, uint_v) {
#ifdef Vc_IMPL_AVX
return AVX::convert<double, uint>(AVX::concat(x0.data(), x1.data()));
#else
return _mm_unpacklo_epi64(convert<double, uint>(x0.data()), convert<double, uint>(x1.data()));
#endif
}
Vc_SIMD_CAST_2(double_v, float_v) {
#ifdef Vc_IMPL_AVX
return _mm256_cvtpd_ps(AVX::concat(x0.data(), x1.data()));
#else
return _mm_movelh_ps(_mm_cvtpd_ps(x0.data()), _mm_cvtpd_ps(x1.data()));
#endif
}
Vc_SIMD_CAST_2( int_v, short_v) { return SSE::convert_int32_to_int16(x0.data(), x1.data()); }
Vc_SIMD_CAST_2( uint_v, short_v) { return SSE::convert_int32_to_int16(x0.data(), x1.data()); }
Vc_SIMD_CAST_2( float_v, short_v) { return _mm_packs_epi32(simd_cast<SSE::int_v>(x0).data(), simd_cast<SSE::int_v>(x1).data()); }
Vc_SIMD_CAST_2(double_v, short_v) { return _mm_packs_epi32(simd_cast<SSE::int_v>(x0, x1).data(), _mm_setzero_si128()); }
Vc_SIMD_CAST_2( int_v, ushort_v) { return SSE::convert_int32_to_int16(x0.data(), x1.data()); }
Vc_SIMD_CAST_2( uint_v, ushort_v) { return SSE::convert_int32_to_int16(x0.data(), x1.data()); }
Vc_SIMD_CAST_2( float_v, ushort_v) { return simd_cast<SSE::ushort_v>(simd_cast<SSE::int_v>(x0), simd_cast<SSE::int_v>(x1)); }
Vc_SIMD_CAST_2(double_v, ushort_v) { return simd_cast<SSE::ushort_v>(simd_cast<SSE::int_v>(x0, x1)); }
Vc_CAST_(short_v) simd_cast(double_v a, double_v b, double_v c)
{
return simd_cast<short_v>(simd_cast<int_v>(a, b), simd_cast<int_v>(c));
}
Vc_CAST_(ushort_v) simd_cast(double_v a, double_v b, double_v c)
{
return simd_cast<ushort_v>(simd_cast<int_v>(a, b), simd_cast<int_v>(c));
}
#undef Vc_CAST_
Vc_SIMD_CAST_4(double_v, short_v) { return _mm_packs_epi32(simd_cast<SSE::int_v>(x0, x1).data(), simd_cast<SSE::int_v>(x2, x3).data()); }
Vc_SIMD_CAST_4(double_v, ushort_v) { return simd_cast<SSE::ushort_v>(simd_cast<SSE::int_v>(x0, x1), simd_cast<SSE::int_v>(x2, x3)); }
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::double_v>::value> )
{
return _mm_setr_pd(x.data(), 0.);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::float_v>::value> )
{
return _mm_setr_ps(x.data(), 0.f, 0.f, 0.f);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::int_v>::value> )
{
return _mm_setr_epi32(x.data(), 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::uint_v>::value> )
{
return _mm_setr_epi32(uint(x.data()), 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::short_v>::value> )
{
return _mm_setr_epi16(
x.data(), 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, SSE::ushort_v>::value> )
{
return _mm_setr_epi16(
x.data(), 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::double_v>::value> )
{
return _mm_setr_pd(x0.data(), x1.data());
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::float_v>::value> )
{
return _mm_setr_ps(x0.data(), x1.data(), 0.f, 0.f);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::int_v>::value> )
{
return _mm_setr_epi32(x0.data(), x1.data(), 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::uint_v>::value> )
{
return _mm_setr_epi32(uint(x0.data()), uint(x1.data()), 0,
0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::short_v>::value> )
{
return _mm_setr_epi16(
x0.data(), x1.data(), 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
enable_if<std::is_same<Return, SSE::ushort_v>::value> )
{
return _mm_setr_epi16(
x0.data(), x1.data(), 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, SSE::float_v>::value>)
{
return _mm_setr_ps(x0.data(), x1.data(), x2.data(), 0.f);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, SSE::int_v>::value>)
{
return _mm_setr_epi32(x0.data(), x1.data(), x2.data(), 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, SSE::uint_v>::value>)
{
return _mm_setr_epi32(uint(x0.data()), uint(x1.data()), uint(x2.data()),
0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, SSE::short_v>::value>)
{
return _mm_setr_epi16(x0.data(), x1.data(), x2.data(), 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, SSE::ushort_v>::value>)
{
return _mm_setr_epi16(x0.data(), x1.data(), x2.data(), 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::float_v>::value> )
{
return _mm_setr_ps(
x0.data(), x1.data(), x2.data(), x3.data());
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::int_v>::value> )
{
return _mm_setr_epi32(
x0.data(), x1.data(), x2.data(), x3.data());
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::uint_v>::value> )
{
return _mm_setr_epi32(uint(x0.data()), uint(x1.data()), uint(x2.data()),
uint(x3.data()));
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::short_v>::value> )
{
return _mm_setr_epi16(
x0.data(), x1.data(), x2.data(), x3.data(), 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, SSE::ushort_v>::value> )
{
return _mm_setr_epi16(
x0.data(), x1.data(), x2.data(), x3.data(), 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, SSE::short_v>::value>)
{
return _mm_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(), 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, SSE::ushort_v>::value>)
{
return _mm_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(), 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, SSE::short_v>::value>)
{
return _mm_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, SSE::ushort_v>::value>)
{
return _mm_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, enable_if<std::is_same<Return, SSE::short_v>::value>)
{
return _mm_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, enable_if<std::is_same<Return, SSE::ushort_v>::value>)
{
return _mm_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
Scalar::Vector<T> x4,
Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
Scalar::Vector<T> x7,
enable_if<std::is_same<Return, SSE::short_v>::value> )
{
return _mm_setr_epi16(x0.data(),
x1.data(),
x2.data(),
x3.data(),
x4.data(),
x5.data(),
x6.data(),
x7.data());
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0,
Scalar::Vector<T> x1,
Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
Scalar::Vector<T> x4,
Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
Scalar::Vector<T> x7,
enable_if<std::is_same<Return, SSE::ushort_v>::value> )
{
return _mm_setr_epi16(x0.data(),
x1.data(),
x2.data(),
x3.data(),
x4.data(),
x5.data(),
x6.data(),
x7.data());
}
template <typename To, typename FromT>
Vc_INTRINSIC Vc_CONST To
simd_cast(SSE::Vector<FromT> x, enable_if<Scalar::is_vector<To>::value> )
{
return static_cast<To>(x[0]);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(SSE::Mask<T> x, enable_if<SSE::is_mask<Return>::value> = nullarg)
{
using M = SSE::Mask<T>;
return {Detail::mask_cast<M::Size, Return::Size, __m128>(x.dataI())};
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(
SSE::Mask<T> x0,
SSE::Mask<T> x1,
enable_if<SSE::is_mask<Return>::value && Mask<T, VectorAbi::Sse>::Size * 2 == Return::Size> = nullarg)
{
return SSE::sse_cast<__m128>(_mm_packs_epi16(x0.dataI(), x1.dataI()));
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(
SSE::Mask<T> x0,
SSE::Mask<T> x1,
enable_if<SSE::is_mask<Return>::value && Mask<T, VectorAbi::Sse>::Size * 4 == Return::Size> = nullarg)
{
return SSE::sse_cast<__m128>(
_mm_packs_epi16(_mm_packs_epi16(x0.dataI(), x1.dataI()), _mm_setzero_si128()));
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(
SSE::Mask<T> x0,
SSE::Mask<T> x1,
SSE::Mask<T> x2,
SSE::Mask<T> x3,
enable_if<SSE::is_mask<Return>::value && Mask<T, VectorAbi::Sse>::Size * 4 == Return::Size> = nullarg)
{
return SSE::sse_cast<__m128>(_mm_packs_epi16(_mm_packs_epi16(x0.dataI(), x1.dataI()),
_mm_packs_epi16(x2.dataI(), x3.dataI())));
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> x, enable_if<SSE::is_mask<Return>::value> = nullarg)
{
Return m(false);
m[0] = x[0];
return m;
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> x0, Scalar::Mask<T> x1, enable_if<SSE::is_mask<Return>::value> = nullarg)
{
Return m(false);
m[0] = x0[0];
m[1] = x1[0];
return m;
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(Scalar::Mask<T> x0,
Scalar::Mask<T> x1,
Scalar::Mask<T> x2,
Scalar::Mask<T> x3,
enable_if<SSE::is_mask<Return>::value> = nullarg)
{
Return m(false);
m[0] = x0[0];
m[1] = x1[0];
if (Return::Size >= 4) {
m[2] = x2[0];
m[3] = x3[0];
}
return m;
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(Scalar::Mask<T> x0,
Scalar::Mask<T> x1,
Scalar::Mask<T> x2,
Scalar::Mask<T> x3,
Scalar::Mask<T> x4,
Scalar::Mask<T> x5,
Scalar::Mask<T> x6,
Scalar::Mask<T> x7,
enable_if<SSE::is_mask<Return>::value> = nullarg)
{
Return m(false);
m[0] = x0[0];
m[1] = x1[0];
if (Return::Size >= 4) {
m[2] = x2[0];
m[3] = x3[0];
}
if (Return::Size >= 8) {
m[4] = x4[0];
m[5] = x5[0];
m[6] = x6[0];
m[7] = x7[0];
}
return m;
}
template <typename To, typename FromT>
Vc_INTRINSIC Vc_CONST To
simd_cast(SSE::Mask<FromT> x, enable_if<Scalar::is_mask<To>::value> = nullarg)
{
return static_cast<To>(x[0]);
}
template <typename Return, int offset, typename V>
Vc_INTRINSIC Vc_CONST Return
simd_cast(V &&x, enable_if<offset == 0 && ((SSE::is_vector<Traits::decay<V>>::value &&
SSE::is_vector<Return>::value) ||
(SSE::is_mask<Traits::decay<V>>::value &&
SSE::is_mask<Return>::value))> = nullarg)
{
return simd_cast<Return>(x);
}
template <typename Return, int offset, typename V>
Vc_INTRINSIC Vc_CONST Return
simd_cast(V &&x,
enable_if<offset == 0 && ((Scalar::is_vector<Traits::decay<V>>::value &&
SSE::is_vector<Return>::value) ||
(Scalar::is_mask<Traits::decay<V>>::value &&
SSE::is_mask<Return>::value))> = nullarg)
{
return simd_cast<Return>(x);
}
template <typename Return, int offset, typename V>
Vc_INTRINSIC Vc_CONST Return simd_cast(
V x,
enable_if<offset != 0 && (SSE::is_vector<Return>::value && SSE::is_vector<V>::value)> = nullarg)
{
constexpr int shift = (sizeof(V) / V::Size) * offset * Return::Size;
static_assert(shift > 0 && shift < 16, "");
return simd_cast<Return>(V{SSE::sse_cast<typename V::VectorType>(
_mm_srli_si128(SSE::sse_cast<__m128i>(x.data()), shift & 0xff))});
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(SSE::Vector<T> x,
enable_if<offset != 0 && Scalar::is_vector<Return>::value> = nullarg)
{
return static_cast<typename Return::EntryType>(x[offset]);
}
template <typename Return, int offset, typename V>
Vc_INTRINSIC Vc_CONST Return simd_cast(
V x,
enable_if<offset != 0 && (SSE::is_mask<Return>::value && SSE::is_mask<V>::value)> = nullarg)
{
constexpr int shift = (sizeof(V) / V::Size) * offset * Return::Size;
static_assert(shift > 0 && shift < 16, "");
return simd_cast<Return>(V{SSE::sse_cast<typename V::VectorType>(
_mm_srli_si128(SSE::sse_cast<__m128i>(x.data()), shift & 0xff))});
}
#undef Vc_SIMD_CAST_1
#undef Vc_SIMD_CAST_2
#undef Vc_SIMD_CAST_4
#undef Vc_SIMD_CAST_8
}
#endif
#endif
#endif
#ifdef Vc_IMPL_AVX
#ifndef VC_AVX_VECTOR_H_
#define VC_AVX_VECTOR_H_ 
#ifndef VC_AVX_VECTORHELPER_H_
#define VC_AVX_VECTORHELPER_H_ 
#include <limits>
namespace Vc_VERSIONED_NAMESPACE
{
namespace AVX
{
template<> struct VectorHelper<__m256>
{
typedef __m256 VectorType;
typedef const VectorType VTArg;
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VTArg x, typename Flags::EnableIfAligned = nullptr) { _mm256_store_ps(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VTArg x, typename Flags::EnableIfUnalignedNotStreaming = nullptr) { _mm256_storeu_ps(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VTArg x, typename Flags::EnableIfStreaming = nullptr) { _mm256_stream_ps(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VTArg x, typename Flags::EnableIfUnalignedAndStreaming = nullptr) { AvxIntrinsics::stream_store(mem, x, setallone_ps()); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VTArg x, VTArg m, typename std::enable_if<!Flags::IsStreaming, void *>::type = nullptr) { _mm256_maskstore(mem, m, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(float *mem, VTArg x, VTArg m, typename std::enable_if< Flags::IsStreaming, void *>::type = nullptr) { AvxIntrinsics::stream_store(mem, x, m); }
};
template<> struct VectorHelper<__m256d>
{
typedef __m256d VectorType;
typedef const VectorType VTArg;
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VTArg x, typename Flags::EnableIfAligned = nullptr) { _mm256_store_pd(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VTArg x, typename Flags::EnableIfUnalignedNotStreaming = nullptr) { _mm256_storeu_pd(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VTArg x, typename Flags::EnableIfStreaming = nullptr) { _mm256_stream_pd(mem, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VTArg x, typename Flags::EnableIfUnalignedAndStreaming = nullptr) { AvxIntrinsics::stream_store(mem, x, setallone_pd()); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VTArg x, VTArg m, typename std::enable_if<!Flags::IsStreaming, void *>::type = nullptr) { _mm256_maskstore(mem, m, x); }
template<typename Flags> static Vc_ALWAYS_INLINE void store(double *mem, VTArg x, VTArg m, typename std::enable_if< Flags::IsStreaming, void *>::type = nullptr) { AvxIntrinsics::stream_store(mem, x, m); }
};
template<> struct VectorHelper<__m256i>
{
typedef __m256i VectorType;
typedef const VectorType VTArg;
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VTArg x, typename Flags::EnableIfAligned = nullptr) { _mm256_store_si256(reinterpret_cast<__m256i *>(mem), x); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VTArg x, typename Flags::EnableIfUnalignedNotStreaming = nullptr) { _mm256_storeu_si256(reinterpret_cast<__m256i *>(mem), x); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VTArg x, typename Flags::EnableIfStreaming = nullptr) { _mm256_stream_si256(reinterpret_cast<__m256i *>(mem), x); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VTArg x, typename Flags::EnableIfUnalignedAndStreaming = nullptr) { AvxIntrinsics::stream_store(mem, x, setallone_si256()); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VTArg x, VTArg m, typename std::enable_if<!Flags::IsStreaming, void *>::type = nullptr) { _mm256_maskstore(mem, m, x); }
template<typename Flags, typename T> static Vc_ALWAYS_INLINE void store(T *mem, VTArg x, VTArg m, typename std::enable_if< Flags::IsStreaming, void *>::type = nullptr) { AvxIntrinsics::stream_store(mem, x, m); }
};
#define Vc_OP1(op) \
static Vc_INTRINSIC VectorType Vc_CONST op(VTArg a) { return Vc_CAT2(_mm256_##op##_, Vc_SUFFIX)(a); }
#define Vc_OP(op) \
static Vc_INTRINSIC VectorType Vc_CONST op(VTArg a, VTArg b) { return Vc_CAT2(op##_ , Vc_SUFFIX)(a, b); }
#define Vc_OP_(op) \
static Vc_INTRINSIC VectorType Vc_CONST op(VTArg a, VTArg b) { return Vc_CAT2(_mm256_##op , Vc_SUFFIX)(a, b); }
#define Vc_OPx(op,op2) \
static Vc_INTRINSIC VectorType Vc_CONST op(VTArg a, VTArg b) { return Vc_CAT2(_mm256_##op2##_, Vc_SUFFIX)(a, b); }
template<> struct VectorHelper<double> {
typedef __m256d VectorType;
typedef const VectorType VTArg;
typedef double EntryType;
#define Vc_SUFFIX pd
static Vc_ALWAYS_INLINE VectorType notMaskedToZero(VTArg a, __m256 mask) { return Vc_CAT2(_mm256_and_, Vc_SUFFIX)(_mm256_castps_pd(mask), a); }
static Vc_ALWAYS_INLINE VectorType set(const double a) { return Vc_CAT2(_mm256_set1_, Vc_SUFFIX)(a); }
static Vc_ALWAYS_INLINE VectorType set(const double a, const double b, const double c, const double d) {
return Vc_CAT2(_mm256_set_, Vc_SUFFIX)(a, b, c, d);
}
static Vc_ALWAYS_INLINE VectorType zero() { return Vc_CAT2(_mm256_setzero_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE VectorType one() { return Vc_CAT2(setone_, Vc_SUFFIX)(); }
static inline void fma(VectorType &v1, VTArg v2, VTArg v3) {
#ifdef Vc_IMPL_FMA4
v1 = _mm256_macc_pd(v1, v2, v3);
#else
VectorType h1 = _mm256_and_pd(v1, _mm256_broadcast_sd(reinterpret_cast<const double *>(&c_general::highMaskDouble)));
VectorType h2 = _mm256_and_pd(v2, _mm256_broadcast_sd(reinterpret_cast<const double *>(&c_general::highMaskDouble)));
#if defined(Vc_GCC) && Vc_GCC < 0x40703
asm("":"+x"(h1), "+x"(h2));
#endif
const VectorType l1 = _mm256_sub_pd(v1, h1);
const VectorType l2 = _mm256_sub_pd(v2, h2);
const VectorType ll = mul(l1, l2);
const VectorType lh = add(mul(l1, h2), mul(h1, l2));
const VectorType hh = mul(h1, h2);
const VectorType lh_lt_v3 = cmplt_pd(abs(lh), abs(v3));
const VectorType b = _mm256_blendv_pd(v3, lh, lh_lt_v3);
const VectorType c = _mm256_blendv_pd(lh, v3, lh_lt_v3);
v1 = add(add(ll, b), add(c, hh));
#endif
}
static Vc_INTRINSIC VectorType Vc_CONST add(VTArg a, VTArg b) { return _mm256_add_pd(a,b); }
static Vc_INTRINSIC VectorType Vc_CONST sub(VTArg a, VTArg b) { return _mm256_sub_pd(a,b); }
static Vc_INTRINSIC VectorType Vc_CONST mul(VTArg a, VTArg b) { return _mm256_mul_pd(a,b); }
Vc_OP1(sqrt)
static Vc_ALWAYS_INLINE Vc_CONST VectorType rsqrt(VTArg x) {
return _mm256_div_pd(one(), sqrt(x));
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType reciprocal(VTArg x) {
return _mm256_div_pd(one(), x);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType abs(VTArg a) {
return Vc_CAT2(_mm256_and_, Vc_SUFFIX)(a, setabsmask_pd());
}
static Vc_INTRINSIC VectorType Vc_CONST min(VTArg a, VTArg b) { return _mm256_min_pd(a, b); }
static Vc_INTRINSIC VectorType Vc_CONST max(VTArg a, VTArg b) { return _mm256_max_pd(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST EntryType min(VTArg a) {
__m128d b = _mm_min_pd(avx_cast<__m128d>(a), _mm256_extractf128_pd(a, 1));
b = _mm_min_sd(b, _mm_unpackhi_pd(b, b));
return _mm_cvtsd_f64(b);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType max(VTArg a) {
__m128d b = _mm_max_pd(avx_cast<__m128d>(a), _mm256_extractf128_pd(a, 1));
b = _mm_max_sd(b, _mm_unpackhi_pd(b, b));
return _mm_cvtsd_f64(b);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType mul(VTArg a) {
__m128d b = _mm_mul_pd(avx_cast<__m128d>(a), _mm256_extractf128_pd(a, 1));
b = _mm_mul_sd(b, _mm_shuffle_pd(b, b, _MM_SHUFFLE2(0, 1)));
return _mm_cvtsd_f64(b);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType add(VTArg a) {
__m128d b = _mm_add_pd(avx_cast<__m128d>(a), _mm256_extractf128_pd(a, 1));
b = _mm_hadd_pd(b, b);
return _mm_cvtsd_f64(b);
}
#undef Vc_SUFFIX
static Vc_ALWAYS_INLINE Vc_CONST VectorType round(VTArg a) {
return _mm256_round_pd(a, _MM_FROUND_NINT);
}
};
template<> struct VectorHelper<float> {
typedef float EntryType;
typedef __m256 VectorType;
typedef const VectorType VTArg;
#define Vc_SUFFIX ps
static Vc_ALWAYS_INLINE Vc_CONST VectorType notMaskedToZero(VTArg a, __m256 mask) { return Vc_CAT2(_mm256_and_, Vc_SUFFIX)(mask, a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const float a) { return Vc_CAT2(_mm256_set1_, Vc_SUFFIX)(a); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType set(const float a, const float b, const float c, const float d,
const float e, const float f, const float g, const float h) {
return Vc_CAT2(_mm256_set_, Vc_SUFFIX)(a, b, c, d, e, f, g, h); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType zero() { return Vc_CAT2(_mm256_setzero_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST VectorType one() { return Vc_CAT2(setone_, Vc_SUFFIX)(); }
static Vc_ALWAYS_INLINE Vc_CONST __m256 concat(__m256d a, __m256d b) { return _mm256_insertf128_ps(avx_cast<__m256>(_mm256_cvtpd_ps(a)), _mm256_cvtpd_ps(b), 1); }
static inline void fma(VectorType &v1, VTArg v2, VTArg v3) {
#ifdef Vc_IMPL_FMA4
v1 = _mm256_macc_ps(v1, v2, v3);
#else
__m256d v1_0 = _mm256_cvtps_pd(lo128(v1));
__m256d v1_1 = _mm256_cvtps_pd(hi128(v1));
__m256d v2_0 = _mm256_cvtps_pd(lo128(v2));
__m256d v2_1 = _mm256_cvtps_pd(hi128(v2));
__m256d v3_0 = _mm256_cvtps_pd(lo128(v3));
__m256d v3_1 = _mm256_cvtps_pd(hi128(v3));
v1 = AVX::concat(
_mm256_cvtpd_ps(_mm256_add_pd(_mm256_mul_pd(v1_0, v2_0), v3_0)),
_mm256_cvtpd_ps(_mm256_add_pd(_mm256_mul_pd(v1_1, v2_1), v3_1)));
#endif
}
static Vc_INTRINSIC VectorType Vc_CONST add(VTArg a, VTArg b) { return _mm256_add_ps(a, b); }
static Vc_INTRINSIC VectorType Vc_CONST sub(VTArg a, VTArg b) { return _mm256_sub_ps(a, b); }
static Vc_INTRINSIC VectorType Vc_CONST mul(VTArg a, VTArg b) { return _mm256_mul_ps(a, b); }
Vc_OP1(sqrt) Vc_OP1(rsqrt)
static Vc_ALWAYS_INLINE Vc_CONST VectorType reciprocal(VTArg x) {
return _mm256_rcp_ps(x);
}
static Vc_ALWAYS_INLINE Vc_CONST VectorType abs(VTArg a) {
return Vc_CAT2(_mm256_and_, Vc_SUFFIX)(a, setabsmask_ps());
}
static Vc_INTRINSIC VectorType Vc_CONST min(VTArg a, VTArg b) { return _mm256_min_ps(a, b); }
static Vc_INTRINSIC VectorType Vc_CONST max(VTArg a, VTArg b) { return _mm256_max_ps(a, b); }
static Vc_ALWAYS_INLINE Vc_CONST EntryType min(VTArg a) {
__m128 b = _mm_min_ps(lo128(a), hi128(a));
b = _mm_min_ps(b, _mm_movehl_ps(b, b));
b = _mm_min_ss(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtss_f32(b);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType max(VTArg a) {
__m128 b = _mm_max_ps(avx_cast<__m128>(a), _mm256_extractf128_ps(a, 1));
b = _mm_max_ps(b, _mm_movehl_ps(b, b));
b = _mm_max_ss(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(1, 1, 1, 1)));
return _mm_cvtss_f32(b);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType mul(VTArg a) {
__m128 b = _mm_mul_ps(avx_cast<__m128>(a), _mm256_extractf128_ps(a, 1));
b = _mm_mul_ps(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(0, 1, 2, 3)));
b = _mm_mul_ss(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 2, 0, 1)));
return _mm_cvtss_f32(b);
}
static Vc_ALWAYS_INLINE Vc_CONST EntryType add(VTArg a) {
__m128 b = _mm_add_ps(avx_cast<__m128>(a), _mm256_extractf128_ps(a, 1));
b = _mm_add_ps(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(0, 1, 2, 3)));
b = _mm_add_ss(b, _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 2, 0, 1)));
return _mm_cvtss_f32(b);
}
#undef Vc_SUFFIX
static Vc_ALWAYS_INLINE Vc_CONST VectorType round(VTArg a) {
return _mm256_round_ps(a, _MM_FROUND_NINT);
}
};
#undef Vc_OP1
#undef Vc_OP
#undef Vc_OP_
#undef Vc_OPx
}
}
#endif
#ifndef VC_AVX_MASK_H_
#define VC_AVX_MASK_H_ 
#include <array>
#ifndef VC_AVX_DETAIL_H_
#define VC_AVX_DETAIL_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename Flags>
Vc_INTRINSIC Vc_PURE __m256 load(const float *x, Flags, LoadTag<__m256, float>,
typename Flags::EnableIfAligned = nullptr)
{
return _mm256_load_ps(x);
}
template <typename Flags>
Vc_INTRINSIC Vc_PURE __m256 load(const float *x, Flags, LoadTag<__m256, float>,
typename Flags::EnableIfUnaligned = nullptr)
{
return _mm256_loadu_ps(x);
}
template <typename Flags>
Vc_INTRINSIC Vc_PURE __m256 load(const float *x, Flags, LoadTag<__m256, float>,
typename Flags::EnableIfStreaming = nullptr)
{
return AvxIntrinsics::stream_load<__m256>(x);
}
template <typename Flags>
Vc_INTRINSIC Vc_PURE __m256d load(const double *x, Flags, LoadTag<__m256d, double>,
typename Flags::EnableIfAligned = nullptr)
{
return _mm256_load_pd(x);
}
template <typename Flags>
Vc_INTRINSIC Vc_PURE __m256d load(const double *x, Flags, LoadTag<__m256d, double>,
typename Flags::EnableIfUnaligned = nullptr)
{
return _mm256_loadu_pd(x);
}
template <typename Flags>
Vc_INTRINSIC Vc_PURE __m256d load(const double *x, Flags, LoadTag<__m256d, double>,
typename Flags::EnableIfStreaming = nullptr)
{
return AvxIntrinsics::stream_load<__m256d>(x);
}
template <typename Flags, typename T, typename = enable_if<std::is_integral<T>::value>>
Vc_INTRINSIC Vc_PURE __m256i
load(const T *x, Flags, LoadTag<__m256i, T>, typename Flags::EnableIfAligned = nullptr)
{
return _mm256_load_si256(reinterpret_cast<const __m256i *>(x));
}
template <typename Flags, typename T, typename = enable_if<std::is_integral<T>::value>>
Vc_INTRINSIC Vc_PURE __m256i
load(const T *x, Flags, LoadTag<__m256i, T>, typename Flags::EnableIfUnaligned = nullptr)
{
return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(x));
}
template <typename Flags, typename T, typename = enable_if<std::is_integral<T>::value>>
Vc_INTRINSIC Vc_PURE __m256i
load(const T *x, Flags, LoadTag<__m256i, T>, typename Flags::EnableIfStreaming = nullptr)
{
return AvxIntrinsics::stream_load<__m256i>(x);
}
Vc_INTRINSIC __m256 load32(const float *mem, when_aligned)
{
return _mm256_load_ps(mem);
}
Vc_INTRINSIC __m256 load32(const float *mem, when_unaligned)
{
return _mm256_loadu_ps(mem);
}
Vc_INTRINSIC __m256 load32(const float *mem, when_streaming)
{
return AvxIntrinsics::stream_load<__m256>(mem);
}
Vc_INTRINSIC __m256d load32(const double *mem, when_aligned)
{
return _mm256_load_pd(mem);
}
Vc_INTRINSIC __m256d load32(const double *mem, when_unaligned)
{
return _mm256_loadu_pd(mem);
}
Vc_INTRINSIC __m256d load32(const double *mem, when_streaming)
{
return AvxIntrinsics::stream_load<__m256d>(mem);
}
template <class T> Vc_INTRINSIC __m256i load32(const T *mem, when_aligned)
{
static_assert(std::is_integral<T>::value, "load32<T> is only intended for integral T");
return _mm256_load_si256(reinterpret_cast<const __m256i *>(mem));
}
template <class T> Vc_INTRINSIC __m256i load32(const T *mem, when_unaligned)
{
static_assert(std::is_integral<T>::value, "load32<T> is only intended for integral T");
return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(mem));
}
template <class T> Vc_INTRINSIC __m256i load32(const T *mem, when_streaming)
{
static_assert(std::is_integral<T>::value, "load32<T> is only intended for integral T");
return AvxIntrinsics::stream_load<__m256i>(mem);
}
#ifdef Vc_MSVC
Vc_INTRINSIC __m256i load(const uint *mem, when_aligned, LoadTag<__m256i, int>)
{
return _mm256_load_si256(reinterpret_cast<const __m256i *>(mem));
}
Vc_INTRINSIC __m256d load(const double *mem, when_unaligned, LoadTag<__m256d, double>)
{
return _mm256_loadu_pd(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256 load(const float *mem, when_aligned,
enable_if<(std::is_same<DstT, float>::value &&
std::is_same<V, __m256>::value)> = nullarg)
{
return _mm256_load_ps(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256 load(const float *mem, when_unaligned,
enable_if<(std::is_same<DstT, float>::value &&
std::is_same<V, __m256>::value)> = nullarg)
{
return _mm256_loadu_ps(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256 load(const float *mem, when_streaming,
enable_if<(std::is_same<DstT, float>::value &&
std::is_same<V, __m256>::value)> = nullarg)
{
return AvxIntrinsics::stream_load<__m256>(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256d load(const double *mem, when_aligned,
enable_if<(std::is_same<DstT, double>::value &&
std::is_same<V, __m256d>::value)> = nullarg)
{
return _mm256_load_pd(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256d load(const double *mem, when_unaligned,
enable_if<(std::is_same<DstT, double>::value &&
std::is_same<V, __m256d>::value)> = nullarg)
{
return _mm256_loadu_pd(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256d load(const double *mem, when_streaming,
enable_if<(std::is_same<DstT, double>::value &&
std::is_same<V, __m256d>::value)> = nullarg)
{
return AvxIntrinsics::stream_load<__m256d>(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const uint *mem, when_aligned,
enable_if<(std::is_same<DstT, uint>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return _mm256_load_si256(reinterpret_cast<const __m256i *>(mem));
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const uint *mem, when_unaligned,
enable_if<(std::is_same<DstT, uint>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(mem));
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const uint *mem, when_streaming,
enable_if<(std::is_same<DstT, uint>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return AvxIntrinsics::stream_load<__m256i>(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const int *mem, when_unaligned,
enable_if<(std::is_same<DstT, int>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(mem));
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const int *mem, when_aligned,
enable_if<(std::is_same<DstT, int>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return _mm256_load_si256(reinterpret_cast<const __m256i *>(mem));
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const int *mem, when_streaming,
enable_if<(std::is_same<DstT, int>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return AvxIntrinsics::stream_load<__m256i>(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const short *mem, when_unaligned,
enable_if<(std::is_same<DstT, short>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(mem));
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const short *mem, when_aligned,
enable_if<(std::is_same<DstT, short>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return _mm256_load_si256(reinterpret_cast<const __m256i *>(mem));
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const short *mem, when_streaming,
enable_if<(std::is_same<DstT, short>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return AvxIntrinsics::stream_load<__m256i>(mem);
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const ushort *mem, when_unaligned,
enable_if<(std::is_same<DstT, ushort>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return _mm256_loadu_si256(reinterpret_cast<const __m256i *>(mem));
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const ushort *mem, when_aligned,
enable_if<(std::is_same<DstT, ushort>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return _mm256_load_si256(reinterpret_cast<const __m256i *>(mem));
}
template <typename V, typename DstT>
Vc_INTRINSIC __m256i load(const ushort *mem, when_streaming,
enable_if<(std::is_same<DstT, ushort>::value &&
std::is_same<V, __m256i>::value)> = nullarg)
{
return AvxIntrinsics::stream_load<__m256i>(mem);
}
#endif
template <typename Flags>
Vc_INTRINSIC __m256i load(const ushort *mem, Flags f, LoadTag<__m256i, short>)
{
return load32(mem, f);
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const uchar *mem, Flags f, LoadTag<__m256i, short>)
{
return AVX::cvtepu8_epi16(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const schar *mem, Flags f, LoadTag<__m256i, short>)
{
return AVX::cvtepi8_epi16(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const uchar *mem, Flags f, LoadTag<__m256i, ushort>)
{
return AVX::cvtepu8_epi16(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const uint *mem, Flags f, LoadTag<__m256i, int>)
{
return load32(mem, f);
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const ushort *mem, Flags f, LoadTag<__m256i, int>)
{
return AVX::cvtepu16_epi32(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const short *mem, Flags f, LoadTag<__m256i, int>)
{
return AVX::cvtepi16_epi32(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const uchar *mem, Flags, LoadTag<__m256i, int>)
{
return AVX::cvtepu8_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const schar *mem, Flags, LoadTag<__m256i, int>)
{
return AVX::cvtepi8_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const ushort *mem, Flags f, LoadTag<__m256i, uint>)
{
return AVX::cvtepu16_epi32(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256i load(const uchar *mem, Flags, LoadTag<__m256i, uint>)
{
return AVX::cvtepu8_epi32(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(mem)));
}
template <typename Flags>
Vc_INTRINSIC __m256d load(const float *mem, Flags f, LoadTag<__m256d, double>)
{
return AVX::convert<float, double>(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256d load(const uint *mem, Flags f, LoadTag<__m256d, double>)
{
return AVX::convert<uint, double>(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256d load(const int *mem, Flags f, LoadTag<__m256d, double>)
{
return AVX::convert<int, double>(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256d load(const ushort *mem, Flags f, LoadTag<__m256d, double>)
{
return AVX::convert<int, double>(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256d load(const short *mem, Flags f, LoadTag<__m256d, double>)
{
return AVX::convert<int, double>(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256d load(const uchar *mem, Flags f, LoadTag<__m256d, double>)
{
return AVX::convert<int, double>(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256d load(const schar *mem, Flags f, LoadTag<__m256d, double>)
{
return AVX::convert<int, double>(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256 load(const double *mem, Flags f, LoadTag<__m256, float>)
{
return AVX::concat(_mm256_cvtpd_ps(load32(&mem[0], f)),
_mm256_cvtpd_ps(load32(&mem[4], f)));
}
template <typename Flags>
Vc_INTRINSIC __m256 load(const uint *mem, Flags f, LoadTag<__m256, float>)
{
const auto v = load32(mem, f);
return _mm256_blendv_ps(
_mm256_cvtepi32_ps(v),
_mm256_add_ps(_mm256_cvtepi32_ps(AVX::sub_epi32(v, AVX::set2power31_epu32())),
AVX::set2power31_ps()),
_mm256_castsi256_ps(AVX::cmplt_epi32(v, _mm256_setzero_si256())));
}
template <typename Flags>
Vc_INTRINSIC __m256 load(const int *mem, Flags f, LoadTag<__m256, float>)
{
return AVX::convert<int, float>(load32(mem, f));
}
template <typename T, typename Flags,
typename = enable_if<!std::is_same<T, float>::value>>
Vc_INTRINSIC __m256 load(const T *mem, Flags f, LoadTag<__m256, float>)
{
return _mm256_cvtepi32_ps(load<__m256i, int>(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256 load(const ushort *mem, Flags f, LoadTag<__m256, float>)
{
return AVX::convert<ushort, float>(load16(mem, f));
}
template <typename Flags>
Vc_INTRINSIC __m256 load(const short *mem, Flags f, LoadTag<__m256, float>)
{
return AVX::convert<short, float>(load16(mem, f));
}
template <int amount, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(sizeof(T) == 32 && amount >= 16), T> shifted(T k)
{
return AVX::avx_cast<T>(AVX::zeroExtend(
_mm_srli_si128(AVX::hi128(AVX::avx_cast<__m256i>(k)), amount - 16)));
}
template <int amount, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(sizeof(T) == 32 && amount > 0 && amount < 16), T>
shifted(T k)
{
return AVX::avx_cast<T>(
AVX::alignr<amount>(Mem::permute128<X1, Const0>(AVX::avx_cast<__m256i>(k)),
AVX::avx_cast<__m256i>(k)));
}
template <int amount, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(sizeof(T) == 32 && amount <= -16), T> shifted(T k)
{
return AVX::avx_cast<T>(Mem::permute128<Const0, X0>(AVX::avx_cast<__m256i>(
_mm_slli_si128(AVX::lo128(AVX::avx_cast<__m256i>(k)), -16 - amount))));
}
template <int amount, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(sizeof(T) == 32 && amount > -16 && amount < 0), T>
shifted(T k)
{
return AVX::avx_cast<T>(
AVX::alignr<16 + amount>(AVX::avx_cast<__m256i>(k),
Mem::permute128<Const0, X0>(AVX::avx_cast<__m256i>(k))));
}
template<size_t From, size_t To, typename R> Vc_INTRINSIC Vc_CONST R mask_cast(__m256i k)
{
static_assert(From == To, "Incorrect mask cast.");
static_assert(std::is_same<R, __m256>::value, "Incorrect mask cast.");
return AVX::avx_cast<__m256>(k);
}
template <> Vc_INTRINSIC Vc_CONST __m128 mask_cast<4, 4, __m128>(__m256i k)
{
return AVX::avx_cast<__m128>(_mm_packs_epi32(AVX::lo128(k), AVX::hi128(k)));
}
template <> Vc_INTRINSIC Vc_CONST __m256 mask_cast<4, 4, __m256>(__m128i k)
{
const auto kk = _mm_castsi128_ps(k);
return AVX::concat(_mm_unpacklo_ps(kk, kk), _mm_unpackhi_ps(kk, kk));
}
template<> Vc_INTRINSIC Vc_CONST __m256 mask_cast<4, 8, __m256>(__m256i k)
{
return AVX::avx_cast<__m256>(AVX::concat(_mm_packs_epi32(AVX::lo128(k), AVX::hi128(k)),
_mm_setzero_si128()));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<4, 8, __m128>(__m256i k)
{
return AVX::avx_cast<__m128>(_mm_packs_epi16(_mm_packs_epi32(AVX::lo128(k), AVX::hi128(k)), _mm_setzero_si128()));
}
template <> Vc_INTRINSIC Vc_CONST __m256 mask_cast<4, 8, __m256>(__m128i k)
{
return AVX::zeroExtend(AVX::avx_cast<__m128>(k));
}
template<> Vc_INTRINSIC Vc_CONST __m256 mask_cast<4, 16, __m256>(__m256i k)
{
return AVX::zeroExtend(mask_cast<4, 8, __m128>(k));
}
template<> Vc_INTRINSIC Vc_CONST __m256 mask_cast<8, 4, __m256>(__m256i k)
{
const auto lo = AVX::lo128(AVX::avx_cast<__m256>(k));
return AVX::concat(_mm_unpacklo_ps(lo, lo),
_mm_unpackhi_ps(lo, lo));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<8, 4, __m128>(__m256i k)
{
return AVX::avx_cast<__m128>(AVX::lo128(k));
}
template<> Vc_INTRINSIC Vc_CONST __m256 mask_cast<8, 4, __m256>(__m128i k)
{
const auto tmp = _mm_unpacklo_epi16(k, k);
return AVX::avx_cast<__m256>(AVX::concat(_mm_unpacklo_epi32(tmp, tmp),
_mm_unpackhi_epi32(tmp, tmp)));
}
template<> Vc_INTRINSIC Vc_CONST __m128 mask_cast<8, 8, __m128>(__m256i k)
{
return AVX::avx_cast<__m128>(_mm_packs_epi16(AVX::lo128(k), AVX::hi128(k)));
}
template<> Vc_INTRINSIC Vc_CONST __m256 mask_cast<8, 8, __m256>(__m128i k)
{
return AVX::avx_cast<__m256>(AVX::concat(_mm_unpacklo_epi16(k, k),
_mm_unpackhi_epi16(k, k)));
}
template<> Vc_INTRINSIC Vc_CONST __m256 mask_cast<8, 16, __m256>(__m256i k)
{
return AVX::zeroExtend(mask_cast<8, 8, __m128>(k));
}
#ifdef Vc_IMPL_AVX2
template<> Vc_INTRINSIC Vc_CONST __m256 mask_cast<16, 8, __m256>(__m256i k)
{
const auto flipped = Mem::permute4x64<X0, X2, X1, X3>(k);
return _mm256_castsi256_ps(AVX::unpacklo_epi16(flipped, flipped));
}
#endif
template<> Vc_INTRINSIC Vc_CONST __m256 mask_cast<16, 4, __m256>(__m256i k)
{
const auto tmp = _mm_unpacklo_epi16(AVX::lo128(k), AVX::lo128(k));
return _mm256_castsi256_ps(AVX::concat(_mm_unpacklo_epi32(tmp, tmp), _mm_unpackhi_epi32(tmp, tmp)));
}
template<> Vc_INTRINSIC Vc_CONST __m256 allone<__m256 >() { return AVX::setallone_ps(); }
template<> Vc_INTRINSIC Vc_CONST __m256i allone<__m256i>() { return AVX::setallone_si256(); }
template<> Vc_INTRINSIC Vc_CONST __m256d allone<__m256d>() { return AVX::setallone_pd(); }
template<> Vc_INTRINSIC Vc_CONST __m256 zero<__m256 >() { return _mm256_setzero_ps(); }
template<> Vc_INTRINSIC Vc_CONST __m256i zero<__m256i>() { return _mm256_setzero_si256(); }
template<> Vc_INTRINSIC Vc_CONST __m256d zero<__m256d>() { return _mm256_setzero_pd(); }
Vc_INTRINSIC Vc_CONST __m256 one( float) { return AVX::setone_ps (); }
Vc_INTRINSIC Vc_CONST __m256d one(double) { return AVX::setone_pd (); }
Vc_INTRINSIC Vc_CONST __m256i one( int) { return AVX::setone_epi32(); }
Vc_INTRINSIC Vc_CONST __m256i one( uint) { return AVX::setone_epu32(); }
Vc_INTRINSIC Vc_CONST __m256i one( short) { return AVX::setone_epi16(); }
Vc_INTRINSIC Vc_CONST __m256i one(ushort) { return AVX::setone_epu16(); }
Vc_INTRINSIC Vc_CONST __m256i one( schar) { return AVX::setone_epi8 (); }
Vc_INTRINSIC Vc_CONST __m256i one( uchar) { return AVX::setone_epu8 (); }
Vc_ALWAYS_INLINE Vc_CONST __m256 negate(__m256 v, std::integral_constant<std::size_t, 4>)
{
return _mm256_xor_ps(v, AVX::setsignmask_ps());
}
Vc_ALWAYS_INLINE Vc_CONST __m256d negate(__m256d v, std::integral_constant<std::size_t, 8>)
{
return _mm256_xor_pd(v, AVX::setsignmask_pd());
}
Vc_ALWAYS_INLINE Vc_CONST __m256i negate(__m256i v, std::integral_constant<std::size_t, 4>)
{
return AVX::sign_epi32(v, Detail::allone<__m256i>());
}
Vc_ALWAYS_INLINE Vc_CONST __m256i negate(__m256i v, std::integral_constant<std::size_t, 2>)
{
return AVX::sign_epi16(v, Detail::allone<__m256i>());
}
Vc_INTRINSIC __m256 xor_(__m256 a, __m256 b) { return _mm256_xor_ps(a, b); }
Vc_INTRINSIC __m256d xor_(__m256d a, __m256d b) { return _mm256_xor_pd(a, b); }
Vc_INTRINSIC __m256i xor_(__m256i a, __m256i b)
{
#ifdef Vc_IMPL_AVX2
return _mm256_xor_si256(a, b);
#else
return _mm256_castps_si256(
_mm256_xor_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}
Vc_INTRINSIC __m256 or_(__m256 a, __m256 b) { return _mm256_or_ps(a, b); }
Vc_INTRINSIC __m256d or_(__m256d a, __m256d b) { return _mm256_or_pd(a, b); }
Vc_INTRINSIC __m256i or_(__m256i a, __m256i b)
{
#ifdef Vc_IMPL_AVX2
return _mm256_or_si256(a, b);
#else
return _mm256_castps_si256(
_mm256_or_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}
Vc_INTRINSIC __m256 and_(__m256 a, __m256 b) { return _mm256_and_ps(a, b); }
Vc_INTRINSIC __m256d and_(__m256d a, __m256d b) { return _mm256_and_pd(a, b); }
Vc_INTRINSIC __m256i and_(__m256i a, __m256i b) {
#ifdef Vc_IMPL_AVX2
return _mm256_and_si256(a, b);
#else
return _mm256_castps_si256(
_mm256_and_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}
Vc_INTRINSIC __m256 andnot_(__m256 a, __m256 b) { return _mm256_andnot_ps(a, b); }
Vc_INTRINSIC __m256d andnot_(__m256d a, __m256d b) { return _mm256_andnot_pd(a, b); }
Vc_INTRINSIC __m256i andnot_(__m256i a, __m256i b)
{
#ifdef Vc_IMPL_AVX2
return _mm256_andnot_si256(a, b);
#else
return _mm256_castps_si256(
_mm256_andnot_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b)));
#endif
}
Vc_INTRINSIC __m256 not_(__m256 a) { return andnot_(a, allone<__m256 >()); }
Vc_INTRINSIC __m256d not_(__m256d a) { return andnot_(a, allone<__m256d>()); }
Vc_INTRINSIC __m256i not_(__m256i a) { return andnot_(a, allone<__m256i>()); }
Vc_INTRINSIC __m256 blend(__m256 a, __m256 b, __m256 c) { return _mm256_blendv_ps(a, b, c); }
Vc_INTRINSIC __m256d blend(__m256d a, __m256d b, __m256d c) { return _mm256_blendv_pd(a, b, c); }
Vc_INTRINSIC __m256i blend(__m256i a, __m256i b, __m256i c) { return AVX::blendv_epi8(a, b, c); }
Vc_INTRINSIC __m256 abs(__m256 a, float) { return and_(a, AVX::setabsmask_ps()); }
Vc_INTRINSIC __m256d abs(__m256d a, double) { return and_(a, AVX::setabsmask_pd()); }
Vc_INTRINSIC __m256i abs(__m256i a, int) { return AVX::abs_epi32(a); }
Vc_INTRINSIC __m256i abs(__m256i a, uint) { return a; }
Vc_INTRINSIC __m256i abs(__m256i a, short) { return AVX::abs_epi16(a); }
Vc_INTRINSIC __m256i abs(__m256i a, ushort) { return a; }
Vc_INTRINSIC __m256i abs(__m256i a, schar) { return AVX::abs_epi8 (a); }
Vc_INTRINSIC __m256i abs(__m256i a, uchar) { return a; }
Vc_INTRINSIC __m256 add(__m256 a, __m256 b, float) { return _mm256_add_ps(a, b); }
Vc_INTRINSIC __m256d add(__m256d a, __m256d b, double) { return _mm256_add_pd(a, b); }
Vc_INTRINSIC __m256i add(__m256i a, __m256i b, int) { return AVX::add_epi32(a, b); }
Vc_INTRINSIC __m256i add(__m256i a, __m256i b, uint) { return AVX::add_epi32(a, b); }
Vc_INTRINSIC __m256i add(__m256i a, __m256i b, short) { return AVX::add_epi16(a, b); }
Vc_INTRINSIC __m256i add(__m256i a, __m256i b, ushort) { return AVX::add_epi16(a, b); }
Vc_INTRINSIC __m256 sub(__m256 a, __m256 b, float) { return _mm256_sub_ps(a, b); }
Vc_INTRINSIC __m256d sub(__m256d a, __m256d b, double) { return _mm256_sub_pd(a, b); }
Vc_INTRINSIC __m256i sub(__m256i a, __m256i b, int) { return AVX::sub_epi32(a, b); }
Vc_INTRINSIC __m256i sub(__m256i a, __m256i b, uint) { return AVX::sub_epi32(a, b); }
Vc_INTRINSIC __m256i sub(__m256i a, __m256i b, short) { return AVX::sub_epi16(a, b); }
Vc_INTRINSIC __m256i sub(__m256i a, __m256i b, ushort) { return AVX::sub_epi16(a, b); }
Vc_INTRINSIC __m256 mul(__m256 a, __m256 b, float) { return _mm256_mul_ps(a, b); }
Vc_INTRINSIC __m256d mul(__m256d a, __m256d b, double) { return _mm256_mul_pd(a, b); }
Vc_INTRINSIC __m256i mul(__m256i a, __m256i b, int) { return AVX::mullo_epi32(a, b); }
Vc_INTRINSIC __m256i mul(__m256i a, __m256i b, uint) { return AVX::mullo_epi32(a, b); }
Vc_INTRINSIC __m256i mul(__m256i a, __m256i b, short) { return AVX::mullo_epi16(a, b); }
Vc_INTRINSIC __m256i mul(__m256i a, __m256i b, ushort) { return AVX::mullo_epi16(a, b); }
Vc_INTRINSIC __m256 div(__m256 a, __m256 b, float) { return _mm256_div_ps(a, b); }
Vc_INTRINSIC __m256d div(__m256d a, __m256d b, double) { return _mm256_div_pd(a, b); }
Vc_INTRINSIC __m256i div(__m256i a, __m256i b, int) {
using namespace AVX;
const __m256d lo1 = _mm256_cvtepi32_pd(lo128(a));
const __m256d lo2 = _mm256_cvtepi32_pd(lo128(b));
const __m256d hi1 = _mm256_cvtepi32_pd(hi128(a));
const __m256d hi2 = _mm256_cvtepi32_pd(hi128(b));
return concat(_mm256_cvttpd_epi32(_mm256_div_pd(lo1, lo2)),
_mm256_cvttpd_epi32(_mm256_div_pd(hi1, hi2)));
}
Vc_INTRINSIC __m256i div(__m256i a, __m256i b, uint) {
using namespace AVX;
const __m256i aa = add_epi32(a, set1_epi32(-2147483648));
const __m256i bb = add_epi32(b, set1_epi32(-2147483648));
const __m256d loa = _mm256_add_pd(_mm256_cvtepi32_pd(lo128(aa)), set1_pd(2147483648.));
const __m256d hia = _mm256_add_pd(_mm256_cvtepi32_pd(hi128(aa)), set1_pd(2147483648.));
const __m256d lob = _mm256_add_pd(_mm256_cvtepi32_pd(lo128(bb)), set1_pd(2147483648.));
const __m256d hib = _mm256_add_pd(_mm256_cvtepi32_pd(hi128(bb)), set1_pd(2147483648.));
return avx_cast<__m256i>(_mm256_blendv_ps(
avx_cast<__m256>(concat(_mm256_cvttpd_epi32(_mm256_div_pd(loa, lob)),
_mm256_cvttpd_epi32(_mm256_div_pd(hia, hib)))),
avx_cast<__m256>(a),
avx_cast<__m256>(cmpeq_epi32(b, setone_epi32()))));
}
Vc_INTRINSIC __m256i div(__m256i a, __m256i b, short) {
using namespace AVX;
const __m256 lo =
_mm256_div_ps(convert<short, float>(lo128(a)), convert<short, float>(lo128(b)));
const __m256 hi =
_mm256_div_ps(convert<short, float>(hi128(a)), convert<short, float>(hi128(b)));
return concat(convert<float, short>(lo), convert<float, short>(hi));
}
template <typename T> Vc_INTRINSIC T add(Common::IntrinsicType<T, 32 / sizeof(T)> a, T)
{
return {add(add(AVX::lo128(a), AVX::hi128(a), T()), T())};
}
template <typename T> Vc_INTRINSIC T mul(Common::IntrinsicType<T, 32 / sizeof(T)> a, T)
{
return {mul(mul(AVX::lo128(a), AVX::hi128(a), T()), T())};
}
template <typename T> Vc_INTRINSIC T min(Common::IntrinsicType<T, 32 / sizeof(T)> a, T)
{
return {min(min(AVX::lo128(a), AVX::hi128(a), T()), T())};
}
template <typename T> Vc_INTRINSIC T max(Common::IntrinsicType<T, 32 / sizeof(T)> a, T)
{
return {max(max(AVX::lo128(a), AVX::hi128(a), T()), T())};
}
Vc_INTRINSIC __m256 cmpeq(__m256 a, __m256 b, float) { return AvxIntrinsics::cmpeq_ps(a, b); }
Vc_INTRINSIC __m256d cmpeq(__m256d a, __m256d b, double) { return AvxIntrinsics::cmpeq_pd(a, b); }
Vc_INTRINSIC __m256i cmpeq(__m256i a, __m256i b, int) { return AvxIntrinsics::cmpeq_epi32(a, b); }
Vc_INTRINSIC __m256i cmpeq(__m256i a, __m256i b, uint) { return AvxIntrinsics::cmpeq_epi32(a, b); }
Vc_INTRINSIC __m256i cmpeq(__m256i a, __m256i b, short) { return AvxIntrinsics::cmpeq_epi16(a, b); }
Vc_INTRINSIC __m256i cmpeq(__m256i a, __m256i b, ushort) { return AvxIntrinsics::cmpeq_epi16(a, b); }
Vc_INTRINSIC __m256 cmpneq(__m256 a, __m256 b, float) { return AvxIntrinsics::cmpneq_ps(a, b); }
Vc_INTRINSIC __m256d cmpneq(__m256d a, __m256d b, double) { return AvxIntrinsics::cmpneq_pd(a, b); }
Vc_INTRINSIC __m256i cmpneq(__m256i a, __m256i b, int) { return not_(AvxIntrinsics::cmpeq_epi32(a, b)); }
Vc_INTRINSIC __m256i cmpneq(__m256i a, __m256i b, uint) { return not_(AvxIntrinsics::cmpeq_epi32(a, b)); }
Vc_INTRINSIC __m256i cmpneq(__m256i a, __m256i b, short) { return not_(AvxIntrinsics::cmpeq_epi16(a, b)); }
Vc_INTRINSIC __m256i cmpneq(__m256i a, __m256i b, ushort) { return not_(AvxIntrinsics::cmpeq_epi16(a, b)); }
Vc_INTRINSIC __m256i cmpneq(__m256i a, __m256i b, schar) { return not_(AvxIntrinsics::cmpeq_epi8 (a, b)); }
Vc_INTRINSIC __m256i cmpneq(__m256i a, __m256i b, uchar) { return not_(AvxIntrinsics::cmpeq_epi8 (a, b)); }
Vc_INTRINSIC __m256 cmpgt(__m256 a, __m256 b, float) { return AVX::cmpgt_ps(a, b); }
Vc_INTRINSIC __m256d cmpgt(__m256d a, __m256d b, double) { return AVX::cmpgt_pd(a, b); }
Vc_INTRINSIC __m256i cmpgt(__m256i a, __m256i b, int) { return AVX::cmpgt_epi32(a, b); }
Vc_INTRINSIC __m256i cmpgt(__m256i a, __m256i b, uint) { return AVX::cmpgt_epu32(a, b); }
Vc_INTRINSIC __m256i cmpgt(__m256i a, __m256i b, short) { return AVX::cmpgt_epi16(a, b); }
Vc_INTRINSIC __m256i cmpgt(__m256i a, __m256i b, ushort) { return AVX::cmpgt_epu16(a, b); }
Vc_INTRINSIC __m256i cmpgt(__m256i a, __m256i b, schar) { return AVX::cmpgt_epi8 (a, b); }
Vc_INTRINSIC __m256i cmpgt(__m256i a, __m256i b, uchar) { return AVX::cmpgt_epu8 (a, b); }
Vc_INTRINSIC __m256 cmpge(__m256 a, __m256 b, float) { return AVX::cmpge_ps(a, b); }
Vc_INTRINSIC __m256d cmpge(__m256d a, __m256d b, double) { return AVX::cmpge_pd(a, b); }
Vc_INTRINSIC __m256i cmpge(__m256i a, __m256i b, int) { return not_(AVX::cmpgt_epi32(b, a)); }
Vc_INTRINSIC __m256i cmpge(__m256i a, __m256i b, uint) { return not_(AVX::cmpgt_epu32(b, a)); }
Vc_INTRINSIC __m256i cmpge(__m256i a, __m256i b, short) { return not_(AVX::cmpgt_epi16(b, a)); }
Vc_INTRINSIC __m256i cmpge(__m256i a, __m256i b, ushort) { return not_(AVX::cmpgt_epu16(b, a)); }
Vc_INTRINSIC __m256i cmpge(__m256i a, __m256i b, schar) { return not_(AVX::cmpgt_epi8 (b, a)); }
Vc_INTRINSIC __m256i cmpge(__m256i a, __m256i b, uchar) { return not_(AVX::cmpgt_epu8 (b, a)); }
Vc_INTRINSIC __m256 cmple(__m256 a, __m256 b, float) { return AVX::cmple_ps(a, b); }
Vc_INTRINSIC __m256d cmple(__m256d a, __m256d b, double) { return AVX::cmple_pd(a, b); }
Vc_INTRINSIC __m256i cmple(__m256i a, __m256i b, int) { return not_(AVX::cmpgt_epi32(a, b)); }
Vc_INTRINSIC __m256i cmple(__m256i a, __m256i b, uint) { return not_(AVX::cmpgt_epu32(a, b)); }
Vc_INTRINSIC __m256i cmple(__m256i a, __m256i b, short) { return not_(AVX::cmpgt_epi16(a, b)); }
Vc_INTRINSIC __m256i cmple(__m256i a, __m256i b, ushort) { return not_(AVX::cmpgt_epu16(a, b)); }
Vc_INTRINSIC __m256i cmple(__m256i a, __m256i b, schar) { return not_(AVX::cmpgt_epi8 (a, b)); }
Vc_INTRINSIC __m256i cmple(__m256i a, __m256i b, uchar) { return not_(AVX::cmpgt_epu8 (a, b)); }
Vc_INTRINSIC __m256 cmplt(__m256 a, __m256 b, float) { return AVX::cmplt_ps(a, b); }
Vc_INTRINSIC __m256d cmplt(__m256d a, __m256d b, double) { return AVX::cmplt_pd(a, b); }
Vc_INTRINSIC __m256i cmplt(__m256i a, __m256i b, int) { return AVX::cmpgt_epi32(b, a); }
Vc_INTRINSIC __m256i cmplt(__m256i a, __m256i b, uint) { return AVX::cmpgt_epu32(b, a); }
Vc_INTRINSIC __m256i cmplt(__m256i a, __m256i b, short) { return AVX::cmpgt_epi16(b, a); }
Vc_INTRINSIC __m256i cmplt(__m256i a, __m256i b, ushort) { return AVX::cmpgt_epu16(b, a); }
Vc_INTRINSIC __m256i cmplt(__m256i a, __m256i b, schar) { return AVX::cmpgt_epi8 (b, a); }
Vc_INTRINSIC __m256i cmplt(__m256i a, __m256i b, uchar) { return AVX::cmpgt_epu8 (b, a); }
Vc_INTRINSIC __m256 fma(__m256 a, __m256 b, __m256 c, float) {
#ifdef Vc_IMPL_FMA4
return _mm256_macc_ps(a, b, c);
#elif defined Vc_IMPL_FMA
return _mm256_fmadd_ps(a, b, c);
#else
using namespace AVX;
__m256d v1_0 = _mm256_cvtps_pd(lo128(a));
__m256d v1_1 = _mm256_cvtps_pd(hi128(a));
__m256d v2_0 = _mm256_cvtps_pd(lo128(b));
__m256d v2_1 = _mm256_cvtps_pd(hi128(b));
__m256d v3_0 = _mm256_cvtps_pd(lo128(c));
__m256d v3_1 = _mm256_cvtps_pd(hi128(c));
return concat(_mm256_cvtpd_ps(_mm256_add_pd(_mm256_mul_pd(v1_0, v2_0), v3_0)),
_mm256_cvtpd_ps(_mm256_add_pd(_mm256_mul_pd(v1_1, v2_1), v3_1)));
#endif
}
Vc_INTRINSIC __m256d fma(__m256d a, __m256d b, __m256d c, double)
{
#ifdef Vc_IMPL_FMA4
return _mm256_macc_pd(a, b, c);
#elif defined Vc_IMPL_FMA
return _mm256_fmadd_pd(a, b, c);
#else
using namespace AVX;
__m256d h1 = and_(a, _mm256_broadcast_sd(reinterpret_cast<const double *>(
&c_general::highMaskDouble)));
__m256d h2 = and_(b, _mm256_broadcast_sd(reinterpret_cast<const double *>(
&c_general::highMaskDouble)));
const __m256d l1 = _mm256_sub_pd(a, h1);
const __m256d l2 = _mm256_sub_pd(b, h2);
const __m256d ll = mul(l1, l2, double());
const __m256d lh = add(mul(l1, h2, double()), mul(h1, l2, double()), double());
const __m256d hh = mul(h1, h2, double());
const __m256d lh_lt_v3 = cmplt(abs(lh, double()), abs(c, double()), double());
const __m256d x = _mm256_blendv_pd(c, lh, lh_lt_v3);
const __m256d y = _mm256_blendv_pd(lh, c, lh_lt_v3);
return add(add(ll, x, double()), add(y, hh, double()), double());
#endif
}
template <typename T> Vc_INTRINSIC __m256i fma(__m256i a, __m256i b, __m256i c, T)
{
return add(mul(a, b, T()), c, T());
}
template <int shift> Vc_INTRINSIC __m256i shiftRight(__m256i a, int) { return AVX::srai_epi32<shift>(a); }
template <int shift> Vc_INTRINSIC __m256i shiftRight(__m256i a, uint) { return AVX::srli_epi32<shift>(a); }
template <int shift> Vc_INTRINSIC __m256i shiftRight(__m256i a, short) { return AVX::srai_epi16<shift>(a); }
template <int shift> Vc_INTRINSIC __m256i shiftRight(__m256i a, ushort) { return AVX::srli_epi16<shift>(a); }
Vc_INTRINSIC __m256i shiftRight(__m256i a, int shift, int) { return AVX::sra_epi32(a, _mm_cvtsi32_si128(shift)); }
Vc_INTRINSIC __m256i shiftRight(__m256i a, int shift, uint) { return AVX::srl_epi32(a, _mm_cvtsi32_si128(shift)); }
Vc_INTRINSIC __m256i shiftRight(__m256i a, int shift, short) { return AVX::sra_epi16(a, _mm_cvtsi32_si128(shift)); }
Vc_INTRINSIC __m256i shiftRight(__m256i a, int shift, ushort) { return AVX::srl_epi16(a, _mm_cvtsi32_si128(shift)); }
template <int shift> Vc_INTRINSIC __m256i shiftLeft(__m256i a, int) { return AVX::slli_epi32<shift>(a); }
template <int shift> Vc_INTRINSIC __m256i shiftLeft(__m256i a, uint) { return AVX::slli_epi32<shift>(a); }
template <int shift> Vc_INTRINSIC __m256i shiftLeft(__m256i a, short) { return AVX::slli_epi16<shift>(a); }
template <int shift> Vc_INTRINSIC __m256i shiftLeft(__m256i a, ushort) { return AVX::slli_epi16<shift>(a); }
Vc_INTRINSIC __m256i shiftLeft(__m256i a, int shift, int) { return AVX::sll_epi32(a, _mm_cvtsi32_si128(shift)); }
Vc_INTRINSIC __m256i shiftLeft(__m256i a, int shift, uint) { return AVX::sll_epi32(a, _mm_cvtsi32_si128(shift)); }
Vc_INTRINSIC __m256i shiftLeft(__m256i a, int shift, short) { return AVX::sll_epi16(a, _mm_cvtsi32_si128(shift)); }
Vc_INTRINSIC __m256i shiftLeft(__m256i a, int shift, ushort) { return AVX::sll_epi16(a, _mm_cvtsi32_si128(shift)); }
Vc_INTRINSIC __m256 zeroExtendIfNeeded(__m256 x) { return x; }
Vc_INTRINSIC __m256d zeroExtendIfNeeded(__m256d x) { return x; }
Vc_INTRINSIC __m256i zeroExtendIfNeeded(__m256i x) { return x; }
Vc_INTRINSIC __m256 zeroExtendIfNeeded(__m128 x) { return AVX::zeroExtend(x); }
Vc_INTRINSIC __m256d zeroExtendIfNeeded(__m128d x) { return AVX::zeroExtend(x); }
Vc_INTRINSIC __m256i zeroExtendIfNeeded(__m128i x) { return AVX::zeroExtend(x); }
Vc_INTRINSIC __m256 avx_broadcast( float x) { return _mm256_set1_ps(x); }
Vc_INTRINSIC __m256d avx_broadcast(double x) { return _mm256_set1_pd(x); }
Vc_INTRINSIC __m256i avx_broadcast( int x) { return _mm256_set1_epi32(x); }
Vc_INTRINSIC __m256i avx_broadcast( uint x) { return _mm256_set1_epi32(x); }
Vc_INTRINSIC __m256i avx_broadcast( short x) { return _mm256_set1_epi16(x); }
Vc_INTRINSIC __m256i avx_broadcast(ushort x) { return _mm256_set1_epi16(x); }
Vc_INTRINSIC __m256i avx_broadcast( char x) { return _mm256_set1_epi8(x); }
Vc_INTRINSIC __m256i avx_broadcast( schar x) { return _mm256_set1_epi8(x); }
Vc_INTRINSIC __m256i avx_broadcast( uchar x) { return _mm256_set1_epi8(x); }
template <Vc::Implementation Impl, typename T,
typename = enable_if<(Impl >= AVXImpl && Impl <= AVX2Impl)>>
Vc_CONST_L AVX2::Vector<T> sorted(AVX2::Vector<T> x) Vc_CONST_R;
template <typename T> Vc_INTRINSIC Vc_CONST AVX2::Vector<T> sorted(AVX2::Vector<T> x)
{
return sorted<CurrentImplementation::current()>(x);
}
template <typename T, typename V>
static Vc_INTRINSIC Vc_CONST enable_if<(sizeof(V) == 32), V> shifted(V v, int amount)
{
using namespace AVX;
constexpr int S = sizeof(T);
switch (amount) {
case 0: return v;
case 1: return shifted<sanitize<V>( 1 * S)>(v);
case 2: return shifted<sanitize<V>( 2 * S)>(v);
case 3: return shifted<sanitize<V>( 3 * S)>(v);
case -1: return shifted<sanitize<V>(-1 * S)>(v);
case -2: return shifted<sanitize<V>(-2 * S)>(v);
case -3: return shifted<sanitize<V>(-3 * S)>(v);
}
if (sizeof(T) <= 4) {
switch (amount) {
case 4: return shifted<sanitize<V>( 4 * S)>(v);
case 5: return shifted<sanitize<V>( 5 * S)>(v);
case 6: return shifted<sanitize<V>( 6 * S)>(v);
case 7: return shifted<sanitize<V>( 7 * S)>(v);
case -4: return shifted<sanitize<V>(-4 * S)>(v);
case -5: return shifted<sanitize<V>(-5 * S)>(v);
case -6: return shifted<sanitize<V>(-6 * S)>(v);
case -7: return shifted<sanitize<V>(-7 * S)>(v);
}
if (sizeof(T) <= 2) {
switch (amount) {
case 8: return shifted<sanitize<V>( 8 * S)>(v);
case 9: return shifted<sanitize<V>( 9 * S)>(v);
case 10: return shifted<sanitize<V>( 10 * S)>(v);
case 11: return shifted<sanitize<V>( 11 * S)>(v);
case 12: return shifted<sanitize<V>( 12 * S)>(v);
case 13: return shifted<sanitize<V>( 13 * S)>(v);
case 14: return shifted<sanitize<V>( 14 * S)>(v);
case 15: return shifted<sanitize<V>( 15 * S)>(v);
case -8: return shifted<sanitize<V>(- 8 * S)>(v);
case -9: return shifted<sanitize<V>(- 9 * S)>(v);
case -10: return shifted<sanitize<V>(-10 * S)>(v);
case -11: return shifted<sanitize<V>(-11 * S)>(v);
case -12: return shifted<sanitize<V>(-12 * S)>(v);
case -13: return shifted<sanitize<V>(-13 * S)>(v);
case -14: return shifted<sanitize<V>(-14 * S)>(v);
case -15: return shifted<sanitize<V>(-15 * S)>(v);
}
if (sizeof(T) == 1) {
switch (amount) {
case 16: return shifted<sanitize<V>( 16)>(v);
case 17: return shifted<sanitize<V>( 17)>(v);
case 18: return shifted<sanitize<V>( 18)>(v);
case 19: return shifted<sanitize<V>( 19)>(v);
case 20: return shifted<sanitize<V>( 20)>(v);
case 21: return shifted<sanitize<V>( 21)>(v);
case 22: return shifted<sanitize<V>( 22)>(v);
case 23: return shifted<sanitize<V>( 23)>(v);
case 24: return shifted<sanitize<V>( 24)>(v);
case 25: return shifted<sanitize<V>( 25)>(v);
case 26: return shifted<sanitize<V>( 26)>(v);
case 27: return shifted<sanitize<V>( 27)>(v);
case 28: return shifted<sanitize<V>( 28)>(v);
case 29: return shifted<sanitize<V>( 29)>(v);
case 30: return shifted<sanitize<V>( 30)>(v);
case 31: return shifted<sanitize<V>( 31)>(v);
case -16: return shifted<sanitize<V>(-16)>(v);
case -17: return shifted<sanitize<V>(-17)>(v);
case -18: return shifted<sanitize<V>(-18)>(v);
case -19: return shifted<sanitize<V>(-19)>(v);
case -20: return shifted<sanitize<V>(-20)>(v);
case -21: return shifted<sanitize<V>(-21)>(v);
case -22: return shifted<sanitize<V>(-22)>(v);
case -23: return shifted<sanitize<V>(-23)>(v);
case -24: return shifted<sanitize<V>(-24)>(v);
case -25: return shifted<sanitize<V>(-25)>(v);
case -26: return shifted<sanitize<V>(-26)>(v);
case -27: return shifted<sanitize<V>(-27)>(v);
case -28: return shifted<sanitize<V>(-28)>(v);
case -29: return shifted<sanitize<V>(-29)>(v);
case -30: return shifted<sanitize<V>(-30)>(v);
case -31: return shifted<sanitize<V>(-31)>(v);
}
}
}
}
return avx_cast<V>(_mm256_setzero_ps());
}
template <typename T, typename V>
static Vc_INTRINSIC Vc_CONST enable_if<(sizeof(V) == 16), V> shifted(V v, int amount)
{
using namespace AVX;
switch (amount) {
case 0: return v;
case 1: return avx_cast<V>(_mm_srli_si128(avx_cast<__m128i>(v), sanitize<V>(1 * sizeof(T))));
case 2: return avx_cast<V>(_mm_srli_si128(avx_cast<__m128i>(v), sanitize<V>(2 * sizeof(T))));
case 3: return avx_cast<V>(_mm_srli_si128(avx_cast<__m128i>(v), sanitize<V>(3 * sizeof(T))));
case -1: return avx_cast<V>(_mm_slli_si128(avx_cast<__m128i>(v), sanitize<V>(1 * sizeof(T))));
case -2: return avx_cast<V>(_mm_slli_si128(avx_cast<__m128i>(v), sanitize<V>(2 * sizeof(T))));
case -3: return avx_cast<V>(_mm_slli_si128(avx_cast<__m128i>(v), sanitize<V>(3 * sizeof(T))));
}
if (sizeof(T) <= 2) {
switch (amount) {
case 4: return avx_cast<V>(_mm_srli_si128(avx_cast<__m128i>(v), sanitize<V>(4 * sizeof(T))));
case 5: return avx_cast<V>(_mm_srli_si128(avx_cast<__m128i>(v), sanitize<V>(5 * sizeof(T))));
case 6: return avx_cast<V>(_mm_srli_si128(avx_cast<__m128i>(v), sanitize<V>(6 * sizeof(T))));
case 7: return avx_cast<V>(_mm_srli_si128(avx_cast<__m128i>(v), sanitize<V>(7 * sizeof(T))));
case -4: return avx_cast<V>(_mm_slli_si128(avx_cast<__m128i>(v), sanitize<V>(4 * sizeof(T))));
case -5: return avx_cast<V>(_mm_slli_si128(avx_cast<__m128i>(v), sanitize<V>(5 * sizeof(T))));
case -6: return avx_cast<V>(_mm_slli_si128(avx_cast<__m128i>(v), sanitize<V>(6 * sizeof(T))));
case -7: return avx_cast<V>(_mm_slli_si128(avx_cast<__m128i>(v), sanitize<V>(7 * sizeof(T))));
}
}
return avx_cast<V>(_mm_setzero_ps());
}
template <typename T, size_t N, typename V>
static Vc_INTRINSIC Vc_CONST enable_if<(sizeof(V) == 32 && N == 4), V> rotated(V v,
int amount)
{
using namespace AVX;
const __m128i vLo = avx_cast<__m128i>(lo128(v));
const __m128i vHi = avx_cast<__m128i>(hi128(v));
switch (static_cast<unsigned int>(amount) % N) {
case 0:
return v;
case 1:
return avx_cast<V>(concat(SSE::alignr_epi8<sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<sizeof(T)>(vLo, vHi)));
case 2:
return Mem::permute128<X1, X0>(v);
case 3:
return avx_cast<V>(concat(SSE::alignr_epi8<sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<sizeof(T)>(vHi, vLo)));
}
return avx_cast<V>(_mm256_setzero_ps());
}
template <typename T, size_t N, typename V>
static Vc_INTRINSIC Vc_CONST enable_if<(sizeof(V) == 32 && N == 8), V> rotated(V v,
int amount)
{
using namespace AVX;
const __m128i vLo = avx_cast<__m128i>(lo128(v));
const __m128i vHi = avx_cast<__m128i>(hi128(v));
switch (static_cast<unsigned int>(amount) % N) {
case 0:
return v;
case 1:
return avx_cast<V>(concat(SSE::alignr_epi8<1 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<1 * sizeof(T)>(vLo, vHi)));
case 2:
return avx_cast<V>(concat(SSE::alignr_epi8<2 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<2 * sizeof(T)>(vLo, vHi)));
case 3:
return avx_cast<V>(concat(SSE::alignr_epi8<3 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<3 * sizeof(T)>(vLo, vHi)));
case 4:
return Mem::permute128<X1, X0>(v);
case 5:
return avx_cast<V>(concat(SSE::alignr_epi8<1 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<1 * sizeof(T)>(vHi, vLo)));
case 6:
return avx_cast<V>(concat(SSE::alignr_epi8<2 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<2 * sizeof(T)>(vHi, vLo)));
case 7:
return avx_cast<V>(concat(SSE::alignr_epi8<3 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<3 * sizeof(T)>(vHi, vLo)));
}
return avx_cast<V>(_mm256_setzero_ps());
}
#ifdef Vc_IMPL_AVX2
template <typename T, size_t N, typename V>
static Vc_INTRINSIC Vc_CONST enable_if<(sizeof(V) == 32 && N == 16), V> rotated(
V v, int amount)
{
using namespace AVX;
const __m128i vLo = avx_cast<__m128i>(lo128(v));
const __m128i vHi = avx_cast<__m128i>(hi128(v));
switch (static_cast<unsigned int>(amount) % N) {
case 0:
return v;
case 1:
return avx_cast<V>(concat(SSE::alignr_epi8<1 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<1 * sizeof(T)>(vLo, vHi)));
case 2:
return avx_cast<V>(concat(SSE::alignr_epi8<2 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<2 * sizeof(T)>(vLo, vHi)));
case 3:
return avx_cast<V>(concat(SSE::alignr_epi8<3 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<3 * sizeof(T)>(vLo, vHi)));
case 4:
return Mem::permute4x64<X1, X2, X3, X0>(v);
case 5:
return avx_cast<V>(concat(SSE::alignr_epi8<5 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<5 * sizeof(T)>(vLo, vHi)));
case 6:
return avx_cast<V>(concat(SSE::alignr_epi8<6 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<6 * sizeof(T)>(vLo, vHi)));
case 7:
return avx_cast<V>(concat(SSE::alignr_epi8<7 * sizeof(T)>(vHi, vLo),
SSE::alignr_epi8<7 * sizeof(T)>(vLo, vHi)));
case 8:
return Mem::permute128<X1, X0>(v);
case 9:
return avx_cast<V>(concat(SSE::alignr_epi8<1 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<1 * sizeof(T)>(vHi, vLo)));
case 10:
return avx_cast<V>(concat(SSE::alignr_epi8<2 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<2 * sizeof(T)>(vHi, vLo)));
case 11:
return avx_cast<V>(concat(SSE::alignr_epi8<3 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<3 * sizeof(T)>(vHi, vLo)));
case 12:
return Mem::permute4x64<X3, X0, X1, X2>(v);
case 13:
return avx_cast<V>(concat(SSE::alignr_epi8<5 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<5 * sizeof(T)>(vHi, vLo)));
case 14:
return avx_cast<V>(concat(SSE::alignr_epi8<6 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<6 * sizeof(T)>(vHi, vLo)));
case 15:
return avx_cast<V>(concat(SSE::alignr_epi8<7 * sizeof(T)>(vLo, vHi),
SSE::alignr_epi8<7 * sizeof(T)>(vHi, vLo)));
}
return avx_cast<V>(_mm256_setzero_ps());
}
#endif
Vc_INTRINSIC Vc_CONST int testc(__m128 a, __m128 b) { return _mm_testc_si128(_mm_castps_si128(a), _mm_castps_si128(b)); }
Vc_INTRINSIC Vc_CONST int testc(__m256 a, __m256 b) { return _mm256_testc_ps(a, b); }
Vc_INTRINSIC Vc_CONST int testc(__m256d a, __m256d b) { return _mm256_testc_pd(a, b); }
Vc_INTRINSIC Vc_CONST int testc(__m256i a, __m256i b) { return _mm256_testc_si256(a, b); }
Vc_INTRINSIC Vc_CONST int testz(__m128 a, __m128 b) { return _mm_testz_si128(_mm_castps_si128(a), _mm_castps_si128(b)); }
Vc_INTRINSIC Vc_CONST int testz(__m256 a, __m256 b) { return _mm256_testz_ps(a, b); }
Vc_INTRINSIC Vc_CONST int testz(__m256d a, __m256d b) { return _mm256_testz_pd(a, b); }
Vc_INTRINSIC Vc_CONST int testz(__m256i a, __m256i b) { return _mm256_testz_si256(a, b); }
Vc_INTRINSIC Vc_CONST int testnzc(__m128 a, __m128 b) { return _mm_testnzc_si128(_mm_castps_si128(a), _mm_castps_si128(b)); }
Vc_INTRINSIC Vc_CONST int testnzc(__m256 a, __m256 b) { return _mm256_testnzc_ps(a, b); }
Vc_INTRINSIC Vc_CONST int testnzc(__m256d a, __m256d b) { return _mm256_testnzc_pd(a, b); }
Vc_INTRINSIC Vc_CONST int testnzc(__m256i a, __m256i b) { return _mm256_testnzc_si256(a, b); }
Vc_INTRINSIC Vc_CONST int movemask(__m256i a) { return AVX::movemask_epi8(a); }
Vc_INTRINSIC Vc_CONST int movemask(__m128i a) { return _mm_movemask_epi8(a); }
Vc_INTRINSIC Vc_CONST int movemask(__m256d a) { return _mm256_movemask_pd(a); }
Vc_INTRINSIC Vc_CONST int movemask(__m128d a) { return _mm_movemask_pd(a); }
Vc_INTRINSIC Vc_CONST int movemask(__m256 a) { return _mm256_movemask_ps(a); }
Vc_INTRINSIC Vc_CONST int movemask(__m128 a) { return _mm_movemask_ps(a); }
template <size_t N, typename Flags>
Vc_INTRINSIC void mask_store(__m256i k, bool *mem, Flags)
{
static_assert(
N == 4 || N == 8 || N == 16,
"mask_store(__m256i, bool *) is only implemented for 4, 8, and 16 entries");
switch (N) {
case 4:
*aliasing_cast<int32_t>(mem) = (_mm_movemask_epi8(AVX::lo128(k)) |
(_mm_movemask_epi8(AVX::hi128(k)) << 16)) &
0x01010101;
break;
case 8: {
const auto k2 = _mm_srli_epi16(_mm_packs_epi16(AVX::lo128(k), AVX::hi128(k)), 15);
const auto k3 = _mm_packs_epi16(k2, _mm_setzero_si128());
#ifdef __x86_64__
*aliasing_cast<int64_t>(mem) = _mm_cvtsi128_si64(k3);
#else
*aliasing_cast<int32_t>(mem) = _mm_cvtsi128_si32(k3);
*aliasing_cast<int32_t>(mem + 4) = _mm_extract_epi32(k3, 1);
#endif
} break;
case 16: {
const auto bools = Detail::and_(AVX::_mm_setone_epu8(),
_mm_packs_epi16(AVX::lo128(k), AVX::hi128(k)));
if (Flags::IsAligned) {
_mm_store_si128(reinterpret_cast<__m128i *>(mem), bools);
} else {
_mm_storeu_si128(reinterpret_cast<__m128i *>(mem), bools);
}
} break;
default:
Vc_UNREACHABLE();
}
}
template <typename R, size_t N, typename Flags>
Vc_INTRINSIC R mask_load(const bool *mem, Flags,
enable_if<std::is_same<R, __m128>::value> = nullarg)
{
static_assert(N == 4 || N == 8,
"mask_load<__m128>(const bool *) is only implemented for 4, 8 entries");
switch (N) {
case 4: {
__m128i k = _mm_cvtsi32_si128(*aliasing_cast<int32_t>(mem));
k = _mm_unpacklo_epi8(k, k);
k = _mm_unpacklo_epi16(k, k);
k = _mm_cmpgt_epi32(k, _mm_setzero_si128());
return AVX::avx_cast<__m128>(k);
}
case 8: {
#ifdef __x86_64__
__m128i k = _mm_cvtsi64_si128(*aliasing_cast<int64_t>(mem));
#else
__m128i k = _mm_castpd_si128(_mm_load_sd(aliasing_cast<double>(mem)));
#endif
return AVX::avx_cast<__m128>(
_mm_cmpgt_epi16(_mm_unpacklo_epi8(k, k), _mm_setzero_si128()));
}
default:
Vc_UNREACHABLE();
}
}
template <typename R, size_t N, typename Flags>
Vc_INTRINSIC R mask_load(const bool *mem, Flags,
enable_if<std::is_same<R, __m256>::value> = nullarg)
{
static_assert(
N == 4 || N == 8 || N == 16,
"mask_load<__m256>(const bool *) is only implemented for 4, 8, and 16 entries");
switch (N) {
case 4: {
__m128i k = AVX::avx_cast<__m128i>(_mm_and_ps(
_mm_set1_ps(*aliasing_cast<float>(mem)),
AVX::avx_cast<__m128>(_mm_setr_epi32(0x1, 0x100, 0x10000, 0x1000000))));
k = _mm_cmpgt_epi32(k, _mm_setzero_si128());
return AVX::avx_cast<__m256>(
AVX::concat(_mm_unpacklo_epi32(k, k), _mm_unpackhi_epi32(k, k)));
}
case 8: {
#ifdef __x86_64__
__m128i k = _mm_cvtsi64_si128(*aliasing_cast<int64_t>(mem));
#else
__m128i k = _mm_castpd_si128(_mm_load_sd(aliasing_cast<double>(mem)));
#endif
k = _mm_cmpgt_epi16(_mm_unpacklo_epi8(k, k), _mm_setzero_si128());
return AVX::avx_cast<__m256>(
AVX::concat(_mm_unpacklo_epi16(k, k), _mm_unpackhi_epi16(k, k)));
}
case 16: {
const auto k128 = _mm_cmpgt_epi8(
Flags::IsAligned ? _mm_load_si128(reinterpret_cast<const __m128i *>(mem))
: _mm_loadu_si128(reinterpret_cast<const __m128i *>(mem)),
_mm_setzero_si128());
return AVX::avx_cast<__m256>(
AVX::concat(_mm_unpacklo_epi8(k128, k128), _mm_unpackhi_epi8(k128, k128)));
}
default:
Vc_UNREACHABLE();
return R();
}
}
template <size_t Size>
Vc_INTRINSIC_L Vc_CONST_L int mask_to_int(__m256i x) Vc_INTRINSIC_R Vc_CONST_R;
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<4>(__m256i k)
{
return movemask(AVX::avx_cast<__m256d>(k));
}
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<8>(__m256i k)
{
return movemask(AVX::avx_cast<__m256>(k));
}
#ifdef Vc_IMPL_BMI2
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<16>(__m256i k)
{
return _pext_u32(movemask(k), 0x55555555u);
}
#endif
template <> Vc_INTRINSIC Vc_CONST int mask_to_int<32>(__m256i k)
{
return movemask(k);
}
template<typename V> struct InterleaveImpl<V, 16, 32> {
template<typename I> static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0,
const typename V::AsArg v1)
{
const __m256i tmp0 = AVX::unpacklo_epi16(v0.data(), v1.data());
const __m256i tmp1 = AVX::unpackhi_epi16(v0.data(), v1.data());
using namespace AVX;
*aliasing_cast<uint32_t>(&data[i[ 0]]) = _mm_cvtsi128_si32(lo128(tmp0));
*aliasing_cast<uint32_t>(&data[i[ 1]]) = _mm_extract_epi32(lo128(tmp0), 1);
*aliasing_cast<uint32_t>(&data[i[ 2]]) = _mm_extract_epi32(lo128(tmp0), 2);
*aliasing_cast<uint32_t>(&data[i[ 3]]) = _mm_extract_epi32(lo128(tmp0), 3);
*aliasing_cast<uint32_t>(&data[i[ 4]]) = _mm_cvtsi128_si32(lo128(tmp1));
*aliasing_cast<uint32_t>(&data[i[ 5]]) = _mm_extract_epi32(lo128(tmp1), 1);
*aliasing_cast<uint32_t>(&data[i[ 6]]) = _mm_extract_epi32(lo128(tmp1), 2);
*aliasing_cast<uint32_t>(&data[i[ 7]]) = _mm_extract_epi32(lo128(tmp1), 3);
*aliasing_cast<uint32_t>(&data[i[ 8]]) = _mm_cvtsi128_si32(hi128(tmp0));
*aliasing_cast<uint32_t>(&data[i[ 9]]) = _mm_extract_epi32(hi128(tmp0), 1);
*aliasing_cast<uint32_t>(&data[i[10]]) = _mm_extract_epi32(hi128(tmp0), 2);
*aliasing_cast<uint32_t>(&data[i[11]]) = _mm_extract_epi32(hi128(tmp0), 3);
*aliasing_cast<uint32_t>(&data[i[12]]) = _mm_cvtsi128_si32(hi128(tmp1));
*aliasing_cast<uint32_t>(&data[i[13]]) = _mm_extract_epi32(hi128(tmp1), 1);
*aliasing_cast<uint32_t>(&data[i[14]]) = _mm_extract_epi32(hi128(tmp1), 2);
*aliasing_cast<uint32_t>(&data[i[15]]) = _mm_extract_epi32(hi128(tmp1), 3);
}
static inline void interleave(typename V::EntryType *const data, const Common::SuccessiveEntries<2> &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
const __m256i tmp0 = AVX::unpacklo_epi16(v0.data(), v1.data());
const __m256i tmp1 = AVX::unpackhi_epi16(v0.data(), v1.data());
V(Mem::shuffle128<X0, Y0>(tmp0, tmp1)).store(&data[i[0]], Vc::Unaligned);
V(Mem::shuffle128<X1, Y1>(tmp0, tmp1)).store(&data[i[8]], Vc::Unaligned);
}
template<typename I> static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1, const typename V::AsArg v2)
{
interleave(data, i, v0, v1);
v2.scatter(data + 2, i);
}
template<typename I> static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
const __m256i tmp0 = AVX::unpacklo_epi16(v0.data(), v2.data());
const __m256i tmp1 = AVX::unpackhi_epi16(v0.data(), v2.data());
const __m256i tmp2 = AVX::unpacklo_epi16(v1.data(), v3.data());
const __m256i tmp3 = AVX::unpackhi_epi16(v1.data(), v3.data());
const __m256i tmp4 = AVX::unpacklo_epi16(tmp0, tmp2);
const __m256i tmp5 = AVX::unpackhi_epi16(tmp0, tmp2);
const __m256i tmp6 = AVX::unpacklo_epi16(tmp1, tmp3);
const __m256i tmp7 = AVX::unpackhi_epi16(tmp1, tmp3);
using namespace AVX;
auto &&store = [&](__m256i x, int offset) {
_mm_storel_epi64(reinterpret_cast<__m128i *>(&data[i[offset + 0]]), lo128(x));
_mm_storel_epi64(reinterpret_cast<__m128i *>(&data[i[offset + 8]]), hi128(x));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[offset + 1]]), avx_cast<__m128>(x));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[offset + 9]]), avx_cast<__m128>(hi128(x)));
};
store(tmp4, 0);
store(tmp5, 2);
store(tmp6, 4);
store(tmp7, 6);
}
static inline void interleave(typename V::EntryType *const data, const Common::SuccessiveEntries<4> &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
const __m256i tmp0 = AVX::unpacklo_epi16(v0.data(), v2.data());
const __m256i tmp1 = AVX::unpackhi_epi16(v0.data(), v2.data());
const __m256i tmp2 = AVX::unpacklo_epi16(v1.data(), v3.data());
const __m256i tmp3 = AVX::unpackhi_epi16(v1.data(), v3.data());
const __m256i tmp4 = AVX::unpacklo_epi16(tmp0, tmp2);
const __m256i tmp5 = AVX::unpackhi_epi16(tmp0, tmp2);
const __m256i tmp6 = AVX::unpacklo_epi16(tmp1, tmp3);
const __m256i tmp7 = AVX::unpackhi_epi16(tmp1, tmp3);
V(Mem::shuffle128<X0, Y0>(tmp4, tmp5)).store(&data[i[0]], ::Vc::Unaligned);
V(Mem::shuffle128<X0, Y0>(tmp6, tmp7)).store(&data[i[4]], ::Vc::Unaligned);
V(Mem::shuffle128<X1, Y1>(tmp4, tmp5)).store(&data[i[8]], ::Vc::Unaligned);
V(Mem::shuffle128<X1, Y1>(tmp6, tmp7)).store(&data[i[12]], ::Vc::Unaligned);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4)
{
interleave(data, i, v0, v1, v2, v3);
v4.scatter(data + 4, i);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6, const typename V::AsArg v7)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6, v7);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1)
{
const __m256i tmp4 =
_mm256_setr_epi32(
*aliasing_cast<int>(&data[i[0]]), *aliasing_cast<int>(&data[i[1]]),
*aliasing_cast<int>(&data[i[2]]), *aliasing_cast<int>(&data[i[3]]),
*aliasing_cast<int>(&data[i[8]]), *aliasing_cast<int>(&data[i[9]]),
*aliasing_cast<int>(&data[i[10]]), *aliasing_cast<int>(&data[i[11]]));
const __m256i tmp5 =
_mm256_setr_epi32(
*aliasing_cast<int>(&data[i[4]]), *aliasing_cast<int>(&data[i[5]]),
*aliasing_cast<int>(&data[i[6]]), *aliasing_cast<int>(&data[i[7]]),
*aliasing_cast<int>(&data[i[12]]), *aliasing_cast<int>(&data[i[13]]),
*aliasing_cast<int>(&data[i[14]]), *aliasing_cast<int>(&data[i[15]]));
const __m256i tmp2 = AVX::unpacklo_epi16(tmp4, tmp5);
const __m256i tmp3 = AVX::unpackhi_epi16(tmp4, tmp5);
const __m256i tmp0 = AVX::unpacklo_epi16(tmp2, tmp3);
const __m256i tmp1 = AVX::unpackhi_epi16(tmp2, tmp3);
v0.data() = AVX::unpacklo_epi16(tmp0, tmp1);
v1.data() = AVX::unpackhi_epi16(tmp0, tmp1);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2)
{
using namespace AVX;
const __m256i tmp0 = avx_cast<__m256i>(_mm256_setr_pd(
*aliasing_cast<double>(&data[i[0]]), *aliasing_cast<double>(&data[i[1]]),
*aliasing_cast<double>(&data[i[8]]), *aliasing_cast<double>(&data[i[9]])));
const __m256i tmp1 = avx_cast<__m256i>(_mm256_setr_pd(
*aliasing_cast<double>(&data[i[2]]), *aliasing_cast<double>(&data[i[3]]),
*aliasing_cast<double>(&data[i[10]]), *aliasing_cast<double>(&data[i[11]])));
const __m256i tmp2 = avx_cast<__m256i>(_mm256_setr_pd(
*aliasing_cast<double>(&data[i[4]]), *aliasing_cast<double>(&data[i[5]]),
*aliasing_cast<double>(&data[i[12]]), *aliasing_cast<double>(&data[i[13]])));
const __m256i tmp3 = avx_cast<__m256i>(_mm256_setr_pd(
*aliasing_cast<double>(&data[i[6]]), *aliasing_cast<double>(&data[i[7]]),
*aliasing_cast<double>(&data[i[14]]), *aliasing_cast<double>(&data[i[15]])));
const __m256i tmp4 = AVX::unpacklo_epi16(tmp0, tmp2);
const __m256i tmp5 = AVX::unpackhi_epi16(tmp0, tmp2);
const __m256i tmp6 = AVX::unpacklo_epi16(tmp1, tmp3);
const __m256i tmp7 = AVX::unpackhi_epi16(tmp1, tmp3);
const __m256i tmp8 = AVX::unpacklo_epi16(tmp4, tmp6);
const __m256i tmp9 = AVX::unpackhi_epi16(tmp4, tmp6);
const __m256i tmp10 = AVX::unpacklo_epi16(tmp5, tmp7);
const __m256i tmp11 = AVX::unpackhi_epi16(tmp5, tmp7);
v0.data() = AVX::unpacklo_epi16(tmp8, tmp10);
v1.data() = AVX::unpackhi_epi16(tmp8, tmp10);
v2.data() = AVX::unpacklo_epi16(tmp9, tmp11);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3)
{
using namespace AVX;
const __m256i tmp0 = avx_cast<__m256i>(_mm256_setr_pd(
*aliasing_cast<double>(&data[i[0]]), *aliasing_cast<double>(&data[i[1]]),
*aliasing_cast<double>(&data[i[8]]), *aliasing_cast<double>(&data[i[9]])));
const __m256i tmp1 = avx_cast<__m256i>(_mm256_setr_pd(
*aliasing_cast<double>(&data[i[2]]), *aliasing_cast<double>(&data[i[3]]),
*aliasing_cast<double>(&data[i[10]]), *aliasing_cast<double>(&data[i[11]])));
const __m256i tmp2 = avx_cast<__m256i>(_mm256_setr_pd(
*aliasing_cast<double>(&data[i[4]]), *aliasing_cast<double>(&data[i[5]]),
*aliasing_cast<double>(&data[i[12]]), *aliasing_cast<double>(&data[i[13]])));
const __m256i tmp3 = avx_cast<__m256i>(_mm256_setr_pd(
*aliasing_cast<double>(&data[i[6]]), *aliasing_cast<double>(&data[i[7]]),
*aliasing_cast<double>(&data[i[14]]), *aliasing_cast<double>(&data[i[15]])));
const __m256i tmp4 = AVX::unpacklo_epi16(tmp0, tmp2);
const __m256i tmp5 = AVX::unpackhi_epi16(tmp0, tmp2);
const __m256i tmp6 = AVX::unpacklo_epi16(tmp1, tmp3);
const __m256i tmp7 = AVX::unpackhi_epi16(tmp1, tmp3);
const __m256i tmp8 = AVX::unpacklo_epi16(tmp4, tmp6);
const __m256i tmp9 = AVX::unpackhi_epi16(tmp4, tmp6);
const __m256i tmp10 = AVX::unpacklo_epi16(tmp5, tmp7);
const __m256i tmp11 = AVX::unpackhi_epi16(tmp5, tmp7);
v0.data() = AVX::unpacklo_epi16(tmp8, tmp10);
v1.data() = AVX::unpackhi_epi16(tmp8, tmp10);
v2.data() = AVX::unpacklo_epi16(tmp9, tmp11);
v3.data() = AVX::unpackhi_epi16(tmp9, tmp11);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4)
{
using namespace AVX;
const __m256i a = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[0]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[8]])));
const __m256i b = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[1]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[9]])));
const __m256i c = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[2]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[10]])));
const __m256i d = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[3]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[11]])));
const __m256i e = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[4]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[12]])));
const __m256i f = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[5]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[13]])));
const __m256i g = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[6]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[14]])));
const __m256i h = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[7]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[15]])));
const __m256i tmp2 = AVX::unpacklo_epi16(a, e);
const __m256i tmp4 = AVX::unpacklo_epi16(b, f);
const __m256i tmp3 = AVX::unpacklo_epi16(c, g);
const __m256i tmp5 = AVX::unpacklo_epi16(d, h);
const __m256i tmp10 = AVX::unpackhi_epi16(a, e);
const __m256i tmp11 = AVX::unpackhi_epi16(c, g);
const __m256i tmp12 = AVX::unpackhi_epi16(b, f);
const __m256i tmp13 = AVX::unpackhi_epi16(d, h);
const __m256i tmp0 = AVX::unpacklo_epi16(tmp2, tmp3);
const __m256i tmp1 = AVX::unpacklo_epi16(tmp4, tmp5);
const __m256i tmp6 = AVX::unpackhi_epi16(tmp2, tmp3);
const __m256i tmp7 = AVX::unpackhi_epi16(tmp4, tmp5);
const __m256i tmp8 = AVX::unpacklo_epi16(tmp10, tmp11);
const __m256i tmp9 = AVX::unpacklo_epi16(tmp12, tmp13);
v0.data() = AVX::unpacklo_epi16(tmp0, tmp1);
v1.data() = AVX::unpackhi_epi16(tmp0, tmp1);
v2.data() = AVX::unpacklo_epi16(tmp6, tmp7);
v3.data() = AVX::unpackhi_epi16(tmp6, tmp7);
v4.data() = AVX::unpacklo_epi16(tmp8, tmp9);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5)
{
using namespace AVX;
const __m256i a = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[0]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[8]])));
const __m256i b = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[1]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[9]])));
const __m256i c = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[2]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[10]])));
const __m256i d = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[3]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[11]])));
const __m256i e = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[4]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[12]])));
const __m256i f = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[5]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[13]])));
const __m256i g = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[6]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[14]])));
const __m256i h = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[7]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[15]])));
const __m256i tmp2 = AVX::unpacklo_epi16(a, e);
const __m256i tmp4 = AVX::unpacklo_epi16(b, f);
const __m256i tmp3 = AVX::unpacklo_epi16(c, g);
const __m256i tmp5 = AVX::unpacklo_epi16(d, h);
const __m256i tmp10 = AVX::unpackhi_epi16(a, e);
const __m256i tmp11 = AVX::unpackhi_epi16(c, g);
const __m256i tmp12 = AVX::unpackhi_epi16(b, f);
const __m256i tmp13 = AVX::unpackhi_epi16(d, h);
const __m256i tmp0 = AVX::unpacklo_epi16(tmp2, tmp3);
const __m256i tmp1 = AVX::unpacklo_epi16(tmp4, tmp5);
const __m256i tmp6 = AVX::unpackhi_epi16(tmp2, tmp3);
const __m256i tmp7 = AVX::unpackhi_epi16(tmp4, tmp5);
const __m256i tmp8 = AVX::unpacklo_epi16(tmp10, tmp11);
const __m256i tmp9 = AVX::unpacklo_epi16(tmp12, tmp13);
v0.data() = AVX::unpacklo_epi16(tmp0, tmp1);
v1.data() = AVX::unpackhi_epi16(tmp0, tmp1);
v2.data() = AVX::unpacklo_epi16(tmp6, tmp7);
v3.data() = AVX::unpackhi_epi16(tmp6, tmp7);
v4.data() = AVX::unpacklo_epi16(tmp8, tmp9);
v5.data() = AVX::unpackhi_epi16(tmp8, tmp9);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6)
{
using namespace AVX;
const __m256i a = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[0]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[8]])));
const __m256i b = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[1]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[9]])));
const __m256i c = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[2]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[10]])));
const __m256i d = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[3]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[11]])));
const __m256i e = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[4]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[12]])));
const __m256i f = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[5]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[13]])));
const __m256i g = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[6]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[14]])));
const __m256i h = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[7]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[15]])));
const __m256i tmp2 = AVX::unpacklo_epi16(a, e);
const __m256i tmp4 = AVX::unpacklo_epi16(b, f);
const __m256i tmp3 = AVX::unpacklo_epi16(c, g);
const __m256i tmp5 = AVX::unpacklo_epi16(d, h);
const __m256i tmp10 = AVX::unpackhi_epi16(a, e);
const __m256i tmp11 = AVX::unpackhi_epi16(c, g);
const __m256i tmp12 = AVX::unpackhi_epi16(b, f);
const __m256i tmp13 = AVX::unpackhi_epi16(d, h);
const __m256i tmp0 = AVX::unpacklo_epi16(tmp2, tmp3);
const __m256i tmp1 = AVX::unpacklo_epi16(tmp4, tmp5);
const __m256i tmp6 = AVX::unpackhi_epi16(tmp2, tmp3);
const __m256i tmp7 = AVX::unpackhi_epi16(tmp4, tmp5);
const __m256i tmp8 = AVX::unpacklo_epi16(tmp10, tmp11);
const __m256i tmp9 = AVX::unpacklo_epi16(tmp12, tmp13);
const __m256i tmp14 = AVX::unpackhi_epi16(tmp10, tmp11);
const __m256i tmp15 = AVX::unpackhi_epi16(tmp12, tmp13);
v0.data() = AVX::unpacklo_epi16(tmp0, tmp1);
v1.data() = AVX::unpackhi_epi16(tmp0, tmp1);
v2.data() = AVX::unpacklo_epi16(tmp6, tmp7);
v3.data() = AVX::unpackhi_epi16(tmp6, tmp7);
v4.data() = AVX::unpacklo_epi16(tmp8, tmp9);
v5.data() = AVX::unpackhi_epi16(tmp8, tmp9);
v6.data() = AVX::unpacklo_epi16(tmp14, tmp15);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6, V &v7)
{
using namespace AVX;
const __m256i a = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[0]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[8]])));
const __m256i b = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[1]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[9]])));
const __m256i c = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[2]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[10]])));
const __m256i d = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[3]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[11]])));
const __m256i e = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[4]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[12]])));
const __m256i f = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[5]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[13]])));
const __m256i g = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[6]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[14]])));
const __m256i h = concat(_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[7]])),
_mm_loadu_si128(reinterpret_cast<const __m128i *>(&data[i[15]])));
const __m256i tmp2 = AVX::unpacklo_epi16(a, e);
const __m256i tmp4 = AVX::unpacklo_epi16(b, f);
const __m256i tmp3 = AVX::unpacklo_epi16(c, g);
const __m256i tmp5 = AVX::unpacklo_epi16(d, h);
const __m256i tmp10 = AVX::unpackhi_epi16(a, e);
const __m256i tmp11 = AVX::unpackhi_epi16(c, g);
const __m256i tmp12 = AVX::unpackhi_epi16(b, f);
const __m256i tmp13 = AVX::unpackhi_epi16(d, h);
const __m256i tmp0 = AVX::unpacklo_epi16(tmp2, tmp3);
const __m256i tmp1 = AVX::unpacklo_epi16(tmp4, tmp5);
const __m256i tmp6 = AVX::unpackhi_epi16(tmp2, tmp3);
const __m256i tmp7 = AVX::unpackhi_epi16(tmp4, tmp5);
const __m256i tmp8 = AVX::unpacklo_epi16(tmp10, tmp11);
const __m256i tmp9 = AVX::unpacklo_epi16(tmp12, tmp13);
const __m256i tmp14 = AVX::unpackhi_epi16(tmp10, tmp11);
const __m256i tmp15 = AVX::unpackhi_epi16(tmp12, tmp13);
v0.data() = AVX::unpacklo_epi16(tmp0, tmp1);
v1.data() = AVX::unpackhi_epi16(tmp0, tmp1);
v2.data() = AVX::unpacklo_epi16(tmp6, tmp7);
v3.data() = AVX::unpackhi_epi16(tmp6, tmp7);
v4.data() = AVX::unpacklo_epi16(tmp8, tmp9);
v5.data() = AVX::unpackhi_epi16(tmp8, tmp9);
v6.data() = AVX::unpacklo_epi16(tmp14, tmp15);
v7.data() = AVX::unpackhi_epi16(tmp14, tmp15);
}
};
template<typename V> struct InterleaveImpl<V, 8, 32> {
static_assert(sizeof(typename V::value_type) == 4, "");
template<typename I> static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
using namespace AVX;
const m256 tmp0 = _mm256_unpacklo_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v1.data()));
const m256 tmp1 = _mm256_unpackhi_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v1.data()));
_mm_storel_pi(reinterpret_cast<__m64 *>(&data[i[0]]), lo128(tmp0));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[1]]), lo128(tmp0));
_mm_storel_pi(reinterpret_cast<__m64 *>(&data[i[2]]), lo128(tmp1));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[3]]), lo128(tmp1));
_mm_storel_pi(reinterpret_cast<__m64 *>(&data[i[4]]), hi128(tmp0));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[5]]), hi128(tmp0));
_mm_storel_pi(reinterpret_cast<__m64 *>(&data[i[6]]), hi128(tmp1));
_mm_storeh_pi(reinterpret_cast<__m64 *>(&data[i[7]]), hi128(tmp1));
}
static inline void interleave(typename V::EntryType *const data, const Common::SuccessiveEntries<2> &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
using namespace AVX;
const m256 tmp0 = _mm256_unpacklo_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v1.data()));
const m256 tmp1 = _mm256_unpackhi_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v1.data()));
_mm_storeu_ps(aliasing_cast<float>(&data[i[0]]), lo128(tmp0));
_mm_storeu_ps(aliasing_cast<float>(&data[i[2]]), lo128(tmp1));
_mm_storeu_ps(aliasing_cast<float>(&data[i[4]]), hi128(tmp0));
_mm_storeu_ps(aliasing_cast<float>(&data[i[6]]), hi128(tmp1));
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2)
{
using namespace AVX;
#ifdef Vc_USE_MASKMOV_SCATTER
const m256 tmp0 = _mm256_unpacklo_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v2.data()));
const m256 tmp1 = _mm256_unpackhi_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v2.data()));
const m256 tmp2 = _mm256_unpacklo_ps(avx_cast<m256>(v1.data()), avx_cast<m256>(v1.data()));
const m256 tmp3 = _mm256_unpackhi_ps(avx_cast<m256>(v1.data()), avx_cast<m256>(v1.data()));
const m256 tmp4 = _mm256_unpacklo_ps(tmp0, tmp2);
const m256 tmp5 = _mm256_unpackhi_ps(tmp0, tmp2);
const m256 tmp6 = _mm256_unpacklo_ps(tmp1, tmp3);
const m256 tmp7 = _mm256_unpackhi_ps(tmp1, tmp3);
const m128i mask = _mm_set_epi32(0, -1, -1, -1);
_mm_maskstore_ps(aliasing_cast<float>(&data[i[0]]), mask, lo128(tmp4));
_mm_maskstore_ps(aliasing_cast<float>(&data[i[1]]), mask, lo128(tmp5));
_mm_maskstore_ps(aliasing_cast<float>(&data[i[2]]), mask, lo128(tmp6));
_mm_maskstore_ps(aliasing_cast<float>(&data[i[3]]), mask, lo128(tmp7));
_mm_maskstore_ps(aliasing_cast<float>(&data[i[4]]), mask, hi128(tmp4));
_mm_maskstore_ps(aliasing_cast<float>(&data[i[5]]), mask, hi128(tmp5));
_mm_maskstore_ps(aliasing_cast<float>(&data[i[6]]), mask, hi128(tmp6));
_mm_maskstore_ps(aliasing_cast<float>(&data[i[7]]), mask, hi128(tmp7));
#else
interleave(data, i, v0, v1);
v2.scatter(data + 2, i);
#endif
}
static inline void interleave(typename V::EntryType *const data,
const Common::SuccessiveEntries<3> &i,
const typename V::AsArg v0_,
const typename V::AsArg v1_,
const typename V::AsArg v2_)
{
__m256 v0 = AVX::avx_cast<__m256>(v0_.data());
__m256 v1 = AVX::avx_cast<__m256>(v1_.data());
__m256 v2 = AVX::avx_cast<__m256>(v2_.data());
v0 = _mm256_shuffle_ps(v0, v0, 0x6c);
v1 = _mm256_shuffle_ps(v1, v1, 0xb1);
v2 = _mm256_shuffle_ps(v2, v2, 0xc6);
__m256 w0 = Mem::blend<X0, X1, Y2, X3, Y4, X5, X6, Y7>(
Mem::blend<X0, Y1, X2, X3, X4, X5, Y6, X7>(v0, v1), v2);
__m256 w1 = Mem::blend<X0, Y1, X2, X3, X4, Y5, X6, X7>(
Mem::blend<Y0, X1, X2, Y3, Y4, X5, X6, Y7>(v0, v1), v2);
__m256 w2 = Mem::blend<Y0, X1, X2, Y3, X4, X5, Y6, X7>(
Mem::blend<X0, X1, Y2, X3, X4, Y5, X6, X7>(v0, v1), v2);
_mm256_storeu_ps(aliasing_cast<float>(&data[i[0]]),
_mm256_permute2f128_ps(w0, w1, 0x20));
_mm256_storeu_ps(aliasing_cast<float>(&data[i[0]] + 8), w2);
_mm256_storeu_ps(aliasing_cast<float>(&data[i[0]] + 16),
_mm256_permute2f128_ps(w1, w0, 0x31));
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
using namespace AVX;
const __m256 tmp0 =
_mm256_unpacklo_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v2.data()));
const __m256 tmp1 =
_mm256_unpackhi_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v2.data()));
const __m256 tmp2 =
_mm256_unpacklo_ps(avx_cast<m256>(v1.data()), avx_cast<m256>(v3.data()));
const __m256 tmp3 =
_mm256_unpackhi_ps(avx_cast<m256>(v1.data()), avx_cast<m256>(v3.data()));
const __m256 _04 = _mm256_unpacklo_ps(tmp0, tmp2);
const __m256 _15 = _mm256_unpackhi_ps(tmp0, tmp2);
const __m256 _26 = _mm256_unpacklo_ps(tmp1, tmp3);
const __m256 _37 = _mm256_unpackhi_ps(tmp1, tmp3);
_mm_storeu_ps(aliasing_cast<float>(&data[i[0]]), lo128(_04));
_mm_storeu_ps(aliasing_cast<float>(&data[i[1]]), lo128(_15));
_mm_storeu_ps(aliasing_cast<float>(&data[i[2]]), lo128(_26));
_mm_storeu_ps(aliasing_cast<float>(&data[i[3]]), lo128(_37));
_mm_storeu_ps(aliasing_cast<float>(&data[i[4]]), hi128(_04));
_mm_storeu_ps(aliasing_cast<float>(&data[i[5]]), hi128(_15));
_mm_storeu_ps(aliasing_cast<float>(&data[i[6]]), hi128(_26));
_mm_storeu_ps(aliasing_cast<float>(&data[i[7]]), hi128(_37));
}
static inline void interleave(typename V::EntryType *const data,
const Common::SuccessiveEntries<4> &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
using namespace AVX;
const __m256 tmp0 =
_mm256_unpacklo_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v2.data()));
const __m256 tmp1 =
_mm256_unpackhi_ps(avx_cast<m256>(v0.data()), avx_cast<m256>(v2.data()));
const __m256 tmp2 =
_mm256_unpacklo_ps(avx_cast<m256>(v1.data()), avx_cast<m256>(v3.data()));
const __m256 tmp3 =
_mm256_unpackhi_ps(avx_cast<m256>(v1.data()), avx_cast<m256>(v3.data()));
const __m256 _04 = _mm256_unpacklo_ps(tmp0, tmp2);
const __m256 _15 = _mm256_unpackhi_ps(tmp0, tmp2);
const __m256 _26 = _mm256_unpacklo_ps(tmp1, tmp3);
const __m256 _37 = _mm256_unpackhi_ps(tmp1, tmp3);
_mm256_storeu_ps(aliasing_cast<float>(&data[i[0]]),
_mm256_permute2f128_ps(_04, _15, 0x20));
_mm256_storeu_ps(aliasing_cast<float>(&data[i[0]] + 8),
_mm256_permute2f128_ps(_26, _37, 0x20));
_mm256_storeu_ps(aliasing_cast<float>(&data[i[0]] + 16),
_mm256_permute2f128_ps(_04, _15, 0x31));
_mm256_storeu_ps(aliasing_cast<float>(&data[i[0]] + 24),
_mm256_permute2f128_ps(_26, _37, 0x31));
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4)
{
interleave(data, i, v0, v1, v2, v3);
v4.scatter(data + 4, i);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6, const typename V::AsArg v7)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6, v7);
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1)
{
using namespace AVX;
const m128 il0 = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<__m64 const *>(&data[i[0]]));
const m128 il2 = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<__m64 const *>(&data[i[2]]));
const m128 il4 = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<__m64 const *>(&data[i[4]]));
const m128 il6 = _mm_loadl_pi(_mm_setzero_ps(), reinterpret_cast<__m64 const *>(&data[i[6]]));
const m128 il01 = _mm_loadh_pi( il0, reinterpret_cast<__m64 const *>(&data[i[1]]));
const m128 il23 = _mm_loadh_pi( il2, reinterpret_cast<__m64 const *>(&data[i[3]]));
const m128 il45 = _mm_loadh_pi( il4, reinterpret_cast<__m64 const *>(&data[i[5]]));
const m128 il67 = _mm_loadh_pi( il6, reinterpret_cast<__m64 const *>(&data[i[7]]));
const m256 tmp2 = concat(il01, il45);
const m256 tmp3 = concat(il23, il67);
const m256 tmp0 = _mm256_unpacklo_ps(tmp2, tmp3);
const m256 tmp1 = _mm256_unpackhi_ps(tmp2, tmp3);
v0.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(tmp0, tmp1));
v1.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(tmp0, tmp1));
}
static inline void deinterleave(typename V::EntryType const *const data,
const Common::SuccessiveEntries<2> &i, V &v0, V &v1)
{
using namespace AVX;
const m256 il0123 = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0]]));
const m256 il4567 = _mm256_loadu_ps(aliasing_cast<float>(&data[i[4]]));
const m256 tmp2 = Mem::shuffle128<X0, Y0>(il0123, il4567);
const m256 tmp3 = Mem::shuffle128<X1, Y1>(il0123, il4567);
const m256 tmp0 = _mm256_unpacklo_ps(tmp2, tmp3);
const m256 tmp1 = _mm256_unpackhi_ps(tmp2, tmp3);
v0.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(tmp0, tmp1));
v1.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(tmp0, tmp1));
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1, V &v2)
{
using namespace AVX;
const m128 il0 = _mm_loadu_ps(aliasing_cast<float>(&data[i[0]]));
const m128 il1 = _mm_loadu_ps(aliasing_cast<float>(&data[i[1]]));
const m128 il2 = _mm_loadu_ps(aliasing_cast<float>(&data[i[2]]));
const m128 il3 = _mm_loadu_ps(aliasing_cast<float>(&data[i[3]]));
const m128 il4 = _mm_loadu_ps(aliasing_cast<float>(&data[i[4]]));
const m128 il5 = _mm_loadu_ps(aliasing_cast<float>(&data[i[5]]));
const m128 il6 = _mm_loadu_ps(aliasing_cast<float>(&data[i[6]]));
const m128 il7 = _mm_loadu_ps(aliasing_cast<float>(&data[i[7]]));
const m256 il04 = concat(il0, il4);
const m256 il15 = concat(il1, il5);
const m256 il26 = concat(il2, il6);
const m256 il37 = concat(il3, il7);
const m256 ab0246 = _mm256_unpacklo_ps(il04, il26);
const m256 ab1357 = _mm256_unpacklo_ps(il15, il37);
const m256 cd0246 = _mm256_unpackhi_ps(il04, il26);
const m256 cd1357 = _mm256_unpackhi_ps(il15, il37);
v0.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(ab0246, ab1357));
v1.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(ab0246, ab1357));
v2.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(cd0246, cd1357));
}
static inline void deinterleave(typename V::EntryType const *const data,
const Common::SuccessiveEntries<3> &i, V &v0, V &v1,
V &v2)
{
__m256 in0 = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0]] + 0));
__m256 in1 = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0]] + 8));
__m256 in2 = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0]] + 16));
const __m256 aaabffgg = _mm256_permute2f128_ps(in0, in2, 0x20);
const __m256 cdddeeef = in1;
const __m256 bbccghhh = _mm256_permute2f128_ps(in0, in2, 0x31);
const __m256 x0 = _mm256_blend_ps(
_mm256_blend_ps(aaabffgg, cdddeeef, 0 + 2 + 0 + 0 + 0x10 + 0 + 0 + 0x80),
bbccghhh, 0 + 0 + 4 + 0 + 0 + 0x20 + 0 + 0);
const __m256 x1 = _mm256_blend_ps(
_mm256_blend_ps(aaabffgg, cdddeeef, 0 + 0 + 4 + 0 + 0 + 0x20 + 0 + 0),
bbccghhh, 1 + 0 + 0 + 8 + 0 + 0 + 0x40 + 0);
const __m256 x2 = _mm256_blend_ps(
_mm256_blend_ps(aaabffgg, cdddeeef, 1 + 0 + 0 + 8 + 0 + 0 + 0x40 + 0),
bbccghhh, 0 + 2 + 0 + 0 + 0x10 + 0 + 0 + 0x80);
v0 = AVX::avx_cast<typename V::VectorType>(_mm256_shuffle_ps(x0, x0, 0x6c));
v1 = AVX::avx_cast<typename V::VectorType>(_mm256_shuffle_ps(x1, x1, 0xb1));
v2 = AVX::avx_cast<typename V::VectorType>(_mm256_shuffle_ps(x2, x2, 0xc6));
}
template <typename I>
static inline void deinterleave(typename V::EntryType const *const data, const I &i,
V &v0, V &v1, V &v2, V &v3)
{
using namespace AVX;
const m128 il0 = _mm_loadu_ps(aliasing_cast<float>(&data[i[0]]));
const m128 il1 = _mm_loadu_ps(aliasing_cast<float>(&data[i[1]]));
const m128 il2 = _mm_loadu_ps(aliasing_cast<float>(&data[i[2]]));
const m128 il3 = _mm_loadu_ps(aliasing_cast<float>(&data[i[3]]));
const m128 il4 = _mm_loadu_ps(aliasing_cast<float>(&data[i[4]]));
const m128 il5 = _mm_loadu_ps(aliasing_cast<float>(&data[i[5]]));
const m128 il6 = _mm_loadu_ps(aliasing_cast<float>(&data[i[6]]));
const m128 il7 = _mm_loadu_ps(aliasing_cast<float>(&data[i[7]]));
const m256 il04 = concat(il0, il4);
const m256 il15 = concat(il1, il5);
const m256 il26 = concat(il2, il6);
const m256 il37 = concat(il3, il7);
const m256 ab0246 = _mm256_unpacklo_ps(il04, il26);
const m256 ab1357 = _mm256_unpacklo_ps(il15, il37);
const m256 cd0246 = _mm256_unpackhi_ps(il04, il26);
const m256 cd1357 = _mm256_unpackhi_ps(il15, il37);
v0.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(ab0246, ab1357));
v1.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(ab0246, ab1357));
v2.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(cd0246, cd1357));
v3.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(cd0246, cd1357));
}
static inline void deinterleave(typename V::EntryType const *const data,
const Common::SuccessiveEntries<4> &i, V &v0, V &v1,
V &v2, V &v3)
{
using namespace AVX;
const __m256 il01 = _mm256_loadu_ps(
aliasing_cast<float>(&data[i[0]]));
const __m256 il23 = _mm256_loadu_ps(
aliasing_cast<float>(&data[i[2]]));
const __m256 il45 = _mm256_loadu_ps(
aliasing_cast<float>(&data[i[4]]));
const __m256 il67 = _mm256_loadu_ps(
aliasing_cast<float>(&data[i[6]]));
const __m256 il04 = _mm256_permute2f128_ps(il01, il45, 0x20);
const __m256 il15 = _mm256_permute2f128_ps(il01, il45, 0x31);
const __m256 il26 = _mm256_permute2f128_ps(il23, il67, 0x20);
const __m256 il37 = _mm256_permute2f128_ps(il23, il67, 0x31);
const __m256 ab0246 = _mm256_unpacklo_ps(il04, il26);
const __m256 ab1357 = _mm256_unpacklo_ps(il15, il37);
const __m256 cd0246 = _mm256_unpackhi_ps(il04, il26);
const __m256 cd1357 = _mm256_unpackhi_ps(il15, il37);
v0.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(ab0246, ab1357));
v1.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(ab0246, ab1357));
v2.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(cd0246, cd1357));
v3.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(cd0246, cd1357));
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4)
{
v4.gather(data + 4, i);
deinterleave(data, i, v0, v1, v2, v3);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5);
}
static inline void deinterleave(typename V::EntryType const *const data,
const Common::SuccessiveEntries<6> &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5)
{
using namespace AVX;
const m256 a = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0]]));
const m256 b = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0] + 1 * V::Size]));
const m256 c = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0] + 2 * V::Size]));
const m256 d = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0] + 3 * V::Size]));
const m256 e = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0] + 4 * V::Size]));
const m256 f = _mm256_loadu_ps(aliasing_cast<float>(&data[i[0] + 5 * V::Size]));
const __m256 tmp2 = Mem::shuffle128<X0, Y0>(a, d);
const __m256 tmp3 = Mem::shuffle128<X1, Y1>(b, e);
const __m256 tmp4 = Mem::shuffle128<X1, Y1>(a, d);
const __m256 tmp5 = Mem::shuffle128<X0, Y0>(c, f);
const __m256 tmp8 = Mem::shuffle128<X0, Y0>(b, e);
const __m256 tmp9 = Mem::shuffle128<X1, Y1>(c, f);
const __m256 tmp0 = _mm256_unpacklo_ps(tmp2, tmp3);
const __m256 tmp1 = _mm256_unpackhi_ps(tmp4, tmp5);
const __m256 tmp6 = _mm256_unpackhi_ps(tmp2, tmp3);
const __m256 tmp7 = _mm256_unpacklo_ps(tmp8, tmp9);
const __m256 tmp10 = _mm256_unpacklo_ps(tmp4, tmp5);
const __m256 tmp11 = _mm256_unpackhi_ps(tmp8, tmp9);
v0.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(tmp0, tmp1));
v1.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(tmp0, tmp1));
v2.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(tmp6, tmp7));
v3.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(tmp6, tmp7));
v4.data() = avx_cast<typename V::VectorType>(_mm256_unpacklo_ps(tmp10, tmp11));
v5.data() = avx_cast<typename V::VectorType>(_mm256_unpackhi_ps(tmp10, tmp11));
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5, v6);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6, V &v7)
{
deinterleave(data, i, v0, v1, v2, v3);
deinterleave(data + 4, i, v4, v5, v6, v7);
}
};
template<typename V> struct InterleaveImpl<V, 4, 32> {
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1)
{
using namespace AVX;
const m256d tmp0 = _mm256_unpacklo_pd(v0.data(), v1.data());
const m256d tmp1 = _mm256_unpackhi_pd(v0.data(), v1.data());
_mm_storeu_pd(&data[i[0]], lo128(tmp0));
_mm_storeu_pd(&data[i[1]], lo128(tmp1));
_mm_storeu_pd(&data[i[2]], hi128(tmp0));
_mm_storeu_pd(&data[i[3]], hi128(tmp1));
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2)
{
using namespace AVX;
#ifdef Vc_USE_MASKMOV_SCATTER
const m256d tmp0 = _mm256_unpacklo_pd(v0.data(), v1.data());
const m256d tmp1 = _mm256_unpackhi_pd(v0.data(), v1.data());
const m256d tmp2 = _mm256_unpacklo_pd(v2.data(), v2.data());
const m256d tmp3 = _mm256_unpackhi_pd(v2.data(), v2.data());
#if defined(Vc_MSVC) && (Vc_MSVC < 170000000 || !defined(_WIN64))
const m256i mask = concat(_mm_setallone_si128(), _mm_set_epi32(0, 0, -1, -1));
#else
const m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
#endif
_mm256_maskstore_pd(&data[i[0]], mask, Mem::shuffle128<X0, Y0>(tmp0, tmp2));
_mm256_maskstore_pd(&data[i[1]], mask, Mem::shuffle128<X0, Y0>(tmp1, tmp3));
_mm256_maskstore_pd(&data[i[2]], mask, Mem::shuffle128<X1, Y1>(tmp0, tmp2));
_mm256_maskstore_pd(&data[i[3]], mask, Mem::shuffle128<X1, Y1>(tmp1, tmp3));
#else
interleave(data, i, v0, v1);
v2.scatter(data + 2, i);
#endif
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3)
{
using namespace AVX;
const m256d tmp0 = _mm256_unpacklo_pd(v0.data(), v1.data());
const m256d tmp1 = _mm256_unpackhi_pd(v0.data(), v1.data());
const m256d tmp2 = _mm256_unpacklo_pd(v2.data(), v3.data());
const m256d tmp3 = _mm256_unpackhi_pd(v2.data(), v3.data());
_mm_storeu_pd(&data[i[0] ], lo128(tmp0));
_mm_storeu_pd(&data[i[0]+2], lo128(tmp2));
_mm_storeu_pd(&data[i[1] ], lo128(tmp1));
_mm_storeu_pd(&data[i[1]+2], lo128(tmp3));
_mm_storeu_pd(&data[i[2] ], hi128(tmp0));
_mm_storeu_pd(&data[i[2]+2], hi128(tmp2));
_mm_storeu_pd(&data[i[3] ], hi128(tmp1));
_mm_storeu_pd(&data[i[3]+2], hi128(tmp3));
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4)
{
interleave(data, i, v0, v1, v2, v3);
v4.scatter(data + 4, i);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6);
}
template <typename I>
static inline void interleave(typename V::EntryType *const data, const I &i,
const typename V::AsArg v0, const typename V::AsArg v1,
const typename V::AsArg v2, const typename V::AsArg v3,
const typename V::AsArg v4, const typename V::AsArg v5,
const typename V::AsArg v6, const typename V::AsArg v7)
{
interleave(data, i, v0, v1, v2, v3);
interleave(data + 4, i, v4, v5, v6, v7);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1)
{
using namespace Vc::AVX;
const m256d ab02 = concat(_mm_loadu_pd(&data[i[0]]), _mm_loadu_pd(&data[i[2]]));
const m256d ab13 = concat(_mm_loadu_pd(&data[i[1]]), _mm_loadu_pd(&data[i[3]]));
v0.data() = _mm256_unpacklo_pd(ab02, ab13);
v1.data() = _mm256_unpackhi_pd(ab02, ab13);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2)
{
v2.gather(data + 2, i);
deinterleave(data, i, v0, v1);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3)
{
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4)
{
v4.gather(data + 4, i);
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5)
{
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
deinterleave(data + 4, i, v4, v5);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6)
{
v6.gather(data + 6, i);
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
deinterleave(data + 4, i, v4, v5);
}
template<typename I> static inline void deinterleave(typename V::EntryType const *const data,
const I &i, V &v0, V &v1, V &v2, V &v3, V &v4, V &v5, V &v6, V &v7)
{
deinterleave(data, i, v0, v1);
deinterleave(data + 2, i, v2, v3);
deinterleave(data + 4, i, v4, v5);
deinterleave(data + 6, i, v6, v7);
}
};
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
template <typename T> class Mask<T, VectorAbi::Avx>
{
public:
using abi = VectorAbi::Avx;
typedef bool EntryType;
using value_type = EntryType;
using MaskBool = Common::MaskBool<sizeof(T)>;
using VectorEntryType = MaskBool;
using Vector = AVX2::Vector<T>;
using VectorTypeF = AVX::FloatVectorType<typename AVX::VectorTypeHelper<T>::Type>;
using VectorTypeD = AVX::DoubleVectorType<VectorTypeF>;
using VectorTypeI = AVX::IntegerVectorType<VectorTypeF>;
private:
typedef const VectorTypeF VArg;
typedef const VectorTypeD VdArg;
typedef const VectorTypeI ViArg;
public:
static constexpr size_t Size = sizeof(VectorTypeF) / sizeof(T);
static constexpr size_t MemoryAlignment = Size;
static constexpr std::size_t size() { return Size; }
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(VectorType));
private:
typedef Common::Storage<T, Size> Storage;
public:
using VectorType = typename Storage::VectorType;
using EntryReference = Vc::Detail::ElementReference<Mask>;
using reference = EntryReference;
#if defined Vc_MSVC && defined _WIN32
typedef const Mask &AsArg;
#else
typedef const Mask AsArg;
#endif
Vc_INTRINSIC Mask() {}
Vc_INTRINSIC Mask(VArg x) : d(AVX::avx_cast<VectorType>(x)) {}
Vc_INTRINSIC Mask(VdArg x) : d(AVX::avx_cast<VectorType>(x)) {}
Vc_INTRINSIC Mask(ViArg x) : d(AVX::avx_cast<VectorType>(x)) {}
Vc_INTRINSIC explicit Mask(VectorSpecialInitializerZero) : d(Detail::zero<VectorType>()) {}
Vc_INTRINSIC explicit Mask(VectorSpecialInitializerOne) : d(Detail::allone<VectorType>()) {}
Vc_INTRINSIC explicit Mask(bool b)
: d(b ? Detail::allone<VectorType>() : Detail::zero<VectorType>())
{
}
Vc_INTRINSIC static Mask Zero() { return Mask{Vc::Zero}; }
Vc_INTRINSIC static Mask One() { return Mask{Vc::One}; }
template <typename U>
Vc_INTRINSIC Mask(
U &&rhs, Common::enable_if_mask_converts_implicitly<Mask, T, U> = nullarg)
: d(AVX::avx_cast<VectorType>(
Detail::mask_cast<Traits::decay<U>::Size, Size, VectorTypeF>(
rhs.dataI())))
{
}
#if Vc_IS_VERSION_1
template <typename U>
Vc_DEPRECATED("use simd_cast instead of explicit type casting to convert between "
"mask types") Vc_INTRINSIC
explicit Mask(U &&rhs,
Common::enable_if_mask_converts_explicitly<T, U> = nullarg);
#endif
template<typename Flags = DefaultLoadTag> Vc_INTRINSIC explicit Mask(const bool *mem, Flags f = Flags()) { load(mem, f); }
template<typename Flags = DefaultLoadTag> Vc_INTRINSIC void load(const bool *mem, Flags = Flags());
template<typename Flags = DefaultLoadTag> Vc_INTRINSIC void store(bool *mem, Flags = Flags()) const;
Vc_INTRINSIC Mask &operator=(const Mask &) = default;
Vc_INTRINSIC_L Mask &operator=(const std::array<bool, Size> &values) Vc_INTRINSIC_R;
Vc_INTRINSIC_L operator std::array<bool, Size>() const Vc_INTRINSIC_R;
Vc_INTRINSIC Vc_PURE bool operator==(const Mask &rhs) const
{ return Detail::movemask(d.v()) == Detail::movemask(rhs.d.v()); }
Vc_INTRINSIC Vc_PURE bool operator!=(const Mask &rhs) const
{ return !operator==(rhs); }
Vc_INTRINSIC Mask operator!() const
{
#ifdef Vc_GCC
return ~dataI();
#else
return Detail::andnot_(data(), Detail::allone<VectorTypeF>());
#endif
}
Vc_INTRINSIC Mask &operator&=(const Mask &rhs) { d.v() = AVX::avx_cast<VectorType>(Detail::and_(data(), rhs.data())); return *this; }
Vc_INTRINSIC Mask &operator|=(const Mask &rhs) { d.v() = AVX::avx_cast<VectorType>(Detail::or_ (data(), rhs.data())); return *this; }
Vc_INTRINSIC Mask &operator^=(const Mask &rhs) { d.v() = AVX::avx_cast<VectorType>(Detail::xor_(data(), rhs.data())); return *this; }
Vc_INTRINSIC Vc_PURE Mask operator&(const Mask &rhs) const { return Detail::and_(data(), rhs.data()); }
Vc_INTRINSIC Vc_PURE Mask operator|(const Mask &rhs) const { return Detail::or_(data(), rhs.data()); }
Vc_INTRINSIC Vc_PURE Mask operator^(const Mask &rhs) const { return Detail::xor_(data(), rhs.data()); }
Vc_INTRINSIC Vc_PURE Mask operator&&(const Mask &rhs) const { return Detail::and_(data(), rhs.data()); }
Vc_INTRINSIC Vc_PURE Mask operator||(const Mask &rhs) const { return Detail::or_(data(), rhs.data()); }
Vc_INTRINSIC_L bool isNotEmpty() const Vc_INTRINSIC_R;
Vc_INTRINSIC_L bool isEmpty() const Vc_INTRINSIC_R;
Vc_INTRINSIC_L bool isFull() const Vc_INTRINSIC_R;
Vc_INTRINSIC_L bool isMix() const Vc_INTRINSIC_R;
Vc_INTRINSIC Vc_PURE int shiftMask() const { return Detail::movemask(dataI()); }
Vc_INTRINSIC Vc_PURE int toInt() const { return Detail::mask_to_int<Size>(dataI()); }
Vc_INTRINSIC VectorTypeF data () const { return AVX::avx_cast<VectorTypeF>(d.v()); }
Vc_INTRINSIC VectorTypeI dataI() const { return AVX::avx_cast<VectorTypeI>(d.v()); }
Vc_INTRINSIC VectorTypeD dataD() const { return AVX::avx_cast<VectorTypeD>(d.v()); }
private:
friend reference;
static Vc_INTRINSIC Vc_PURE value_type get(const Mask &m, int i) noexcept
{
return m.toInt() & (1 << i);
}
template <typename U>
static Vc_INTRINSIC void set(Mask &m, int i,
U &&v) noexcept(noexcept(MaskBool(std::declval<U>())))
{
m.d.set(i, MaskBool(std::forward<U>(v)));
}
public:
Vc_ALWAYS_INLINE reference operator[](size_t index) noexcept
{
return {*this, int(index)};
}
Vc_ALWAYS_INLINE Vc_PURE value_type operator[](size_t index) const noexcept
{
return get(*this, index);
}
Vc_INTRINSIC Vc_PURE int count() const { return Detail::popcnt16(toInt()); }
Vc_INTRINSIC Vc_PURE int firstOne() const { return _bit_scan_forward(toInt()); }
template <typename G> static Vc_INTRINSIC_L Mask generate(G &&gen) Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vc_PURE_L Mask shifted(int amount) const Vc_INTRINSIC_R Vc_PURE_R;
private:
#ifdef Vc_COMPILE_BENCHMARKS
public:
#endif
Storage d;
};
template <typename T> constexpr size_t Mask<T, VectorAbi::Avx>::Size;
template <typename T> constexpr size_t Mask<T, VectorAbi::Avx>::MemoryAlignment;
}
namespace Vc_VERSIONED_NAMESPACE
{
template <typename T>
template <typename Flags>
Vc_INTRINSIC void Mask<T, VectorAbi::Avx>::store(bool *mem, Flags f) const
{
Detail::mask_store<Size>(dataI(), mem, f);
}
template <typename T>
template <typename Flags>
Vc_INTRINSIC void Mask<T, VectorAbi::Avx>::load(const bool *mem, Flags f)
{
d.v() = AVX::avx_cast<VectorType>(Detail::mask_load<VectorTypeF, Size>(mem, f));
}
#ifdef Vc_IMPL_AVX2
template <>
Vc_INTRINSIC Vc_PURE bool AVX2::Mask<int16_t>::get(const AVX2::Mask<int16_t> &m,
int index) noexcept
{
return m.shiftMask() & (1 << 2 * index);
}
template <>
Vc_INTRINSIC Vc_PURE bool AVX2::Mask<uint16_t>::get(const AVX2::Mask<uint16_t> &m,
int index) noexcept
{
return m.shiftMask() & (1 << 2 * index);
}
#endif
template <> Vc_INTRINSIC Vc_PURE bool AVX2::double_m::operator==(const AVX2::double_m &rhs) const
{ return Detail::movemask(dataD()) == Detail::movemask(rhs.dataD()); }
#ifdef Vc_IMPL_AVX2
template <> Vc_INTRINSIC Vc_PURE bool AVX2::short_m::operator==(const AVX2::short_m &rhs) const
{ return Detail::movemask(dataI()) == Detail::movemask(rhs.dataI()); }
template <> Vc_INTRINSIC Vc_PURE bool AVX2::ushort_m::operator==(const AVX2::ushort_m &rhs) const
{ return Detail::movemask(dataI()) == Detail::movemask(rhs.dataI()); }
#endif
template <typename T> Vc_INTRINSIC bool Mask<T, VectorAbi::Avx>::isFull() const {
if (sizeof(T) == 8) {
return 0 != Detail::testc(dataD(), Detail::allone<VectorTypeD>());
} else if (sizeof(T) == 4) {
return 0 != Detail::testc(data (), Detail::allone<VectorTypeF>());
} else {
return 0 != Detail::testc(dataI(), Detail::allone<VectorTypeI>());
}
}
template <typename T> Vc_INTRINSIC bool Mask<T, VectorAbi::Avx>::isNotEmpty() const {
if (sizeof(T) == 8) {
return 0 == Detail::testz(dataD(), dataD());
} else if (sizeof(T) == 4) {
return 0 == Detail::testz(data (), data ());
} else {
return 0 == Detail::testz(dataI(), dataI());
}
}
template <typename T> Vc_INTRINSIC bool Mask<T, VectorAbi::Avx>::isEmpty() const {
if (sizeof(T) == 8) {
return 0 != Detail::testz(dataD(), dataD());
} else if (sizeof(T) == 4) {
return 0 != Detail::testz(data (), data ());
} else {
return 0 != Detail::testz(dataI(), dataI());
}
}
template <typename T> Vc_INTRINSIC bool Mask<T, VectorAbi::Avx>::isMix() const {
if (sizeof(T) == 8) {
return 0 != Detail::testnzc(dataD(), Detail::allone<VectorTypeD>());
} else if (sizeof(T) == 4) {
return 0 != Detail::testnzc(data (), Detail::allone<VectorTypeF>());
} else {
return 0 != Detail::testnzc(dataI(), Detail::allone<VectorTypeI>());
}
}
template <typename M, typename G>
Vc_INTRINSIC M generate_impl(G &&gen, std::integral_constant<int, 4 + 32>)
{
return _mm256_setr_epi64x(
gen(0) ? 0xffffffffffffffffull : 0, gen(1) ? 0xffffffffffffffffull : 0,
gen(2) ? 0xffffffffffffffffull : 0, gen(3) ? 0xffffffffffffffffull : 0);
}
template <typename M, typename G>
Vc_INTRINSIC M generate_impl(G &&gen, std::integral_constant<int, 8 + 32>)
{
return _mm256_setr_epi32(gen(0) ? 0xfffffffful : 0, gen(1) ? 0xfffffffful : 0,
gen(2) ? 0xfffffffful : 0, gen(3) ? 0xfffffffful : 0,
gen(4) ? 0xfffffffful : 0, gen(5) ? 0xfffffffful : 0,
gen(6) ? 0xfffffffful : 0, gen(7) ? 0xfffffffful : 0);
}
template <typename M, typename G>
Vc_INTRINSIC M generate_impl(G &&gen, std::integral_constant<int, 16 + 32>)
{
return _mm256_setr_epi16(gen(0) ? 0xfffful : 0, gen(1) ? 0xfffful : 0,
gen(2) ? 0xfffful : 0, gen(3) ? 0xfffful : 0,
gen(4) ? 0xfffful : 0, gen(5) ? 0xfffful : 0,
gen(6) ? 0xfffful : 0, gen(7) ? 0xfffful : 0,
gen(8) ? 0xfffful : 0, gen(9) ? 0xfffful : 0,
gen(10) ? 0xfffful : 0, gen(11) ? 0xfffful : 0,
gen(12) ? 0xfffful : 0, gen(13) ? 0xfffful : 0,
gen(14) ? 0xfffful : 0, gen(15) ? 0xfffful : 0);
}
template <typename T>
template <typename G>
Vc_INTRINSIC AVX2::Mask<T> Mask<T, VectorAbi::Avx>::generate(G &&gen)
{
return generate_impl<AVX2::Mask<T>>(std::forward<G>(gen),
std::integral_constant<int, Size + sizeof(Storage)>());
}
template <typename T> Vc_INTRINSIC Vc_PURE AVX2::Mask<T> Mask<T, VectorAbi::Avx>::shifted(int amount) const
{
switch (amount * int(sizeof(VectorEntryType))) {
case 0: return *this;
case 1: return Detail::shifted< 1>(dataI());
case 2: return Detail::shifted< 2>(dataI());
case 3: return Detail::shifted< 3>(dataI());
case 4: return Detail::shifted< 4>(dataI());
case 5: return Detail::shifted< 5>(dataI());
case 6: return Detail::shifted< 6>(dataI());
case 7: return Detail::shifted< 7>(dataI());
case 8: return Detail::shifted< 8>(dataI());
case 9: return Detail::shifted< 9>(dataI());
case 10: return Detail::shifted< 10>(dataI());
case 11: return Detail::shifted< 11>(dataI());
case 12: return Detail::shifted< 12>(dataI());
case 13: return Detail::shifted< 13>(dataI());
case 14: return Detail::shifted< 14>(dataI());
case 15: return Detail::shifted< 15>(dataI());
case 16: return Detail::shifted< 16>(dataI());
case 17: return Detail::shifted< 17>(dataI());
case 18: return Detail::shifted< 18>(dataI());
case 19: return Detail::shifted< 19>(dataI());
case 20: return Detail::shifted< 20>(dataI());
case 21: return Detail::shifted< 21>(dataI());
case 22: return Detail::shifted< 22>(dataI());
case 23: return Detail::shifted< 23>(dataI());
case 24: return Detail::shifted< 24>(dataI());
case 25: return Detail::shifted< 25>(dataI());
case 26: return Detail::shifted< 26>(dataI());
case 27: return Detail::shifted< 27>(dataI());
case 28: return Detail::shifted< 28>(dataI());
case 29: return Detail::shifted< 29>(dataI());
case 30: return Detail::shifted< 30>(dataI());
case 31: return Detail::shifted< 31>(dataI());
case -1: return Detail::shifted< -1>(dataI());
case -2: return Detail::shifted< -2>(dataI());
case -3: return Detail::shifted< -3>(dataI());
case -4: return Detail::shifted< -4>(dataI());
case -5: return Detail::shifted< -5>(dataI());
case -6: return Detail::shifted< -6>(dataI());
case -7: return Detail::shifted< -7>(dataI());
case -8: return Detail::shifted< -8>(dataI());
case -9: return Detail::shifted< -9>(dataI());
case -10: return Detail::shifted<-10>(dataI());
case -11: return Detail::shifted<-11>(dataI());
case -12: return Detail::shifted<-12>(dataI());
case -13: return Detail::shifted<-13>(dataI());
case -14: return Detail::shifted<-14>(dataI());
case -15: return Detail::shifted<-15>(dataI());
case -16: return Detail::shifted<-16>(dataI());
case -17: return Detail::shifted<-17>(dataI());
case -18: return Detail::shifted<-18>(dataI());
case -19: return Detail::shifted<-19>(dataI());
case -20: return Detail::shifted<-20>(dataI());
case -21: return Detail::shifted<-21>(dataI());
case -22: return Detail::shifted<-22>(dataI());
case -23: return Detail::shifted<-23>(dataI());
case -24: return Detail::shifted<-24>(dataI());
case -25: return Detail::shifted<-25>(dataI());
case -26: return Detail::shifted<-26>(dataI());
case -27: return Detail::shifted<-27>(dataI());
case -28: return Detail::shifted<-28>(dataI());
case -29: return Detail::shifted<-29>(dataI());
case -30: return Detail::shifted<-30>(dataI());
case -31: return Detail::shifted<-31>(dataI());
}
return Zero();
}
}
#endif
#include <algorithm>
#include <cmath>
#ifdef isfinite
#undef isfinite
#endif
#ifdef isnan
#undef isnan
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename T, typename Abi> struct VectorTraits
{
using mask_type = Vc::Mask<T, Abi>;
using vector_type = Vc::Vector<T, Abi>;
using writemasked_vector_type = Common::WriteMaskedVector<vector_type, mask_type>;
using intrinsic_type = typename AVX::VectorTypeHelper<T>::Type;
};
}
#define Vc_CURRENT_CLASS_NAME Vector
template <typename T> class Vector<T, VectorAbi::Avx>
{
public:
using abi = VectorAbi::Avx;
private:
using traits_type = Detail::VectorTraits<T, abi>;
static_assert(
std::is_arithmetic<T>::value,
"Vector<T> only accepts arithmetic builtin types as template parameter T.");
using WriteMaskedVector = typename traits_type::writemasked_vector_type;
public:
using VectorType = typename traits_type::intrinsic_type;
using vector_type = VectorType;
using mask_type = typename traits_type::mask_type;
using Mask = mask_type;
using MaskType = mask_type;
using MaskArg Vc_DEPRECATED_ALIAS("Use MaskArgument instead.") = typename Mask::AsArg;
using MaskArgument = typename Mask::AsArg;
using reference = Detail::ElementReference<Vector>;
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(VectorType));
using EntryType = typename Common::ensure_alignment_equals_sizeof<T>::type;
using value_type = EntryType;
typedef EntryType VectorEntryType;
static constexpr size_t Size = sizeof(VectorType) / sizeof(EntryType);
static constexpr size_t MemoryAlignment = alignof(VectorType);
enum Constants {
HasVectorDivision = AVX::HasVectorDivisionHelper<T>::Value
};
#ifdef Vc_IMPL_AVX2
typedef typename std::conditional<
(Size >= 8), SimdArray<int, Size, AVX2::int_v, 8>,
typename std::conditional<(Size >= 4), SimdArray<int, Size, SSE::int_v, 4>,
SimdArray<int, Size, Scalar::int_v, 1>>::type>::type
IndexType;
#else
typedef typename std::conditional<(Size >= 4),
SimdArray<int, Size, SSE::int_v, 4>,
SimdArray<int, Size, Scalar::int_v, 1>>::type IndexType;
#endif
typedef Vector<T, abi> AsArg;
typedef VectorType VectorTypeArg;
protected:
template <typename U> using V = Vector<U, abi>;
typedef AVX::VectorHelper<VectorType> HV;
typedef AVX::VectorHelper<T> HT;
template <typename V> static Vc_INTRINSIC VectorType _cast(V v)
{
return AVX::avx_cast<VectorType>(v);
}
typedef Common::VectorMemoryUnion<VectorType, EntryType> StorageType;
StorageType d;
using WidthT = Common::WidthT<VectorType>;
public:
public:
Vc_INTRINSIC Vector() = default;
static constexpr std::size_t size() { return Size; }
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerZero) Vc_INTRINSIC_R;
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerOne) Vc_INTRINSIC_R;
explicit Vc_INTRINSIC_L Vector(VectorSpecialInitializerIndexesFromZero) Vc_INTRINSIC_R;
static Vc_INTRINSIC Vc_CONST Vector Zero() { return Vector(Vc::Zero); }
static Vc_INTRINSIC Vc_CONST Vector One() { return Vector(Vc::One); }
static Vc_INTRINSIC Vc_CONST Vector IndexesFromZero()
{
return Vector(Vc::IndexesFromZero);
}
template <class G, class...,
class = typename std::enable_if<std::is_convertible<
decltype(std::declval<G>()(size_t())), value_type>::value>::type>
explicit Vector(G &&g) : Vector(generate(std::forward<G>(g)))
{
}
static Vc_ALWAYS_INLINE_L Vector Random() Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE Vector(VectorTypeArg x) : d(x) {}
template <typename U>
Vc_INTRINSIC Vector(
V<U> x, typename std::enable_if<Traits::is_implicit_cast_allowed<U, T>::value,
void *>::type = nullptr)
: d(AVX::convert<U, T>(x.data()))
{
}
#if Vc_IS_VERSION_1
template <typename U>
Vc_DEPRECATED("use simd_cast instead of explicit type casting to convert between "
"vector types") Vc_INTRINSIC explicit Vector(
V<U> x,
typename std::enable_if<!Traits::is_implicit_cast_allowed<U, T>::value,
void *>::type = nullptr)
: d(Detail::zeroExtendIfNeeded(AVX::convert<U, T>(x.data())))
{
}
template <typename U,
typename = enable_if<Traits::is_simd_vector<U>::value &&
!std::is_same<Vector, Traits::decay<U>>::value>>
Vc_DEPRECATED("use simd_cast instead of explicit type casting to convert between "
"vector types") Vc_INTRINSIC_L
explicit Vector(U &&x) Vc_INTRINSIC_R;
#endif
Vc_INTRINSIC Vector(EntryType a) : d(Detail::avx_broadcast(a)) {}
template <typename U>
Vc_INTRINSIC Vector(U a,
typename std::enable_if<std::is_same<U, int>::value &&
!std::is_same<U, EntryType>::value,
void *>::type = nullptr)
: Vector(static_cast<EntryType>(a))
{
}
explicit Vector(std::initializer_list<EntryType>)
{
static_assert(std::is_same<EntryType, void>::value,
"A SIMD vector object cannot be initialized from an initializer list "
"because the number of entries in the vector is target-dependent.");
}
explicit Vc_INTRINSIC Vector(const EntryType *mem)
{
load(mem);
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const EntryType *mem, Flags flags)
{
load(mem, flags);
}
template <typename U, typename Flags = DefaultLoadTag,
typename = enable_if<
(!std::is_integral<U>::value || !std::is_integral<EntryType>::value ||
sizeof(EntryType) >= sizeof(U)) &&
std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC Vector(const U *x, Flags flags = Flags())
{
load<U, Flags>(x, flags);
}
Vc_INTRINSIC void load(const EntryType *mem)
{
load(mem, DefaultLoadTag());
}
template <typename Flags>
Vc_INTRINSIC enable_if<Traits::is_load_store_flag<Flags>::value, void>
load(const EntryType *mem, Flags flags)
{
load<EntryType, Flags>(mem, flags);
}
private:
template <typename U, typename Flags>
struct load_concept : public std::enable_if<
(!std::is_integral<U>::value || !std::is_integral<EntryType>::value ||
sizeof(EntryType) >= sizeof(U)) &&
std::is_arithmetic<U>::value && Traits::is_load_store_flag<Flags>::value, void>
{};
public:
template <typename U, typename Flags = DefaultLoadTag>
Vc_INTRINSIC_L typename load_concept<U, Flags>::type load(const U *mem, Flags = Flags()) Vc_INTRINSIC_R;
template <
typename U,
typename Flags = DefaultStoreTag,
typename = enable_if<std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC_L void store(U *mem, Flags flags = Flags()) const Vc_INTRINSIC_R;
template <
typename U,
typename Flags = DefaultStoreTag,
typename = enable_if<std::is_arithmetic<U>::value &&Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC_L void Vc_VDECL store(U *mem, MaskType mask, Flags flags = Flags()) const Vc_INTRINSIC_R;
Vc_INTRINSIC void store(EntryType *mem) const
{
store<EntryType, DefaultStoreTag>(mem, DefaultStoreTag());
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC void store(EntryType *mem, Flags flags) const
{
store<EntryType, Flags>(mem, flags);
}
Vc_INTRINSIC void Vc_VDECL store(EntryType *mem, MaskType mask) const
{
store<EntryType, DefaultStoreTag>(mem, mask, DefaultStoreTag());
}
template <typename Flags, typename = enable_if<Traits::is_load_store_flag<Flags>::value>>
Vc_INTRINSIC void Vc_VDECL store(EntryType *mem, MaskType mask, Flags flags) const
{
store<EntryType, Flags>(mem, mask, flags);
}
Vc_INTRINSIC_L void setZero() Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setZero(const Mask &k) Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setZeroInverted(const Mask &k) Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setQnan() Vc_INTRINSIC_R;
Vc_INTRINSIC_L void setQnan(MaskArgument k) Vc_INTRINSIC_R;
#ifndef Vc_CURRENT_CLASS_NAME
#error "incorrect use of common/gatherinterface.h: Vc_CURRENT_CLASS_NAME must be defined to the current class name for declaring constructors."
#endif
private:
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes);
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes, MaskArgument mask);
template <typename IT, typename = enable_if<std::is_pointer<IT>::value ||
Traits::is_simd_vector<IT>::value>>
static Vc_INTRINSIC const IT &adjustIndexParameter(const IT &indexes)
{
return indexes;
}
template <
typename IT,
typename = enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value>>
static Vc_INTRINSIC decltype(std::addressof(std::declval<const IT &>()[0]))
adjustIndexParameter(const IT &i)
{
return std::addressof(i[0]);
}
template <typename IT>
static Vc_INTRINSIC enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
!std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value,
IT>
adjustIndexParameter(const IT &i)
{
return i;
}
public:
#define Vc_ASSERT_GATHER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<MT, EntryType>::value, \
"The memory pointer needs to point to a type that can be converted to the " \
"EntryType of this SIMD vector type."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT, typename IT,
typename = enable_if<Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes,
MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes, MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args)
{
gather(args.address, adjustIndexParameter(args.indexes));
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args, MaskArgument mask)
{
gather(args.address, adjustIndexParameter(args.indexes), mask);
}
#undef Vc_ASSERT_GATHER_PARAMETER_TYPES_
private:
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes) const;
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes, MaskArgument mask) const;
public:
#define Vc_ASSERT_SCATTER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<EntryType, MT>::value, \
"The memory pointer needs to point to a type that the EntryType of this " \
"SIMD vector type can be converted to."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes));
}
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes, MaskArgument mask) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args) const
{
scatter(args.address, args.indexes);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args, MaskArgument mask) const
{
scatter(args.address, args.indexes, mask);
}
#undef Vc_ASSERT_SCATTER_PARAMETER_TYPES_
#if defined Vc_IMPL_AVX2 && !defined Vc_MSVC
Vc_INTRINSIC_L void gatherImplementation(
const EntryType *mem,
typename std::conditional<
Size == 8, AVX2::int_v,
typename std::conditional<Size == 4, SSE::int_v, void *>::type>::type
indexes) Vc_INTRINSIC_R;
template <class MT, class U>
Vc_INTRINSIC
enable_if<std::is_arithmetic<MT>::value && std::is_integral<U>::value &&
(sizeof(MT) >= sizeof(short)),
void>
gatherImplementation(const MT *mem, const SimdArray<U, Size> &indexes)
{
*this = simd_cast<Vector>(SimdArray<MT, Size>(mem, indexes));
}
template <class U>
Vc_INTRINSIC enable_if<std::is_integral<U>::value && sizeof(EntryType) == 2, void>
gatherImplementation(const EntryType *mem, const SimdArray<U, 16> &indexes)
{
const auto lo = simd_cast<AVX2::int_v, 0>(indexes);
const auto hi = simd_cast<AVX2::int_v, 1>(indexes);
*this = simd_cast<Vector>(AVX2::int_v(_mm256_i32gather_epi32(
aliasing_cast<int>(mem), lo.data(), 2)),
AVX2::int_v(_mm256_i32gather_epi32(
aliasing_cast<int>(mem), hi.data(), 2)));
}
template <class U, class V, std::size_t Wt>
Vc_INTRINSIC enable_if<std::is_integral<U>::value && Size == 8, void>
gatherImplementation(const EntryType *mem, const SimdArray<U, 8, V, Wt> &indexes)
{
gatherImplementation(mem, simd_cast<AVX2::int_v>(indexes));
}
template <class U, class V, std::size_t Wt>
Vc_INTRINSIC enable_if<std::is_integral<U>::value && Size == 4, void>
gatherImplementation(const EntryType *mem, const SimdArray<U, 4, V, Wt> &indexes)
{
gatherImplementation(mem, simd_cast<SSE::int_v>(indexes));
}
#endif
Vc_ALWAYS_INLINE Vector &operator++() { data() = Detail::add(data(), Detail::one(T()), T()); return *this; }
Vc_ALWAYS_INLINE Vector &operator--() { data() = Detail::sub(data(), Detail::one(T()), T()); return *this; }
Vc_ALWAYS_INLINE Vector operator++(int) { const Vector r = *this; data() = Detail::add(data(), Detail::one(T()), T()); return r; }
Vc_ALWAYS_INLINE Vector operator--(int) { const Vector r = *this; data() = Detail::sub(data(), Detail::one(T()), T()); return r; }
private:
friend reference;
Vc_INTRINSIC static value_type get(const Vector &o, int i) noexcept
{
return o.d.m(i);
}
template <typename U>
Vc_INTRINSIC static void set(Vector &o, int i, U &&v) noexcept(
noexcept(std::declval<value_type &>() = v))
{
return o.d.set(i, v);
}
public:
Vc_ALWAYS_INLINE reference operator[](size_t index) noexcept
{
static_assert(noexcept(reference{std::declval<Vector &>(), int()}), "");
return {*this, int(index)};
}
Vc_ALWAYS_INLINE value_type operator[](size_t index) const noexcept
{
return d.m(index);
}
Vc_INTRINSIC_L Vc_PURE_L Vector operator[](Permutation::ReversedTag) const Vc_INTRINSIC_R Vc_PURE_R;
Vc_INTRINSIC_L Vc_PURE_L Vector operator[](const IndexType &perm) const Vc_INTRINSIC_R Vc_PURE_R;
Vc_INTRINSIC Vc_PURE Mask operator!() const
{
return *this == Zero();
}
Vc_ALWAYS_INLINE Vector operator~() const
{
#ifndef Vc_ENABLE_FLOAT_BIT_OPERATORS
static_assert(std::is_integral<T>::value,
"bit-complement can only be used with Vectors of integral type");
#endif
return Detail::andnot_(data(), Detail::allone<VectorType>());
}
Vc_ALWAYS_INLINE_L Vc_PURE_L Vector operator-() const Vc_ALWAYS_INLINE_R Vc_PURE_R;
Vc_INTRINSIC Vc_PURE Vector operator+() const { return *this; }
#define Vc_OP_VEC(op) \
Vc_INTRINSIC Vector &operator op##=(AsArg x); \
Vc_INTRINSIC Vc_PURE Vector operator op(AsArg x) const \
{ \
static_assert( \
std::is_integral<T>::value, \
"bitwise-operators can only be used with Vectors of integral type"); \
}
Vc_ALL_SHIFTS(Vc_OP_VEC);
#undef Vc_OP_VEC
Vc_ALWAYS_INLINE_L Vector &operator>>=(int x) Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L Vector &operator<<=(int x) Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L Vector operator>>(int x) const Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L Vector operator<<(int x) const Vc_ALWAYS_INLINE_R;
Vc_DEPRECATED("use isnegative(x) instead") Vc_INTRINSIC Vc_PURE Mask
isNegative() const
{
return Vc::isnegative(*this);
}
Vc_ALWAYS_INLINE void assign( const Vector &v, const Mask &mask ) {
const VectorType k = _cast(mask.data());
data() = Detail::blend(data(), v.data(), k);
}
template <typename V2>
Vc_DEPRECATED("Use simd_cast instead of Vector::staticCast") Vc_ALWAYS_INLINE V2
staticCast() const
{
return V2(*this);
}
template <typename V2>
Vc_DEPRECATED("use reinterpret_components_cast instead") Vc_ALWAYS_INLINE V2
reinterpretCast() const
{
return AVX::avx_cast<typename V2::VectorType>(data());
}
Vc_ALWAYS_INLINE WriteMaskedVector operator()(const Mask &k)
{
return {*this, k};
}
Vc_ALWAYS_INLINE VectorType &data() { return d.v(); }
Vc_ALWAYS_INLINE const VectorType &data() const { return d.v(); }
template<int Index>
Vc_INTRINSIC_L Vector broadcast() const Vc_INTRINSIC_R;
Vc_INTRINSIC_L std::pair<Vector, int> minIndex() const Vc_INTRINSIC_R;
Vc_INTRINSIC_L std::pair<Vector, int> maxIndex() const Vc_INTRINSIC_R;
Vc_ALWAYS_INLINE EntryType min() const { return Detail::min(data(), T()); }
Vc_ALWAYS_INLINE EntryType max() const { return Detail::max(data(), T()); }
Vc_ALWAYS_INLINE EntryType product() const { return Detail::mul(data(), T()); }
Vc_ALWAYS_INLINE EntryType sum() const { return Detail::add(data(), T()); }
Vc_ALWAYS_INLINE_L Vector partialSum() const Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L EntryType min(MaskArgument m) const Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L EntryType max(MaskArgument m) const Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L EntryType product(MaskArgument m) const Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L EntryType sum(MaskArgument m) const Vc_ALWAYS_INLINE_R;
Vc_INTRINSIC_L Vector shifted(int amount, Vector shiftIn) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector shifted(int amount) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector rotated(int amount) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vc_PURE_L Vector reversed() const Vc_INTRINSIC_R Vc_PURE_R;
Vc_ALWAYS_INLINE_L Vc_PURE_L Vector sorted() const Vc_ALWAYS_INLINE_R Vc_PURE_R;
template <typename F> void callWithValuesSorted(F &&f)
{
EntryType value = d.m(0);
f(value);
for (size_t i = 1; i < Size; ++i) {
if (d.m(i) != value) {
value = d.m(i);
f(value);
}
}
}
template <typename F> Vc_INTRINSIC void call(F &&f) const
{
Common::for_all_vector_entries<Size>([&](size_t i) { f(EntryType(d.m(i))); });
}
template <typename F> Vc_INTRINSIC void call(F &&f, const Mask &mask) const
{
for (size_t i : where(mask)) {
f(EntryType(d.m(i)));
}
}
template <typename F> Vc_INTRINSIC Vector apply(F &&f) const
{
Vector r;
Common::for_all_vector_entries<Size>(
[&](size_t i) { r.d.set(i, f(EntryType(d.m(i)))); });
return r;
}
template <typename F> Vc_INTRINSIC Vector apply(F &&f, const Mask &mask) const
{
Vector r(*this);
for (size_t i : where(mask)) {
r.d.set(i, f(EntryType(r.d.m(i))));
}
return r;
}
template<typename IndexT> Vc_INTRINSIC void fill(EntryType (&f)(IndexT)) {
Common::for_all_vector_entries<Size>([&](size_t i) { d.set(i, f(i)); });
}
Vc_INTRINSIC void fill(EntryType (&f)()) {
Common::for_all_vector_entries<Size>([&](size_t i) { d.set(i, f()); });
}
template <typename G> static Vc_INTRINSIC_L Vector generate(G gen) Vc_INTRINSIC_R;
Vc_DEPRECATED("use copysign(x, y) instead") Vc_INTRINSIC Vector
copySign(AsArg x) const
{
return Vc::copysign(*this, x);
}
Vc_DEPRECATED("use exponent(x) instead") Vc_INTRINSIC Vector exponent() const
{
Vc::exponent(*this);
}
Vc_INTRINSIC_L Vector interleaveLow(Vector x) const Vc_INTRINSIC_R;
Vc_INTRINSIC_L Vector interleaveHigh(Vector x) const Vc_INTRINSIC_R;
};
#undef Vc_CURRENT_CLASS_NAME
template <typename T> constexpr size_t Vector<T, VectorAbi::Avx>::Size;
template <typename T> constexpr size_t Vector<T, VectorAbi::Avx>::MemoryAlignment;
static_assert(Traits::is_simd_vector<AVX2::double_v>::value, "is_simd_vector<double_v>::value");
static_assert(Traits::is_simd_vector<AVX2:: float_v>::value, "is_simd_vector< float_v>::value");
static_assert(Traits::is_simd_vector<AVX2:: int_v>::value, "is_simd_vector<   int_v>::value");
static_assert(Traits::is_simd_vector<AVX2:: uint_v>::value, "is_simd_vector<  uint_v>::value");
static_assert(Traits::is_simd_vector<AVX2:: short_v>::value, "is_simd_vector< short_v>::value");
static_assert(Traits::is_simd_vector<AVX2::ushort_v>::value, "is_simd_vector<ushort_v>::value");
static_assert(Traits::is_simd_mask <AVX2::double_m>::value, "is_simd_mask  <double_m>::value");
static_assert(Traits::is_simd_mask <AVX2:: float_m>::value, "is_simd_mask  < float_m>::value");
static_assert(Traits::is_simd_mask <AVX2:: int_m>::value, "is_simd_mask  <   int_m>::value");
static_assert(Traits::is_simd_mask <AVX2:: uint_m>::value, "is_simd_mask  <  uint_m>::value");
static_assert(Traits::is_simd_mask <AVX2:: short_m>::value, "is_simd_mask  < short_m>::value");
static_assert(Traits::is_simd_mask <AVX2::ushort_m>::value, "is_simd_mask  <ushort_m>::value");
#ifdef Vc_IMPL_AVX2
static_assert(!std::is_convertible<float *, AVX2::short_v>::value, "A float* should never implicitly convert to short_v. Something is broken.");
static_assert(!std::is_convertible<int * , AVX2::short_v>::value, "An int* should never implicitly convert to short_v. Something is broken.");
static_assert(!std::is_convertible<short *, AVX2::short_v>::value, "A short* should never implicitly convert to short_v. Something is broken.");
#endif
#define Vc_CONDITIONAL_ASSIGN(name_,op_) \
template <Operator O, typename T, typename M, typename U> \
Vc_INTRINSIC enable_if<O == Operator::name_, void> conditional_assign( \
AVX2::Vector<T> &lhs, M &&mask, U &&rhs) \
{ \
lhs(mask) op_ rhs; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_CONDITIONAL_ASSIGN( Assign, =);
Vc_CONDITIONAL_ASSIGN( PlusAssign, +=);
Vc_CONDITIONAL_ASSIGN( MinusAssign, -=);
Vc_CONDITIONAL_ASSIGN( MultiplyAssign, *=);
Vc_CONDITIONAL_ASSIGN( DivideAssign, /=);
Vc_CONDITIONAL_ASSIGN( RemainderAssign, %=);
Vc_CONDITIONAL_ASSIGN( XorAssign, ^=);
Vc_CONDITIONAL_ASSIGN( AndAssign, &=);
Vc_CONDITIONAL_ASSIGN( OrAssign, |=);
Vc_CONDITIONAL_ASSIGN( LeftShiftAssign,<<=);
Vc_CONDITIONAL_ASSIGN(RightShiftAssign,>>=);
#undef Vc_CONDITIONAL_ASSIGN
#define Vc_CONDITIONAL_ASSIGN(name_,expr_) \
template <Operator O, typename T, typename M> \
Vc_INTRINSIC enable_if<O == Operator::name_, AVX2::Vector<T>> conditional_assign( \
AVX2::Vector<T> &lhs, M &&mask) \
{ \
return expr_; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_CONDITIONAL_ASSIGN(PostIncrement, lhs(mask)++);
Vc_CONDITIONAL_ASSIGN( PreIncrement, ++lhs(mask));
Vc_CONDITIONAL_ASSIGN(PostDecrement, lhs(mask)--);
Vc_CONDITIONAL_ASSIGN( PreDecrement, --lhs(mask));
#undef Vc_CONDITIONAL_ASSIGN
}
#ifndef VC_AVX_LIMITS_H_
#define VC_AVX_LIMITS_H_ 
namespace std
{
#define Vc_NUM_LIM(T,_max,_min) \
template <> struct numeric_limits<Vc::AVX2::Vector<T>> : public numeric_limits<T> { \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> max() Vc_NOEXCEPT \
{ \
return _max; \
} \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> min() Vc_NOEXCEPT \
{ \
return _min; \
} \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> lowest() Vc_NOEXCEPT \
{ \
return min(); \
} \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> epsilon() Vc_NOEXCEPT \
{ \
return Vc::AVX2::Vector<T>::Zero(); \
} \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> round_error() Vc_NOEXCEPT \
{ \
return Vc::AVX2::Vector<T>::Zero(); \
} \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> infinity() Vc_NOEXCEPT \
{ \
return Vc::AVX2::Vector<T>::Zero(); \
} \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> quiet_NaN() Vc_NOEXCEPT \
{ \
return Vc::AVX2::Vector<T>::Zero(); \
} \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> signaling_NaN() Vc_NOEXCEPT \
{ \
return Vc::AVX2::Vector<T>::Zero(); \
} \
static Vc_INTRINSIC Vc_CONST Vc::AVX2::Vector<T> denorm_min() Vc_NOEXCEPT \
{ \
return Vc::AVX2::Vector<T>::Zero(); \
} \
}
#ifdef Vc_IMPL_AVX2
Vc_NUM_LIM(unsigned short, Vc::Detail::allone<__m256i>(), Vc::Detail::zero<__m256i>());
Vc_NUM_LIM( short, _mm256_srli_epi16(Vc::Detail::allone<__m256i>(), 1), Vc::AVX::setmin_epi16());
Vc_NUM_LIM( unsigned int, Vc::Detail::allone<__m256i>(), Vc::Detail::zero<__m256i>());
Vc_NUM_LIM( int, _mm256_srli_epi32(Vc::Detail::allone<__m256i>(), 1), Vc::AVX::setmin_epi32());
#endif
#undef Vc_NUM_LIM
}
#endif
#ifndef VC_AVX_CONST_H_
#define VC_AVX_CONST_H_ 
#include <cstddef>
namespace Vc_VERSIONED_NAMESPACE
{
namespace AVX
{
template<typename T> struct IndexesFromZeroData;
template<> struct IndexesFromZeroData<int> {
static Vc_ALWAYS_INLINE Vc_CONST const int *address() { return reinterpret_cast<const int *>(&_IndexesFromZero32[0]); }
};
template<> struct IndexesFromZeroData<unsigned int> {
static Vc_ALWAYS_INLINE Vc_CONST const unsigned int *address() { return &_IndexesFromZero32[0]; }
};
template<> struct IndexesFromZeroData<short> {
static Vc_ALWAYS_INLINE Vc_CONST const short *address() { return reinterpret_cast<const short *>(&_IndexesFromZero16[0]); }
};
template<> struct IndexesFromZeroData<unsigned short> {
static Vc_ALWAYS_INLINE Vc_CONST const unsigned short *address() { return &_IndexesFromZero16[0]; }
};
template<> struct IndexesFromZeroData<signed char> {
static Vc_ALWAYS_INLINE Vc_CONST const signed char *address() { return reinterpret_cast<const signed char *>(&_IndexesFromZero8[0]); }
};
template<> struct IndexesFromZeroData<char> {
static Vc_ALWAYS_INLINE Vc_CONST const char *address() { return reinterpret_cast<const char *>(&_IndexesFromZero8[0]); }
};
template<> struct IndexesFromZeroData<unsigned char> {
static Vc_ALWAYS_INLINE Vc_CONST const unsigned char *address() { return &_IndexesFromZero8[0]; }
};
template<typename _T> struct Const
{
typedef Vector<_T> V;
typedef typename V::EntryType T;
typedef typename V::Mask M;
static Vc_ALWAYS_INLINE Vc_CONST V _pi_4() { return V(c_trig<T>::data[0]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_4_hi() { return V(c_trig<T>::data[1]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_4_rem1() { return V(c_trig<T>::data[2]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_4_rem2() { return V(c_trig<T>::data[3]); }
static Vc_ALWAYS_INLINE Vc_CONST V _1_16() { return V(c_trig<T>::data[4]); }
static Vc_ALWAYS_INLINE Vc_CONST V _16() { return V(c_trig<T>::data[5]); }
static Vc_ALWAYS_INLINE Vc_CONST V atanP(int i) { return V(c_trig<T>::data[(12 + i)]); }
static Vc_ALWAYS_INLINE Vc_CONST V atanQ(int i) { return V(c_trig<T>::data[(17 + i)]); }
static Vc_ALWAYS_INLINE Vc_CONST V atanThrsHi() { return V(c_trig<T>::data[22]); }
static Vc_ALWAYS_INLINE Vc_CONST V atanThrsLo() { return V(c_trig<T>::data[23]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_2_rem() { return V(c_trig<T>::data[24]); }
static Vc_ALWAYS_INLINE Vc_CONST V lossThreshold() { return V(c_trig<T>::data[8]); }
static Vc_ALWAYS_INLINE Vc_CONST V _4_pi() { return V(c_trig<T>::data[9]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_2() { return V(c_trig<T>::data[10]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi() { return V(c_trig<T>::data[11]); }
static Vc_ALWAYS_INLINE Vc_CONST V asinCoeff0(int i) { return V(c_trig<T>::data[(28 + i)]); }
static Vc_ALWAYS_INLINE Vc_CONST V asinCoeff1(int i) { return V(c_trig<T>::data[(33 + i)]); }
static Vc_ALWAYS_INLINE Vc_CONST V asinCoeff2(int i) { return V(c_trig<T>::data[(37 + i)]); }
static Vc_ALWAYS_INLINE Vc_CONST V asinCoeff3(int i) { return V(c_trig<T>::data[(43 + i)]); }
static Vc_ALWAYS_INLINE Vc_CONST V smallAsinInput() { return V(c_trig<T>::data[25]); }
static Vc_ALWAYS_INLINE Vc_CONST V largeAsinInput() { return V(c_trig<T>::data[26]); }
static Vc_ALWAYS_INLINE Vc_CONST M exponentMask() { return M(V(c_log<T>::d(1)).data()); }
static Vc_ALWAYS_INLINE Vc_CONST V _1_2() { return V(c_log<T>::d(18)); }
static Vc_ALWAYS_INLINE Vc_CONST V _1_sqrt2() { return V(c_log<T>::d(15)); }
static Vc_ALWAYS_INLINE Vc_CONST V P(int i) { return V(c_log<T>::d(2 + i)); }
static Vc_ALWAYS_INLINE Vc_CONST V Q(int i) { return V(c_log<T>::d(8 + i)); }
static Vc_ALWAYS_INLINE Vc_CONST V min() { return V(c_log<T>::d(14)); }
static Vc_ALWAYS_INLINE Vc_CONST V ln2_small() { return V(c_log<T>::d(17)); }
static Vc_ALWAYS_INLINE Vc_CONST V ln2_large() { return V(c_log<T>::d(16)); }
static Vc_ALWAYS_INLINE Vc_CONST V neginf() { return V(c_log<T>::d(13)); }
static Vc_ALWAYS_INLINE Vc_CONST V log10_e() { return V(c_log<T>::d(19)); }
static Vc_ALWAYS_INLINE Vc_CONST V log2_e() { return V(c_log<T>::d(20)); }
static Vc_ALWAYS_INLINE_L Vc_CONST_L V highMask() Vc_ALWAYS_INLINE_R Vc_CONST_R;
static Vc_ALWAYS_INLINE_L Vc_CONST_L V highMask(int bits) Vc_ALWAYS_INLINE_R Vc_CONST_R;
};
template <> Vc_ALWAYS_INLINE Vc_CONST Vector<float> Const<float>::highMask()
{
return _mm256_broadcast_ss(
reinterpret_cast<const float *>(&c_general::highMaskFloat));
}
template <> Vc_ALWAYS_INLINE Vc_CONST Vector<double> Const<double>::highMask()
{
return _mm256_broadcast_sd(
reinterpret_cast<const double *>(&c_general::highMaskDouble));
}
template <> Vc_ALWAYS_INLINE Vc_CONST Vector<float> Const<float>::highMask(int bits)
{
#ifdef Vc_IMPL_AVX2
#if defined Vc_ICC || defined Vc_MSVC
__m256i allone;
allone = _mm256_cmpeq_epi8(allone, allone);
#else
auto allone = ~__m256i();
#endif
return _mm256_castsi256_ps(_mm256_slli_epi32(allone, bits));
#else
__m128 tmp = _mm_castsi128_ps(_mm_slli_epi32(_mm_setallone_si128(), bits));
return concat(tmp, tmp);
#endif
}
template <> Vc_ALWAYS_INLINE Vc_CONST Vector<double> Const<double>::highMask(int bits)
{
#ifdef Vc_IMPL_AVX2
#if defined Vc_ICC || defined Vc_MSVC
__m256i allone;
allone = _mm256_cmpeq_epi8(allone, allone);
#else
auto allone = ~__m256i();
#endif
return _mm256_castsi256_pd(_mm256_slli_epi64(allone, bits));
#else
__m128d tmp = _mm_castsi128_pd(_mm_slli_epi64(_mm_setallone_si128(), bits));
return concat(tmp, tmp);
#endif
}
}
namespace AVX2
{
using AVX::IndexesFromZeroData;
using AVX::Const;
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
Vc_INTRINSIC AVX2::double_m operator==(AVX2::double_v a, AVX2::double_v b) { return AVX::cmpeq_pd(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: float_m operator==(AVX2:: float_v a, AVX2:: float_v b) { return AVX::cmpeq_ps(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: int_m operator==(AVX2:: int_v a, AVX2:: int_v b) { return AVX::cmpeq_epi32(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: uint_m operator==(AVX2:: uint_v a, AVX2:: uint_v b) { return AVX::cmpeq_epi32(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: short_m operator==(AVX2:: short_v a, AVX2:: short_v b) { return AVX::cmpeq_epi16(a.data(), b.data()); }
Vc_INTRINSIC AVX2::ushort_m operator==(AVX2::ushort_v a, AVX2::ushort_v b) { return AVX::cmpeq_epi16(a.data(), b.data()); }
Vc_INTRINSIC AVX2::double_m operator!=(AVX2::double_v a, AVX2::double_v b) { return AVX::cmpneq_pd(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: float_m operator!=(AVX2:: float_v a, AVX2:: float_v b) { return AVX::cmpneq_ps(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: int_m operator!=(AVX2:: int_v a, AVX2:: int_v b) { return not_(AVX::cmpeq_epi32(a.data(), b.data())); }
Vc_INTRINSIC AVX2:: uint_m operator!=(AVX2:: uint_v a, AVX2:: uint_v b) { return not_(AVX::cmpeq_epi32(a.data(), b.data())); }
Vc_INTRINSIC AVX2:: short_m operator!=(AVX2:: short_v a, AVX2:: short_v b) { return not_(AVX::cmpeq_epi16(a.data(), b.data())); }
Vc_INTRINSIC AVX2::ushort_m operator!=(AVX2::ushort_v a, AVX2::ushort_v b) { return not_(AVX::cmpeq_epi16(a.data(), b.data())); }
Vc_INTRINSIC AVX2::double_m operator>=(AVX2::double_v a, AVX2::double_v b) { return AVX::cmpnlt_pd(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: float_m operator>=(AVX2:: float_v a, AVX2:: float_v b) { return AVX::cmpnlt_ps(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: int_m operator>=(AVX2:: int_v a, AVX2:: int_v b) { return not_(AVX::cmplt_epi32(a.data(), b.data())); }
Vc_INTRINSIC AVX2:: uint_m operator>=(AVX2:: uint_v a, AVX2:: uint_v b) { return not_(AVX::cmplt_epu32(a.data(), b.data())); }
Vc_INTRINSIC AVX2:: short_m operator>=(AVX2:: short_v a, AVX2:: short_v b) { return not_(AVX::cmplt_epi16(a.data(), b.data())); }
Vc_INTRINSIC AVX2::ushort_m operator>=(AVX2::ushort_v a, AVX2::ushort_v b) { return not_(AVX::cmplt_epu16(a.data(), b.data())); }
Vc_INTRINSIC AVX2::double_m operator<=(AVX2::double_v a, AVX2::double_v b) { return AVX::cmple_pd(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: float_m operator<=(AVX2:: float_v a, AVX2:: float_v b) { return AVX::cmple_ps(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: int_m operator<=(AVX2:: int_v a, AVX2:: int_v b) { return not_(AVX::cmpgt_epi32(a.data(), b.data())); }
Vc_INTRINSIC AVX2:: uint_m operator<=(AVX2:: uint_v a, AVX2:: uint_v b) { return not_(AVX::cmpgt_epu32(a.data(), b.data())); }
Vc_INTRINSIC AVX2:: short_m operator<=(AVX2:: short_v a, AVX2:: short_v b) { return not_(AVX::cmpgt_epi16(a.data(), b.data())); }
Vc_INTRINSIC AVX2::ushort_m operator<=(AVX2::ushort_v a, AVX2::ushort_v b) { return not_(AVX::cmpgt_epu16(a.data(), b.data())); }
Vc_INTRINSIC AVX2::double_m operator> (AVX2::double_v a, AVX2::double_v b) { return AVX::cmpgt_pd(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: float_m operator> (AVX2:: float_v a, AVX2:: float_v b) { return AVX::cmpgt_ps(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: int_m operator> (AVX2:: int_v a, AVX2:: int_v b) { return AVX::cmpgt_epi32(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: uint_m operator> (AVX2:: uint_v a, AVX2:: uint_v b) { return AVX::cmpgt_epu32(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: short_m operator> (AVX2:: short_v a, AVX2:: short_v b) { return AVX::cmpgt_epi16(a.data(), b.data()); }
Vc_INTRINSIC AVX2::ushort_m operator> (AVX2::ushort_v a, AVX2::ushort_v b) { return AVX::cmpgt_epu16(a.data(), b.data()); }
Vc_INTRINSIC AVX2::double_m operator< (AVX2::double_v a, AVX2::double_v b) { return AVX::cmplt_pd(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: float_m operator< (AVX2:: float_v a, AVX2:: float_v b) { return AVX::cmplt_ps(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: int_m operator< (AVX2:: int_v a, AVX2:: int_v b) { return AVX::cmplt_epi32(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: uint_m operator< (AVX2:: uint_v a, AVX2:: uint_v b) { return AVX::cmplt_epu32(a.data(), b.data()); }
Vc_INTRINSIC AVX2:: short_m operator< (AVX2:: short_v a, AVX2:: short_v b) { return AVX::cmplt_epi16(a.data(), b.data()); }
Vc_INTRINSIC AVX2::ushort_m operator< (AVX2::ushort_v a, AVX2::ushort_v b) { return AVX::cmplt_epu16(a.data(), b.data()); }
template <typename T>
Vc_INTRINSIC AVX2::Vector<T> operator^(AVX2::Vector<T> a, AVX2::Vector<T> b)
{
return xor_(a.data(), b.data());
}
template <typename T>
Vc_INTRINSIC AVX2::Vector<T> operator&(AVX2::Vector<T> a, AVX2::Vector<T> b)
{
return and_(a.data(), b.data());
}
template <typename T>
Vc_INTRINSIC AVX2::Vector<T> operator|(AVX2::Vector<T> a, AVX2::Vector<T> b)
{
return or_(a.data(), b.data());
}
template <typename T>
Vc_INTRINSIC AVX2::Vector<T> operator+(AVX2::Vector<T> a, AVX2::Vector<T> b)
{
return add(a.data(), b.data(), T());
}
template <typename T>
Vc_INTRINSIC AVX2::Vector<T> operator-(AVX2::Vector<T> a, AVX2::Vector<T> b)
{
return sub(a.data(), b.data(), T());
}
template <typename T>
Vc_INTRINSIC AVX2::Vector<T> operator*(AVX2::Vector<T> a, AVX2::Vector<T> b)
{
return mul(a.data(), b.data(), T());
}
template <typename T>
Vc_INTRINSIC AVX2::Vector<T> operator/(AVX2::Vector<T> a, AVX2::Vector<T> b)
{
return div(a.data(), b.data(), T());
}
Vc_INTRINSIC AVX2::Vector<ushort> operator/(AVX2::Vector<ushort> a,
AVX2::Vector<ushort> b)
{
using namespace AVX;
const __m256 lo = _mm256_div_ps(convert<ushort, float>(lo128(a.data())),
convert<ushort, float>(lo128(b.data())));
const __m256 hi = _mm256_div_ps(convert<ushort, float>(hi128(a.data())),
convert<ushort, float>(hi128(b.data())));
const float_v threshold = 32767.f;
using Detail::operator>;
const __m128i loShort = (Vc_IS_UNLIKELY((float_v(lo) > threshold).isNotEmpty()))
? convert<float, ushort>(lo)
: convert<float, short>(lo);
const __m128i hiShort = (Vc_IS_UNLIKELY((float_v(hi) > threshold).isNotEmpty()))
? convert<float, ushort>(hi)
: convert<float, short>(hi);
return concat(loShort, hiShort);
}
template <typename T>
Vc_INTRINSIC enable_if<std::is_integral<T>::value, AVX2::Vector<T>> operator%(
AVX2::Vector<T> a, AVX2::Vector<T> b)
{
return a - a / b * b;
}
}
template <> template <typename G> Vc_INTRINSIC AVX2::double_v AVX2::double_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
return _mm256_setr_pd(tmp0, tmp1, tmp2, tmp3);
}
template <> template <typename G> Vc_INTRINSIC AVX2::float_v AVX2::float_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
const auto tmp4 = gen(4);
const auto tmp5 = gen(5);
const auto tmp6 = gen(6);
const auto tmp7 = gen(7);
return _mm256_setr_ps(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7);
}
#ifdef Vc_IMPL_AVX2
template <> template <typename G> Vc_INTRINSIC AVX2::int_v AVX2::int_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
const auto tmp4 = gen(4);
const auto tmp5 = gen(5);
const auto tmp6 = gen(6);
const auto tmp7 = gen(7);
return _mm256_setr_epi32(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7);
}
template <> template <typename G> Vc_INTRINSIC AVX2::uint_v AVX2::uint_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
const auto tmp4 = gen(4);
const auto tmp5 = gen(5);
const auto tmp6 = gen(6);
const auto tmp7 = gen(7);
return _mm256_setr_epi32(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7);
}
template <> template <typename G> Vc_INTRINSIC AVX2::short_v AVX2::short_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
const auto tmp4 = gen(4);
const auto tmp5 = gen(5);
const auto tmp6 = gen(6);
const auto tmp7 = gen(7);
const auto tmp8 = gen(8);
const auto tmp9 = gen(9);
const auto tmp10 = gen(10);
const auto tmp11 = gen(11);
const auto tmp12 = gen(12);
const auto tmp13 = gen(13);
const auto tmp14 = gen(14);
const auto tmp15 = gen(15);
return _mm256_setr_epi16(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15);
}
template <> template <typename G> Vc_INTRINSIC AVX2::ushort_v AVX2::ushort_v::generate(G gen)
{
const auto tmp0 = gen(0);
const auto tmp1 = gen(1);
const auto tmp2 = gen(2);
const auto tmp3 = gen(3);
const auto tmp4 = gen(4);
const auto tmp5 = gen(5);
const auto tmp6 = gen(6);
const auto tmp7 = gen(7);
const auto tmp8 = gen(8);
const auto tmp9 = gen(9);
const auto tmp10 = gen(10);
const auto tmp11 = gen(11);
const auto tmp12 = gen(12);
const auto tmp13 = gen(13);
const auto tmp14 = gen(14);
const auto tmp15 = gen(15);
return _mm256_setr_epi16(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15);
}
#endif
template <typename T> Vc_INTRINSIC Vector<T, VectorAbi::Avx>::Vector(VectorSpecialInitializerZero) : d{} {}
template <> Vc_INTRINSIC Vector<double, VectorAbi::Avx>::Vector(VectorSpecialInitializerOne) : d(AVX::setone_pd()) {}
template <> Vc_INTRINSIC Vector< float, VectorAbi::Avx>::Vector(VectorSpecialInitializerOne) : d(AVX::setone_ps()) {}
#ifdef Vc_IMPL_AVX2
template <> Vc_INTRINSIC Vector< int, VectorAbi::Avx>::Vector(VectorSpecialInitializerOne) : d(AVX::setone_epi32()) {}
template <> Vc_INTRINSIC Vector< uint, VectorAbi::Avx>::Vector(VectorSpecialInitializerOne) : d(AVX::setone_epu32()) {}
template <> Vc_INTRINSIC Vector< short, VectorAbi::Avx>::Vector(VectorSpecialInitializerOne) : d(AVX::setone_epi16()) {}
template <> Vc_INTRINSIC Vector<ushort, VectorAbi::Avx>::Vector(VectorSpecialInitializerOne) : d(AVX::setone_epu16()) {}
template <> Vc_INTRINSIC Vector< schar, VectorAbi::Avx>::Vector(VectorSpecialInitializerOne) : d(AVX::setone_epi8()) {}
template <> Vc_INTRINSIC Vector< uchar, VectorAbi::Avx>::Vector(VectorSpecialInitializerOne) : d(AVX::setone_epu8()) {}
#endif
template <typename T>
Vc_ALWAYS_INLINE Vector<T, VectorAbi::Avx>::Vector(
VectorSpecialInitializerIndexesFromZero)
: Vector(AVX::IndexesFromZeroData<T>::address(), Vc::Aligned)
{
}
template <>
Vc_ALWAYS_INLINE Vector<float, VectorAbi::Avx>::Vector(VectorSpecialInitializerIndexesFromZero)
: Vector(AVX::IndexesFromZeroData<int>::address(), Vc::Aligned)
{
}
template <>
Vc_ALWAYS_INLINE Vector<double, VectorAbi::Avx>::Vector(VectorSpecialInitializerIndexesFromZero)
: Vector(AVX::IndexesFromZeroData<int>::address(), Vc::Aligned)
{
}
template <typename DstT>
template <typename SrcT, typename Flags>
Vc_INTRINSIC typename Vector<DstT, VectorAbi::Avx>::
#ifndef Vc_MSVC
template
#endif
load_concept<SrcT, Flags>::type Vector<DstT, VectorAbi::Avx>::load(const SrcT *mem, Flags flags)
{
Common::handleLoadPrefetches(mem, flags);
d.v() = Detail::load<VectorType, DstT>(mem, flags);
}
template<typename T> Vc_INTRINSIC void Vector<T, VectorAbi::Avx>::setZero()
{
data() = Detail::zero<VectorType>();
}
template<typename T> Vc_INTRINSIC void Vector<T, VectorAbi::Avx>::setZero(const Mask &k)
{
data() = Detail::andnot_(AVX::avx_cast<VectorType>(k.data()), data());
}
template<typename T> Vc_INTRINSIC void Vector<T, VectorAbi::Avx>::setZeroInverted(const Mask &k)
{
data() = Detail::and_(AVX::avx_cast<VectorType>(k.data()), data());
}
template<> Vc_INTRINSIC void Vector<double, VectorAbi::Avx>::setQnan()
{
data() = Detail::allone<VectorType>();
}
template<> Vc_INTRINSIC void Vector<double, VectorAbi::Avx>::setQnan(MaskArgument k)
{
data() = _mm256_or_pd(data(), k.dataD());
}
template<> Vc_INTRINSIC void Vector<float, VectorAbi::Avx>::setQnan()
{
data() = Detail::allone<VectorType>();
}
template<> Vc_INTRINSIC void Vector<float, VectorAbi::Avx>::setQnan(MaskArgument k)
{
data() = _mm256_or_ps(data(), k.data());
}
template <typename T>
template <typename U,
typename Flags,
typename>
Vc_INTRINSIC void Vector<T, VectorAbi::Avx>::store(U *mem, Flags flags) const
{
Common::handleStorePrefetches(mem, flags);
HV::template store<Flags>(mem, data());
}
template <typename T>
template <typename U,
typename Flags,
typename>
Vc_INTRINSIC void Vector<T, VectorAbi::Avx>::store(U *mem, Mask mask, Flags flags) const
{
Common::handleStorePrefetches(mem, flags);
HV::template store<Flags>(mem, data(), AVX::avx_cast<VectorType>(mask.data()));
}
#ifdef Vc_IMPL_AVX2
template <> Vc_ALWAYS_INLINE AVX2::Vector< int> Vector< int, VectorAbi::Avx>::operator<<(AsArg x) const { return _mm256_sllv_epi32(d.v(), x.d.v()); }
template <> Vc_ALWAYS_INLINE AVX2::Vector< uint> Vector< uint, VectorAbi::Avx>::operator<<(AsArg x) const { return _mm256_sllv_epi32(d.v(), x.d.v()); }
template <> Vc_ALWAYS_INLINE AVX2::Vector< int> Vector< int, VectorAbi::Avx>::operator>>(AsArg x) const { return _mm256_srav_epi32(d.v(), x.d.v()); }
template <> Vc_ALWAYS_INLINE AVX2::Vector< uint> Vector< uint, VectorAbi::Avx>::operator>>(AsArg x) const { return _mm256_srlv_epi32(d.v(), x.d.v()); }
template <> Vc_ALWAYS_INLINE AVX2::Vector< short> Vector< short, VectorAbi::Avx>::operator<<(AsArg x) const { return generate([&](int i) { return get(*this, i) << get(x, i); }); }
template <> Vc_ALWAYS_INLINE AVX2::Vector<ushort> Vector<ushort, VectorAbi::Avx>::operator<<(AsArg x) const { return generate([&](int i) { return get(*this, i) << get(x, i); }); }
template <> Vc_ALWAYS_INLINE AVX2::Vector< short> Vector< short, VectorAbi::Avx>::operator>>(AsArg x) const { return generate([&](int i) { return get(*this, i) >> get(x, i); }); }
template <> Vc_ALWAYS_INLINE AVX2::Vector<ushort> Vector<ushort, VectorAbi::Avx>::operator>>(AsArg x) const { return generate([&](int i) { return get(*this, i) >> get(x, i); }); }
template <typename T>
Vc_ALWAYS_INLINE AVX2::Vector<T> &Vector<T, VectorAbi::Avx>::operator<<=(AsArg x)
{
static_assert(std::is_integral<T>::value,
"bitwise-operators can only be used with Vectors of integral type");
return *this = *this << x;
}
template <typename T>
Vc_ALWAYS_INLINE AVX2::Vector<T> &Vector<T, VectorAbi::Avx>::operator>>=(AsArg x)
{
static_assert(std::is_integral<T>::value,
"bitwise-operators can only be used with Vectors of integral type");
return *this = *this >> x;
}
#endif
template<typename T> Vc_ALWAYS_INLINE AVX2::Vector<T> &Vector<T, VectorAbi::Avx>::operator>>=(int shift) {
d.v() = Detail::shiftRight(d.v(), shift, T());
return *static_cast<AVX2::Vector<T> *>(this);
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE AVX2::Vector<T> Vector<T, VectorAbi::Avx>::operator>>(int shift) const {
return Detail::shiftRight(d.v(), shift, T());
}
template<typename T> Vc_ALWAYS_INLINE AVX2::Vector<T> &Vector<T, VectorAbi::Avx>::operator<<=(int shift) {
d.v() = Detail::shiftLeft(d.v(), shift, T());
return *static_cast<AVX2::Vector<T> *>(this);
}
template<typename T> Vc_ALWAYS_INLINE Vc_PURE AVX2::Vector<T> Vector<T, VectorAbi::Avx>::operator<<(int shift) const {
return Detail::shiftLeft(d.v(), shift, T());
}
Vc_INTRINSIC Vc_CONST AVX2::float_m isnegative(AVX2::float_v x)
{
return AVX::avx_cast<__m256>(AVX::srai_epi32<31>(
AVX::avx_cast<__m256i>(_mm256_and_ps(AVX::setsignmask_ps(), x.data()))));
}
Vc_INTRINSIC Vc_CONST AVX2::double_m isnegative(AVX2::double_v x)
{
return Mem::permute<X1, X1, X3, X3>(AVX::avx_cast<__m256>(AVX::srai_epi32<31>(
AVX::avx_cast<__m256i>(_mm256_and_pd(AVX::setsignmask_pd(), x.data())))));
}
template <>
template <typename MT, typename IT>
inline void AVX2::double_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm256_setr_pd(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]], mem[indexes[3]]);
}
template <>
template <typename MT, typename IT>
inline void AVX2::float_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm256_setr_ps(mem[indexes[0]],
mem[indexes[1]],
mem[indexes[2]],
mem[indexes[3]],
mem[indexes[4]],
mem[indexes[5]],
mem[indexes[6]],
mem[indexes[7]]);
}
#ifdef Vc_IMPL_AVX2
#ifndef Vc_MSVC
template <>
Vc_INTRINSIC void AVX2::double_v::gatherImplementation(const double *mem,
SSE::int_v indexes)
{
d.v() = _mm256_i32gather_pd(mem, indexes.data(), sizeof(double));
}
template <>
Vc_INTRINSIC void AVX2::float_v::gatherImplementation(const float *mem,
AVX2::int_v indexes)
{
d.v() = _mm256_i32gather_ps(mem, indexes.data(), sizeof(float));
}
template <>
Vc_INTRINSIC void AVX2::int_v::gatherImplementation(const int *mem,
AVX2::int_v indexes)
{
d.v() = _mm256_i32gather_epi32(mem, indexes.data(), sizeof(int));
}
template <>
Vc_INTRINSIC void AVX2::uint_v::gatherImplementation(const uint *mem,
AVX2::int_v indexes)
{
d.v() =
_mm256_i32gather_epi32(aliasing_cast<int>(mem), indexes.data(), sizeof(unsigned));
}
#endif
template <>
template <typename MT, typename IT>
inline void AVX2::int_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm256_setr_epi32(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]],
mem[indexes[3]], mem[indexes[4]], mem[indexes[5]],
mem[indexes[6]], mem[indexes[7]]);
}
template <>
template <typename MT, typename IT>
inline void AVX2::uint_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm256_setr_epi32(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]],
mem[indexes[3]], mem[indexes[4]], mem[indexes[5]],
mem[indexes[6]], mem[indexes[7]]);
}
template <>
template <typename MT, typename IT>
inline void AVX2::short_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm256_setr_epi16(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]],
mem[indexes[3]], mem[indexes[4]], mem[indexes[5]],
mem[indexes[6]], mem[indexes[7]], mem[indexes[8]],
mem[indexes[9]], mem[indexes[10]], mem[indexes[11]],
mem[indexes[12]], mem[indexes[13]], mem[indexes[14]],
mem[indexes[15]]);
}
template <>
template <typename MT, typename IT>
inline void AVX2::ushort_v::gatherImplementation(const MT *mem, const IT &indexes)
{
d.v() = _mm256_setr_epi16(mem[indexes[0]], mem[indexes[1]], mem[indexes[2]],
mem[indexes[3]], mem[indexes[4]], mem[indexes[5]],
mem[indexes[6]], mem[indexes[7]], mem[indexes[8]],
mem[indexes[9]], mem[indexes[10]], mem[indexes[11]],
mem[indexes[12]], mem[indexes[13]], mem[indexes[14]],
mem[indexes[15]]);
}
#endif
template <typename T>
template <typename MT, typename IT>
inline void Vector<T, VectorAbi::Avx>::gatherImplementation(const MT *mem, const IT &indexes, MaskArgument mask)
{
using Selector = std::integral_constant < Common::GatherScatterImplementation,
#ifdef Vc_USE_SET_GATHERS
Traits::is_simd_vector<IT>::value ? Common::GatherScatterImplementation::SetIndexZero :
#endif
#ifdef Vc_USE_BSF_GATHERS
Common::GatherScatterImplementation::BitScanLoop
#elif defined Vc_USE_POPCNT_BSF_GATHERS
Common::GatherScatterImplementation::PopcntSwitch
#else
Common::GatherScatterImplementation::SimpleLoop
#endif
> ;
Common::executeGather(Selector(), *this, mem, indexes, mask);
}
template <typename T>
template <typename MT, typename IT>
inline void Vector<T, VectorAbi::Avx>::scatterImplementation(MT *mem, IT &&indexes) const
{
Common::unrolled_loop<std::size_t, 0, Size>([&](std::size_t i) { mem[indexes[i]] = d.m(i); });
}
template <typename T>
template <typename MT, typename IT>
inline void Vector<T, VectorAbi::Avx>::scatterImplementation(MT *mem, IT &&indexes, MaskArgument mask) const
{
using Selector = std::integral_constant < Common::GatherScatterImplementation,
#ifdef Vc_USE_SET_GATHERS
Traits::is_simd_vector<IT>::value ? Common::GatherScatterImplementation::SetIndexZero :
#endif
#ifdef Vc_USE_BSF_GATHERS
Common::GatherScatterImplementation::BitScanLoop
#elif defined Vc_USE_POPCNT_BSF_GATHERS
Common::GatherScatterImplementation::PopcntSwitch
#else
Common::GatherScatterImplementation::SimpleLoop
#endif
> ;
Common::executeScatter(Selector(), *this, mem, std::forward<IT>(indexes), mask);
}
#ifdef Vc_USE_BUILTIN_VECTOR_TYPES
template<typename T> Vc_ALWAYS_INLINE Vc_PURE AVX2::Vector<T> Vector<T, VectorAbi::Avx>::operator-() const
{
return VectorType(-d.builtin());
}
#else
template<typename T> Vc_ALWAYS_INLINE Vc_PURE AVX2::Vector<T> Vector<T, VectorAbi::Avx>::operator-() const
{
return Detail::negate(d.v(), std::integral_constant<std::size_t, sizeof(T)>());
}
#endif
template <typename T>
Vc_INTRINSIC std::pair<Vector<T, VectorAbi::Avx>, int>
Vector<T, VectorAbi::Avx>::minIndex() const
{
AVX2::Vector<T> x = min();
return std::make_pair(x, (*this == x).firstOne());
}
template <typename T>
Vc_INTRINSIC std::pair<Vector<T, VectorAbi::Avx>, int>
Vector<T, VectorAbi::Avx>::maxIndex() const
{
AVX2::Vector<T> x = max();
return std::make_pair(x, (*this == x).firstOne());
}
template <> Vc_INTRINSIC std::pair<AVX2::float_v, int> AVX2::float_v::minIndex() const
{
__m256 x = d.v();
__m256 idx = Vector<float>::IndexesFromZero().data();
__m256 y = Mem::permute128<X1, X0>(x);
__m256 idy = Mem::permute128<X1, X0>(idx);
__m256 less = AVX::cmplt_ps(x, y);
x = _mm256_blendv_ps(y, x, less);
idx = _mm256_blendv_ps(idy, idx, less);
y = Reg::permute<X2, X3, X0, X1>(x);
idy = Reg::permute<X2, X3, X0, X1>(idx);
less = AVX::cmplt_ps(x, y);
x = _mm256_blendv_ps(y, x, less);
idx = _mm256_blendv_ps(idy, idx, less);
y = Reg::permute<X1, X0, X3, X2>(x);
idy = Reg::permute<X1, X0, X3, X2>(idx);
less = AVX::cmplt_ps(x, y);
idx = _mm256_blendv_ps(idy, idx, less);
const auto index = _mm_cvtsi128_si32(AVX::avx_cast<__m128i>(idx));
#ifdef Vc_GNU_ASM
__asm__ __volatile__("");
#endif
x = _mm256_blendv_ps(y, x, less);
return std::make_pair(x, index);
}
template<typename T> Vc_ALWAYS_INLINE AVX2::Vector<T> Vector<T, VectorAbi::Avx>::partialSum() const
{
AVX2::Vector<T> tmp = *this;
if (Size > 1) tmp += tmp.shifted(-1);
if (Size > 2) tmp += tmp.shifted(-2);
if (Size > 4) tmp += tmp.shifted(-4);
if (Size > 8) tmp += tmp.shifted(-8);
if (Size > 16) tmp += tmp.shifted(-16);
return tmp;
}
template<typename T> Vc_ALWAYS_INLINE typename Vector<T, VectorAbi::Avx>::EntryType Vector<T, VectorAbi::Avx>::min(MaskArgument m) const
{
AVX2::Vector<T> tmp = std::numeric_limits<AVX2::Vector<T> >::max();
tmp(m) = *this;
return tmp.min();
}
template<typename T> Vc_ALWAYS_INLINE typename Vector<T, VectorAbi::Avx>::EntryType Vector<T, VectorAbi::Avx>::max(MaskArgument m) const
{
AVX2::Vector<T> tmp = std::numeric_limits<AVX2::Vector<T> >::min();
tmp(m) = *this;
return tmp.max();
}
template<typename T> Vc_ALWAYS_INLINE typename Vector<T, VectorAbi::Avx>::EntryType Vector<T, VectorAbi::Avx>::product(MaskArgument m) const
{
AVX2::Vector<T> tmp(Vc::One);
tmp(m) = *this;
return tmp.product();
}
template<typename T> Vc_ALWAYS_INLINE typename Vector<T, VectorAbi::Avx>::EntryType Vector<T, VectorAbi::Avx>::sum(MaskArgument m) const
{
AVX2::Vector<T> tmp(Vc::Zero);
tmp(m) = *this;
return tmp.sum();
}
namespace Detail
{
Vc_INTRINSIC Vc_CONST __m256 exponent(__m256 v)
{
using namespace AVX;
__m128i tmp0 = _mm_srli_epi32(avx_cast<__m128i>(v), 23);
__m128i tmp1 = _mm_srli_epi32(avx_cast<__m128i>(hi128(v)), 23);
tmp0 = _mm_sub_epi32(tmp0, _mm_set1_epi32(0x7f));
tmp1 = _mm_sub_epi32(tmp1, _mm_set1_epi32(0x7f));
return _mm256_cvtepi32_ps(concat(tmp0, tmp1));
}
Vc_INTRINSIC Vc_CONST __m256d exponent(__m256d v)
{
using namespace AVX;
__m128i tmp0 = _mm_srli_epi64(avx_cast<__m128i>(v), 52);
__m128i tmp1 = _mm_srli_epi64(avx_cast<__m128i>(hi128(v)), 52);
tmp0 = _mm_sub_epi32(tmp0, _mm_set1_epi32(0x3ff));
tmp1 = _mm_sub_epi32(tmp1, _mm_set1_epi32(0x3ff));
return _mm256_cvtepi32_pd(avx_cast<__m128i>(Mem::shuffle<X0, X2, Y0, Y2>(avx_cast<__m128>(tmp0), avx_cast<__m128>(tmp1))));
}
}
Vc_INTRINSIC Vc_CONST AVX2::float_v exponent(AVX2::float_v x)
{
using Detail::operator>=;
Vc_ASSERT((x >= x.Zero()).isFull());
return Detail::exponent(x.data());
}
Vc_INTRINSIC Vc_CONST AVX2::double_v exponent(AVX2::double_v x)
{
using Detail::operator>=;
Vc_ASSERT((x >= x.Zero()).isFull());
return Detail::exponent(x.data());
}
static Vc_ALWAYS_INLINE __m256i _doRandomStep()
{
using Detail::operator*;
using Detail::operator+;
#ifdef Vc_IMPL_AVX2
using AVX2::uint_v;
uint_v state0(&Common::RandomState[0]);
uint_v state1(&Common::RandomState[uint_v::Size]);
(state1 * uint_v(0xdeece66du) + uint_v(11)).store(&Common::RandomState[uint_v::Size]);
uint_v(Detail::xor_((state0 * uint_v(0xdeece66du) + uint_v(11)).data(),
_mm256_srli_epi32(state1.data(), 16)))
.store(&Common::RandomState[0]);
return state0.data();
#else
using SSE::uint_v;
uint_v state0(&Common::RandomState[0]);
uint_v state1(&Common::RandomState[uint_v::Size]);
uint_v state2(&Common::RandomState[2 * uint_v::Size]);
uint_v state3(&Common::RandomState[3 * uint_v::Size]);
(state2 * uint_v(0xdeece66du) + uint_v(11))
.store(&Common::RandomState[2 * uint_v::Size]);
(state3 * uint_v(0xdeece66du) + uint_v(11))
.store(&Common::RandomState[3 * uint_v::Size]);
uint_v(Detail::xor_((state0 * uint_v(0xdeece66du) + uint_v(11)).data(),
_mm_srli_epi32(state2.data(), 16)))
.store(&Common::RandomState[0]);
uint_v(Detail::xor_((state1 * uint_v(0xdeece66du) + uint_v(11)).data(),
_mm_srli_epi32(state3.data(), 16)))
.store(&Common::RandomState[uint_v::Size]);
return AVX::concat(state0.data(), state1.data());
#endif
}
#ifdef Vc_IMPL_AVX2
template<typename T> Vc_ALWAYS_INLINE AVX2::Vector<T> Vector<T, VectorAbi::Avx>::Random()
{
return {_doRandomStep()};
}
#endif
template <> Vc_ALWAYS_INLINE AVX2::float_v AVX2::float_v::Random()
{
return HT::sub(Detail::or_(_cast(AVX::srli_epi32<2>(_doRandomStep())), HT::one()),
HT::one());
}
template<> Vc_ALWAYS_INLINE AVX2::double_v AVX2::double_v::Random()
{
const __m256i state = Detail::load(&Common::RandomState[0], Vc::Aligned,
Detail::LoadTag<__m256i, int>());
for (size_t k = 0; k < 8; k += 2) {
typedef unsigned long long uint64 Vc_MAY_ALIAS;
const uint64 stateX = *aliasing_cast<uint64>(&Common::RandomState[k]);
*aliasing_cast<uint64>(&Common::RandomState[k]) = (stateX * 0x5deece66dull + 11);
}
return HT::sub(Detail::or_(_cast(AVX::srli_epi64<12>(state)), HT::one()), HT::one());
}
template<typename T> Vc_INTRINSIC AVX2::Vector<T> Vector<T, VectorAbi::Avx>::shifted(int amount) const
{
return Detail::shifted<EntryType>(d.v(), amount);
}
template <typename VectorType>
Vc_INTRINSIC Vc_CONST VectorType shifted_shortcut(VectorType left, VectorType right, Common::WidthT<__m128>)
{
return Mem::shuffle<X2, X3, Y0, Y1>(left, right);
}
template <typename VectorType>
Vc_INTRINSIC Vc_CONST VectorType shifted_shortcut(VectorType left, VectorType right, Common::WidthT<__m256>)
{
return Mem::shuffle128<X1, Y0>(left, right);
}
template<typename T> Vc_INTRINSIC AVX2::Vector<T> Vector<T, VectorAbi::Avx>::shifted(int amount, Vector shiftIn) const
{
#ifdef __GNUC__
if (__builtin_constant_p(amount)) {
const __m256i a = AVX::avx_cast<__m256i>(d.v());
const __m256i b = AVX::avx_cast<__m256i>(shiftIn.d.v());
if (amount * 2 == int(Size)) {
return shifted_shortcut(d.v(), shiftIn.d.v(), WidthT());
}
if (amount * 2 == -int(Size)) {
return shifted_shortcut(shiftIn.d.v(), d.v(), WidthT());
}
switch (amount) {
case 1:
return AVX::avx_cast<VectorType>(
#ifdef Vc_IMPL_AVX2
_mm256_alignr_epi8(_mm256_permute2x128_si256(a, b, 0x21), a,
sizeof(EntryType))
#else
AVX::concat(
_mm_alignr_epi8(AVX::hi128(a), AVX::lo128(a), sizeof(EntryType)),
_mm_alignr_epi8(AVX::lo128(b), AVX::hi128(a), sizeof(EntryType)))
#endif
);
case 2:
return AVX::avx_cast<VectorType>(
#ifdef Vc_IMPL_AVX2
_mm256_alignr_epi8(_mm256_permute2x128_si256(a, b, 0x21), a,
2 * sizeof(EntryType))
#else
AVX::concat(
_mm_alignr_epi8(AVX::hi128(a), AVX::lo128(a), 2 * sizeof(EntryType)),
_mm_alignr_epi8(AVX::lo128(b), AVX::hi128(a), 2 * sizeof(EntryType)))
#endif
);
case 3:
if (6u < Size) {
return AVX::avx_cast<VectorType>(
#ifdef Vc_IMPL_AVX2
_mm256_alignr_epi8(_mm256_permute2x128_si256(a, b, 0x21), a,
3 * sizeof(EntryType))
#else
AVX::concat(_mm_alignr_epi8(AVX::hi128(a), AVX::lo128(a),
3 * sizeof(EntryType)),
_mm_alignr_epi8(AVX::lo128(b), AVX::hi128(a),
3 * sizeof(EntryType)))
#endif
);
}
}
}
#endif
using Detail::operator|;
return shifted(amount) | (amount > 0 ?
shiftIn.shifted(amount - Size) :
shiftIn.shifted(Size + amount));
}
template<typename T> Vc_INTRINSIC AVX2::Vector<T> Vector<T, VectorAbi::Avx>::rotated(int amount) const
{
return Detail::rotated<EntryType, size()>(d.v(), amount);
}
template <typename T>
Vc_ALWAYS_INLINE Vc_PURE Vector<T, VectorAbi::Avx> Vector<T, VectorAbi::Avx>::sorted()
const
{
return Detail::sorted(*this);
}
template <> Vc_INTRINSIC AVX2::double_v AVX2::double_v::interleaveLow(AVX2::double_v x) const
{
return Mem::shuffle128<X0, Y0>(_mm256_unpacklo_pd(data(), x.data()),
_mm256_unpackhi_pd(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::double_v AVX2::double_v::interleaveHigh(AVX2::double_v x) const
{
return Mem::shuffle128<X1, Y1>(_mm256_unpacklo_pd(data(), x.data()),
_mm256_unpackhi_pd(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::float_v AVX2::float_v::interleaveLow(AVX2::float_v x) const
{
return Mem::shuffle128<X0, Y0>(_mm256_unpacklo_ps(data(), x.data()),
_mm256_unpackhi_ps(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::float_v AVX2::float_v::interleaveHigh(AVX2::float_v x) const
{
return Mem::shuffle128<X1, Y1>(_mm256_unpacklo_ps(data(), x.data()),
_mm256_unpackhi_ps(data(), x.data()));
}
#ifdef Vc_IMPL_AVX2
template <> Vc_INTRINSIC AVX2::int_v AVX2::int_v::interleaveLow ( AVX2::int_v x) const {
return Mem::shuffle128<X0, Y0>(_mm256_unpacklo_epi32(data(), x.data()),
_mm256_unpackhi_epi32(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::int_v AVX2::int_v::interleaveHigh( AVX2::int_v x) const {
return Mem::shuffle128<X1, Y1>(_mm256_unpacklo_epi32(data(), x.data()),
_mm256_unpackhi_epi32(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::uint_v AVX2::uint_v::interleaveLow ( AVX2::uint_v x) const {
return Mem::shuffle128<X0, Y0>(_mm256_unpacklo_epi32(data(), x.data()),
_mm256_unpackhi_epi32(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::uint_v AVX2::uint_v::interleaveHigh( AVX2::uint_v x) const {
return Mem::shuffle128<X1, Y1>(_mm256_unpacklo_epi32(data(), x.data()),
_mm256_unpackhi_epi32(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::short_v AVX2::short_v::interleaveLow ( AVX2::short_v x) const {
return Mem::shuffle128<X0, Y0>(_mm256_unpacklo_epi16(data(), x.data()),
_mm256_unpackhi_epi16(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::short_v AVX2::short_v::interleaveHigh( AVX2::short_v x) const {
return Mem::shuffle128<X1, Y1>(_mm256_unpacklo_epi16(data(), x.data()),
_mm256_unpackhi_epi16(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::ushort_v AVX2::ushort_v::interleaveLow (AVX2::ushort_v x) const {
return Mem::shuffle128<X0, Y0>(_mm256_unpacklo_epi16(data(), x.data()),
_mm256_unpackhi_epi16(data(), x.data()));
}
template <> Vc_INTRINSIC AVX2::ushort_v AVX2::ushort_v::interleaveHigh(AVX2::ushort_v x) const {
return Mem::shuffle128<X1, Y1>(_mm256_unpacklo_epi16(data(), x.data()),
_mm256_unpackhi_epi16(data(), x.data()));
}
#endif
template <> Vc_INTRINSIC Vc_PURE AVX2::double_v AVX2::double_v::operator[](Permutation::ReversedTag) const
{
return Mem::permute128<X1, X0>(Mem::permute<X1, X0, X3, X2>(d.v()));
}
template <> Vc_INTRINSIC Vc_PURE AVX2::float_v AVX2::float_v::operator[](Permutation::ReversedTag) const
{
return Mem::permute128<X1, X0>(Mem::permute<X3, X2, X1, X0>(d.v()));
}
#ifdef Vc_IMPL_AVX2
template <>
Vc_INTRINSIC Vc_PURE AVX2::int_v AVX2::int_v::operator[](Permutation::ReversedTag) const
{
return Mem::permute128<X1, X0>(Mem::permute<X3, X2, X1, X0>(d.v()));
}
template <>
Vc_INTRINSIC Vc_PURE AVX2::uint_v AVX2::uint_v::operator[](Permutation::ReversedTag) const
{
return Mem::permute128<X1, X0>(Mem::permute<X3, X2, X1, X0>(d.v()));
}
template <>
Vc_INTRINSIC Vc_PURE AVX2::short_v AVX2::short_v::operator[](
Permutation::ReversedTag) const
{
return Mem::permute128<X1, X0>(AVX::avx_cast<__m256i>(Mem::shuffle<X1, Y0, X3, Y2>(
AVX::avx_cast<__m256d>(Mem::permuteHi<X7, X6, X5, X4>(d.v())),
AVX::avx_cast<__m256d>(Mem::permuteLo<X3, X2, X1, X0>(d.v())))));
}
template <>
Vc_INTRINSIC Vc_PURE AVX2::ushort_v AVX2::ushort_v::operator[](
Permutation::ReversedTag) const
{
return Mem::permute128<X1, X0>(AVX::avx_cast<__m256i>(Mem::shuffle<X1, Y0, X3, Y2>(
AVX::avx_cast<__m256d>(Mem::permuteHi<X7, X6, X5, X4>(d.v())),
AVX::avx_cast<__m256d>(Mem::permuteLo<X3, X2, X1, X0>(d.v())))));
}
#endif
template <> Vc_INTRINSIC AVX2::float_v Vector<float, VectorAbi::Avx>::operator[](const IndexType & ) const
{
return *this;
#ifdef Vc_IMPL_AVX2
#else
#endif
}
template <typename T>
Vc_INTRINSIC Vc_PURE Vector<T, VectorAbi::Avx> Vector<T, VectorAbi::Avx>::reversed() const
{
return (*this)[Permutation::Reversed];
}
template <> template <int Index> Vc_INTRINSIC AVX2::float_v AVX2::float_v::broadcast() const
{
constexpr VecPos Inner = static_cast<VecPos>(Index & 0x3);
constexpr VecPos Outer = static_cast<VecPos>((Index & 0x4) / 4);
return Mem::permute<Inner, Inner, Inner, Inner>(Mem::permute128<Outer, Outer>(d.v()));
}
template <> template <int Index> Vc_INTRINSIC AVX2::double_v AVX2::double_v::broadcast() const
{
constexpr VecPos Inner = static_cast<VecPos>(Index & 0x1);
constexpr VecPos Outer = static_cast<VecPos>((Index & 0x2) / 2);
return Mem::permute<Inner, Inner>(Mem::permute128<Outer, Outer>(d.v()));
}
}
#ifndef VC_AVX_SIMD_CAST_H_
#define VC_AVX_SIMD_CAST_H_ 
#ifndef VC_AVX_VECTOR_H_
#error "Vc/avx/vector.h needs to be included before Vc/avx/simd_cast.h"
#endif
namespace Vc_VERSIONED_NAMESPACE
{
#define Vc_SIMD_CAST_AVX_1(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
AVX2::from_ x, enable_if<std::is_same<To, AVX2::to_>::value> = nullarg)
#define Vc_SIMD_CAST_AVX_2(from_,to_) \
static_assert(AVX2::from_::size() * 2 <= AVX2::to_::size(), \
"this type combination is wrong"); \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
AVX2::from_ x0, AVX2::from_ x1, \
enable_if<std::is_same<To, AVX2::to_>::value> = nullarg)
#define Vc_SIMD_CAST_AVX_3(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
AVX2::from_ x0, AVX2::from_ x1, AVX2::from_ x2, \
enable_if<std::is_same<To, AVX2::to_>::value> = nullarg)
#define Vc_SIMD_CAST_AVX_4(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
AVX2::from_ x0, AVX2::from_ x1, AVX2::from_ x2, AVX2::from_ x3, \
enable_if<std::is_same<To, AVX2::to_>::value> = nullarg)
#define Vc_SIMD_CAST_1(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x, enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_2(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_3(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, from_ x2, enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_4(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, from_ x2, from_ x3, \
enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_5(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, \
enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_6(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, from_ x5, \
enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_7(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, from_ x5, from_ x6, \
enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_8(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, from_ x5, from_ x6, from_ x7, \
enable_if<std::is_same<To, to_>::value> = nullarg)
#define Vc_SIMD_CAST_OFFSET(from_,to_,offset_) \
static_assert(from_::size() >= to_::size() * (offset_ + 1), \
"this offset cannot exist for this type combination"); \
template <typename To, int offset> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x, \
enable_if<(offset == offset_ && std::is_same<To, to_>::value)> = nullarg)
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(From x, enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)> =
nullarg);
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To simd_cast(
From x0, From x1,
enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)> = nullarg);
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To simd_cast(
From x0, From x1, From x2,
enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)> = nullarg);
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To simd_cast(
From x0, From x1, From x2, From x3,
enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)> = nullarg);
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To simd_cast(
From x0, From x1, From x2, From x3, From x4, From x5, From x6, From x7,
enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)> = nullarg);
Vc_SIMD_CAST_AVX_1( float_v, double_v);
Vc_SIMD_CAST_AVX_1(double_v, float_v);
Vc_SIMD_CAST_AVX_2(double_v, float_v);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_1( int_v, double_v);
Vc_SIMD_CAST_AVX_1( uint_v, double_v);
Vc_SIMD_CAST_AVX_1( short_v, double_v);
Vc_SIMD_CAST_AVX_1(ushort_v, double_v);
Vc_SIMD_CAST_AVX_1( int_v, float_v);
Vc_SIMD_CAST_AVX_1( uint_v, float_v);
Vc_SIMD_CAST_AVX_1( short_v, float_v);
Vc_SIMD_CAST_AVX_1(ushort_v, float_v);
Vc_SIMD_CAST_AVX_1(double_v, int_v);
Vc_SIMD_CAST_AVX_1( float_v, int_v);
Vc_SIMD_CAST_AVX_1( uint_v, int_v);
Vc_SIMD_CAST_AVX_1( short_v, int_v);
Vc_SIMD_CAST_AVX_1(ushort_v, int_v);
Vc_SIMD_CAST_AVX_2(double_v, int_v);
Vc_SIMD_CAST_AVX_1(double_v, uint_v);
Vc_SIMD_CAST_AVX_1( float_v, uint_v);
Vc_SIMD_CAST_AVX_1( int_v, uint_v);
Vc_SIMD_CAST_AVX_1( short_v, uint_v);
Vc_SIMD_CAST_AVX_1(ushort_v, uint_v);
Vc_SIMD_CAST_AVX_2(double_v, uint_v);
Vc_SIMD_CAST_AVX_1(double_v, short_v);
Vc_SIMD_CAST_AVX_1( float_v, short_v);
Vc_SIMD_CAST_AVX_1( int_v, short_v);
Vc_SIMD_CAST_AVX_1( uint_v, short_v);
Vc_SIMD_CAST_AVX_1(ushort_v, short_v);
Vc_SIMD_CAST_AVX_2(double_v, short_v);
Vc_SIMD_CAST_AVX_2( float_v, short_v);
Vc_SIMD_CAST_AVX_2( int_v, short_v);
Vc_SIMD_CAST_AVX_2( uint_v, short_v);
Vc_SIMD_CAST_AVX_3(double_v, short_v);
Vc_SIMD_CAST_AVX_4(double_v, short_v);
Vc_SIMD_CAST_AVX_1(double_v, ushort_v);
Vc_SIMD_CAST_AVX_1( float_v, ushort_v);
Vc_SIMD_CAST_AVX_1( int_v, ushort_v);
Vc_SIMD_CAST_AVX_1( uint_v, ushort_v);
Vc_SIMD_CAST_AVX_1( short_v, ushort_v);
Vc_SIMD_CAST_AVX_2(double_v, ushort_v);
Vc_SIMD_CAST_AVX_2( float_v, ushort_v);
Vc_SIMD_CAST_AVX_2( int_v, ushort_v);
Vc_SIMD_CAST_AVX_2( uint_v, ushort_v);
Vc_SIMD_CAST_AVX_3(double_v, ushort_v);
Vc_SIMD_CAST_AVX_4(double_v, ushort_v);
#endif
Vc_SIMD_CAST_1(SSE::double_v, AVX2::double_v);
Vc_SIMD_CAST_1(SSE:: float_v, AVX2::double_v);
Vc_SIMD_CAST_1(SSE:: int_v, AVX2::double_v);
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2::double_v);
Vc_SIMD_CAST_1(SSE:: short_v, AVX2::double_v);
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2::double_v);
Vc_SIMD_CAST_1(SSE::double_v, AVX2:: float_v);
Vc_SIMD_CAST_1(SSE:: float_v, AVX2:: float_v);
Vc_SIMD_CAST_1(SSE:: int_v, AVX2:: float_v);
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2:: float_v);
Vc_SIMD_CAST_1(SSE:: short_v, AVX2:: float_v);
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2:: float_v);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(SSE::double_v, AVX2:: int_v);
Vc_SIMD_CAST_1(SSE::double_v, AVX2:: uint_v);
Vc_SIMD_CAST_1(SSE::double_v, AVX2:: short_v);
Vc_SIMD_CAST_1(SSE::double_v, AVX2::ushort_v);
Vc_SIMD_CAST_1(SSE:: float_v, AVX2:: int_v);
Vc_SIMD_CAST_1(SSE:: float_v, AVX2:: uint_v);
Vc_SIMD_CAST_1(SSE:: float_v, AVX2:: short_v);
Vc_SIMD_CAST_1(SSE:: float_v, AVX2::ushort_v);
Vc_SIMD_CAST_1(SSE:: int_v, AVX2:: int_v);
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2:: int_v);
Vc_SIMD_CAST_1(SSE:: short_v, AVX2:: int_v);
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2:: int_v);
Vc_SIMD_CAST_1(SSE:: int_v, AVX2:: uint_v);
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2:: uint_v);
Vc_SIMD_CAST_1(SSE:: short_v, AVX2:: uint_v);
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2:: uint_v);
Vc_SIMD_CAST_1(SSE:: int_v, AVX2:: short_v);
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2:: short_v);
Vc_SIMD_CAST_1(SSE:: short_v, AVX2:: short_v);
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2:: short_v);
Vc_SIMD_CAST_1(SSE:: int_v, AVX2::ushort_v);
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2::ushort_v);
Vc_SIMD_CAST_1(SSE:: short_v, AVX2::ushort_v);
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2::ushort_v);
#endif
Vc_SIMD_CAST_2(SSE::double_v, AVX2::double_v);
Vc_SIMD_CAST_2(SSE::double_v, AVX2:: float_v);
Vc_SIMD_CAST_2(SSE:: float_v, AVX2:: float_v);
Vc_SIMD_CAST_2(SSE:: int_v, AVX2:: float_v);
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2:: float_v);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_2(SSE::double_v, AVX2:: int_v);
Vc_SIMD_CAST_2(SSE::double_v, AVX2:: uint_v);
Vc_SIMD_CAST_2(SSE::double_v, AVX2:: short_v);
Vc_SIMD_CAST_2(SSE::double_v, AVX2::ushort_v);
Vc_SIMD_CAST_2(SSE:: float_v, AVX2:: int_v);
Vc_SIMD_CAST_2(SSE:: float_v, AVX2:: uint_v);
Vc_SIMD_CAST_2(SSE:: float_v, AVX2:: short_v);
Vc_SIMD_CAST_2(SSE:: float_v, AVX2::ushort_v);
Vc_SIMD_CAST_2(SSE:: int_v, AVX2:: int_v);
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2:: int_v);
Vc_SIMD_CAST_2(SSE:: int_v, AVX2:: uint_v);
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2:: uint_v);
Vc_SIMD_CAST_2(SSE:: int_v, AVX2:: short_v);
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2:: short_v);
Vc_SIMD_CAST_2(SSE:: short_v, AVX2:: short_v);
Vc_SIMD_CAST_2(SSE::ushort_v, AVX2:: short_v);
Vc_SIMD_CAST_2(SSE:: int_v, AVX2::ushort_v);
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2::ushort_v);
Vc_SIMD_CAST_2(SSE:: short_v, AVX2::ushort_v);
Vc_SIMD_CAST_2(SSE::ushort_v, AVX2::ushort_v);
#endif
Vc_SIMD_CAST_3(SSE::double_v, AVX2:: float_v);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_3(SSE::double_v, AVX2:: int_v);
Vc_SIMD_CAST_3(SSE::double_v, AVX2:: uint_v);
Vc_SIMD_CAST_3(SSE::double_v, AVX2:: short_v);
Vc_SIMD_CAST_3(SSE::double_v, AVX2::ushort_v);
Vc_SIMD_CAST_3(SSE:: float_v, AVX2:: short_v);
Vc_SIMD_CAST_3(SSE:: float_v, AVX2::ushort_v);
Vc_SIMD_CAST_3(SSE:: int_v, AVX2:: short_v);
Vc_SIMD_CAST_3(SSE:: uint_v, AVX2:: short_v);
Vc_SIMD_CAST_3(SSE:: int_v, AVX2::ushort_v);
Vc_SIMD_CAST_3(SSE:: uint_v, AVX2::ushort_v);
#endif
Vc_SIMD_CAST_4(SSE::double_v, AVX2:: float_v);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_4(SSE::double_v, AVX2:: int_v);
Vc_SIMD_CAST_4(SSE::double_v, AVX2:: uint_v);
Vc_SIMD_CAST_4(SSE::double_v, AVX2:: short_v);
Vc_SIMD_CAST_4(SSE::double_v, AVX2::ushort_v);
Vc_SIMD_CAST_4(SSE:: float_v, AVX2:: short_v);
Vc_SIMD_CAST_4(SSE:: float_v, AVX2::ushort_v);
Vc_SIMD_CAST_4(SSE:: int_v, AVX2:: short_v);
Vc_SIMD_CAST_4(SSE:: uint_v, AVX2:: short_v);
Vc_SIMD_CAST_4(SSE:: int_v, AVX2::ushort_v);
Vc_SIMD_CAST_4(SSE:: uint_v, AVX2::ushort_v);
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_5(SSE::double_v, AVX2:: short_v);
Vc_SIMD_CAST_5(SSE::double_v, AVX2::ushort_v);
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_6(SSE::double_v, AVX2:: short_v);
Vc_SIMD_CAST_6(SSE::double_v, AVX2::ushort_v);
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_7(SSE::double_v, AVX2:: short_v);
Vc_SIMD_CAST_7(SSE::double_v, AVX2::ushort_v);
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_8(SSE::double_v, AVX2:: short_v);
Vc_SIMD_CAST_8(SSE::double_v, AVX2::ushort_v);
#endif
Vc_SIMD_CAST_1(AVX2::double_v, SSE::double_v);
Vc_SIMD_CAST_1(AVX2::double_v, SSE:: float_v);
Vc_SIMD_CAST_1(AVX2::double_v, SSE:: int_v);
Vc_SIMD_CAST_1(AVX2::double_v, SSE:: uint_v);
Vc_SIMD_CAST_1(AVX2::double_v, SSE:: short_v);
Vc_SIMD_CAST_1(AVX2::double_v, SSE::ushort_v);
Vc_SIMD_CAST_1(AVX2:: float_v, SSE::double_v);
Vc_SIMD_CAST_1(AVX2:: float_v, SSE:: float_v);
Vc_SIMD_CAST_1(AVX2:: float_v, SSE:: int_v);
Vc_SIMD_CAST_1(AVX2:: float_v, SSE:: uint_v);
Vc_SIMD_CAST_1(AVX2:: float_v, SSE:: short_v);
Vc_SIMD_CAST_1(AVX2:: float_v, SSE::ushort_v);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(AVX2:: int_v, SSE::double_v);
Vc_SIMD_CAST_1(AVX2:: int_v, SSE:: float_v);
Vc_SIMD_CAST_1(AVX2:: int_v, SSE:: uint_v);
Vc_SIMD_CAST_1(AVX2:: int_v, SSE:: int_v);
Vc_SIMD_CAST_1(AVX2:: int_v, SSE:: short_v);
Vc_SIMD_CAST_1(AVX2:: int_v, SSE::ushort_v);
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE::double_v);
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE:: float_v);
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE:: int_v);
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE:: uint_v);
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE:: short_v);
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE::ushort_v);
Vc_SIMD_CAST_1(AVX2:: short_v, SSE::double_v);
Vc_SIMD_CAST_1(AVX2:: short_v, SSE:: float_v);
Vc_SIMD_CAST_1(AVX2:: short_v, SSE:: int_v);
Vc_SIMD_CAST_1(AVX2:: short_v, SSE:: uint_v);
Vc_SIMD_CAST_1(AVX2:: short_v, SSE:: short_v);
Vc_SIMD_CAST_1(AVX2:: short_v, SSE::ushort_v);
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE::double_v);
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE:: float_v);
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE:: int_v);
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE:: uint_v);
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE:: short_v);
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE::ushort_v);
#endif
Vc_SIMD_CAST_2(AVX2::double_v, SSE:: short_v);
Vc_SIMD_CAST_2(AVX2::double_v, SSE::ushort_v);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::double_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::float_v>::value> = nullarg);
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::double_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::float_v>::value> = nullarg);
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::double_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::float_v>::value> = nullarg);
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::double_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::float_v>::value> = nullarg);
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::float_v>::value> = nullarg);
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::float_v>::value> = nullarg);
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::float_v>::value> = nullarg);
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::float_v>::value> = nullarg);
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::int_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::uint_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13, Scalar::Vector<T> x14,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13, Scalar::Vector<T> x14,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13, Scalar::Vector<T> x14,
Scalar::Vector<T> x15,
enable_if<std::is_same<Return, AVX2::short_v>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13, Scalar::Vector<T> x14,
Scalar::Vector<T> x15,
enable_if<std::is_same<Return, AVX2::ushort_v>::value> = nullarg);
#endif
template <typename To, typename FromT>
Vc_INTRINSIC Vc_CONST To simd_cast(AVX2::Vector<FromT> x,
enable_if<Scalar::is_vector<To>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(const AVX2::Mask<T> &k, enable_if<AVX2::is_mask<Return>::value> = nullarg);
Vc_SIMD_CAST_AVX_2(double_m, float_m);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_2(double_m, int_m);
Vc_SIMD_CAST_AVX_2(double_m, uint_m);
Vc_SIMD_CAST_AVX_2(double_m, short_m);
Vc_SIMD_CAST_AVX_2(double_m, ushort_m);
Vc_SIMD_CAST_AVX_2( float_m, short_m);
Vc_SIMD_CAST_AVX_2( float_m, ushort_m);
Vc_SIMD_CAST_AVX_2( int_m, short_m);
Vc_SIMD_CAST_AVX_2( int_m, ushort_m);
Vc_SIMD_CAST_AVX_2( uint_m, short_m);
Vc_SIMD_CAST_AVX_2( uint_m, ushort_m);
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_4(double_m, short_m);
Vc_SIMD_CAST_AVX_4(double_m, ushort_m);
#endif
Vc_SIMD_CAST_1(SSE::double_m, AVX2::double_m);
Vc_SIMD_CAST_1(SSE::double_m, AVX2:: float_m);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(SSE::double_m, AVX2:: int_m);
Vc_SIMD_CAST_1(SSE::double_m, AVX2:: uint_m);
Vc_SIMD_CAST_1(SSE::double_m, AVX2:: short_m);
Vc_SIMD_CAST_1(SSE::double_m, AVX2::ushort_m);
#endif
Vc_SIMD_CAST_1(SSE:: float_m, AVX2::double_m);
Vc_SIMD_CAST_1(SSE:: int_m, AVX2::double_m);
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2::double_m);
Vc_SIMD_CAST_1(SSE:: short_m, AVX2::double_m);
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2::double_m);
Vc_SIMD_CAST_1(SSE:: float_m, AVX2:: float_m);
Vc_SIMD_CAST_1(SSE:: int_m, AVX2:: float_m);
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2:: float_m);
Vc_SIMD_CAST_1(SSE:: short_m, AVX2:: float_m);
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2:: float_m);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(SSE:: float_m, AVX2:: int_m);
Vc_SIMD_CAST_1(SSE:: float_m, AVX2:: uint_m);
Vc_SIMD_CAST_1(SSE:: int_m, AVX2:: int_m);
Vc_SIMD_CAST_1(SSE:: int_m, AVX2:: uint_m);
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2:: int_m);
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2:: uint_m);
Vc_SIMD_CAST_1(SSE:: float_m, AVX2:: short_m);
Vc_SIMD_CAST_1(SSE:: int_m, AVX2:: short_m);
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2:: short_m);
Vc_SIMD_CAST_1(SSE:: short_m, AVX2:: short_m);
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2:: short_m);
Vc_SIMD_CAST_1(SSE:: float_m, AVX2::ushort_m);
Vc_SIMD_CAST_1(SSE:: int_m, AVX2::ushort_m);
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2::ushort_m);
Vc_SIMD_CAST_1(SSE:: short_m, AVX2::ushort_m);
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2::ushort_m);
Vc_SIMD_CAST_1(SSE:: short_m, AVX2:: int_m);
Vc_SIMD_CAST_1(SSE:: short_m, AVX2:: uint_m);
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2:: int_m);
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2:: uint_m);
#endif
Vc_SIMD_CAST_2(SSE::double_m, AVX2::double_m);
Vc_SIMD_CAST_2(SSE::double_m, AVX2:: float_m);
Vc_SIMD_CAST_2(SSE:: float_m, AVX2:: float_m);
Vc_SIMD_CAST_2(SSE:: int_m, AVX2:: float_m);
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2:: float_m);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_2(SSE::double_m, AVX2:: int_m);
Vc_SIMD_CAST_2(SSE::double_m, AVX2:: uint_m);
Vc_SIMD_CAST_2(SSE::double_m, AVX2:: short_m);
Vc_SIMD_CAST_2(SSE::double_m, AVX2::ushort_m);
Vc_SIMD_CAST_2(SSE:: float_m, AVX2:: int_m);
Vc_SIMD_CAST_2(SSE:: float_m, AVX2:: uint_m);
Vc_SIMD_CAST_2(SSE:: float_m, AVX2:: short_m);
Vc_SIMD_CAST_2(SSE:: float_m, AVX2::ushort_m);
Vc_SIMD_CAST_2(SSE:: int_m, AVX2:: int_m);
Vc_SIMD_CAST_2(SSE:: int_m, AVX2:: uint_m);
Vc_SIMD_CAST_2(SSE:: int_m, AVX2:: short_m);
Vc_SIMD_CAST_2(SSE:: int_m, AVX2::ushort_m);
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2:: int_m);
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2:: uint_m);
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2:: short_m);
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2::ushort_m);
Vc_SIMD_CAST_2(SSE:: short_m, AVX2:: short_m);
Vc_SIMD_CAST_2(SSE:: short_m, AVX2::ushort_m);
Vc_SIMD_CAST_2(SSE::ushort_m, AVX2:: short_m);
Vc_SIMD_CAST_2(SSE::ushort_m, AVX2::ushort_m);
#endif
Vc_SIMD_CAST_4(SSE::double_m, AVX2:: float_m);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_4(SSE::double_m, AVX2:: int_m);
Vc_SIMD_CAST_4(SSE::double_m, AVX2:: uint_m);
Vc_SIMD_CAST_4(SSE::double_m, AVX2:: short_m);
Vc_SIMD_CAST_4(SSE::double_m, AVX2::ushort_m);
Vc_SIMD_CAST_4(SSE:: float_m, AVX2:: short_m);
Vc_SIMD_CAST_4(SSE:: float_m, AVX2::ushort_m);
Vc_SIMD_CAST_4(SSE:: int_m, AVX2:: short_m);
Vc_SIMD_CAST_4(SSE:: int_m, AVX2::ushort_m);
Vc_SIMD_CAST_4(SSE:: uint_m, AVX2:: short_m);
Vc_SIMD_CAST_4(SSE:: uint_m, AVX2::ushort_m);
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> k,
enable_if<AVX2::is_mask<Return>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> k0, Scalar::Mask<T> k1,
enable_if<AVX2::is_mask<Return>::value> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(
Scalar::Mask<T> k0, Scalar::Mask<T> k1, Scalar::Mask<T> k2, Scalar::Mask<T> k3,
enable_if<(AVX2::is_mask<Return>::value && Return::Size >= 4)> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast(
Scalar::Mask<T> k0, Scalar::Mask<T> k1, Scalar::Mask<T> k2, Scalar::Mask<T> k3,
Scalar::Mask<T> k4, Scalar::Mask<T> k5, Scalar::Mask<T> k6, Scalar::Mask<T> k7,
enable_if<(AVX2::is_mask<Return>::value && Return::Size >= 8)> = nullarg);
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> k0, Scalar::Mask<T> k1, Scalar::Mask<T> k2, Scalar::Mask<T> k3,
Scalar::Mask<T> k4, Scalar::Mask<T> k5, Scalar::Mask<T> k6, Scalar::Mask<T> k7,
Scalar::Mask<T> k8, Scalar::Mask<T> k9, Scalar::Mask<T> k10,
Scalar::Mask<T> k11, Scalar::Mask<T> k12, Scalar::Mask<T> k13,
Scalar::Mask<T> k14, Scalar::Mask<T> k15,
enable_if<(AVX2::is_mask<Return>::value && Return::Size >= 16)> = nullarg);
Vc_SIMD_CAST_1(AVX2::double_m, SSE::double_m);
Vc_SIMD_CAST_1(AVX2::double_m, SSE:: float_m);
Vc_SIMD_CAST_1(AVX2::double_m, SSE:: int_m);
Vc_SIMD_CAST_1(AVX2::double_m, SSE:: uint_m);
Vc_SIMD_CAST_1(AVX2::double_m, SSE:: short_m);
Vc_SIMD_CAST_1(AVX2::double_m, SSE::ushort_m);
Vc_SIMD_CAST_1(AVX2:: float_m, SSE::double_m);
Vc_SIMD_CAST_1(AVX2:: float_m, SSE:: float_m);
Vc_SIMD_CAST_1(AVX2:: float_m, SSE:: int_m);
Vc_SIMD_CAST_1(AVX2:: float_m, SSE:: uint_m);
Vc_SIMD_CAST_1(AVX2:: float_m, SSE:: short_m);
Vc_SIMD_CAST_1(AVX2:: float_m, SSE::ushort_m);
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(AVX2:: int_m, SSE::double_m);
Vc_SIMD_CAST_1(AVX2:: int_m, SSE:: float_m);
Vc_SIMD_CAST_1(AVX2:: int_m, SSE:: int_m);
Vc_SIMD_CAST_1(AVX2:: int_m, SSE:: uint_m);
Vc_SIMD_CAST_1(AVX2:: int_m, SSE:: short_m);
Vc_SIMD_CAST_1(AVX2:: int_m, SSE::ushort_m);
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE::double_m);
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE:: float_m);
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE:: int_m);
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE:: uint_m);
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE:: short_m);
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE::ushort_m);
Vc_SIMD_CAST_1(AVX2:: short_m, SSE::double_m);
Vc_SIMD_CAST_1(AVX2:: short_m, SSE:: float_m);
Vc_SIMD_CAST_1(AVX2:: short_m, SSE:: int_m);
Vc_SIMD_CAST_1(AVX2:: short_m, SSE:: uint_m);
Vc_SIMD_CAST_1(AVX2:: short_m, SSE:: short_m);
Vc_SIMD_CAST_1(AVX2:: short_m, SSE::ushort_m);
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE::double_m);
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE:: float_m);
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE:: int_m);
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE:: uint_m);
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE:: short_m);
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE::ushort_m);
#endif
Vc_SIMD_CAST_2(AVX2::double_m, SSE:: short_m);
Vc_SIMD_CAST_2(AVX2::double_m, SSE::ushort_m);
template <typename To, typename FromT>
Vc_INTRINSIC Vc_CONST To simd_cast(AVX2::Mask<FromT> x,
enable_if<Scalar::is_mask<To>::value> = nullarg);
template <typename Return, int offset, typename From>
Vc_INTRINSIC Vc_CONST enable_if<
(offset == 0 &&
((AVX2::is_vector<From>::value && !Scalar::is_vector<Return>::value &&
Traits::is_simd_vector<Return>::value && !Traits::isSimdArray<Return>::value) ||
(AVX2::is_mask<From>::value && !Scalar::is_mask<Return>::value &&
Traits::is_simd_mask<Return>::value &&
!Traits::isSimdMaskArray<Return>::value))),
Return>
simd_cast(const From &x);
template <typename Return, int offset, typename From>
Vc_INTRINSIC Vc_CONST Return simd_cast(
const From &x,
enable_if<offset == 0 && ((SSE::is_vector<From>::value &&
AVX2::is_vector<Return>::value) ||
(SSE::is_mask<From>::value &&
AVX2::is_mask<Return>::value))> = nullarg);
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(AVX2::is_vector<Return>::value && offset != 0),
Return>
simd_cast(AVX2::Vector<T> x);
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0 && SSE::is_vector<Return>::value &&
sizeof(AVX2::Vector<T>) == 32),
Return>
simd_cast(AVX2::Vector<T> x);
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0 && SSE::is_vector<Return>::value &&
sizeof(AVX2::Vector<T>) == 16),
Return>
simd_cast(AVX2::Vector<T> x);
Vc_SIMD_CAST_OFFSET(SSE:: short_v, AVX2::double_v, 1);
Vc_SIMD_CAST_OFFSET(SSE::ushort_v, AVX2::double_v, 1);
Vc_SIMD_CAST_OFFSET(SSE:: short_m, AVX2::double_m, 1);
Vc_SIMD_CAST_OFFSET(SSE::ushort_m, AVX2::double_m, 1);
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0 && SSE::is_mask<Return>::value &&
sizeof(AVX2::Mask<T>) == 32),
Return>
simd_cast(AVX2::Mask<T> x);
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0 && SSE::is_mask<Return>::value &&
sizeof(AVX2::Mask<T>) == 16),
Return>
simd_cast(AVX2::Mask<T> x);
#undef Vc_SIMD_CAST_AVX_1
#define Vc_SIMD_CAST_AVX_1(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(AVX2::from_ x, \
enable_if<std::is_same<To, AVX2::to_>::value>)
#undef Vc_SIMD_CAST_AVX_2
#define Vc_SIMD_CAST_AVX_2(from_,to_) \
static_assert(AVX2::from_::size() * 2 <= AVX2::to_::size(), \
"this type combination is wrong"); \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(AVX2::from_ x0, AVX2::from_ x1, \
enable_if<std::is_same<To, AVX2::to_>::value>)
#undef Vc_SIMD_CAST_AVX_3
#define Vc_SIMD_CAST_AVX_3(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(AVX2::from_ x0, AVX2::from_ x1, AVX2::from_ x2, \
enable_if<std::is_same<To, AVX2::to_>::value>)
#undef Vc_SIMD_CAST_AVX_4
#define Vc_SIMD_CAST_AVX_4(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(AVX2::from_ x0, AVX2::from_ x1, AVX2::from_ x2, \
AVX2::from_ x3, \
enable_if<std::is_same<To, AVX2::to_>::value>)
#undef Vc_SIMD_CAST_1
#define Vc_SIMD_CAST_1(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x, enable_if<std::is_same<To, to_>::value>)
#undef Vc_SIMD_CAST_2
#define Vc_SIMD_CAST_2(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, \
enable_if<std::is_same<To, to_>::value>)
#undef Vc_SIMD_CAST_3
#define Vc_SIMD_CAST_3(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, from_ x2, \
enable_if<std::is_same<To, to_>::value>)
#undef Vc_SIMD_CAST_4
#define Vc_SIMD_CAST_4(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, from_ x2, from_ x3, \
enable_if<std::is_same<To, to_>::value>)
#undef Vc_SIMD_CAST_5
#define Vc_SIMD_CAST_5(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, \
enable_if<std::is_same<To, to_>::value>)
#undef Vc_SIMD_CAST_6
#define Vc_SIMD_CAST_6(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, \
from_ x5, \
enable_if<std::is_same<To, to_>::value>)
#undef Vc_SIMD_CAST_7
#define Vc_SIMD_CAST_7(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, \
from_ x5, from_ x6, \
enable_if<std::is_same<To, to_>::value>)
#undef Vc_SIMD_CAST_8
#define Vc_SIMD_CAST_8(from_,to_) \
template <typename To> \
Vc_INTRINSIC Vc_CONST To simd_cast(from_ x0, from_ x1, from_ x2, from_ x3, from_ x4, \
from_ x5, from_ x6, from_ x7, \
enable_if<std::is_same<To, to_>::value>)
#undef Vc_SIMD_CAST_OFFSET
#define Vc_SIMD_CAST_OFFSET(from_,to_,offset_) \
static_assert(from_::size() >= to_::size() * (offset_ + 1), \
"this offset cannot exist for this type combination"); \
template <typename To, int offset> \
Vc_INTRINSIC Vc_CONST To simd_cast( \
from_ x, enable_if<(offset == offset_ && std::is_same<To, to_>::value)>)
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(From x, enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)>)
{
return simd_cast<SSE::Vector<typename To::EntryType>>(x).data();
}
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(From x0, From x1,
enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)>)
{
return simd_cast<SSE::Vector<typename To::EntryType>>(x0, x1).data();
}
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(From x0, From x1, From x2,
enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)>)
{
return simd_cast<SSE::Vector<typename To::EntryType>>(x0, x1, x2).data();
}
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(From x0, From x1, From x2, From x3,
enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)>)
{
return simd_cast<SSE::Vector<typename To::EntryType>>(x0, x1, x2, x3).data();
}
template <typename To, typename From>
Vc_INTRINSIC Vc_CONST To
simd_cast(From x0, From x1, From x2, From x3, From x4, From x5, From x6, From x7,
enable_if<(AVX2::is_vector<To>::value && SSE::is_vector<From>::value &&
SSE::Vector<typename To::EntryType>::Size == To::Size)>)
{
return simd_cast<SSE::Vector<typename To::EntryType>>(x0, x1, x2, x3, x4, x5, x6, x7)
.data();
}
Vc_SIMD_CAST_AVX_1( float_v, double_v) { return _mm256_cvtps_pd(AVX::lo128(x.data())); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_1( int_v, double_v) { return AVX::convert< int, double>(AVX::lo128(x.data())); }
Vc_SIMD_CAST_AVX_1( uint_v, double_v) { return AVX::convert< uint, double>(AVX::lo128(x.data())); }
Vc_SIMD_CAST_AVX_1( short_v, double_v) { return AVX::convert< short, double>(AVX::lo128(x.data())); }
Vc_SIMD_CAST_AVX_1(ushort_v, double_v) { return AVX::convert<ushort, double>(AVX::lo128(x.data())); }
#endif
Vc_SIMD_CAST_AVX_1(double_v, float_v) { return AVX::zeroExtend(_mm256_cvtpd_ps(x.data())); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_1( int_v, float_v) { return AVX::convert< int, float>(x.data()); }
Vc_SIMD_CAST_AVX_1( uint_v, float_v) { return AVX::convert< uint, float>(x.data()); }
Vc_SIMD_CAST_AVX_1( short_v, float_v) { return AVX::convert< short, float>(AVX::lo128(x.data())); }
Vc_SIMD_CAST_AVX_1(ushort_v, float_v) { return AVX::convert<ushort, float>(AVX::lo128(x.data())); }
#endif
Vc_SIMD_CAST_AVX_2(double_v, float_v) { return AVX::concat(_mm256_cvtpd_ps(x0.data()), _mm256_cvtpd_ps(x1.data())); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_1(double_v, int_v) { return AVX::zeroExtend(_mm256_cvttpd_epi32(x.data())); }
Vc_SIMD_CAST_AVX_1( float_v, int_v) { return _mm256_cvttps_epi32(x.data()); }
Vc_SIMD_CAST_AVX_1( uint_v, int_v) { return x.data(); }
Vc_SIMD_CAST_AVX_1( short_v, int_v) {
const auto tmp = Mem::permute4x64<X0, X2, X1, X3>(x.data());
return _mm256_srai_epi32(_mm256_unpacklo_epi16(tmp, tmp), 16);
}
Vc_SIMD_CAST_AVX_1(ushort_v, int_v) {
const auto tmp = Mem::permute4x64<X0, X2, X1, X3>(x.data());
return _mm256_srli_epi32(_mm256_unpacklo_epi16(tmp, tmp), 16);
}
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_2(double_v, int_v) { return AVX::concat(_mm256_cvttpd_epi32(x0.data()), _mm256_cvttpd_epi32(x1.data())); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_1(double_v, uint_v) { return AVX::zeroExtend(AVX::convert<double, uint>(x.data())); }
Vc_SIMD_CAST_AVX_1( float_v, uint_v) {
return _mm256_blendv_epi8(
_mm256_cvttps_epi32(x.data()),
_mm256_add_epi32(
_mm256_cvttps_epi32(_mm256_sub_ps(x.data(), AVX::set2power31_ps())),
AVX::set2power31_epu32()),
_mm256_castps_si256(AVX::cmpge_ps(x.data(), AVX::set2power31_ps())));
}
Vc_SIMD_CAST_AVX_1( int_v, uint_v) { return x.data(); }
Vc_SIMD_CAST_AVX_1( short_v, uint_v) {
const auto tmp = Mem::permute4x64<X0, X2, X1, X3>(x.data());
return _mm256_srai_epi32(_mm256_unpacklo_epi16(tmp, tmp), 16);
}
Vc_SIMD_CAST_AVX_1(ushort_v, uint_v) {
const auto tmp = Mem::permute4x64<X0, X2, X1, X3>(x.data());
return _mm256_srli_epi32(_mm256_unpacklo_epi16(tmp, tmp), 16);
}
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_2(double_v, uint_v) { return AVX::concat(AVX::convert<double, uint>(x0.data()), AVX::convert<double, uint>(x1.data())); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_1(double_v, short_v) { return AVX::zeroExtend(_mm_packs_epi32(_mm256_cvttpd_epi32(x.data()), _mm_setzero_si128())); }
Vc_SIMD_CAST_AVX_1( float_v, short_v) {
const auto tmp = _mm256_cvttps_epi32(x.data());
return AVX::zeroExtend(_mm_packs_epi32(AVX::lo128(tmp), AVX::hi128(tmp)));
}
Vc_SIMD_CAST_AVX_1( int_v, short_v) { return AVX::zeroExtend(AVX::convert< int, short>(x.data())); }
Vc_SIMD_CAST_AVX_1( uint_v, short_v) { return AVX::zeroExtend(AVX::convert<uint, short>(x.data())); }
Vc_SIMD_CAST_AVX_1(ushort_v, short_v) { return x.data(); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_2(double_v, short_v) {
const auto tmp0 = _mm256_cvttpd_epi32(x0.data());
const auto tmp1 = _mm256_cvttpd_epi32(x1.data());
return AVX::zeroExtend(_mm_packs_epi32(tmp0, tmp1));
}
Vc_SIMD_CAST_AVX_2( float_v, short_v) {
using AVX2::short_v;
using AVX2::int_v;
return simd_cast<short_v>(simd_cast<int_v>(x0), simd_cast<int_v>(x1));
}
Vc_SIMD_CAST_AVX_2( int_v, short_v) {
auto tmp0 = _mm256_unpacklo_epi16(x0.data(), x1.data());
auto tmp1 = _mm256_unpackhi_epi16(x0.data(), x1.data());
auto tmp2 = _mm256_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm256_unpackhi_epi16(tmp0, tmp1);
return Mem::permute4x64<X0, X2, X1, X3>(_mm256_unpacklo_epi16(tmp2, tmp3));
}
Vc_SIMD_CAST_AVX_2( uint_v, short_v) {
auto tmp0 = _mm256_unpacklo_epi16(x0.data(), x1.data());
auto tmp1 = _mm256_unpackhi_epi16(x0.data(), x1.data());
auto tmp2 = _mm256_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm256_unpackhi_epi16(tmp0, tmp1);
return Mem::permute4x64<X0, X2, X1, X3>(_mm256_unpacklo_epi16(tmp2, tmp3));
}
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_3(double_v, short_v) {
const auto tmp0 = _mm256_cvttpd_epi32(x0.data());
const auto tmp1 = _mm256_cvttpd_epi32(x1.data());
const auto tmp2 = _mm256_cvttpd_epi32(x2.data());
return AVX::concat(_mm_packs_epi32(tmp0, tmp1), _mm_packs_epi32(tmp2, _mm_setzero_si128()));
}
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_4(double_v, short_v) {
const auto tmp0 = _mm256_cvttpd_epi32(x0.data());
const auto tmp1 = _mm256_cvttpd_epi32(x1.data());
const auto tmp2 = _mm256_cvttpd_epi32(x2.data());
const auto tmp3 = _mm256_cvttpd_epi32(x3.data());
return AVX::concat(_mm_packs_epi32(tmp0, tmp1), _mm_packs_epi32(tmp2, tmp3));
}
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_1(double_v, ushort_v) {
const auto tmp = _mm256_cvttpd_epi32(x.data());
return AVX::zeroExtend(_mm_packs_epi32(tmp, _mm_setzero_si128()));
}
Vc_SIMD_CAST_AVX_1( float_v, ushort_v) {
const auto tmp = _mm256_cvttps_epi32(x.data());
return AVX::zeroExtend(_mm_packs_epi32(AVX::lo128(tmp), AVX::hi128(tmp)));
}
Vc_SIMD_CAST_AVX_1( int_v, ushort_v) { return AVX::zeroExtend(AVX::convert< int, ushort>(x.data())); }
Vc_SIMD_CAST_AVX_1( uint_v, ushort_v) { return AVX::zeroExtend(AVX::convert<uint, ushort>(x.data())); }
Vc_SIMD_CAST_AVX_1( short_v, ushort_v) { return x.data(); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_2(double_v, ushort_v) {
const auto tmp0 = _mm256_cvttpd_epi32(x0.data());
const auto tmp1 = _mm256_cvttpd_epi32(x1.data());
return AVX::zeroExtend(_mm_packs_epi32(tmp0, tmp1));
}
Vc_SIMD_CAST_AVX_2( float_v, ushort_v) {
using AVX2::ushort_v;
using AVX2::int_v;
return simd_cast<ushort_v>(simd_cast<int_v>(x0), simd_cast<int_v>(x1));
}
Vc_SIMD_CAST_AVX_2( int_v, ushort_v) {
auto tmp0 = _mm256_unpacklo_epi16(x0.data(), x1.data());
auto tmp1 = _mm256_unpackhi_epi16(x0.data(), x1.data());
auto tmp2 = _mm256_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm256_unpackhi_epi16(tmp0, tmp1);
return Mem::permute4x64<X0, X2, X1, X3>(_mm256_unpacklo_epi16(tmp2, tmp3));
}
Vc_SIMD_CAST_AVX_2( uint_v, ushort_v) {
auto tmp0 = _mm256_unpacklo_epi16(x0.data(), x1.data());
auto tmp1 = _mm256_unpackhi_epi16(x0.data(), x1.data());
auto tmp2 = _mm256_unpacklo_epi16(tmp0, tmp1);
auto tmp3 = _mm256_unpackhi_epi16(tmp0, tmp1);
return Mem::permute4x64<X0, X2, X1, X3>(_mm256_unpacklo_epi16(tmp2, tmp3));
}
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_3(double_v, ushort_v) {
const auto tmp0 = _mm256_cvttpd_epi32(x0.data());
const auto tmp1 = _mm256_cvttpd_epi32(x1.data());
const auto tmp2 = _mm256_cvttpd_epi32(x2.data());
return AVX::concat(_mm_packs_epi32(tmp0, tmp1), _mm_packs_epi32(tmp2, _mm_setzero_si128()));
}
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_4(double_v, ushort_v) {
const auto tmp0 = _mm256_cvttpd_epi32(x0.data());
const auto tmp1 = _mm256_cvttpd_epi32(x1.data());
const auto tmp2 = _mm256_cvttpd_epi32(x2.data());
const auto tmp3 = _mm256_cvttpd_epi32(x3.data());
return AVX::concat(_mm_packs_epi32(tmp0, tmp1), _mm_packs_epi32(tmp2, tmp3));
}
#endif
Vc_SIMD_CAST_1(SSE::double_v, AVX2::double_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: float_v, AVX2::double_v) { return _mm256_cvtps_pd(x.data()); }
Vc_SIMD_CAST_1(SSE:: int_v, AVX2::double_v) { return _mm256_cvtepi32_pd(x.data()); }
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2::double_v) { using namespace AvxIntrinsics; return _mm256_add_pd(_mm256_cvtepi32_pd(_mm_sub_epi32(x.data(), _mm_setmin_epi32())), set1_pd(1u << 31)); }
Vc_SIMD_CAST_1(SSE:: short_v, AVX2::double_v) { return simd_cast<AVX2::double_v>(simd_cast<SSE::int_v>(x)); }
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2::double_v) { return simd_cast<AVX2::double_v>(simd_cast<SSE::int_v>(x)); }
Vc_SIMD_CAST_1(SSE::double_v, AVX2:: float_v) { return AVX::zeroExtend(simd_cast<SSE:: float_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: float_v, AVX2:: float_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: int_v, AVX2:: float_v) { return AVX::zeroExtend(_mm_cvtepi32_ps(x.data())); }
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2:: float_v) { return AVX::zeroExtend(simd_cast<SSE::float_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: short_v, AVX2:: float_v) { return AVX::convert< short, float>(x.data()); }
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2:: float_v) { return AVX::convert<ushort, float>(x.data()); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(SSE::double_v, AVX2:: int_v) { return AVX::zeroExtend(simd_cast<SSE:: int_v>(x).data()); }
Vc_SIMD_CAST_1(SSE::double_v, AVX2:: uint_v) { return AVX::zeroExtend(simd_cast<SSE:: uint_v>(x).data()); }
Vc_SIMD_CAST_1(SSE::double_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE:: short_v>(x).data()); }
Vc_SIMD_CAST_1(SSE::double_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: float_v, AVX2:: int_v) { return AVX::zeroExtend(simd_cast<SSE::int_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: float_v, AVX2:: uint_v) { return AVX::zeroExtend(simd_cast<SSE::uint_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: float_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE::short_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: float_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: int_v, AVX2:: int_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2:: int_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: short_v, AVX2:: int_v) { return AVX::convert< short, int>(x.data()); }
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2:: int_v) { return AVX::convert<ushort, int>(x.data()); }
Vc_SIMD_CAST_1(SSE:: int_v, AVX2:: uint_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2:: uint_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: short_v, AVX2:: uint_v) { return AVX::convert< short, uint>(x.data()); }
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2:: uint_v) { return AVX::convert<ushort, uint>(x.data()); }
Vc_SIMD_CAST_1(SSE:: int_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE::short_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE::short_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: short_v, AVX2:: short_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2:: short_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: int_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: uint_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x).data()); }
Vc_SIMD_CAST_1(SSE:: short_v, AVX2::ushort_v) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE::ushort_v, AVX2::ushort_v) { return AVX::zeroExtend(x.data()); }
#endif
Vc_SIMD_CAST_2(SSE::double_v, AVX2::double_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE::double_v, AVX2:: float_v) { return AVX::zeroExtend(simd_cast<SSE:: float_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE:: float_v, AVX2:: float_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: int_v, AVX2:: float_v) { return AVX::convert< int, float>(AVX::concat(x0.data(), x1.data())); }
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2:: float_v) { return AVX::convert<uint, float>(AVX::concat(x0.data(), x1.data())); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_2(SSE::double_v, AVX2:: int_v) { return AVX::zeroExtend(simd_cast<SSE:: int_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE::double_v, AVX2:: uint_v) { return AVX::zeroExtend(simd_cast<SSE:: uint_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE::double_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE:: short_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE::double_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE:: float_v, AVX2:: int_v) { return simd_cast<AVX2:: int_v>(simd_cast<AVX2::float_v>(x0, x1)); }
Vc_SIMD_CAST_2(SSE:: float_v, AVX2:: uint_v) { return simd_cast<AVX2::uint_v>(simd_cast<AVX2::float_v>(x0, x1)); }
Vc_SIMD_CAST_2(SSE:: float_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE:: short_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE:: float_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE:: int_v, AVX2:: int_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2:: int_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: int_v, AVX2:: uint_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2:: uint_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: int_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE:: short_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE:: short_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE:: short_v, AVX2:: short_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE::ushort_v, AVX2:: short_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: int_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE:: uint_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x0, x1).data()); }
Vc_SIMD_CAST_2(SSE:: short_v, AVX2::ushort_v) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE::ushort_v, AVX2::ushort_v) { return AVX::concat(x0.data(), x1.data()); }
#endif
Vc_SIMD_CAST_3(SSE::double_v, AVX2:: float_v) { return simd_cast<AVX2:: float_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2)); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_3(SSE::double_v, AVX2:: int_v) { return simd_cast<AVX2:: int_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2)); }
Vc_SIMD_CAST_3(SSE::double_v, AVX2:: uint_v) { return simd_cast<AVX2::uint_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2)); }
Vc_SIMD_CAST_3(SSE::double_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE:: short_v>(x0, x1, x2).data()); }
Vc_SIMD_CAST_3(SSE::double_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x0, x1, x2).data()); }
Vc_SIMD_CAST_3(SSE:: float_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2::float_v>(x0, x1), simd_cast<AVX2::float_v>(x2)); }
Vc_SIMD_CAST_3(SSE:: float_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2::float_v>(x0, x1), simd_cast<AVX2::float_v>(x2)); }
Vc_SIMD_CAST_3(SSE:: int_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2:: int_v>(x0, x1), simd_cast<AVX2:: int_v>(x2)); }
Vc_SIMD_CAST_3(SSE:: uint_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2::uint_v>(x0, x1), simd_cast<AVX2::uint_v>(x2)); }
Vc_SIMD_CAST_3(SSE:: int_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2:: int_v>(x0, x1), simd_cast<AVX2:: int_v>(x2)); }
Vc_SIMD_CAST_3(SSE:: uint_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2::uint_v>(x0, x1), simd_cast<AVX2::uint_v>(x2)); }
#endif
Vc_SIMD_CAST_4(SSE::double_v, AVX2:: float_v) { return simd_cast<AVX2:: float_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3)); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_4(SSE::double_v, AVX2:: int_v) { return simd_cast<AVX2:: int_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3)); }
Vc_SIMD_CAST_4(SSE::double_v, AVX2:: uint_v) { return simd_cast<AVX2::uint_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3)); }
Vc_SIMD_CAST_4(SSE::double_v, AVX2:: short_v) { return AVX::zeroExtend(simd_cast<SSE:: short_v>(x0, x1, x2, x3).data()); }
Vc_SIMD_CAST_4(SSE::double_v, AVX2::ushort_v) { return AVX::zeroExtend(simd_cast<SSE::ushort_v>(x0, x1, x2, x3).data()); }
Vc_SIMD_CAST_4(SSE:: float_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2::float_v>(x0, x1), simd_cast<AVX2::float_v>(x2, x3)); }
Vc_SIMD_CAST_4(SSE:: float_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2::float_v>(x0, x1), simd_cast<AVX2::float_v>(x2, x3)); }
Vc_SIMD_CAST_4(SSE:: int_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2:: int_v>(x0, x1), simd_cast<AVX2:: int_v>(x2, x3)); }
Vc_SIMD_CAST_4(SSE:: uint_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2::uint_v>(x0, x1), simd_cast<AVX2::uint_v>(x2, x3)); }
Vc_SIMD_CAST_4(SSE:: int_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2:: int_v>(x0, x1), simd_cast<AVX2:: int_v>(x2, x3)); }
Vc_SIMD_CAST_4(SSE:: uint_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2::uint_v>(x0, x1), simd_cast<AVX2::uint_v>(x2, x3)); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_5(SSE::double_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3), simd_cast<AVX2::double_v>(x4)); }
Vc_SIMD_CAST_5(SSE::double_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3), simd_cast<AVX2::double_v>(x4)); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_6(SSE::double_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3), simd_cast<AVX2::double_v>(x4, x5)); }
Vc_SIMD_CAST_6(SSE::double_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3), simd_cast<AVX2::double_v>(x4, x5)); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_7(SSE::double_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3), simd_cast<AVX2::double_v>(x4, x5), simd_cast<AVX2::double_v>(x6)); }
Vc_SIMD_CAST_7(SSE::double_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3), simd_cast<AVX2::double_v>(x4, x5), simd_cast<AVX2::double_v>(x6)); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_8(SSE::double_v, AVX2:: short_v) { return simd_cast<AVX2:: short_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3), simd_cast<AVX2::double_v>(x4, x5), simd_cast<AVX2::double_v>(x6, x7)); }
Vc_SIMD_CAST_8(SSE::double_v, AVX2::ushort_v) { return simd_cast<AVX2::ushort_v>(simd_cast<AVX2::double_v>(x0, x1), simd_cast<AVX2::double_v>(x2, x3), simd_cast<AVX2::double_v>(x4, x5), simd_cast<AVX2::double_v>(x6, x7)); }
#endif
Vc_SIMD_CAST_1(AVX2::double_v, SSE::double_v) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2:: float_v, SSE:: float_v) { return AVX::lo128(x.data()); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(AVX2:: int_v, SSE:: int_v) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE:: uint_v) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2:: short_v, SSE:: short_v) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE::ushort_v) { return AVX::lo128(x.data()); }
#endif
Vc_SIMD_CAST_1(AVX2::double_v, SSE:: float_v) { return simd_cast<SSE:: float_v>(simd_cast<AVX2:: float_v>(x)); }
Vc_SIMD_CAST_1(AVX2::double_v, SSE:: int_v) { return AVX::convert<double, int>(x.data()); }
Vc_SIMD_CAST_1(AVX2::double_v, SSE:: uint_v) { return AVX::convert<double, unsigned int>(x.data()); }
Vc_SIMD_CAST_1(AVX2::double_v, SSE:: short_v) { return AVX::convert<double, short>(x.data()); }
Vc_SIMD_CAST_1(AVX2::double_v, SSE::ushort_v) { return AVX::convert<double, unsigned short>(x.data()); }
Vc_SIMD_CAST_1(AVX2:: float_v, SSE::double_v) { return simd_cast<SSE::double_v>(simd_cast<SSE:: float_v>(x)); }
Vc_SIMD_CAST_1(AVX2:: float_v, SSE:: int_v) { return simd_cast<SSE:: int_v>(simd_cast<SSE:: float_v>(x)); }
Vc_SIMD_CAST_1(AVX2:: float_v, SSE:: uint_v) { return simd_cast<SSE:: uint_v>(simd_cast<SSE:: float_v>(x)); }
Vc_SIMD_CAST_1(AVX2:: float_v, SSE:: short_v) { return AVX::convert<float, short>(x.data()); }
Vc_SIMD_CAST_1(AVX2:: float_v, SSE::ushort_v) { return AVX::convert<float, unsigned short>(x.data()); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(AVX2:: int_v, SSE::double_v) { return SSE::convert<int, double>(AVX::lo128(x.data())); }
Vc_SIMD_CAST_1(AVX2:: int_v, SSE:: float_v) { return SSE::convert<int, float>(AVX::lo128(x.data())); }
Vc_SIMD_CAST_1(AVX2:: int_v, SSE:: uint_v) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2:: int_v, SSE:: short_v) { return AVX::convert<int, short>(x.data()); }
Vc_SIMD_CAST_1(AVX2:: int_v, SSE::ushort_v) { return AVX::convert<int, ushort>(x.data()); }
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE::double_v) { return SSE::convert<uint, double>(AVX::lo128(x.data())); }
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE:: float_v) { return SSE::convert<uint, float>(AVX::lo128(x.data())); }
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE:: int_v) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE:: short_v) { return AVX::convert<uint, short>(x.data()); }
Vc_SIMD_CAST_1(AVX2:: uint_v, SSE::ushort_v) { return AVX::convert<uint, ushort>(x.data()); }
Vc_SIMD_CAST_1(AVX2:: short_v, SSE::double_v) { return simd_cast<SSE::double_v>(simd_cast<SSE:: short_v>(x)); }
Vc_SIMD_CAST_1(AVX2:: short_v, SSE:: float_v) { return simd_cast<SSE:: float_v>(simd_cast<SSE:: short_v>(x)); }
Vc_SIMD_CAST_1(AVX2:: short_v, SSE:: int_v) { return simd_cast<SSE:: int_v>(simd_cast<SSE:: short_v>(x)); }
Vc_SIMD_CAST_1(AVX2:: short_v, SSE:: uint_v) { return simd_cast<SSE:: uint_v>(simd_cast<SSE:: short_v>(x)); }
Vc_SIMD_CAST_1(AVX2:: short_v, SSE::ushort_v) { return simd_cast<SSE::ushort_v>(simd_cast<SSE:: short_v>(x)); }
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE::double_v) { return simd_cast<SSE::double_v>(simd_cast<SSE::ushort_v>(x)); }
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE:: float_v) { return simd_cast<SSE:: float_v>(simd_cast<SSE::ushort_v>(x)); }
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE:: int_v) { return simd_cast<SSE:: int_v>(simd_cast<SSE::ushort_v>(x)); }
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE:: uint_v) { return simd_cast<SSE:: uint_v>(simd_cast<SSE::ushort_v>(x)); }
Vc_SIMD_CAST_1(AVX2::ushort_v, SSE:: short_v) { return simd_cast<SSE:: short_v>(simd_cast<SSE::ushort_v>(x)); }
#endif
Vc_SIMD_CAST_2(AVX2::double_v, SSE:: short_v) {
const auto tmp0 = _mm256_cvttpd_epi32(x0.data());
const auto tmp1 = _mm256_cvttpd_epi32(x1.data());
return _mm_packs_epi32(tmp0, tmp1);
}
Vc_SIMD_CAST_2(AVX2::double_v, SSE::ushort_v) {
const auto tmp0 = _mm256_cvttpd_epi32(x0.data());
const auto tmp1 = _mm256_cvttpd_epi32(x1.data());
return _mm_packs_epi32(tmp0, tmp1);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::double_v>::value>)
{
return AVX::zeroExtend(_mm_setr_pd(x.data(), 0.));
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::float_v>::value>)
{
return AVX::zeroExtend(_mm_setr_ps(x.data(), 0.f, 0.f, 0.f));
}
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::int_v>::value>)
{
return _mm256_setr_epi32(x.data(), 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::uint_v>::value>)
{
return _mm256_setr_epi32(uint(x.data()), 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::double_v>::value>)
{
return AVX::zeroExtend(_mm_setr_pd(x0.data(), x1.data()));
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::float_v>::value>)
{
return AVX::zeroExtend(_mm_setr_ps(x0.data(), x1.data(), 0.f, 0.f));
}
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::int_v>::value>)
{
return _mm256_setr_epi32(x0.data(), x1.data(), 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::uint_v>::value>)
{
return _mm256_setr_epi32(uint(x0.data()), uint(x1.data()), 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::double_v>::value>)
{
return _mm256_setr_pd(x0.data(), x1.data(), x2.data(), 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::float_v>::value>)
{
return AVX::zeroExtend(_mm_setr_ps(x0.data(), x1.data(), x2.data(), 0));
}
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::int_v>::value>)
{
return _mm256_setr_epi32(x0.data(), x1.data(), x2.data(), 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::uint_v>::value>)
{
return _mm256_setr_epi32(uint(x0.data()), uint(x1.data()), uint(x2.data()), 0, 0, 0,
0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::double_v>::value>)
{
return _mm256_setr_pd(x0.data(), x1.data(), x2.data(), x3.data());
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::float_v>::value>)
{
return AVX::zeroExtend(_mm_setr_ps(x0.data(), x1.data(), x2.data(), x3.data()));
}
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::int_v>::value>)
{
return _mm256_setr_epi32(x0.data(), x1.data(), x2.data(), x3.data(), 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::uint_v>::value>)
{
return _mm256_setr_epi32(uint(x0.data()), uint(x1.data()), uint(x2.data()),
uint(x3.data()), 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::float_v>::value>)
{
return _mm256_setr_ps(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(), 0, 0, 0);
}
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::int_v>::value>)
{
return _mm256_setr_epi32(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(), 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::uint_v>::value>)
{
return _mm256_setr_epi32(uint(x0.data()), uint(x1.data()), uint(x2.data()),
uint(x3.data()), uint(x4.data()), 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::float_v>::value>)
{
return _mm256_setr_ps(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), 0, 0);
}
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::int_v>::value>)
{
return _mm256_setr_epi32(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::uint_v>::value>)
{
return _mm256_setr_epi32(uint(x0.data()), uint(x1.data()), uint(x2.data()),
uint(x3.data()), uint(x4.data()), uint(x5.data()), 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::float_v>::value>)
{
return _mm256_setr_ps(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), 0);
}
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::int_v>::value>)
{
return _mm256_setr_epi32(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::uint_v>::value>)
{
return _mm256_setr_epi32(uint(x0.data()), uint(x1.data()), uint(x2.data()),
uint(x3.data()), uint(x4.data()), uint(x5.data()),
uint(x6.data()), 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::float_v>::value>)
{
return _mm256_setr_ps(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data());
}
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::int_v>::value>)
{
return _mm256_setr_epi32(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data());
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::uint_v>::value>)
{
return _mm256_setr_epi32(uint(x0.data()), uint(x1.data()), uint(x2.data()),
uint(x3.data()), uint(x4.data()), uint(x5.data()),
uint(x6.data()), uint(x7.data()));
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), 0, 0, 0, 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), 0, 0, 0, 0, 0, 0, 0, 0);
}
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), 0, 0, 0, 0, 0, 0,
0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), 0, 0, 0, 0, 0, 0,
0);
}
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(), 0, 0,
0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(), 0, 0,
0, 0, 0, 0);
}
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), 0, 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), 0, 0, 0, 0, 0);
}
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), 0, 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), 0, 0, 0, 0);
}
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), x12.data(), 0, 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), x12.data(), 0, 0, 0);
}
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), x12.data(), x13.data(), 0, 0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), x12.data(), x13.data(), 0, 0);
}
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13, Scalar::Vector<T> x14,
enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), x12.data(), x13.data(), x14.data(),
0);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13, Scalar::Vector<T> x14,
enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), x12.data(), x13.data(), x14.data(),
0);
}
#endif
#ifdef Vc_IMPL_AVX2
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13, Scalar::Vector<T> x14,
Scalar::Vector<T> x15, enable_if<std::is_same<Return, AVX2::short_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), x12.data(), x13.data(), x14.data(),
x15.data());
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Vector<T> x0, Scalar::Vector<T> x1, Scalar::Vector<T> x2,
Scalar::Vector<T> x3, Scalar::Vector<T> x4, Scalar::Vector<T> x5,
Scalar::Vector<T> x6, Scalar::Vector<T> x7, Scalar::Vector<T> x8,
Scalar::Vector<T> x9, Scalar::Vector<T> x10, Scalar::Vector<T> x11,
Scalar::Vector<T> x12, Scalar::Vector<T> x13, Scalar::Vector<T> x14,
Scalar::Vector<T> x15, enable_if<std::is_same<Return, AVX2::ushort_v>::value>)
{
return _mm256_setr_epi16(x0.data(), x1.data(), x2.data(), x3.data(), x4.data(),
x5.data(), x6.data(), x7.data(), x8.data(), x9.data(),
x10.data(), x11.data(), x12.data(), x13.data(), x14.data(),
x15.data());
}
#endif
template <typename To, typename FromT>
Vc_INTRINSIC Vc_CONST To
simd_cast(AVX2::Vector<FromT> x, enable_if<Scalar::is_vector<To>::value>)
{
return static_cast<To>(x[0]);
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(const AVX2::Mask<T> &k, enable_if<AVX2::is_mask<Return>::value>)
{
return {Detail::mask_cast<Mask<T, VectorAbi::Avx>::Size, Return::Size,
typename Return::VectorTypeF>(k.dataI())};
}
Vc_SIMD_CAST_AVX_2(double_m, float_m) { return AVX::concat(_mm_packs_epi32(AVX::lo128(x0.dataI()), AVX::hi128(x0.dataI())), _mm_packs_epi32(AVX::lo128(x1.dataI()), AVX::hi128(x1.dataI()))); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_2(double_m, int_m) { return Mem::permute4x64<X0, X2, X1, X3>(_mm256_packs_epi32(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_AVX_2(double_m, uint_m) { return Mem::permute4x64<X0, X2, X1, X3>(_mm256_packs_epi32(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_AVX_2(double_m, short_m) { return AVX::zeroExtend(_mm_packs_epi16(_mm_packs_epi32(AVX::lo128(x0.dataI()), AVX::hi128(x0.dataI())), _mm_packs_epi32(AVX::lo128(x1.dataI()), AVX::hi128(x1.dataI())))); }
Vc_SIMD_CAST_AVX_2(double_m, ushort_m) { return AVX::zeroExtend(_mm_packs_epi16(_mm_packs_epi32(AVX::lo128(x0.dataI()), AVX::hi128(x0.dataI())), _mm_packs_epi32(AVX::lo128(x1.dataI()), AVX::hi128(x1.dataI())))); }
Vc_SIMD_CAST_AVX_2( float_m, short_m) { return Mem::permute4x64<X0, X2, X1, X3>(_mm256_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_AVX_2( float_m, ushort_m) { return Mem::permute4x64<X0, X2, X1, X3>(_mm256_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_AVX_2( int_m, short_m) { return Mem::permute4x64<X0, X2, X1, X3>(_mm256_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_AVX_2( int_m, ushort_m) { return Mem::permute4x64<X0, X2, X1, X3>(_mm256_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_AVX_2( uint_m, short_m) { return Mem::permute4x64<X0, X2, X1, X3>(_mm256_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_AVX_2( uint_m, ushort_m) { return Mem::permute4x64<X0, X2, X1, X3>(_mm256_packs_epi16(x0.dataI(), x1.dataI())); }
#endif
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_AVX_4(double_m, short_m)
{
using namespace AVX;
const auto tmp = _mm256_packs_epi32(
_mm256_packs_epi32(x0.dataI(), x1.dataI())
,
_mm256_packs_epi32(x2.dataI(), x3.dataI())
);
return concat(_mm_unpacklo_epi32(lo128(tmp), hi128(tmp)),
_mm_unpackhi_epi32(lo128(tmp), hi128(tmp)));
}
Vc_SIMD_CAST_AVX_4(double_m, ushort_m) { return simd_cast<AVX2::short_m>(x0, x1, x2, x3).data(); }
#endif
Vc_SIMD_CAST_1(SSE::double_m, AVX2::double_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE::double_m, AVX2:: float_m) { return AVX::zeroExtend(simd_cast<SSE:: float_m>(x).data()); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(SSE::double_m, AVX2:: int_m) { return AVX::zeroExtend(simd_cast<SSE:: int_m>(x).data()); }
Vc_SIMD_CAST_1(SSE::double_m, AVX2:: uint_m) { return AVX::zeroExtend(simd_cast<SSE:: uint_m>(x).data()); }
Vc_SIMD_CAST_1(SSE::double_m, AVX2:: short_m) { return AVX::zeroExtend(simd_cast<SSE:: short_m>(x).data()); }
Vc_SIMD_CAST_1(SSE::double_m, AVX2::ushort_m) { return AVX::zeroExtend(simd_cast<SSE::ushort_m>(x).data()); }
#endif
Vc_SIMD_CAST_1(SSE:: float_m, AVX2::double_m) { return AVX::concat(_mm_unpacklo_ps(x.data(), x.data()), _mm_unpackhi_ps(x.data(), x.data())); }
Vc_SIMD_CAST_1(SSE:: int_m, AVX2::double_m) { return AVX::concat(_mm_unpacklo_ps(x.data(), x.data()), _mm_unpackhi_ps(x.data(), x.data())); }
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2::double_m) { return AVX::concat(_mm_unpacklo_ps(x.data(), x.data()), _mm_unpackhi_ps(x.data(), x.data())); }
Vc_SIMD_CAST_1(SSE:: short_m, AVX2::double_m) { auto tmp = _mm_unpacklo_epi16(x.dataI(), x.dataI()); return AVX::concat(_mm_unpacklo_epi32(tmp, tmp), _mm_unpackhi_epi32(tmp, tmp)); }
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2::double_m) { auto tmp = _mm_unpacklo_epi16(x.dataI(), x.dataI()); return AVX::concat(_mm_unpacklo_epi32(tmp, tmp), _mm_unpackhi_epi32(tmp, tmp)); }
Vc_SIMD_CAST_1(SSE:: float_m, AVX2:: float_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: int_m, AVX2:: float_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2:: float_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: short_m, AVX2:: float_m) { return AVX::concat(_mm_unpacklo_epi16(x.dataI(), x.dataI()), _mm_unpackhi_epi16(x.dataI(), x.dataI())); }
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2:: float_m) { return AVX::concat(_mm_unpacklo_epi16(x.dataI(), x.dataI()), _mm_unpackhi_epi16(x.dataI(), x.dataI())); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(SSE:: float_m, AVX2:: int_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: float_m, AVX2:: uint_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: int_m, AVX2:: int_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: int_m, AVX2:: uint_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2:: int_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2:: uint_m) { return AVX::zeroExtend(x.data()); }
Vc_SIMD_CAST_1(SSE:: float_m, AVX2:: short_m) { return AVX::zeroExtend(simd_cast<SSE:: short_m>(x).data()); }
Vc_SIMD_CAST_1(SSE:: int_m, AVX2:: short_m) { return AVX::zeroExtend(simd_cast<SSE:: short_m>(x).data()); }
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2:: short_m) { return AVX::zeroExtend(simd_cast<SSE:: short_m>(x).data()); }
Vc_SIMD_CAST_1(SSE:: short_m, AVX2:: short_m) { return AVX::zeroExtend(simd_cast<SSE:: short_m>(x).data()); }
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2:: short_m) { return AVX::zeroExtend(simd_cast<SSE:: short_m>(x).data()); }
Vc_SIMD_CAST_1(SSE:: float_m, AVX2::ushort_m) { return AVX::zeroExtend(simd_cast<SSE::ushort_m>(x).data()); }
Vc_SIMD_CAST_1(SSE:: int_m, AVX2::ushort_m) { return AVX::zeroExtend(simd_cast<SSE::ushort_m>(x).data()); }
Vc_SIMD_CAST_1(SSE:: uint_m, AVX2::ushort_m) { return AVX::zeroExtend(simd_cast<SSE::ushort_m>(x).data()); }
Vc_SIMD_CAST_1(SSE:: short_m, AVX2::ushort_m) { return AVX::zeroExtend(simd_cast<SSE::ushort_m>(x).data()); }
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2::ushort_m) { return AVX::zeroExtend(simd_cast<SSE::ushort_m>(x).data()); }
Vc_SIMD_CAST_1(SSE:: short_m, AVX2:: int_m) { const auto v = Mem::permute4x64<X0, X2, X1, X3>(AVX::avx_cast<__m256i>(x.data())); return _mm256_unpacklo_epi16(v, v); }
Vc_SIMD_CAST_1(SSE:: short_m, AVX2:: uint_m) { const auto v = Mem::permute4x64<X0, X2, X1, X3>(AVX::avx_cast<__m256i>(x.data())); return _mm256_unpacklo_epi16(v, v); }
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2:: int_m) { const auto v = Mem::permute4x64<X0, X2, X1, X3>(AVX::avx_cast<__m256i>(x.data())); return _mm256_unpacklo_epi16(v, v); }
Vc_SIMD_CAST_1(SSE::ushort_m, AVX2:: uint_m) { const auto v = Mem::permute4x64<X0, X2, X1, X3>(AVX::avx_cast<__m256i>(x.data())); return _mm256_unpacklo_epi16(v, v); }
#endif
Vc_SIMD_CAST_2(SSE::double_m, AVX2::double_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE::double_m, AVX2:: float_m) { return AVX::zeroExtend(_mm_packs_epi32(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE:: float_m, AVX2:: float_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: int_m, AVX2:: float_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2:: float_m) { return AVX::concat(x0.data(), x1.data()); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_2(SSE::double_m, AVX2:: int_m) { return AVX::zeroExtend(_mm_packs_epi32(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE::double_m, AVX2:: uint_m) { return AVX::zeroExtend(_mm_packs_epi32(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE::double_m, AVX2:: short_m) { return AVX::zeroExtend(_mm_packs_epi16(_mm_packs_epi32(x0.dataI(), x1.dataI()), _mm_setzero_si128())); }
Vc_SIMD_CAST_2(SSE::double_m, AVX2::ushort_m) { return AVX::zeroExtend(_mm_packs_epi16(_mm_packs_epi32(x0.dataI(), x1.dataI()), _mm_setzero_si128())); }
Vc_SIMD_CAST_2(SSE:: float_m, AVX2:: int_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: float_m, AVX2:: uint_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: float_m, AVX2:: short_m) { return AVX::zeroExtend(_mm_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE:: float_m, AVX2::ushort_m) { return AVX::zeroExtend(_mm_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE:: int_m, AVX2:: int_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: int_m, AVX2:: uint_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: int_m, AVX2:: short_m) { return AVX::zeroExtend(_mm_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE:: int_m, AVX2::ushort_m) { return AVX::zeroExtend(_mm_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2:: int_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2:: uint_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2:: short_m) { return AVX::zeroExtend(_mm_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE:: uint_m, AVX2::ushort_m) { return AVX::zeroExtend(_mm_packs_epi16(x0.dataI(), x1.dataI())); }
Vc_SIMD_CAST_2(SSE:: short_m, AVX2:: short_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE:: short_m, AVX2::ushort_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE::ushort_m, AVX2:: short_m) { return AVX::concat(x0.data(), x1.data()); }
Vc_SIMD_CAST_2(SSE::ushort_m, AVX2::ushort_m) { return AVX::concat(x0.data(), x1.data()); }
#endif
Vc_SIMD_CAST_4(SSE::double_m, AVX2:: float_m) { return AVX::concat(_mm_packs_epi32(x0.dataI(), x1.dataI()), _mm_packs_epi32(x2.dataI(), x3.dataI())); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_4(SSE::double_m, AVX2:: int_m) { return AVX::concat(_mm_packs_epi32(x0.dataI(), x1.dataI()), _mm_packs_epi32(x2.dataI(), x3.dataI())); }
Vc_SIMD_CAST_4(SSE::double_m, AVX2:: uint_m) { return AVX::concat(_mm_packs_epi32(x0.dataI(), x1.dataI()), _mm_packs_epi32(x2.dataI(), x3.dataI())); }
Vc_SIMD_CAST_4(SSE::double_m, AVX2:: short_m) { return AVX::zeroExtend(_mm_packs_epi16(_mm_packs_epi32(x0.dataI(), x1.dataI()), _mm_packs_epi32(x2.dataI(), x3.dataI()))); }
Vc_SIMD_CAST_4(SSE::double_m, AVX2::ushort_m) { return AVX::zeroExtend(_mm_packs_epi16(_mm_packs_epi32(x0.dataI(), x1.dataI()), _mm_packs_epi32(x2.dataI(), x3.dataI()))); }
Vc_SIMD_CAST_4(SSE:: float_m, AVX2:: short_m) { return AVX::concat(_mm_packs_epi16(x0.dataI(), x1.dataI()), _mm_packs_epi16(x2.dataI(), x3.dataI())); }
Vc_SIMD_CAST_4(SSE:: float_m, AVX2::ushort_m) { return AVX::concat(_mm_packs_epi16(x0.dataI(), x1.dataI()), _mm_packs_epi16(x2.dataI(), x3.dataI())); }
Vc_SIMD_CAST_4(SSE:: int_m, AVX2:: short_m) { return AVX::concat(_mm_packs_epi16(x0.dataI(), x1.dataI()), _mm_packs_epi16(x2.dataI(), x3.dataI())); }
Vc_SIMD_CAST_4(SSE:: int_m, AVX2::ushort_m) { return AVX::concat(_mm_packs_epi16(x0.dataI(), x1.dataI()), _mm_packs_epi16(x2.dataI(), x3.dataI())); }
Vc_SIMD_CAST_4(SSE:: uint_m, AVX2:: short_m) { return AVX::concat(_mm_packs_epi16(x0.dataI(), x1.dataI()), _mm_packs_epi16(x2.dataI(), x3.dataI())); }
Vc_SIMD_CAST_4(SSE:: uint_m, AVX2::ushort_m) { return AVX::concat(_mm_packs_epi16(x0.dataI(), x1.dataI()), _mm_packs_epi16(x2.dataI(), x3.dataI())); }
#endif
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> k, enable_if<AVX2::is_mask<Return>::value>)
{
Return r{false};
r[0] = k.data();
return r;
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> k0, Scalar::Mask<T> k1,
enable_if<AVX2::is_mask<Return>::value>)
{
Return r{false};
r[0] = k0.data();
r[1] = k1.data();
return r;
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> k0, Scalar::Mask<T> k1, Scalar::Mask<T> k2, Scalar::Mask<T> k3,
enable_if<(AVX2::is_mask<Return>::value && Return::Size >= 4)>)
{
Return r{false};
r[0] = k0.data();
r[1] = k1.data();
r[2] = k2.data();
r[3] = k3.data();
return r;
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> k0, Scalar::Mask<T> k1, Scalar::Mask<T> k2, Scalar::Mask<T> k3,
Scalar::Mask<T> k4, Scalar::Mask<T> k5, Scalar::Mask<T> k6, Scalar::Mask<T> k7,
enable_if<(AVX2::is_mask<Return>::value && Return::Size >= 8)>)
{
Return r{false};
r[0] = k0.data();
r[1] = k1.data();
r[2] = k2.data();
r[3] = k3.data();
r[4] = k4.data();
r[5] = k5.data();
r[6] = k6.data();
r[7] = k7.data();
return r;
}
template <typename Return, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(Scalar::Mask<T> k0, Scalar::Mask<T> k1, Scalar::Mask<T> k2, Scalar::Mask<T> k3,
Scalar::Mask<T> k4, Scalar::Mask<T> k5, Scalar::Mask<T> k6, Scalar::Mask<T> k7,
Scalar::Mask<T> k8, Scalar::Mask<T> k9, Scalar::Mask<T> k10,
Scalar::Mask<T> k11, Scalar::Mask<T> k12, Scalar::Mask<T> k13,
Scalar::Mask<T> k14, Scalar::Mask<T> k15,
enable_if<(AVX2::is_mask<Return>::value && Return::Size >= 16)>)
{
Return r{false};
r[0] = k0.data();
r[1] = k1.data();
r[2] = k2.data();
r[3] = k3.data();
r[4] = k4.data();
r[5] = k5.data();
r[6] = k6.data();
r[7] = k7.data();
r[8] = k8.data();
r[9] = k9.data();
r[10] = k10.data();
r[11] = k11.data();
r[12] = k12.data();
r[13] = k13.data();
r[14] = k14.data();
r[15] = k15.data();
return r;
}
Vc_SIMD_CAST_1(AVX2::double_m, SSE::double_m) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2::double_m, SSE:: float_m) { return _mm_packs_epi32(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2::double_m, SSE:: int_m) { return _mm_packs_epi32(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2::double_m, SSE:: uint_m) { return _mm_packs_epi32(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2::double_m, SSE:: short_m) { return _mm_packs_epi16(_mm_packs_epi32(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())), _mm_setzero_si128()); }
Vc_SIMD_CAST_1(AVX2::double_m, SSE::ushort_m) { return _mm_packs_epi16(_mm_packs_epi32(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())), _mm_setzero_si128()); }
Vc_SIMD_CAST_1(AVX2:: float_m, SSE::double_m) { return _mm_unpacklo_ps(AVX::lo128(x.data()), AVX::lo128(x.data())); }
Vc_SIMD_CAST_1(AVX2:: float_m, SSE:: float_m) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2:: float_m, SSE:: int_m) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2:: float_m, SSE:: uint_m) { return AVX::lo128(x.data()); }
Vc_SIMD_CAST_1(AVX2:: float_m, SSE:: short_m) { return _mm_packs_epi16(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2:: float_m, SSE::ushort_m) { return _mm_packs_epi16(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
#ifdef Vc_IMPL_AVX2
Vc_SIMD_CAST_1(AVX2:: int_m, SSE::double_m) { return _mm_unpacklo_epi32(AVX::lo128(x.dataI()), AVX::lo128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2:: int_m, SSE:: float_m) { return AVX::lo128(x.dataI()); }
Vc_SIMD_CAST_1(AVX2:: int_m, SSE:: int_m) { return AVX::lo128(x.dataI()); }
Vc_SIMD_CAST_1(AVX2:: int_m, SSE:: uint_m) { return AVX::lo128(x.dataI()); }
Vc_SIMD_CAST_1(AVX2:: int_m, SSE:: short_m) { return _mm_packs_epi16(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2:: int_m, SSE::ushort_m) { return _mm_packs_epi16(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE::double_m) { return _mm_unpacklo_epi32(AVX::lo128(x.dataI()), AVX::lo128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE:: float_m) { return AVX::lo128(x.dataI()); }
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE:: int_m) { return AVX::lo128(x.dataI()); }
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE:: uint_m) { return AVX::lo128(x.dataI()); }
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE:: short_m) { return _mm_packs_epi16(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2:: uint_m, SSE::ushort_m) { return _mm_packs_epi16(AVX::lo128(x.dataI()), AVX::hi128(x.dataI())); }
Vc_SIMD_CAST_1(AVX2:: short_m, SSE::double_m) { return simd_cast<SSE::double_m>(SSE::short_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2:: short_m, SSE:: float_m) { return simd_cast<SSE:: float_m>(SSE::short_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2:: short_m, SSE:: int_m) { return simd_cast<SSE:: int_m>(SSE::short_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2:: short_m, SSE:: uint_m) { return simd_cast<SSE:: uint_m>(SSE::short_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2:: short_m, SSE:: short_m) { return simd_cast<SSE:: short_m>(SSE::short_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2:: short_m, SSE::ushort_m) { return simd_cast<SSE::ushort_m>(SSE::short_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE::double_m) { return simd_cast<SSE::double_m>(SSE::ushort_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE:: float_m) { return simd_cast<SSE:: float_m>(SSE::ushort_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE:: int_m) { return simd_cast<SSE:: int_m>(SSE::ushort_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE:: uint_m) { return simd_cast<SSE:: uint_m>(SSE::ushort_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE:: short_m) { return simd_cast<SSE:: short_m>(SSE::ushort_m(AVX::lo128(x.data()))); }
Vc_SIMD_CAST_1(AVX2::ushort_m, SSE::ushort_m) { return simd_cast<SSE::ushort_m>(SSE::ushort_m(AVX::lo128(x.data()))); }
#endif
Vc_SIMD_CAST_2(AVX2::double_m, SSE:: short_m) { return _mm_packs_epi16(_mm_packs_epi32(AVX::lo128(x0.dataI()), AVX::hi128(x0.dataI())), _mm_packs_epi32(AVX::lo128(x1.dataI()), AVX::hi128(x1.dataI()))); }
Vc_SIMD_CAST_2(AVX2::double_m, SSE::ushort_m) { return _mm_packs_epi16(_mm_packs_epi32(AVX::lo128(x0.dataI()), AVX::hi128(x0.dataI())), _mm_packs_epi32(AVX::lo128(x1.dataI()), AVX::hi128(x1.dataI()))); }
template <typename To, typename FromT>
Vc_INTRINSIC Vc_CONST To
simd_cast(AVX2::Mask<FromT> x, enable_if<Scalar::is_mask<To>::value>)
{
return static_cast<To>(x[0]);
}
template <typename Return, int offset, typename From>
Vc_INTRINSIC Vc_CONST enable_if<
(offset == 0 &&
((AVX2::is_vector<From>::value && !Scalar::is_vector<Return>::value &&
Traits::is_simd_vector<Return>::value && !Traits::isSimdArray<Return>::value) ||
(AVX2::is_mask<From>::value && !Scalar::is_mask<Return>::value &&
Traits::is_simd_mask<Return>::value &&
!Traits::isSimdMaskArray<Return>::value))),
Return>
simd_cast(const From &x)
{
return simd_cast<Return>(x);
}
template <typename Return, int offset, typename From>
Vc_INTRINSIC Vc_CONST Return
simd_cast(const From &x,
enable_if<offset == 0 && ((SSE::is_vector<From>::value &&
AVX2::is_vector<Return>::value) ||
(SSE::is_mask<From>::value &&
AVX2::is_mask<Return>::value))>)
{
return simd_cast<Return>(x);
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(AVX2::is_vector<Return>::value && offset != 0),
Return>
simd_cast(AVX2::Vector<T> x)
{
using V = AVX2::Vector<T>;
constexpr int shift = sizeof(T) * offset * Return::Size;
static_assert(shift > 0 && shift < sizeof(x), "");
if (shift < 16) {
return simd_cast<Return>(V{AVX::avx_cast<typename V::VectorType>(
_mm_srli_si128(AVX::avx_cast<__m128i>(AVX::lo128(x.data())), shift))});
} else if (shift == 16) {
return simd_cast<Return>(V{Mem::permute128<X1, Const0>(x.data())});
} else {
#ifdef Vc_MSVC
#pragma warning(push)
#pragma warning(disable : 4556)
#endif
return simd_cast<Return>(V{AVX::avx_cast<typename V::VectorType>(
_mm_srli_si128(AVX::avx_cast<__m128i>(AVX::hi128(x.data())), shift - 16))});
#ifdef Vc_MSVC
#pragma warning(pop)
#endif
}
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0 && SSE::is_vector<Return>::value &&
sizeof(AVX2::Vector<T>) == 32),
Return>
simd_cast(AVX2::Vector<T> x)
{
using V = AVX2::Vector<T>;
constexpr int shift = sizeof(V) / V::Size * offset * Return::Size;
static_assert(shift > 0, "");
static_assert(shift < sizeof(V), "");
using SseVector = SSE::Vector<typename V::EntryType>;
if (shift == 16) {
return simd_cast<Return>(SseVector{AVX::hi128(x.data())});
}
using Intrin = typename SseVector::VectorType;
return simd_cast<Return>(SseVector{AVX::avx_cast<Intrin>(
_mm_alignr_epi8(AVX::avx_cast<__m128i>(AVX::hi128(x.data())),
AVX::avx_cast<__m128i>(AVX::lo128(x.data())), shift))});
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0 && SSE::is_vector<Return>::value &&
sizeof(AVX2::Vector<T>) == 16),
Return>
simd_cast(AVX2::Vector<T> x)
{
using V = AVX2::Vector<T>;
constexpr int shift = sizeof(V) / V::Size * offset * Return::Size;
static_assert(shift > 0, "");
static_assert(shift < sizeof(V), "");
using SseVector = SSE::Vector<typename V::EntryType>;
return simd_cast<Return>(SseVector{_mm_srli_si128(x.data(), shift)});
}
Vc_SIMD_CAST_OFFSET(SSE:: short_v, AVX2::double_v, 1) { return simd_cast<AVX2::double_v>(simd_cast<SSE::int_v, 1>(x)); }
Vc_SIMD_CAST_OFFSET(SSE::ushort_v, AVX2::double_v, 1) { return simd_cast<AVX2::double_v>(simd_cast<SSE::int_v, 1>(x)); }
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(const AVX2::Mask<T> &k,
enable_if<(AVX2::is_mask<Return>::value && offset == 1 &&
AVX2::Mask<T>::Size == Return::Size * 2)> = nullarg)
{
const auto tmp = AVX::hi128(k.dataI());
return AVX::concat(_mm_unpacklo_epi8(tmp, tmp), _mm_unpackhi_epi8(tmp, tmp));
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(const AVX2::Mask<T> &k,
enable_if<(AVX2::is_mask<Return>::value && offset == 1 &&
AVX2::Mask<T>::Size == Return::Size * 4)> = nullarg)
{
auto tmp = AVX::lo128(k.dataI());
tmp = _mm_unpackhi_epi8(tmp, tmp);
return AVX::concat(_mm_unpacklo_epi16(tmp, tmp), _mm_unpackhi_epi16(tmp, tmp));
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(const AVX2::Mask<T> &k,
enable_if<(AVX2::is_mask<Return>::value && offset == 2 &&
AVX2::Mask<T>::Size == Return::Size * 4)> = nullarg)
{
auto tmp = AVX::hi128(k.dataI());
tmp = _mm_unpacklo_epi8(tmp, tmp);
return AVX::concat(_mm_unpacklo_epi16(tmp, tmp), _mm_unpackhi_epi16(tmp, tmp));
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST Return
simd_cast(const AVX2::Mask<T> &k,
enable_if<(AVX2::is_mask<Return>::value && offset == 3 &&
AVX2::Mask<T>::Size == Return::Size * 4)> = nullarg)
{
auto tmp = AVX::hi128(k.dataI());
tmp = _mm_unpackhi_epi8(tmp, tmp);
return AVX::concat(_mm_unpacklo_epi16(tmp, tmp), _mm_unpackhi_epi16(tmp, tmp));
}
Vc_SIMD_CAST_OFFSET(SSE:: short_m, AVX2::double_m, 1) { auto tmp = _mm_unpackhi_epi16(x.dataI(), x.dataI()); return AVX::concat(_mm_unpacklo_epi32(tmp, tmp), _mm_unpackhi_epi32(tmp, tmp)); }
Vc_SIMD_CAST_OFFSET(SSE::ushort_m, AVX2::double_m, 1) { auto tmp = _mm_unpackhi_epi16(x.dataI(), x.dataI()); return AVX::concat(_mm_unpacklo_epi32(tmp, tmp), _mm_unpackhi_epi32(tmp, tmp)); }
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0 && SSE::is_mask<Return>::value &&
sizeof(AVX2::Mask<T>) == 32),
Return>
simd_cast(AVX2::Mask<T> x)
{
using M = AVX2::Mask<T>;
constexpr int shift = sizeof(M) / M::Size * offset * Return::Size;
static_assert(shift > 0, "");
static_assert(shift < sizeof(M), "");
using SseVector = SSE::Mask<Traits::entry_type_of<typename M::Vector>>;
if (shift == 16) {
return simd_cast<Return>(SseVector{AVX::hi128(x.data())});
}
using Intrin = typename SseVector::VectorType;
return simd_cast<Return>(SseVector{AVX::avx_cast<Intrin>(
_mm_alignr_epi8(AVX::hi128(x.dataI()), AVX::lo128(x.dataI()), shift))});
}
template <typename Return, int offset, typename T>
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0 && SSE::is_mask<Return>::value &&
sizeof(AVX2::Mask<T>) == 16),
Return>
simd_cast(AVX2::Mask<T> x)
{
return simd_cast<Return, offset>(simd_cast<SSE::Mask<T>>(x));
}
#undef Vc_SIMD_CAST_AVX_1
#undef Vc_SIMD_CAST_AVX_2
#undef Vc_SIMD_CAST_AVX_3
#undef Vc_SIMD_CAST_AVX_4
#undef Vc_SIMD_CAST_1
#undef Vc_SIMD_CAST_2
#undef Vc_SIMD_CAST_3
#undef Vc_SIMD_CAST_4
#undef Vc_SIMD_CAST_5
#undef Vc_SIMD_CAST_6
#undef Vc_SIMD_CAST_7
#undef Vc_SIMD_CAST_8
#undef Vc_SIMD_CAST_OFFSET
}
#endif
#endif
#endif
namespace Vc_VERSIONED_NAMESPACE
{
using double_v = Vector<double>;
using float_v = Vector<float>;
using int_v = Vector<int>;
using uint_v = Vector<uint>;
using short_v = Vector<short>;
using ushort_v = Vector<ushort>;
using llong_v = Vector<llong>;
using ullong_v = Vector<ullong>;
using long_v = Vector<long>;
using ulong_v = Vector<ulong>;
using schar_v = Vector<schar>;
using uchar_v = Vector<uchar>;
using double_m = Mask<double>;
using float_m = Mask< float>;
using llong_m = Mask< llong>;
using ullong_m = Mask<ullong>;
using long_m = Mask< long>;
using ulong_m = Mask< ulong>;
using int_m = Mask< int>;
using uint_m = Mask< uint>;
using short_m = Mask< short>;
using ushort_m = Mask<ushort>;
using schar_m = Mask< schar>;
using uchar_m = Mask< uchar>;
typedef Vector<std:: int_least64_t> int_least64_v;
typedef Vector<std::uint_least64_t> uint_least64_v;
typedef Vector<std:: int_least32_t> int_least32_v;
typedef Vector<std::uint_least32_t> uint_least32_v;
typedef Vector<std:: int_least16_t> int_least16_v;
typedef Vector<std::uint_least16_t> uint_least16_v;
typedef Vector<std:: int_least8_t> int_least8_v;
typedef Vector<std:: uint_least8_t> uint_least8_v;
typedef Mask<std:: int_least64_t> int_least64_m;
typedef Mask<std::uint_least64_t> uint_least64_m;
typedef Mask<std:: int_least32_t> int_least32_m;
typedef Mask<std::uint_least32_t> uint_least32_m;
typedef Mask<std:: int_least16_t> int_least16_m;
typedef Mask<std::uint_least16_t> uint_least16_m;
typedef Mask<std:: int_least8_t> int_least8_m;
typedef Mask<std:: uint_least8_t> uint_least8_m;
typedef Vector<std:: int_fast64_t> int_fast64_v;
typedef Vector<std::uint_fast64_t> uint_fast64_v;
typedef Vector<std:: int_fast32_t> int_fast32_v;
typedef Vector<std::uint_fast32_t> uint_fast32_v;
typedef Vector<std:: int_fast16_t> int_fast16_v;
typedef Vector<std::uint_fast16_t> uint_fast16_v;
typedef Vector<std:: int_fast8_t> int_fast8_v;
typedef Vector<std:: uint_fast8_t> uint_fast8_v;
typedef Mask<std:: int_fast64_t> int_fast64_m;
typedef Mask<std::uint_fast64_t> uint_fast64_m;
typedef Mask<std:: int_fast32_t> int_fast32_m;
typedef Mask<std::uint_fast32_t> uint_fast32_m;
typedef Mask<std:: int_fast16_t> int_fast16_m;
typedef Mask<std::uint_fast16_t> uint_fast16_m;
typedef Mask<std:: int_fast8_t> int_fast8_m;
typedef Mask<std:: uint_fast8_t> uint_fast8_m;
#if defined INT64_MAX && defined UINT64_MAX
typedef Vector<std:: int64_t> int64_v;
typedef Vector<std::uint64_t> uint64_v;
typedef Mask<std:: int64_t> int64_m;
typedef Mask<std::uint64_t> uint64_m;
#endif
#if defined INT32_MAX && defined UINT32_MAX
typedef Vector<std:: int32_t> int32_v;
typedef Vector<std::uint32_t> uint32_v;
typedef Mask<std:: int32_t> int32_m;
typedef Mask<std::uint32_t> uint32_m;
#endif
#if defined INT16_MAX && defined UINT16_MAX
typedef Vector<std:: int16_t> int16_v;
typedef Vector<std::uint16_t> uint16_v;
typedef Mask<std:: int16_t> int16_m;
typedef Mask<std::uint16_t> uint16_m;
#endif
#if defined INT8_MAX && defined UINT8_MAX
typedef Vector<std:: int8_t> int8_v;
typedef Vector<std::uint8_t> uint8_v;
typedef Mask<std:: int8_t> int8_m;
typedef Mask<std::uint8_t> uint8_m;
#endif
namespace {
static_assert(double_v::Size == Vc_DOUBLE_V_SIZE, "Vc_DOUBLE_V_SIZE macro defined to an incorrect value");
static_assert(float_v::Size == Vc_FLOAT_V_SIZE , "Vc_FLOAT_V_SIZE macro defined to an incorrect value ");
static_assert(int_v::Size == Vc_INT_V_SIZE , "Vc_INT_V_SIZE macro defined to an incorrect value   ");
static_assert(uint_v::Size == Vc_UINT_V_SIZE , "Vc_UINT_V_SIZE macro defined to an incorrect value  ");
static_assert(short_v::Size == Vc_SHORT_V_SIZE , "Vc_SHORT_V_SIZE macro defined to an incorrect value ");
static_assert(ushort_v::Size == Vc_USHORT_V_SIZE, "Vc_USHORT_V_SIZE macro defined to an incorrect value");
}
}
#ifndef COMMON_OPERATORS_H_
#define COMMON_OPERATORS_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename T, typename Abi, typename U>
enable_if<!std::is_same<T, U>::value, U> is_convertible_to_any_vector(Vector<U, Abi>);
template <typename T, typename Abi> T is_convertible_to_any_vector(Vector<T, Abi>);
template <typename T, typename Abi> void is_convertible_to_any_vector(...);
template <typename T, typename U, bool = std::is_integral<T>::value,
bool = std::is_integral<U>::value>
struct FundamentalReturnType;
template <typename T, typename U> struct FundamentalReturnType<T, U, false, false> {
using type = typename std::conditional<
std::is_arithmetic<U>::value,
typename std::conditional<(sizeof(T) < sizeof(U)), U, T>::type,
T>::type;
};
template <typename T, typename U> struct FundamentalReturnType<T, U, true, false> {
using type = typename std::conditional<
std::is_arithmetic<U>::value, U,
T>::type;
};
template <typename T, typename U> struct FundamentalReturnType<T, U, false, true> {
using type = T;
};
template <typename T> struct my_make_signed : public std::make_signed<T> {
};
template <> struct my_make_signed<bool> {
using type = bool;
};
template <typename TT, typename UU>
struct higher_conversion_rank {
template <typename A>
using fix_sign =
typename std::conditional<(std::is_unsigned<TT>::value ||
std::is_unsigned<UU>::value),
typename std::make_unsigned<A>::type, A>::type;
using T = typename my_make_signed<TT>::type;
using U = typename my_make_signed<UU>::type;
template <typename Test, typename Otherwise>
using c = typename std::conditional<std::is_same<T, Test>::value ||
std::is_same<U, Test>::value,
Test, Otherwise>::type;
using type = fix_sign<c<long long, c<long, c<int, c<short, c<signed char, void>>>>>>;
};
template <typename T, typename U> struct FundamentalReturnType<T, U, true, true> {
template <bool B, class Then, class E>
using c = typename std::conditional<B, Then, E>::type;
using type =
c<(sizeof(T) > sizeof(U)), T,
c<(sizeof(T) < sizeof(U)), U, typename higher_conversion_rank<T, U>::type>>;
};
static_assert(std::is_same<long, typename FundamentalReturnType<int, long>::type>::value, "");
template <typename V, typename T, bool, typename, bool> struct ReturnTypeImpl {
};
template <typename T, typename U, typename Abi, typename Deduced>
struct ReturnTypeImpl<Vector<T, Abi>, Vector<U, Abi>, false, Deduced, false> {
using type = Vc::Vector<typename FundamentalReturnType<T, U>::type, Abi>;
};
template <typename T, typename Abi>
struct ReturnTypeImpl<Vector<T, Abi>, int, true, T, true> {
using type = Vc::Vector<T, Abi>;
};
template <typename T, typename Abi>
struct ReturnTypeImpl<Vector<T, Abi>, unsigned int, true, T, true> {
using type = Vc::Vector<typename std::make_unsigned<T>::type, Abi>;
};
template <typename T, typename U, typename Abi, bool Integral>
struct ReturnTypeImpl<Vector<T, Abi>, U, true, T, Integral> {
using type = Vc::Vector<typename FundamentalReturnType<T, U>::type, Abi>;
};
template <typename T, typename U, typename Abi, bool Integral>
struct ReturnTypeImpl<Vector<T, Abi>, U, false, void, Integral> {
};
template <typename T, typename U, typename Abi, typename V, bool Integral>
struct ReturnTypeImpl<Vector<T, Abi>, U, false, V, Integral> {
using type = Vc::Vector<typename FundamentalReturnType<T, V>::type, Abi>;
};
template <typename V, typename T>
using ReturnType = ReturnTypeImpl<
V, T, std::is_arithmetic<T>::value || std::is_convertible<T, int>::value,
decltype(is_convertible_to_any_vector<typename V::value_type, typename V::abi>(
std::declval<const T &>())),
std::is_integral<typename V::value_type>::value>;
template <typename T> struct is_a_type : public std::true_type {
};
#ifdef Vc_ENABLE_FLOAT_BIT_OPERATORS
#define Vc_TEST_FOR_BUILTIN_OPERATOR(op_) true
#else
#define Vc_TEST_FOR_BUILTIN_OPERATOR(op_) \
Detail::is_a_type<decltype( \
std::declval<typename Detail::ReturnType<Vector<T, Abi>, U>::type::EntryType>() \
op_ std::declval<typename Detail::ReturnType<Vector<T, Abi>, \
U>::type::EntryType>())>::value
#endif
}
#define Vc_GENERIC_OPERATOR(op_) \
template <typename T, typename Abi, typename U, \
class R = typename Detail::ReturnType<Vector<T, Abi>, U>::type> \
Vc_ALWAYS_INLINE enable_if<Vc_TEST_FOR_BUILTIN_OPERATOR(op_) && \
std::is_convertible<Vector<T, Abi>, R>::value && \
std::is_convertible<U, R>::value, \
R> \
operator op_(Vector<T, Abi> x, const U &y) \
{ \
using V = typename Detail::ReturnType<Vector<T, Abi>, U>::type; \
return Detail::operator op_(V(x), V(y)); \
} \
template <typename T, typename Abi, typename U, \
class R = typename Detail::ReturnType<Vector<T, Abi>, U>::type> \
Vc_ALWAYS_INLINE enable_if<Vc_TEST_FOR_BUILTIN_OPERATOR(op_) && \
!Traits::is_simd_vector_internal<U>::value && \
std::is_convertible<Vector<T, Abi>, R>::value && \
std::is_convertible<U, R>::value, \
R> \
operator op_(const U &x, Vector<T, Abi> y) \
{ \
using V = typename Detail::ReturnType<Vector<T, Abi>, U>::type; \
return Detail::operator op_(V(x), V(y)); \
} \
template <typename T, typename Abi, typename U, \
class R = typename Detail::ReturnType<Vector<T, Abi>, U>::type> \
Vc_ALWAYS_INLINE enable_if<Vc_TEST_FOR_BUILTIN_OPERATOR(op_) && \
std::is_convertible<Vector<T, Abi>, R>::value && \
std::is_convertible<U, R>::value, \
Vector<T, Abi> &> \
operator op_##=(Vector<T, Abi> &x, const U &y) \
{ \
using V = typename Detail::ReturnType<Vector<T, Abi>, U>::type; \
x = Detail::operator op_(V(x), V(y)); \
return x; \
}
#define Vc_LOGICAL_OPERATOR(op_) \
template <typename T, typename Abi> \
Vc_ALWAYS_INLINE typename Vector<T, Abi>::Mask operator op_(Vector<T, Abi> x, \
Vector<T, Abi> y) \
{ \
return !!x op_ !!y; \
} \
template <typename T, typename Abi, typename U> \
Vc_ALWAYS_INLINE enable_if< \
std::is_convertible<Vector<T, Abi>, Vector<U, Abi>>::value && \
std::is_convertible<Vector<U, Abi>, Vector<T, Abi>>::value, \
typename Detail::ReturnType<Vector<T, Abi>, Vector<U, Abi>>::type::Mask> \
operator op_(Vector<T, Abi> x, Vector<U, Abi> y) \
{ \
return !!x op_ !!y; \
} \
template <typename T, typename Abi, typename U> \
Vc_ALWAYS_INLINE \
enable_if<std::is_same<bool, decltype(!std::declval<const U &>())>::value, \
typename Vector<T, Abi>::Mask> \
operator op_(Vector<T, Abi> x, const U &y) \
{ \
using M = typename Vector<T, Abi>::Mask; \
return !!x op_ M(!!y); \
} \
template <typename T, typename Abi, typename U> \
Vc_ALWAYS_INLINE \
enable_if<std::is_same<bool, decltype(!std::declval<const U &>())>::value, \
typename Vector<T, Abi>::Mask> \
operator op_(const U &x, Vector<T, Abi> y) \
{ \
using M = typename Vector<T, Abi>::Mask; \
return M(!!x) op_ !!y; \
}
#define Vc_COMPARE_OPERATOR(op_) \
template <typename T, typename Abi, typename U> \
Vc_ALWAYS_INLINE enable_if< \
std::is_convertible<Vector<T, Abi>, typename Detail::ReturnType< \
Vector<T, Abi>, U>::type>::value && \
std::is_convertible< \
U, typename Detail::ReturnType<Vector<T, Abi>, U>::type>::value, \
typename Detail::ReturnType<Vector<T, Abi>, U>::type::Mask> \
operator op_(Vector<T, Abi> x, const U &y) \
{ \
using V = typename Detail::ReturnType<Vector<T, Abi>, U>::type; \
return Detail::operator op_(V(x), V(y)); \
} \
template <typename T, typename Abi, typename U> \
Vc_ALWAYS_INLINE enable_if< \
!Traits::is_simd_vector_internal<U>::value && \
std::is_convertible<Vector<T, Abi>, typename Detail::ReturnType< \
Vector<T, Abi>, U>::type>::value && \
std::is_convertible< \
U, typename Detail::ReturnType<Vector<T, Abi>, U>::type>::value, \
typename Detail::ReturnType<Vector<T, Abi>, U>::type::Mask> \
operator op_(const U &x, Vector<T, Abi> y) \
{ \
using V = typename Detail::ReturnType<Vector<T, Abi>, U>::type; \
return Detail::operator op_(V(x), V(y)); \
}
Vc_ALL_LOGICAL (Vc_LOGICAL_OPERATOR);
Vc_ALL_BINARY (Vc_GENERIC_OPERATOR);
Vc_ALL_ARITHMETICS(Vc_GENERIC_OPERATOR);
Vc_ALL_COMPARES (Vc_COMPARE_OPERATOR);
#undef Vc_LOGICAL_OPERATOR
#undef Vc_GENERIC_OPERATOR
#undef Vc_COMPARE_OPERATOR
#undef Vc_INVALID_OPERATOR
}
#endif
#ifndef VC_COMMON_SIMDARRAY_H_
#define VC_COMMON_SIMDARRAY_H_ 
#include <array>
#ifndef VC_COMMON_SIMDARRAYHELPER_H_
#define VC_COMMON_SIMDARRAYHELPER_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace
{
static constexpr struct private_init_t {} private_init = {};
}
namespace Common
{
namespace Operations
{
struct tag {};
#define Vc_DEFINE_OPERATION(name_) \
struct name_ : public tag { \
template <typename V, typename... Args> \
Vc_INTRINSIC void operator()(V &v, Args &&... args) \
{ \
v.name_(std::forward<Args>(args)...); \
} \
}
Vc_DEFINE_OPERATION(gather);
Vc_DEFINE_OPERATION(scatter);
Vc_DEFINE_OPERATION(load);
Vc_DEFINE_OPERATION(store);
Vc_DEFINE_OPERATION(setZero);
Vc_DEFINE_OPERATION(setZeroInverted);
Vc_DEFINE_OPERATION(assign);
#undef Vc_DEFINE_OPERATION
#define Vc_DEFINE_OPERATION(name_,code_) \
struct name_ : public tag { \
template <typename V> Vc_INTRINSIC void operator()(V &v) { code_; } \
}
Vc_DEFINE_OPERATION(increment, ++(v));
Vc_DEFINE_OPERATION(decrement, --(v));
Vc_DEFINE_OPERATION(random, v = V::Random());
#undef Vc_DEFINE_OPERATION
#define Vc_DEFINE_OPERATION_FORWARD(name_) \
struct Forward_##name_ : public tag \
{ \
template <typename... Args, typename = decltype(name_(std::declval<Args>()...))> \
Vc_INTRINSIC void operator()(decltype(name_(std::declval<Args>()...)) &v, \
Args &&... args) \
{ \
v = name_(std::forward<Args>(args)...); \
} \
template <typename... Args, typename = decltype(name_(std::declval<Args>()...))> \
Vc_INTRINSIC void operator()(std::nullptr_t, Args && ... args) \
{ \
name_(std::forward<Args>(args)...); \
} \
}
Vc_DEFINE_OPERATION_FORWARD(abs);
Vc_DEFINE_OPERATION_FORWARD(asin);
Vc_DEFINE_OPERATION_FORWARD(atan);
Vc_DEFINE_OPERATION_FORWARD(atan2);
Vc_DEFINE_OPERATION_FORWARD(cos);
Vc_DEFINE_OPERATION_FORWARD(ceil);
Vc_DEFINE_OPERATION_FORWARD(copysign);
Vc_DEFINE_OPERATION_FORWARD(exp);
Vc_DEFINE_OPERATION_FORWARD(exponent);
Vc_DEFINE_OPERATION_FORWARD(fma);
Vc_DEFINE_OPERATION_FORWARD(floor);
Vc_DEFINE_OPERATION_FORWARD(frexp);
Vc_DEFINE_OPERATION_FORWARD(isfinite);
Vc_DEFINE_OPERATION_FORWARD(isinf);
Vc_DEFINE_OPERATION_FORWARD(isnan);
Vc_DEFINE_OPERATION_FORWARD(isnegative);
Vc_DEFINE_OPERATION_FORWARD(ldexp);
Vc_DEFINE_OPERATION_FORWARD(log);
Vc_DEFINE_OPERATION_FORWARD(log10);
Vc_DEFINE_OPERATION_FORWARD(log2);
Vc_DEFINE_OPERATION_FORWARD(reciprocal);
Vc_DEFINE_OPERATION_FORWARD(round);
Vc_DEFINE_OPERATION_FORWARD(rsqrt);
Vc_DEFINE_OPERATION_FORWARD(sin);
Vc_DEFINE_OPERATION_FORWARD(sincos);
Vc_DEFINE_OPERATION_FORWARD(sqrt);
Vc_DEFINE_OPERATION_FORWARD(trunc);
Vc_DEFINE_OPERATION_FORWARD(min);
Vc_DEFINE_OPERATION_FORWARD(max);
#undef Vc_DEFINE_OPERATION_FORWARD
template<typename T> using is_operation = std::is_base_of<tag, T>;
}
template <typename T_, std::size_t Pieces_, std::size_t Index_> struct Segment
{
static_assert(Index_ < Pieces_, "You found a bug in Vc. Please report.");
using type = T_;
using type_decayed = typename std::decay<type>::type;
static constexpr std::size_t Pieces = Pieces_;
static constexpr std::size_t Index = Index_;
using simd_array_type = SimdArray<
typename std::conditional<Traits::is_simd_vector<type_decayed>::value,
typename type_decayed::EntryType, float>::type,
type_decayed::Size / Pieces>;
type data;
static constexpr std::size_t EntryOffset = Index * type_decayed::Size / Pieces;
decltype(std::declval<const type &>()[0]) operator[](size_t i) const { return data[i + EntryOffset]; }
simd_array_type asSimdArray() const
{
return simd_cast<simd_array_type, Index>(data);
}
};
template <typename T_, std::size_t Pieces_, std::size_t Index_>
struct Segment<T_ *, Pieces_, Index_> {
static_assert(Index_ < Pieces_, "You found a bug in Vc. Please report.");
using type = T_ *;
using type_decayed = typename std::decay<T_>::type;
static constexpr size_t Pieces = Pieces_;
static constexpr size_t Index = Index_;
using simd_array_type = SimdArray<
typename std::conditional<Traits::is_simd_vector<type_decayed>::value,
typename type_decayed::VectorEntryType, float>::type,
type_decayed::Size / Pieces> *;
type data;
static constexpr std::size_t EntryOffset = Index * type_decayed::size() / Pieces;
simd_array_type asSimdArray() const
{
return reinterpret_cast<
#ifdef Vc_GCC
typename std::remove_pointer<simd_array_type>::type
#else
MayAlias<typename std::remove_pointer<simd_array_type>::type>
#endif
*>(data) +
Index;
}
};
template <typename T, std::size_t Offset> struct AddOffset
{
constexpr AddOffset() = default;
};
template <std::size_t secondOffset> class Split
{
template <class G>
struct GeneratorOffset {
G gen;
Vc_INTRINSIC decltype(gen(std::size_t())) operator()(std::size_t i)
{
return gen(i + secondOffset);
}
};
template <class G, class = decltype(std::declval<G>()(std::size_t())),
class = typename std::enable_if<!Traits::is_simd_vector<G>::value>::type>
static Vc_INTRINSIC GeneratorOffset<G> hiImpl(G &&gen)
{
return {std::forward<G>(gen)};
}
static Vc_INTRINSIC AddOffset<VectorSpecialInitializerIndexesFromZero, secondOffset>
hiImpl(VectorSpecialInitializerIndexesFromZero)
{
return {};
}
template <std::size_t Offset>
static Vc_INTRINSIC
AddOffset<VectorSpecialInitializerIndexesFromZero, Offset + secondOffset>
hiImpl(AddOffset<VectorSpecialInitializerIndexesFromZero, Offset>)
{
return {};
}
template <typename U, std::size_t N, typename V, std::size_t M,
typename = enable_if<N != M>>
static Vc_INTRINSIC auto loImpl(const SimdArray<U, N, V, M> &x)
-> decltype(internal_data0(x))
{
return internal_data0(x);
}
template <typename U, std::size_t N, typename V, std::size_t M,
typename = enable_if<N != M>>
static Vc_INTRINSIC auto hiImpl(const SimdArray<U, N, V, M> &x)
-> decltype(internal_data1(x))
{
return internal_data1(x);
}
template <typename U, std::size_t N, typename V, std::size_t M,
typename = enable_if<N != M>>
static Vc_INTRINSIC auto loImpl(SimdArray<U, N, V, M> *x)
-> decltype(&internal_data0(*x))
{
return &internal_data0(*x);
}
template <typename U, std::size_t N, typename V, std::size_t M,
typename = enable_if<N != M>>
static Vc_INTRINSIC auto hiImpl(SimdArray<U, N, V, M> *x)
-> decltype(&internal_data1(*x))
{
return &internal_data1(*x);
}
template <typename U, std::size_t N, typename V>
static Vc_INTRINSIC Segment<V, 2, 0> loImpl(const SimdArray<U, N, V, N> &x)
{
return {internal_data(x)};
}
template <typename U, std::size_t N, typename V>
static Vc_INTRINSIC Segment<V, 2, 1> hiImpl(const SimdArray<U, N, V, N> &x)
{
return {internal_data(x)};
}
template <typename U, std::size_t N, typename V>
static Vc_INTRINSIC Segment<V *, 2, 0> loImpl(SimdArray<U, N, V, N> *x)
{
return {&internal_data(*x)};
}
template <typename U, std::size_t N, typename V>
static Vc_INTRINSIC Segment<V *, 2, 1> hiImpl(SimdArray<U, N, V, N> *x)
{
return {&internal_data(*x)};
}
template <typename U, std::size_t N, typename V, std::size_t M>
static Vc_INTRINSIC auto loImpl(const SimdMaskArray<U, N, V, M> &x) -> decltype(internal_data0(x))
{
return internal_data0(x);
}
template <typename U, std::size_t N, typename V, std::size_t M>
static Vc_INTRINSIC auto hiImpl(const SimdMaskArray<U, N, V, M> &x) -> decltype(internal_data1(x))
{
return internal_data1(x);
}
template <typename U, std::size_t N, typename V>
static Vc_INTRINSIC Segment<typename SimdMaskArray<U, N, V, N>::mask_type, 2, 0> loImpl(
const SimdMaskArray<U, N, V, N> &x)
{
return {internal_data(x)};
}
template <typename U, std::size_t N, typename V>
static Vc_INTRINSIC Segment<typename SimdMaskArray<U, N, V, N>::mask_type, 2, 1> hiImpl(
const SimdMaskArray<U, N, V, N> &x)
{
return {internal_data(x)};
}
template <typename T>
static constexpr bool is_vector_or_mask(){
return (Traits::is_simd_vector<T>::value && !Traits::isSimdArray<T>::value) ||
(Traits::is_simd_mask<T>::value && !Traits::isSimdMaskArray<T>::value);
}
template <typename V>
static Vc_INTRINSIC Segment<V, 2, 0> loImpl(V &&x, enable_if<is_vector_or_mask<V>()> = nullarg)
{
return {std::forward<V>(x)};
}
template <typename V>
static Vc_INTRINSIC Segment<V, 2, 1> hiImpl(V &&x, enable_if<is_vector_or_mask<V>()> = nullarg)
{
return {std::forward<V>(x)};
}
template <typename V, std::size_t Pieces, std::size_t Index>
static Vc_INTRINSIC Segment<V, 2 * Pieces, 2 * Index> loImpl(
const Segment<V, Pieces, Index> &x)
{
return {x.data};
}
template <typename V, std::size_t Pieces, std::size_t Index>
static Vc_INTRINSIC Segment<V, 2 * Pieces, 2 * Index + 1> hiImpl(
const Segment<V, Pieces, Index> &x)
{
return {x.data};
}
template <typename T, typename = decltype(loImpl(std::declval<T>()))>
static std::true_type have_lo_impl(int);
template <typename T> static std::false_type have_lo_impl(float);
template <typename T> static constexpr bool have_lo_impl()
{
return decltype(have_lo_impl<T>(1))::value;
}
template <typename T, typename = decltype(hiImpl(std::declval<T>()))>
static std::true_type have_hi_impl(int);
template <typename T> static std::false_type have_hi_impl(float);
template <typename T> static constexpr bool have_hi_impl()
{
return decltype(have_hi_impl<T>(1))::value;
}
public:
template <typename U>
static Vc_INTRINSIC const U *lo(Operations::gather, const U *ptr)
{
return ptr;
}
template <typename U>
static Vc_INTRINSIC const U *hi(Operations::gather, const U *ptr)
{
return ptr + secondOffset;
}
template <typename U, typename = enable_if<!std::is_pointer<U>::value>>
static Vc_ALWAYS_INLINE decltype(loImpl(std::declval<U>()))
lo(Operations::gather, U &&x)
{
return loImpl(std::forward<U>(x));
}
template <typename U, typename = enable_if<!std::is_pointer<U>::value>>
static Vc_ALWAYS_INLINE decltype(hiImpl(std::declval<U>()))
hi(Operations::gather, U &&x)
{
return hiImpl(std::forward<U>(x));
}
template <typename U>
static Vc_INTRINSIC const U *lo(Operations::scatter, const U *ptr)
{
return ptr;
}
template <typename U>
static Vc_INTRINSIC const U *hi(Operations::scatter, const U *ptr)
{
return ptr + secondOffset;
}
template <typename U>
static Vc_ALWAYS_INLINE decltype(loImpl(std::declval<U>())) lo(U &&x)
{
return loImpl(std::forward<U>(x));
}
template <typename U>
static Vc_ALWAYS_INLINE decltype(hiImpl(std::declval<U>())) hi(U &&x)
{
return hiImpl(std::forward<U>(x));
}
template <typename U>
static Vc_ALWAYS_INLINE enable_if<!have_lo_impl<U>(), U> lo(U &&x)
{
return std::forward<U>(x);
}
template <typename U>
static Vc_ALWAYS_INLINE enable_if<!have_hi_impl<U>(), U> hi(U &&x)
{
return std::forward<U>(x);
}
};
template <typename Op, typename U, std::size_t M, typename V>
static Vc_INTRINSIC const V &actual_value(Op, const SimdArray<U, M, V, M> &x)
{
return internal_data(x);
}
template <typename Op, typename U, std::size_t M, typename V>
static Vc_INTRINSIC V *actual_value(Op, SimdArray<U, M, V, M> *x)
{
return &internal_data(*x);
}
template <typename Op, typename T, size_t Pieces, size_t Index>
static Vc_INTRINSIC typename Segment<T, Pieces, Index>::simd_array_type actual_value(
Op, Segment<T, Pieces, Index> &&seg)
{
return seg.asSimdArray();
}
template <typename Op, typename U, std::size_t M, typename V>
static Vc_INTRINSIC const typename V::Mask &actual_value(Op, const SimdMaskArray<U, M, V, M> &x)
{
return internal_data(x);
}
template <typename Op, typename U, std::size_t M, typename V>
static Vc_INTRINSIC typename V::Mask *actual_value(Op, SimdMaskArray<U, M, V, M> *x)
{
return &internal_data(*x);
}
template <typename Op, typename Arg>
Vc_INTRINSIC decltype(actual_value(std::declval<Op &>(), std::declval<Arg>()))
conditionalUnpack(std::true_type, Op op, Arg &&arg)
{
return actual_value(op, std::forward<Arg>(arg));
}
template <typename Op, typename Arg>
Vc_INTRINSIC Arg conditionalUnpack(std::false_type, Op, Arg &&arg)
{
return std::forward<Arg>(arg);
}
template <size_t A, size_t B>
struct selectorType : public std::integral_constant<bool, !((A & (size_t(1) << B)) != 0)> {
};
template <size_t I, typename Op, typename R, typename... Args, size_t... Indexes>
Vc_INTRINSIC decltype(std::declval<Op &>()(std::declval<R &>(),
conditionalUnpack(selectorType<I, Indexes>(),
std::declval<Op &>(),
std::declval<Args>())...))
unpackArgumentsAutoImpl(int, index_sequence<Indexes...>, Op op, R &&r, Args &&... args)
{
op(std::forward<R>(r),
conditionalUnpack(selectorType<I, Indexes>(), op, std::forward<Args>(args))...);
}
template <size_t I, typename Op, typename R, typename... Args, size_t... Indexes>
Vc_INTRINSIC enable_if<(I <= (size_t(1) << sizeof...(Args))), void> unpackArgumentsAutoImpl(
float, index_sequence<Indexes...> is, Op op, R &&r, Args &&... args)
{
static_assert(
I < (1 << sizeof...(Args)) - (std::is_same<R, std::nullptr_t>::value ? 1 : 0),
"Vc or compiler bug. Please report. Failed to find a combination of "
"actual_value(arg) transformations that allows calling Op.");
unpackArgumentsAutoImpl<I + 1, Op, R, Args...>(int(), is, op, std::forward<R>(r),
std::forward<Args>(args)...);
}
#ifdef Vc_ICC
template <size_t, typename... Ts> struct IccWorkaround {
using type = void;
};
template <typename... Ts> struct IccWorkaround<2, Ts...> {
using type = typename std::remove_pointer<typename std::decay<
typename std::tuple_element<1, std::tuple<Ts...>>::type>::type>::type;
};
#endif
template <typename Op, typename R, typename... Args>
Vc_INTRINSIC void unpackArgumentsAuto(Op op, R &&r, Args &&... args)
{
#ifdef Vc_ICC
const int recursionStart =
Traits::isSimdArray<
typename IccWorkaround<sizeof...(Args), Args...>::type>::value &&
(std::is_same<Op, Common::Operations::Forward_frexp>::value ||
std::is_same<Op, Common::Operations::Forward_ldexp>::value)
? 2
: 0;
#else
const int recursionStart = 0;
#endif
unpackArgumentsAutoImpl<recursionStart>(
int(), make_index_sequence<sizeof...(Args)>(), op, std::forward<R>(r),
std::forward<Args>(args)...);
}
}
}
#endif
#ifndef VC_COMMON_SIMDMASKARRAY_H_
#define VC_COMMON_SIMDMASKARRAY_H_ 
#include <type_traits>
#include <array>
namespace Vc_VERSIONED_NAMESPACE
{
template <typename T, std::size_t N, typename VectorType_>
class SimdMaskArray<T, N, VectorType_, N>
{
public:
using VectorType = VectorType_;
using vector_type = VectorType;
using mask_type = typename vector_type::Mask;
using storage_type = mask_type;
friend storage_type &internal_data(SimdMaskArray &m) { return m.data; }
friend const storage_type &internal_data(const SimdMaskArray &m) { return m.data; }
static constexpr std::size_t size() { return N; }
static constexpr std::size_t Size = size();
static constexpr std::size_t MemoryAlignment = storage_type::MemoryAlignment;
static_assert(Size == vector_type::Size, "size mismatch");
using vectorentry_type = typename mask_type::VectorEntryType;
using value_type = typename mask_type::EntryType;
using Mask = mask_type;
using VectorEntryType = vectorentry_type;
using EntryType = value_type;
using EntryReference = Vc::Detail::ElementReference<storage_type, SimdMaskArray>;
using reference = EntryReference;
using Vector = SimdArray<T, N, VectorType, N>;
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(mask_type));
SimdMaskArray() = default;
Vc_INTRINSIC explicit SimdMaskArray(VectorSpecialInitializerOne one) : data(one) {}
Vc_INTRINSIC explicit SimdMaskArray(VectorSpecialInitializerZero zero) : data(zero) {}
Vc_INTRINSIC explicit SimdMaskArray(bool b) : data(b) {}
Vc_INTRINSIC static SimdMaskArray Zero() { return {private_init, storage_type::Zero()}; }
Vc_INTRINSIC static SimdMaskArray One() { return {private_init, storage_type::One()}; }
template <typename U, typename V>
Vc_INTRINSIC_L SimdMaskArray(const SimdMaskArray<U, N, V> &x,
enable_if<N == V::Size> = nullarg) Vc_INTRINSIC_R;
template <typename U, typename V>
Vc_INTRINSIC_L SimdMaskArray(const SimdMaskArray<U, N, V> &x,
enable_if<(N > V::Size && N <= 2 * V::Size)> = nullarg)
Vc_INTRINSIC_R;
template <typename U, typename V>
Vc_INTRINSIC_L SimdMaskArray(const SimdMaskArray<U, N, V> &x,
enable_if<(N > 2 * V::Size && N <= 4 * V::Size)> = nullarg)
Vc_INTRINSIC_R;
template <typename M, std::size_t Pieces, std::size_t Index>
Vc_INTRINSIC_L SimdMaskArray(
Common::Segment<M, Pieces, Index> &&x,
enable_if<Traits::simd_vector_size<M>::value == Size * Pieces> = nullarg) Vc_INTRINSIC_R;
template <typename M>
Vc_INTRINSIC_L SimdMaskArray(
M k,
enable_if<(Traits::is_simd_mask<M>::value && !Traits::isSimdMaskArray<M>::value &&
Traits::simd_vector_size<M>::value == Size)> = nullarg) Vc_INTRINSIC_R;
template <typename U, typename A, typename = enable_if<Vc::Mask<U, A>::Size == N>>
operator Vc::Mask<U, A>() const
{
return simd_cast<Vc::Mask<U, A>>(data);
}
template <typename Flags = DefaultLoadTag>
Vc_INTRINSIC explicit SimdMaskArray(const bool *mem, Flags f = Flags())
: data(mem, f)
{
}
Vc_INTRINSIC void load(const bool *mem) { data.load(mem); }
template <typename Flags> Vc_INTRINSIC void load(const bool *mem, Flags f)
{
data.load(mem, f);
}
Vc_INTRINSIC void store(bool *mem) const { data.store(mem); }
template <typename Flags> Vc_INTRINSIC void store(bool *mem, Flags f) const
{
data.store(mem, f);
}
Vc_INTRINSIC Vc_PURE bool operator==(const SimdMaskArray &rhs) const
{
return data == rhs.data;
}
Vc_INTRINSIC Vc_PURE bool operator!=(const SimdMaskArray &rhs) const
{
return data != rhs.data;
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator!() const
{
return {private_init, !data};
}
Vc_INTRINSIC SimdMaskArray &operator&=(const SimdMaskArray &rhs)
{
data &= rhs.data;
return *this;
}
Vc_INTRINSIC SimdMaskArray &operator|=(const SimdMaskArray &rhs)
{
data |= rhs.data;
return *this;
}
Vc_INTRINSIC SimdMaskArray &operator^=(const SimdMaskArray &rhs)
{
data ^= rhs.data;
return *this;
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator&(const SimdMaskArray &rhs) const
{
return {private_init, data & rhs.data};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator|(const SimdMaskArray &rhs) const
{
return {private_init, data | rhs.data};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator^(const SimdMaskArray &rhs) const
{
return {private_init, data ^ rhs.data};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator&&(const SimdMaskArray &rhs) const
{
return {private_init, data && rhs.data};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator||(const SimdMaskArray &rhs) const
{
return {private_init, data || rhs.data};
}
Vc_INTRINSIC Vc_PURE bool isFull() const { return data.isFull(); }
Vc_INTRINSIC Vc_PURE bool isNotEmpty() const { return data.isNotEmpty(); }
Vc_INTRINSIC Vc_PURE bool isEmpty() const { return data.isEmpty(); }
Vc_INTRINSIC Vc_PURE bool isMix() const { return data.isMix(); }
Vc_INTRINSIC Vc_PURE int shiftMask() const { return data.shiftMask(); }
Vc_INTRINSIC Vc_PURE int toInt() const { return data.toInt(); }
private:
friend reference;
static Vc_INTRINSIC value_type get(const storage_type &k, int i) noexcept
{
return k[i];
}
template <typename U>
static Vc_INTRINSIC void set(storage_type &k, int i, U &&v) noexcept(
noexcept(std::declval<storage_type &>()[0] = std::declval<U>()))
{
k[i] = std::forward<U>(v);
}
public:
Vc_INTRINSIC Vc_PURE reference operator[](size_t index) noexcept
{
return {data, int(index)};
}
Vc_INTRINSIC Vc_PURE value_type operator[](size_t index) const noexcept
{
return data[index];
}
Vc_INTRINSIC Vc_PURE int count() const { return data.count(); }
Vc_INTRINSIC Vc_PURE int firstOne() const { return data.firstOne(); }
template <typename G> static Vc_INTRINSIC SimdMaskArray generate(const G &gen)
{
return {private_init, mask_type::generate(gen)};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray shifted(int amount) const
{
return {private_init, data.shifted(amount)};
}
template <typename Op, typename... Args>
static Vc_INTRINSIC SimdMaskArray fromOperation(Op op, Args &&... args)
{
SimdMaskArray r;
Common::unpackArgumentsAuto(op, r.data, std::forward<Args>(args)...);
return r;
}
Vc_INTRINSIC SimdMaskArray(private_init_t, mask_type &&x) : data(std::move(x)) {}
private:
alignas(static_cast<std::size_t>(
Common::BoundedAlignment<Common::NextPowerOfTwo<N>::value * sizeof(VectorType_) /
VectorType_::size()>::value)) storage_type data;
};
template <typename T, std::size_t N, typename VectorType> constexpr std::size_t SimdMaskArray<T, N, VectorType, N>::Size;
template <typename T, std::size_t N, typename VectorType>
constexpr std::size_t SimdMaskArray<T, N, VectorType, N>::MemoryAlignment;
template <typename T, size_t N, typename V, size_t Wt>
class SimdMaskArray
{
static constexpr std::size_t N0 = Common::left_size<N>();
using Split = Common::Split<N0>;
public:
using storage_type0 = SimdMaskArray<T, N0>;
using storage_type1 = SimdMaskArray<T, N - N0>;
static_assert(storage_type0::size() == N0, "");
using vector_type = SimdArray<T, N>;
friend storage_type0 &internal_data0(SimdMaskArray &m) { return m.data0; }
friend storage_type1 &internal_data1(SimdMaskArray &m) { return m.data1; }
friend const storage_type0 &internal_data0(const SimdMaskArray &m) { return m.data0; }
friend const storage_type1 &internal_data1(const SimdMaskArray &m) { return m.data1; }
using mask_type = SimdMaskArray;
static constexpr std::size_t size() { return N; }
static constexpr std::size_t Size = size();
static constexpr std::size_t MemoryAlignment =
storage_type0::MemoryAlignment > storage_type1::MemoryAlignment
? storage_type0::MemoryAlignment
: storage_type1::MemoryAlignment;
static_assert(Size == vector_type::Size, "size mismatch");
using vectorentry_type = typename storage_type0::VectorEntryType;
using value_type = typename storage_type0::EntryType;
using MaskType = mask_type;
using VectorEntryType = vectorentry_type;
using EntryType = value_type;
using EntryReference = Vc::Detail::ElementReference<SimdMaskArray>;
using reference = EntryReference;
using Vector = SimdArray<T, N, V, V::Size>;
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(mask_type));
SimdMaskArray() = default;
SimdMaskArray(const SimdMaskArray &) = default;
SimdMaskArray(SimdMaskArray &&) = default;
SimdMaskArray &operator=(const SimdMaskArray &) = default;
SimdMaskArray &operator=(SimdMaskArray &&) = default;
template <typename U, typename W>
Vc_INTRINSIC SimdMaskArray(const SimdMaskArray<U, N, W> &rhs)
: data0(Split::lo(rhs)), data1(Split::hi(rhs))
{
}
template <typename M, std::size_t Pieces, std::size_t Index>
Vc_INTRINSIC SimdMaskArray(
Common::Segment<M, Pieces, Index> &&rhs,
enable_if<Traits::simd_vector_size<M>::value == Size * Pieces> = nullarg)
: data0(Split::lo(rhs)), data1(Split::hi(rhs))
{
}
template <typename M>
Vc_INTRINSIC SimdMaskArray(
M k,
enable_if<(Traits::is_simd_mask<M>::value && !Traits::isSimdMaskArray<M>::value &&
Traits::simd_vector_size<M>::value == Size)> = nullarg)
: data0(Split::lo(k)), data1(Split::hi(k))
{
}
template <typename U, typename A, typename = enable_if<Vc::Mask<U, A>::Size == N>>
operator Vc::Mask<U, A>() const
{
return simd_cast<Vc::Mask<U, A>>(data0, data1);
}
Vc_INTRINSIC explicit SimdMaskArray(VectorSpecialInitializerOne one)
: data0(one), data1(one)
{
}
Vc_INTRINSIC explicit SimdMaskArray(VectorSpecialInitializerZero zero)
: data0(zero), data1(zero)
{
}
Vc_INTRINSIC explicit SimdMaskArray(bool b) : data0(b), data1(b) {}
Vc_INTRINSIC static SimdMaskArray Zero() { return {storage_type0::Zero(), storage_type1::Zero()}; }
Vc_INTRINSIC static SimdMaskArray One() { return {storage_type0::One(), storage_type1::One()}; }
template <typename Flags = DefaultLoadTag>
Vc_INTRINSIC explicit SimdMaskArray(const bool *mem, Flags f = Flags())
: data0(mem, f), data1(mem + storage_type0::size(), f)
{
}
Vc_INTRINSIC void load(const bool *mem)
{
data0.load(mem);
data1.load(mem + storage_type0::size());
}
template <typename Flags> Vc_INTRINSIC void load(const bool *mem, Flags f)
{
data0.load(mem, f);
data1.load(mem + storage_type0::size(), f);
}
Vc_INTRINSIC void store(bool *mem) const
{
data0.store(mem);
data1.store(mem + storage_type0::size());
}
template <typename Flags> Vc_INTRINSIC void store(bool *mem, Flags f) const
{
data0.store(mem, f);
data1.store(mem + storage_type0::size(), f);
}
Vc_INTRINSIC Vc_PURE bool operator==(const SimdMaskArray &mask) const
{
return data0 == mask.data0 && data1 == mask.data1;
}
Vc_INTRINSIC Vc_PURE bool operator!=(const SimdMaskArray &mask) const
{
return data0 != mask.data0 || data1 != mask.data1;
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator!() const
{
return {!data0, !data1};
}
Vc_INTRINSIC SimdMaskArray &operator&=(const SimdMaskArray &rhs)
{
data0 &= rhs.data0;
data1 &= rhs.data1;
return *this;
}
Vc_INTRINSIC SimdMaskArray &operator|=(const SimdMaskArray &rhs)
{
data0 |= rhs.data0;
data1 |= rhs.data1;
return *this;
}
Vc_INTRINSIC SimdMaskArray &operator^=(const SimdMaskArray &rhs)
{
data0 ^= rhs.data0;
data1 ^= rhs.data1;
return *this;
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator&(const SimdMaskArray &rhs) const
{
return {data0 & rhs.data0, data1 & rhs.data1};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator|(const SimdMaskArray &rhs) const
{
return {data0 | rhs.data0, data1 | rhs.data1};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator^(const SimdMaskArray &rhs) const
{
return {data0 ^ rhs.data0, data1 ^ rhs.data1};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator&&(const SimdMaskArray &rhs) const
{
return {data0 && rhs.data0, data1 && rhs.data1};
}
Vc_INTRINSIC Vc_PURE SimdMaskArray operator||(const SimdMaskArray &rhs) const
{
return {data0 || rhs.data0, data1 || rhs.data1};
}
Vc_INTRINSIC Vc_PURE bool isFull() const { return data0.isFull() && data1.isFull(); }
Vc_INTRINSIC Vc_PURE bool isNotEmpty() const { return data0.isNotEmpty() || data1.isNotEmpty(); }
Vc_INTRINSIC Vc_PURE bool isEmpty() const { return data0.isEmpty() && data1.isEmpty(); }
Vc_INTRINSIC Vc_PURE bool isMix() const { return !isFull() && !isEmpty(); }
Vc_INTRINSIC Vc_PURE int toInt() const
{
return data0.toInt() | (data1.toInt() << data0.size());
}
private:
friend reference;
static Vc_INTRINSIC value_type get(const SimdMaskArray &o, int i) noexcept
{
if (i < int(o.data0.size())) {
return o.data0[i];
} else {
return o.data1[i - o.data0.size()];
}
}
template <typename U>
static Vc_INTRINSIC void set(SimdMaskArray &o, int i, U &&v) noexcept(
noexcept(std::declval<storage_type0 &>()[0] = std::declval<U>()) &&
noexcept(std::declval<storage_type1 &>()[0] = std::declval<U>()))
{
if (i < int(o.data0.size())) {
o.data0[i] = std::forward<U>(v);
} else {
o.data1[i - o.data0.size()] = std::forward<U>(v);
}
}
public:
Vc_INTRINSIC Vc_PURE reference operator[](size_t index) noexcept
{
return {*this, int(index)};
}
Vc_INTRINSIC Vc_PURE value_type operator[](size_t index) const noexcept
{
return get(*this, index);
}
Vc_INTRINSIC Vc_PURE int count() const { return data0.count() + data1.count(); }
Vc_INTRINSIC Vc_PURE int firstOne() const {
if (data0.isEmpty()) {
return data1.firstOne() + storage_type0::size();
}
return data0.firstOne();
}
template <typename G> static Vc_INTRINSIC SimdMaskArray generate(const G &gen)
{
return {storage_type0::generate(gen),
storage_type1::generate([&](std::size_t i) { return gen(i + N0); })};
}
inline Vc_PURE SimdMaskArray shifted(int amount) const
{
if (Vc_IS_UNLIKELY(amount == 0)) {
return *this;
}
return generate([&](unsigned i) {
const unsigned j = i + amount;
return j < size() ? get(*this, j) : false;
});
}
template <typename Op, typename... Args>
static Vc_INTRINSIC SimdMaskArray fromOperation(Op op, Args &&... args)
{
SimdMaskArray r = {
storage_type0::fromOperation(op, Split::lo(args)...),
storage_type1::fromOperation(op, Split::hi(std::forward<Args>(args))...)};
return r;
}
Vc_INTRINSIC SimdMaskArray(storage_type0 &&x, storage_type1 &&y)
: data0(std::move(x)), data1(std::move(y))
{
}
private:
alignas(static_cast<std::size_t>(
Common::BoundedAlignment<Common::NextPowerOfTwo<N>::value * sizeof(V) /
V::size()>::value)) storage_type0 data0;
storage_type1 data1;
};
template <typename T, std::size_t N, typename V, std::size_t M>
constexpr std::size_t SimdMaskArray<T, N, V, M>::Size;
template <typename T, std::size_t N, typename V, std::size_t M>
constexpr std::size_t SimdMaskArray<T, N, V, M>::MemoryAlignment;
}
#ifndef VC_COMMON_SIMD_CAST_CALLER_TCC_
#define VC_COMMON_SIMD_CAST_CALLER_TCC_ 
namespace Vc_VERSIONED_NAMESPACE {
template <typename T, std::size_t N, typename VectorType>
template <typename U, typename V>
Vc_INTRINSIC SimdMaskArray<T, N, VectorType, N>::SimdMaskArray(
const SimdMaskArray<U, N, V> &x,
enable_if<N == V::Size>)
: data(simd_cast<mask_type>(internal_data(x)))
{
}
template <typename T, std::size_t N, typename VectorType>
template <typename U, typename V>
Vc_INTRINSIC SimdMaskArray<T, N, VectorType, N>::SimdMaskArray(
const SimdMaskArray<U, N, V> &x,
enable_if<(N > V::Size && N <= 2 * V::Size)>)
: data(simd_cast<mask_type>(internal_data(internal_data0(x)), internal_data(internal_data1(x))))
{
}
template <typename T, std::size_t N, typename VectorType>
template <typename U, typename V>
Vc_INTRINSIC SimdMaskArray<T, N, VectorType, N>::SimdMaskArray(
const SimdMaskArray<U, N, V> &x,
enable_if<(N > 2 * V::Size && N <= 4 * V::Size)>)
: data(simd_cast<mask_type>(internal_data(internal_data0(internal_data0(x))),
internal_data(internal_data1(internal_data0(x))),
internal_data(internal_data0(internal_data1(x))),
internal_data(internal_data1(internal_data1(x)))))
{
}
template <typename T, std::size_t N, typename VectorType>
template <typename M, std::size_t Pieces, std::size_t Index>
Vc_INTRINSIC SimdMaskArray<T, N, VectorType, N>::SimdMaskArray(
Common::Segment<M, Pieces, Index> &&x,
enable_if<Traits::simd_vector_size<M>::value == Size * Pieces>)
: data(simd_cast<mask_type, Index>(x.data))
{
}
template <typename T, std::size_t N, typename VectorType>
template <typename M>
Vc_INTRINSIC SimdMaskArray<T, N, VectorType, N>::SimdMaskArray(
M k,
enable_if<(Traits::is_simd_mask<M>::value && !Traits::isSimdMaskArray<M>::value &&
Traits::simd_vector_size<M>::value == Size)>)
: data(simd_cast<mask_type>(k))
{
}
}
#endif
#endif
#ifndef VC_COMMON_INTERLEAVE_H_
#define VC_COMMON_INTERLEAVE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
template <typename V, typename = enable_if<Traits::is_simd_vector<V>::value>>
std::pair<V, V> interleave(const V &a, const V &b)
{
return {a.interleaveLow(b), a.interleaveHigh(b)};
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template <std::size_t N, class... Candidates> struct select_best_vector_type_impl;
template <std::size_t N, class T> struct select_best_vector_type_impl<N, T> {
using type = T;
};
template <std::size_t N, class T, class... Candidates>
struct select_best_vector_type_impl<N, T, Candidates...> {
using type = typename std::conditional<
(N < T::Size), typename select_best_vector_type_impl<N, Candidates...>::type,
T>::type;
};
template <class T, std::size_t N>
struct select_best_vector_type : select_best_vector_type_impl<N,
#ifdef Vc_IMPL_AVX2
Vc::AVX2::Vector<T>,
#elif defined Vc_IMPL_AVX
Vc::AVX::Vector<T>,
#endif
#ifdef Vc_IMPL_SSE
Vc::SSE::Vector<T>,
#endif
Vc::Scalar::Vector<T>> {
};
}
namespace internal
{
template <typename T> T Vc_INTRINSIC Vc_PURE product_helper_(const T &l, const T &r) { return l * r; }
template <typename T> T Vc_INTRINSIC Vc_PURE sum_helper_(const T &l, const T &r) { return l + r; }
}
template <typename T, std::size_t N, typename V, std::size_t M>
inline SimdArray<T, N, V, M> min(const SimdArray<T, N, V, M> &x,
const SimdArray<T, N, V, M> &y);
template <typename T, std::size_t N, typename V, std::size_t M>
inline SimdArray<T, N, V, M> max(const SimdArray<T, N, V, M> &x,
const SimdArray<T, N, V, M> &y);
#define Vc_CURRENT_CLASS_NAME SimdArray
template <typename T, std::size_t N, typename VectorType_>
class SimdArray<T, N, VectorType_, N>
{
static_assert(std::is_same<T, double>::value || std::is_same<T, float>::value ||
std::is_same<T, int32_t>::value ||
std::is_same<T, uint32_t>::value ||
std::is_same<T, int16_t>::value ||
std::is_same<T, uint16_t>::value,
"SimdArray<T, N> may only be used with T = { double, float, int32_t, uint32_t, "
"int16_t, uint16_t }");
public:
using VectorType = VectorType_;
using vector_type = VectorType;
using storage_type = vector_type;
using vectorentry_type = typename vector_type::VectorEntryType;
using value_type = T;
using mask_type = SimdMaskArray<T, N, vector_type>;
using index_type = SimdArray<int, N>;
static constexpr std::size_t size() { return N; }
using Mask = mask_type;
using MaskType = Mask;
using MaskArgument = const MaskType &;
using VectorEntryType = vectorentry_type;
using EntryType = value_type;
using IndexType = index_type;
using AsArg = const SimdArray &;
using reference = Detail::ElementReference<SimdArray>;
static constexpr std::size_t Size = size();
static constexpr std::size_t MemoryAlignment = storage_type::MemoryAlignment;
#ifndef Vc_MSVC
Vc_INTRINSIC SimdArray() = default;
#endif
Vc_INTRINSIC SimdArray(const SimdArray &) = default;
Vc_INTRINSIC SimdArray(SimdArray &&) = default;
Vc_INTRINSIC SimdArray &operator=(const SimdArray &) = default;
Vc_INTRINSIC SimdArray(const value_type &a) : data(a) {}
Vc_INTRINSIC SimdArray(value_type &a) : data(a) {}
Vc_INTRINSIC SimdArray(value_type &&a) : data(a) {}
template <
typename U,
typename = enable_if<std::is_same<U, int>::value && !std::is_same<int, value_type>::value>>
Vc_INTRINSIC SimdArray(U a)
: SimdArray(static_cast<value_type>(a))
{
}
template <class U, class V, class..., class = enable_if<N == V::Size>>
Vc_INTRINSIC SimdArray(const SimdArray<U, N, V> &x)
: data(simd_cast<vector_type>(internal_data(x)))
{
}
template <class U, class V, class..., class...,
class = enable_if<(N > V::Size && N <= 2 * V::Size)>>
Vc_INTRINSIC SimdArray(const SimdArray<U, N, V> &x)
: data(simd_cast<vector_type>(internal_data(internal_data0(x)),
internal_data(internal_data1(x))))
{
}
template <class U, class V, class..., class..., class...,
class = enable_if<(N > 2 * V::Size && N <= 4 * V::Size)>>
Vc_INTRINSIC SimdArray(const SimdArray<U, N, V> &x)
: data(simd_cast<vector_type>(internal_data(internal_data0(internal_data0(x))),
internal_data(internal_data1(internal_data0(x))),
internal_data(internal_data0(internal_data1(x))),
internal_data(internal_data1(internal_data1(x)))))
{
}
template <typename V, std::size_t Pieces, std::size_t Index>
Vc_INTRINSIC SimdArray(Common::Segment<V, Pieces, Index> &&x)
: data(simd_cast<vector_type, Index>(x.data))
{
}
Vc_INTRINSIC SimdArray(const std::initializer_list<value_type> &init)
: data(init.begin(), Vc::Unaligned)
{
#if defined Vc_CXX14 && 0
static_assert(init.size() == size(), "The initializer_list argument to "
"SimdArray<T, N> must contain exactly N "
"values.");
#else
Vc_ASSERT(init.size() == size());
#endif
}
template <
typename V,
typename = enable_if<Traits::is_simd_vector<V>::value && !Traits::isSimdArray<V>::value>>
Vc_INTRINSIC SimdArray(const V &x)
: data(simd_cast<vector_type>(x))
{
}
template <typename U, typename A,
typename =
enable_if<std::is_convertible<T, U>::value && Vector<U, A>::Size == N &&
!std::is_same<A, simd_abi::fixed_size<N>>::value>>
Vc_INTRINSIC operator Vector<U, A>() const
{
return simd_cast<Vector<U, A>>(data);
}
operator fixed_size_simd<T, N>() const
{
return static_cast<fixed_size_simd<T, N>>(data);
}
#ifndef Vc_CURRENT_CLASS_NAME
#error "incorrect use of common/gatherinterface.h: Vc_CURRENT_CLASS_NAME must be defined to the current class name for declaring constructors."
#endif
private:
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes);
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes, MaskArgument mask);
template <typename IT, typename = enable_if<std::is_pointer<IT>::value ||
Traits::is_simd_vector<IT>::value>>
static Vc_INTRINSIC const IT &adjustIndexParameter(const IT &indexes)
{
return indexes;
}
template <
typename IT,
typename = enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value>>
static Vc_INTRINSIC decltype(std::addressof(std::declval<const IT &>()[0]))
adjustIndexParameter(const IT &i)
{
return std::addressof(i[0]);
}
template <typename IT>
static Vc_INTRINSIC enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
!std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value,
IT>
adjustIndexParameter(const IT &i)
{
return i;
}
public:
#define Vc_ASSERT_GATHER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<MT, EntryType>::value, \
"The memory pointer needs to point to a type that can be converted to the " \
"EntryType of this SIMD vector type."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT, typename IT,
typename = enable_if<Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes,
MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes, MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args)
{
gather(args.address, adjustIndexParameter(args.indexes));
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args, MaskArgument mask)
{
gather(args.address, adjustIndexParameter(args.indexes), mask);
}
#undef Vc_ASSERT_GATHER_PARAMETER_TYPES_
private:
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes) const;
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes, MaskArgument mask) const;
public:
#define Vc_ASSERT_SCATTER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<EntryType, MT>::value, \
"The memory pointer needs to point to a type that the EntryType of this " \
"SIMD vector type can be converted to."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes));
}
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes, MaskArgument mask) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args) const
{
scatter(args.address, args.indexes);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args, MaskArgument mask) const
{
scatter(args.address, args.indexes, mask);
}
#undef Vc_ASSERT_SCATTER_PARAMETER_TYPES_
template <typename... Args,
typename = enable_if<!Traits::is_cast_arguments<Args...>::value &&
!Traits::is_gather_signature<Args...>::value &&
!Traits::is_initializer_list<Args...>::value>>
explicit Vc_INTRINSIC SimdArray(Args &&... args)
: data(std::forward<Args>(args)...)
{
}
template <std::size_t Offset>
explicit Vc_INTRINSIC SimdArray(
Common::AddOffset<VectorSpecialInitializerIndexesFromZero, Offset>)
: data(Vc::IndexesFromZero)
{
data += value_type(Offset);
}
Vc_INTRINSIC void setZero() { data.setZero(); }
Vc_INTRINSIC void setZero(mask_type k) { data.setZero(internal_data(k)); }
Vc_INTRINSIC void setZeroInverted() { data.setZeroInverted(); }
Vc_INTRINSIC void setZeroInverted(mask_type k) { data.setZeroInverted(internal_data(k)); }
Vc_INTRINSIC void setQnan() { data.setQnan(); }
Vc_INTRINSIC void setQnan(mask_type m) { data.setQnan(internal_data(m)); }
template <typename Op, typename... Args>
static Vc_INTRINSIC SimdArray fromOperation(Op op, Args &&... args)
{
SimdArray r;
Common::unpackArgumentsAuto(op, r.data, std::forward<Args>(args)...);
return r;
}
template <typename Op, typename... Args>
static Vc_INTRINSIC void callOperation(Op op, Args &&... args)
{
Common::unpackArgumentsAuto(op, nullptr, std::forward<Args>(args)...);
}
static Vc_INTRINSIC SimdArray Zero()
{
return SimdArray(Vc::Zero);
}
static Vc_INTRINSIC SimdArray One()
{
return SimdArray(Vc::One);
}
static Vc_INTRINSIC SimdArray IndexesFromZero()
{
return SimdArray(Vc::IndexesFromZero);
}
static Vc_INTRINSIC SimdArray Random()
{
return fromOperation(Common::Operations::random());
}
template <typename... Args> Vc_INTRINSIC void load(Args &&... args)
{
data.load(std::forward<Args>(args)...);
}
template <typename... Args> Vc_INTRINSIC void store(Args &&... args) const
{
data.store(std::forward<Args>(args)...);
}
Vc_INTRINSIC mask_type operator!() const
{
return {private_init, !data};
}
Vc_INTRINSIC SimdArray operator-() const
{
return {private_init, -data};
}
Vc_INTRINSIC SimdArray operator+() const { return *this; }
Vc_INTRINSIC SimdArray operator~() const
{
return {private_init, ~data};
}
template <typename U,
typename = enable_if<std::is_integral<T>::value && std::is_integral<U>::value>>
Vc_INTRINSIC Vc_CONST SimdArray operator<<(U x) const
{
return {private_init, data << x};
}
template <typename U,
typename = enable_if<std::is_integral<T>::value && std::is_integral<U>::value>>
Vc_INTRINSIC SimdArray &operator<<=(U x)
{
data <<= x;
return *this;
}
template <typename U,
typename = enable_if<std::is_integral<T>::value && std::is_integral<U>::value>>
Vc_INTRINSIC Vc_CONST SimdArray operator>>(U x) const
{
return {private_init, data >> x};
}
template <typename U,
typename = enable_if<std::is_integral<T>::value && std::is_integral<U>::value>>
Vc_INTRINSIC SimdArray &operator>>=(U x)
{
data >>= x;
return *this;
}
#define Vc_BINARY_OPERATOR_(op) \
Vc_INTRINSIC Vc_CONST SimdArray operator op(const SimdArray &rhs) const \
{ \
return {private_init, data op rhs.data}; \
} \
Vc_INTRINSIC SimdArray &operator op##=(const SimdArray &rhs) \
{ \
data op## = rhs.data; \
return *this; \
}
Vc_ALL_ARITHMETICS(Vc_BINARY_OPERATOR_);
Vc_ALL_BINARY(Vc_BINARY_OPERATOR_);
Vc_ALL_SHIFTS(Vc_BINARY_OPERATOR_);
#undef Vc_BINARY_OPERATOR_
#define Vc_COMPARES(op) \
Vc_INTRINSIC mask_type operator op(const SimdArray &rhs) const \
{ \
return {private_init, data op rhs.data}; \
}
Vc_ALL_COMPARES(Vc_COMPARES);
#undef Vc_COMPARES
Vc_DEPRECATED("use isnegative(x) instead") Vc_INTRINSIC MaskType isNegative() const
{
return {private_init, isnegative(data)};
}
private:
friend reference;
Vc_INTRINSIC static value_type get(const SimdArray &o, int i) noexcept
{
return o.data[i];
}
template <typename U>
Vc_INTRINSIC static void set(SimdArray &o, int i, U &&v) noexcept(
noexcept(std::declval<value_type &>() = v))
{
o.data[i] = v;
}
public:
Vc_INTRINSIC reference operator[](size_t i) noexcept
{
static_assert(noexcept(reference{std::declval<SimdArray &>(), int()}), "");
return {*this, int(i)};
}
Vc_INTRINSIC value_type operator[](size_t i) const noexcept
{
return get(*this, int(i));
}
Vc_INTRINSIC Common::WriteMaskedVector<SimdArray, mask_type> operator()(const mask_type &k)
{
return {*this, k};
}
Vc_INTRINSIC void assign(const SimdArray &v, const mask_type &k)
{
data.assign(v.data, internal_data(k));
}
#define Vc_REDUCTION_FUNCTION_(name_) \
Vc_INTRINSIC Vc_PURE value_type name_() const { return data.name_(); } \
Vc_INTRINSIC Vc_PURE value_type name_(mask_type mask) const \
{ \
return data.name_(internal_data(mask)); \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_REDUCTION_FUNCTION_(min);
Vc_REDUCTION_FUNCTION_(max);
Vc_REDUCTION_FUNCTION_(product);
Vc_REDUCTION_FUNCTION_(sum);
#undef Vc_REDUCTION_FUNCTION_
Vc_INTRINSIC Vc_PURE SimdArray partialSum() const
{
return {private_init, data.partialSum()};
}
template <typename F> Vc_INTRINSIC SimdArray apply(F &&f) const
{
return {private_init, data.apply(std::forward<F>(f))};
}
template <typename F> Vc_INTRINSIC SimdArray apply(F &&f, const mask_type &k) const
{
return {private_init, data.apply(std::forward<F>(f), k)};
}
Vc_INTRINSIC SimdArray shifted(int amount) const
{
return {private_init, data.shifted(amount)};
}
template <std::size_t NN>
Vc_INTRINSIC SimdArray shifted(int amount, const SimdArray<value_type, NN> &shiftIn)
const
{
return {private_init, data.shifted(amount, simd_cast<VectorType>(shiftIn))};
}
Vc_INTRINSIC SimdArray rotated(int amount) const
{
return {private_init, data.rotated(amount)};
}
Vc_DEPRECATED("use exponent(x) instead") Vc_INTRINSIC SimdArray exponent() const
{
return {private_init, exponent(data)};
}
Vc_INTRINSIC SimdArray interleaveLow(SimdArray x) const
{
return {private_init, data.interleaveLow(x.data)};
}
Vc_INTRINSIC SimdArray interleaveHigh(SimdArray x) const
{
return {private_init, data.interleaveHigh(x.data)};
}
Vc_INTRINSIC SimdArray reversed() const
{
return {private_init, data.reversed()};
}
Vc_INTRINSIC SimdArray sorted() const
{
return {private_init, data.sorted()};
}
template <typename G> static Vc_INTRINSIC SimdArray generate(const G &gen)
{
return {private_init, VectorType::generate(gen)};
}
Vc_DEPRECATED("use copysign(x, y) instead") Vc_INTRINSIC SimdArray
copySign(const SimdArray &x) const
{
return {private_init, Vc::copysign(data, x.data)};
}
friend VectorType &internal_data<>(SimdArray &x);
friend const VectorType &internal_data<>(const SimdArray &x);
Vc_INTRINSIC SimdArray(private_init_t, VectorType &&x) : data(std::move(x)) {}
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(storage_type));
private:
alignas(static_cast<std::size_t>(
Common::BoundedAlignment<Common::NextPowerOfTwo<N>::value * sizeof(VectorType_) /
VectorType_::size()>::value)) storage_type data;
};
template <typename T, std::size_t N, typename VectorType> constexpr std::size_t SimdArray<T, N, VectorType, N>::Size;
template <typename T, std::size_t N, typename VectorType>
constexpr std::size_t SimdArray<T, N, VectorType, N>::MemoryAlignment;
template <typename T, std::size_t N, typename VectorType>
#ifndef Vc_MSVC
Vc_INTRINSIC
#endif
VectorType &internal_data(SimdArray<T, N, VectorType, N> &x)
{
return x.data;
}
template <typename T, std::size_t N, typename VectorType>
#ifndef Vc_MSVC
Vc_INTRINSIC
#endif
const VectorType &internal_data(const SimdArray<T, N, VectorType, N> &x)
{
return x.data;
}
template <typename T> T unpackIfSegment(T &&x) { return std::forward<T>(x); }
template <typename T, size_t Pieces, size_t Index>
auto unpackIfSegment(Common::Segment<T, Pieces, Index> &&x) -> decltype(x.asSimdArray())
{
return x.asSimdArray();
}
template <typename T, std::size_t N, typename VectorType>
template <typename MT, typename IT>
inline void SimdArray<T, N, VectorType, N>::gatherImplementation(const MT *mem,
const IT &indexes)
{
data.gather(mem, unpackIfSegment(indexes));
}
template <typename T, std::size_t N, typename VectorType>
template <typename MT, typename IT>
inline void SimdArray<T, N, VectorType, N>::gatherImplementation(const MT *mem,
const IT &indexes,
MaskArgument mask)
{
data.gather(mem, unpackIfSegment(indexes), mask);
}
template <typename T, std::size_t N, typename VectorType>
template <typename MT, typename IT>
inline void SimdArray<T, N, VectorType, N>::scatterImplementation(MT *mem,
IT &&indexes) const
{
data.scatter(mem, unpackIfSegment(std::forward<IT>(indexes)));
}
template <typename T, std::size_t N, typename VectorType>
template <typename MT, typename IT>
inline void SimdArray<T, N, VectorType, N>::scatterImplementation(MT *mem,
IT &&indexes,
MaskArgument mask) const
{
data.scatter(mem, unpackIfSegment(std::forward<IT>(indexes)), mask);
}
template <typename T, size_t N, typename V, size_t Wt> class SimdArray
{
static_assert(std::is_same<T, double>::value ||
std::is_same<T, float>::value ||
std::is_same<T, int32_t>::value ||
std::is_same<T, uint32_t>::value ||
std::is_same<T, int16_t>::value ||
std::is_same<T, uint16_t>::value, "SimdArray<T, N> may only be used with T = { double, float, int32_t, uint32_t, int16_t, uint16_t }");
static_assert(
std::is_same<typename V::EntryType, typename V::VectorEntryType>::value ||
(N % V::size() == 0),
"SimdArray<(un)signed short, N> on MIC only works correctly for N = k * "
"MIC::(u)short_v::size(), i.e. k * 16.");
using my_traits = SimdArrayTraits<T, N>;
static constexpr std::size_t N0 = my_traits::N0;
static constexpr std::size_t N1 = my_traits::N1;
using Split = Common::Split<N0>;
template <typename U, std::size_t K> using CArray = U[K];
public:
using storage_type0 = typename my_traits::storage_type0;
using storage_type1 = typename my_traits::storage_type1;
static_assert(storage_type0::size() == N0, "");
using vector_type = V;
using vectorentry_type = typename storage_type0::vectorentry_type;
typedef vectorentry_type alias_type Vc_MAY_ALIAS;
using value_type = T;
using mask_type = SimdMaskArray<T, N, vector_type>;
using index_type = SimdArray<int, N>;
static constexpr std::size_t size() { return N; }
using Mask = mask_type;
using MaskType = Mask;
using MaskArgument = const MaskType &;
using VectorEntryType = vectorentry_type;
using EntryType = value_type;
using IndexType = index_type;
using AsArg = const SimdArray &;
using reference = Detail::ElementReference<SimdArray>;
static constexpr std::size_t MemoryAlignment =
storage_type0::MemoryAlignment > storage_type1::MemoryAlignment
? storage_type0::MemoryAlignment
: storage_type1::MemoryAlignment;
static Vc_INTRINSIC SimdArray Zero()
{
return SimdArray(Vc::Zero);
}
static Vc_INTRINSIC SimdArray One()
{
return SimdArray(Vc::One);
}
static Vc_INTRINSIC SimdArray IndexesFromZero()
{
return SimdArray(Vc::IndexesFromZero);
}
static Vc_INTRINSIC SimdArray Random()
{
return fromOperation(Common::Operations::random());
}
template <typename G> static Vc_INTRINSIC SimdArray generate(const G &gen)
{
auto tmp = storage_type0::generate(gen);
return {std::move(tmp),
storage_type1::generate([&](std::size_t i) { return gen(i + N0); })};
}
#ifndef Vc_MSVC
SimdArray() = default;
#endif
Vc_INTRINSIC SimdArray(value_type a) : data0(a), data1(a) {}
template <
typename U,
typename = enable_if<std::is_same<U, int>::value && !std::is_same<int, value_type>::value>>
SimdArray(U a)
: SimdArray(static_cast<value_type>(a))
{
}
SimdArray(const SimdArray &) = default;
SimdArray(SimdArray &&) = default;
SimdArray &operator=(const SimdArray &) = default;
template <typename U, typename Flags = DefaultLoadTag,
typename = enable_if<std::is_arithmetic<U>::value &&
Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC SimdArray(const U *mem, Flags f = Flags())
: data0(mem, f), data1(mem + storage_type0::size(), f)
{
}
#ifndef Vc_MSVC
template <typename U, std::size_t Extent, typename Flags = DefaultLoadTag,
typename = enable_if<std::is_arithmetic<U>::value &&
Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC SimdArray(CArray<U, Extent> &mem, Flags f = Flags())
: data0(&mem[0], f), data1(&mem[storage_type0::size()], f)
{
}
template <typename U, std::size_t Extent, typename Flags = DefaultLoadTag,
typename = enable_if<std::is_arithmetic<U>::value &&
Traits::is_load_store_flag<Flags>::value>>
explicit Vc_INTRINSIC SimdArray(const CArray<U, Extent> &mem, Flags f = Flags())
: data0(&mem[0], f), data1(&mem[storage_type0::size()], f)
{
}
#endif
Vc_INTRINSIC SimdArray(const std::initializer_list<value_type> &init)
: data0(init.begin(), Vc::Unaligned)
, data1(init.begin() + storage_type0::size(), Vc::Unaligned)
{
#if defined Vc_CXX14 && 0
static_assert(init.size() == size(), "The initializer_list argument to "
"SimdArray<T, N> must contain exactly N "
"values.");
#else
Vc_ASSERT(init.size() == size());
#endif
}
#ifndef Vc_CURRENT_CLASS_NAME
#error "incorrect use of common/gatherinterface.h: Vc_CURRENT_CLASS_NAME must be defined to the current class name for declaring constructors."
#endif
private:
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes);
template <typename MT, typename IT>
inline void gatherImplementation(const MT *mem, const IT &indexes, MaskArgument mask);
template <typename IT, typename = enable_if<std::is_pointer<IT>::value ||
Traits::is_simd_vector<IT>::value>>
static Vc_INTRINSIC const IT &adjustIndexParameter(const IT &indexes)
{
return indexes;
}
template <
typename IT,
typename = enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value>>
static Vc_INTRINSIC decltype(std::addressof(std::declval<const IT &>()[0]))
adjustIndexParameter(const IT &i)
{
return std::addressof(i[0]);
}
template <typename IT>
static Vc_INTRINSIC enable_if<
!std::is_pointer<IT>::value && !Traits::is_simd_vector<IT>::value &&
!std::is_lvalue_reference<decltype(std::declval<const IT &>()[0])>::value,
IT>
adjustIndexParameter(const IT &i)
{
return i;
}
public:
#define Vc_ASSERT_GATHER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<MT, EntryType>::value, \
"The memory pointer needs to point to a type that can be converted to the " \
"EntryType of this SIMD vector type."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT, typename IT,
typename = enable_if<Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC Vc_CURRENT_CLASS_NAME(const MT *mem, const IT &indexes,
MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes));
}
template <typename MT, typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void gather(const MT *mem, const IT &indexes, MaskArgument mask)
{
Vc_ASSERT_GATHER_PARAMETER_TYPES_;
gatherImplementation(mem, adjustIndexParameter(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args)
{
gather(args.address, adjustIndexParameter(args.indexes));
}
template <typename MT, typename IT>
Vc_INTRINSIC void gather(const Common::GatherArguments<MT, IT> &args, MaskArgument mask)
{
gather(args.address, adjustIndexParameter(args.indexes), mask);
}
#undef Vc_ASSERT_GATHER_PARAMETER_TYPES_
private:
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes) const;
template <typename MT, typename IT>
inline void scatterImplementation(MT *mem, IT &&indexes, MaskArgument mask) const;
public:
#define Vc_ASSERT_SCATTER_PARAMETER_TYPES_ \
static_assert( \
std::is_convertible<EntryType, MT>::value, \
"The memory pointer needs to point to a type that the EntryType of this " \
"SIMD vector type can be converted to."); \
static_assert( \
Vc::Traits::has_subscript_operator<IT>::value, \
"The indexes argument must be a type that implements the subscript operator."); \
static_assert( \
!Traits::is_simd_vector<IT>::value || \
Traits::simd_vector_size<IT>::value >= Size, \
"If you use a SIMD vector for the indexes parameter, the index vector must " \
"have at least as many entries as this SIMD vector."); \
static_assert( \
!std::is_array<T>::value || \
(std::rank<T>::value == 1 && \
(std::extent<T>::value == 0 || std::extent<T>::value >= Size)), \
"If you use a simple array for the indexes parameter, the array must have " \
"at least as many entries as this SIMD vector.")
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes));
}
template <typename MT,
typename IT,
typename = enable_if<Vc::Traits::has_subscript_operator<IT>::value>>
Vc_INTRINSIC void scatter(MT *mem, IT &&indexes, MaskArgument mask) const
{
Vc_ASSERT_SCATTER_PARAMETER_TYPES_;
scatterImplementation(mem, std::forward<IT>(indexes), mask);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args) const
{
scatter(args.address, args.indexes);
}
template <typename MT, typename IT>
Vc_INTRINSIC void scatter(const Common::ScatterArguments<MT, IT> &args, MaskArgument mask) const
{
scatter(args.address, args.indexes, mask);
}
#undef Vc_ASSERT_SCATTER_PARAMETER_TYPES_
template <typename... Args,
typename = enable_if<!Traits::is_cast_arguments<Args...>::value &&
!Traits::is_initializer_list<Args...>::value &&
!Traits::is_gather_signature<Args...>::value &&
!Traits::is_load_arguments<Args...>::value>>
explicit Vc_INTRINSIC SimdArray(Args &&... args)
: data0(Split::lo(args)...)
, data1(Split::hi(std::forward<Args>(args))...)
{
}
template <
class W, class...,
class = enable_if<(Traits::is_simd_vector<W>::value &&
Traits::simd_vector_size<W>::value == N &&
!(std::is_convertible<Traits::entry_type_of<W>, T>::value &&
Traits::isSimdArray<W>::value))>>
Vc_INTRINSIC explicit SimdArray(W &&x) : data0(Split::lo(x)), data1(Split::hi(x))
{
}
template <
class W, class..., class...,
class = enable_if<(Traits::isSimdArray<W>::value &&
Traits::simd_vector_size<W>::value == N &&
std::is_convertible<Traits::entry_type_of<W>, T>::value)>>
Vc_INTRINSIC SimdArray(W &&x) : data0(Split::lo(x)), data1(Split::hi(x))
{
}
template <typename U, typename A,
typename =
enable_if<std::is_convertible<T, U>::value && Vector<U, A>::Size == N &&
!std::is_same<A, simd_abi::fixed_size<N>>::value>>
operator Vector<U, A>() const
{
auto r = simd_cast<Vector<U, A>>(data0, data1);
return r;
}
Vc_INTRINSIC operator const fixed_size_simd<T, N> &() const
{
return static_cast<const fixed_size_simd<T, N> &>(*this);
}
Vc_INTRINSIC void setZero()
{
data0.setZero();
data1.setZero();
}
Vc_INTRINSIC void setZero(const mask_type &k)
{
data0.setZero(Split::lo(k));
data1.setZero(Split::hi(k));
}
Vc_INTRINSIC void setZeroInverted()
{
data0.setZeroInverted();
data1.setZeroInverted();
}
Vc_INTRINSIC void setZeroInverted(const mask_type &k)
{
data0.setZeroInverted(Split::lo(k));
data1.setZeroInverted(Split::hi(k));
}
Vc_INTRINSIC void setQnan() {
data0.setQnan();
data1.setQnan();
}
Vc_INTRINSIC void setQnan(const mask_type &m) {
data0.setQnan(Split::lo(m));
data1.setQnan(Split::hi(m));
}
template <typename Op, typename... Args>
static Vc_INTRINSIC SimdArray fromOperation(Op op, Args &&... args)
{
SimdArray r = {
storage_type0::fromOperation(op, Split::lo(args)...),
storage_type1::fromOperation(op, Split::hi(std::forward<Args>(args))...)};
return r;
}
template <typename Op, typename... Args>
static Vc_INTRINSIC void callOperation(Op op, Args &&... args)
{
storage_type0::callOperation(op, Split::lo(args)...);
storage_type1::callOperation(op, Split::hi(std::forward<Args>(args))...);
}
template <typename U, typename... Args> Vc_INTRINSIC void load(const U *mem, Args &&... args)
{
data0.load(mem, Split::lo(args)...);
data1.load(mem + storage_type0::size(), Split::hi(std::forward<Args>(args))...);
}
template <typename U, typename... Args> Vc_INTRINSIC void store(U *mem, Args &&... args) const
{
data0.store(mem, Split::lo(args)...);
data1.store(mem + storage_type0::size(), Split::hi(std::forward<Args>(args))...);
}
Vc_INTRINSIC mask_type operator!() const
{
return {!data0, !data1};
}
Vc_INTRINSIC SimdArray operator-() const
{
return {-data0, -data1};
}
Vc_INTRINSIC SimdArray operator+() const { return *this; }
Vc_INTRINSIC SimdArray operator~() const
{
return {~data0, ~data1};
}
template <typename U,
typename = enable_if<std::is_integral<T>::value && std::is_integral<U>::value>>
Vc_INTRINSIC Vc_CONST SimdArray operator<<(U x) const
{
return {data0 << x, data1 << x};
}
template <typename U,
typename = enable_if<std::is_integral<T>::value && std::is_integral<U>::value>>
Vc_INTRINSIC SimdArray &operator<<=(U x)
{
data0 <<= x;
data1 <<= x;
return *this;
}
template <typename U,
typename = enable_if<std::is_integral<T>::value && std::is_integral<U>::value>>
Vc_INTRINSIC Vc_CONST SimdArray operator>>(U x) const
{
return {data0 >> x, data1 >> x};
}
template <typename U,
typename = enable_if<std::is_integral<T>::value && std::is_integral<U>::value>>
Vc_INTRINSIC SimdArray &operator>>=(U x)
{
data0 >>= x;
data1 >>= x;
return *this;
}
#define Vc_BINARY_OPERATOR_(op) \
Vc_INTRINSIC Vc_CONST SimdArray operator op(const SimdArray &rhs) const \
{ \
return {data0 op rhs.data0, data1 op rhs.data1}; \
} \
Vc_INTRINSIC SimdArray &operator op##=(const SimdArray &rhs) \
{ \
data0 op## = rhs.data0; \
data1 op## = rhs.data1; \
return *this; \
}
Vc_ALL_ARITHMETICS(Vc_BINARY_OPERATOR_);
Vc_ALL_BINARY(Vc_BINARY_OPERATOR_);
Vc_ALL_SHIFTS(Vc_BINARY_OPERATOR_);
#undef Vc_BINARY_OPERATOR_
#define Vc_COMPARES(op) \
Vc_INTRINSIC mask_type operator op(const SimdArray &rhs) const \
{ \
return {data0 op rhs.data0, data1 op rhs.data1}; \
}
Vc_ALL_COMPARES(Vc_COMPARES);
#undef Vc_COMPARES
private:
friend reference;
Vc_INTRINSIC static value_type get(const SimdArray &o, int i) noexcept
{
return reinterpret_cast<const alias_type *>(&o)[i];
}
template <typename U>
Vc_INTRINSIC static void set(SimdArray &o, int i, U &&v) noexcept(
noexcept(std::declval<value_type &>() = v))
{
reinterpret_cast<alias_type *>(&o)[i] = v;
}
public:
Vc_INTRINSIC reference operator[](size_t i) noexcept
{
static_assert(noexcept(reference{std::declval<SimdArray &>(), int()}), "");
return {*this, int(i)};
}
Vc_INTRINSIC value_type operator[](size_t index) const noexcept
{
return get(*this, int(index));
}
Vc_INTRINSIC Common::WriteMaskedVector<SimdArray, mask_type> operator()(
const mask_type &mask)
{
return {*this, mask};
}
Vc_INTRINSIC void assign(const SimdArray &v, const mask_type &k)
{
data0.assign(v.data0, internal_data0(k));
data1.assign(v.data1, internal_data1(k));
}
#define Vc_REDUCTION_FUNCTION_(name_,binary_fun_,scalar_fun_) \
private: \
template <typename ForSfinae = void> \
Vc_INTRINSIC enable_if<std::is_same<ForSfinae, void>::value && \
storage_type0::Size == storage_type1::Size, \
value_type> name_##_impl() const \
{ \
return binary_fun_(data0, data1).name_(); \
} \
\
template <typename ForSfinae = void> \
Vc_INTRINSIC enable_if<std::is_same<ForSfinae, void>::value && \
storage_type0::Size != storage_type1::Size, \
value_type> name_##_impl() const \
{ \
return scalar_fun_(data0.name_(), data1.name_()); \
} \
\
public: \
\
Vc_INTRINSIC value_type name_() const { return name_##_impl(); } \
\
Vc_INTRINSIC value_type name_(const mask_type &mask) const \
{ \
if (Vc_IS_UNLIKELY(Split::lo(mask).isEmpty())) { \
return data1.name_(Split::hi(mask)); \
} else if (Vc_IS_UNLIKELY(Split::hi(mask).isEmpty())) { \
return data0.name_(Split::lo(mask)); \
} else { \
return scalar_fun_(data0.name_(Split::lo(mask)), \
data1.name_(Split::hi(mask))); \
} \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_REDUCTION_FUNCTION_(min, Vc::min, std::min);
Vc_REDUCTION_FUNCTION_(max, Vc::max, std::max);
Vc_REDUCTION_FUNCTION_(product, internal::product_helper_, internal::product_helper_);
Vc_REDUCTION_FUNCTION_(sum, internal::sum_helper_, internal::sum_helper_);
#undef Vc_REDUCTION_FUNCTION_
Vc_INTRINSIC Vc_PURE SimdArray partialSum() const
{
auto ps0 = data0.partialSum();
auto tmp = data1;
tmp[0] += ps0[data0.size() - 1];
return {std::move(ps0), tmp.partialSum()};
}
template <typename F> inline SimdArray apply(F &&f) const
{
return {data0.apply(f), data1.apply(f)};
}
template <typename F> inline SimdArray apply(F &&f, const mask_type &k) const
{
return {data0.apply(f, Split::lo(k)), data1.apply(f, Split::hi(k))};
}
inline SimdArray shifted(int amount) const
{
constexpr int SSize = Size;
constexpr int SSize0 = storage_type0::Size;
constexpr int SSize1 = storage_type1::Size;
if (amount == 0) {
return *this;
}
if (amount < 0) {
if (amount > -SSize0) {
return {data0.shifted(amount), data1.shifted(amount, data0)};
}
if (amount == -SSize0) {
return {storage_type0::Zero(), simd_cast<storage_type1>(data0)};
}
if (amount < -SSize0) {
return {storage_type0::Zero(), simd_cast<storage_type1>(data0.shifted(
amount + SSize0))};
}
return Zero();
} else {
if (amount >= SSize) {
return Zero();
} else if (amount >= SSize0) {
return {
simd_cast<storage_type0>(data1).shifted(amount - SSize0),
storage_type1::Zero()};
} else if (amount >= SSize1) {
return {data0.shifted(amount, data1), storage_type1::Zero()};
} else {
return {data0.shifted(amount, data1), data1.shifted(amount)};
}
}
}
template <std::size_t NN>
inline enable_if<
!(std::is_same<storage_type0, storage_type1>::value &&
N == NN),
SimdArray>
shifted(int amount, const SimdArray<value_type, NN> &shiftIn) const
{
constexpr int SSize = Size;
if (amount < 0) {
return SimdArray::generate([&](int i) -> value_type {
i += amount;
if (i >= 0) {
return operator[](i);
} else if (i >= -SSize) {
return shiftIn[i + SSize];
}
return 0;
});
}
return SimdArray::generate([&](int i) -> value_type {
i += amount;
if (i < SSize) {
return operator[](i);
} else if (i < 2 * SSize) {
return shiftIn[i - SSize];
}
return 0;
});
}
private:
template <std::size_t NN> struct bisectable_shift
: public std::integral_constant<bool,
std::is_same<storage_type0, storage_type1>::value &&
N == NN>
{
};
public:
template <std::size_t NN>
inline SimdArray shifted(enable_if<bisectable_shift<NN>::value, int> amount,
const SimdArray<value_type, NN> &shiftIn) const
{
constexpr int SSize = Size;
if (amount < 0) {
if (amount > -static_cast<int>(storage_type0::Size)) {
return {data0.shifted(amount, internal_data1(shiftIn)),
data1.shifted(amount, data0)};
}
if (amount == -static_cast<int>(storage_type0::Size)) {
return {storage_type0(internal_data1(shiftIn)), storage_type1(data0)};
}
if (amount > -SSize) {
return {
internal_data1(shiftIn)
.shifted(amount + static_cast<int>(storage_type0::Size), internal_data0(shiftIn)),
data0.shifted(amount + static_cast<int>(storage_type0::Size), internal_data1(shiftIn))};
}
if (amount == -SSize) {
return shiftIn;
}
if (amount > -2 * SSize) {
return shiftIn.shifted(amount + SSize);
}
}
if (amount == 0) {
return *this;
}
if (amount < static_cast<int>(storage_type0::Size)) {
return {data0.shifted(amount, data1),
data1.shifted(amount, internal_data0(shiftIn))};
}
if (amount == static_cast<int>(storage_type0::Size)) {
return {storage_type0(data1), storage_type1(internal_data0(shiftIn))};
}
if (amount < SSize) {
return {data1.shifted(amount - static_cast<int>(storage_type0::Size), internal_data0(shiftIn)),
internal_data0(shiftIn)
.shifted(amount - static_cast<int>(storage_type0::Size), internal_data1(shiftIn))};
}
if (amount == SSize) {
return shiftIn;
}
if (amount < 2 * SSize) {
return shiftIn.shifted(amount - SSize);
}
return Zero();
}
Vc_INTRINSIC SimdArray rotated(int amount) const
{
amount %= int(size());
if (amount == 0) {
return *this;
} else if (amount < 0) {
amount += size();
}
#ifdef Vc_MSVC
alignas(MemoryAlignment) T tmp[N + data0.size()];
data0.store(&tmp[0], Vc::Aligned);
data1.store(&tmp[data0.size()], Vc::Aligned);
data0.store(&tmp[N], Vc::Unaligned);
SimdArray r;
r.data0.load(&tmp[amount], Vc::Unaligned);
r.data1.load(&tmp[(amount + data0.size()) % size()], Vc::Unaligned);
return r;
#else
auto &&d0cvtd = simd_cast<storage_type1>(data0);
auto &&d1cvtd = simd_cast<storage_type0>(data1);
constexpr int size0 = storage_type0::size();
constexpr int size1 = storage_type1::size();
if (amount == size0 && std::is_same<storage_type0, storage_type1>::value) {
return {std::move(d1cvtd), std::move(d0cvtd)};
} else if (amount < size1) {
return {data0.shifted(amount, d1cvtd), data1.shifted(amount, d0cvtd)};
} else if (amount == size1) {
return {data0.shifted(amount, d1cvtd), std::move(d0cvtd)};
} else if (int(size()) - amount < size1) {
return {data0.shifted(amount - int(size()), d1cvtd.shifted(size1 - size0)),
data1.shifted(amount - int(size()), data0.shifted(size0 - size1))};
} else if (int(size()) - amount == size1) {
return {data0.shifted(-size1, d1cvtd.shifted(size1 - size0)),
simd_cast<storage_type1>(data0.shifted(size0 - size1))};
} else if (amount <= size0) {
return {data0.shifted(size1, d1cvtd).shifted(amount - size1, data0),
simd_cast<storage_type1>(data0.shifted(amount - size1))};
} else {
return {data0.shifted(size1, d1cvtd).shifted(amount - size1, data0),
simd_cast<storage_type1>(data0.shifted(amount - size1, d1cvtd))};
}
return *this;
#endif
}
Vc_INTRINSIC SimdArray interleaveLow(const SimdArray &x) const
{
return {data0.interleaveLow(x.data0),
simd_cast<storage_type1>(data0.interleaveHigh(x.data0))};
}
Vc_INTRINSIC SimdArray interleaveHigh(const SimdArray &x) const
{
return interleaveHighImpl(
x,
std::integral_constant<bool, storage_type0::Size == storage_type1::Size>());
}
private:
Vc_INTRINSIC SimdArray interleaveHighImpl(const SimdArray &x, std::true_type) const
{
return {data1.interleaveLow(x.data1), data1.interleaveHigh(x.data1)};
}
inline SimdArray interleaveHighImpl(const SimdArray &x, std::false_type) const
{
return {data0.interleaveHigh(x.data0)
.shifted(storage_type1::Size,
simd_cast<storage_type0>(data1.interleaveLow(x.data1))),
data1.interleaveHigh(x.data1)};
}
public:
inline SimdArray reversed() const
{
if (std::is_same<storage_type0, storage_type1>::value) {
return {simd_cast<storage_type0>(data1).reversed(),
simd_cast<storage_type1>(data0).reversed()};
} else {
#ifdef Vc_MSVC
alignas(MemoryAlignment) T tmp[N];
data1.reversed().store(&tmp[0], Vc::Aligned);
data0.reversed().store(&tmp[data1.size()], Vc::Unaligned);
return SimdArray{&tmp[0], Vc::Aligned};
#else
return {data0.shifted(storage_type1::Size, data1).reversed(),
simd_cast<storage_type1>(data0.reversed().shifted(
storage_type0::Size - storage_type1::Size))};
#endif
}
}
inline SimdArray sorted() const
{
return sortedImpl(
std::integral_constant<bool, storage_type0::Size == storage_type1::Size>());
}
Vc_INTRINSIC SimdArray sortedImpl(std::true_type) const
{
#ifdef Vc_DEBUG_SORTED
std::cerr << "-- " << data0 << data1 << '\n';
#endif
const auto a = data0.sorted();
const auto b = data1.sorted().reversed();
const auto lo = Vc::min(a, b);
const auto hi = Vc::max(a, b);
return {lo.sorted(), hi.sorted()};
}
Vc_INTRINSIC SimdArray sortedImpl(std::false_type) const
{
using SortableArray =
SimdArray<value_type, Common::NextPowerOfTwo<size()>::value>;
auto sortable = simd_cast<SortableArray>(*this);
for (std::size_t i = Size; i < SortableArray::Size; ++i) {
using limits = std::numeric_limits<value_type>;
if (limits::has_infinity) {
sortable[i] = limits::infinity();
} else {
sortable[i] = std::numeric_limits<value_type>::max();
}
}
return simd_cast<SimdArray>(sortable.sorted());
}
static constexpr std::size_t Size = size();
Vc_DEPRECATED("use exponent(x) instead") Vc_INTRINSIC SimdArray exponent() const
{
return {exponent(data0), exponent(data1)};
}
Vc_DEPRECATED("use isnegative(x) instead") Vc_INTRINSIC MaskType isNegative() const
{
return {isnegative(data0), isnegative(data1)};
}
Vc_DEPRECATED("use copysign(x, y) instead") Vc_INTRINSIC SimdArray
copySign(const SimdArray &x) const
{
return {Vc::copysign(data0, x.data0),
Vc::copysign(data1, x.data1)};
}
friend storage_type0 &internal_data0<>(SimdArray &x);
friend storage_type1 &internal_data1<>(SimdArray &x);
friend const storage_type0 &internal_data0<>(const SimdArray &x);
friend const storage_type1 &internal_data1<>(const SimdArray &x);
Vc_INTRINSIC SimdArray(storage_type0 &&x, storage_type1 &&y)
: data0(std::move(x)), data1(std::move(y))
{
}
Vc_FREE_STORE_OPERATORS_ALIGNED(alignof(storage_type0));
private:
alignas(static_cast<std::size_t>(
Common::BoundedAlignment<Common::NextPowerOfTwo<N>::value * sizeof(V) /
V::size()>::value)) storage_type0 data0;
storage_type1 data1;
};
#undef Vc_CURRENT_CLASS_NAME
template <typename T, std::size_t N, typename V, std::size_t M>
constexpr std::size_t SimdArray<T, N, V, M>::Size;
template <typename T, std::size_t N, typename V, std::size_t M>
constexpr std::size_t SimdArray<T, N, V, M>::MemoryAlignment;
template <typename T, std::size_t N, typename VectorType, std::size_t M>
template <typename MT, typename IT>
inline void SimdArray<T, N, VectorType, M>::gatherImplementation(const MT *mem,
const IT &indexes)
{
data0.gather(mem, Split::lo(Common::Operations::gather(), indexes));
data1.gather(mem, Split::hi(Common::Operations::gather(), indexes));
}
template <typename T, std::size_t N, typename VectorType, std::size_t M>
template <typename MT, typename IT>
inline void SimdArray<T, N, VectorType, M>::gatherImplementation(const MT *mem,
const IT &indexes,
MaskArgument mask)
{
data0.gather(mem, Split::lo(Common::Operations::gather(), indexes), Split::lo(mask));
data1.gather(mem, Split::hi(Common::Operations::gather(), indexes), Split::hi(mask));
}
template <typename T, std::size_t N, typename VectorType, std::size_t M>
template <typename MT, typename IT>
inline void SimdArray<T, N, VectorType, M>::scatterImplementation(MT *mem,
IT &&indexes) const
{
data0.scatter(mem, Split::lo(Common::Operations::gather(),
indexes));
data1.scatter(mem, Split::hi(Common::Operations::gather(), std::forward<IT>(indexes)));
}
template <typename T, std::size_t N, typename VectorType, std::size_t M>
template <typename MT, typename IT>
inline void SimdArray<T, N, VectorType, M>::scatterImplementation(MT *mem,
IT &&indexes, MaskArgument mask) const
{
data0.scatter(mem, Split::lo(Common::Operations::gather(), indexes),
Split::lo(mask));
data1.scatter(mem, Split::hi(Common::Operations::gather(), std::forward<IT>(indexes)),
Split::hi(mask));
}
template <typename T, std::size_t N, typename V, std::size_t M>
#ifndef Vc_MSVC
Vc_INTRINSIC
#endif
typename SimdArrayTraits<T, N>::storage_type0 &internal_data0(
SimdArray<T, N, V, M> &x)
{
return x.data0;
}
template <typename T, std::size_t N, typename V, std::size_t M>
#ifndef Vc_MSVC
Vc_INTRINSIC
#endif
typename SimdArrayTraits<T, N>::storage_type1 &internal_data1(
SimdArray<T, N, V, M> &x)
{
return x.data1;
}
template <typename T, std::size_t N, typename V, std::size_t M>
#ifndef Vc_MSVC
Vc_INTRINSIC
#endif
const typename SimdArrayTraits<T, N>::storage_type0 &internal_data0(
const SimdArray<T, N, V, M> &x)
{
return x.data0;
}
template <typename T, std::size_t N, typename V, std::size_t M>
#ifndef Vc_MSVC
Vc_INTRINSIC
#endif
const typename SimdArrayTraits<T, N>::storage_type1 &internal_data1(
const SimdArray<T, N, V, M> &x)
{
return x.data1;
}
#if defined Vc_MSVC && defined Vc_IMPL_SSE
template <>
Vc_INTRINSIC SimdArray<double, 8, SSE::Vector<double>, 2>::SimdArray(
SimdArray<double, 4> &&x, SimdArray<double, 4> &&y)
: data0(x), data1(0)
{
data1 = y;
}
#endif
namespace result_vector_type_internal
{
template <typename T>
using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
template <typename T>
using is_integer_larger_than_int = std::integral_constant<
bool, std::is_integral<T>::value &&(sizeof(T) > sizeof(int) ||
std::is_same<T, long>::value ||
std::is_same<T, unsigned long>::value)>;
template <
typename L, typename R,
std::size_t N = Traits::isSimdArray<L>::value ? Traits::simd_vector_size<L>::value
: Traits::simd_vector_size<R>::value,
bool =
(Traits::isSimdArray<L>::value ||
Traits::isSimdArray<R>::value)
&& !std::is_same<type<L>, type<R>>::value
&&
((std::is_arithmetic<type<L>>::value &&
!is_integer_larger_than_int<type<L>>::value) ||
(std::is_arithmetic<type<R>>::value &&
!is_integer_larger_than_int<type<R>>::value)
||
(
Traits::simd_vector_size<L>::value == Traits::simd_vector_size<R>::value &&
((Traits::is_simd_vector<L>::value && !Traits::isSimdArray<L>::value) ||
(Traits::is_simd_vector<R>::value && !Traits::isSimdArray<R>::value))))>
struct evaluate;
template <typename L, typename R, std::size_t N> struct evaluate<L, R, N, true>
{
private:
using LScalar = Traits::entry_type_of<L>;
using RScalar = Traits::entry_type_of<R>;
template <bool B, typename T, typename F>
using conditional = typename std::conditional<B, T, F>::type;
public:
using type = SimdArray<
conditional<(std::is_integral<LScalar>::value &&std::is_integral<RScalar>::value &&
sizeof(LScalar) < sizeof(int) &&
sizeof(RScalar) < sizeof(int)),
conditional<(sizeof(LScalar) == sizeof(RScalar)),
conditional<std::is_unsigned<LScalar>::value, LScalar, RScalar>,
conditional<(sizeof(LScalar) > sizeof(RScalar)), LScalar, RScalar>>,
decltype(std::declval<LScalar>() + std::declval<RScalar>())>,
N>;
};
}
template <typename L, typename R>
using result_vector_type = typename result_vector_type_internal::evaluate<L, R>::type;
static_assert(
std::is_same<result_vector_type<short int, Vc::SimdArray<short unsigned int, 32ul>>,
Vc::SimdArray<short unsigned int, 32ul>>::value,
"result_vector_type does not work");
#define Vc_BINARY_OPERATORS_(op_) \
\
template <typename L, typename R> \
Vc_INTRINSIC result_vector_type<L, R> operator op_(L &&lhs, R &&rhs) \
{ \
using Return = result_vector_type<L, R>; \
return Return(std::forward<L>(lhs)).operator op_(std::forward<R>(rhs)); \
}
Vc_ALL_ARITHMETICS(Vc_BINARY_OPERATORS_);
Vc_ALL_BINARY(Vc_BINARY_OPERATORS_);
#undef Vc_BINARY_OPERATORS_
#define Vc_BINARY_OPERATORS_(op_) \
\
template <typename L, typename R> \
Vc_INTRINSIC typename result_vector_type<L, R>::mask_type operator op_(L &&lhs, \
R &&rhs) \
{ \
using Promote = result_vector_type<L, R>; \
return Promote(std::forward<L>(lhs)) op_ Promote(std::forward<R>(rhs)); \
}
Vc_ALL_COMPARES(Vc_BINARY_OPERATORS_);
#undef Vc_BINARY_OPERATORS_
#define Vc_FORWARD_UNARY_OPERATOR(name_) \
\
template <typename T, std::size_t N, typename V, std::size_t M> \
inline SimdArray<T, N, V, M> name_(const SimdArray<T, N, V, M> &x) \
{ \
return SimdArray<T, N, V, M>::fromOperation( \
Common::Operations::Forward_##name_(), x); \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_FORWARD_UNARY_BOOL_OPERATOR(name_) \
\
template <typename T, std::size_t N, typename V, std::size_t M> \
inline SimdMaskArray<T, N, V, M> name_(const SimdArray<T, N, V, M> &x) \
{ \
return SimdMaskArray<T, N, V, M>::fromOperation( \
Common::Operations::Forward_##name_(), x); \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
#define Vc_FORWARD_BINARY_OPERATOR(name_) \
\
template <typename T, std::size_t N, typename V, std::size_t M> \
inline SimdArray<T, N, V, M> name_(const SimdArray<T, N, V, M> &x, \
const SimdArray<T, N, V, M> &y) \
{ \
return SimdArray<T, N, V, M>::fromOperation( \
Common::Operations::Forward_##name_(), x, y); \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_FORWARD_UNARY_OPERATOR(abs);
Vc_FORWARD_UNARY_OPERATOR(asin);
Vc_FORWARD_UNARY_OPERATOR(atan);
Vc_FORWARD_BINARY_OPERATOR(atan2);
Vc_FORWARD_UNARY_OPERATOR(ceil);
Vc_FORWARD_BINARY_OPERATOR(copysign);
Vc_FORWARD_UNARY_OPERATOR(cos);
Vc_FORWARD_UNARY_OPERATOR(exp);
Vc_FORWARD_UNARY_OPERATOR(exponent);
Vc_FORWARD_UNARY_OPERATOR(floor);
template <typename T, std::size_t N>
inline SimdArray<T, N> fma(const SimdArray<T, N> &a, const SimdArray<T, N> &b,
const SimdArray<T, N> &c)
{
return SimdArray<T, N>::fromOperation(Common::Operations::Forward_fma(), a, b, c);
}
Vc_FORWARD_UNARY_BOOL_OPERATOR(isfinite);
Vc_FORWARD_UNARY_BOOL_OPERATOR(isinf);
Vc_FORWARD_UNARY_BOOL_OPERATOR(isnan);
#if defined Vc_MSVC && defined Vc_IMPL_SSE
inline SimdMaskArray<double, 8, SSE::Vector<double>, 2> isnan(
const SimdArray<double, 8, SSE::Vector<double>, 2> &x)
{
using V = SSE::Vector<double>;
const SimdArray<double, 4, V, 2> &x0 = internal_data0(x);
const SimdArray<double, 4, V, 2> &x1 = internal_data1(x);
SimdMaskArray<double, 4, V, 2> r0;
SimdMaskArray<double, 4, V, 2> r1;
internal_data(internal_data0(r0)) = isnan(internal_data(internal_data0(x0)));
internal_data(internal_data1(r0)) = isnan(internal_data(internal_data1(x0)));
internal_data(internal_data0(r1)) = isnan(internal_data(internal_data0(x1)));
internal_data(internal_data1(r1)) = isnan(internal_data(internal_data1(x1)));
return {std::move(r0), std::move(r1)};
}
#endif
Vc_FORWARD_UNARY_BOOL_OPERATOR(isnegative);
template <typename T, std::size_t N>
inline SimdArray<T, N> frexp(const SimdArray<T, N> &x, SimdArray<int, N> *e)
{
return SimdArray<T, N>::fromOperation(Common::Operations::Forward_frexp(), x, e);
}
template <typename T, std::size_t N>
inline SimdArray<T, N> ldexp(const SimdArray<T, N> &x, const SimdArray<int, N> &e)
{
return SimdArray<T, N>::fromOperation(Common::Operations::Forward_ldexp(), x, e);
}
Vc_FORWARD_UNARY_OPERATOR(log);
Vc_FORWARD_UNARY_OPERATOR(log10);
Vc_FORWARD_UNARY_OPERATOR(log2);
Vc_FORWARD_UNARY_OPERATOR(reciprocal);
Vc_FORWARD_UNARY_OPERATOR(round);
Vc_FORWARD_UNARY_OPERATOR(rsqrt);
Vc_FORWARD_UNARY_OPERATOR(sin);
template <typename T, std::size_t N>
void sincos(const SimdArray<T, N> &x, SimdArray<T, N> *sin, SimdArray<T, N> *cos)
{
SimdArray<T, N>::callOperation(Common::Operations::Forward_sincos(), x, sin, cos);
}
Vc_FORWARD_UNARY_OPERATOR(sqrt);
Vc_FORWARD_UNARY_OPERATOR(trunc);
Vc_FORWARD_BINARY_OPERATOR(min);
Vc_FORWARD_BINARY_OPERATOR(max);
#undef Vc_FORWARD_UNARY_OPERATOR
#undef Vc_FORWARD_UNARY_BOOL_OPERATOR
#undef Vc_FORWARD_BINARY_OPERATOR
#ifdef Vc_MSVC
#define Vc_DUMMY_ARG0 , int = 0
#define Vc_DUMMY_ARG1 , long = 0
#define Vc_DUMMY_ARG2 , short = 0
#define Vc_DUMMY_ARG3 , char = '0'
#define Vc_DUMMY_ARG4 , unsigned = 0u
#define Vc_DUMMY_ARG5 , unsigned short = 0u
#else
#define Vc_DUMMY_ARG0 
#define Vc_DUMMY_ARG1 
#define Vc_DUMMY_ARG2 
#define Vc_DUMMY_ARG3 
#define Vc_DUMMY_ARG4 
#define Vc_DUMMY_ARG5 
#endif
template <typename Return, std::size_t N, typename T, typename... From>
Vc_INTRINSIC Vc_CONST enable_if<sizeof...(From) != 0, Return>
simd_cast_impl_smaller_input(const From &... xs, const T &last)
{
Return r = simd_cast<Return>(xs...);
for (size_t i = 0; i < N; ++i) {
r[i + N * sizeof...(From)] = static_cast<typename Return::EntryType>(last[i]);
}
return r;
}
template <typename Return, std::size_t N, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast_impl_smaller_input(const T &last)
{
Return r = Return();
for (size_t i = 0; i < N; ++i) {
r[i] = static_cast<typename Return::EntryType>(last[i]);
}
return r;
}
template <typename Return, std::size_t N, typename T, typename... From>
Vc_INTRINSIC Vc_CONST enable_if<sizeof...(From) != 0, Return> simd_cast_impl_larger_input(
const From &... xs, const T &last)
{
Return r = simd_cast<Return>(xs...);
for (size_t i = N * sizeof...(From); i < Return::Size; ++i) {
r[i] = static_cast<typename Return::EntryType>(last[i - N * sizeof...(From)]);
}
return r;
}
template <typename Return, std::size_t N, typename T>
Vc_INTRINSIC Vc_CONST Return simd_cast_impl_larger_input(const T &last)
{
Return r = Return();
for (size_t i = 0; i < Return::size(); ++i) {
r[i] = static_cast<typename Return::EntryType>(last[i]);
}
return r;
}
template <typename Return, typename T, typename... From>
Vc_INTRINSIC_L Vc_CONST_L Return
simd_cast_without_last(const From &... xs, const T &) Vc_INTRINSIC_R Vc_CONST_R;
template <typename... Ts> struct are_all_types_equal;
template <typename T>
struct are_all_types_equal<T> : public std::integral_constant<bool, true>
{
};
template <typename T0, typename T1, typename... Ts>
struct are_all_types_equal<T0, T1, Ts...>
: public std::integral_constant<
bool, std::is_same<T0, T1>::value && are_all_types_equal<T1, Ts...>::value>
{
};
template <typename Return, typename... Ts>
Vc_INTRINSIC Vc_CONST Return
simd_cast_interleaved_argument_order(const Ts &... a, const Ts &... b);
template <typename Return, std::size_t offset, typename From, typename... Froms>
Vc_INTRINSIC Vc_CONST
enable_if<(are_all_types_equal<From, Froms...>::value && offset == 0), Return>
simd_cast_with_offset(const From &x, const Froms &... xs);
template <typename Return, std::size_t offset, typename From>
Vc_INTRINSIC Vc_CONST
enable_if<(From::Size > offset && offset > 0 && offset % Return::Size == 0), Return>
simd_cast_with_offset(const From &x);
template <typename Return, std::size_t offset, typename From>
Vc_INTRINSIC Vc_CONST
enable_if<(From::Size > offset && offset > 0 && offset % Return::Size != 0 &&
((Traits::isSimdArray<Return>::value &&
!Traits::isAtomicSimdArray<Return>::value) ||
(Traits::isSimdMaskArray<Return>::value &&
!Traits::isAtomicSimdMaskArray<Return>::value))),
Return>
simd_cast_with_offset(const From &x);
template <typename Return, std::size_t offset, typename From>
Vc_INTRINSIC Vc_CONST
enable_if<(From::Size > offset && offset > 0 && offset % Return::Size != 0 &&
((Traits::isSimdArray<Return>::value &&
Traits::isAtomicSimdArray<Return>::value) ||
(Traits::isSimdMaskArray<Return>::value &&
Traits::isAtomicSimdMaskArray<Return>::value))),
Return>
simd_cast_with_offset(const From &x);
template <typename Return, std::size_t offset, typename From, typename... Froms>
Vc_INTRINSIC Vc_CONST enable_if<
(are_all_types_equal<From, Froms...>::value && From::Size <= offset), Return>
simd_cast_with_offset(const From &, const Froms &... xs)
{
return simd_cast_with_offset<Return, offset - From::Size>(xs...);
}
template <typename Return, std::size_t offset, typename From>
Vc_INTRINSIC Vc_CONST enable_if<(From::Size <= offset), Return> simd_cast_with_offset(
const From &)
{
return Return::Zero();
}
template <typename T, typename... Ts> struct first_type_of_impl
{
using type = T;
};
template <typename... Ts> using first_type_of = typename first_type_of_impl<Ts...>::type;
template <typename Return, typename From>
Vc_INTRINSIC Vc_CONST Return simd_cast_drop_arguments(From x);
template <typename Return, typename... Froms>
Vc_INTRINSIC Vc_CONST
enable_if<(are_all_types_equal<Froms...>::value &&
sizeof...(Froms) * first_type_of<Froms...>::Size < Return::Size),
Return>
simd_cast_drop_arguments(Froms... xs, first_type_of<Froms...> x);
template <typename Return, typename From, typename... Froms>
Vc_INTRINSIC Vc_CONST enable_if<
(are_all_types_equal<From, Froms...>::value &&
(1 + sizeof...(Froms)) * From::Size >= Return::Size && sizeof...(Froms) != 0),
Return>
simd_cast_drop_arguments(Froms... xs, From x, From);
template <typename Return, typename From>
Vc_INTRINSIC Vc_CONST
enable_if<(are_all_types_equal<From>::value && From::Size >= Return::Size), Return>
simd_cast_drop_arguments(From x, From);
namespace
{
#ifdef Vc_DEBUG_SIMD_CAST
void debugDoNothing(const std::initializer_list<void *> &) {}
template <typename T0, typename... Ts>
inline void vc_debug_(const char *prefix, const char *suffix, const T0 &arg0,
const Ts &... args)
{
std::cerr << prefix << arg0;
debugDoNothing({&(std::cerr << ", " << args)...});
std::cerr << suffix;
}
#else
template <typename T0, typename... Ts>
Vc_INTRINSIC void vc_debug_(const char *, const char *, const T0 &, const Ts &...)
{
}
#endif
}
template <size_t A, size_t B>
struct is_less : public std::integral_constant<bool, (A < B)> {
};
template <size_t N>
struct is_power_of_2 : public std::integral_constant<bool, ((N - 1) & N) == 0> {
};
#define Vc_SIMDARRAY_CASTS(SimdArrayType_,NativeType_) \
template <typename Return, typename T, typename A, typename... Froms> \
Vc_INTRINSIC Vc_CONST enable_if< \
(Traits::isAtomic##SimdArrayType_<Return>::value && \
is_less<NativeType_<T, A>::Size * sizeof...(Froms), Return::Size>::value && \
are_all_types_equal<NativeType_<T, A>, Froms...>::value && \
!detail::is_fixed_size_abi<A>::value), \
Return> \
simd_cast(NativeType_<T, A> x, Froms... xs) \
{ \
vc_debug_("simd_cast{1}(", ")\n", x, xs...); \
return {private_init, simd_cast<typename Return::storage_type>(x, xs...)}; \
} \
template <typename Return, typename T, typename A, typename... Froms> \
Vc_INTRINSIC Vc_CONST enable_if< \
(Traits::isAtomic##SimdArrayType_<Return>::value && \
!is_less<NativeType_<T, A>::Size * sizeof...(Froms), Return::Size>::value && \
are_all_types_equal<NativeType_<T, A>, Froms...>::value && \
!detail::is_fixed_size_abi<A>::value), \
Return> \
simd_cast(NativeType_<T, A> x, Froms... xs) \
{ \
vc_debug_("simd_cast{2}(", ")\n", x, xs...); \
return {simd_cast_without_last<Return, NativeType_<T, A>, Froms...>(x, xs...)}; \
} \
template <typename Return, typename T, typename A, typename... Froms> \
Vc_INTRINSIC Vc_CONST \
enable_if<(Traits::is##SimdArrayType_<Return>::value && \
!Traits::isAtomic##SimdArrayType_<Return>::value && \
is_less<Common::left_size<Return::Size>(), \
NativeType_<T, A>::Size *(1 + sizeof...(Froms))>::value && \
are_all_types_equal<NativeType_<T, A>, Froms...>::value && \
!detail::is_fixed_size_abi<A>::value), \
Return> \
simd_cast(NativeType_<T, A> x, Froms... xs) \
{ \
vc_debug_("simd_cast{3}(", ")\n", x, xs...); \
using R0 = typename Return::storage_type0; \
using R1 = typename Return::storage_type1; \
return {simd_cast_drop_arguments<R0, Froms...>(x, xs...), \
simd_cast_with_offset<R1, R0::Size>(x, xs...)}; \
} \
template <typename Return, typename T, typename A, typename... Froms> \
Vc_INTRINSIC Vc_CONST \
enable_if<(Traits::is##SimdArrayType_<Return>::value && \
!Traits::isAtomic##SimdArrayType_<Return>::value && \
!is_less<Common::left_size<Return::Size>(), \
NativeType_<T, A>::Size *(1 + sizeof...(Froms))>::value && \
are_all_types_equal<NativeType_<T, A>, Froms...>::value && \
!detail::is_fixed_size_abi<A>::value), \
Return> \
simd_cast(NativeType_<T, A> x, Froms... xs) \
{ \
vc_debug_("simd_cast{4}(", ")\n", x, xs...); \
using R0 = typename Return::storage_type0; \
using R1 = typename Return::storage_type1; \
return {simd_cast<R0>(x, xs...), R1::Zero()}; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_SIMDARRAY_CASTS(SimdArray, Vc::Vector);
Vc_SIMDARRAY_CASTS(SimdMaskArray, Vc::Mask);
#undef Vc_SIMDARRAY_CASTS
#define Vc_SIMDARRAY_CASTS(SimdArrayType_,NativeType_) \
\
template <typename Return, int offset, typename T, typename A> \
Vc_INTRINSIC Vc_CONST \
enable_if<Traits::isAtomic##SimdArrayType_<Return>::value, Return> \
simd_cast(NativeType_<T, A> x Vc_DUMMY_ARG0) \
{ \
vc_debug_("simd_cast{offset, atomic}(", ")\n", offset, x); \
return {private_init, simd_cast<typename Return::storage_type, offset>(x)}; \
} \
\
template <typename Return, int offset, typename T, typename A> \
Vc_INTRINSIC Vc_CONST \
enable_if<(Traits::is##SimdArrayType_<Return>::value && \
!Traits::isAtomic##SimdArrayType_<Return>::value && \
Return::Size * offset + Common::left_size<Return::Size>() < \
NativeType_<T, A>::Size), \
Return> \
simd_cast(NativeType_<T, A> x Vc_DUMMY_ARG1) \
{ \
vc_debug_("simd_cast{offset, split Return}(", ")\n", offset, x); \
using R0 = typename Return::storage_type0; \
constexpr int entries_offset = offset * Return::Size; \
constexpr int entries_offset_right = entries_offset + R0::Size; \
return { \
simd_cast_with_offset<typename Return::storage_type0, entries_offset>(x), \
simd_cast_with_offset<typename Return::storage_type1, entries_offset_right>( \
x)}; \
} \
\
\
template <typename Return, int offset, typename T, typename A> \
Vc_INTRINSIC Vc_CONST \
enable_if<(Traits::is##SimdArrayType_<Return>::value && \
!Traits::isAtomic##SimdArrayType_<Return>::value && \
Return::Size * offset + Common::left_size<Return::Size>() >= \
NativeType_<T, A>::Size), \
Return> \
simd_cast(NativeType_<T, A> x Vc_DUMMY_ARG2) \
{ \
vc_debug_("simd_cast{offset, R1::Zero}(", ")\n", offset, x); \
using R0 = typename Return::storage_type0; \
using R1 = typename Return::storage_type1; \
constexpr int entries_offset = offset * Return::Size; \
return {simd_cast_with_offset<R0, entries_offset>(x), R1::Zero()}; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_SIMDARRAY_CASTS(SimdArray, Vc::Vector);
Vc_SIMDARRAY_CASTS(SimdMaskArray, Vc::Mask);
#undef Vc_SIMDARRAY_CASTS
#define Vc_SIMDARRAY_CASTS(SimdArrayType_) \
\
template <typename Return, typename T, std::size_t N, typename V, typename... From> \
Vc_INTRINSIC Vc_CONST \
enable_if<(are_all_types_equal<SimdArrayType_<T, N, V, N>, From...>::value && \
(sizeof...(From) == 0 || N * sizeof...(From) < Return::Size) && \
!std::is_same<Return, SimdArrayType_<T, N, V, N>>::value), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, N> &x0, const From &... xs) \
{ \
vc_debug_("simd_cast{indivisible}(", ")\n", x0, xs...); \
return simd_cast<Return>(internal_data(x0), internal_data(xs)...); \
} \
\
template <typename Return, typename T, std::size_t N, typename V, typename... From> \
Vc_INTRINSIC Vc_CONST \
enable_if<(are_all_types_equal<SimdArrayType_<T, N, V, N>, From...>::value && \
(sizeof...(From) > 0 && (N * sizeof...(From) >= Return::Size)) && \
!std::is_same<Return, SimdArrayType_<T, N, V, N>>::value), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, N> &x0, const From &... xs) \
{ \
vc_debug_("simd_cast{indivisible2}(", ")\n", x0, xs...); \
return simd_cast_without_last<Return, \
typename SimdArrayType_<T, N, V, N>::storage_type, \
typename From::storage_type...>( \
internal_data(x0), internal_data(xs)...); \
} \
\
template <typename Return, typename T, std::size_t N, typename V, std::size_t M, \
typename... From> \
Vc_INTRINSIC Vc_CONST enable_if< \
(N != M && are_all_types_equal<SimdArrayType_<T, N, V, M>, From...>::value && \
!std::is_same<Return, SimdArrayType_<T, N, V, M>>::value && \
is_less<N * sizeof...(From), Return::Size>::value && is_power_of_2<N>::value), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x0, const From &... xs) \
{ \
vc_debug_("simd_cast{bisectable}(", ")\n", x0, xs...); \
return simd_cast_interleaved_argument_order< \
Return, typename SimdArrayType_<T, N, V, M>::storage_type0, \
typename From::storage_type0...>(internal_data0(x0), internal_data0(xs)..., \
internal_data1(x0), internal_data1(xs)...); \
} \
\
template <typename Return, typename T, std::size_t N, typename V, std::size_t M, \
typename... From> \
Vc_INTRINSIC Vc_CONST enable_if< \
(N != M && are_all_types_equal<SimdArrayType_<T, N, V, M>, From...>::value && \
!is_less<N * sizeof...(From), Return::Size>::value && is_power_of_2<N>::value), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x0, const From &... xs) \
{ \
vc_debug_("simd_cast{bisectable2}(", ")\n", x0, xs...); \
return simd_cast_without_last<Return, SimdArrayType_<T, N, V, M>, From...>( \
x0, xs...); \
} \
\
template <typename Return, typename T, std::size_t N, typename V, std::size_t M, \
typename... From> \
Vc_INTRINSIC Vc_CONST enable_if< \
(N != M && are_all_types_equal<SimdArrayType_<T, N, V, M>, From...>::value && \
N * (1 + sizeof...(From)) <= Return::Size && !is_power_of_2<N>::value), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x0, const From &... xs) \
{ \
vc_debug_("simd_cast{remaining}(", ")\n", x0, xs...); \
return simd_cast_impl_smaller_input<Return, N, SimdArrayType_<T, N, V, M>, \
From...>(x0, xs...); \
} \
\
template <typename Return, typename T, std::size_t N, typename V, std::size_t M, \
typename... From> \
Vc_INTRINSIC Vc_CONST enable_if< \
(N != M && are_all_types_equal<SimdArrayType_<T, N, V, M>, From...>::value && \
N * (1 + sizeof...(From)) > Return::Size && !is_power_of_2<N>::value), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x0, const From &... xs) \
{ \
vc_debug_("simd_cast{remaining2}(", ")\n", x0, xs...); \
return simd_cast_impl_larger_input<Return, N, SimdArrayType_<T, N, V, M>, \
From...>(x0, xs...); \
} \
\
template <typename Return, typename T, std::size_t N, typename V, std::size_t M> \
Vc_INTRINSIC Vc_CONST \
enable_if<(N != M && N >= 2 * Return::Size && is_power_of_2<N>::value), Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x) \
{ \
vc_debug_("simd_cast{single bisectable}(", ")\n", x); \
return simd_cast<Return>(internal_data0(x)); \
} \
template <typename Return, typename T, std::size_t N, typename V, std::size_t M> \
Vc_INTRINSIC Vc_CONST enable_if<(N != M && N > Return::Size && \
N < 2 * Return::Size && is_power_of_2<N>::value), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x) \
{ \
vc_debug_("simd_cast{single bisectable2}(", ")\n", x); \
return simd_cast<Return>(internal_data0(x), internal_data1(x)); \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_SIMDARRAY_CASTS(SimdArray);
Vc_SIMDARRAY_CASTS(SimdMaskArray);
#undef Vc_SIMDARRAY_CASTS
#define Vc_SIMDARRAY_CASTS(SimdArrayType_) \
\
template <typename Return, int offset, typename T, std::size_t N, typename V, \
std::size_t M> \
Vc_INTRINSIC Vc_CONST enable_if<(offset == 0), Return> simd_cast( \
const SimdArrayType_<T, N, V, M> &x Vc_DUMMY_ARG0) \
{ \
vc_debug_("simd_cast{offset == 0}(", ")\n", offset, x); \
return simd_cast<Return>(x); \
} \
\
template <typename Return, int offset, typename T, std::size_t N, typename V> \
Vc_INTRINSIC Vc_CONST enable_if<(offset != 0), Return> simd_cast( \
const SimdArrayType_<T, N, V, N> &x Vc_DUMMY_ARG1) \
{ \
vc_debug_("simd_cast{offset, forward}(", ")\n", offset, x); \
return simd_cast<Return, offset>(internal_data(x)); \
} \
\
template <typename Return, int offset, typename T, std::size_t N, typename V, \
std::size_t M> \
Vc_INTRINSIC Vc_CONST \
enable_if<(N != M && offset * Return::Size >= Common::left_size<N>() && \
offset != 0 && Common::left_size<N>() % Return::Size == 0), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x Vc_DUMMY_ARG2) \
{ \
vc_debug_("simd_cast{offset, right}(", ")\n", offset, x); \
return simd_cast<Return, offset - Common::left_size<N>() / Return::Size>( \
internal_data1(x)); \
} \
\
template <typename Return, int offset, typename T, std::size_t N, typename V, \
std::size_t M> \
Vc_INTRINSIC Vc_CONST \
enable_if<(N != M && offset * Return::Size >= Common::left_size<N>() && \
offset != 0 && Common::left_size<N>() % Return::Size != 0), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x Vc_DUMMY_ARG3) \
{ \
vc_debug_("simd_cast{offset, right, nofit}(", ")\n", offset, x); \
return simd_cast_with_offset<Return, \
offset * Return::Size - Common::left_size<N>()>( \
internal_data1(x)); \
} \
\
template <typename Return, int offset, typename T, std::size_t N, typename V, \
std::size_t M> \
Vc_INTRINSIC Vc_CONST enable_if< \
(N != M && \
offset != 0 && (offset + 1) * Return::Size <= Common::left_size<N>()), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x Vc_DUMMY_ARG4) \
{ \
vc_debug_("simd_cast{offset, left}(", ")\n", offset, x); \
return simd_cast<Return, offset>(internal_data0(x)); \
} \
\
template <typename Return, int offset, typename T, std::size_t N, typename V, \
std::size_t M> \
Vc_INTRINSIC Vc_CONST \
enable_if<(N != M && (offset * Return::Size < Common::left_size<N>()) && \
offset != 0 && (offset + 1) * Return::Size > Common::left_size<N>()), \
Return> \
simd_cast(const SimdArrayType_<T, N, V, M> &x Vc_DUMMY_ARG5) \
{ \
vc_debug_("simd_cast{offset, copy scalars}(", ")\n", offset, x); \
using R = typename Return::EntryType; \
Return r = Return::Zero(); \
for (std::size_t i = offset * Return::Size; \
i < std::min(N, (offset + 1) * Return::Size); ++i) { \
r[i - offset * Return::Size] = static_cast<R>(x[i]); \
} \
return r; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_SIMDARRAY_CASTS(SimdArray);
Vc_SIMDARRAY_CASTS(SimdMaskArray);
#undef Vc_SIMDARRAY_CASTS
template <typename Return, typename From>
Vc_INTRINSIC Vc_CONST Return simd_cast_drop_arguments(From x)
{
return simd_cast<Return>(x);
}
template <typename Return, typename... Froms>
Vc_INTRINSIC Vc_CONST
enable_if<(are_all_types_equal<Froms...>::value &&
sizeof...(Froms) * first_type_of<Froms...>::Size < Return::Size),
Return>
simd_cast_drop_arguments(Froms... xs, first_type_of<Froms...> x)
{
return simd_cast<Return>(xs..., x);
}
template <typename Return, typename From, typename... Froms>
Vc_INTRINSIC Vc_CONST enable_if<
(are_all_types_equal<From, Froms...>::value &&
(1 + sizeof...(Froms)) * From::Size >= Return::Size && sizeof...(Froms) != 0),
Return>
simd_cast_drop_arguments(Froms... xs, From x, From)
{
return simd_cast_drop_arguments<Return, Froms...>(xs..., x);
}
template <typename Return, typename From>
Vc_INTRINSIC Vc_CONST
enable_if<(are_all_types_equal<From>::value && From::Size >= Return::Size), Return>
simd_cast_drop_arguments(From x, From)
{
return simd_cast_drop_arguments<Return>(x);
}
template <typename Return, std::size_t offset, typename From>
Vc_INTRINSIC Vc_CONST
enable_if<(From::Size > offset && offset > 0 && offset % Return::Size == 0),
Return> simd_cast_with_offset(const From &x)
{
return simd_cast<Return, offset / Return::Size>(x);
}
template <typename Return, std::size_t offset, typename From>
Vc_INTRINSIC Vc_CONST
enable_if<(From::Size > offset && offset > 0 && offset % Return::Size != 0 &&
((Traits::isSimdArray<Return>::value &&
!Traits::isAtomicSimdArray<Return>::value) ||
(Traits::isSimdMaskArray<Return>::value &&
!Traits::isAtomicSimdMaskArray<Return>::value))),
Return>
simd_cast_with_offset(const From &x)
{
using R0 = typename Return::storage_type0;
using R1 = typename Return::storage_type1;
return {simd_cast_with_offset<R0, offset>(x),
simd_cast_with_offset<R1, offset + R0::Size>(x)};
}
template <typename Return, std::size_t offset, typename From>
Vc_INTRINSIC Vc_CONST
enable_if<(From::Size > offset && offset > 0 && offset % Return::Size != 0 &&
((Traits::isSimdArray<Return>::value &&
Traits::isAtomicSimdArray<Return>::value) ||
(Traits::isSimdMaskArray<Return>::value &&
Traits::isAtomicSimdMaskArray<Return>::value))),
Return>
simd_cast_with_offset(const From &x)
{
return simd_cast<Return, offset / Return::Size>(x.shifted(offset % Return::Size));
}
template <typename Return, std::size_t offset, typename From, typename... Froms>
Vc_INTRINSIC Vc_CONST
enable_if<(are_all_types_equal<From, Froms...>::value && offset == 0), Return>
simd_cast_with_offset(const From &x, const Froms &... xs)
{
return simd_cast<Return>(x, xs...);
}
template <typename Return, typename T, typename... From>
Vc_INTRINSIC Vc_CONST Return simd_cast_without_last(const From &... xs, const T &)
{
return simd_cast<Return>(xs...);
}
#ifdef Vc_MSVC
template <std::size_t I, typename T0>
Vc_INTRINSIC Vc_CONST enable_if<(I == 0), T0> extract_interleaved(const T0 &a0, const T0 &)
{
return a0;
}
template <std::size_t I, typename T0>
Vc_INTRINSIC Vc_CONST enable_if<(I == 1), T0> extract_interleaved(const T0 &, const T0 &b0)
{
return b0;
}
#endif
template <std::size_t I, typename T0, typename... Ts>
Vc_INTRINSIC Vc_CONST enable_if<(I == 0), T0> extract_interleaved(const T0 &a0,
const Ts &...,
const T0 &,
const Ts &...)
{
return a0;
}
template <std::size_t I, typename T0, typename... Ts>
Vc_INTRINSIC Vc_CONST enable_if<(I == 1), T0> extract_interleaved(const T0 &,
const Ts &...,
const T0 &b0,
const Ts &...)
{
return b0;
}
template <std::size_t I, typename T0, typename... Ts>
Vc_INTRINSIC Vc_CONST enable_if<(I > 1), T0> extract_interleaved(const T0 &,
const Ts &... a,
const T0 &,
const Ts &... b)
{
return extract_interleaved<I - 2, Ts...>(a..., b...);
}
template <typename Return, typename... Ts, std::size_t... Indexes>
Vc_INTRINSIC Vc_CONST Return
simd_cast_interleaved_argument_order_1(index_sequence<Indexes...>, const Ts &... a,
const Ts &... b)
{
return simd_cast<Return>(extract_interleaved<Indexes, Ts...>(a..., b...)...);
}
template <typename Return, typename... Ts>
Vc_INTRINSIC Vc_CONST Return
simd_cast_interleaved_argument_order(const Ts &... a, const Ts &... b)
{
using seq = make_index_sequence<sizeof...(Ts)*2>;
return simd_cast_interleaved_argument_order_1<Return, Ts...>(seq(), a..., b...);
}
#define Vc_CONDITIONAL_ASSIGN(name_,op_) \
template <Operator O, typename T, std::size_t N, typename V, size_t VN, typename M, \
typename U> \
Vc_INTRINSIC enable_if<O == Operator::name_, void> conditional_assign( \
SimdArray<T, N, V, VN> &lhs, M &&mask, U &&rhs) \
{ \
lhs(mask) op_ rhs; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_CONDITIONAL_ASSIGN( Assign, =);
Vc_CONDITIONAL_ASSIGN( PlusAssign, +=);
Vc_CONDITIONAL_ASSIGN( MinusAssign, -=);
Vc_CONDITIONAL_ASSIGN( MultiplyAssign, *=);
Vc_CONDITIONAL_ASSIGN( DivideAssign, /=);
Vc_CONDITIONAL_ASSIGN( RemainderAssign, %=);
Vc_CONDITIONAL_ASSIGN( XorAssign, ^=);
Vc_CONDITIONAL_ASSIGN( AndAssign, &=);
Vc_CONDITIONAL_ASSIGN( OrAssign, |=);
Vc_CONDITIONAL_ASSIGN( LeftShiftAssign,<<=);
Vc_CONDITIONAL_ASSIGN(RightShiftAssign,>>=);
#undef Vc_CONDITIONAL_ASSIGN
#define Vc_CONDITIONAL_ASSIGN(name_,expr_) \
template <Operator O, typename T, std::size_t N, typename V, size_t VN, typename M> \
Vc_INTRINSIC enable_if<O == Operator::name_, SimdArray<T, N, V, VN>> \
conditional_assign(SimdArray<T, N, V, VN> &lhs, M &&mask) \
{ \
return expr_; \
} \
Vc_NOTHING_EXPECTING_SEMICOLON
Vc_CONDITIONAL_ASSIGN(PostIncrement, lhs(mask)++);
Vc_CONDITIONAL_ASSIGN( PreIncrement, ++lhs(mask));
Vc_CONDITIONAL_ASSIGN(PostDecrement, lhs(mask)--);
Vc_CONDITIONAL_ASSIGN( PreDecrement, --lhs(mask));
#undef Vc_CONDITIONAL_ASSIGN
namespace Common
{
template <typename T, size_t N, typename V>
inline void transpose_impl(
TransposeTag<4, 4>, SimdArray<T, N, V, N> *Vc_RESTRICT r[],
const TransposeProxy<SimdArray<T, N, V, N>, SimdArray<T, N, V, N>,
SimdArray<T, N, V, N>, SimdArray<T, N, V, N>> &proxy)
{
V *Vc_RESTRICT r2[4] = {&internal_data(*r[0]), &internal_data(*r[1]),
&internal_data(*r[2]), &internal_data(*r[3])};
transpose_impl(TransposeTag<4, 4>(), &r2[0],
TransposeProxy<V, V, V, V>{internal_data(std::get<0>(proxy.in)),
internal_data(std::get<1>(proxy.in)),
internal_data(std::get<2>(proxy.in)),
internal_data(std::get<3>(proxy.in))});
}
template <typename T, typename V>
inline void transpose_impl(
TransposeTag<2, 4>, SimdArray<T, 4, V, 1> *Vc_RESTRICT r[],
const TransposeProxy<SimdArray<T, 2, V, 1>, SimdArray<T, 2, V, 1>,
SimdArray<T, 2, V, 1>, SimdArray<T, 2, V, 1>> &proxy)
{
auto &lo = *r[0];
auto &hi = *r[1];
internal_data0(internal_data0(lo)) = internal_data0(std::get<0>(proxy.in));
internal_data1(internal_data0(lo)) = internal_data0(std::get<1>(proxy.in));
internal_data0(internal_data1(lo)) = internal_data0(std::get<2>(proxy.in));
internal_data1(internal_data1(lo)) = internal_data0(std::get<3>(proxy.in));
internal_data0(internal_data0(hi)) = internal_data1(std::get<0>(proxy.in));
internal_data1(internal_data0(hi)) = internal_data1(std::get<1>(proxy.in));
internal_data0(internal_data1(hi)) = internal_data1(std::get<2>(proxy.in));
internal_data1(internal_data1(hi)) = internal_data1(std::get<3>(proxy.in));
}
template <typename T, typename V>
inline void transpose_impl(
TransposeTag<4, 4>, SimdArray<T, 1, V, 1> *Vc_RESTRICT r[],
const TransposeProxy<SimdArray<T, 1, V, 1>, SimdArray<T, 1, V, 1>,
SimdArray<T, 1, V, 1>, SimdArray<T, 1, V, 1>> &proxy)
{
V *Vc_RESTRICT r2[4] = {&internal_data(*r[0]), &internal_data(*r[1]),
&internal_data(*r[2]), &internal_data(*r[3])};
transpose_impl(TransposeTag<4, 4>(), &r2[0],
TransposeProxy<V, V, V, V>{internal_data(std::get<0>(proxy.in)),
internal_data(std::get<1>(proxy.in)),
internal_data(std::get<2>(proxy.in)),
internal_data(std::get<3>(proxy.in))});
}
template <typename T, size_t N, typename V>
inline void transpose_impl(
TransposeTag<4, 4>, SimdArray<T, N, V, 1> *Vc_RESTRICT r[],
const TransposeProxy<SimdArray<T, N, V, 1>, SimdArray<T, N, V, 1>,
SimdArray<T, N, V, 1>, SimdArray<T, N, V, 1>> &proxy)
{
SimdArray<T, N, V, 1> *Vc_RESTRICT r0[4 / 2] = {r[0], r[1]};
SimdArray<T, N, V, 1> *Vc_RESTRICT r1[4 / 2] = {r[2], r[3]};
using H = SimdArray<T, 2>;
transpose_impl(TransposeTag<2, 4>(), &r0[0],
TransposeProxy<H, H, H, H>{internal_data0(std::get<0>(proxy.in)),
internal_data0(std::get<1>(proxy.in)),
internal_data0(std::get<2>(proxy.in)),
internal_data0(std::get<3>(proxy.in))});
transpose_impl(TransposeTag<2, 4>(), &r1[0],
TransposeProxy<H, H, H, H>{internal_data1(std::get<0>(proxy.in)),
internal_data1(std::get<1>(proxy.in)),
internal_data1(std::get<2>(proxy.in)),
internal_data1(std::get<3>(proxy.in))});
}
}
static_assert(Traits::has_no_allocated_data<const volatile Vc::SimdArray<int, 4> &>::value, "");
static_assert(Traits::has_no_allocated_data<const volatile Vc::SimdArray<int, 4>>::value, "");
static_assert(Traits::has_no_allocated_data<volatile Vc::SimdArray<int, 4> &>::value, "");
static_assert(Traits::has_no_allocated_data<volatile Vc::SimdArray<int, 4>>::value, "");
static_assert(Traits::has_no_allocated_data<const Vc::SimdArray<int, 4> &>::value, "");
static_assert(Traits::has_no_allocated_data<const Vc::SimdArray<int, 4>>::value, "");
static_assert(Traits::has_no_allocated_data<Vc::SimdArray<int, 4>>::value, "");
static_assert(Traits::has_no_allocated_data<Vc::SimdArray<int, 4> &&>::value, "");
namespace Detail
{
template <class T, size_t N, class V, size_t VSizeof>
struct InterleaveImpl<SimdArray<T, N, V, N>, N, VSizeof> {
template <class I, class... VV>
static Vc_INTRINSIC void interleave(T *const data, const I &i, const VV &... vv)
{
InterleaveImpl<V, N, VSizeof>::interleave(data, i, internal_data(vv)...);
}
template <class I, class... VV>
static Vc_INTRINSIC void deinterleave(T const *const data, const I &i, VV &... vv)
{
InterleaveImpl<V, N, VSizeof>::deinterleave(data, i, internal_data(vv)...);
}
};
}
}
namespace std
{
template <typename T, size_t N, typename V, size_t VN>
struct numeric_limits<Vc::SimdArray<T, N, V, VN>> : public numeric_limits<T> {
private:
using R = Vc::SimdArray<T, N, V, VN>;
public:
static Vc_ALWAYS_INLINE Vc_CONST R max() noexcept { return numeric_limits<T>::max(); }
static Vc_ALWAYS_INLINE Vc_CONST R min() noexcept { return numeric_limits<T>::min(); }
static Vc_ALWAYS_INLINE Vc_CONST R lowest() noexcept
{
return numeric_limits<T>::lowest();
}
static Vc_ALWAYS_INLINE Vc_CONST R epsilon() noexcept
{
return numeric_limits<T>::epsilon();
}
static Vc_ALWAYS_INLINE Vc_CONST R round_error() noexcept
{
return numeric_limits<T>::round_error();
}
static Vc_ALWAYS_INLINE Vc_CONST R infinity() noexcept
{
return numeric_limits<T>::infinity();
}
static Vc_ALWAYS_INLINE Vc_CONST R quiet_NaN() noexcept
{
return numeric_limits<T>::quiet_NaN();
}
static Vc_ALWAYS_INLINE Vc_CONST R signaling_NaN() noexcept
{
return numeric_limits<T>::signaling_NaN();
}
static Vc_ALWAYS_INLINE Vc_CONST R denorm_min() noexcept
{
return numeric_limits<T>::denorm_min();
}
};
}
#endif
#ifndef VC_COMMON_ALIGNEDBASE_H_
#define VC_COMMON_ALIGNEDBASE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename T> constexpr T max(T a) { return a; }
template <typename T, typename... Ts> constexpr T max(T a, T b, Ts... rest)
{
return a > b ? max(a, rest...) : max(b, rest...);
}
}
namespace Common
{
template <std::size_t> Vc_INTRINSIC void *aligned_malloc(std::size_t);
Vc_ALWAYS_INLINE void free(void *);
}
template <std::size_t Alignment> struct alignas(Alignment) AlignedBase
{
Vc_FREE_STORE_OPERATORS_ALIGNED(Alignment);
};
using VectorAlignedBase = AlignedBase<
Detail::max(alignof(Vector<float>), alignof(Vector<double>), alignof(Vector<ullong>),
alignof(Vector<llong>), alignof(Vector<ulong>), alignof(Vector<long>),
alignof(Vector<uint>), alignof(Vector<int>), alignof(Vector<ushort>),
alignof(Vector<short>), alignof(Vector<uchar>), alignof(Vector<schar>))>;
template <typename V> using VectorAlignedBaseT = AlignedBase<alignof(V)>;
using MemoryAlignedBase = AlignedBase<
Detail::max(Vector<float>::MemoryAlignment, Vector<double>::MemoryAlignment,
Vector<ullong>::MemoryAlignment, Vector<llong>::MemoryAlignment,
Vector<ulong>::MemoryAlignment, Vector<long>::MemoryAlignment,
Vector<uint>::MemoryAlignment, Vector<int>::MemoryAlignment,
Vector<ushort>::MemoryAlignment, Vector<short>::MemoryAlignment,
Vector<uchar>::MemoryAlignment, Vector<schar>::MemoryAlignment)>;
template <typename V> using MemoryAlignedBaseT = AlignedBase<V::MemoryAlignment>;
}
#endif
namespace Vc_VERSIONED_NAMESPACE {
constexpr std::size_t VectorAlignment = alignof(VectorAlignedBase);
constexpr std::size_t MemoryAlignment = alignof(MemoryAlignedBase);
}
#define Vc_VECTOR_DECLARED_ 1
#ifndef VC_SCALAR_DEINTERLEAVE_H_
#define VC_SCALAR_DEINTERLEAVE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename T, typename M, typename A>
Vc_ALWAYS_INLINE void deinterleave(Scalar::Vector<T> &a, Scalar::Vector<T> &b,
const M *mem, A)
{
a = mem[0];
b = mem[1];
}
Vc_ALWAYS_INLINE void prefetchForOneRead(const void *, VectorAbi::Scalar) {}
Vc_ALWAYS_INLINE void prefetchForModify(const void *, VectorAbi::Scalar) {}
Vc_ALWAYS_INLINE void prefetchClose(const void *, VectorAbi::Scalar) {}
Vc_ALWAYS_INLINE void prefetchMid(const void *, VectorAbi::Scalar) {}
Vc_ALWAYS_INLINE void prefetchFar(const void *, VectorAbi::Scalar) {}
}
}
#endif
#ifndef VC_SCALAR_MATH_H_
#define VC_SCALAR_MATH_H_ 
#include <cstdlib>
namespace Vc_VERSIONED_NAMESPACE
{
Vc_INTRINSIC Scalar::float_v copysign(Scalar::float_v mag, Scalar::float_v sign)
{
union {
float f;
unsigned int i;
} value, s;
value.f = mag.data();
s.f = sign.data();
value.i = (s.i & 0x80000000u) | (value.i & 0x7fffffffu);
return Scalar::float_v{value.f};
}
Vc_INTRINSIC Vc_CONST Scalar::double_v copysign(Scalar::double_v mag,
Scalar::double_v sign)
{
union {
double f;
unsigned long long i;
} value, s;
value.f = mag.data();
s.f = sign.data();
value.i = (s.i & 0x8000000000000000ull) | (value.i & 0x7fffffffffffffffull);
return Scalar::double_v{value.f};
}
#define Vc_MINMAX(V) \
static Vc_ALWAYS_INLINE Scalar::V min(const Scalar::V &x, const Scalar::V &y) \
{ \
return Scalar::V(std::min(x.data(), y.data())); \
} \
static Vc_ALWAYS_INLINE Scalar::V max(const Scalar::V &x, const Scalar::V &y) \
{ \
return Scalar::V(std::max(x.data(), y.data())); \
}
Vc_ALL_VECTOR_TYPES(Vc_MINMAX);
#undef Vc_MINMAX
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> sqrt (const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::sqrt(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> rsqrt(const Scalar::Vector<T> &x)
{
const typename Vector<T, VectorAbi::Scalar>::EntryType one = 1; return Scalar::Vector<T>(one / std::sqrt(x.data()));
}
template <typename T,
typename = enable_if<std::is_same<T, double>::value || std::is_same<T, float>::value ||
std::is_same<T, short>::value ||
std::is_same<T, int>::value>>
Vc_ALWAYS_INLINE Vc_PURE Scalar::Vector<T> abs(Scalar::Vector<T> x)
{
return std::abs(x.data());
}
template<typename T> static Vc_ALWAYS_INLINE void sincos(const Scalar::Vector<T> &x, Scalar::Vector<T> *sin, Scalar::Vector<T> *cos)
{
#if defined(_WIN32) || defined(__APPLE__)
sin->data() = std::sin(x.data());
cos->data() = std::cos(x.data());
#elif Vc_HAS_BUILTIN(__builtin_sincosf) || defined Vc_GCC
__builtin_sincosf(x.data(), &sin->data(), &cos->data());
#else
sincosf(x.data(), &sin->data(), &cos->data());
#endif
}
template<> Vc_ALWAYS_INLINE void sincos(const Scalar::Vector<double> &x, Scalar::Vector<double> *sin, Scalar::Vector<double> *cos)
{
#if defined(_WIN32) || defined(__APPLE__)
sin->data() = std::sin(x.data());
cos->data() = std::cos(x.data());
#elif Vc_HAS_BUILTIN(__builtin_sincos) || defined Vc_GCC
__builtin_sincos(x.data(), &sin->data(), &cos->data());
#else
::sincos(x.data(), &sin->data(), &cos->data());
#endif
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> sin (const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::sin(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> asin (const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::asin(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> cos (const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::cos(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> log (const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::log(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> log10(const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::log10(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> log2(const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::log2(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> exp (const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::exp(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> atan (const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::atan( x.data() ));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> atan2(const Scalar::Vector<T> &x, const Scalar::Vector<T> &y)
{
return Scalar::Vector<T>(std::atan2( x.data(), y.data() ));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> trunc(const Scalar::Vector<T> &x)
{
return std::trunc(x.data());
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> floor(const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::floor(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> ceil(const Scalar::Vector<T> &x)
{
return Scalar::Vector<T>(std::ceil(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> round(const Scalar::Vector<T> &x)
{
return x;
}
namespace
{
template<typename T> bool _realIsEvenHalf(T x) {
const T two = 2;
const T half = 0.5;
const T f = std::floor(x * half) * two;
return (x - f) == half;
}
}
template<> Vc_ALWAYS_INLINE Scalar::Vector<float> round(const Scalar::Vector<float> &x)
{
return Scalar::float_v(std::floor(x.data() + 0.5f) - (_realIsEvenHalf(x.data()) ? 1.f : 0.f));
}
template<> Vc_ALWAYS_INLINE Scalar::Vector<double> round(const Scalar::Vector<double> &x)
{
return Scalar::double_v(std::floor(x.data() + 0.5 ) - (_realIsEvenHalf(x.data()) ? 1. : 0. ));
}
template<typename T> static Vc_ALWAYS_INLINE Scalar::Vector<T> reciprocal(const Scalar::Vector<T> &x)
{
const typename Vector<T, VectorAbi::Scalar>::EntryType one = 1; return Scalar::Vector<T>(one / x.data());
}
#ifdef isfinite
#undef isfinite
#endif
#ifdef isnan
#undef isnan
#endif
template<typename T> static Vc_ALWAYS_INLINE typename Vector<T, VectorAbi::Scalar>::Mask isfinite(const Scalar::Vector<T> &x)
{
return typename Vector<T, VectorAbi::Scalar>::Mask(
#ifdef _MSC_VER
!!_finite(x.data())
#elif defined(__INTEL_COMPILER) && __INTEL_COMPILER < 1500
::isfinite(x.data())
#else
std::isfinite(x.data())
#endif
);
}
template<typename T> Vc_ALWAYS_INLINE typename Vector<T, VectorAbi::Scalar>::Mask isinf(const Scalar::Vector<T> &x)
{
return typename Vector<T, VectorAbi::Scalar>::Mask(std::isinf(x.data()));
}
template<typename T> static Vc_ALWAYS_INLINE typename Vector<T, VectorAbi::Scalar>::Mask isnan(const Scalar::Vector<T> &x)
{
return typename Vector<T, VectorAbi::Scalar>::Mask(
#ifdef _MSC_VER
!!_isnan(x.data())
#elif defined(__INTEL_COMPILER) && __INTEL_COMPILER < 1500
::isnan(x.data())
#else
std::isnan(x.data())
#endif
);
}
Vc_ALWAYS_INLINE Scalar::Vector<float> frexp(Scalar::Vector<float> x, SimdArray<int, 1, Scalar::Vector<int>, 1> *e) {
return Scalar::float_v(std::frexp(x.data(), &internal_data(*e).data()));
}
Vc_ALWAYS_INLINE Scalar::Vector<double> frexp(Scalar::Vector<double> x, SimdArray<int, 1, Scalar::Vector<int>, 1> *e) {
return Scalar::double_v(std::frexp(x.data(), &internal_data(*e).data()));
}
Vc_ALWAYS_INLINE Scalar::Vector<float> ldexp(Scalar::Vector<float> x, const SimdArray<int, 1, Scalar::Vector<int>, 1> &e) {
return Scalar::float_v(std::ldexp(x.data(), internal_data(e).data()));
}
Vc_ALWAYS_INLINE Scalar::Vector<double> ldexp(Scalar::Vector<double> x, const SimdArray<int, 1, Scalar::Vector<int>, 1> &e) {
return Scalar::double_v(std::ldexp(x.data(), internal_data(e).data()));
}
template <typename T>
Vc_ALWAYS_INLINE Vector<T, VectorAbi::Scalar> fma(Vector<T, VectorAbi::Scalar> a,
Vector<T, VectorAbi::Scalar> b,
Vector<T, VectorAbi::Scalar> c)
{
if (std::is_integral<T>::value) {
return a * b + c;
} else {
return std::fma(a.data(), b.data(), c.data());
}
}
}
#endif
#ifndef Vc_SCALAR_SIMD_CAST_CALLER_TCC_
#define Vc_SCALAR_SIMD_CAST_CALLER_TCC_ 
namespace Vc_VERSIONED_NAMESPACE
{
#if Vc_IS_VERSION_1
template <typename T>
template <typename U>
Vc_INTRINSIC Mask<T, VectorAbi::Scalar>::Mask(
U &&rhs, Common::enable_if_mask_converts_explicitly<T, U>)
: Mask(simd_cast<Mask>(std::forward<U>(rhs)))
{
}
#endif
}
#endif
#if defined(Vc_IMPL_SSE)
#ifndef VC_SSE_DEINTERLEAVE_H_
#define VC_SSE_DEINTERLEAVE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename A>
inline void deinterleave(SSE::float_v &, SSE::float_v &, const float *, A);
template <typename A>
inline void deinterleave(SSE::float_v &, SSE::float_v &, const short *, A);
template <typename A>
inline void deinterleave(SSE::float_v &, SSE::float_v &, const ushort *, A);
template <typename A>
inline void deinterleave(SSE::double_v &, SSE::double_v &, const double *, A);
template <typename A>
inline void deinterleave(SSE::int_v &, SSE::int_v &, const int *, A);
template <typename A>
inline void deinterleave(SSE::int_v &, SSE::int_v &, const short *, A);
template <typename A>
inline void deinterleave(SSE::uint_v &, SSE::uint_v &, const uint *, A);
template <typename A>
inline void deinterleave(SSE::uint_v &, SSE::uint_v &, const ushort *, A);
template <typename A>
inline void deinterleave(SSE::short_v &, SSE::short_v &, const short *, A);
template <typename A>
inline void deinterleave(SSE::ushort_v &, SSE::ushort_v &, const ushort *, A);
Vc_ALWAYS_INLINE_L void prefetchForOneRead(const void *addr, VectorAbi::Sse) Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L void prefetchForModify(const void *addr, VectorAbi::Sse) Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L void prefetchClose(const void *addr, VectorAbi::Sse) Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L void prefetchMid(const void *addr, VectorAbi::Sse) Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE_L void prefetchFar(const void *addr, VectorAbi::Sse) Vc_ALWAYS_INLINE_R;
}
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace SSE
{
inline void deinterleave(Vector<float> &a, Vector<float> &b)
{
const _M128 tmp0 = _mm_unpacklo_ps(a.data(), b.data());
const _M128 tmp1 = _mm_unpackhi_ps(a.data(), b.data());
a.data() = _mm_unpacklo_ps(tmp0, tmp1);
b.data() = _mm_unpackhi_ps(tmp0, tmp1);
}
inline void deinterleave(Vector<float> &a, Vector<float> &b, Vector<short>::AsArg tmp)
{
a.data() = _mm_cvtepi32_ps(_mm_srai_epi32(_mm_slli_epi32(tmp.data(), 16), 16));
b.data() = _mm_cvtepi32_ps(_mm_srai_epi32(tmp.data(), 16));
}
inline void deinterleave(Vector<float> &a, Vector<float> &b, Vector<unsigned short>::AsArg tmp)
{
a.data() = _mm_cvtepi32_ps(_mm_srli_epi32(_mm_slli_epi32(tmp.data(), 16), 16));
b.data() = _mm_cvtepi32_ps(_mm_srli_epi32(tmp.data(), 16));
}
inline void deinterleave(Vector<double> &a, Vector<double> &b)
{
_M128D tmp = _mm_unpacklo_pd(a.data(), b.data());
b.data() = _mm_unpackhi_pd(a.data(), b.data());
a.data() = tmp;
}
inline void deinterleave(Vector<int> &a, Vector<int> &b)
{
const _M128I tmp0 = _mm_unpacklo_epi32(a.data(), b.data());
const _M128I tmp1 = _mm_unpackhi_epi32(a.data(), b.data());
a.data() = _mm_unpacklo_epi32(tmp0, tmp1);
b.data() = _mm_unpackhi_epi32(tmp0, tmp1);
}
inline void deinterleave(Vector<unsigned int> &a, Vector<unsigned int> &b)
{
const _M128I tmp0 = _mm_unpacklo_epi32(a.data(), b.data());
const _M128I tmp1 = _mm_unpackhi_epi32(a.data(), b.data());
a.data() = _mm_unpacklo_epi32(tmp0, tmp1);
b.data() = _mm_unpackhi_epi32(tmp0, tmp1);
}
inline void deinterleave(Vector<short> &a, Vector<short> &b)
{
_M128I tmp0 = _mm_unpacklo_epi16(a.data(), b.data());
_M128I tmp1 = _mm_unpackhi_epi16(a.data(), b.data());
_M128I tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
_M128I tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
a.data() = _mm_unpacklo_epi16(tmp2, tmp3);
b.data() = _mm_unpackhi_epi16(tmp2, tmp3);
}
inline void deinterleave(Vector<unsigned short> &a, Vector<unsigned short> &b)
{
_M128I tmp0 = _mm_unpacklo_epi16(a.data(), b.data());
_M128I tmp1 = _mm_unpackhi_epi16(a.data(), b.data());
_M128I tmp2 = _mm_unpacklo_epi16(tmp0, tmp1);
_M128I tmp3 = _mm_unpackhi_epi16(tmp0, tmp1);
a.data() = _mm_unpacklo_epi16(tmp2, tmp3);
b.data() = _mm_unpackhi_epi16(tmp2, tmp3);
}
inline void deinterleave(Vector<int> &a, Vector<int> &b, Vector<short>::AsArg tmp)
{
a.data() = _mm_srai_epi32(_mm_slli_epi32(tmp.data(), 16), 16);
b.data() = _mm_srai_epi32(tmp.data(), 16);
}
inline void deinterleave(Vector<unsigned int> &a, Vector<unsigned int> &b, Vector<unsigned short>::AsArg tmp)
{
a.data() = _mm_srli_epi32(_mm_slli_epi32(tmp.data(), 16), 16);
b.data() = _mm_srli_epi32(tmp.data(), 16);
}
}
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template<typename A> inline void deinterleave(
SSE::float_v &a, SSE::float_v &b, const float *m, A align)
{
a.load(m, align);
b.load(m + SSE::float_v::Size, align);
Vc::SSE::deinterleave(a, b);
}
template<typename A> inline void deinterleave(
SSE::float_v &a, SSE::float_v &b, const short *m, A align)
{
SSE::short_v tmp(m, align);
Vc::SSE::deinterleave(a, b, tmp);
}
template<typename A> inline void deinterleave(
SSE::float_v &a, SSE::float_v &b, const unsigned short *m, A align)
{
SSE::ushort_v tmp(m, align);
Vc::SSE::deinterleave(a, b, tmp);
}
template<typename A> inline void deinterleave(
SSE::double_v &a, SSE::double_v &b, const double *m, A align)
{
a.load(m, align);
b.load(m + SSE::double_v::Size, align);
Vc::SSE::deinterleave(a, b);
}
template<typename A> inline void deinterleave(
SSE::int_v &a, SSE::int_v &b, const int *m, A align)
{
a.load(m, align);
b.load(m + SSE::int_v::Size, align);
Vc::SSE::deinterleave(a, b);
}
template<typename A> inline void deinterleave(
SSE::int_v &a, SSE::int_v &b, const short *m, A align)
{
SSE::short_v tmp(m, align);
Vc::SSE::deinterleave(a, b, tmp);
}
template<typename A> inline void deinterleave(
SSE::uint_v &a, SSE::uint_v &b, const unsigned int *m, A align)
{
a.load(m, align);
b.load(m + SSE::uint_v::Size, align);
Vc::SSE::deinterleave(a, b);
}
template<typename A> inline void deinterleave(
SSE::uint_v &a, SSE::uint_v &b, const unsigned short *m, A align)
{
SSE::ushort_v tmp(m, align);
Vc::SSE::deinterleave(a, b, tmp);
}
template<typename A> inline void deinterleave(
SSE::short_v &a, SSE::short_v &b, const short *m, A align)
{
a.load(m, align);
b.load(m + SSE::short_v::Size, align);
Vc::SSE::deinterleave(a, b);
}
template<typename A> inline void deinterleave(
SSE::ushort_v &a, SSE::ushort_v &b, const unsigned short *m, A align)
{
a.load(m, align);
b.load(m + SSE::ushort_v::Size, align);
Vc::SSE::deinterleave(a, b);
}
}
}
#ifndef VC_SSE_PREFETCHES_TCC_
#define VC_SSE_PREFETCHES_TCC_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
Vc_ALWAYS_INLINE void prefetchForOneRead(const void *addr, VectorAbi::Sse)
{
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_NTA);
}
Vc_ALWAYS_INLINE void prefetchClose(const void *addr, VectorAbi::Sse)
{
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_T0);
}
Vc_ALWAYS_INLINE void prefetchMid(const void *addr, VectorAbi::Sse)
{
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_T1);
}
Vc_ALWAYS_INLINE void prefetchFar(const void *addr, VectorAbi::Sse)
{
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_T2);
}
Vc_ALWAYS_INLINE void prefetchForModify(const void *addr, VectorAbi::Sse)
{
#ifdef __3dNOW__
_m_prefetchw(const_cast<void *>(addr));
#else
_mm_prefetch(static_cast<char *>(const_cast<void *>(addr)), _MM_HINT_T0);
#endif
}
}
}
#endif
#endif
#ifndef VC_SSE_MATH_H_
#define VC_SSE_MATH_H_ 
#ifndef VC_SSE_CONST_H_
#define VC_SSE_CONST_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace SSE
{
template<typename T> struct Const
{
typedef Vector<T> V;
typedef Mask<T> M;
enum Constants { Stride = 16 / sizeof(T) };
static Vc_ALWAYS_INLINE Vc_CONST V _pi_4() { return load(&c_trig<T>::data[0 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_4_hi() { return load(&c_trig<T>::data[1 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_4_rem1() { return load(&c_trig<T>::data[2 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_4_rem2() { return load(&c_trig<T>::data[3 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _1_16() { return load(&c_trig<T>::data[4 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _16() { return load(&c_trig<T>::data[5 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V atanP(int i) { return load(&c_trig<T>::data[(12 + i) * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V atanQ(int i) { return load(&c_trig<T>::data[(17 + i) * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V atanThrsHi() { return load(&c_trig<T>::data[22 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V atanThrsLo() { return load(&c_trig<T>::data[23 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_2_rem() { return load(&c_trig<T>::data[24 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V lossThreshold() { return load(&c_trig<T>::data[8 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _4_pi() { return load(&c_trig<T>::data[9 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi_2() { return load(&c_trig<T>::data[10 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V _pi() { return load(&c_trig<T>::data[11 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V asinCoeff0(int i) { return load(&c_trig<T>::data[(28 + i) * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V asinCoeff1(int i) { return load(&c_trig<T>::data[(33 + i) * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V asinCoeff2(int i) { return load(&c_trig<T>::data[(37 + i) * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V asinCoeff3(int i) { return load(&c_trig<T>::data[(43 + i) * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V smallAsinInput() { return load(&c_trig<T>::data[25 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST V largeAsinInput() { return load(&c_trig<T>::data[26 * Stride]); }
static Vc_ALWAYS_INLINE Vc_CONST M exponentMask() { return M(load(c_log<T>::d(1)).data()); }
static Vc_ALWAYS_INLINE Vc_CONST V _1_2() { return load(c_log<T>::d(18)); }
static Vc_ALWAYS_INLINE Vc_CONST V _1_sqrt2() { return load(c_log<T>::d(15)); }
static Vc_ALWAYS_INLINE Vc_CONST V P(int i) { return load(c_log<T>::d(2 + i)); }
static Vc_ALWAYS_INLINE Vc_CONST V Q(int i) { return load(c_log<T>::d(8 + i)); }
static Vc_ALWAYS_INLINE Vc_CONST V min() { return load(c_log<T>::d(14)); }
static Vc_ALWAYS_INLINE Vc_CONST V ln2_small() { return load(c_log<T>::d(17)); }
static Vc_ALWAYS_INLINE Vc_CONST V ln2_large() { return load(c_log<T>::d(16)); }
static Vc_ALWAYS_INLINE Vc_CONST V neginf() { return load(c_log<T>::d(13)); }
static Vc_ALWAYS_INLINE Vc_CONST V log10_e() { return load(c_log<T>::d(19)); }
static Vc_ALWAYS_INLINE Vc_CONST V log2_e() { return load(c_log<T>::d(20)); }
static Vc_ALWAYS_INLINE_L Vc_CONST_L V highMask() Vc_ALWAYS_INLINE_R Vc_CONST_R;
static Vc_ALWAYS_INLINE_L Vc_CONST_L V highMask(int bits) Vc_ALWAYS_INLINE_R Vc_CONST_R;
private:
static Vc_ALWAYS_INLINE_L Vc_CONST_L V load(const T *mem) Vc_ALWAYS_INLINE_R Vc_CONST_R;
};
template<typename T> Vc_ALWAYS_INLINE Vc_CONST Vector<T> Const<T>::load(const T *mem) { return V(mem); }
template <> Vc_ALWAYS_INLINE Vc_CONST Vector<float> Const<float>::highMask()
{
return Vector<float>(reinterpret_cast<const float *>(&c_general::highMaskFloat));
}
template <> Vc_ALWAYS_INLINE Vc_CONST Vector<double> Const<double>::highMask()
{
return Vector<double>(
reinterpret_cast<const double *>(&c_general::highMaskDouble));
}
template <> Vc_ALWAYS_INLINE Vc_CONST Vector<float> Const<float>::highMask(int bits)
{
return _mm_castsi128_ps(_mm_slli_epi32(_mm_setallone_si128(), bits));
}
template <> Vc_ALWAYS_INLINE Vc_CONST Vector<double> Const<double>::highMask(int bits)
{
return _mm_castsi128_pd(_mm_slli_epi64(_mm_setallone_si128(), bits));
}
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
Vc_INTRINSIC Vc_CONST SSE::float_v copysign(SSE::float_v mag, SSE::float_v sign)
{
return _mm_or_ps(_mm_and_ps(sign.data(), SSE::_mm_setsignmask_ps()),
_mm_and_ps(mag.data(), SSE::_mm_setabsmask_ps()));
}
Vc_INTRINSIC Vc_CONST SSE::double_v copysign(SSE::double_v mag, SSE::double_v sign)
{
return _mm_or_pd(_mm_and_pd(sign.data(), SSE::_mm_setsignmask_pd()),
_mm_and_pd(mag.data(), SSE::_mm_setabsmask_pd()));
}
inline SSE::double_v frexp(const SSE::double_v &v,
SimdArray<int, 2, Scalar::int_v, 1> *e)
{
const __m128i exponentBits = SSE::Const<double>::exponentMask().dataI();
const __m128i exponentPart = _mm_and_si128(_mm_castpd_si128(v.data()), exponentBits);
SSE::int_v exponent =
_mm_sub_epi32(_mm_srli_epi64(exponentPart, 52), _mm_set1_epi32(0x3fe));
const __m128d exponentMaximized = _mm_or_pd(v.data(), _mm_castsi128_pd(exponentBits));
SSE::double_v ret = _mm_and_pd(
exponentMaximized,
_mm_load_pd(reinterpret_cast<const double *>(&SSE::c_general::frexpMask[0])));
SSE::double_m zeroMask = v == SSE::double_v::Zero();
ret(isnan(v) || !isfinite(v) || zeroMask) = v;
exponent.setZero(zeroMask.data());
(*e)[0] = exponent[0];
(*e)[1] = exponent[2];
return ret;
}
inline SSE::float_v frexp(const SSE::float_v &v, SimdArray<int, 4, SSE::int_v, 4> *e)
{
const __m128i exponentBits = SSE::Const<float>::exponentMask().dataI();
const __m128i exponentPart = _mm_and_si128(_mm_castps_si128(v.data()), exponentBits);
internal_data(*e) =
_mm_sub_epi32(_mm_srli_epi32(exponentPart, 23), _mm_set1_epi32(0x7e));
const __m128 exponentMaximized = _mm_or_ps(v.data(), _mm_castsi128_ps(exponentBits));
SSE::float_v ret =
_mm_and_ps(exponentMaximized, _mm_castsi128_ps(_mm_set1_epi32(0xbf7fffffu)));
ret(isnan(v) || !isfinite(v) || v == SSE::float_v::Zero()) = v;
e->setZero(v == SSE::float_v::Zero());
return ret;
}
inline SSE::double_v ldexp(SSE::double_v::AsArg v,
const SimdArray<int, 2, Scalar::int_v, 1> &_e)
{
SSE::int_v e = _mm_setr_epi32(_e[0], 0, _e[1], 0);
e.setZero((v == SSE::double_v::Zero()).dataI());
const __m128i exponentBits = _mm_slli_epi64(e.data(), 52);
return _mm_castsi128_pd(_mm_add_epi64(_mm_castpd_si128(v.data()), exponentBits));
}
inline SSE::float_v ldexp(SSE::float_v::AsArg v,
const SimdArray<int, 4, SSE::int_v, 4> &_e)
{
SSE::int_v e = internal_data(_e);
e.setZero(simd_cast<SSE::int_m>(v == SSE::float_v::Zero()));
return reinterpret_components_cast<SSE::float_v>(
reinterpret_components_cast<SSE::int_v>(v) + (e << 23));
}
#ifdef Vc_IMPL_SSE4_1
inline SSE::double_v trunc(SSE::double_v::AsArg v) { return _mm_round_pd(v.data(), 0x3); }
inline SSE::float_v trunc(SSE::float_v::AsArg v) { return _mm_round_ps(v.data(), 0x3); }
inline SSE::double_v floor(SSE::double_v::AsArg v) { return _mm_floor_pd(v.data()); }
inline SSE::float_v floor(SSE::float_v::AsArg v) { return _mm_floor_ps(v.data()); }
inline SSE::double_v ceil(SSE::double_v::AsArg v) { return _mm_ceil_pd(v.data()); }
inline SSE::float_v ceil(SSE::float_v::AsArg v) { return _mm_ceil_ps(v.data()); }
#else
inline SSE::Vector<float> trunc(SSE::Vector<float> x)
{
const auto truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(x.data()));
const auto no_fractional_values = _mm_castsi128_ps(_mm_cmplt_epi32(
_mm_and_si128(_mm_castps_si128(x.data()), _mm_set1_epi32(0x7f800000u)),
_mm_set1_epi32(0x4b000000)));
return _mm_or_ps(_mm_andnot_ps(no_fractional_values, x.data()),
_mm_and_ps(no_fractional_values, truncated));
}
inline SSE::Vector<double> trunc(SSE::Vector<double> x)
{
const auto abs_x = Vc::abs(x).data();
const auto min_no_fractional_bits =
_mm_castsi128_pd(_mm_set1_epi64x(0x4330000000000000ull));
__m128d truncated =
_mm_sub_pd(_mm_add_pd(abs_x, min_no_fractional_bits), min_no_fractional_bits);
truncated = _mm_sub_pd(truncated,
_mm_and_pd(_mm_cmplt_pd(abs_x, truncated), _mm_set1_pd(1.)));
return _mm_or_pd(
_mm_and_pd(_mm_castsi128_pd(_mm_set1_epi64x(0x8000000000000000ull)), x.data()),
truncated);
}
template <typename T> inline SSE::Vector<T> floor(SSE::Vector<T> x)
{
auto y = trunc(x);
y(!(y == x) && x < 0) -= 1;
return y;
}
template <typename T> inline SSE::Vector<T> ceil(SSE::Vector<T> x)
{
auto y = trunc(x);
y(!(y == x || x < 0)) += 1;
return y;
}
#endif
template <typename T>
Vc_ALWAYS_INLINE Vector<T, VectorAbi::Sse> fma(Vector<T, VectorAbi::Sse> a,
Vector<T, VectorAbi::Sse> b,
Vector<T, VectorAbi::Sse> c)
{
SSE::VectorHelper<T>::fma(a.data(), b.data(), c.data());
return a;
}
}
#endif
#ifndef Vc_SSE_SIMD_CAST_CALLER_TCC_
#define Vc_SSE_SIMD_CAST_CALLER_TCC_ 
namespace Vc_VERSIONED_NAMESPACE
{
#if Vc_IS_VERSION_1
template <typename T>
template <typename U>
Vc_INTRINSIC Mask<T, VectorAbi::Sse>::Mask(U &&rhs, Common::enable_if_mask_converts_explicitly<T, U>)
: Mask(Vc::simd_cast<Mask>(std::forward<U>(rhs)))
{
}
#endif
}
#endif
#endif
#if defined(Vc_IMPL_AVX)
#ifndef VC_AVX_HELPERIMPL_H_
#define VC_AVX_HELPERIMPL_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <typename A>
inline void deinterleave(AVX2::float_v &, AVX2::float_v &, const float *, A);
template <typename A>
inline void deinterleave(AVX2::float_v &, AVX2::float_v &, const short *, A);
template <typename A>
inline void deinterleave(AVX2::float_v &, AVX2::float_v &, const ushort *, A);
template <typename A>
inline void deinterleave(AVX2::double_v &, AVX2::double_v &, const double *, A);
template <typename A>
inline void deinterleave(AVX2::int_v &, AVX2::int_v &, const int *, A);
template <typename A>
inline void deinterleave(AVX2::int_v &, AVX2::int_v &, const short *, A);
template <typename A>
inline void deinterleave(AVX2::uint_v &, AVX2::uint_v &, const uint *, A);
template <typename A>
inline void deinterleave(AVX2::uint_v &, AVX2::uint_v &, const ushort *, A);
template <typename A>
inline void deinterleave(AVX2::short_v &, AVX2::short_v &, const short *, A);
template <typename A>
inline void deinterleave(AVX2::ushort_v &, AVX2::ushort_v &, const ushort *, A);
template <typename T, typename M, typename A>
Vc_ALWAYS_INLINE_L void deinterleave(AVX2::Vector<T> &Vc_RESTRICT a,
AVX2::Vector<T> &Vc_RESTRICT b,
AVX2::Vector<T> &Vc_RESTRICT c,
const M *Vc_RESTRICT memory,
A align) Vc_ALWAYS_INLINE_R;
template <typename T, typename M, typename A>
Vc_ALWAYS_INLINE_L void deinterleave(AVX2::Vector<T> &Vc_RESTRICT a,
AVX2::Vector<T> &Vc_RESTRICT b,
AVX2::Vector<T> &Vc_RESTRICT c,
AVX2::Vector<T> &Vc_RESTRICT d,
const M *Vc_RESTRICT memory,
A align) Vc_ALWAYS_INLINE_R;
template <typename T, typename M, typename A>
Vc_ALWAYS_INLINE_L void deinterleave(AVX2::Vector<T> &Vc_RESTRICT a,
AVX2::Vector<T> &Vc_RESTRICT b,
AVX2::Vector<T> &Vc_RESTRICT c,
AVX2::Vector<T> &Vc_RESTRICT d,
AVX2::Vector<T> &Vc_RESTRICT e,
const M *Vc_RESTRICT memory,
A align) Vc_ALWAYS_INLINE_R;
template <typename T, typename M, typename A>
Vc_ALWAYS_INLINE_L void deinterleave(
AVX2::Vector<T> &Vc_RESTRICT a, AVX2::Vector<T> &Vc_RESTRICT b,
AVX2::Vector<T> &Vc_RESTRICT c, AVX2::Vector<T> &Vc_RESTRICT d,
AVX2::Vector<T> &Vc_RESTRICT e, AVX2::Vector<T> &Vc_RESTRICT f,
const M *Vc_RESTRICT memory, A align) Vc_ALWAYS_INLINE_R;
template <typename T, typename M, typename A>
Vc_ALWAYS_INLINE_L void deinterleave(
AVX2::Vector<T> &Vc_RESTRICT a, AVX2::Vector<T> &Vc_RESTRICT b,
AVX2::Vector<T> &Vc_RESTRICT c, AVX2::Vector<T> &Vc_RESTRICT d,
AVX2::Vector<T> &Vc_RESTRICT e, AVX2::Vector<T> &Vc_RESTRICT f,
AVX2::Vector<T> &Vc_RESTRICT g, AVX2::Vector<T> &Vc_RESTRICT h,
const M *Vc_RESTRICT memory, A align) Vc_ALWAYS_INLINE_R;
Vc_ALWAYS_INLINE void prefetchForOneRead(const void *addr, VectorAbi::Avx)
{
prefetchForOneRead(addr, VectorAbi::Sse());
}
Vc_ALWAYS_INLINE void prefetchForModify(const void *addr, VectorAbi::Avx)
{
prefetchForModify(addr, VectorAbi::Sse());
}
Vc_ALWAYS_INLINE void prefetchClose(const void *addr, VectorAbi::Avx)
{
prefetchClose(addr, VectorAbi::Sse());
}
Vc_ALWAYS_INLINE void prefetchMid(const void *addr, VectorAbi::Avx)
{
prefetchMid(addr, VectorAbi::Sse());
}
Vc_ALWAYS_INLINE void prefetchFar(const void *addr, VectorAbi::Avx)
{
prefetchFar(addr, VectorAbi::Sse());
}
}
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace AVX2
{
inline void deinterleave(double_v &Vc_RESTRICT a, double_v &Vc_RESTRICT b, double_v &Vc_RESTRICT c)
{
const m256d tmp0 = Mem::shuffle128<X0, Y1>(a.data(), b.data());
const m256d tmp1 = Mem::shuffle128<X1, Y0>(a.data(), c.data());
const m256d tmp2 = Mem::shuffle128<X0, Y1>(b.data(), c.data());
a.data() = Mem::shuffle<X0, Y1, X2, Y3>(tmp0, tmp1);
b.data() = Mem::shuffle<X1, Y0, X3, Y2>(tmp0, tmp2);
c.data() = Mem::shuffle<X0, Y1, X2, Y3>(tmp1, tmp2);
}
inline void deinterleave(float_v &Vc_RESTRICT a, float_v &Vc_RESTRICT b, float_v &Vc_RESTRICT c)
{
const m256 ac0 = Mem::shuffle128<X0, Y0>(a.data(), c.data());
const m256 ac1 = Mem::shuffle128<X1, Y1>(a.data(), c.data());
m256 tmp0 = Mem::blend<X0, Y1, X2, X3, Y4, X5, X6, Y7>( ac0, b.data());
tmp0 = Mem::blend<X0, X1, Y2, X3, X4, Y5, X6, X7>(tmp0, ac1);
m256 tmp1 = Mem::blend<X0, X1, Y2, X3, X4, Y5, X6, X7>( ac0, b.data());
tmp1 = Mem::blend<Y0, X1, X2, Y3, X4, X5, Y6, X7>(tmp1, ac1);
m256 tmp2 = Mem::blend<Y0, X1, X2, Y3, X4, X5, Y6, X7>( ac0, b.data());
tmp2 = Mem::blend<X0, Y1, X2, X3, Y4, X5, X6, Y7>(tmp2, ac1);
a.data() = Mem::permute<X0, X3, X2, X1>(tmp0);
b.data() = Mem::permute<X1, X0, X3, X2>(tmp1);
c.data() = Mem::permute<X2, X1, X0, X3>(tmp2);
}
inline void deinterleave(int_v &Vc_RESTRICT a, int_v &Vc_RESTRICT b, int_v &Vc_RESTRICT c)
{
deinterleave(reinterpret_cast<float_v &>(a), reinterpret_cast<float_v &>(b),
reinterpret_cast<float_v &>(c));
}
inline void deinterleave(uint_v &Vc_RESTRICT a, uint_v &Vc_RESTRICT b, uint_v &Vc_RESTRICT c)
{
deinterleave(reinterpret_cast<float_v &>(a), reinterpret_cast<float_v &>(b),
reinterpret_cast<float_v &>(c));
}
inline void deinterleave(Vector<short> &Vc_RESTRICT , Vector<short> &Vc_RESTRICT ,
Vector<short> &Vc_RESTRICT )
{
return;
}
inline void deinterleave(Vector<unsigned short> &Vc_RESTRICT a, Vector<unsigned short> &Vc_RESTRICT b,
Vector<unsigned short> &Vc_RESTRICT c)
{
deinterleave(reinterpret_cast<Vector<short> &>(a), reinterpret_cast<Vector<short> &>(b),
reinterpret_cast<Vector<short> &>(c));
}
inline void deinterleave(Vector<float> &a, Vector<float> &b)
{
const m256 tmp0 = Reg::permute128<Y0, X0>(a.data(), b.data());
const m256 tmp1 = Reg::permute128<Y1, X1>(a.data(), b.data());
const m256 tmp2 = _mm256_unpacklo_ps(tmp0, tmp1);
const m256 tmp3 = _mm256_unpackhi_ps(tmp0, tmp1);
a.data() = _mm256_unpacklo_ps(tmp2, tmp3);
b.data() = _mm256_unpackhi_ps(tmp2, tmp3);
}
inline void deinterleave(Vector<short> &a,
Vector<short> &b)
{
auto v0 = Mem::shuffle128<X0, Y0>(a.data(), b.data());
auto v1 = Mem::shuffle128<X1, Y1>(a.data(), b.data());
auto v2 = AVX::unpacklo_epi16(v0, v1);
auto v3 = AVX::unpackhi_epi16(v0, v1);
v0 = AVX::unpacklo_epi16(v2, v3);
v1 = AVX::unpackhi_epi16(v2, v3);
a.data() = AVX::unpacklo_epi16(v0, v1);
b.data() = AVX::unpackhi_epi16(v0, v1);
}
inline void deinterleave(Vector<ushort> &a, Vector<ushort> &b)
{
auto v0 = Mem::shuffle128<X0, Y0>(a.data(), b.data());
auto v1 = Mem::shuffle128<X1, Y1>(a.data(), b.data());
auto v2 = AVX::unpacklo_epi16(v0, v1);
auto v3 = AVX::unpackhi_epi16(v0, v1);
v0 = AVX::unpacklo_epi16(v2, v3);
v1 = AVX::unpackhi_epi16(v2, v3);
a.data() = AVX::unpacklo_epi16(v0, v1);
b.data() = AVX::unpackhi_epi16(v0, v1);
}
}
namespace Detail
{
template <typename Flags>
inline void deinterleave(AVX2::float_v &a, AVX2::float_v &b, const float *m, Flags align)
{
a.load(m, align);
b.load(m + AVX2::float_v::Size, align);
Vc::AVX2::deinterleave(a, b);
}
template <typename Flags>
inline void deinterleave(AVX2::float_v &a, AVX2::float_v &b, const short *m, Flags f)
{
using namespace Vc::AVX2;
const auto tmp = Detail::load32(m, f);
a.data() =
_mm256_cvtepi32_ps(concat(_mm_srai_epi32(_mm_slli_epi32(lo128(tmp), 16), 16),
_mm_srai_epi32(_mm_slli_epi32(hi128(tmp), 16), 16)));
b.data() = _mm256_cvtepi32_ps(
concat(_mm_srai_epi32(lo128(tmp), 16), _mm_srai_epi32(hi128(tmp), 16)));
}
template <typename Flags>
inline void deinterleave(AVX2::float_v &a, AVX2::float_v &b, const unsigned short *m, Flags f)
{
using namespace Vc::AVX2;
const auto tmp = Detail::load32(m, f);
a.data() = _mm256_cvtepi32_ps(
concat(_mm_blend_epi16(lo128(tmp), _mm_setzero_si128(), 0xaa),
_mm_blend_epi16(hi128(tmp), _mm_setzero_si128(), 0xaa)));
b.data() = _mm256_cvtepi32_ps(
concat(_mm_srli_epi32(lo128(tmp), 16), _mm_srli_epi32(hi128(tmp), 16)));
}
template <typename Flags>
inline void deinterleave(AVX2::double_v &a, AVX2::double_v &b, const double *m, Flags align)
{
using namespace Vc::AVX2;
a.load(m, align);
b.load(m + AVX2::double_v::Size, align);
m256d tmp0 = Mem::shuffle128<Vc::X0, Vc::Y0>(a.data(), b.data());
m256d tmp1 = Mem::shuffle128<Vc::X1, Vc::Y1>(a.data(), b.data());
a.data() = _mm256_unpacklo_pd(tmp0, tmp1);
b.data() = _mm256_unpackhi_pd(tmp0, tmp1);
}
template <typename Flags>
inline void deinterleave(AVX2::int_v &a, AVX2::int_v &b, const int *m, Flags align)
{
using namespace AVX;
a.load(m, align);
b.load(m + AVX2::int_v::Size, align);
const m256 tmp0 = avx_cast<m256>(Mem::shuffle128<Vc::X0, Vc::Y0>(a.data(), b.data()));
const m256 tmp1 = avx_cast<m256>(Mem::shuffle128<Vc::X1, Vc::Y1>(a.data(), b.data()));
const m256 tmp2 = _mm256_unpacklo_ps(tmp0, tmp1);
const m256 tmp3 = _mm256_unpackhi_ps(tmp0, tmp1);
a.data() = avx_cast<m256i>(_mm256_unpacklo_ps(tmp2, tmp3));
b.data() = avx_cast<m256i>(_mm256_unpackhi_ps(tmp2, tmp3));
}
template <typename Flags>
inline void deinterleave(AVX2::int_v &a, AVX2::int_v &b, const short *m, Flags f)
{
using namespace Vc::AVX;
const AVX2::short_v tmp0(m, f);
const m256i tmp = tmp0.data();
a.data() = concat(
_mm_srai_epi32(_mm_slli_epi32(lo128(tmp), 16), 16),
_mm_srai_epi32(_mm_slli_epi32(hi128(tmp), 16), 16));
b.data() = concat(
_mm_srai_epi32(lo128(tmp), 16),
_mm_srai_epi32(hi128(tmp), 16));
}
template <typename Flags>
inline void deinterleave(AVX2::uint_v &a, AVX2::uint_v &b, const unsigned int *m, Flags align)
{
using namespace AVX;
a.load(m, align);
b.load(m + AVX2::uint_v::Size, align);
const m256 tmp0 = avx_cast<m256>(Mem::shuffle128<Vc::X0, Vc::Y0>(a.data(), b.data()));
const m256 tmp1 = avx_cast<m256>(Mem::shuffle128<Vc::X1, Vc::Y1>(a.data(), b.data()));
const m256 tmp2 = _mm256_unpacklo_ps(tmp0, tmp1);
const m256 tmp3 = _mm256_unpackhi_ps(tmp0, tmp1);
a.data() = avx_cast<m256i>(_mm256_unpacklo_ps(tmp2, tmp3));
b.data() = avx_cast<m256i>(_mm256_unpackhi_ps(tmp2, tmp3));
}
template <typename Flags>
inline void deinterleave(AVX2::uint_v &a, AVX2::uint_v &b, const unsigned short *m, Flags f)
{
using namespace Vc::AVX;
const AVX2::ushort_v tmp0(m, f);
const m256i tmp = tmp0.data();
a.data() = concat(
_mm_srai_epi32(_mm_slli_epi32(lo128(tmp), 16), 16),
_mm_srai_epi32(_mm_slli_epi32(hi128(tmp), 16), 16));
b.data() = concat(
_mm_srai_epi32(lo128(tmp), 16),
_mm_srai_epi32(hi128(tmp), 16));
}
template <typename Flags>
inline void deinterleave(AVX2::short_v &a, AVX2::short_v &b, const short *m, Flags align)
{
a.load(m, align);
b.load(m + AVX2::short_v::Size, align);
Vc::AVX2::deinterleave(a, b);
}
template <typename Flags>
inline void deinterleave(AVX2::ushort_v &a, AVX2::ushort_v &b, const unsigned short *m, Flags align)
{
a.load(m, align);
b.load(m + AVX2::ushort_v::Size, align);
Vc::AVX2::deinterleave(a, b);
}
template <typename T, typename M, typename Flags>
Vc_ALWAYS_INLINE void deinterleave(AVX2::Vector<T> &Vc_RESTRICT a,
AVX2::Vector<T> &Vc_RESTRICT b,
AVX2::Vector<T> &Vc_RESTRICT c,
const M *Vc_RESTRICT memory, Flags align)
{
using V = AVX2::Vector<T>;
a.load(&memory[0 * V::Size], align);
b.load(&memory[1 * V::Size], align);
c.load(&memory[2 * V::Size], align);
Vc::AVX2::deinterleave(a, b, c);
}
}
}
#endif
#ifndef VC_AVX_MATH_H_
#define VC_AVX_MATH_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
#ifdef Vc_IMPL_AVX2
Vc_ALWAYS_INLINE AVX2::int_v min(const AVX2::int_v &x, const AVX2::int_v &y) { return _mm256_min_epi32(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::uint_v min(const AVX2::uint_v &x, const AVX2::uint_v &y) { return _mm256_min_epu32(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::short_v min(const AVX2::short_v &x, const AVX2::short_v &y) { return _mm256_min_epi16(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::ushort_v min(const AVX2::ushort_v &x, const AVX2::ushort_v &y) { return _mm256_min_epu16(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::int_v max(const AVX2::int_v &x, const AVX2::int_v &y) { return _mm256_max_epi32(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::uint_v max(const AVX2::uint_v &x, const AVX2::uint_v &y) { return _mm256_max_epu32(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::short_v max(const AVX2::short_v &x, const AVX2::short_v &y) { return _mm256_max_epi16(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::ushort_v max(const AVX2::ushort_v &x, const AVX2::ushort_v &y) { return _mm256_max_epu16(x.data(), y.data()); }
#endif
Vc_ALWAYS_INLINE AVX2::float_v min(const AVX2::float_v &x, const AVX2::float_v &y) { return _mm256_min_ps(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::double_v min(const AVX2::double_v &x, const AVX2::double_v &y) { return _mm256_min_pd(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::float_v max(const AVX2::float_v &x, const AVX2::float_v &y) { return _mm256_max_ps(x.data(), y.data()); }
Vc_ALWAYS_INLINE AVX2::double_v max(const AVX2::double_v &x, const AVX2::double_v &y) { return _mm256_max_pd(x.data(), y.data()); }
template <typename T>
Vc_ALWAYS_INLINE Vc_PURE AVX2::Vector<T> sqrt(const AVX2::Vector<T> &x)
{
return AVX::VectorHelper<T>::sqrt(x.data());
}
template <typename T>
Vc_ALWAYS_INLINE Vc_PURE AVX2::Vector<T> rsqrt(const AVX2::Vector<T> &x)
{
return AVX::VectorHelper<T>::rsqrt(x.data());
}
template <typename T>
Vc_ALWAYS_INLINE Vc_PURE AVX2::Vector<T> reciprocal(const AVX2::Vector<T> &x)
{
return AVX::VectorHelper<T>::reciprocal(x.data());
}
template <typename T>
Vc_ALWAYS_INLINE Vc_PURE AVX2::Vector<T> round(const AVX2::Vector<T> &x)
{
return AVX::VectorHelper<T>::round(x.data());
}
Vc_INTRINSIC Vc_CONST AVX2::double_v abs(AVX2::double_v x)
{
return Detail::and_(x.data(), AVX::setabsmask_pd());
}
Vc_INTRINSIC Vc_CONST AVX2::float_v abs(AVX2::float_v x)
{
return Detail::and_(x.data(), AVX::setabsmask_ps());
}
#ifdef Vc_IMPL_AVX2
Vc_INTRINSIC Vc_CONST AVX2::int_v abs(AVX2::int_v x)
{
return _mm256_abs_epi32(x.data());
}
Vc_INTRINSIC Vc_CONST AVX2::short_v abs(AVX2::short_v x)
{
return _mm256_abs_epi16(x.data());
}
#endif
Vc_ALWAYS_INLINE Vc_PURE AVX2::double_m isfinite(const AVX2::double_v &x)
{
return AVX::cmpord_pd(x.data(), _mm256_mul_pd(Detail::zero<__m256d>(), x.data()));
}
Vc_ALWAYS_INLINE Vc_PURE AVX2::float_m isfinite(const AVX2::float_v &x)
{
return AVX::cmpord_ps(x.data(), _mm256_mul_ps(Detail::zero<__m256>(), x.data()));
}
Vc_ALWAYS_INLINE Vc_PURE AVX2::double_m isinf(const AVX2::double_v &x)
{
return _mm256_castsi256_pd(AVX::cmpeq_epi64(
_mm256_castpd_si256(abs(x).data()),
_mm256_castpd_si256(Detail::avx_broadcast(AVX::c_log<double>::d(1)))));
}
Vc_ALWAYS_INLINE Vc_PURE AVX2::float_m isinf(const AVX2::float_v &x)
{
return _mm256_castsi256_ps(
AVX::cmpeq_epi32(_mm256_castps_si256(abs(x).data()),
_mm256_castps_si256(Detail::avx_broadcast(AVX::c_log<float>::d(1)))));
}
Vc_ALWAYS_INLINE Vc_PURE AVX2::double_m isnan(const AVX2::double_v &x)
{
return AVX::cmpunord_pd(x.data(), x.data());
}
Vc_ALWAYS_INLINE Vc_PURE AVX2::float_m isnan(const AVX2::float_v &x)
{
return AVX::cmpunord_ps(x.data(), x.data());
}
Vc_INTRINSIC Vc_CONST AVX2::float_v copysign(AVX2::float_v mag, AVX2::float_v sign)
{
return _mm256_or_ps(_mm256_and_ps(sign.data(), AVX::setsignmask_ps()),
_mm256_and_ps(mag.data(), AVX::setabsmask_ps()));
}
Vc_INTRINSIC Vc_CONST AVX2::double_v copysign(AVX2::double_v::AsArg mag,
AVX2::double_v::AsArg sign)
{
return _mm256_or_pd(_mm256_and_pd(sign.data(), AVX::setsignmask_pd()),
_mm256_and_pd(mag.data(), AVX::setabsmask_pd()));
}
inline AVX2::double_v frexp(AVX2::double_v::AsArg v, SimdArray<int, 4, SSE::int_v, 4> *e)
{
const __m256d exponentBits = AVX::Const<double>::exponentMask().dataD();
const __m256d exponentPart = _mm256_and_pd(v.data(), exponentBits);
auto lo = AVX::avx_cast<__m128i>(AVX::lo128(exponentPart));
auto hi = AVX::avx_cast<__m128i>(AVX::hi128(exponentPart));
lo = _mm_sub_epi32(_mm_srli_epi64(lo, 52), _mm_set1_epi64x(0x3fe));
hi = _mm_sub_epi32(_mm_srli_epi64(hi, 52), _mm_set1_epi64x(0x3fe));
SSE::int_v exponent = Mem::shuffle<X0, X2, Y0, Y2>(lo, hi);
const __m256d exponentMaximized = _mm256_or_pd(v.data(), exponentBits);
AVX2::double_v ret =
_mm256_and_pd(exponentMaximized,
_mm256_broadcast_sd(reinterpret_cast<const double *>(&AVX::c_general::frexpMask)));
const double_m zeroMask = v == AVX2::double_v::Zero();
ret(isnan(v) || !isfinite(v) || zeroMask) = v;
exponent.setZero(simd_cast<SSE::int_m>(zeroMask));
internal_data(*e) = exponent;
return ret;
}
#ifdef Vc_IMPL_AVX2
inline SimdArray<double, 8, AVX2::double_v, 4> frexp(
const SimdArray<double, 8, AVX2::double_v, 4> &v,
SimdArray<int, 8, AVX2::int_v, 8> *e)
{
const __m256d exponentBits = AVX::Const<double>::exponentMask().dataD();
const __m256d w[2] = {internal_data(internal_data0(v)).data(),
internal_data(internal_data1(v)).data()};
const __m256i exponentPart[2] = {
_mm256_castpd_si256(_mm256_and_pd(w[0], exponentBits)),
_mm256_castpd_si256(_mm256_and_pd(w[1], exponentBits))};
const __m256i lo = _mm256_sub_epi32(_mm256_srli_epi64(exponentPart[0], 52),
_mm256_set1_epi32(0x3fe));
const __m256i hi = _mm256_sub_epi32(_mm256_srli_epi64(exponentPart[1], 52),
_mm256_set1_epi32(0x3fe));
const __m256i a = _mm256_unpacklo_epi32(lo, hi);
const __m256i b = _mm256_unpackhi_epi32(lo, hi);
const __m256i tmp = _mm256_unpacklo_epi32(a, b);
const __m256i exponent =
AVX::concat(_mm_unpacklo_epi64(AVX::lo128(tmp), AVX::hi128(tmp)),
_mm_unpackhi_epi64(AVX::lo128(tmp), AVX::hi128(tmp)));
const __m256d exponentMaximized[2] = {_mm256_or_pd(w[0], exponentBits),
_mm256_or_pd(w[1], exponentBits)};
const auto frexpMask =
_mm256_broadcast_sd(reinterpret_cast<const double *>(&AVX::c_general::frexpMask));
SimdArray<double, 8, AVX2::double_v, 4> ret = {
SimdArray<double, 4, AVX2::double_v, 4>(
_mm256_and_pd(exponentMaximized[0], frexpMask)),
SimdArray<double, 4, AVX2::double_v, 4>(
_mm256_and_pd(exponentMaximized[1], frexpMask))};
const auto zeroMask = v == v.Zero();
ret(isnan(v) || !isfinite(v) || zeroMask) = v;
internal_data(*e) =
Detail::andnot_(simd_cast<AVX2::int_m>(zeroMask).dataI(), exponent);
return ret;
}
#endif
namespace Detail
{
Vc_INTRINSIC AVX2::float_v::IndexType extractExponent(__m256 e)
{
SimdArray<uint, float_v::Size> exponentPart;
const auto ee = AVX::avx_cast<__m256i>(e);
#ifdef Vc_IMPL_AVX2
exponentPart = AVX2::uint_v(ee);
#else
internal_data(internal_data0(exponentPart)) = AVX::lo128(ee);
internal_data(internal_data1(exponentPart)) = AVX::hi128(ee);
#endif
return (exponentPart >> 23) - 0x7e;
}
}
inline AVX2::float_v frexp(AVX2::float_v::AsArg v, AVX2::float_v::IndexType *e)
{
using namespace Detail;
using namespace AVX2;
const __m256 exponentBits = Const<float>::exponentMask().data();
*e = extractExponent(and_(v.data(), exponentBits));
const __m256 exponentMaximized = or_(v.data(), exponentBits);
AVX2::float_v ret = _mm256_and_ps(exponentMaximized, avx_cast<__m256>(set1_epi32(0xbf7fffffu)));
ret(isnan(v) || !isfinite(v) || v == AVX2::float_v::Zero()) = v;
e->setZero(simd_cast<decltype(*e == *e)>(v == AVX2::float_v::Zero()));
return ret;
}
inline AVX2::double_v ldexp(AVX2::double_v::AsArg v,
const SimdArray<int, 4, SSE::int_v, 4> &_e)
{
SSE::int_v e = internal_data(_e);
e.setZero(simd_cast<SSE::int_m>(v == AVX2::double_v::Zero()));
const __m256i exponentBits =
AVX::concat(_mm_slli_epi64(_mm_unpacklo_epi32(e.data(), e.data()), 52),
_mm_slli_epi64(_mm_unpackhi_epi32(e.data(), e.data()), 52));
return AVX::avx_cast<__m256d>(
AVX::add_epi64(AVX::avx_cast<__m256i>(v.data()), exponentBits));
}
inline AVX2::float_v ldexp(AVX2::float_v::AsArg v, SimdArray<int, 8, SSE::int_v, 4> e)
{
e.setZero(simd_cast<decltype(e == e)>(v == AVX2::float_v::Zero()));
e <<= 23;
return {AVX::avx_cast<__m256>(
AVX::concat(_mm_add_epi32(AVX::avx_cast<__m128i>(AVX::lo128(v.data())),
internal_data(internal_data0(e)).data()),
_mm_add_epi32(AVX::avx_cast<__m128i>(AVX::hi128(v.data())),
internal_data(internal_data1(e)).data())))};
}
Vc_ALWAYS_INLINE AVX2::float_v trunc(AVX2::float_v::AsArg v)
{
return _mm256_round_ps(v.data(), 0x3);
}
Vc_ALWAYS_INLINE AVX2::double_v trunc(AVX2::double_v::AsArg v)
{
return _mm256_round_pd(v.data(), 0x3);
}
Vc_ALWAYS_INLINE AVX2::float_v floor(AVX2::float_v::AsArg v)
{
return _mm256_floor_ps(v.data());
}
Vc_ALWAYS_INLINE AVX2::double_v floor(AVX2::double_v::AsArg v)
{
return _mm256_floor_pd(v.data());
}
Vc_ALWAYS_INLINE AVX2::float_v ceil(AVX2::float_v::AsArg v)
{
return _mm256_ceil_ps(v.data());
}
Vc_ALWAYS_INLINE AVX2::double_v ceil(AVX2::double_v::AsArg v)
{
return _mm256_ceil_pd(v.data());
}
template <typename T>
Vc_ALWAYS_INLINE Vector<T, VectorAbi::Avx> fma(Vector<T, VectorAbi::Avx> a,
Vector<T, VectorAbi::Avx> b,
Vector<T, VectorAbi::Avx> c)
{
return Detail::fma(a.data(), b.data(), c.data(), T());
}
}
#endif
#ifndef Vc_AVX_SIMD_CAST_CALLER_TCC_
#define Vc_AVX_SIMD_CAST_CALLER_TCC_ 
namespace Vc_VERSIONED_NAMESPACE
{
#if Vc_IS_VERSION_1
template <typename T>
template <typename U, typename>
Vc_INTRINSIC Vector<T, VectorAbi::Avx>::Vector(U &&x)
: d(simd_cast<Vector>(std::forward<U>(x)).data())
{
}
template <typename T>
template <typename U>
Vc_INTRINSIC Mask<T, VectorAbi::Avx>::Mask(U &&rhs,
Common::enable_if_mask_converts_explicitly<T, U>)
: Mask(simd_cast<Mask>(std::forward<U>(rhs)))
{
}
#endif
}
#endif
#endif
#ifndef VC_COMMON_MATH_H_
#define VC_COMMON_MATH_H_ 
#define Vc_COMMON_MATH_H_INTERNAL 1
#ifndef VC_COMMON_TRIGONOMETRIC_H_
#define VC_COMMON_TRIGONOMETRIC_H_ 
#ifdef Vc_HAVE_LIBMVEC
extern "C" {
__m128 _ZGVbN4v_sinf(__m128);
__m128d _ZGVbN2v_sin(__m128d);
__m128 _ZGVbN4v_cosf(__m128);
__m128d _ZGVbN2v_cos(__m128d);
__m256 _ZGVdN8v_sinf(__m256);
__m256d _ZGVdN4v_sin(__m256d);
__m256 _ZGVdN8v_cosf(__m256);
__m256d _ZGVdN4v_cos(__m256d);
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template<Vc::Implementation Impl> struct MapImpl { enum Dummy { Value = Impl }; };
template<> struct MapImpl<Vc::SSE42Impl> { enum Dummy { Value = MapImpl<Vc::SSE41Impl>::Value }; };
template<Vc::Implementation Impl> using TrigonometricImplementation =
ImplementationT<MapImpl<Impl>::Value
#if defined(Vc_IMPL_XOP) && defined(Vc_IMPL_FMA4)
+ Vc::XopInstructions
+ Vc::Fma4Instructions
#endif
>;
}
namespace Common
{
template<typename Impl> struct Trigonometric
{
template<typename T> static T sin(const T &_x);
template<typename T> static T cos(const T &_x);
template<typename T> static void sincos(const T &_x, T *_sin, T *_cos);
template<typename T> static T asin (const T &_x);
template<typename T> static T atan (const T &_x);
template<typename T> static T atan2(const T &y, const T &x);
};
}
#if defined Vc_IMPL_SSE || defined DOXYGEN
namespace Detail
{
template <typename T, typename Abi>
using Trig = Common::Trigonometric<Detail::TrigonometricImplementation<
(std::is_same<Abi, VectorAbi::Sse>::value
? SSE42Impl
: std::is_same<Abi, VectorAbi::Avx>::value ? AVXImpl : ScalarImpl)>>;
}
#ifdef Vc_HAVE_LIBMVEC
Vc_INTRINSIC __m128 sin_dispatch(__m128 x) { return ::_ZGVbN4v_sinf(x); }
Vc_INTRINSIC __m128d sin_dispatch(__m128d x) { return ::_ZGVbN2v_sin (x); }
Vc_INTRINSIC __m128 cos_dispatch(__m128 x) { return ::_ZGVbN4v_cosf(x); }
Vc_INTRINSIC __m128d cos_dispatch(__m128d x) { return ::_ZGVbN2v_cos (x); }
#ifdef Vc_IMPL_AVX
Vc_INTRINSIC __m256 sin_dispatch(__m256 x) { return ::_ZGVdN8v_sinf(x); }
Vc_INTRINSIC __m256d sin_dispatch(__m256d x) { return ::_ZGVdN4v_sin (x); }
Vc_INTRINSIC __m256 cos_dispatch(__m256 x) { return ::_ZGVdN8v_cosf(x); }
Vc_INTRINSIC __m256d cos_dispatch(__m256d x) { return ::_ZGVdN4v_cos (x); }
#endif
template <typename T, typename Abi>
Vc_INTRINSIC Vector<T, detail::not_fixed_size_abi<Abi>> sin(const Vector<T, Abi> &x)
{
return sin_dispatch(x.data());
}
template <typename T, typename Abi>
Vc_INTRINSIC Vector<T, detail::not_fixed_size_abi<Abi>> cos(const Vector<T, Abi> &x)
{
return cos_dispatch(x.data());
}
#else
template <typename T, typename Abi>
Vc_INTRINSIC Vector<T, detail::not_fixed_size_abi<Abi>> sin(const Vector<T, Abi> &x)
{
return Detail::Trig<T, Abi>::sin(x);
}
template <typename T, typename Abi>
Vc_INTRINSIC Vector<T, detail::not_fixed_size_abi<Abi>> cos(const Vector<T, Abi> &x)
{
return Detail::Trig<T, Abi>::cos(x);
}
#endif
template <typename T, typename Abi>
Vc_INTRINSIC Vector<T, detail::not_fixed_size_abi<Abi>> asin(const Vector<T, Abi> &x)
{
return Detail::Trig<T, Abi>::asin(x);
}
template <typename T, typename Abi>
Vc_INTRINSIC Vector<T, detail::not_fixed_size_abi<Abi>> atan(const Vector<T, Abi> &x)
{
return Detail::Trig<T, Abi>::atan(x);
}
template <typename T, typename Abi>
Vc_INTRINSIC Vector<T, detail::not_fixed_size_abi<Abi>> atan2(const Vector<T, Abi> &y,
const Vector<T, Abi> &x)
{
return Detail::Trig<T, Abi>::atan2(y, x);
}
template <typename T, typename Abi>
Vc_INTRINSIC void sincos(const Vector<T, Abi> &x,
Vector<T, detail::not_fixed_size_abi<Abi>> *sin,
Vector<T, Abi> *cos)
{
Detail::Trig<T, Abi>::sincos(x, sin, cos);
}
#endif
}
#endif
#ifndef VC_COMMON_CONST_H_
#define VC_COMMON_CONST_H_ 
#include <type_traits>
namespace Vc_VERSIONED_NAMESPACE
{
namespace Detail
{
template <int exponent> constexpr double exponentToFloat(std::integral_constant<bool, true>);
template <int exponent> constexpr double exponentToFloat(std::integral_constant<bool, false>);
template <> constexpr double exponentToFloat<0>(std::integral_constant<bool, true>)
{
return 1.;
}
template <> constexpr double exponentToFloat<0>(std::integral_constant<bool, false>)
{
return 1.;
}
template <> constexpr double exponentToFloat<-32>(std::integral_constant<bool, true>)
{
return 1. / (65536. * 65536.);
}
template <> constexpr double exponentToFloat<32>(std::integral_constant<bool, false>)
{
return 65536. * 65536.;
}
template <> constexpr double exponentToFloat<-64>(std::integral_constant<bool, true>)
{
return 1. / (65536. * 65536. * 65536. * 65536.);
}
template <> constexpr double exponentToFloat<64>(std::integral_constant<bool, false>)
{
return 65536. * 65536. * 65536. * 65536.;
}
template <int exponent>
constexpr double exponentToFloat(std::integral_constant<bool, false> negative)
{
return exponentToFloat<exponent - 1>(negative) * 2.0;
}
template <int exponent>
constexpr double exponentToFloat(std::integral_constant<bool, true> negative)
{
return exponentToFloat<exponent + 1>(negative) * 0.5;
}
template <int sign, unsigned long long mantissa, int exponent> constexpr double doubleConstant()
{
return (static_cast<double>((mantissa & 0x000fffffffffffffull) | 0x0010000000000000ull) /
0x0010000000000000ull) *
exponentToFloat<exponent>(std::integral_constant<bool, (exponent < 0)>()) * sign;
}
template <int sign, unsigned int mantissa, int exponent> constexpr float floatConstant()
{
return (static_cast<float>((mantissa & 0x007fffffu) | 0x00800000u) / 0x00800000u) *
static_cast<float>(
exponentToFloat<exponent>(std::integral_constant<bool, (exponent < 0)>())) *
sign;
}
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
template <class T, class Abi>
SimdArray<int, Vector<T, Abi>::size()> fpclassify(const Vector<T, Abi> &x)
{
return SimdArray<int, Vector<T, Abi>::size()>(
[&](std::size_t i) { return std::fpclassify(x[i]); });
}
template <class T, size_t N> SimdArray<int, N> fpclassify(const SimdArray<T, N> &x)
{
return SimdArray<int, N>([&](std::size_t i) { return std::fpclassify(x[i]); });
}
#ifdef Vc_IMPL_SSE
#ifdef Vc_COMMON_MATH_H_INTERNAL
enum LogarithmBase {
BaseE, Base10, Base2
};
namespace Detail
{
template <typename T, typename Abi>
using Const = typename std::conditional<std::is_same<Abi, VectorAbi::Avx>::value,
AVX::Const<T>, SSE::Const<T>>::type;
template<LogarithmBase Base>
struct LogImpl
{
template<typename T, typename Abi> static Vc_ALWAYS_INLINE void log_series(Vector<T, Abi> &Vc_RESTRICT x, typename Vector<T, Abi>::AsArg exponent) {
typedef Vector<T, Abi> V;
typedef Detail::Const<T, Abi> C;
const V x2 = x * x;
#ifdef Vc_LOG_ILP
V y2 = (C::P(6) * x2 + C::P(7) * x) + C::P(8);
V y0 = (C::P(0) * x2 + C::P(1) * x) + C::P(2);
V y1 = (C::P(3) * x2 + C::P(4) * x) + C::P(5);
const V x3 = x2 * x;
const V x6 = x3 * x3;
const V x9 = x6 * x3;
V y = (y0 * x9 + y1 * x6) + y2 * x3;
#elif defined Vc_LOG_ILP2
const V x3 = x2 * x;
const V x4 = x2 * x2;
const V x5 = x2 * x3;
const V x6 = x3 * x3;
const V x7 = x4 * x3;
const V x8 = x4 * x4;
const V x9 = x5 * x4;
const V x10 = x5 * x5;
const V x11 = x5 * x6;
V y = C::P(0) * x11 + C::P(1) * x10 + C::P(2) * x9 + C::P(3) * x8 + C::P(4) * x7
+ C::P(5) * x6 + C::P(6) * x5 + C::P(7) * x4 + C::P(8) * x3;
#else
V y = C::P(0);
Vc::Common::unrolled_loop<int, 1, 9>([&](int i) { y = y * x + C::P(i); });
y *= x * x2;
#endif
switch (Base) {
case BaseE:
y += exponent * C::ln2_small();
y -= x2 * C::_1_2();
x += y;
x += exponent * C::ln2_large();
break;
case Base10:
y += exponent * C::ln2_small();
y -= x2 * C::_1_2();
x += y;
x += exponent * C::ln2_large();
x *= C::log10_e();
break;
case Base2:
{
const V x_ = x;
x *= C::log2_e();
y *= C::log2_e();
y -= x_ * x * C::_1_2();
x += y;
x += exponent;
break;
}
}
}
template <typename Abi>
static Vc_ALWAYS_INLINE void log_series(Vector<double, Abi> &Vc_RESTRICT x,
typename Vector<double, Abi>::AsArg exponent)
{
typedef Vector<double, Abi> V;
typedef Detail::Const<double, Abi> C;
const V x2 = x * x;
V y = C::P(0);
V y2 = C::Q(0) + x;
Vc::Common::unrolled_loop<int, 1, 5>([&](int i) {
y = y * x + C::P(i);
y2 = y2 * x + C::Q(i);
});
y2 = x / y2;
y = y * x + C::P(5);
y = x2 * y * y2;
switch (Base) {
case BaseE:
y += exponent * C::ln2_small();
y -= x2 * C::_1_2();
x += y;
x += exponent * C::ln2_large();
break;
case Base10:
y += exponent * C::ln2_small();
y -= x2 * C::_1_2();
x += y;
x += exponent * C::ln2_large();
x *= C::log10_e();
break;
case Base2:
{
const V x_ = x;
x *= C::log2_e();
y *= C::log2_e();
y -= x_ * x * C::_1_2();
x += y;
x += exponent;
break;
}
}
}
template <typename T, typename Abi, typename V = Vector<T, Abi>>
static inline Vector<T, Abi> calc(V _x)
{
typedef typename V::Mask M;
typedef Detail::Const<T, Abi> C;
V x(_x);
const M invalidMask = x < V::Zero();
const M infinityMask = x == V::Zero();
const M denormal = x <= C::min();
x(denormal) *= V(Vc::Detail::doubleConstant<1, 0, 54>());
V exponent = Detail::exponent(x.data());
exponent(denormal) -= 54;
x.setZero(C::exponentMask());
x = Detail::operator|(x,
C::_1_2());
const M smallX = x < C::_1_sqrt2();
x(smallX) += x;
x -= V::One();
exponent(!smallX) += V::One();
log_series(x, exponent);
x.setQnan(invalidMask);
x(infinityMask) = C::neginf();
return x;
}
};
}
template <typename T, typename Abi>
Vc_INTRINSIC Vc_CONST Vector<T, detail::not_fixed_size_abi<Abi>> log(
const Vector<T, Abi> &x)
{
return Detail::LogImpl<BaseE>::calc<T, Abi>(x);
}
template <typename T, typename Abi>
Vc_INTRINSIC Vc_CONST Vector<T, detail::not_fixed_size_abi<Abi>> log10(
const Vector<T, Abi> &x)
{
return Detail::LogImpl<Base10>::calc<T, Abi>(x);
}
template <typename T, typename Abi>
Vc_INTRINSIC Vc_CONST Vector<T, detail::not_fixed_size_abi<Abi>> log2(
const Vector<T, Abi> &x)
{
return Detail::LogImpl<Base2>::calc<T, Abi>(x);
}
#endif
#ifdef Vc_COMMON_MATH_H_INTERNAL
constexpr float log2_e = 1.44269504088896341f;
constexpr float MAXLOGF = 88.72283905206835f;
constexpr float MINLOGF = -103.278929903431851103f;
constexpr float MAXNUMF = 3.4028234663852885981170418348451692544e38f;
template <typename Abi, typename = enable_if<std::is_same<Abi, VectorAbi::Sse>::value ||
std::is_same<Abi, VectorAbi::Avx>::value>>
inline Vector<float, detail::not_fixed_size_abi<Abi>> exp(Vector<float, Abi> x)
{
using V = Vector<float, Abi>;
typedef typename V::Mask M;
typedef Detail::Const<float, Abi> C;
const M overflow = x > MAXLOGF;
const M underflow = x < MINLOGF;
V z = floor(C::log2_e() * x + 0.5f);
const auto n = static_cast<Vc::SimdArray<int, V::Size>>(z);
x -= z * C::ln2_large();
x -= z * C::ln2_small();
z = ((((( 1.9875691500E-4f * x
+ 1.3981999507E-3f) * x
+ 8.3334519073E-3f) * x
+ 4.1665795894E-2f) * x
+ 1.6666665459E-1f) * x
+ 5.0000001201E-1f) * (x * x)
+ x
+ 1.0f;
x = ldexp(z, n);
x(overflow) = std::numeric_limits<typename V::EntryType>::infinity();
x.setZero(underflow);
return x;
}
#endif
#ifdef Vc_IMPL_AVX
inline AVX::double_v exp(AVX::double_v _x)
{
AVX::Vector<double> x = _x;
typedef AVX::Vector<double> V;
typedef V::Mask M;
typedef AVX::Const<double> C;
const M overflow = x > Vc::Detail::doubleConstant< 1, 0x0006232bdd7abcd2ull, 9>();
const M underflow = x < Vc::Detail::doubleConstant<-1, 0x0006232bdd7abcd2ull, 9>();
V px = floor(C::log2_e() * x + 0.5);
__m128i tmp = _mm256_cvttpd_epi32(px.data());
const SimdArray<int, V::Size> n = SSE::int_v{tmp};
x -= px * C::ln2_large();
x -= px * C::ln2_small();
const double P[] = {
Vc::Detail::doubleConstant<1, 0x000089cdd5e44be8ull, -13>(),
Vc::Detail::doubleConstant<1, 0x000f06d10cca2c7eull, -6>(),
Vc::Detail::doubleConstant<1, 0x0000000000000000ull, 0>()
};
const double Q[] = {
Vc::Detail::doubleConstant<1, 0x00092eb6bc365fa0ull, -19>(),
Vc::Detail::doubleConstant<1, 0x0004ae39b508b6c0ull, -9>(),
Vc::Detail::doubleConstant<1, 0x000d17099887e074ull, -3>(),
Vc::Detail::doubleConstant<1, 0x0000000000000000ull, 1>()
};
const V x2 = x * x;
px = x * ((P[0] * x2 + P[1]) * x2 + P[2]);
x = px / ((((Q[0] * x2 + Q[1]) * x2 + Q[2]) * x2 + Q[3]) - px);
x = V::One() + 2.0 * x;
x = ldexp(x, n);
x(overflow) = std::numeric_limits<double>::infinity();
x.setZero(underflow);
return x;
}
#endif
inline SSE::double_v exp(SSE::double_v::AsArg _x) {
SSE::Vector<double> x = _x;
typedef SSE::Vector<double> V;
typedef V::Mask M;
typedef SSE::Const<double> C;
const M overflow = x > Vc::Detail::doubleConstant< 1, 0x0006232bdd7abcd2ull, 9>();
const M underflow = x < Vc::Detail::doubleConstant<-1, 0x0006232bdd7abcd2ull, 9>();
V px = floor(C::log2_e() * x + 0.5);
SimdArray<int, V::Size> n;
_mm_storel_epi64(reinterpret_cast<__m128i *>(&n), _mm_cvttpd_epi32(px.data()));
x -= px * C::ln2_large();
x -= px * C::ln2_small();
const double P[] = {
Vc::Detail::doubleConstant<1, 0x000089cdd5e44be8ull, -13>(),
Vc::Detail::doubleConstant<1, 0x000f06d10cca2c7eull, -6>(),
Vc::Detail::doubleConstant<1, 0x0000000000000000ull, 0>()
};
const double Q[] = {
Vc::Detail::doubleConstant<1, 0x00092eb6bc365fa0ull, -19>(),
Vc::Detail::doubleConstant<1, 0x0004ae39b508b6c0ull, -9>(),
Vc::Detail::doubleConstant<1, 0x000d17099887e074ull, -3>(),
Vc::Detail::doubleConstant<1, 0x0000000000000000ull, 1>()
};
const V x2 = x * x;
px = x * ((P[0] * x2 + P[1]) * x2 + P[2]);
x = px / ((((Q[0] * x2 + Q[1]) * x2 + Q[2]) * x2 + Q[3]) - px);
x = V::One() + 2.0 * x;
x = ldexp(x, n);
x(overflow) = std::numeric_limits<double>::infinity();
x.setZero(underflow);
return x;
}
#endif
}
#undef Vc_COMMON_MATH_H_INTERNAL
#endif
#ifdef isfinite
#undef isfinite
#endif
#ifdef isnan
#undef isnan
#endif
#ifndef VC_COMMON_VECTORTUPLE_H_
#define VC_COMMON_VECTORTUPLE_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template<size_t StructSize, typename V, typename I, bool Readonly = true> struct InterleavedMemoryReadAccess;
template <int Length, typename V> class VectorReferenceArray
{
typedef typename V::EntryType T;
typedef V &Vc_RESTRICT Reference;
std::array<V * Vc_RESTRICT, Length> r;
typedef make_index_sequence<Length> IndexSequence;
template <typename VV, std::size_t... Indexes>
constexpr VectorReferenceArray<Length + 1, VV> appendOneReference(
VV &a, index_sequence<Indexes...>) const
{
return {*r[Indexes]..., a};
}
template <typename A, std::size_t... Indexes>
Vc_INTRINSIC void callDeinterleave(const A &access, index_sequence<Indexes...>) const
{
access.deinterleave(*r[Indexes]...);
}
public:
template <typename... Us, typename = enable_if<(sizeof...(Us) == Length)>>
constexpr VectorReferenceArray(Us &&... args)
: r{{std::addressof(std::forward<Us>(args))...}}
{
}
template <typename VV, typename = enable_if<!std::is_const<V>::value &&
std::is_same<VV, V>::value>>
Vc_DEPRECATED("build the tuple with Vc::tie instead")
constexpr VectorReferenceArray<Length + 1, V> operator, (VV & a) const
{
return appendOneReference(a, IndexSequence());
}
Vc_DEPRECATED("build the tuple with Vc::tie instead")
constexpr VectorReferenceArray<Length + 1, const V> operator, (const V &a) const
{
return appendOneReference(a, IndexSequence());
}
template <size_t StructSize, typename I, bool RO>
Vc_ALWAYS_INLINE enable_if<(Length <= StructSize), void> operator=(
const InterleavedMemoryReadAccess<StructSize, V, I, RO> &access)
{
callDeinterleave(access, IndexSequence());
}
template <size_t StructSize, typename I, bool RO>
enable_if<(Length > StructSize), void> operator=(
const InterleavedMemoryReadAccess<StructSize, V, I, RO> &access) =
delete;
template <typename... Inputs> void operator=(TransposeProxy<Inputs...> &&proxy)
{
transpose_impl(TransposeTag<Length, sizeof...(Inputs)>(), &r[0], proxy);
}
template <typename T, typename IndexVector, typename Scale, bool Flag>
void operator=(const SubscriptOperation<T, IndexVector, Scale, Flag> &sub)
{
const auto &args = sub.gatherArguments();
Common::InterleavedMemoryReadAccess<1, V, Traits::decay<decltype(args.indexes)>>
deinterleaver(args.address, args.indexes);
callDeinterleave(deinterleaver, IndexSequence());
}
Vc_ALWAYS_INLINE Reference operator[](std::size_t i) { return *r[i]; }
};
}
template <typename T, typename Abi>
Vc_DEPRECATED("build the tuple with Vc::tie instead")
constexpr Common::VectorReferenceArray<2, Vc::Vector<T, Abi>>
operator,(Vc::Vector<T, Abi> &a, Vc::Vector<T, Abi> &b)
{
return {a, b};
}
template <typename T, typename Abi>
Vc_DEPRECATED("build the tuple with Vc::tie instead")
constexpr Common::VectorReferenceArray<2, const Vc::Vector<T, Abi>>
operator,(const Vc::Vector<T, Abi> &a, const Vc::Vector<T, Abi> &b)
{
return {a, b};
}
template <typename V, typename... Vs>
constexpr Common::VectorReferenceArray<sizeof...(Vs) + 1,
typename std::remove_reference<V>::type>
tie(V &&a, Vs &&... b)
{
return {std::forward<V>(a), std::forward<Vs>(b)...};
}
}
#endif
#ifndef VC_COMMON_ALGORITHMS_H_
#define VC_COMMON_ALGORITHMS_H_ 
#ifndef VC_COMMON_SIMDIZE_H_
#define VC_COMMON_SIMDIZE_H_ 
#include <tuple>
#include <array>
#ifndef VC_ALLOCATOR_H_
#define VC_ALLOCATOR_H_ 
#include <new>
#include <cstddef>
#include <cstdlib>
#include <utility>
#ifdef Vc_MSVC
#define Vc_DECLARE_ALLOCATOR(Type) \
namespace std \
{ \
template <> class allocator<Type> : public ::Vc::Allocator<Type> \
{ \
public: \
template <typename U> struct rebind { \
typedef ::std::allocator<U> other; \
}; \
\
const allocator &select_on_container_copy_construction() const { return *this; } \
}; \
}
#else
#define Vc_DECLARE_ALLOCATOR(Type) \
namespace std \
{ \
template <> class allocator<Type> : public ::Vc::Allocator<Type> \
{ \
public: \
template <typename U> struct rebind { \
typedef ::std::allocator<U> other; \
}; \
}; \
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
using std::size_t;
using std::ptrdiff_t;
template<typename T> class Allocator
{
private:
enum Constants {
#ifdef Vc_HAVE_STD_MAX_ALIGN_T
NaturalAlignment = alignof(std::max_align_t),
#elif defined(Vc_HAVE_MAX_ALIGN_T)
NaturalAlignment = alignof(::max_align_t),
#else
NaturalAlignment = sizeof(void *) > alignof(long double) ? sizeof(void *) :
(alignof(long double) > alignof(long long) ? alignof(long double) : alignof(long long)),
#endif
#if defined Vc_IMPL_AVX
SimdAlignment = 32,
#elif defined Vc_IMPL_SSE
SimdAlignment = 16,
#else
SimdAlignment = 1,
#endif
Alignment = alignof(T) > SimdAlignment ? alignof(T) : SimdAlignment,
ExtraBytes = Alignment > NaturalAlignment ? Alignment : 0,
AlignmentMask = Alignment - 1
};
public:
typedef size_t size_type;
typedef ptrdiff_t difference_type;
typedef T* pointer;
typedef const T* const_pointer;
typedef T& reference;
typedef const T& const_reference;
typedef T value_type;
template<typename U> struct rebind { typedef Allocator<U> other; };
Allocator() throw() { }
Allocator(const Allocator&) throw() { }
template<typename U> Allocator(const Allocator<U>&) throw() { }
pointer address(reference x) const { return &x; }
const_pointer address(const_reference x) const { return &x; }
pointer allocate(size_type n, const void* = 0)
{
if (n > this->max_size()) {
throw std::bad_alloc();
}
char *p = static_cast<char *>(::operator new(n * sizeof(T) + ExtraBytes));
if (ExtraBytes > 0) {
char *const pp = p;
p += ExtraBytes;
const char *null = 0;
p -= ((p - null) & AlignmentMask);
reinterpret_cast<char **>(p)[-1] = pp;
}
return reinterpret_cast<pointer>(p);
}
void deallocate(pointer p, size_type)
{
if (ExtraBytes > 0) {
p = reinterpret_cast<pointer *>(p)[-1];
}
::operator delete(p);
}
size_type max_size() const throw() { return size_t(-1) / sizeof(T); }
#ifdef Vc_MSVC
const Allocator &select_on_container_copy_construction() const { return *this; }
void construct(pointer p) { ::new(p) T(); }
void construct(pointer p, const T& val) { ::new(p) T(val); }
void destroy(pointer p) { p->~T(); }
#else
template<typename U, typename... Args> void construct(U* p, Args&&... args)
{
::new(p) U(std::forward<Args>(args)...);
}
template<typename U> void destroy(U* p) { p->~U(); }
#endif
};
template<typename T> inline bool operator==(const Allocator<T>&, const Allocator<T>&) { return true; }
template<typename T> inline bool operator!=(const Allocator<T>&, const Allocator<T>&) { return false; }
}
namespace std
{
template<typename T> class allocator<Vc::Vector<T> > : public ::Vc::Allocator<Vc::Vector<T> >
{
public:
template<typename U> struct rebind { typedef ::std::allocator<U> other; };
#ifdef Vc_MSVC
const allocator &select_on_container_copy_construction() const { return *this; }
#endif
};
template <typename T>
class allocator<Vc::Mask<T>> : public ::Vc::Allocator<Vc::Mask<T>>
{
public:
template<typename U> struct rebind { typedef ::std::allocator<U> other; };
#ifdef Vc_MSVC
const allocator &select_on_container_copy_construction() const { return *this; }
#endif
};
template <typename T, std::size_t N, typename V, std::size_t M>
class allocator<Vc::SimdArray<T, N, V, M>> : public ::Vc::Allocator<Vc::SimdArray<T, N, V, M>>
{
public:
template<typename U> struct rebind { typedef ::std::allocator<U> other; };
#ifdef Vc_MSVC
const allocator &select_on_container_copy_construction() const { return *this; }
#endif
};
template <typename T, std::size_t N, typename V, std::size_t M>
class allocator<Vc::SimdMaskArray<T, N, V, M>> : public ::Vc::Allocator<Vc::SimdMaskArray<T, N, V, M>>
{
public:
template<typename U> struct rebind { typedef ::std::allocator<U> other; };
#ifdef Vc_MSVC
const allocator &select_on_container_copy_construction() const { return *this; }
#endif
};
}
#endif
#ifndef VC_COMMON_INTERLEAVEDMEMORY_H_
#define VC_COMMON_INTERLEAVEDMEMORY_H_ 
namespace Vc_VERSIONED_NAMESPACE
{
namespace Common
{
template<typename V, typename I, bool Readonly> struct InterleavedMemoryAccessBase
{
typedef typename std::conditional<
Readonly, typename std::add_const<typename V::EntryType>::type,
typename V::EntryType>::type T;
typedef typename V::AsArg VArg;
typedef T Ta Vc_MAY_ALIAS;
const I m_indexes;
Ta *const m_data;
Vc_ALWAYS_INLINE InterleavedMemoryAccessBase(typename I::AsArg indexes, Ta *data)
: m_indexes(indexes), m_data(data)
{
}
template <typename... Vs> Vc_INTRINSIC void deinterleave(Vs &&... vs) const
{
Impl::deinterleave(m_data, m_indexes, std::forward<Vs>(vs)...);
}
protected:
using Impl = Vc::Detail::InterleaveImpl<V, V::Size, sizeof(V)>;
template <typename T, std::size_t... Indexes>
Vc_INTRINSIC void callInterleave(T &&a, index_sequence<Indexes...>)
{
Impl::interleave(m_data, m_indexes, a[Indexes]...);
}
};
template <size_t StructSize, typename V, typename I = typename V::IndexType,
bool Readonly>
struct InterleavedMemoryReadAccess : public InterleavedMemoryAccessBase<V, I, Readonly>
{
typedef InterleavedMemoryAccessBase<V, I, Readonly> Base;
typedef typename Base::Ta Ta;
Vc_ALWAYS_INLINE InterleavedMemoryReadAccess(Ta *data, typename I::AsArg indexes)
: Base(StructSize == 1u
? indexes
: StructSize == 2u
? indexes << 1
: StructSize == 4u
? indexes << 2
: StructSize == 8u
? indexes << 3
: StructSize == 16u ? indexes << 4
: indexes * I(int(StructSize)),
data)
{
}
template <typename T, std::size_t... Indexes>
Vc_ALWAYS_INLINE T deinterleave_unpack(index_sequence<Indexes...>) const
{
T r;
Base::Impl::deinterleave(this->m_data, this->m_indexes, std::get<Indexes>(r)...);
return r;
}
template <typename T,
typename = enable_if<(std::is_default_constructible<T>::value &&
std::is_same<V, Traits::decay<decltype(std::get<0>(
std::declval<T &>()))>>::value)>>
Vc_ALWAYS_INLINE operator T() const
{
return deinterleave_unpack<T>(make_index_sequence<std::tuple_size<T>::value>());
}
};
template<typename I> struct CheckIndexesUnique
{
#ifdef NDEBUG
static Vc_INTRINSIC void test(const I &) {}
#else
static void test(const I &indexes)
{
const I test = indexes.sorted();
Vc_ASSERT(I::Size == 1 || (test == test.rotated(1)).isEmpty())
}
#endif
};
template<size_t S> struct CheckIndexesUnique<SuccessiveEntries<S> >
{
static Vc_INTRINSIC void test(const SuccessiveEntries<S> &) {}
};
template <size_t StructSize, typename V, typename I = typename V::IndexType>
struct InterleavedMemoryAccess : public InterleavedMemoryReadAccess<StructSize, V, I, false>
{
typedef InterleavedMemoryAccessBase<V, I, false> Base;
typedef typename Base::Ta Ta;
Vc_ALWAYS_INLINE InterleavedMemoryAccess(Ta *data, typename I::AsArg indexes)
: InterleavedMemoryReadAccess<StructSize, V, I, false>(data, indexes)
{
CheckIndexesUnique<I>::test(indexes);
}
template <int N> Vc_ALWAYS_INLINE void operator=(VectorReferenceArray<N, V> &&rhs)
{
static_assert(N <= StructSize,
"You_are_trying_to_scatter_more_data_into_the_struct_than_it_has");
this->callInterleave(std::move(rhs), make_index_sequence<N>());
}
template <int N> Vc_ALWAYS_INLINE void operator=(VectorReferenceArray<N, const V> &&rhs)
{
static_assert(N <= StructSize,
"You_are_trying_to_scatter_more_data_into_the_struct_than_it_has");
this->callInterleave(std::move(rhs), make_index_sequence<N>());
}
};
template<typename S, typename V> class InterleavedMemoryWrapper
{
typedef typename std::conditional<std::is_const<S>::value,
const typename V::EntryType,
typename V::EntryType>::type T;
typedef typename V::IndexType I;
typedef typename V::AsArg VArg;
typedef const I &IndexType;
static constexpr std::size_t StructSize = sizeof(S) / sizeof(T);
typedef InterleavedMemoryAccess<StructSize, V> Access;
typedef InterleavedMemoryReadAccess<StructSize, V> ReadAccess;
typedef InterleavedMemoryAccess<StructSize, V, SuccessiveEntries<StructSize> > AccessSuccessiveEntries;
typedef InterleavedMemoryReadAccess<StructSize, V, SuccessiveEntries<StructSize> > ReadSuccessiveEntries;
typedef T Ta Vc_MAY_ALIAS;
Ta *const m_data;
static_assert(StructSize * sizeof(T) == sizeof(S),
"InterleavedMemoryAccess_does_not_support_packed_structs");
public:
Vc_ALWAYS_INLINE InterleavedMemoryWrapper(S *s)
: m_data(reinterpret_cast<Ta *>(s))
{
}
template <typename IT>
Vc_ALWAYS_INLINE enable_if<!std::is_convertible<IT, size_t>::value &&
std::is_convertible<IT, IndexType>::value &&
!std::is_const<S>::value,
Access>
operator[](IT indexes)
{
return Access(m_data, indexes);
}
Vc_ALWAYS_INLINE ReadAccess operator[](IndexType indexes) const
{
return ReadAccess(m_data, indexes);
}
Vc_ALWAYS_INLINE ReadAccess gather(IndexType indexes) const { return operator[](indexes); }
Vc_ALWAYS_INLINE ReadSuccessiveEntries operator[](size_t first) const
{
return ReadSuccessiveEntries(m_data, first);
}
Vc_ALWAYS_INLINE AccessSuccessiveEntries operator[](size_t first)
{
return AccessSuccessiveEntries(m_data, first);
}
};
}
using Common::InterleavedMemoryWrapper;
template <typename V, typename S>
inline Common::InterleavedMemoryWrapper<S, V> make_interleave_wrapper(S *s)
{
return Common::InterleavedMemoryWrapper<S, V>(s);
}
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
namespace SimdizeDetail
{
using std::is_same;
using std::is_base_of;
using std::false_type;
using std::true_type;
using std::iterator_traits;
using std::conditional;
using std::size_t;
template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;
template <typename... Ts> struct Typelist;
enum class Category {
None,
ArithmeticVectorizable,
InputIterator,
OutputIterator,
ForwardIterator,
BidirectionalIterator,
RandomAccessIterator,
ClassTemplate
};
template <typename T, typename ItCat = typename T::iterator_category>
constexpr Category iteratorCategories(int, ItCat * = nullptr)
{
return is_base_of<std::random_access_iterator_tag, ItCat>::value
? Category::RandomAccessIterator
: is_base_of<std::bidirectional_iterator_tag, ItCat>::value
? Category::BidirectionalIterator
: is_base_of<std::forward_iterator_tag, ItCat>::value
? Category::ForwardIterator
: is_base_of<std::output_iterator_tag, ItCat>::value
? Category::OutputIterator
: is_base_of<std::input_iterator_tag, ItCat>::value
? Category::InputIterator
: Category::None;
}
template <typename T>
constexpr enable_if<std::is_pointer<T>::value, Category> iteratorCategories(float)
{
return Category::RandomAccessIterator;
}
template <typename T> constexpr Category iteratorCategories(...)
{
return Category::None;
}
template <typename T> struct is_class_template : public false_type
{
};
template <template <typename...> class C, typename... Ts>
struct is_class_template<C<Ts...>> : public true_type
{
};
template <typename T> constexpr Category typeCategory()
{
return (is_same<T, bool>::value || is_same<T, short>::value ||
is_same<T, unsigned short>::value || is_same<T, int>::value ||
is_same<T, unsigned int>::value || is_same<T, float>::value ||
is_same<T, double>::value)
? Category::ArithmeticVectorizable
: iteratorCategories<T>(int()) != Category::None
? iteratorCategories<T>(int())
: is_class_template<T>::value ? Category::ClassTemplate
: Category::None;
}
template <typename T, size_t TupleSize = std::tuple_size<T>::value>
constexpr size_t determine_tuple_size()
{
return TupleSize;
}
template <typename T, size_t TupleSize = T::tuple_size>
constexpr size_t determine_tuple_size(size_t = T::tuple_size)
{
return TupleSize;
}
template <typename T> struct determine_tuple_size_
: public std::integral_constant<size_t, determine_tuple_size<T>()>
{};
namespace
{
template <typename T> struct The_simdization_for_the_requested_type_is_not_implemented;
}
template <typename T, size_t N, typename MT, Category = typeCategory<T>()>
struct ReplaceTypes : public The_simdization_for_the_requested_type_is_not_implemented<T>
{
};
template <typename T, size_t N, typename MT> struct ReplaceTypes<T, N, MT, Category::None>
{
typedef T type;
};
template <typename T, size_t N = 0, typename MT = void>
using simdize = typename SimdizeDetail::ReplaceTypes<T, N, MT>::type;
template <class T, size_t N,
class Best = typename Common::select_best_vector_type<T, N>::type>
using deduce_vector_t =
typename std::conditional<Best::size() == N, Best, SimdArray<T, N>>::type;
template <typename T, size_t N, typename MT>
struct ReplaceTypes<T, N, MT, Category::ArithmeticVectorizable>
: public conditional<N == 0, Vector<T>, deduce_vector_t<T, N>> {
};
template <size_t N, typename MT>
struct ReplaceTypes<bool, N, MT, Category::ArithmeticVectorizable>
: public std::enable_if<true, typename ReplaceTypes<MT, N, MT>::type::mask_type> {
};
template <size_t N>
struct ReplaceTypes<bool, N, void, Category::ArithmeticVectorizable>
: public ReplaceTypes<bool, N, float, Category::ArithmeticVectorizable>
{
};
template <size_t N, typename MT, typename Replaced, typename... Remaining>
struct SubstituteOneByOne;
template <size_t N, typename MT, typename... Replaced, typename T,
typename... Remaining>
struct SubstituteOneByOne<N, MT, Typelist<Replaced...>, T, Remaining...>
{
private:
template <typename U, size_t M = U::Size>
static std::integral_constant<size_t, M> size_or_0(int);
template <typename U> static std::integral_constant<size_t, 0> size_or_0(...);
using V = simdize<T, N, MT>;
static constexpr auto NewN = N != 0 ? N : decltype(size_or_0<V>(int()))::value;
typedef conditional_t<(N != NewN && is_same<MT, void>::value),
conditional_t<is_same<T, bool>::value, float, T>, MT> NewMT;
public:
using type = typename SubstituteOneByOne<NewN, NewMT, Typelist<Replaced..., V>,
Remaining...>::type;
};
template <size_t Size, typename... Replaced> struct SubstitutedBase;
template <typename Replaced> struct SubstitutedBase<1, Replaced> {
template <typename ValueT, template <typename, ValueT...> class C, ValueT... Values>
using SubstitutedWithValues = C<Replaced, Values...>;
};
template <typename R0, typename R1> struct SubstitutedBase<2, R0, R1>
{
template <typename ValueT, template <typename, typename, ValueT...> class C,
ValueT... Values>
using SubstitutedWithValues = C<R0, R1, Values...>;
};
template <typename R0, typename R1, typename R2> struct SubstitutedBase<3, R0, R1, R2>
{
template <typename ValueT, template <typename, typename, typename, ValueT...> class C,
ValueT... Values>
using SubstitutedWithValues = C<R0, R1, R2, Values...>;
};
#if defined Vc_ICC || defined Vc_MSVC
#define Vc_VALUE_PACK_EXPANSION_IS_BROKEN 1
#endif
template <typename... Replaced> struct SubstitutedBase<4, Replaced...> {
#ifndef Vc_VALUE_PACK_EXPANSION_IS_BROKEN
template <typename ValueT,
template <typename, typename, typename, typename, ValueT...> class C,
ValueT... Values>
using SubstitutedWithValues = C<Replaced..., Values...>;
#endif
};
template <typename... Replaced> struct SubstitutedBase<5, Replaced...> {
#ifndef Vc_VALUE_PACK_EXPANSION_IS_BROKEN
template <typename ValueT, template <typename, typename, typename, typename, typename,
ValueT...> class C,
ValueT... Values>
using SubstitutedWithValues = C<Replaced..., Values...>;
#endif
};
template <typename... Replaced> struct SubstitutedBase<6, Replaced...> {
#ifndef Vc_VALUE_PACK_EXPANSION_IS_BROKEN
template <typename ValueT, template <typename, typename, typename, typename, typename,
typename, ValueT...> class C,
ValueT... Values>
using SubstitutedWithValues = C<Replaced..., Values...>;
#endif
};
template <typename... Replaced> struct SubstitutedBase<7, Replaced...> {
#ifndef Vc_VALUE_PACK_EXPANSION_IS_BROKEN
template <typename ValueT, template <typename, typename, typename, typename, typename,
typename, typename, ValueT...> class C,
ValueT... Values>
using SubstitutedWithValues = C<Replaced..., Values...>;
#endif
};
template <typename... Replaced> struct SubstitutedBase<8, Replaced...> {
#ifndef Vc_VALUE_PACK_EXPANSION_IS_BROKEN
template <typename ValueT, template <typename, typename, typename, typename, typename,
typename, typename, typename, ValueT...> class C,
ValueT... Values>
using SubstitutedWithValues = C<Replaced..., Values...>;
#endif
};
template <size_t N_, typename MT, typename Replaced0, typename... Replaced>
struct SubstituteOneByOne<N_, MT, Typelist<Replaced0, Replaced...>>
{
struct type
: public SubstitutedBase<sizeof...(Replaced) + 1, Replaced0, Replaced...> {
static constexpr auto N = N_;
template <template <typename...> class C>
using Substituted = C<Replaced0, Replaced...>;
};
};
template <typename Scalar, typename Base, size_t N> class Adapter;
template <template <typename...> class C, typename... Ts, size_t N, typename MT>
struct ReplaceTypes<C<Ts...>, N, MT, Category::ClassTemplate>
{
using SubstitutionResult =
typename SubstituteOneByOne<N, MT, Typelist<>, Ts...>::type;
using Vectorized = typename SubstitutionResult::template Substituted<C>;
using type = conditional_t<is_same<C<Ts...>, Vectorized>::value, C<Ts...>,
Adapter<C<Ts...>, Vectorized, SubstitutionResult::N>>;
};
#ifdef Vc_VALUE_PACK_EXPANSION_IS_BROKEN
#define Vc_DEFINE_NONTYPE_REPLACETYPES_(ValueType_) \
template <template <typename, ValueType_...> class C, typename T, ValueType_ Value0, \
ValueType_... Values> \
struct is_class_template<C<T, Value0, Values...>> : public true_type { \
}; \
template <template <typename, typename, ValueType_...> class C, typename T0, \
typename T1, ValueType_ Value0, ValueType_... Values> \
struct is_class_template<C<T0, T1, Value0, Values...>> : public true_type { \
}; \
template <template <typename, typename, typename, ValueType_...> class C, \
typename T0, typename T1, typename T2, ValueType_ Value0, \
ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, Value0, Values...>> : public true_type { \
}; \
template <template <typename, typename, typename, typename, ValueType_...> class C, \
typename T0, typename T1, typename T2, typename T3, ValueType_ Value0, \
ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, T3, Value0, Values...>> : public true_type { \
}; \
template <template <typename, typename, typename, typename, typename, ValueType_...> \
class C, \
typename T0, typename T1, typename T2, typename T3, typename T4, \
ValueType_ Value0, ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, T3, T4, Value0, Values...>> \
: public true_type { \
}; \
template <template <typename, typename, typename, typename, typename, typename, \
ValueType_...> class C, \
typename T0, typename T1, typename T2, typename T3, typename T4, \
typename T5, ValueType_ Value0, ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, T3, T4, T5, Value0, Values...>> \
: public true_type { \
}; \
template <template <typename, typename, typename, typename, typename, typename, \
typename, ValueType_...> class C, \
typename T0, typename T1, typename T2, typename T3, typename T4, \
typename T5, typename T6, ValueType_ Value0, ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, T3, T4, T5, T6, Value0, Values...>> \
: public true_type { \
}; \
template <template <typename, ValueType_> class C, typename T0, ValueType_ Value0, \
size_t N, typename MT> \
struct ReplaceTypes<C<T0, Value0>, N, MT, Category::ClassTemplate> { \
typedef typename SubstituteOneByOne<N, MT, Typelist<>, T0>::type tmp; \
typedef typename tmp::template SubstitutedWithValues<ValueType_, C, Value0> \
Substituted; \
static constexpr auto NN = tmp::N; \
typedef conditional_t<is_same<C<T0, Value0>, Substituted>::value, C<T0, Value0>, \
Adapter<C<T0, Value0>, Substituted, NN>> type; \
}; \
template <template <typename, typename, ValueType_> class C, typename T0, \
typename T1, ValueType_ Value0, size_t N, typename MT> \
struct ReplaceTypes<C<T0, T1, Value0>, N, MT, Category::ClassTemplate> { \
typedef typename SubstituteOneByOne<N, MT, Typelist<>, T0, T1>::type tmp; \
typedef typename tmp::template SubstitutedWithValues<ValueType_, C, Value0> \
Substituted; \
static constexpr auto NN = tmp::N; \
typedef conditional_t<is_same<C<T0, T1, Value0>, Substituted>::value, \
C<T0, T1, Value0>, \
Adapter<C<T0, T1, Value0>, Substituted, NN>> type; \
}; \
template <template <typename, typename, typename, ValueType_> class C, typename T0, \
typename T1, typename T2, ValueType_ Value0, size_t N, typename MT> \
struct ReplaceTypes<C<T0, T1, T2, Value0>, N, MT, Category::ClassTemplate> { \
typedef typename SubstituteOneByOne<N, MT, Typelist<>, T0, T1, T2>::type tmp; \
typedef typename tmp::template SubstitutedWithValues<ValueType_, C, Value0> \
Substituted; \
static constexpr auto NN = tmp::N; \
typedef conditional_t<is_same<C<T0, T1, T2, Value0>, Substituted>::value, \
C<T0, T1, T2, Value0>, \
Adapter<C<T0, T1, T2, Value0>, Substituted, NN>> type; \
}
#else
#define Vc_DEFINE_NONTYPE_REPLACETYPES_(ValueType_) \
template <template <typename, ValueType_...> class C, typename T, ValueType_ Value0, \
ValueType_... Values> \
struct is_class_template<C<T, Value0, Values...>> : public true_type { \
}; \
template <template <typename, typename, ValueType_...> class C, typename T0, \
typename T1, ValueType_ Value0, ValueType_... Values> \
struct is_class_template<C<T0, T1, Value0, Values...>> : public true_type { \
}; \
template <template <typename, typename, typename, ValueType_...> class C, \
typename T0, typename T1, typename T2, ValueType_ Value0, \
ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, Value0, Values...>> : public true_type { \
}; \
template <template <typename, typename, typename, typename, ValueType_...> class C, \
typename T0, typename T1, typename T2, typename T3, ValueType_ Value0, \
ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, T3, Value0, Values...>> : public true_type { \
}; \
template <template <typename, typename, typename, typename, typename, ValueType_...> \
class C, \
typename T0, typename T1, typename T2, typename T3, typename T4, \
ValueType_ Value0, ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, T3, T4, Value0, Values...>> \
: public true_type { \
}; \
template <template <typename, typename, typename, typename, typename, typename, \
ValueType_...> class C, \
typename T0, typename T1, typename T2, typename T3, typename T4, \
typename T5, ValueType_ Value0, ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, T3, T4, T5, Value0, Values...>> \
: public true_type { \
}; \
template <template <typename, typename, typename, typename, typename, typename, \
typename, ValueType_...> class C, \
typename T0, typename T1, typename T2, typename T3, typename T4, \
typename T5, typename T6, ValueType_ Value0, ValueType_... Values> \
struct is_class_template<C<T0, T1, T2, T3, T4, T5, T6, Value0, Values...>> \
: public true_type { \
}; \
template <template <typename, ValueType_...> class C, typename T0, \
ValueType_ Value0, ValueType_... Values, size_t N, typename MT> \
struct ReplaceTypes<C<T0, Value0, Values...>, N, MT, Category::ClassTemplate> { \
typedef typename SubstituteOneByOne<N, MT, Typelist<>, T0>::type tmp; \
typedef typename tmp::template SubstitutedWithValues<ValueType_, C, Value0, \
Values...> Substituted; \
static constexpr auto NN = tmp::N; \
typedef conditional_t<is_same<C<T0, Value0, Values...>, Substituted>::value, \
C<T0, Value0, Values...>, \
Adapter<C<T0, Value0, Values...>, Substituted, NN>> type; \
}; \
template <template <typename, typename, ValueType_...> class C, typename T0, \
typename T1, ValueType_ Value0, ValueType_... Values, size_t N, \
typename MT> \
struct ReplaceTypes<C<T0, T1, Value0, Values...>, N, MT, Category::ClassTemplate> { \
typedef typename SubstituteOneByOne<N, MT, Typelist<>, T0, T1>::type tmp; \
typedef typename tmp::template SubstitutedWithValues<ValueType_, C, Value0, \
Values...> Substituted; \
static constexpr auto NN = tmp::N; \
typedef conditional_t<is_same<C<T0, T1, Value0, Values...>, Substituted>::value, \
C<T0, T1, Value0, Values...>, \
Adapter<C<T0, T1, Value0, Values...>, Substituted, NN>> \
type; \
}; \
template <template <typename, typename, typename, ValueType_...> class C, \
typename T0, typename T1, typename T2, ValueType_ Value0, \
ValueType_... Values, size_t N, typename MT> \
struct ReplaceTypes<C<T0, T1, T2, Value0, Values...>, N, MT, \
Category::ClassTemplate> { \
typedef typename SubstituteOneByOne<N, MT, Typelist<>, T0, T1, T2>::type tmp; \
typedef typename tmp::template SubstitutedWithValues<ValueType_, C, Value0, \
Values...> Substituted; \
static constexpr auto NN = tmp::N; \
typedef conditional_t< \
is_same<C<T0, T1, T2, Value0, Values...>, Substituted>::value, \
C<T0, T1, T2, Value0, Values...>, \
Adapter<C<T0, T1, T2, Value0, Values...>, Substituted, NN>> type; \
}
#endif
Vc_DEFINE_NONTYPE_REPLACETYPES_(bool);
Vc_DEFINE_NONTYPE_REPLACETYPES_(wchar_t);
Vc_DEFINE_NONTYPE_REPLACETYPES_(char);
Vc_DEFINE_NONTYPE_REPLACETYPES_( signed char);
Vc_DEFINE_NONTYPE_REPLACETYPES_(unsigned char);
Vc_DEFINE_NONTYPE_REPLACETYPES_( signed short);
Vc_DEFINE_NONTYPE_REPLACETYPES_(unsigned short);
Vc_DEFINE_NONTYPE_REPLACETYPES_( signed int);
Vc_DEFINE_NONTYPE_REPLACETYPES_(unsigned int);
Vc_DEFINE_NONTYPE_REPLACETYPES_( signed long);
Vc_DEFINE_NONTYPE_REPLACETYPES_(unsigned long);
Vc_DEFINE_NONTYPE_REPLACETYPES_( signed long long);
Vc_DEFINE_NONTYPE_REPLACETYPES_(unsigned long long);
#undef Vc_DEFINE_NONTYPE_REPLACETYPES_
namespace preferred_construction_impl
{
template <typename T> T create();
template <class Type, class... Init, class = decltype(Type(create<Init>()...))>
constexpr std::integral_constant<int, 0> test(int);
template <class Type, class... Init, class = decltype(Type{create<Init>()...})>
constexpr std::integral_constant<int, 1> test(float);
template <class Type, class... Init, class T, class = decltype(Type{{create<Init>()...}})>
constexpr std::integral_constant<int, 2> test(T);
template <class Type, class... Init> constexpr std::integral_constant<int, 3> test(...);
}
template <class Type, class... Init>
constexpr inline decltype(preferred_construction_impl::test<Type, Init...>(0))
preferred_construction()
{
return {};
}
template <size_t I, typename T,
typename R = decltype(std::declval<T &>().template vc_get_<I>())>
R get_dispatcher(T &x, void * = nullptr)
{
return x.template vc_get_<I>();
}
template <size_t I, typename T,
typename R = decltype(std::declval<const T &>().template vc_get_<I>())>
R get_dispatcher(const T &x, void * = nullptr)
{
return x.template vc_get_<I>();
}
template <size_t I, typename T, typename R = decltype(std::get<I>(std::declval<T &>()))>
R get_dispatcher(T &x, int = 0)
{
return std::get<I>(x);
}
template <size_t I, typename T,
typename R = decltype(std::get<I>(std::declval<const T &>()))>
R get_dispatcher(const T &x, int = 0)
{
return std::get<I>(x);
}
template <class... Ts> struct homogeneous_sizeof;
template <class T, class = void> struct homogeneous_sizeof_one;
template <class T, size_t... Is>
std::integral_constant<size_t,
homogeneous_sizeof<typename std::remove_reference<decltype(
get_dispatcher<Is>(std::declval<T>()))>::type...>::value>
homogeneous_sizeof_helper(index_sequence<Is...>);
template <class T>
struct homogeneous_sizeof_one<T,
typename std::enable_if<std::is_arithmetic<T>::value>::type>
: std::integral_constant<size_t, sizeof(T)> {
};
template <class T>
struct homogeneous_sizeof_one<T, typename std::enable_if<std::is_class<T>::value>::type>
: decltype(homogeneous_sizeof_helper<T>(
make_index_sequence<determine_tuple_size_<T>::value>())) {
};
template <class T0> struct homogeneous_sizeof<T0> : homogeneous_sizeof_one<T0> {
};
template <class T0, class... Ts>
struct homogeneous_sizeof<T0, Ts...>
: std::integral_constant<size_t, homogeneous_sizeof<T0>::value ==
homogeneous_sizeof<Ts...>::value
? homogeneous_sizeof<T0>::value
: 0> {
};
template <typename Scalar, typename Base, size_t N> class Adapter : public Base
{
private:
template <std::size_t... Indexes, int X>
Adapter(Vc::index_sequence<Indexes...>, const Scalar,
std::integral_constant<int, X>)
{
static_assert(
X < 3, "Failed to construct an object of type Base. Neither via "
"parenthesis-init, brace-init, nor double-brace init appear to work.");
}
template <std::size_t... Indexes>
Adapter(Vc::index_sequence<Indexes...>, const Scalar &x_,
std::integral_constant<int, 2>)
: Base{{get_dispatcher<Indexes>(x_)...}}
{
}
template <std::size_t... Indexes>
Adapter(Vc::index_sequence<Indexes...>, const Scalar &x_,
std::integral_constant<int, 1>)
: Base{get_dispatcher<Indexes>(x_)...}
{
}
template <std::size_t... Indexes>
Adapter(Vc::index_sequence<Indexes...>, const Scalar &x_,
std::integral_constant<int, 0>)
: Base(get_dispatcher<Indexes>(x_)...)
{
}
template <std::size_t... Indexes>
Adapter(Vc::index_sequence<Indexes...> seq_, const Scalar &x_)
: Adapter(seq_, x_,
preferred_construction<Base, decltype(get_dispatcher<Indexes>(
std::declval<const Scalar &>()))...>())
{
}
public:
static constexpr size_t size() { return N; }
static constexpr size_t Size = N;
using base_type = Base;
using scalar_type = Scalar;
Adapter() = default;
#if defined Vc_CLANG && Vc_CLANG < 0x30700
Vc_INTRINSIC Adapter(const Adapter &x) : Base(x) {}
#else
Adapter(const Adapter &) = default;
#endif
Adapter(Adapter &&) = default;
Adapter &operator=(const Adapter &) = default;
Adapter &operator=(Adapter &&) = default;
template <typename U, size_t TupleSize = determine_tuple_size_<Scalar>::value,
typename Seq = Vc::make_index_sequence<TupleSize>,
typename = enable_if<std::is_convertible<U, Scalar>::value>>
Adapter(U &&x_)
: Adapter(Seq(), static_cast<const Scalar &>(x_))
{
}
template <class F,
class = decltype(static_cast<Scalar>(std::declval<F>()(
size_t())))>
Adapter(F &&fun)
{
for (size_t i = 0; i < N; ++i) {
assign(*this, i, fun(i));
}
}
template <typename A0, typename... Args,
typename = typename std::enable_if<
!Traits::is_index_sequence<A0>::value &&
(sizeof...(Args) > 0 || !std::is_convertible<A0, Scalar>::value)>::type>
Adapter(A0 &&arg0_, Args &&... arguments_)
: Base(std::forward<A0>(arg0_), std::forward<Args>(arguments_)...)
{
}
template <typename T,
typename = decltype(Base(std::declval<const std::initializer_list<T> &>()))>
Adapter(const std::initializer_list<T> &l_)
: Base(l_)
{
}
void *operator new(size_t size)
{
return Vc::Common::aligned_malloc<alignof(Adapter)>(size);
}
void *operator new(size_t, void *p_) { return p_; }
void *operator new[](size_t size)
{
return Vc::Common::aligned_malloc<alignof(Adapter)>(size);
}
void *operator new[](size_t , void *p_) { return p_; }
void operator delete(void *ptr_, size_t) { Vc::Common::free(ptr_); }
void operator delete(void *, void *) {}
void operator delete[](void *ptr_, size_t) { Vc::Common::free(ptr_); }
void operator delete[](void *, void *) {}
};
template <class... TTypes, class... TTypesV, class... UTypes, class... UTypesV, size_t N>
inline void operator==(
const Adapter<std::tuple<TTypes...>, std::tuple<TTypesV...>, N> &t,
const Adapter<std::tuple<UTypes...>, std::tuple<UTypesV...>, N> &u) = delete;
template <class... TTypes, class... TTypesV, class... UTypes, class... UTypesV, size_t N>
inline void operator!=(
const Adapter<std::tuple<TTypes...>, std::tuple<TTypesV...>, N> &t,
const Adapter<std::tuple<UTypes...>, std::tuple<UTypesV...>, N> &u) = delete;
template <class... TTypes, class... TTypesV, class... UTypes, class... UTypesV, size_t N>
inline void operator<=(
const Adapter<std::tuple<TTypes...>, std::tuple<TTypesV...>, N> &t,
const Adapter<std::tuple<UTypes...>, std::tuple<UTypesV...>, N> &u) = delete;
template <class... TTypes, class... TTypesV, class... UTypes, class... UTypesV, size_t N>
inline void operator>=(
const Adapter<std::tuple<TTypes...>, std::tuple<TTypesV...>, N> &t,
const Adapter<std::tuple<UTypes...>, std::tuple<UTypesV...>, N> &u) = delete;
template <class... TTypes, class... TTypesV, class... UTypes, class... UTypesV, size_t N>
inline void operator<(
const Adapter<std::tuple<TTypes...>, std::tuple<TTypesV...>, N> &t,
const Adapter<std::tuple<UTypes...>, std::tuple<UTypesV...>, N> &u) = delete;
template <class... TTypes, class... TTypesV, class... UTypes, class... UTypesV, size_t N>
inline void operator>(
const Adapter<std::tuple<TTypes...>, std::tuple<TTypesV...>, N> &t,
const Adapter<std::tuple<UTypes...>, std::tuple<UTypesV...>, N> &u) = delete;
}
}
namespace std
{
template <typename Scalar, typename Base, size_t N>
class tuple_size<Vc::SimdizeDetail::Adapter<Scalar, Base, N>> : public tuple_size<Base>
{
};
template <size_t I, typename Scalar, typename Base, size_t N>
class tuple_element<I, Vc::SimdizeDetail::Adapter<Scalar, Base, N>>
: public tuple_element<I, Base>
{
};
template <typename S, typename T, size_t N>
class allocator<Vc::SimdizeDetail::Adapter<S, T, N>>
: public Vc::Allocator<Vc::SimdizeDetail::Adapter<S, T, N>>
{
public:
template <typename U> struct rebind
{
typedef std::allocator<U> other;
};
};
}
namespace Vc_VERSIONED_NAMESPACE
{
namespace SimdizeDetail
{
template <typename T> static inline T decay_workaround(const T &x) { return x; }
template <typename S, typename T, size_t N, size_t... Indexes>
inline void assign_impl(Adapter<S, T, N> &a, size_t i, const S &x,
Vc::index_sequence<Indexes...>)
{
const std::tuple<decltype(decay_workaround(get_dispatcher<Indexes>(x)))...> tmp(
decay_workaround(get_dispatcher<Indexes>(x))...);
auto &&unused = {(get_dispatcher<Indexes>(a)[i] = get_dispatcher<Indexes>(tmp), 0)...};
if (&unused == &unused) {}
}
template <class S, class... Args>
S construct(std::integral_constant<int, 0>, Args &&... args)
{
return S(std::forward<Args>(args)...);
}
template <class S, class... Args>
S construct(std::integral_constant<int, 1>, Args &&... args)
{
return S{std::forward<Args>(args)...};
}
template <class S, class... Args>
S construct(std::integral_constant<int, 2>, Args &&... args)
{
return S{{std::forward<Args>(args)...}};
}
template <typename S, typename T, size_t N, size_t... Indexes>
inline S extract_impl(const Adapter<S, T, N> &a, size_t i, Vc::index_sequence<Indexes...>)
{
const std::tuple<decltype(decay_workaround(get_dispatcher<Indexes>(a)[i]))...> tmp(
decay_workaround(get_dispatcher<Indexes>(a)[i])...);
return construct<S>(
preferred_construction<S, decltype(decay_workaround(
get_dispatcher<Indexes>(a)[i]))...>(),
decay_workaround(get_dispatcher<Indexes>(a)[i])...);
}
template <typename S, typename T, std::size_t N, std::size_t... Indexes>
inline Adapter<S, T, N> shifted_impl(const Adapter<S, T, N> &a, int shift,
Vc::index_sequence<Indexes...>)
{
Adapter<S, T, N> r;
auto &&unused = {(get_dispatcher<Indexes>(r) = get_dispatcher<Indexes>(a).shifted(shift), 0)...};
if (&unused == &unused) {}
return r;
}
template <typename S, typename T, size_t N>
inline Adapter<S, T, N> shifted(const Adapter<S, T, N> &a, int shift)
{
return shifted_impl(a, shift, Vc::make_index_sequence<determine_tuple_size<T>()>());
}
template <typename S, typename T, std::size_t N, std::size_t... Indexes>
inline void swap_impl(Adapter<S, T, N> &a, std::size_t i, S &x,
Vc::index_sequence<Indexes...>)
{
const auto &a_const = a;
const std::tuple<decltype(decay_workaround(get_dispatcher<Indexes>(a_const)[0]))...>
tmp{decay_workaround(get_dispatcher<Indexes>(a_const)[i])...};
auto &&unused = {(get_dispatcher<Indexes>(a)[i] = get_dispatcher<Indexes>(x), 0)...};
auto &&unused2 = {(get_dispatcher<Indexes>(x) = get_dispatcher<Indexes>(tmp), 0)...};
if (&unused == &unused2) {}
}
template <typename S, typename T, std::size_t N, std::size_t... Indexes>
inline void swap_impl(Adapter<S, T, N> &a, std::size_t i, Adapter<S, T, N> &b,
std::size_t j, Vc::index_sequence<Indexes...>)
{
const auto &a_const = a;
const auto &b_const = b;
const std::tuple<decltype(decay_workaround(get_dispatcher<Indexes>(a_const)[0]))...>
tmp{decay_workaround(get_dispatcher<Indexes>(a_const)[i])...};
auto &&unused = {(get_dispatcher<Indexes>(a)[i] = get_dispatcher<Indexes>(b_const)[j], 0)...};
auto &&unused2 = {(get_dispatcher<Indexes>(b)[j] = get_dispatcher<Indexes>(tmp), 0)...};
if (&unused == &unused2) {}
}
template <typename S, typename T, std::size_t N>
inline void swap(Adapter<S, T, N> &a, std::size_t i, S &x)
{
swap_impl(a, i, x, Vc::make_index_sequence<determine_tuple_size<T>()>());
}
template <typename S, typename T, std::size_t N>
inline void swap(Adapter<S, T, N> &a, std::size_t i, Adapter<S, T, N> &b, std::size_t j)
{
swap_impl(a, i, b, j, Vc::make_index_sequence<determine_tuple_size<T>()>());
}
template <typename A> class Scalar
{
using reference = typename std::add_lvalue_reference<A>::type;
using S = typename A::scalar_type;
using IndexSeq = Vc::make_index_sequence<determine_tuple_size<S>()>;
public:
Scalar(reference aa, size_t ii) : a(aa), i(ii) {}
Scalar(const Scalar &) = delete;
Scalar(Scalar &&) = delete;
Scalar &operator=(const Scalar &) = delete;
Scalar &operator=(Scalar &&) = delete;
void operator=(const S &x) { assign_impl(a, i, x, IndexSeq()); }
operator S() const { return extract_impl(a, i, IndexSeq()); }
template <typename AA>
friend inline void swap(Scalar<AA> &&a, typename AA::scalar_type &b);
template <typename AA>
friend inline void swap(typename AA::scalar_type &b, Scalar<AA> &&a);
template <typename AA> friend inline void swap(Scalar<AA> &&a, Scalar<AA> &&b);
private:
reference a;
size_t i;
};
template <typename A> inline void swap(Scalar<A> &&a, typename A::scalar_type &b)
{
swap_impl(a.a, a.i, b, typename Scalar<A>::IndexSeq());
}
template <typename A> inline void swap(typename A::scalar_type &b, Scalar<A> &&a)
{
swap_impl(a.a, a.i, b, typename Scalar<A>::IndexSeq());
}
template <typename A> inline void swap(Scalar<A> &&a, Scalar<A> &&b)
{
swap_impl(a.a, a.i, b.a, b.i, typename Scalar<A>::IndexSeq());
}
template <class S, class T, size_t N, size_t... I>
inline void load_interleaved_impl(Vc::index_sequence<I...>, Adapter<S, T, N> &a,
const S *mem)
{
const InterleavedMemoryWrapper<S, decltype(decay_workaround(get_dispatcher<0>(a)))>
wrapper(const_cast<S *>(mem));
Vc::tie(get_dispatcher<I>(a)...) = wrapper[0];
}
template <class S, class T, size_t N, size_t... I>
inline void store_interleaved_impl(Vc::index_sequence<I...>, const Adapter<S, T, N> &a,
S *mem)
{
InterleavedMemoryWrapper<S, decltype(decay_workaround(get_dispatcher<0>(a)))> wrapper(
mem);
wrapper[0] = Vc::tie(get_dispatcher<I>(a)...);
}
template <typename A> class Interface
{
using reference = typename std::add_lvalue_reference<A>::type;
using IndexSeq =
Vc::make_index_sequence<determine_tuple_size<typename A::scalar_type>()>;
public:
Interface(reference aa) : a(aa) {}
Scalar<A> operator[](size_t i)
{
return {a, i};
}
typename A::scalar_type operator[](size_t i) const
{
return extract_impl(a, i, IndexSeq());
}
A shifted(int amount) const
{
return shifted_impl(a, amount, IndexSeq());
}
void load(const typename A::scalar_type *mem) { load_interleaved(*this, mem); }
void store(typename A::scalar_type *mem) { store_interleaved(*this, mem); }
private:
reference a;
};
}
template <typename S, typename T, size_t N>
inline void assign(SimdizeDetail::Adapter<S, T, N> &a, size_t i, const S &x)
{
SimdizeDetail::assign_impl(
a, i, x, Vc::make_index_sequence<SimdizeDetail::determine_tuple_size<T>()>());
}
template <typename V, typename = enable_if<Traits::is_simd_vector<V>::value>>
Vc_INTRINSIC void assign(V &v, size_t i, typename V::EntryType x)
{
v[i] = x;
}
template <typename S, typename T, size_t N>
inline S extract(const SimdizeDetail::Adapter<S, T, N> &a, size_t i)
{
return SimdizeDetail::extract_impl(
a, i, Vc::make_index_sequence<SimdizeDetail::determine_tuple_size<S>()>());
}
template <typename V, typename = enable_if<Traits::is_simd_vector<V>::value>>
Vc_INTRINSIC typename V::EntryType extract(const V &v, size_t i)
{
return v[i];
}
template <class S, class T, size_t N>
inline void load_interleaved(SimdizeDetail::Adapter<S, T, N> &a, const S *mem)
{
if (SimdizeDetail::homogeneous_sizeof<S>::value == 0) {
Common::unrolled_loop<std::size_t, 0, N>(
[&](std::size_t i) { assign(a, i, mem[i]); });
} else {
constexpr size_t TupleSize = SimdizeDetail::determine_tuple_size_<S>::value;
SimdizeDetail::load_interleaved_impl(Vc::make_index_sequence<TupleSize>(), a,
mem);
}
}
template <
class V, class T,
class = enable_if<Traits::is_simd_vector<V>::value && std::is_arithmetic<T>::value>>
Vc_INTRINSIC void load_interleaved(V &a, const T *mem)
{
a.load(mem, Vc::Unaligned);
}
template <class S, class T, size_t N>
inline void store_interleaved(const SimdizeDetail::Adapter<S, T, N> &a, S *mem)
{
if (SimdizeDetail::homogeneous_sizeof<S>::value == 0) {
Common::unrolled_loop<std::size_t, 0, N>(
[&](std::size_t i) { mem[i] = extract(a, i); });
} else {
constexpr size_t TupleSize = SimdizeDetail::determine_tuple_size_<S>::value;
SimdizeDetail::store_interleaved_impl(Vc::make_index_sequence<TupleSize>(), a,
mem);
}
}
template <
class V, class T,
class = enable_if<Traits::is_simd_vector<V>::value && std::is_arithmetic<T>::value>>
Vc_INTRINSIC void store_interleaved(const V &a, T *mem)
{
a.store(mem, Vc::Unaligned);
}
template <typename S, typename T, size_t N>
SimdizeDetail::Interface<SimdizeDetail::Adapter<S, T, N>> decorate(
SimdizeDetail::Adapter<S, T, N> &a)
{
return {a};
}
template <typename S, typename T, size_t N>
const SimdizeDetail::Interface<const SimdizeDetail::Adapter<S, T, N>> decorate(
const SimdizeDetail::Adapter<S, T, N> &a)
{
return {a};
}
template <class V, class = typename std::enable_if<
Traits::is_simd_vector<typename std::decay<V>::type>::value>>
V &&decorate(V &&v)
{
return std::forward<V>(v);
}
namespace SimdizeDetail
{
namespace IteratorDetails
{
enum class Mutable { Yes, No };
template <typename It, typename V, size_t I, size_t End>
Vc_INTRINSIC V fromIteratorImpl(enable_if<(I == End), It>)
{
return {};
}
template <typename It, typename V, size_t I, size_t End>
Vc_INTRINSIC V fromIteratorImpl(enable_if<(I < End), It> it)
{
V r = fromIteratorImpl<It, V, I + 1, End>(it);
Traits::decay<decltype(get_dispatcher<I>(r))> tmp;
for (size_t j = 0; j < V::size(); ++j, ++it) {
tmp[j] = get_dispatcher<I>(*it);
}
get_dispatcher<I>(r) = tmp;
return r;
}
template <typename It, typename V>
Vc_INTRINSIC V fromIterator(enable_if<!Traits::is_simd_vector<V>::value, const It &> it)
{
return fromIteratorImpl<It, V, 0, determine_tuple_size<V>()>(it);
}
template <typename It, typename V>
Vc_INTRINSIC V fromIterator(enable_if<Traits::is_simd_vector<V>::value, It> it)
{
V r;
for (size_t j = 0; j < V::size(); ++j, ++it) {
r[j] = *it;
}
return r;
}
template <typename T, typename value_vector, Mutable> class Pointer;
template <typename T, typename value_vector> class Pointer<T, value_vector, Mutable::Yes>
{
static constexpr auto Size = value_vector::size();
public:
value_vector *operator->() { return &data; }
Pointer() = delete;
Pointer(const Pointer &) = delete;
Pointer &operator=(const Pointer &) = delete;
Pointer &operator=(Pointer &&) = delete;
Pointer(Pointer &&) = default;
~Pointer()
{
for (size_t i = 0; i < Size; ++i, ++begin_iterator) {
*begin_iterator = extract(data, i);
}
}
Pointer(const T &it) : data(fromIterator<T, value_vector>(it)), begin_iterator(it) {}
private:
value_vector data;
T begin_iterator;
};
template <typename T, typename value_vector> class Pointer<T, value_vector, Mutable::No>
{
static constexpr auto Size = value_vector::size();
public:
const value_vector *operator->() const { return &data; }
Pointer() = delete;
Pointer(const Pointer &) = delete;
Pointer &operator=(const Pointer &) = delete;
Pointer &operator=(Pointer &&) = delete;
Pointer(Pointer &&) = default;
Pointer(const T &it) : data(fromIterator<T, value_vector>(it)) {}
private:
value_vector data;
};
template <typename T, typename value_vector, Mutable M> class Reference;
template <typename T, typename value_vector>
class Reference<T, value_vector, Mutable::Yes> : public value_vector
{
static constexpr auto Size = value_vector::size();
using reference = typename std::add_lvalue_reference<T>::type;
reference scalar_it;
public:
Reference(reference first_it)
: value_vector(fromIterator<T, value_vector>(first_it)), scalar_it(first_it)
{
}
Reference(const Reference &) = delete;
Reference(Reference &&) = default;
Reference &operator=(const Reference &) = delete;
Reference &operator=(Reference &&) = delete;
void operator=(const value_vector &x)
{
static_cast<value_vector &>(*this) = x;
auto it = scalar_it;
for (size_t i = 0; i < Size; ++i, ++it) {
*it = extract(x, i);
}
}
};
#define Vc_OP(op_) \
template <typename T0, typename V0, typename T1, typename V1> \
decltype(std::declval<const V0 &>() op_ std::declval<const V1 &>()) operator op_( \
const Reference<T0, V0, Mutable::Yes> &x, \
const Reference<T1, V1, Mutable::Yes> &y) \
{ \
return static_cast<const V0 &>(x) op_ static_cast<const V1 &>(y); \
}
Vc_ALL_COMPARES(Vc_OP);
Vc_ALL_ARITHMETICS(Vc_OP);
Vc_ALL_BINARY(Vc_OP);
Vc_ALL_LOGICAL(Vc_OP);
Vc_ALL_SHIFTS(Vc_OP);
#undef Vc_OP
template <typename T, typename value_vector>
class Reference<T, value_vector, Mutable::No> : public value_vector
{
static constexpr auto Size = value_vector::size();
public:
Reference(const T &it) : value_vector(fromIterator<T, value_vector>(it)) {}
Reference(const Reference &) = delete;
Reference(Reference &&) = default;
Reference &operator=(const Reference &) = delete;
Reference &operator=(Reference &&) = delete;
void operator=(const value_vector &x) = delete;
};
template <typename T, size_t N,
IteratorDetails::Mutable M =
(Traits::is_output_iterator<T>::value ? Mutable::Yes : Mutable::No),
typename V = simdize<typename std::iterator_traits<T>::value_type, N>,
size_t Size = V::Size,
typename = typename std::iterator_traits<T>::iterator_category>
class Iterator;
template <typename T, size_t N, IteratorDetails::Mutable M, typename V, size_t Size_>
class Iterator<T, N, M, V, Size_, std::forward_iterator_tag>
: public std::iterator<typename std::iterator_traits<T>::iterator_category, V,
typename std::iterator_traits<T>::difference_type,
IteratorDetails::Pointer<T, V, M>,
IteratorDetails::Reference<T, V, M>>
{
public:
using pointer = IteratorDetails::Pointer<T, V, M>;
using reference = IteratorDetails::Reference<T, V, M>;
using const_pointer = IteratorDetails::Pointer<T, V, IteratorDetails::Mutable::No>;
using const_reference =
IteratorDetails::Reference<T, V, IteratorDetails::Mutable::No>;
static constexpr std::size_t size() { return Size_; }
static constexpr std::size_t Size = Size_;
Iterator() = default;
Iterator(const T &x) : scalar_it(x) {}
Iterator(T &&x) : scalar_it(std::move(x)) {}
Iterator &operator=(const T &x)
{
scalar_it = x;
return *this;
}
Iterator &operator=(T &&x)
{
scalar_it = std::move(x);
return *this;
}
Iterator(const Iterator &) = default;
Iterator(Iterator &&) = default;
Iterator &operator=(const Iterator &) = default;
Iterator &operator=(Iterator &&) = default;
Iterator &operator++()
{
std::advance(scalar_it, Size);
return *this;
}
Iterator operator++(int)
{
Iterator copy(*this);
operator++();
return copy;
}
bool operator==(const Iterator &rhs) const
{
#ifndef NDEBUG
if (scalar_it == rhs.scalar_it) {
return true;
} else {
T it(scalar_it);
for (size_t i = 1; i < Size; ++i) {
Vc_ASSERT((++it != rhs.scalar_it));
}
return false;
}
#else
return scalar_it == rhs.scalar_it;
#endif
}
bool operator!=(const Iterator &rhs) const
{
return !operator==(rhs);
}
pointer operator->() { return scalar_it; }
reference operator*() { return scalar_it; }
const_pointer operator->() const { return scalar_it; }
const_reference operator*() const { return scalar_it; }
operator const T &() const { return scalar_it; }
protected:
T scalar_it;
};
template <typename T, size_t N, IteratorDetails::Mutable M, typename V, size_t Size>
class Iterator<T, N, M, V, Size, std::bidirectional_iterator_tag>
: public Iterator<T, N, M, V, Size, std::forward_iterator_tag>
{
using Base = Iterator<T, N, M, V, Size, std::forward_iterator_tag>;
protected:
using Base::scalar_it;
public:
using pointer = typename Base::pointer;
using reference = typename Base::reference;
using const_pointer = typename Base::const_pointer;
using const_reference = typename Base::const_reference;
using Iterator<T, N, M, V, Size,
std::forward_iterator_tag>::Iterator;
Iterator &operator--()
{
std::advance(scalar_it, -Size);
return *this;
}
Iterator operator--(int)
{
Iterator copy(*this);
operator--();
return copy;
}
};
template <typename T, size_t N, IteratorDetails::Mutable M, typename V, size_t Size>
class Iterator<T, N, M, V, Size, std::random_access_iterator_tag>
: public Iterator<T, N, M, V, Size, std::bidirectional_iterator_tag>
{
using Base = Iterator<T, N, M, V, Size, std::bidirectional_iterator_tag>;
protected:
using Base::scalar_it;
public:
using pointer = typename Base::pointer;
using reference = typename Base::reference;
using const_pointer = typename Base::const_pointer;
using const_reference = typename Base::const_reference;
using difference_type = typename std::iterator_traits<T>::difference_type;
using Iterator<T, N, M, V, Size, std::bidirectional_iterator_tag>::
Iterator;
Iterator &operator+=(difference_type n)
{
scalar_it += n * difference_type(Size);
return *this;
}
Iterator operator+(difference_type n) const { return Iterator(*this) += n; }
Iterator &operator-=(difference_type n)
{
scalar_it -= n * difference_type(Size);
return *this;
}
Iterator operator-(difference_type n) const { return Iterator(*this) -= n; }
difference_type operator-(const Iterator &rhs) const
{
constexpr difference_type n = Size;
Vc_ASSERT((scalar_it - rhs.scalar_it) % n ==
0);
return (scalar_it - rhs.scalar_it) / n;
}
bool operator<(const Iterator &rhs) const
{
return rhs.scalar_it - scalar_it >= difference_type(Size);
}
bool operator>(const Iterator &rhs) const
{
return scalar_it - rhs.scalar_it >= difference_type(Size);
}
bool operator<=(const Iterator &rhs) const
{
return rhs.scalar_it - scalar_it >= difference_type(Size) - 1;
}
bool operator>=(const Iterator &rhs) const
{
return scalar_it - rhs.scalar_it >= difference_type(Size) - 1;
}
reference operator[](difference_type i) { return *(*this + i); }
const_reference operator[](difference_type i) const { return *(*this + i); }
};
template <typename T, size_t N, IteratorDetails::Mutable M, typename V, size_t Size>
Iterator<T, N, M, V, Size, std::random_access_iterator_tag> operator+(
typename Iterator<T, N, M, V, Size, std::random_access_iterator_tag>::difference_type
n,
const Iterator<T, N, M, V, Size, std::random_access_iterator_tag> &i)
{
return i + n;
}
}
template <typename T, size_t N, typename MT>
struct ReplaceTypes<T, N, MT, Category::ForwardIterator>
{
using type = IteratorDetails::Iterator<T, N>;
};
template <typename T, size_t N, typename MT>
struct ReplaceTypes<T, N, MT, Category::BidirectionalIterator>
{
using type = IteratorDetails::Iterator<T, N>;
};
template <typename T, size_t N, typename MT>
struct ReplaceTypes<T, N, MT, Category::RandomAccessIterator>
{
using type = IteratorDetails::Iterator<T, N>;
};
template <Vc::Operator Op, typename S, typename T, std::size_t N, typename M, typename U,
std::size_t Offset>
Vc_INTRINSIC Vc::enable_if<(Offset >= determine_tuple_size_<S>::value && M::Size == N), void>
conditional_assign(Adapter<S, T, N> &, const M &, const U &)
{
}
template <Vc::Operator Op, typename S, typename T, std::size_t N, typename M, typename U,
std::size_t Offset = 0>
Vc_INTRINSIC Vc::enable_if<(Offset < determine_tuple_size_<S>::value && M::Size == N), void>
conditional_assign(Adapter<S, T, N> &lhs, const M &mask, const U &rhs)
{
using V = typename std::decay<decltype(get_dispatcher<Offset>(lhs))>::type;
using M2 = typename V::mask_type;
conditional_assign<Op>(get_dispatcher<Offset>(lhs), simd_cast<M2>(mask), get_dispatcher<Offset>(rhs));
conditional_assign<Op, S, T, N, M, U, Offset + 1>(lhs, mask, rhs);
}
template <Vc::Operator Op, typename S, typename T, std::size_t N, typename M,
std::size_t Offset>
Vc_INTRINSIC Vc::enable_if<(Offset >= determine_tuple_size_<S>::value && M::Size == N), void>
conditional_assign(Adapter<S, T, N> &, const M &)
{
}
template <Vc::Operator Op, typename S, typename T, std::size_t N, typename M,
std::size_t Offset = 0>
Vc_INTRINSIC Vc::enable_if<(Offset < determine_tuple_size_<S>::value && M::Size == N), void>
conditional_assign(Adapter<S, T, N> &lhs, const M &mask)
{
using V = typename std::decay<decltype(get_dispatcher<Offset>(lhs))>::type;
using M2 = typename V::mask_type;
conditional_assign<Op>(get_dispatcher<Offset>(lhs), simd_cast<M2>(mask));
conditional_assign<Op, S, T, N, M, Offset + 1>(lhs, mask);
}
}
template <typename T, size_t N = 0, typename MT = void>
using simdize = SimdizeDetail::simdize<T, N, MT>;
#define Vc_SIMDIZE_INTERFACE(MEMBERS_) \
template <std::size_t N_> \
inline auto vc_get_()->decltype(std::get<N_>(std::tie MEMBERS_)) \
{ \
return std::get<N_>(std::tie MEMBERS_); \
} \
template <std::size_t N_> \
inline auto vc_get_() const->decltype(std::get<N_>(std::tie MEMBERS_)) \
{ \
return std::get<N_>(std::tie MEMBERS_); \
} \
enum : std::size_t { \
tuple_size = std::tuple_size<decltype(std::make_tuple MEMBERS_)>::value \
}
}
namespace std
{
using Vc::SimdizeDetail::swap;
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
template<typename Mask> constexpr bool all_of(const Mask &m) { return m.isFull(); }
constexpr bool all_of(bool b) { return b; }
template<typename Mask> constexpr bool any_of(const Mask &m) { return m.isNotEmpty(); }
constexpr bool any_of(bool b) { return b; }
template<typename Mask> constexpr bool none_of(const Mask &m) { return m.isEmpty(); }
constexpr bool none_of(bool b) { return !b; }
template<typename Mask> constexpr bool some_of(const Mask &m) { return m.isMix(); }
constexpr bool some_of(bool) { return false; }
#ifdef DOXYGEN
template <class InputIt, class UnaryFunction>
UnaryFunction simd_for_each(InputIt first, InputIt last, UnaryFunction f);
#else
template <class InputIt, class UnaryFunction,
class ValueType = typename std::iterator_traits<InputIt>::value_type>
inline enable_if<
Traits::is_functor_argument_immutable<UnaryFunction, simdize<ValueType>>::value,
UnaryFunction>
simd_for_each(InputIt first, InputIt last, UnaryFunction f)
{
typedef simdize<ValueType> V;
typedef simdize<ValueType, 1> V1;
const auto lastV = last - V::Size + 1;
for (; first < lastV; first += V::Size) {
V tmp;
load_interleaved(tmp, std::addressof(*first));
f(tmp);
}
for (; first != last; ++first) {
V1 tmp;
load_interleaved(tmp, std::addressof(*first));
f(tmp);
}
return std::move(f);
}
template <typename InputIt, typename UnaryFunction,
class ValueType = typename std::iterator_traits<InputIt>::value_type>
inline enable_if<
!Traits::is_functor_argument_immutable<UnaryFunction, simdize<ValueType>>::value,
UnaryFunction>
simd_for_each(InputIt first, InputIt last, UnaryFunction f)
{
typedef simdize<ValueType> V;
typedef simdize<ValueType, 1> V1;
const auto lastV = last - V::size() + 1;
for (; first < lastV; first += V::size()) {
V tmp;
load_interleaved(tmp, std::addressof(*first));
f(tmp);
store_interleaved(tmp, std::addressof(*first));
}
for (; first != last; ++first) {
V1 tmp;
load_interleaved(tmp, std::addressof(*first));
f(tmp);
store_interleaved(tmp, std::addressof(*first));
}
return std::move(f);
}
#endif
template <typename InputIt, typename UnaryFunction,
class ValueType = typename std::iterator_traits<InputIt>::value_type>
inline enable_if<
Traits::is_functor_argument_immutable<UnaryFunction, simdize<ValueType>>::value,
UnaryFunction>
simd_for_each_n(InputIt first, std::size_t count, UnaryFunction f)
{
typename std::make_signed<size_t>::type len = count;
typedef simdize<ValueType> V;
typedef simdize<ValueType, 1> V1;
for (; len >= int(V::size()); len -= V::Size, first += V::Size) {
V tmp;
load_interleaved(tmp, std::addressof(*first));
f(tmp);
}
for (; len != 0; --len, ++first) {
V1 tmp;
load_interleaved(tmp, std::addressof(*first));
f(tmp);
}
return std::move(f);
}
template <typename InputIt, typename UnaryFunction,
class ValueType = typename std::iterator_traits<InputIt>::value_type>
inline enable_if<
!Traits::is_functor_argument_immutable<UnaryFunction, simdize<ValueType>>::value,
UnaryFunction>
simd_for_each_n(InputIt first, std::size_t count, UnaryFunction f)
{
typename std::make_signed<size_t>::type len = count;
typedef simdize<ValueType> V;
typedef simdize<ValueType, 1> V1;
for (; len >= int(V::size()); len -= V::Size, first += V::Size) {
V tmp;
load_interleaved(tmp, std::addressof(*first));
f(tmp);
store_interleaved(tmp, std::addressof(*first));
}
for (; len != 0; --len, ++first) {
V1 tmp;
load_interleaved(tmp, std::addressof(*first));
f(tmp);
store_interleaved(tmp, std::addressof(*first));
}
return std::move(f);
}
}
#endif
#ifndef VC_COMMON_IIF_H_
#define VC_COMMON_IIF_H_ 
#ifndef VC_TYPE_TRAITS_
#define VC_TYPE_TRAITS_ 
#include <type_traits>
namespace Vc_VERSIONED_NAMESPACE
{
using Traits::is_simd_mask;
using Traits::is_simd_vector;
using Traits::is_integral;
using Traits::is_floating_point;
using Traits::is_arithmetic;
using Traits::is_signed;
using Traits::is_unsigned;
template<typename T>
struct memory_alignment : public std::integral_constant<size_t, alignof(T)> {};
template<> struct memory_alignment<short_v> : public std::integral_constant<size_t, short_v::MemoryAlignment> {};
template<> struct memory_alignment<ushort_v> : public std::integral_constant<size_t, ushort_v::MemoryAlignment> {};
}
#endif
namespace Vc_VERSIONED_NAMESPACE
{
template <typename Mask, typename T>
Vc_ALWAYS_INLINE enable_if<is_simd_mask<Mask>::value && is_simd_vector<T>::value, T> iif(
const Mask &condition, const T &trueValue, const T &falseValue)
{
T result(falseValue);
Vc::where(condition) | result = trueValue;
return result;
}
template <typename Mask, typename T>
enable_if<is_simd_mask<Mask>::value && !is_simd_vector<T>::value, T> iif(
const Mask &, const T &, const T &) = delete;
template<typename T> constexpr T iif (bool condition, const T &trueValue, const T &falseValue)
{
return condition ? trueValue : falseValue;
}
}
#endif
#ifndef Vc_NO_STD_FUNCTIONS
namespace std
{
using Vc::min;
using Vc::max;
using Vc::abs;
using Vc::asin;
using Vc::atan;
using Vc::atan2;
using Vc::ceil;
using Vc::cos;
using Vc::exp;
using Vc::fma;
using Vc::trunc;
using Vc::floor;
using Vc::frexp;
using Vc::ldexp;
using Vc::log;
using Vc::log10;
using Vc::log2;
using Vc::round;
using Vc::sin;
using Vc::sqrt;
using Vc::isfinite;
using Vc::isnan;
}
#endif
Vc_RESET_DIAGNOSTICS
#endif
