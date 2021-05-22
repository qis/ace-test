MAKEFLAGS += --no-print-directory

CMAKE = /opt/cmake/bin/cmake
TOOLCHAIN = $(ACE)/llvm.cmake
SHARED = ON
NAME = ace

all: llvm msvc

llvm:
	@rm -rf build
	@$(MAKE) test TOOLCHAIN=$(ACE)/llvm.cmake SHARED=ON  NAME=llvm-shared
	@$(MAKE) test TOOLCHAIN=$(ACE)/llvm.cmake SHARED=OFF NAME=llvm-static
	@echo ""

msvc:
	@rm -rf build
	@$(MAKE) test TOOLCHAIN=$(ACE)/msvc.cmake SHARED=ON  NAME=msvc-shared
	@$(MAKE) test TOOLCHAIN=$(ACE)/msvc.cmake SHARED=OFF NAME=msvc-static

check:
	@echo ""
	@$(ACE)/llvm/bin/clang --version >/dev/null
	@$(ACE)/llvm/bin/clang-format --version >/dev/null
	@$(ACE)/llvm/bin/clang-tidy --version >/dev/null
	@$(ACE)/llvm/bin/clangd --version >/dev/null
	@$(ACE)/llvm/bin/lld-link --version >/dev/null
	@$(ACE)/llvm/bin/lldb --version >/dev/null
	@$(ACE)/llvm/bin/lldb-instr --version >/dev/null
	@$(ACE)/llvm/bin/lldb-server version 2>/dev/null
	@$(ACE)/llvm/bin/lldb-vscode --help >/dev/null
	@$(ACE)/llvm/bin/llvm-ar --version >/dev/null
	@$(ACE)/llvm/bin/llvm-mt '/?' >/dev/null
	@$(ACE)/llvm/bin/llvm-objcopy --version >/dev/null
	@$(ACE)/llvm/bin/llvm-rc '/?' >/dev/null
	@echo "Checking ACE binaries: OK"
	@echo ""

test: build/$(NAME)/build.ninja
	@echo ""
	@echo "==============================================================================="
	@echo " $(NAME)-debug"
	@echo "==============================================================================="
	@$(CMAKE) --build build/$(NAME) --config Debug --target run-main
	@echo ""
	@echo "==============================================================================="
	@echo " $(NAME)-release"
	@echo "==============================================================================="
	@$(CMAKE) --build build/$(NAME) --config Release --target run-main
	@echo ""
	@echo "==============================================================================="
	@echo " $(NAME)-minsizerel"
	@echo "==============================================================================="
	@$(CMAKE) --build build/$(NAME) --config MinSizeRel --target run-main
	@echo ""
	@echo "==============================================================================="
	@echo " $(NAME)-relwithdebinfo"
	@echo "==============================================================================="
	@$(CMAKE) --build build/$(NAME) --config RelWithDebInfo --target run-main

build/$(NAME)/build.ninja:
	@$(CMAKE) -G "Ninja Multi-Config" --no-warn-unused-cli \
	  -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
	  -DBUILD_SHARED_LIBS=$(SHARED) \
	  -B build/$(NAME)
