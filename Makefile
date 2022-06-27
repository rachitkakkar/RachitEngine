debug:
	cmake --build build/debug-make
	./compile-shaders-macos.sh
	./build/debug-make/RachitEngine

release:
	cmake --build build/release-make
	./compile-shaders-macos.sh
	./build/release-make/RachitEngine