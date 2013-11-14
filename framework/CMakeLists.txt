project(framework)

# make data dir display in QtCreator Projects view
file(GLOB FILES ../data/* *.cpp *.h)

add_library(${PROJECT_NAME} STATIC ${FILES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
