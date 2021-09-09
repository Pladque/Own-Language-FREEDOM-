# CMakeList.txt : CMake project for FreedomLanguage, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME FreedomLanguage)
set(CMAKE_CXX_STANDARD 11)

include_directories(basic fem posit utils)



# Add source to this project's executable.
add_executable (FreedomLanguage "main.cpp" "FreedomLanguage.h" 
"Headers/Lexer.h" "Classes/Lexer.cpp" "Headers/Core.h" "Classes/Core.cpp" "Headers/Parser.h" "Classes/Parser.cpp"
"Headers/Token.h" "Classes/Token.cpp" "Headers/Position.h" "Classes/Position.cpp")

# TODO: Add tests and install targets if needed.
install (TARGETS FreedomLanguage DESTINATION "FreedomLanguage/bin")
