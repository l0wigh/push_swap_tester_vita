set(Project "push_swap_tester")

cmake_minimum_required(VERSION 3.19)

set(CMAKE_TOOLCHAIN_FILE "$ENV{SCE_PSP2_SDK_DIR}/host_tools/build/cmake/psp2-snc-toolchain.cmake")

project(${Project} LANGUAGES C CXX)

include(VitaDevelopmentSuite)

add_compile_options(
    -Xdiag=2 -Xquit=2
)

include_directories(SYSTEM
  ${VDSUITE_USER_INCLUDE_DIRECTORIES}
)

link_directories(
  ${VDSUITE_LIBRARY_DIRECTORIES}
)


add_executable(${Project}
    src/push_swap.h
    src/ps_func.c
    src/better_sort.c
    src/main.c
)

target_link_libraries(${Project}
    SceDisplayUser_stub
    SceTouch_stub
    SceCtrl_stub
    SceDbgFont
)

VDSuiteCreateSfo(${Project}-param.sfo param.yml)

VDSuitePackage(${Project}.vpk
    FILES
        $<TARGET_FILE:${Project}> eboot.bin
        ${Project}-param.sfo sce_sys/param.sfo
)
