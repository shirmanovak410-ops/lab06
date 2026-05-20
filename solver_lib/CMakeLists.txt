add_library(solver_lib STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/solver.cpp)
target_include_directories(solver_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(solver_lib)
