# utils used for compatible for fluid op system
add_subdirectory(compat)

if(WITH_GPU)
  cc_library(convert_utils SRCS convert_utils.cc DEPS data_type place gpu_info)
elseif(WITH_ROCM)
  cc_library(convert_utils SRCS convert_utils.cc DEPS data_type place gpu_info)
else()
  cc_library(convert_utils SRCS convert_utils.cc DEPS data_type place)
endif()

cc_library(errors SRCS errors.cc)
set(pten_enforce_deps errors flags)
if(WITH_GPU)
  set(pten_enforce_deps ${pten_enforce_deps} external_error_proto)
endif()
cc_library(pten_enforce INTERFACE SRCS enforce.cc DEPS ${pten_enforce_deps})

cc_library(kernel_factory SRCS kernel_factory.cc DEPS pten_enforce convert_utils)
cc_library(kernel_context SRCS kernel_context.cc DEPS pten_enforce pten_context)

cc_library(tensor_base SRCS tensor_base.cc allocator.cc storage.cc DEPS pten_enforce)
cc_library(tensor_meta SRCS tensor_meta.cc DEPS pten_enforce mixed_vector)
cc_library(lod_utils SRCS lod_utils.cc DEPS pten_enforce mixed_vector)
cc_library(sparse_coo_tensor SRCS sparse_coo_tensor.cc DEPS tensor_meta tensor_base)
cc_library(sparse_csr_tensor SRCS sparse_csr_tensor.cc DEPS dense_tensor tensor_base)
cc_library(dense_tensor SRCS dense_tensor.cc dense_tensor_impl.cc DEPS convert_utils tensor_meta tensor_base)
cc_library(pten_device_context SRCS device_context.cc DEPS tensor_base )

cc_library(meta_tensor SRCS meta_tensor.cc DEPS tensor_base tensor_meta dense_tensor)
cc_library(infermeta_utils SRCS infermeta_utils.cc DEPS meta_tensor)
cc_library(selected_rows SRCS selected_rows.cc DEPS dense_tensor mixed_vector pten_enforce ddim)

cc_test(unroll_array_ops_test SRCS unroll_array_ops_test.cc)
cc_library(ddim SRCS ddim.cc DEPS eigen3 boost enforce)

# Will remove once we implemented MKLDNN_Tensor
if(WITH_MKLDNN)
    add_dependencies(dense_tensor mkldnn)
    add_dependencies(tensor_base mkldnn)
endif()
