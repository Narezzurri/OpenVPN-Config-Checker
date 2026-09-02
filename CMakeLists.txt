# Target name
set (CHECKER_NAME "Checker")
set (AUTH_NAME "Auth")
# Full name
set (CHECKER_DIR "Checker")
set (AUTH_DIR "Authenticator")
# Version
set (CHECKER_VER "1.3.0")
set (AUTH_VER "1.0.0")

function (split VERSION MAJOR MINOR PATCH)
	string (REPLACE "." ";" VERSION "${VERSION}")
	list (GET VERSION 0 major)
	list (GET VERSION 1 minor)
	list (GET VERSION 2 patch)
	set (${MAJOR} ${major} PARENT_SCOPE)
	set (${MINOR} ${minor} PARENT_SCOPE)
	set (${PATCH} ${patch} PARENT_SCOPE)
endfunction ()


cmake_minimum_required (VERSION 3.12)
project (OpenVPN-Config-Manager VERSION 2.1.0 LANGUAGES CXX HOMEPAGE_URL https://github.com/Narezzurri/OpenVPN-Config-Manager)

include_directories (.)

add_library (lib STATIC lib.cpp)

set (EXES CHECKER AUTH)
foreach (EXE ${EXES})
	add_executable (${EXE} ${CMAKE_CURRENT_SOURCE_DIR}/${${EXE}_DIR}/${EXE}.cpp)
	set_target_properties (${EXE} PROPERTIES VERSION ${${EXE}_VER} OUTPUT_NAME "${${EXE}_NAME}")
	# resource
	set (APP_NAME "${${EXE}_NAME}")
	set (APP_FULLNAME "${${EXE}_DIR}")
	split ("${${EXE}_VER}" APP_VERSION_MAJOR APP_VERSION_MINOR APP_VERSION_PATCH)
	configure_file (resource.rc.in ${CMAKE_CURRENT_BINARY_DIR}/${${EXE}_DIR}/resource.rc @ONLY)
	target_sources (${EXE} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${${EXE}_DIR}/resource.rc)
	# library
	target_link_libraries (${EXE} lib)
endforeach ()

# Install package

configure_file ("Setup.nsi.in" "Setup.nsi" @ONLY)
add_custom_target (
	build
	COMMAND ${CMAKE_COMMAND} -E echo "Building NSIS installer..."
	COMMAND makensis "${CMAKE_BINARY_DIR}/Setup.nsi"
	DEPENDS ${CMAKE_BINARY_DIR}/Setup.nsi CHECKER AUTH
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Creating NSIS installer"
)

# install (
# 	TARGETS CHECKER AUTH
# 	RUNTIME DESTINATION "."
# 	ARCHIVE DESTINATION lib
# )
# install (FILES "LICENSE" DESTINATION ".")
# install (FILES "NOTICE" DESTINATION ".")

# set (CPACK_GENERATOR "NSIS")
# set (CPACK_NSIS_LANGUAGE "English")
# set (CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
# set (CPACK_PACKAGE_NAME "OpenVPN Config Manager")
# set (CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME}")
# set (CPACK_NSIS_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
# set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
# set (CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resource/InstallerLight.ico")
# set (CPACK_NSIS_MUI_UNICON "${CMAKE_SOURCE_DIR}/resource/UninstallerLight.ico")
# set (CPACK_PACKAGE_FILE_NAME "OpenVPNConfigManagerSetup-${CPACK_PACKAGE_VERSION}")

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# include (CPack)
