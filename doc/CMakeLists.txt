# Add documentation target
if( ${DOXYGEN_FOUND} STREQUAL "YES" )
  if( ${LATEX_FOUND} )
    add_custom_target( doc
      ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/doxyfile"
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.."
      COMMENT "Generating API documentation with Doxygen." VERBATIM
      )
  endif()
endif()

