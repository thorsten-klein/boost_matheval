find_package(Boost 1.65.1 REQUIRED)

add_library(matheval.x3
    ast_adapted.hpp
    ast.hpp
    evaluator.cpp
    evaluator.hpp
    matheval.cpp
    math.hpp
    parser.cpp
    parser_def.hpp
    parser.hpp
)
target_include_directories(matheval.x3
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/matheval/x3>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/matheval/x3>
)
target_compile_features(matheval.x3
    PUBLIC 
        cxx_std_14
)
target_link_libraries(matheval.x3
    PUBLIC
        Boost::boost
)

set_target_properties(matheval.x3 PROPERTIES EXPORT_NAME x3)

add_library(matheval::x3 ALIAS matheval.x3)

install(
    TARGETS matheval.x3
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    EXPORT ${PROJECT_NAME}
)
