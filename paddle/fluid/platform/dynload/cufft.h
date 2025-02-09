/* Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once
#ifdef PADDLE_WITH_CUDA
#include <cufft.h>
#include <cufftXt.h>
#include <glog/logging.h>
#include <mutex>  // NOLINT

#include "paddle/pten/backends/dynload/cufft.h"

namespace paddle {
namespace platform {
namespace dynload {

extern bool HasCUFFT();

#define PLATFORM_DECLARE_DYNAMIC_LOAD_CUFFT_WRAP(__name)      \
  using DynLoad__##__name = pten::dynload::DynLoad__##__name; \
  extern DynLoad__##__name __name

/**
 * include all needed cufft functions in HPPL
 * different cufft version has different interfaces
 **/
#define CUFFT_FFT_ROUTINE_EACH(__macro)  \
  __macro(cufftPlan1d);                  \
  __macro(cufftPlan2d);                  \
  __macro(cufftPlan3d);                  \
  __macro(cufftPlanMany);                \
  __macro(cufftMakePlan1d);              \
  __macro(cufftMakePlan2d);              \
  __macro(cufftMakePlan3d);              \
  __macro(cufftMakePlanMany);            \
  __macro(cufftMakePlanMany64);          \
  __macro(cufftGetSizeMany64);           \
  __macro(cufftEstimate1d);              \
  __macro(cufftEstimate2d);              \
  __macro(cufftEstimate3d);              \
  __macro(cufftEstimateMany);            \
  __macro(cufftCreate);                  \
  __macro(cufftGetSize1d);               \
  __macro(cufftGetSize2d);               \
  __macro(cufftGetSize3d);               \
  __macro(cufftGetSizeMany);             \
  __macro(cufftGetSize);                 \
  __macro(cufftSetWorkArea);             \
  __macro(cufftSetAutoAllocation);       \
  __macro(cufftExecC2C);                 \
  __macro(cufftExecR2C);                 \
  __macro(cufftExecC2R);                 \
  __macro(cufftExecZ2Z);                 \
  __macro(cufftExecD2Z);                 \
  __macro(cufftExecZ2D);                 \
  __macro(cufftSetStream);               \
  __macro(cufftDestroy);                 \
  __macro(cufftGetVersion);              \
  __macro(cufftGetProperty);             \
  __macro(cufftXtSetGPUs);               \
  __macro(cufftXtMalloc);                \
  __macro(cufftXtMemcpy);                \
  __macro(cufftXtFree);                  \
  __macro(cufftXtSetWorkArea);           \
  __macro(cufftXtExecDescriptorC2C);     \
  __macro(cufftXtExecDescriptorR2C);     \
  __macro(cufftXtExecDescriptorC2R);     \
  __macro(cufftXtExecDescriptorZ2Z);     \
  __macro(cufftXtExecDescriptorD2Z);     \
  __macro(cufftXtExecDescriptorZ2D);     \
  __macro(cufftXtQueryPlan);             \
  __macro(cufftXtSetCallback);           \
  __macro(cufftXtClearCallback);         \
  __macro(cufftXtSetCallbackSharedSize); \
  __macro(cufftXtMakePlanMany);          \
  __macro(cufftXtGetSizeMany);           \
  __macro(cufftXtExec);                  \
  __macro(cufftXtExecDescriptor);        \
  __macro(cufftXtSetWorkAreaPolicy);

CUFFT_FFT_ROUTINE_EACH(PLATFORM_DECLARE_DYNAMIC_LOAD_CUFFT_WRAP)

}  // namespace dynload
}  // namespace platform
}  // namespace paddle

#endif
