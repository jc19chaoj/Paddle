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

#pragma once

#include <memory>

// TODO(wilber): Do we need to use place in pten kernel?
#include "paddle/pten/common/place.h"

#include "paddle/pten/common/data_type.h"
#include "paddle/pten/core/allocator.h"

namespace pten {
class TensorBase;

/**
 * DeviceContext provides device-related interfaces.
 *
 * All kernels must access the interfaces provided by the backend through
 * DeviceContext.
 */
class DeviceContext {
  using DataType = paddle::experimental::DataType;

 public:
  /**
   * @brief Default construct.
   */
  DeviceContext();

  /**
   * @brief Copy construct.
   */
  DeviceContext(const DeviceContext&);

  /**
   * @brief Move construct.
   */
  DeviceContext(DeviceContext&&);

  /**
   * @brief Default destruct.
   */
  virtual ~DeviceContext();

  /**
   * @brief Set the device-related Allocator object.
   *
   * @param allocator
   */
  void SetDeviceAllocator(const Allocator*);

  /**
   * @brief Set the host Allocator object.
   *
   * @param allocator
   */
  void SetHostAllocator(const Allocator*);

  /**
  * @brief Set the zero-size Allocator object.
  *
  * @param allocator
  */
  void SetZeroAllocator(const Allocator*);

  /**
   * @brief Get the const Allocator object.
   *
   * @return Allocator
   */
  const Allocator& GetDeviceAllocator() const;

  /**
   * @brief Get the const device-related Allocator object.
   *
   * @return Allocator
   */
  const Allocator& GetHostAllocator() const;

  const Allocator& GetZeroAllocator() const;

  /**
   * @brief Allocate device memory for tensor.
   */
  void* Alloc(TensorBase*,
              DataType dtype = DataType::UNDEFINED,
              size_t requested_size = 0) const;

  template <typename T>
  T* Alloc(TensorBase* tensor, size_t requested_size = 0) const;

  /**
   * @brief Allocate host memory for tensor.
   */
  void* HostAlloc(TensorBase* tensor,
                  DataType dtype = DataType::UNDEFINED,
                  size_t requested_size = 0) const;

  template <typename T>
  T* HostAlloc(TensorBase* tensor, size_t requested_size = 0) const;

  // TODO(wilber): Just for the convenience of migrating the code, it will be
  // modified or removed later.
  virtual Place GetPlace() const = 0;
  // TODO(wilber): The fluid framework uses wait() in many places, how to delete
  // this API interface.
  virtual void Wait() const {}

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace pten
