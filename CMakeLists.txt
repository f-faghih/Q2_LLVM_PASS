 cmake_minimum_required(VERSION 3.10)

   project(MyLLVMPass)

   find_package(LLVM REQUIRED CONFIG)

   set(CMAKE_CXX_STANDARD 17)
   set(CMAKE_CXX_STANDARD_REQUIRED YES)
   set(CMAKE_CXX_EXTENSIONS NO)

   include_directories(${LLVM_INCLUDE_DIRS})
   add_definitions(${LLVM_DEFINITIONS})

   add_library(mypass MODULE mypass.cpp)
   target_link_libraries(mypass PRIVATE LLVM)