APPL_COBJS +=

APPL_CXXOBJS += RMD_main.o SW_ButtonController.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(WORKSPACE_LIB_DIR)/libcpp-ev3/Makefile

endif
