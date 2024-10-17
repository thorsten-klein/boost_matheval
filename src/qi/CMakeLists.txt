find_package(Boost 1.65.1 REQUIRED)

add_library(matheval.qi
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
target_include_directories(matheval.qi
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/matheval/qi>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/matheval/qi>
)
target_compile_features(matheval.qi
    PUBLIC 
        cxx_std_98
)
target_link_libraries(matheval.qi
    PUBLIC
        Boost::boost
)

set_target_properties(matheval.qi PROPERTIES EXPORT_NAME qi)

add_library(matheval::qi ALIAS matheval.qi)

install(
    TARGETS matheval.qi 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    EXPORT ${PROJECT_NAME}
)

