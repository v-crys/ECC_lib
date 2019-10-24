cmake_minimum_required(VERSION 2.8)

project(ECC_class)


#---- src
FILE(GLOB_RECURSE INC_FILES "include/*.h")
FILE(GLOB_RECURSE SRC_FILES "src/*.cpp")

#---- dir
SET(SRC_DIR "src")
SET(INC_DIR "include")


INCLUDE_DIRECTORIES(
  ${SRC_DIR}/.
  ${INC_DIR}/.
)

add_executable(${PROJECT_NAME} "main.cpp" "Matrix.h" "Vector.h" ${INC_FILES} ${SRC_FILES} )
