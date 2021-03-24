# CMakeList.txt: проект CMake для ip_filter2; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

cmake_minimum_required (VERSION 3.8)
project(ip_filter2 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include(${PROJECT_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Добавьте источник в исполняемый файл этого проекта.
add_executable (ip_filter2 "ip_filter2.cpp" "ip_filter2.h")

set_target_properties(ip_filter2 PROPERTIES
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON
COMPLETE_OPTIONS "-Wall")

install(TARGETS ip_filter2 RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ilianovi@mail.ru)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
