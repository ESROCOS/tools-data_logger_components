# ======================================================================
#  FILE:  $URL$
# ======================================================================
#  PROJECT:             :  data_logger_components
#  VERSION              :  @VERION@
#  LANGUAGE             :  CMake script
#  AUTHOR               :  @AUTHOR@
#  COPYRIGHT            :  @COPYRIGHT@
#  COMPILER             :  cmake version 3.0.2
#  CREATED              :  @CREATED@
#  CLASS                :  -
#  LAST MODIFIED        :  @LASTMODIFIED@
#  GENERATED FROM MODEL :  -
#  ORIGINAL MODEL AUTHOR:  -
# ----------------------------------------------------------------------
#  @DESCRIPTION@
# ----------------------------------------------------------------------
#  HISTORY
#  $History$
# ======================================================================

cmake_minimum_required(VERSION 3.2)

project(data_logger_components)

include($ENV{ESROCOS_CMAKE})

#required function call to set up esrocos
esrocos_init()

########### FOR INTEGRATION PROJECTS ##############

#uncomment if you want to add dependencies for the build process (only required in integration projects)
esrocos_add_dependency(PARTITION test_logger
                       MODULES   data_logger)

########### FOR COMPONENT PROJECTS ################

#uncomment if you want to export a function
esrocos_export_function("motion_command2d_logger" "share/taste_components/data_loggers")
esrocos_export_function("rbs_logger" "share/taste_components/data_loggers")
esrocos_export_function("double_logger" "share/taste_components/data_loggers")

#uncomment to export PKG-CONFIG-file
esrocos_export_pkgconfig( VERSION 1.0
                          DESCRIPTION "none"
                          REQUIRES "ldata_logger"
                          LIBS ""
                          STATIC_LIBS "" 
                          C_FLAGS ""
                        ) 
