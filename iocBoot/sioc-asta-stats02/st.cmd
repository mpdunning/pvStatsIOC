#!../../bin/linux-x86_64/pvStats

< envPaths

cd ${TOP}

dbLoadDatabase "dbd/pvStats.dbd"
pvStats_registerRecordDeviceDriver pdbbase

epicsEnvSet("N",      "02")
epicsEnvSet("P",      "ASTA:PVSTATS$(N):SCOPE")
epicsEnvSet("SCOPE",  "ASTA:SCOP02")

save_restoreSet_status_prefix( "")
save_restoreSet_IncompleteSetsOk( 1)
save_restoreSet_DatedBackupFiles( 1)
set_savefile_path( "/nfs/slac/g/testfac/asta/$(IOC)","autosave")
set_pass0_restoreFile( "pvStats.sav")
set_pass1_restoreFile( "pvStats.sav")

#dbLoadRecords("db/pvStats-asta.db","P=$(P)")
dbLoadRecords("db/scope.db","P=$(P),SCOPE=$(SCOPE),IOC=$(IOC)")

#cd ${AUTOSAVE}
#dbLoadRecords( "db/save_restoreStatus.db","P=$(P)")

cd ${TOP}/iocBoot/${IOC}
iocInit

create_monitor_set( "pvStats.req",30,"P=$(P)")
