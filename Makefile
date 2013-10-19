PTL_PATH = PeripheralTemplateLibrary
include $(PTL_PATH)/Makefile.rules

ALL = simplejtag_l0

.PHONY: $(ALL)

all: $(ALL)

simplejtag_l0: $(TARGETDIR)/simplejtag_l0

deploy: deploy-simplejtag_l0
