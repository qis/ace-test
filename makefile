MAKEFLAGS += --no-print-directory

CMAKE = /opt/cmake/bin/cmake
TOOLCHAIN = $(ACE)/llvm.cmake
EXCEPTIONS = OFF
SHARED = ON
NAME = ace

all: ace

ace:
	@rm -rf build
	@$(MAKE) test TOOLCHAIN=$(ACE)/llvm.cmake EXCEPTIONS=OFF SHARED=ON  NAME=llvm-shared
	@$(MAKE) test TOOLCHAIN=$(ACE)/llvm.cmake EXCEPTIONS=OFF SHARED=OFF NAME=llvm-static
	@echo ""

msvc:
	@rm -rf build
	@$(MAKE) test TOOLCHAIN=$(ACE)/msvc.cmake EXCEPTIONS=OFF SHARED=ON  NAME=msvc-shared
	@$(MAKE) test TOOLCHAIN=$(ACE)/msvc.cmake EXCEPTIONS=OFF SHARED=OFF NAME=msvc-static
	@$(MAKE) test TOOLCHAIN=$(ACE)/msvc.cmake EXCEPTIONS=ON  SHARED=ON  NAME=msvc-shared-exceptions
	@$(MAKE) test TOOLCHAIN=$(ACE)/msvc.cmake EXCEPTIONS=ON  SHARED=OFF NAME=msvc-static-exceptions

llvm:
	@rm -rf build
	@$(MAKE) test TOOLCHAIN=/opt/llvm/toolchain.cmake EXCEPTIONS=ON  SHARED=ON  NAME=llvm-shared-exceptions
	@$(MAKE) test TOOLCHAIN=/opt/llvm/toolchain.cmake EXCEPTIONS=ON  SHARED=OFF NAME=llvm-static-exceptions

check:
	@echo ""
	@$(ACE)/bin/clang --version >/dev/null
	@$(ACE)/bin/clang-format --version >/dev/null
	@$(ACE)/bin/clang-tidy --version >/dev/null
	@$(ACE)/bin/clangd --version >/dev/null
	@$(ACE)/bin/lld-link --version >/dev/null
	@$(ACE)/bin/lldb --version >/dev/null
	@$(ACE)/bin/lldb-instr --version >/dev/null
	@$(ACE)/bin/lldb-server version 2>/dev/null
	@$(ACE)/bin/lldb-vscode --help >/dev/null
	@$(ACE)/bin/llvm-ar --version >/dev/null
	@$(ACE)/bin/llvm-mt '/?' >/dev/null
	@$(ACE)/bin/llvm-objcopy --version >/dev/null
	@$(ACE)/bin/llvm-rc '/?' >/dev/null
	@echo "Checking ACE binaries: OK"
	@echo ""

test: build/$(NAME)/build.ninja
	@echo ""
	@echo "==============================================================================="
	@echo " $(NAME)-debug"
	@echo "==============================================================================="
	@$(CMAKE) --build build/$(NAME) --config Debug --target run-main
	@$(CMAKE) --build build/$(NAME) --config Debug --target run-tests
	@$(CMAKE) --build build/$(NAME) --config Debug --target run-benchmarks
	@echo ""
	@echo "==============================================================================="
	@echo " $(NAME)-release"
	@echo "==============================================================================="
	@$(CMAKE) --build build/$(NAME) --config Release --target run-main
	@$(CMAKE) --build build/$(NAME) --config Release --target run-tests
	@$(CMAKE) --build build/$(NAME) --config Release --target run-benchmarks
	@echo ""
	@echo "==============================================================================="
	@echo " $(NAME)-minsizerel"
	@echo "==============================================================================="
	@$(CMAKE) --build build/$(NAME) --config MinSizeRel --target run-main
	@$(CMAKE) --build build/$(NAME) --config MinSizeRel --target run-tests
	@$(CMAKE) --build build/$(NAME) --config MinSizeRel --target run-benchmarks
	@echo ""
	@echo "==============================================================================="
	@echo " $(NAME)-relwithdebinfo"
	@echo "==============================================================================="
	@$(CMAKE) --build build/$(NAME) --config RelWithDebInfo --target run-main
	@$(CMAKE) --build build/$(NAME) --config RelWithDebInfo --target run-tests
	@$(CMAKE) --build build/$(NAME) --config RelWithDebInfo --target run-benchmarks

build/$(NAME)/build.ninja:
	@$(CMAKE) -G "Ninja Multi-Config" --no-warn-unused-cli \
	  -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
	  -DLLVM_ENABLE_EXCEPTIONS=$(EXCEPTIONS) \
	  -DBUILD_SHARED_LIBS=$(SHARED) \
	  -B build/$(NAME)
