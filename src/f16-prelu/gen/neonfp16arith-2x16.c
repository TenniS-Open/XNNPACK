// Auto-generated file. Do not edit!
//   Template: src/f16-prelu/neonfp16arith.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/math.h>
#include <xnnpack/prelu.h>


void xnn_f16_prelu_ukernel__neonfp16arith_2x16(
    size_t rows,
    size_t channels,
    const void* restrict input,
    size_t input_stride,
    const void* restrict weights,
    void* restrict output,
    size_t output_stride) XNN_DISABLE_TSAN
{
  assert(rows != 0);
  assert(channels != 0);
  assert(channels % sizeof(__fp16) == 0);

  const __fp16* i0 = (const __fp16*) input;
  __fp16* o0 = (__fp16*) output;

  const __fp16* i1 = (const __fp16*) ((uintptr_t) i0 + input_stride);
  __fp16* o1 = (__fp16*) ((uintptr_t) o0 + output_stride);
  if XNN_UNPREDICTABLE(rows < 2) {
    i1 = i0;
    o1 = o0;
  }

  const size_t input_increment = input_stride * 2 - channels;
  const size_t output_increment = output_stride * 2 - channels;

  do {
    const __fp16* w = (const __fp16*) weights;
    size_t c = channels;
    for (; c >= 16 * sizeof(__fp16); c -= 16 * sizeof(__fp16)) {
      const float16x8_t vw01234567 = vld1q_f16(w); w += 8;
      const float16x8_t vw89ABCDEF = vld1q_f16(w); w += 8;

      const float16x8_t vi0x001234567 = vld1q_f16(i0); i0 += 8;
      const float16x8_t vi0x089ABCDEF = vld1q_f16(i0); i0 += 8;
      const float16x8_t vi1x001234567 = vld1q_f16(i1); i1 += 8;
      const float16x8_t vi1x089ABCDEF = vld1q_f16(i1); i1 += 8;

      float16x8_t vacc0x001234567 = vmulq_f16(vi0x001234567, vw01234567);
      const uint16x8_t vm0x001234567 = vcltq_s16(vreinterpretq_s16_f16(vi0x001234567), vmovq_n_s16(0));
      float16x8_t vacc0x089ABCDEF = vmulq_f16(vi0x089ABCDEF, vw89ABCDEF);
      const uint16x8_t vm0x089ABCDEF = vcltq_s16(vreinterpretq_s16_f16(vi0x089ABCDEF), vmovq_n_s16(0));
      float16x8_t vacc1x001234567 = vmulq_f16(vi1x001234567, vw01234567);
      const uint16x8_t vm1x001234567 = vcltq_s16(vreinterpretq_s16_f16(vi1x001234567), vmovq_n_s16(0));
      float16x8_t vacc1x089ABCDEF = vmulq_f16(vi1x089ABCDEF, vw89ABCDEF);
      const uint16x8_t vm1x089ABCDEF = vcltq_s16(vreinterpretq_s16_f16(vi1x089ABCDEF), vmovq_n_s16(0));

      vacc0x001234567 = vbslq_f16(vm0x001234567, vacc0x001234567, vi0x001234567);
      vacc0x089ABCDEF = vbslq_f16(vm0x089ABCDEF, vacc0x089ABCDEF, vi0x089ABCDEF);
      vacc1x001234567 = vbslq_f16(vm1x001234567, vacc1x001234567, vi1x001234567);
      vacc1x089ABCDEF = vbslq_f16(vm1x089ABCDEF, vacc1x089ABCDEF, vi1x089ABCDEF);

      vst1q_f16(o0, vacc0x001234567); o0 += 8;
      vst1q_f16(o0, vacc0x089ABCDEF); o0 += 8;
      vst1q_f16(o1, vacc1x001234567); o1 += 8;
      vst1q_f16(o1, vacc1x089ABCDEF); o1 += 8;
    }
    for (; c >= 8 * sizeof(__fp16); c -= 8 * sizeof(__fp16)) {
      const float16x8_t vw01234567 = vld1q_f16(w); w += 8;

      const float16x8_t vi0x01234567 = vld1q_f16(i0);
      i0 += 8;
      const float16x8_t vi1x01234567 = vld1q_f16(i1);
      i1 += 8;

      float16x8_t vacc0x01234567 = vmulq_f16(vi0x01234567, vw01234567);
      const uint16x8_t vm0x01234567 = vcltq_s16(vreinterpretq_s16_f16(vi0x01234567), vmovq_n_s16(0));
      float16x8_t vacc1x01234567 = vmulq_f16(vi1x01234567, vw01234567);
      const uint16x8_t vm1x01234567 = vcltq_s16(vreinterpretq_s16_f16(vi1x01234567), vmovq_n_s16(0));

      vacc0x01234567 = vbslq_f16(vm0x01234567, vacc0x01234567, vi0x01234567);
      vacc1x01234567 = vbslq_f16(vm1x01234567, vacc1x01234567, vi1x01234567);

      vst1q_f16(o0, vacc0x01234567); o0 += 8;
      vst1q_f16(o1, vacc1x01234567); o1 += 8;
    }
    if XNN_UNLIKELY(c != 0) {
      const float16x8_t vw01234567 = vld1q_f16(w); w += 8;

      const float16x8_t vi0x01234567 = vld1q_f16(i0);
      i0 = (const __fp16*) ((uintptr_t) i0 + c);
      const float16x8_t vi1x01234567 = vld1q_f16(i1);
      i1 = (const __fp16*) ((uintptr_t) i1 + c);

      float16x8_t vacc0x01234567 = vmulq_f16(vi0x01234567, vw01234567);
      const uint16x8_t vm0x01234567 = vcltq_s16(vreinterpretq_s16_f16(vi0x01234567), vmovq_n_s16(0));
      float16x8_t vacc1x01234567 = vmulq_f16(vi1x01234567, vw01234567);
      const uint16x8_t vm1x01234567 = vcltq_s16(vreinterpretq_s16_f16(vi1x01234567), vmovq_n_s16(0));

      vacc0x01234567 = vbslq_f16(vm0x01234567, vacc0x01234567, vi0x01234567);
      vacc1x01234567 = vbslq_f16(vm1x01234567, vacc1x01234567, vi1x01234567);

      float16x4_t vacc0x0123 = vget_low_f16(vacc0x01234567);
      float16x4_t vacc1x0123 = vget_low_f16(vacc1x01234567);
      if (c & (4 * sizeof(__fp16))) {
        vst1_f16(o0, vacc0x0123); o0 += 4;
        vst1_f16(o1, vacc1x0123); o1 += 4;

        vacc0x0123 = vget_high_f16(vacc0x01234567);
        vacc1x0123 = vget_high_f16(vacc1x01234567);
      }
      if (c & (2 * sizeof(__fp16))) {
        vst1_lane_u32((void*) o0, vreinterpret_u32_f16(vacc0x0123), 0); o0 += 2;
        vacc0x0123 = vext_f16(vacc0x0123, vacc0x0123, 2);
        vst1_lane_u32((void*) o1, vreinterpret_u32_f16(vacc1x0123), 0); o1 += 2;
        vacc1x0123 = vext_f16(vacc1x0123, vacc1x0123, 2);
      }
      if (c & (1 * sizeof(__fp16))) {
        vst1_lane_f16(o0, vacc0x0123, 0); o0 += 1;
        vst1_lane_f16(o1, vacc1x0123, 0); o1 += 1;
      }
    }
    i0 = (const __fp16*) ((uintptr_t) i0 + input_increment);
    o0 = (__fp16*) ((uintptr_t) o0 + output_increment);
    i1 = (const __fp16*) ((uintptr_t) i1 + input_increment);
    o1 = (__fp16*) ((uintptr_t) o1 + output_increment);
    if XNN_UNPREDICTABLE(rows < 4) {
      i1 = i0;
      o1 = o0;
    }
    rows = doz(rows, 2);
  } while (rows != 0);
}
