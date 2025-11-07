
#include "math.h"

#include <stdio.h>
#include <stdarg.h>

static u32 g_num_fails = 0;

void assert_fn(const u64 c, const char* msg, ...)
{
    if(!c)
    {
        char buf[1024] = {0};
        va_list args;
        va_start(args, msg);
        vsnprintf(buf, sizeof(buf), msg, args);
        va_end(args);

        fprintf(stderr, "FAIL  %s\n", buf);
        g_num_fails++;
    }
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    const u8 u8_vals[]   = {  u8_MIN,  u8_MIN + 1,  u8_MIN + 2,  u8_MIN + 3,  u8_MAX - 3,  u8_MAX - 2,  u8_MAX - 1,  u8_MAX };
    const s8 s8_vals[]   = {  s8_MIN,  s8_MIN + 1,  s8_MIN + 2,           0,  s8_MAX - 3,  s8_MAX - 2,  s8_MAX - 1,  s8_MAX };
    const u16 u16_vals[] = { u16_MIN, u16_MIN + 1, u16_MIN + 2, u16_MIN + 3, u16_MAX - 3, u16_MAX - 2, u16_MAX - 1, u16_MAX };
    const s16 s16_vals[] = { s16_MIN, s16_MIN + 1, s16_MIN + 2,           0, s16_MAX - 3, s16_MAX - 2, s16_MAX - 1, s16_MAX };
    const u32 u32_vals[] = { u32_MIN, u32_MIN + 1, u32_MIN + 2, u32_MIN + 3, u32_MAX - 3, u32_MAX - 2, u32_MAX - 1, u32_MAX };
    const s32 s32_vals[] = { s32_MIN, s32_MIN + 1, s32_MIN + 2,           0, s32_MAX - 3, s32_MAX - 2, s32_MAX - 1, s32_MAX };
    const u64 u64_vals[] = { u64_MIN, u64_MIN + 1, u64_MIN + 2, u64_MIN + 3, u64_MAX - 3, u64_MAX - 2, u64_MAX - 1, u64_MAX };
    const s64 s64_vals[] = { s64_MIN, s64_MIN + 1, s64_MIN + 2,           0, s64_MAX - 3, s64_MAX - 2, s64_MAX - 1, s64_MAX };
    const f32 f32_vals[] = {
        -INFINITY,
        -1.0f,
        u32_bits_as_f32(0x80000001),
        0.0f,
        u32_bits_as_f32(0x00000001),
        1.0f,
        2.0f,
        INFINITY,
    };
    const u64 num_vals = ARRAY_COUNT(u8_vals);

    // min
    {
        for(u64 i = 0; i < num_vals - 1; i++)
        {
            ASSERT(min_u8(u8_vals[i], u8_vals[i + 1]) == u8_vals[i], "Test fail.");
            ASSERT(min_s8(s8_vals[i], s8_vals[i + 1]) == s8_vals[i], "Test fail.");
            ASSERT(min_u16(u16_vals[i], u16_vals[i + 1]) == u16_vals[i], "Test fail.");
            ASSERT(min_s16(s16_vals[i], s16_vals[i + 1]) == s16_vals[i], "Test fail.");
            ASSERT(min_u32(u32_vals[i], u32_vals[i + 1]) == u32_vals[i], "Test fail.");
            ASSERT(min_s32(s32_vals[i], s32_vals[i + 1]) == s32_vals[i], "Test fail.");
            ASSERT(min_u64(u64_vals[i], u64_vals[i + 1]) == u64_vals[i], "Test fail.");
            ASSERT(min_s64(s64_vals[i], s64_vals[i + 1]) == s64_vals[i], "Test fail.");
            ASSERT(min_f32(f32_vals[i], f32_vals[i + 1]) == f32_vals[i], "Test fail.");
        }

        ASSERT(is_nan(min_f32(nan_f32(), -nan_f32())), "Test fail.");
        ASSERT(is_nan(min_f32(-INFINITY, -nan_f32())), "Test fail.");
        ASSERT(min_f32(nan_f32(), 1.0f) == 1.0f, "Test fail.");
        ASSERT(is_nan(min_f32(1.0f, nan_f32())), "Test fail.");
    }

    // max
    {
        for(u64 i = 0; i < num_vals - 1; i++)
        {
            ASSERT(max_u8(u8_vals[i], u8_vals[i + 1]) == u8_vals[i + 1], "Test fail.");
            ASSERT(max_s8(s8_vals[i], s8_vals[i + 1]) == s8_vals[i + 1], "Test fail.");
            ASSERT(max_u16(u16_vals[i], u16_vals[i + 1]) == u16_vals[i + 1], "Test fail.");
            ASSERT(max_s16(s16_vals[i], s16_vals[i + 1]) == s16_vals[i + 1], "Test fail.");
            ASSERT(max_u32(u32_vals[i], u32_vals[i + 1]) == u32_vals[i + 1], "Test fail.");
            ASSERT(max_s32(s32_vals[i], s32_vals[i + 1]) == s32_vals[i + 1], "Test fail.");
            ASSERT(max_u64(u64_vals[i], u64_vals[i + 1]) == u64_vals[i + 1], "Test fail.");
            ASSERT(max_s64(s64_vals[i], s64_vals[i + 1]) == s64_vals[i + 1], "Test fail.");
            ASSERT(max_f32(f32_vals[i], f32_vals[i + 1]) == f32_vals[i + 1], "Test fail.");
        }

        ASSERT(is_nan(max_f32(nan_f32(), -nan_f32())), "Test fail.");
        ASSERT(is_nan(max_f32(INFINITY, nan_f32())), "Test fail.");
        ASSERT(max_f32(nan_f32(), 1.0f) == 1.0f, "Test fail.");
        ASSERT(is_nan(max_f32(1.0f, nan_f32())), "Test fail.");
    }

    // clamp
    {
        ASSERT(clamp_u8( 9, 10, 20) == 10, "Test fail.");
        ASSERT(clamp_u8(10, 10, 20) == 10, "Test fail.");
        ASSERT(clamp_u8(15, 10, 20) == 15, "Test fail.");
        ASSERT(clamp_u8(20, 10, 20) == 20, "Test fail.");
        ASSERT(clamp_u8(21, 10, 20) == 20, "Test fail.");

        ASSERT(clamp_s8(-11, -10,  10) == -10, "Test fail.");
        ASSERT(clamp_s8(-10, -10,  10) == -10, "Test fail.");
        ASSERT(clamp_s8(  0, -10,  10) ==   0, "Test fail.");
        ASSERT(clamp_s8( 10, -10,  10) ==  10, "Test fail.");
        ASSERT(clamp_s8( 11, -10,  10) ==  10, "Test fail.");

        ASSERT(clamp_u16( 9, 10, 20) == 10, "Test fail.");
        ASSERT(clamp_u16(10, 10, 20) == 10, "Test fail.");
        ASSERT(clamp_u16(15, 10, 20) == 15, "Test fail.");
        ASSERT(clamp_u16(20, 10, 20) == 20, "Test fail.");
        ASSERT(clamp_u16(21, 10, 20) == 20, "Test fail.");

        ASSERT(clamp_s16(-11, -10,  10) == -10, "Test fail.");
        ASSERT(clamp_s16(-10, -10,  10) == -10, "Test fail.");
        ASSERT(clamp_s16(  0, -10,  10) ==   0, "Test fail.");
        ASSERT(clamp_s16( 10, -10,  10) ==  10, "Test fail.");
        ASSERT(clamp_s16( 11, -10,  10) ==  10, "Test fail.");

        ASSERT(clamp_u32( 9, 10, 20) == 10, "Test fail.");
        ASSERT(clamp_u32(10, 10, 20) == 10, "Test fail.");
        ASSERT(clamp_u32(15, 10, 20) == 15, "Test fail.");
        ASSERT(clamp_u32(20, 10, 20) == 20, "Test fail.");
        ASSERT(clamp_u32(21, 10, 20) == 20, "Test fail.");

        ASSERT(clamp_s32(-11, -10,  10) == -10, "Test fail.");
        ASSERT(clamp_s32(-10, -10,  10) == -10, "Test fail.");
        ASSERT(clamp_s32(  0, -10,  10) ==   0, "Test fail.");
        ASSERT(clamp_s32( 10, -10,  10) ==  10, "Test fail.");
        ASSERT(clamp_s32( 11, -10,  10) ==  10, "Test fail.");

        ASSERT(clamp_u64( 9, 10, 20) == 10, "Test fail.");
        ASSERT(clamp_u64(10, 10, 20) == 10, "Test fail.");
        ASSERT(clamp_u64(15, 10, 20) == 15, "Test fail.");
        ASSERT(clamp_u64(20, 10, 20) == 20, "Test fail.");
        ASSERT(clamp_u64(21, 10, 20) == 20, "Test fail.");

        ASSERT(clamp_s64(-11, -10,  10) == -10, "Test fail.");
        ASSERT(clamp_s64(-10, -10,  10) == -10, "Test fail.");
        ASSERT(clamp_s64(  0, -10,  10) ==   0, "Test fail.");
        ASSERT(clamp_s64( 10, -10,  10) ==  10, "Test fail.");
        ASSERT(clamp_s64( 11, -10,  10) ==  10, "Test fail.");

        ASSERT(clamp_f32(-11.0f, -10.0f, 10.0f) == -10.0f, "Test fail.");
        ASSERT(clamp_f32(-10.0f, -10.0f, 10.0f) == -10.0f, "Test fail.");
        ASSERT(clamp_f32(  0.0f, -10.0f, 10.0f) ==   0.0f, "Test fail.");
        ASSERT(clamp_f32( 10.0f, -10.0f, 10.0f) ==  10.0f, "Test fail.");
        ASSERT(clamp_f32( 11.0f, -10.0f, 10.0f) ==  10.0f, "Test fail.");
    }
    
    // abs
    {
        ASSERT(abs_s8(s8_MIN + 1) == s8_MAX, "Test fail.");
        ASSERT(abs_s8(s8_MAX) == s8_MAX, "Test fail.");

        ASSERT(abs_s16(s16_MIN + 1) == s16_MAX, "Test fail.");
        ASSERT(abs_s16(s16_MAX) == s16_MAX, "Test fail.");

        ASSERT(abs_s32(s32_MIN + 1) == s32_MAX, "Test fail.");
        ASSERT(abs_s32(s32_MAX) == s32_MAX, "Test fail.");

        ASSERT(abs_s64(s64_MIN + 1) == s64_MAX, "Test fail.");
        ASSERT(abs_s64(s64_MAX) == s64_MAX, "Test fail.");

        ASSERT(is_nan(abs_f32(nan_f32())), "Test fail.");
        ASSERT(is_nan(abs_f32(-nan_f32())), "Test fail.");

        ASSERT(abs_f32(-INFINITY) == INFINITY, "Test fail.");
        ASSERT(abs_f32(INFINITY) == INFINITY, "Test fail.");

        ASSERT(abs_f32(-1.0f) == 1.0f, "Test fail.");
        ASSERT(abs_f32(1.0f) == 1.0f, "Test fail.");
    }

    // square
    {
        ASSERT(sq_u8(2) == 4, "Test fail.");

        ASSERT(sq_s8(2) == 4, "Test fail.");
        ASSERT(sq_s8(-2) == 4, "Test fail.");

        ASSERT(sq_u16(2) == 4, "Test fail.");

        ASSERT(sq_s16(2) == 4, "Test fail.");
        ASSERT(sq_s16(-2) == 4, "Test fail.");

        ASSERT(sq_u32(2) == 4, "Test fail.");

        ASSERT(sq_s32(2) == 4, "Test fail.");
        ASSERT(sq_s32(-2) == 4, "Test fail.");

        ASSERT(sq_u64(2) == 4, "Test fail.");

        ASSERT(sq_s64(2) == 4, "Test fail.");
        ASSERT(sq_s64(-2) == 4, "Test fail.");

        ASSERT(is_nan(sq_f32(nan_f32())), "Test fail.");
        ASSERT(sq_f32(INFINITY) == INFINITY, "Test fail.");
        ASSERT(sq_f32(-INFINITY) == INFINITY, "Test fail.");
        ASSERT(sq_f32(-1.0f) == 1.0f, "Test fail.");
        ASSERT(sq_f32( 2.0f) == 4.0f, "Test fail.");
    }

    // round
    {
        ASSERT(is_nan(round_neg_inf(nan_f32())), "Test fail.");
        ASSERT(round_neg_inf(-INFINITY) == -INFINITY, "Test fail.");
        ASSERT(round_neg_inf(INFINITY) == INFINITY, "Test fail.");
        ASSERT(round_neg_inf(-1.0f) == -1.0f, "Test fail.");
        ASSERT(round_neg_inf(-0.5f) == -1.0f, "Test fail.");
        ASSERT(round_neg_inf( 0.0f) ==  0.0f, "Test fail.");
        ASSERT(round_neg_inf( 0.5f) ==  0.0f, "Test fail.");
        ASSERT(round_neg_inf( 1.0f) ==  1.0f, "Test fail.");

        ASSERT(is_nan(round_pos_inf(nan_f32())), "Test fail.");
        ASSERT(round_pos_inf(-INFINITY) == -INFINITY, "Test fail.");
        ASSERT(round_pos_inf(INFINITY) == INFINITY, "Test fail.");
        ASSERT(round_pos_inf(-1.0f) == -1.0f, "Test fail.");
        ASSERT(round_pos_inf(-0.5f) ==  0.0f, "Test fail.");
        ASSERT(round_pos_inf( 0.0f) ==  0.0f, "Test fail.");
        ASSERT(round_pos_inf( 0.5f) ==  1.0f, "Test fail.");
        ASSERT(round_pos_inf( 1.0f) ==  1.0f, "Test fail.");
    }

    // sqrt
    {
        ASSERT(is_nan(sqrt_f32(nan_f32())), "Test fail.");
        ASSERT(is_nan(sqrt_f32(-1.0f)), "Test fail.");
        ASSERT(is_nan(sqrt_f32(-INFINITY)), "Test fail.");
        ASSERT(sqrt_f32(INFINITY) == INFINITY, "Test fail.");
        ASSERT(sqrt_f32(0.0f) == 0.0f, "Test fail.");
        ASSERT(sqrt_f32(1.0f) == 1.0f, "Test fail.");
        ASSERT(sqrt_f32(2.0f) == u32_bits_as_f32(0x3FB504F3), "Test fail.");
        ASSERT(sqrt_f32(4.0f) == 2.0f, "Test fail.");
    }

    // vector constructors
    {
        _Alignas(16) f32 a[4];
        {
            v2 r2 = zero_v2();
            _mm_store_ps(a, r2.v);
            ASSERT(a[0] == 0.0f, "Test fail.");
            ASSERT(a[1] == 0.0f, "Test fail.");
            ASSERT(is_nan(a[2]), "Test fail.");
            ASSERT(is_nan(a[3]), "Test fail.");

            v3 r3 = zero_v3();
            _mm_store_ps(a, r3.v);
            ASSERT(a[0] == 0.0f, "Test fail.");
            ASSERT(a[1] == 0.0f, "Test fail.");
            ASSERT(a[2] == 0.0f, "Test fail.");
            ASSERT(is_nan(a[3]), "Test fail.");

            v4 r4 = zero_v4();
            _mm_store_ps(a, r4.v);
            ASSERT(a[0] == 0.0f, "Test fail.");
            ASSERT(a[1] == 0.0f, "Test fail.");
            ASSERT(a[2] == 0.0f, "Test fail.");
            ASSERT(a[3] == 0.0f, "Test fail.");
        }

        {
            v2 r2 = make_v2(1.0f, 2.0f);
            _mm_store_ps(a, r2.v);
            ASSERT(a[0] == 1.0f, "Test fail.");
            ASSERT(a[1] == 2.0f, "Test fail.");
            ASSERT(is_nan(a[2]), "Test fail.");
            ASSERT(is_nan(a[3]), "Test fail.");

            v3 r3 = make_v3(1.0f, 2.0f, 3.0f);
            _mm_store_ps(a, r3.v);
            ASSERT(a[0] == 1.0f, "Test fail.");
            ASSERT(a[1] == 2.0f, "Test fail.");
            ASSERT(a[2] == 3.0f, "Test fail.");
            ASSERT(is_nan(a[3]), "Test fail.");

            v4 r4 = make_v4(1.0f, 2.0f, 3.0f, 4.0f);
            _mm_store_ps(a, r4.v);
            ASSERT(a[0] == 1.0f, "Test fail.");
            ASSERT(a[1] == 2.0f, "Test fail.");
            ASSERT(a[2] == 3.0f, "Test fail.");
            ASSERT(a[3] == 4.0f, "Test fail.");
        }
    }

    // add
    {
        v2 r2 = add_v2(make_v2(1.0f, 2.0f), make_v2(10.0f, 20.0f));
        ASSERT(r2.x == 11.0f, "Test fail.");
        ASSERT(r2.y == 22.0f, "Test fail.");

        v3 r3 = add_v3(make_v3(1.0f, 2.0f, 3.0f), make_v3(10.0f, 20.0f, 30.0f));
        ASSERT(r3.x == 11.0f, "Test fail.");
        ASSERT(r3.y == 22.0f, "Test fail.");
        ASSERT(r3.z == 33.0f, "Test fail.");

        v4 r4 = add_v4(make_v4(1.0f, 2.0f, 3.0f, 4.0f), make_v4(10.0f, 20.0f, 30.0f, 40.0f));
        ASSERT(r4.x == 11.0f, "Test fail.");
        ASSERT(r4.y == 22.0f, "Test fail.");
        ASSERT(r4.z == 33.0f, "Test fail.");
        ASSERT(r4.w == 44.0f, "Test fail.");
    }

    // sub
    {
        v2 r2 = sub_v2(make_v2(-1.0f, -2.0f), make_v2(10.0f, 20.0f));
        ASSERT(r2.x == -11.0f, "Test fail.");
        ASSERT(r2.y == -22.0f, "Test fail.");

        v3 r3 = sub_v3(make_v3(-1.0f, -2.0f, -3.0f), make_v3(10.0f, 20.0f, 30.0f));
        ASSERT(r3.x == -11.0f, "Test fail.");
        ASSERT(r3.y == -22.0f, "Test fail.");
        ASSERT(r3.z == -33.0f, "Test fail.");

        v4 r4 = sub_v4(make_v4(-1.0f, -2.0f, -3.0f, -4.0f), make_v4(10.0f, 20.0f, 30.0f, 40.0f));
        ASSERT(r4.x == -11.0f, "Test fail.");
        ASSERT(r4.y == -22.0f, "Test fail.");
        ASSERT(r4.z == -33.0f, "Test fail.");
        ASSERT(r4.w == -44.0f, "Test fail.");
    }

    // scale
    {
        v2 r2 = scale_v2(make_v2(1.0f, 2.0f), 2.0f);
        ASSERT(r2.x == 2.0f, "Test fail.");
        ASSERT(r2.y == 4.0f, "Test fail.");

        v3 r3 = scale_v3(make_v3(1.0f, 2.0f, 3.0f), 2.0f);
        ASSERT(r3.x == 2.0f, "Test fail.");
        ASSERT(r3.y == 4.0f, "Test fail.");
        ASSERT(r3.z == 6.0f, "Test fail.");

        v4 r4 = scale_v4(make_v4(1.0f, 2.0f, 3.0f, 4.0f), 2.0f);
        ASSERT(r4.x == 2.0f, "Test fail.");
        ASSERT(r4.y == 4.0f, "Test fail.");
        ASSERT(r4.z == 6.0f, "Test fail.");
        ASSERT(r4.w == 8.0f, "Test fail.");
    }

    // lerp
    {
        ASSERT(lerp_f32(10.0f, 20.0f, 0.0f) == 10.0f, "Test fail.");
        ASSERT(lerp_f32(10.0f, 20.0f, 0.5f) == 15.0f, "Test fail.");
        ASSERT(lerp_f32(10.0f, 20.0f, 1.0f) == 20.0f, "Test fail.");

        v2 r2 = lerp_v2(make_v2(10.0f, 100.0f), make_v2(20.0f, 200.0f), 0.0f);
        ASSERT(r2.x == 10.0f, "Test fail.");
        ASSERT(r2.y == 100.0f, "Test fail.");
        r2 = lerp_v2(make_v2(10.0f, 100.0f), make_v2(20.0f, 200.0f), 0.5f);
        ASSERT(r2.x == 15.0f, "Test fail.");
        ASSERT(r2.y == 150.0f, "Test fail.");
        r2 = lerp_v2(make_v2(10.0f, 100.0f), make_v2(20.0f, 200.0f), 1.0f);
        ASSERT(r2.x == 20.0f, "Test fail.");
        ASSERT(r2.y == 200.0f, "Test fail.");

        v3 r3 = lerp_v3(make_v3(10.0f, 100.0f, 1000.0f), make_v3(20.0f, 200.0f, 2000.0f), 0.0f);
        ASSERT(r3.x == 10.0f, "Test fail.");
        ASSERT(r3.y == 100.0f, "Test fail.");
        ASSERT(r3.z == 1000.0f, "Test fail.");
        r3 = lerp_v3(make_v3(10.0f, 100.0f, 1000.0f), make_v3(20.0f, 200.0f, 2000.0f), 0.5f);
        ASSERT(r3.x == 15.0f, "Test fail.");
        ASSERT(r3.y == 150.0f, "Test fail.");
        ASSERT(r3.z == 1500.0f, "Test fail.");
        r3 = lerp_v3(make_v3(10.0f, 100.0f, 1000.0f), make_v3(20.0f, 200.0f, 2000.0f), 1.0f);
        ASSERT(r3.x == 20.0f, "Test fail.");
        ASSERT(r3.y == 200.0f, "Test fail.");
        ASSERT(r3.z == 2000.0f, "Test fail.");

        v4 r4 = lerp_v4(make_v4(10.0f, 100.0f, 1000.0f, 10000.0f), make_v4(20.0f, 200.0f, 2000.0f, 20000.0f), 0.0f);
        ASSERT(r4.x == 10.0f, "Test fail.");
        ASSERT(r4.y == 100.0f, "Test fail.");
        ASSERT(r4.z == 1000.0f, "Test fail.");
        ASSERT(r4.w == 10000.0f, "Test fail.");
        r4 = lerp_v4(make_v4(10.0f, 100.0f, 1000.0f, 10000.0f), make_v4(20.0f, 200.0f, 2000.0f, 20000.0f), 0.5f);
        ASSERT(r4.x == 15.0f, "Test fail.");
        ASSERT(r4.y == 150.0f, "Test fail.");
        ASSERT(r4.z == 1500.0f, "Test fail.");
        ASSERT(r4.w == 15000.0f, "Test fail.");
        r4 = lerp_v4(make_v4(10.0f, 100.0f, 1000.0f, 10000.0f), make_v4(20.0f, 200.0f, 2000.0f, 20000.0f), 1.0f);
        ASSERT(r4.x == 20.0f, "Test fail.");
        ASSERT(r4.y == 200.0f, "Test fail.");
        ASSERT(r4.z == 2000.0f, "Test fail.");
        ASSERT(r4.w == 20000.0f, "Test fail.");
    }

    // dot product
    {
        ASSERT(dot_v2(make_v2(1.0f, 2.0f), make_v2(3.0f, 4.0f)) == 11.0f, "Test fail.");
        ASSERT(dot_v3(make_v3(1.0f, 2.0f, 3.0f), make_v3(4.0f, 5.0f, 6.0f)) == 32.0f, "Test fail.");
        ASSERT(dot_v4(make_v4(1.0f, 2.0f, 3.0f, 4.0f), make_v4(5.0f, 6.0f, 7.0f, 8.0f)) == 70.0f, "Test fail.");
    }

    // length
    {
        ASSERT(length_sq_v2(make_v2(3.0f, -4.0f)) == 25.0f, "Test fail.");
        ASSERT(length_sq_v3(make_v3(3.0f, -4.0f, 5.0f)) == 50.0f, "Test fail.");
        ASSERT(length_sq_v4(make_v4(3.0f, -4.0f, 5.0f, 6.0f)) == 86.0f, "Test fail.");
        
        ASSERT(length_v2(make_v2(3.0f, -4.0f)) == 5.0f, "Test fail.");
        ASSERT(length_v3(make_v3(3.0f, -4.0f, 5.0f)) == sqrt_f32(50.0f), "Test fail.");
        ASSERT(length_v4(make_v4(3.0f, -4.0f, 5.0f, 6.0)) == sqrt_f32(86.0f), "Test fail.");
    }

    // normalize
    {
        {
            v2 r2 = normalize_v2(make_v2(1.0f, -2.0f));
            ASSERT(r2.x == 1.0f / sqrt_f32(5.0f), "Test fail.");
            ASSERT(r2.y == -2.0f / sqrt_f32(5.0f), "Test fail.");
            r2 = normalize_v2(zero_v2());
            ASSERT(is_nan(r2.x), "Test fail.");
            ASSERT(is_nan(r2.y), "Test fail.");

            v3 r3 = normalize_v3(make_v3(1.0f, -2.0f, 3.0f));
            ASSERT(r3.x == 1.0f / sqrt_f32(14.0f), "Test fail.");
            ASSERT(r3.y == -2.0f / sqrt_f32(14.0f), "Test fail.");
            ASSERT(r3.z == 3.0f / sqrt_f32(14.0f), "Test fail.");
            r3 = normalize_v3(zero_v3());
            ASSERT(is_nan(r3.x), "Test fail.");
            ASSERT(is_nan(r3.y), "Test fail.");
            ASSERT(is_nan(r3.z), "Test fail.");

            v4 r4 = normalize_v4(make_v4(1.0f, -2.0f, 3.0f, -4.0f));
            ASSERT(r4.x == 1.0f / sqrt_f32(30.0f), "Test fail.");
            ASSERT(r4.y == -2.0f / sqrt_f32(30.0f), "Test fail.");
            ASSERT(r4.z == 3.0f / sqrt_f32(30.0f), "Test fail.");
            ASSERT(r4.w == -4.0f / sqrt_f32(30.0f), "Test fail.");
            r4 = normalize_v4(zero_v4());
            ASSERT(is_nan(r4.x), "Test fail.");
            ASSERT(is_nan(r4.y), "Test fail.");
            ASSERT(is_nan(r4.z), "Test fail.");
            ASSERT(is_nan(r4.w), "Test fail.");
        }

        {
            v2 r2 = normalize_or_v2(make_v2(1.0f, -2.0f), zero_v2());
            ASSERT(r2.x == 1.0f / sqrt_f32(5.0f), "Test fail.");
            ASSERT(r2.y == -2.0f / sqrt_f32(5.0f), "Test fail.");
            r2 = normalize_or_v2(zero_v2(), make_v2(100.0f, 200.0f));
            ASSERT(r2.x == 100.0f, "Test fail.");
            ASSERT(r2.y == 200.0f, "Test fail.");

            v3 r3 = normalize_or_v3(make_v3(1.0f, -2.0f, 3.0f), zero_v3());
            ASSERT(r3.x == 1.0f / sqrt_f32(14.0f), "Test fail.");
            ASSERT(r3.y == -2.0f / sqrt_f32(14.0f), "Test fail.");
            ASSERT(r3.z == 3.0f / sqrt_f32(14.0f), "Test fail.");
            r3 = normalize_or_v3(zero_v3(), make_v3(100.0f, 200.0f, 300.0f));
            ASSERT(r3.x == 100.0f, "Test fail.");
            ASSERT(r3.y == 200.0f, "Test fail.");
            ASSERT(r3.z == 300.0f, "Test fail.");

            v4 r4 = normalize_or_v4(make_v4(1.0f, -2.0f, 3.0f, -4.0f), zero_v4());
            ASSERT(r4.x == 1.0f / sqrt_f32(30.0f), "Test fail.");
            ASSERT(r4.y == -2.0f / sqrt_f32(30.0f), "Test fail.");
            ASSERT(r4.z == 3.0f / sqrt_f32(30.0f), "Test fail.");
            ASSERT(r4.w == -4.0f / sqrt_f32(30.0f), "Test fail.");
            r4 = normalize_or_v4(zero_v4(), make_v4(100.0f, 200.0f, 300.0f, 400.0f));
            ASSERT(r4.x == 100.0f, "Test fail.");
            ASSERT(r4.y == 200.0f, "Test fail.");
            ASSERT(r4.z == 300.0f, "Test fail.");
            ASSERT(r4.w == 400.0f, "Test fail.");
        }
    }

    // matrix multiply
    {
        m4x4 m0 = {
            .a = {
                {1.0f, 2.0f, 3.0f, 4.0f},
                {5.0f, 6.0f, 7.0f, 8.0f},
                {9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f},
            }
        };

        m4x4 m1 = {
            .a = {
                {0.0f, 2.0f, 4.0f, 6.0f},
                {8.0f, 10.0f, 12.0f, 14.0f},
                {16.0f, 18.0f, 20.0f, 22.0f},
                {24.0f, 26.0f, 28.0f, 30.0f},
            }
        };

        m4x4 result;
        mul_m4x4(&result, &m0, &m1);

        ASSERT(result.a[0][0] == 160.0f, "Test fail.");
        ASSERT(result.a[0][1] == 180.0f, "Test fail.");
        ASSERT(result.a[0][2] == 200.0f, "Test fail.");
        ASSERT(result.a[0][3] == 220.0f, "Test fail.");

        ASSERT(result.a[1][0] == 352.0f, "Test fail.");
        ASSERT(result.a[1][1] == 404.0f, "Test fail.");
        ASSERT(result.a[1][2] == 456.0f, "Test fail.");
        ASSERT(result.a[1][3] == 508.0f, "Test fail.");

        ASSERT(result.a[2][0] == 544.0f, "Test fail.");
        ASSERT(result.a[2][1] == 628.0f, "Test fail.");
        ASSERT(result.a[2][2] == 712.0f, "Test fail.");
        ASSERT(result.a[2][3] == 796.0f, "Test fail.");

        ASSERT(result.a[3][0] == 736.0f, "Test fail.");
        ASSERT(result.a[3][1] == 852.0f, "Test fail.");
        ASSERT(result.a[3][2] == 968.0f, "Test fail.");
        ASSERT(result.a[3][3] == 1084.0f, "Test fail.");
    }

    return g_num_fails != 0;
}
