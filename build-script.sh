#!/bin/bash -e

# This script will build your TASTE system.

# You should not change this file as it was automatically generated.

# If you need additional preprocessing, there are three hook files
# that you can provide and that are called dring the build:
# user_init_pre.sh, user_init_post.sh and user_init_last.sh
# These files will never get overwritten by TASTE.'

# Inside these files you may set some environment variables:
#    C_INCLUDE_PATH=/usr/include/xenomai/analogy/:${C_INCLUDE_PATH}
#    unset USE_POHIC   

CWD=$(pwd)

if [ -t 1 ] ; then
    COLORON="\e[1m\e[32m"
    COLOROFF="\e[0m"
else
    COLORON=""
    COLOROFF=""
fi
INFO="${COLORON}[INFO]${COLOROFF}"

if [ -f user_init_pre.sh ]
then
    echo -e "${INFO} Executing user-defined init script"
    source user_init_pre.sh
fi

# Set up the cache to limit the calls to ASN1SCC in DMT tools
mkdir -p .cache
export PROJECT_CACHE=$(pwd)/.cache

# Use PolyORB-HI-C runtime
USE_POHIC=1

# Set Debug mode by default
DEBUG_MODE=--debug

# Detect models from Ellidiss tools v2, and convert them to 1.3
INTERFACEVIEW=data_logger_components_iv.aadl
grep "version => \"2" data_logger_components_iv.aadl >/dev/null && {
    echo -e "${INFO} Converting interface view from V2 to V1.3"
    TASTE --load-interface-view data_logger_components_iv.aadl --export-interface-view-to-1_3 __iv_1_3.aadl
    INTERFACEVIEW=__iv_1_3.aadl
};

if [ -z "$DEPLOYMENTVIEW" ]
then
    DEPLOYMENTVIEW=DeploymentView.aadl
fi

# Detect models from Ellidiss tools v2, and convert them to 1.3
grep "version => \"2" "$DEPLOYMENTVIEW" >/dev/null && {
    echo -e "${INFO} Converting deployment view from V2 to V1.3"
    TASTE --load-deployment-view "$DEPLOYMENTVIEW" --export-deployment-view-to-1_3 __dv_1_3.aadl
    DEPLOYMENTVIEW=__dv_1_3.aadl
};

SKELS="./"

# Check if Dataview references existing files 
mono $(which taste-extract-asn-from-design.exe) -i "$INTERFACEVIEW" -j /tmp/dv.asn

cd "$SKELS" && rm -f motion_command2d_logger.zip && zip motion_command2d_logger motion_command2d_logger/* && cd $OLDPWD

cd "$SKELS" && rm -f fake_input.zip && zip fake_input fake_input/* && cd $OLDPWD

cd "$SKELS" && rm -f double_fake_input.zip && zip double_fake_input double_fake_input/* && cd $OLDPWD

cd "$SKELS" && rm -f rbs_fake_input.zip && zip rbs_fake_input rbs_fake_input/* && cd $OLDPWD

cd "$SKELS" && rm -f signal_handler.zip && zip signal_handler signal_handler/* && cd $OLDPWD

cd "$SKELS" && rm -f double_replay.zip && zip double_replay double_replay/* && cd $OLDPWD

cd "$SKELS" && rm -f rbs_replay.zip && zip rbs_replay rbs_replay/* && cd $OLDPWD

cd "$SKELS" && rm -f fake_motion_command2d_consumer.zip && zip fake_motion_command2d_consumer fake_motion_command2d_consumer/* && cd $OLDPWD

cd "$SKELS" && rm -f fake_double_consumer.zip && zip fake_double_consumer fake_double_consumer/* && cd $OLDPWD

cd "$SKELS" && rm -f fake_rbs_consumer.zip && zip fake_rbs_consumer fake_rbs_consumer/* && cd $OLDPWD

[ ! -z "$CLEANUP" ] && rm -rf binary*

if [ -f ConcurrencyView.pro ]
then
    ORCHESTRATOR_OPTIONS+=" -w ConcurrencyView.pro "
elif [ -f ConcurrencyView_Properties.aadl ]
then
    ORCHESTRATOR_OPTIONS+=" -w ConcurrencyView_Properties.aadl "
fi

if [ -f user_init_post.sh ]
then
    echo -e "${INFO} Executing user-defined post-init script"
    source user_init_post.sh
fi

if [ -f additionalCommands.sh ]
then
    source additionalCommands.sh
fi

if [ ! -z "$USE_POHIC" ]
then
    OUTPUTDIR=binary.c
    ORCHESTRATOR_OPTIONS+=" -p "
elif [ ! -z "$USE_POHIADA" ]
then
    OUTPUTDIR=binary.ada
else
    OUTPUTDIR=binary
fi

cd "$CWD" && assert-builder-ocarina.py \
	--fast \
	$DEBUG_MODE \
	--aadlv2 \
	--keep-case \
	--interfaceView "$INTERFACEVIEW" \
	--deploymentView "$DEPLOYMENTVIEW" \
	-o "$OUTPUTDIR" \
	--subCPP motion_command2d_logger:"$SKELS"/motion_command2d_logger.zip \
	--subC fake_input:"$SKELS"/fake_input.zip \
	--subC double_fake_input:"$SKELS"/double_fake_input.zip \
	--subCPP double_logger:double_logger.zip \
	--subCPP rbs_logger:rbs_logger.zip \
	--subC rbs_fake_input:"$SKELS"/rbs_fake_input.zip \
	--subCPP signal_handler:"$SKELS"/signal_handler.zip \
	--subCPP motion_command2d_replay:motion_command2d_replay.zip \
	--subCPP double_replay:"$SKELS"/double_replay.zip \
	--subCPP rbs_replay:"$SKELS"/rbs_replay.zip \
	--subCPP fake_motion_command2d_consumer:"$SKELS"/fake_motion_command2d_consumer.zip \
	--subCPP fake_double_consumer:"$SKELS"/fake_double_consumer.zip \
	--subCPP fake_rbs_consumer:"$SKELS"/fake_rbs_consumer.zip \
	$ORCHESTRATOR_OPTIONS

if [ -f user_init_last.sh ]
then
    echo -e "${INFO} Executing user-defined post-build script"
    source user_init_last.sh
fi

