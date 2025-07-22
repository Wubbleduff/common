
#pragma once

#ifndef MATH_SKIP_INCLUDES
#include "common.h"
#endif

// Vector structures. Not intended for storage. Only use as locals for convenience.
typedef struct v2Tag
{
    union
    {
        __m128 v;
        struct
        {
            f32 x;
            f32 y;
        };
    };
} v2;
typedef struct v3Tag
{
    union
    {
        __m128 v;
        struct
        {
            f32 x;
            f32 y;
            f32 z;
        };
    };
} v3;
typedef struct v4Tag
{
    union
    {
        __m128 v;
        struct
        {
            f32 x;
            f32 y;
            f32 z;
            f32 w;
        };
    };
} v4;


////////////////////////////////////////////////////////////////////////////////
// min
static inline u8  min_u8(u8 a, u8 b)    { return a < b ? a : b; }
static inline s8  min_s8(s8 a, s8 b)    { return a < b ? a : b; }
static inline u16 min_u16(u16 a, u16 b) { return a < b ? a : b; }
static inline s16 min_s16(s16 a, s16 b) { return a < b ? a : b; }
static inline u32 min_u32(u32 a, u32 b) { return a < b ? a : b; }
static inline s32 min_s32(s32 a, s32 b) { return a < b ? a : b; }
static inline u64 min_u64(u64 a, u64 b) { return a < b ? a : b; }
static inline s64 min_s64(s64 a, s64 b) { return a < b ? a : b; }
static inline f32 min_f32(f32 a, f32 b) { return a < b ? a : b; }
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// max
static inline u8  max_u8(u8 a, u8 b)    { return a > b ? a : b; }
static inline s8  max_s8(s8 a, s8 b)    { return a > b ? a : b; }
static inline u16 max_u16(u16 a, u16 b) { return a > b ? a : b; }
static inline s16 max_s16(s16 a, s16 b) { return a > b ? a : b; }
static inline u32 max_u32(u32 a, u32 b) { return a > b ? a : b; }
static inline s32 max_s32(s32 a, s32 b) { return a > b ? a : b; }
static inline u64 max_u64(u64 a, u64 b) { return a > b ? a : b; }
static inline s64 max_s64(s64 a, s64 b) { return a > b ? a : b; }
static inline f32 max_f32(f32 a, f32 b) { return a > b ? a : b; }
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// clamp
static inline u8  clamp_u8(u8 a, u8 min, u8 max)     { return min_u8(max_u8(a, min), max); }
static inline s8  clamp_s8(s8 a, s8 min, s8 max)     { return min_s8(max_s8(a, min), max); }
static inline u16 clamp_u16(u16 a, u16 min, u16 max) { return min_u16(max_u16(a, min), max); }
static inline s16 clamp_s16(s16 a, s16 min, s16 max) { return min_s16(max_s16(a, min), max); }
static inline u32 clamp_u32(u32 a, u32 min, u32 max) { return min_u32(max_u32(a, min), max); }
static inline s32 clamp_s32(s32 a, s32 min, s32 max) { return min_s32(max_s32(a, min), max); }
static inline u64 clamp_u64(u64 a, u64 min, u64 max) { return min_u64(max_u64(a, min), max); }
static inline s64 clamp_s64(s64 a, s64 min, s64 max) { return min_s64(max_s64(a, min), max); }
static inline f32 clamp_f32(f32 a, f32 min, f32 max) { return min_f32(max_f32(a, min), max); }
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// abs
static inline s8  abs_s8(s8 a)   { return a < 0 ? -a : a; }
static inline s16 abs_s16(s16 a) { return a < 0 ? -a : a; }
static inline s32 abs_s32(s32 a) { return a < 0 ? -a : a; }
static inline s64 abs_s64(s64 a) { return a < 0 ? -a : a; }
static inline f32 abs_f32(f32 a)
{
    return u32_bits_as_f32(f32_bits_as_u32(a) & 0x7FFFFFFF);
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// square
static inline u8  sq_u8(u8 a)   { return a * a; }
static inline s8  sq_s8(s8 a)   { return a * a; }
static inline u16 sq_u16(u16 a) { return a * a; }
static inline s16 sq_s16(s16 a) { return a * a; }
static inline u32 sq_u32(u32 a) { return a * a; }
static inline s32 sq_s32(s32 a) { return a * a; }
static inline u64 sq_u64(u64 a) { return a * a; }
static inline s64 sq_s64(s64 a) { return a * a; }
static inline f32 sq_f32(f32 a) { return a * a; }
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// round
static inline f32 round_neg_inf(f32 a)
{
    return _mm_cvtss_f32(_mm_round_ps(_mm_set1_ps(a), _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));
}

static inline f32 round_pos_inf(f32 a)
{
    return _mm_cvtss_f32(_mm_round_ps(_mm_set1_ps(a), _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC));
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// sqrt
static inline f32 sqrt_f32(f32 a)
{
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set1_ps(a)));
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// vector constructors
static inline v2 zero_v2()
{
    v2 r;
    r.v = _mm_setr_ps(0.0f, 0.0f, nan_f32(), nan_f32());
    return r;
}
static inline v3 zero_v3()
{
    v3 r;
    r.v = _mm_setr_ps(0.0f, 0.0f, 0.0f, nan_f32());
    return r;
}
static inline v4 zero_v4()
{
    v4 r;
    r.v = _mm_set1_ps(0.0f);
    return r;
}

static inline v2 make_v2(f32 x, f32 y)
{
    v2 r;
    r.v = _mm_setr_ps(x, y, nan_f32(), nan_f32());
    return r;
}
static inline v3 make_v3(f32 x, f32 y, f32 z)
{
    v3 r;
    r.v = _mm_setr_ps(x, y, z, nan_f32());
    return r;
}
static inline v4 make_v4(f32 x, f32 y, f32 z, f32 w)
{
    v4 r;
    r.v = _mm_setr_ps(x, y, z, w);
    return r;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// add
static inline v2 add_v2(v2 a, v2 b)
{
    v2 r;
    r.v = _mm_add_ps(a.v, b.v);
    return r;
}
static inline v3 add_v3(v3 a, v3 b)
{
    v3 r;
    r.v = _mm_add_ps(a.v, b.v);
    return r;
}
static inline v4 add_v4(v4 a, v4 b)
{
    v4 r;
    r.v = _mm_add_ps(a.v, b.v);
    return r;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// sub
static inline v2 sub_v2(v2 a, v2 b)
{
    v2 r;
    r.v = _mm_sub_ps(a.v, b.v);
    return r;
}
static inline v3 sub_v3(v3 a, v3 b)
{
    v3 r;
    r.v = _mm_sub_ps(a.v, b.v);
    return r;
}
static inline v4 sub_v4(v4 a, v4 b)
{
    v4 r;
    r.v = _mm_sub_ps(a.v, b.v);
    return r;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// scale
static inline v2 scale_v2(v2 a, f32 b)
{
    v2 r;
    r.v = _mm_mul_ps(a.v, _mm_set1_ps(b));
    return r;
}
static inline v3 scale_v3(v3 a, f32 b)
{
    v3 r;
    r.v = _mm_mul_ps(a.v, _mm_set1_ps(b));
    return r;
}
static inline v4 scale_v4(v4 a, f32 b)
{
    v4 r;
    r.v = _mm_mul_ps(a.v, _mm_set1_ps(b));
    return r;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// lerp
static inline f32 lerp_f32(f32 a, f32 b, f32 t)
{
    return a * (1.0f - t) + b * t;
}
static inline v2 lerp_v2(v2 a, v2 b, f32 t)
{
    v2 result;
    result.v = _mm_add_ps(
            _mm_mul_ps(_mm_sub_ps(_mm_set1_ps(1.0f), _mm_set1_ps(t)), a.v),
            _mm_mul_ps(_mm_set1_ps(t), b.v));
    return result;
}
static inline v3 lerp_v3(v3 a, v3 b, f32 t)
{
    v3 result;
    result.v = _mm_add_ps(
            _mm_mul_ps(_mm_sub_ps(_mm_set1_ps(1.0f), _mm_set1_ps(t)), a.v),
            _mm_mul_ps(_mm_set1_ps(t), b.v));
    return result;
}
static inline v4 lerp_v4(v4 a, v4 b, f32 t)
{
    v4 result;
    result.v = _mm_add_ps(
            _mm_mul_ps(_mm_sub_ps(_mm_set1_ps(1.0f), _mm_set1_ps(t)), a.v),
            _mm_mul_ps(_mm_set1_ps(t), b.v));
    return result;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// dot product
static inline f32 dot_v2(v2 a, v2 b)
{
    v2 r;
    r.v = _mm_mul_ps(a.v, b.v);
    r.v = _mm_add_ps(r.v, _mm_shuffle_ps(r.v, r.v, _MM_SHUFFLE(3, 2, 1, 1)));
    return r.x;
}
static inline f32 dot_v3(v3 a, v3 b)
{
    v3 r;
    r.v = _mm_mul_ps(a.v, b.v);
    __m128 tmp = r.v;
    r.v = _mm_add_ps(r.v, _mm_shuffle_ps(r.v, r.v, _MM_SHUFFLE(3, 2, 1, 1)));
    r.v = _mm_add_ps(r.v, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(3, 2, 1, 2)));
    return r.x;
}
static inline f32 dot_v4(v4 a, v4 b)
{
    v4 r;
    r.v = _mm_mul_ps(a.v, b.v);
    r.v = _mm_add_ps(r.v, _mm_shuffle_ps(r.v, r.v, _MM_SHUFFLE(0, 3, 2, 1)));
    r.v = _mm_add_ps(r.v, _mm_shuffle_ps(r.v, r.v, _MM_SHUFFLE(1, 0, 3, 2)));
    return r.x;
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// length
static inline f32 length_sq_v2(v2 a) { return dot_v2(a, a); }
static inline f32 length_sq_v3(v3 a) { return dot_v3(a, a); }
static inline f32 length_sq_v4(v4 a) { return dot_v4(a, a); }

static inline f32 length_v2(v2 a)
{
    return sqrt_f32(length_sq_v2(a));
}
static inline f32 length_v3(v3 a)
{
    return sqrt_f32(length_sq_v3(a));
}
static inline f32 length_v4(v4 a)
{
    return sqrt_f32(length_sq_v4(a));
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// normalize
static inline v2 normalize_v2(v2 a)
{
    v2 result;
    __m128 l2 = _mm_mul_ps(a.v, a.v);
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(l2, l2, _MM_SHUFFLE(3, 2, 0, 1)));
    result.v = _mm_div_ps(a.v, _mm_sqrt_ps(l2));
    return result;
}
static inline v3 normalize_v3(v3 a)
{
    v3 result;
    __m128 l2 = _mm_mul_ps(a.v, a.v);
    __m128 tmp = l2;
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(l2, l2, _MM_SHUFFLE(3, 0, 2, 1)));
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(3, 1, 0, 2)));
    result.v = _mm_div_ps(a.v, _mm_sqrt_ps(l2));
    return result;
}
static inline v4 normalize_v4(v4 a)
{
    v4 result;
    __m128 l2 = _mm_mul_ps(a.v, a.v);
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(l2, l2, _MM_SHUFFLE(0, 3, 2, 1)));
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(l2, l2, _MM_SHUFFLE(1, 0, 3, 2)));
    result.v = _mm_div_ps(a.v, _mm_sqrt_ps(l2));
    return result;
}

static inline v2 normalize_or_v2(v2 a, v2 def)
{
    v2 result;
    __m128 l2 = _mm_mul_ps(a.v, a.v);
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(l2, l2, _MM_SHUFFLE(3, 2, 0, 1)));
    result.v = _mm_div_ps(a.v, _mm_sqrt_ps(l2));
    result.v = _mm_blendv_ps(
        result.v,
        def.v,
        _mm_cmp_ps(l2, _mm_set1_ps(0.0f), _CMP_EQ_OQ)
    );
    return result;
}
static inline v3 normalize_or_v3(v3 a, v3 def)
{
    v3 result;
    __m128 l2 = _mm_mul_ps(a.v, a.v);
    __m128 tmp = l2;
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(l2, l2, _MM_SHUFFLE(3, 0, 2, 1)));
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(3, 1, 0, 2)));
    result.v = _mm_div_ps(a.v, _mm_sqrt_ps(l2));
    result.v = _mm_blendv_ps(
        result.v,
        def.v,
        _mm_cmp_ps(l2, _mm_set1_ps(0.0f), _CMP_EQ_OQ)
    );
    return result;
}
static inline v4 normalize_or_v4(v4 a, v4 def)
{
    v4 result;
    __m128 l2 = _mm_mul_ps(a.v, a.v);
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(l2, l2, _MM_SHUFFLE(0, 3, 2, 1)));
    l2 = _mm_add_ps(l2, _mm_shuffle_ps(l2, l2, _MM_SHUFFLE(1, 0, 3, 2)));
    result.v = _mm_div_ps(a.v, _mm_sqrt_ps(l2));
    result.v = _mm_blendv_ps(
        result.v,
        def.v,
        _mm_cmp_ps(l2, _mm_set1_ps(0.0f), _CMP_EQ_OQ)
    );
    return result;
}
////////////////////////////////////////////////////////////////////////////////
