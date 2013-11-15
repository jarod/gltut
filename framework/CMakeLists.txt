project(framework)

# make data dir display in QtCreator Projects view
file(GLOB FILES ../data/* *.cpp *.h)
list(REMOVE_ITEM FILES "${framework_SOURCE_DIR}/empty.cpp")

add_library(${PROJECT_NAME} STATIC ${FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
