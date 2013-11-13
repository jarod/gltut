project(tut01)

add_executable(${PROJECT_NAME} tut1.cpp ../framework/framework.cpp)

target_link_libraries(${PROJECT_NAME} ${LIBS})
