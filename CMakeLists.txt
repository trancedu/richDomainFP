cmake_minimum_required(VERSION 3.12)
project(FinancialProductsDemo)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(FinancialDemo
    main.cpp
    FinancialProducts.h
    FinancialProducts.cpp
)

# Enable C++20 modules if needed (though not used in this example)
target_compile_features(FinancialDemo PRIVATE cxx_std_20) 