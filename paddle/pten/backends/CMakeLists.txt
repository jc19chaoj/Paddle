add_subdirectory(dynload)

add_subdirectory(cpu)

if(WITH_XPU)
  add_subdirectory(xpu)
endif()

cc_library(pten_context SRCS all_context.cc DEPS device_context cpu_context)

if(WITH_XPU)
  add_dependencies(pten_context xpu_context)
endif()
