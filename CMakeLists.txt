cmake_minimum_required(VERSION 3.10)

project(VRR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug")
set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(PROJECT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# GLM
set(GLM_DIR "${PROJECT_INCLUDE_DIR}/glm")
add_subdirectory(${GLM_DIR} EXCLUDE_FROM_ALL)

# STB
set(STB_DIR "${PROJECT_INCLUDE_DIR}/stb")

#GLAD
set(GLAD_DIR "${PROJECT_INCLUDE_DIR}/glad")

add_executable(${PROJECT_NAME}
${PROJECT_SOURCE_DIR}/main.cpp
${PROJECT_SOURCE_DIR}/VRRenderer/glad.c
${PROJECT_SOURCE_DIR}/VRRenderer/shaderClass.cpp
${PROJECT_SOURCE_DIR}/VRRenderer/VBO.cpp 
${PROJECT_SOURCE_DIR}/VRRenderer/EBO.cpp 
${PROJECT_SOURCE_DIR}/VRRenderer/VAO.cpp 
${PROJECT_SOURCE_DIR}/VRRenderer/stb.cpp 
${PROJECT_SOURCE_DIR}/VRRenderer/Texture.cpp 
${PROJECT_SOURCE_DIR}/VRRenderer/Camera.cpp 
${PROJECT_SOURCE_DIR}/VRRenderer/Mesh.cpp
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC
		"${PROJECT_INCLUDE_DIR}/*"
	PRIVATE
		"${PROJECT_SOURCE_DIR}"
)

target_include_directories(${PROJECT_NAME} PUBLIC GL)
target_link_libraries(${PROJECT_NAME} glm GL glfw dl)

message([CMAKE_RUNTIME_OUTPUT_DIRECTORY]    :\t-- ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message([CMAKE_BINARY_DIR]      :\t-- ${CMAKE_BINARY_DIR})
message([PROJECT_SOURCE_DIR]    :\t-- ${PROJECT_SOURCE_DIR})
message([PROJECT_INCLUDE_DIR]   :\t-- ${PROJECT_INCLUDE_DIR})
message([GLM_DIR]               :\t-- ${GLM_DIR})
message([STB_DIR]               :\t-- ${STB_DIR})
message([GLAD_DIR]               :\t-- ${GLAD_DIR})