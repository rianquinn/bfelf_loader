# ------------------------------------------------------------------------------
# CMake Includes
# ------------------------------------------------------------------------------

include("${CMAKE_INSTALL_PREFIX}/cmake/CMakeGlobal_Includes.txt")
include("${CMAKE_INSTALL_PREFIX}/cmake/CMakeOption_Testing.txt")

# ------------------------------------------------------------------------------
# Custom Flags
# ------------------------------------------------------------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBAREFLANK_SYSROOT_PATH=\\\"${BAREFLANK_SYSROOT_PATH}\\\"")

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------

add_library(test_support STATIC test_real_elf.cpp test_fake_elf.cpp)

macro(do_test str)
    add_executable(test_${str} test_${str}.cpp )
    target_link_libraries(test_${str} test_support)
    add_test(bfelf_${str} test_${str})
endmacro(do_test)

do_test(file_get_entry)
do_test(file_get_load_instr)
do_test(file_get_needed)
do_test(file_get_num_load_instrs)
do_test(file_get_num_needed)
do_test(file_get_pic_pie)
do_test(file_get_relro)
do_test(file_get_section_info)
do_test(file_get_stack_perm)
do_test(file_get_total_size)
do_test(file_init)
do_test(loader_add)
do_test(loader_relocate)
do_test(loader_resolve_symbol)
do_test(helpers)
do_test(real)