add_library(call_finder SHARED
        ASTConsumer.cc
        PluginASTAction.cc
        PPCallbacks.cc
        RecursiveASTVisitor.cc
)

target_include_directories(call_finder PUBLIC
        ${CLANG_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_definitions(call_finder PUBLIC ${CLANG_DEFINITIONS})
target_compile_features(call_finder PUBLIC cxx_std_20)
target_compile_options(call_finder PUBLIC
        -Wall
        -Wextra
        -Werror 
        -Wpedantic
        -Wno-unused-parameter
        -fno-exceptions
        -fno-rtti
)
