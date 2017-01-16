cmake_minimum_required(VERSION 3.5)

project(SelfDev-1-2dRpg)

set(SRC
    "src/main.cpp"
)

set(LIBS
    "sfml-system"
    "sfml-graphics"
    "sfml-window"
    "sfml-audio"
    "sfml-network"
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

set(TO_INSTALL
    "asset"
)
file(INSTALL ${TO_INSTALL} DESTINATION ${PROJECT_BINARY_DIR})
