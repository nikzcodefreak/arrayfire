FILE(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/kernel/scan_by_key/scan_by_key_impl.cpp" FILESTRINGS)

FOREACH(STR ${FILESTRINGS})
    IF(${STR} MATCHES "// SBK_BINARY_OPS")
        STRING(REPLACE "// SBK_BINARY_OPS:" "" TEMP ${STR})
        STRING(REPLACE " " ";" SBK_BINARY_OPS ${TEMP})
    ENDIF()
ENDFOREACH()

FOREACH(SBK_BINARY_OP ${SBK_BINARY_OPS})
    ADD_LIBRARY(opencl_scan_by_key_${SBK_BINARY_OP} OBJECT
        "${CMAKE_CURRENT_SOURCE_DIR}/kernel/scan_by_key/scan_by_key_impl.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/kernel/scan_first_by_key_impl.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/kernel/scan_dim_by_key_impl.hpp")
    ADD_DEPENDENCIES(opencl_scan_by_key_${SBK_BINARY_OP} ${cl_kernel_targets})
    IF(NOT USE_SYSTEM_CL2HPP)
        ADD_DEPENDENCIES(opencl_scan_by_key_${SBK_BINARY_OP} cl2hpp)
    ENDIF()
    IF(FORGE_FOUND AND NOT USE_SYSTEM_FORGE)
        ADD_DEPENDENCIES(opencl_scan_by_key_${SBK_BINARY_OP} forge)
    ENDIF()
    SET_TARGET_PROPERTIES(opencl_scan_by_key_${SBK_BINARY_OP} PROPERTIES COMPILE_FLAGS "-DTYPE=${SBK_BINARY_OP}")
    LIST(APPEND SCAN_BY_KEY_OBJECTS $<TARGET_OBJECTS:opencl_scan_by_key_${SBK_BINARY_OP}>)
ENDFOREACH(SBK_BINARY_OP ${SBK_BINARY_OPS})
