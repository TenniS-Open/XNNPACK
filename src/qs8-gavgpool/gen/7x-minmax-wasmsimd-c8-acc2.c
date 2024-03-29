// Auto-generated file. Do not edit!
//   Template: src/qs8-gavgpool/unipass-wasmsimd.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/gavgpool.h>


void xnn_qs8_gavgpool_minmax_ukernel_7x__wasmsimd_c8_acc2(
    size_t rows,
    size_t channels,
    const int8_t* input,
    size_t input_stride,
    const int8_t* zero,
    int8_t* output,
    const union xnn_qs8_avgpool_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_DISABLE_TSAN
{
  assert(rows != 0);
  assert(rows <= 7);
  assert(channels != 0);

  const int8_t* i0 = input;
  const int8_t* i1 = (const int8_t*) ((uintptr_t) i0 + input_stride);
  if XNN_UNPREDICTABLE(rows < 2) {
    i1 = zero;
  }
  const int8_t* i2 = (const int8_t*) ((uintptr_t) i1 + input_stride);
  if XNN_UNPREDICTABLE(rows <= 2) {
    i2 = zero;
  }
  const int8_t* i3 = (const int8_t*) ((uintptr_t) i2 + input_stride);
  if XNN_UNPREDICTABLE(rows < 4) {
    i3 = zero;
  }
  const int8_t* i4 = (const int8_t*) ((uintptr_t) i3 + input_stride);
  if XNN_UNPREDICTABLE(rows <= 4) {
    i4 = zero;
  }
  const int8_t* i5 = (const int8_t*) ((uintptr_t) i4 + input_stride);
  if XNN_UNPREDICTABLE(rows < 6) {
    i5 = zero;
  }
  const int8_t* i6 = (const int8_t*) ((uintptr_t) i5 + input_stride);
  if XNN_UNPREDICTABLE(rows <= 6) {
    i6 = zero;
  }

  const v128_t vbias = wasm_v128_load(params->wasmsimd.bias);
  const v128_t vmultiplier = wasm_v128_load(params->wasmsimd.multiplier);
  const v128_t vrounding = wasm_v128_load(params->wasmsimd.rounding);
  const int32_t vshift = params->wasmsimd.shift;
  const v128_t vzero = wasm_i32x4_splat(0);
  while (channels >= 8) {
    const v128_t vxi0x01234567 = wasm_i16x8_load8x8(i0);
    i0 += 8;
    const v128_t vxi1x01234567 = wasm_i16x8_load8x8(i1);
    i1 += 8;
    const v128_t vxi2x01234567 = wasm_i16x8_load8x8(i2);
    i2 += 8;
    const v128_t vxi3x01234567 = wasm_i16x8_load8x8(i3);
    i3 += 8;
    const v128_t vxi4x01234567 = wasm_i16x8_load8x8(i4);
    i4 += 8;
    const v128_t vxi5x01234567 = wasm_i16x8_load8x8(i5);
    i5 += 8;
    const v128_t vxi6x01234567 = wasm_i16x8_load8x8(i6);
    i6 += 8;

    v128_t vacc0x01234567 = wasm_i16x8_add(vxi0x01234567, vxi1x01234567);
    v128_t vacc1x01234567 = wasm_i16x8_add(vxi2x01234567, vxi3x01234567);

    vacc0x01234567 = wasm_i16x8_add(vacc0x01234567, vxi4x01234567);
    vacc1x01234567 = wasm_i16x8_add(vacc1x01234567, vxi5x01234567);
    vacc0x01234567 = wasm_i16x8_add(vacc0x01234567, vxi6x01234567);

    // Add up all accumulators to vacc0x01234567
    vacc0x01234567 = wasm_i16x8_add(vacc0x01234567, vacc1x01234567);

    const v128_t vacc0123 = wasm_i32x4_add(vbias, wasm_i32x4_extend_low_i16x8(vacc0x01234567));
    const v128_t vacc4567 = wasm_i32x4_add(vbias, wasm_i32x4_extend_high_i16x8(vacc0x01234567));

    const v128_t vabsacc0123 = wasm_i32x4_abs(vacc0123);
    const v128_t vabsacc4567 = wasm_i32x4_abs(vacc4567);

    const v128_t vsgnacc0123 = wasm_i32x4_gt(vabsacc0123, vacc0123);
    const v128_t vsgnacc4567 = wasm_i32x4_gt(vabsacc4567, vacc4567);

    const v128_t vabsacc01 = wasm_v32x4_shuffle(vabsacc0123, vzero, 0, 4, 1, 5);
    const v128_t vabsacc23 = wasm_v32x4_shuffle(vabsacc0123, vzero, 2, 6, 3, 7);
    const v128_t vabsacc45 = wasm_v32x4_shuffle(vabsacc4567, vzero, 0, 4, 1, 5);
    const v128_t vabsacc67 = wasm_v32x4_shuffle(vabsacc4567, vzero, 2, 6, 3, 7);

    const v128_t vabsprod01 = wasm_i64x2_mul(vabsacc01, vmultiplier);
    const v128_t vabsprod23 = wasm_i64x2_mul(vabsacc23, vmultiplier);
    const v128_t vabsprod45 = wasm_i64x2_mul(vabsacc45, vmultiplier);
    const v128_t vabsprod67 = wasm_i64x2_mul(vabsacc67, vmultiplier);

    const v128_t vabsout01 = wasm_u64x2_shr(wasm_i64x2_add(vabsprod01, vrounding), vshift);
    const v128_t vabsout23 = wasm_u64x2_shr(wasm_i64x2_add(vabsprod23, vrounding), vshift);
    const v128_t vabsout45 = wasm_u64x2_shr(wasm_i64x2_add(vabsprod45, vrounding), vshift);
    const v128_t vabsout67 = wasm_u64x2_shr(wasm_i64x2_add(vabsprod67, vrounding), vshift);

    const v128_t vabsout0123 = wasm_v32x4_shuffle(vabsout01, vabsout23, 0, 2, 4, 6);
    const v128_t vabsout4567 = wasm_v32x4_shuffle(vabsout45, vabsout67, 0, 2, 4, 6);

    const v128_t vout0123 = wasm_i32x4_sub(wasm_v128_xor(vabsout0123, vsgnacc0123), vsgnacc0123);
    const v128_t vout4567 = wasm_i32x4_sub(wasm_v128_xor(vabsout4567, vsgnacc4567), vsgnacc4567);

    const v128_t voutput_zero_point = wasm_v128_load(params->wasmsimd.output_zero_point);
    const v128_t vout01234567 = wasm_i16x8_add_sat(wasm_i16x8_narrow_i32x4(vout0123, vout4567), voutput_zero_point);

    const v128_t voutput_min = wasm_v128_load(params->wasmsimd.output_min);
    const v128_t voutput_max = wasm_v128_load(params->wasmsimd.output_max);
    const v128_t vout0123456701234567 = wasm_i8x16_min(wasm_i8x16_max(wasm_i8x16_narrow_i16x8(vout01234567, vout01234567), voutput_min), voutput_max);

    *((double*) output) = wasm_f64x2_extract_lane(vout0123456701234567, 0);
    output += 8;

    channels -= 8;
  }
  if XNN_UNLIKELY(channels != 0) {
    {
      const v128_t vxi0x01234567 = wasm_i16x8_load8x8(i0);
      i0 += 8;
      const v128_t vxi1x01234567 = wasm_i16x8_load8x8(i1);
      i1 += 8;
      const v128_t vxi2x01234567 = wasm_i16x8_load8x8(i2);
      i2 += 8;
      const v128_t vxi3x01234567 = wasm_i16x8_load8x8(i3);
      i3 += 8;
      const v128_t vxi4x01234567 = wasm_i16x8_load8x8(i4);
      i4 += 8;
      const v128_t vxi5x01234567 = wasm_i16x8_load8x8(i5);
      i5 += 8;
      const v128_t vxi6x01234567 = wasm_i16x8_load8x8(i6);
      i6 += 8;

      v128_t vacc0x01234567 = wasm_i16x8_add(vxi0x01234567, vxi1x01234567);
      v128_t vacc1x01234567 = wasm_i16x8_add(vxi2x01234567, vxi3x01234567);

      vacc0x01234567 = wasm_i16x8_add(vacc0x01234567, vxi4x01234567);
      vacc1x01234567 = wasm_i16x8_add(vacc1x01234567, vxi5x01234567);
      vacc0x01234567 = wasm_i16x8_add(vacc0x01234567, vxi6x01234567);

      // Add up all accumulators to vacc0x01234567
      vacc0x01234567 = wasm_i16x8_add(vacc0x01234567, vacc1x01234567);

      const v128_t vacc0123 = wasm_i32x4_add(vbias, wasm_i32x4_extend_low_i16x8(vacc0x01234567));
      const v128_t vacc4567 = wasm_i32x4_add(vbias, wasm_i32x4_extend_high_i16x8(vacc0x01234567));

      const v128_t vabsacc0123 = wasm_i32x4_abs(vacc0123);
      const v128_t vabsacc4567 = wasm_i32x4_abs(vacc4567);

      const v128_t vsgnacc0123 = wasm_i32x4_gt(vabsacc0123, vacc0123);
      const v128_t vsgnacc4567 = wasm_i32x4_gt(vabsacc4567, vacc4567);

      const v128_t vabsacc01 = wasm_v32x4_shuffle(vabsacc0123, vzero, 0, 4, 1, 5);
      const v128_t vabsacc23 = wasm_v32x4_shuffle(vabsacc0123, vzero, 2, 6, 3, 7);
      const v128_t vabsacc45 = wasm_v32x4_shuffle(vabsacc4567, vzero, 0, 4, 1, 5);
      const v128_t vabsacc67 = wasm_v32x4_shuffle(vabsacc4567, vzero, 2, 6, 3, 7);

      const v128_t vabsprod01 = wasm_i64x2_mul(vabsacc01, vmultiplier);
      const v128_t vabsprod23 = wasm_i64x2_mul(vabsacc23, vmultiplier);
      const v128_t vabsprod45 = wasm_i64x2_mul(vabsacc45, vmultiplier);
      const v128_t vabsprod67 = wasm_i64x2_mul(vabsacc67, vmultiplier);

      const v128_t vabsout01 = wasm_u64x2_shr(wasm_i64x2_add(vabsprod01, vrounding), vshift);
      const v128_t vabsout23 = wasm_u64x2_shr(wasm_i64x2_add(vabsprod23, vrounding), vshift);
      const v128_t vabsout45 = wasm_u64x2_shr(wasm_i64x2_add(vabsprod45, vrounding), vshift);
      const v128_t vabsout67 = wasm_u64x2_shr(wasm_i64x2_add(vabsprod67, vrounding), vshift);

      const v128_t vabsout0123 = wasm_v32x4_shuffle(vabsout01, vabsout23, 0, 2, 4, 6);
      const v128_t vabsout4567 = wasm_v32x4_shuffle(vabsout45, vabsout67, 0, 2, 4, 6);

      const v128_t vout0123 = wasm_i32x4_sub(wasm_v128_xor(vabsout0123, vsgnacc0123), vsgnacc0123);
      const v128_t vout4567 = wasm_i32x4_sub(wasm_v128_xor(vabsout4567, vsgnacc4567), vsgnacc4567);

      const v128_t voutput_zero_point = wasm_v128_load(params->wasmsimd.output_zero_point);
      const v128_t vout01234567 = wasm_i16x8_add_sat(wasm_i16x8_narrow_i32x4(vout0123, vout4567), voutput_zero_point);

      const v128_t voutput_min = wasm_v128_load(params->wasmsimd.output_min);
      const v128_t voutput_max = wasm_v128_load(params->wasmsimd.output_max);
      v128_t vout0123456701234567 = wasm_i8x16_min(wasm_i8x16_max(wasm_i8x16_narrow_i16x8(vout01234567, vout01234567), voutput_min), voutput_max);

      if (channels & 4) {
        *((float*) output) = wasm_f32x4_extract_lane(vout0123456701234567, 0);
        vout0123456701234567 = wasm_u64x2_shr(vout0123456701234567, 32);
        output += 4;
      }
      {
        uint32_t vout0123 = wasm_i32x4_extract_lane(vout0123456701234567, 0);
        if (channels & 2) {
          *((uint16_t*) output) = (uint16_t) vout0123;
          vout0123 >>= 16;
          output += 2;
        }
        if (channels & 1) {
          *output = (int8_t) vout0123;
        }
      }
    }
  }
}
