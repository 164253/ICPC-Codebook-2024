CLANG_FORMAT = clang-format

ifeq ($(OS),Windows_NT)
    OS_NAME := windows
    MV = move
    SEP = \\
    PYTHONCMD = python
    FORMAT_CMD = for /R nacl %%f in (*.c *.h *.cpp *.hpp) do $(CLANG_FORMAT) -i "%%f"
else
    OS_NAME := linux
    MV = mv
    SEP = /
    PYTHONCMD = python3
    FORMAT_CMD = find nacl/ -type f -regex ".*\.\(c\|h\|cpp\|hpp\)" -exec $(CLANG_FORMAT) -i {} +
endif

help:
	@echo "Available commands:"
	@echo "    make help           - Show this help"
	@echo "    make codebook       - Build the codebook PDF"
	@echo "    make format         - Run clang-format on all source files"
	@echo "    make tests          - Compile all the tests"
	@echo "    make clean-latex    - Remove LaTeX build files"
	@echo "    make clean-tests    - Remove test files"
	@echo "    make clean          - Clean up all build processes"

codebook: format
	$(PYTHONCMD) gen_config.py
	$(MAKE) -C codebook all OS_NAME=$(OS_NAME) MV=$(MV) SEP=$(SEP) PYTHONCMD=$(PYTHONCMD)
	$(MV) codebook$(SEP)main.pdf codebook.pdf

format:
	$(FORMAT_CMD)

tests:
	$(MV) codebook$(SEP)main.pdf codebook.pdf

clean-latex:
	$(MAKE) -C codebook clean OS_NAME=$(OS_NAME) MV=$(MV)
