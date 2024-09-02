add_llvm_executable(svf-ex-double-free svf-ex-double-free.cpp)
target_link_libraries(svf-ex-double-free PUBLIC ${llvm_libs} SvfLLVM)