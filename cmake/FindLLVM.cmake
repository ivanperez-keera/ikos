if (NOT LLVM_FOUND)
  find_program(LLVM_CONFIG_EXECUTABLE CACHE NAMES llvm-config DOC "llvm-config executable")

  if (LLVM_CONFIG_EXECUTABLE)
    message(STATUS "LLVM llvm-config found at: ${LLVM_CONFIG_EXECUTABLE}")
  else (LLVM_CONFIG_EXECUTABLE)
    message(WARNING "Could NOT find llvm-config. Set LLVM_CONFIG_EXECUTABLE.")
  endif()

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --prefix
    OUTPUT_VARIABLE LLVM_ROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --includedir
    OUTPUT_VARIABLE LLVM_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --bindir
    OUTPUT_VARIABLE LLVM_TOOLS_BINARY_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --libdir
    OUTPUT_VARIABLE LLVM_LIBRARY_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --cppflags
    OUTPUT_VARIABLE LLVM_CPPFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --cxxflags
    OUTPUT_VARIABLE LLVM_CXXFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --ldflags
    OUTPUT_VARIABLE LLVM_LDFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --obj-root
    OUTPUT_VARIABLE LLVM_OBJ_ROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --libs core bitreader asmparser analysis
    OUTPUT_VARIABLE LLVM_MODULE_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --version
    OUTPUT_VARIABLE LLVM_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(LLVM
    REQUIRED_VARS LLVM_ROOT LLVM_INCLUDE_DIR LLVM_TOOLS_BINARY_DIR LLVM_LIBRARY_DIR LLVM_CPPFLAGS LLVM_CXXFLAGS LLVM_LDFLAGS LLVM_OBJ_ROOT LLVM_MODULE_LIBS LLVM_VERSION
    FAIL_MESSAGE "Could NOT find LLVM. Please provide -DLLVM_CONFIG_EXECUTABLE=<llvm-config-file-path>")
endif()
