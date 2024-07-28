#!/bin/bash

# Stops on first error, echo on
set -e
# set -x

: "${SRCDIR:=$(dirname "$(pwd)/$0")/..}"

: ${FLAVOR:="nv14;el18;t12;t12max;t15;t16;t18;t8;zorro;pocket;commando8;tlite;tpro;tprov2;tpros;t20;t20v2;t14;lr3pro;mt12;tx12;tx12mk2;boxer;tx16s;x10;x10express;x12s;x7;x7access;x9d;x9dp;x9dp2019;x9e;x9lite;x9lites;xlite;xlites;f16"}
: ${COMMON_OPTIONS:="-DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_RULE_MESSAGES=OFF -Wno-dev -DCMAKE_MESSAGE_LOG_LEVEL=WARNING"}

# wipe build directory clean
rm -rf build && mkdir -p build && cd build

target_names=$(echo "$FLAVOR" | tr '[:upper:]' '[:lower:]' | tr ';' '\n')

TARGET_DIR="${SRCDIR}/radio/src/targets/hw_defs"

for target_name in $target_names
do
    BUILD_OPTIONS=${COMMON_OPTIONS}
    BUILD_OPTIONS+=" $EXTRA_OPTIONS "

    echo "Processing ${target_name}"
    case $target_name in
        x9lite)
            BUILD_OPTIONS+="-DPCB=X9LITE"
            ;;
        x9lites)
            BUILD_OPTIONS+="-DPCB=X9LITES"
            ;;
        x7)
            BUILD_OPTIONS+="-DPCB=X7"
            ;;
        x7access)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=ACCESS -DPXX1=YES"
            ;;
        t12)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=T12 -DINTERNAL_MODULE_MULTI=ON"
            ;;
        tx12)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TX12"
            ;;
        tx12mk2)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TX12MK2"
            ;;
        boxer)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=BOXER"
            ;;
        t8)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=T8"
            ;;
        zorro)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=ZORRO"
            ;;
        pocket)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=POCKET"
            ;;
        mt12)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=MT12"
            ;;
        tlite)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TLITE"
            ;;
        tpro)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TPRO"
            ;;
        tprov2)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TPROV2"
            ;;
        tpros)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TPROS"
            ;;
        t20)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=T20"
            ;;
        t20v2)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=T20V2"
            ;;
        t12max)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=T12MAX"
            ;;
        t14)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=T14"
            ;;
        lr3pro)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=LR3PRO"
            ;;
        commando8)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=COMMANDO8"
            ;;
        xlite)
            BUILD_OPTIONS+="-DPCB=XLITE"
            ;;
        xlites)
            BUILD_OPTIONS+="-DPCB=XLITES"
            ;;
        x9d)
            BUILD_OPTIONS+="-DPCB=X9D"
            ;;
        x9dp)
            BUILD_OPTIONS+="-DPCB=X9D+"
            ;;
        x9dp2019)
            BUILD_OPTIONS+="-DPCB=X9D+ -DPCBREV=2019"
            ;;
        x9e)
            BUILD_OPTIONS+="-DPCB=X9E"
            ;;
        x9e-hall)
            BUILD_OPTIONS+="-DPCB=X9E -DSTICKS=HORUS"
            ;;
        x10)
            BUILD_OPTIONS+="-DPCB=X10"
            ;;
        x10express)
            BUILD_OPTIONS+="-DPCB=X10 -DPCBREV=EXPRESS -DPXX1=YES"
            ;;
        x12s)
            BUILD_OPTIONS+="-DPCB=X12S"
            ;;
        t15)
            BUILD_OPTIONS+="-DPCB=X10 -DPCBREV=T15 -DINTERNAL_MODULE_CRSF=ON"
            ;;
        t16)
            BUILD_OPTIONS+="-DPCB=X10 -DPCBREV=T16 -DINTERNAL_MODULE_MULTI=ON"
            ;;
        t18)
            BUILD_OPTIONS+="-DPCB=X10 -DPCBREV=T18"
            ;;
        tx16s)
            BUILD_OPTIONS+="-DPCB=X10 -DPCBREV=TX16S"
            ;;
        f16)
            BUILD_OPTIONS+="-DPCB=X10 -DPCBREV=F16"
            ;;
        nv14)
            BUILD_OPTIONS+="-DPCB=NV14"
            ;;
        el18)
            BUILD_OPTIONS+="-DPCB=NV14 -DPCBREV=EL18"
            ;;
        pl18)
            BUILD_OPTIONS+="-DPCB=PL18"
            ;;
        pl18ev)
            BUILD_OPTIONS+="-DPCB=PL18 -DPCBREV=PL18EV"
            ;;
        *)
            echo "Unknown target: $target_name"
            exit 1
            ;;
    esac

    cmake ${BUILD_OPTIONS} "${SRCDIR}"
    cmake --build . --target arm-none-eabi-configure
    cmake --build arm-none-eabi --target hardware_defs

    mkdir -p ${TARGET_DIR}
    mv arm-none-eabi/radio/src/*.json* ${TARGET_DIR}
    
    rm -f CMakeCache.txt arm-none-eabi/CMakeCache.txt
done
