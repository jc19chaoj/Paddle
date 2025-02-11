/* Copyright (c) 2022 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#include "paddle/pten/infermeta/backward.h"

namespace pten {

std::tuple<DenseTensorMeta, DenseTensorMeta> MatmulGradInferMeta(
    const DenseTensorMeta& x_meta,
    const DenseTensorMeta& y_meta,
    const DenseTensorMeta& out_grad_meta,
    bool transpose_x,
    bool transpose_y) {
  return std::make_tuple(x_meta, y_meta);
}

}  // namespace pten
