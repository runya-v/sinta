add_custom_target("untar_ctpp" ALL)
add_custom_command(
	TARGET "untar_ctpp"
	COMMAND "tar"
	ARGS "xzvf ctpp2-2.8.3.tar.gz"
	DEPENDS "ctpp2-2.8.3"
	)

add_custom_target("path_ctpp" ALL)
add_custom_command(
	TARGET "path_ctpp"
	COMMAND "path"
	ARGS "-p0 ctpp2-2.8.3/src/CTPP2FileSourceLoader.cpp -i CTPP2FileSourceLoader.cpp.diff"
	DEPENDS "untar_ctpp"
	)

add_custom_target("mkdir_bld_ctpp" ALL)
add_custom_command(
	TARGET "mkdir_bld_ctpp"
	COMMAND "mkdir"
	ARGS "bld"
	DEPENDS "path_ctpp"
	)

add_custom_target("cmake_ctpp" ALL)
add_custom_command(
	TARGET "cmake_ctpp"
	WORKING_DIRECTORY "ctpp2-2.8.3/bld"
	COMMAND "cmake"
	ARGS ".."
	DEPENDS "mkdir_bld_ctpp"
	)

add_custom_target("make_ctpp" ALL)
add_custom_command(
	TARGET "make_ctpp"
	WORKING_DIRECTORY "ctpp2-2.8.3/bld"
	COMMAND "make"
	ARGS "-j$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)"
	DEPENDS "cmake_ctpp"
	)
