cmake_minimum_required(VERSION 3.12)
project(FinancialProductsDemo)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(FinancialDemo
    main.cpp
    FinancialProduct.cpp
    Pricer.cpp
    Swap.cpp
    Option.cpp
)

target_include_directories(FinancialDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) 