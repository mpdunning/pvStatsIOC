TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = pvStats
DBD += pvStats.dbd

pvStats_DBD += base.dbd
pvStats_DBD += asSupport.dbd
pvStats_DBD += pvStatsSup.dbd

pvStats_LIBS += autosave 

pvStats_SRCS += pvStats_registerRecordDeviceDriver.cpp
pvStats_SRCS += pvStatsASub.c

pvStats_SRCS_DEFAULT += main.cpp
pvStats_SRCS_vxWorks += -nil-

pvStats_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

