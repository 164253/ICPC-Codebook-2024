BUILD_DIR   = build
LATEX       = xelatex
LATEX_FLAGS = -shell-escape -output-directory $(BUILD_DIR)
export TEXMF_OUTPUT_DIRECTORY := $(BUILD_DIR)

ifeq ($(OS_NAME),linux)
    RM = rm -rf
    PYTHONCMD = python3
    MKDIR = mkdir -p
else ifeq ($(OS_NAME),windows)
    RM = rmdir /s /q
    PYTHONCMD = python
    MKDIR = mkdir
endif

$(info OS_NAME=$(OS_NAME))
$(info PYTHONCMD=$(PYTHONCMD))

all: build content
	$(LATEX) $(LATEX_FLAGS) main.tex && $(LATEX) $(LATEX_FLAGS) main.tex
	$(MV) $(BUILD_DIR)$(SEP)main.pdf .

clean:
	$(RM) $(BUILD_DIR)

build:
	$(MKDIR) $(BUILD_DIR)

content:
	echo \newcommand{\pythoncmd}{$(PYTHONCMD)} > pythoncmd.tex
	$(PYTHONCMD) content-generator.py config.yaml $(BUILD_DIR)$(SEP)content.tex
