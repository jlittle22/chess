# Declare new library
add_library(game game.cpp piece.cpp)

# Define include directory for our new library.
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})