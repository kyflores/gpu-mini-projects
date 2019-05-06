set(VEC_MULTIPLY_SRC
    vector_multiply.cc)

set(COMPILER_FLAGS "-g --std=c++17")

add_executable(VectorMultiply ${VEC_MULTIPLY_SRC})
target_include_directories(VectorMultiply PRIVATE .)
set_target_properties(VectorMultiply PROPERTIES COMPILE_FLAGS ${COMPILER_FLAGS})