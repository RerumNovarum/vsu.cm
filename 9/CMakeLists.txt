cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 11)

file(GLOB PY_SCRIPTS "*.py")
file(COPY ${PY_SCRIPTS} DESTINATION "./")

add_executable(td2tex tridiag-to-tex.cpp)
add_executable(tdsolv tridiagsolve.cpp)
add_executable(error error.cpp)
add_executable(stats stats.cpp)
add_executable(row row.cpp)
add_executable(row_add row_add.cpp)
