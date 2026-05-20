add_library(formatter STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/formatter.cpp)
target_include_directories(formatter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
