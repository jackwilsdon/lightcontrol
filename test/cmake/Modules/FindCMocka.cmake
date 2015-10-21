# FindCMocka
# ----------
# Tries to find CMocka
#
# Variables:
#  CMOCKA_ROOT_DIR - Set this variable to the root installation of CMocka
#
# Read-Only variables:
#  CMOCKA_FOUND - system has CMocka
#  CMOCKA_INCLUDE_DIR - the CMocka include directory
#  CMOCKA_LIBRARIES - Link these to use CMocka
#  CMOCKA_DEFINITIONS - Compiler switches required for using CMocka
#

include(FindPackageHandleStandardArgs)

set(CMOCKA_ROOT_DIR ${CMOCKA_ROOT_DIR} CACHE PATH "Root installation directory of CMocka")

find_path(CMOCKA_INCLUDE_DIR
  NAMES cmocka.h
  PATHS ${CMOCKA_ROOT_DIR}/include
  NO_DEFAULT_PATH
)

find_library(CMOCKA_LIBRARY
  NAMES cmocka
  PATHS ${CMOCKA_ROOT_DIR}/lib
  NO_DEFAULT_PATH
)

message(STATUS "CMOCKA_INCLUDE_DIR = " ${CMOCKA_INCLUDE_DIR})
message(STATUS "CMOCKA_LIBRARY = " ${CMOCKA_LIBRARY})

find_package_handle_standard_args(CMocka DEFAULT_MSG CMOCKA_LIBRARY CMOCKA_INCLUDE_DIR)

mark_as_advanced(CMOCKA_INCLUDE_DIR CMOCKA_LIBRARY)

