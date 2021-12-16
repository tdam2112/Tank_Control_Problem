cmake_minimum_required(VERSION 3.0.2)
project(solution)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    actionlib
    actionlib_msgs
    tank
)

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS roscpp actionlib actionlib_msgs
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

# Additional files may be compiled by adding them next to "src/main.cpp"
add_executable(${PROJECT_NAME} src/main.cpp src/client.cpp)
add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})