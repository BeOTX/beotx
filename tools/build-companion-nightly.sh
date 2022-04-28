#!/bin/bash

# Stops on first error, echo on
set -e
set -x

if [ "$(uname)" = "Darwin" ]; then
  num_cpus=$(sysctl -n hw.ncpu)
  : "${JOBS:=$num_cpus}"
else
  JOBS=3
fi

while [ $# -gt 0 ]
do
  case "$1" in
    --jobs=*)
      JOBS="${1#*=}";;
    -j*)
      JOBS="${1#*j}";;
    -*)
      echo >&2 "usage: $0 [-j<jobs>|--jobs=<jobs>] SRCDIR OUTDIR VERSION_SUFFIX"
      exit 1;;
    *)
      break;;   # terminate while loop
  esac
  shift
done

SRCDIR=$1
OUTDIR=$2

COMMON_OPTIONS="-DGVARS=YES -DHELI=YES -DLUA=YES -Wno-dev -DCMAKE_BUILD_TYPE=Release"
if [ "$(uname)" = "Darwin" ]; then
    COMMON_OPTIONS="${COMMON_OPTIONS} -DCMAKE_OSX_DEPLOYMENT_TARGET='10.9'"
elif [ "$(uname)" != "Linux" ]; then
    COMMON_OPTIONS="${COMMON_OPTIONS} -DSDL_LIBRARY_PATH=/mingw64/bin/"
fi

if [ "$3" != "" ]; then
  COMMON_OPTIONS="${COMMON_OPTIONS} -DVERSION_SUFFIX=$3"
else
  COMMON_OPTIONS="${COMMON_OPTIONS} -DVERSION_SUFFIX=nightly"
fi

rm -rf build
mkdir build
cd build

declare -a simulator_plugins=(x9lite x9lites
                              x7 x7-access
                              t8 t12 tx12
                              zorro
                              tlite tpro
                              x9d x9dp x9dp2019 x9e
                              xlite xlites
                              nv14
                              x10 x10-access x12s
                              t16 t18 tx16s)

for plugin in "${simulator_plugins[@]}"
do
    BUILD_OPTIONS="${COMMON_OPTIONS} "

    echo "Building ${plugin}"
    case $plugin in
        x9lite)
            BUILD_OPTIONS+="-DPCB=X9LITE"
            ;;
        x9lites)
            BUILD_OPTIONS+="-DPCB=X9LITES"
            ;;
        x7)
            BUILD_OPTIONS+="-DPCB=X7"
            ;;
        x7-access)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=ACCESS -DPXX1=YES"
            ;;
        t12)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=T12 -DINTERNAL_MODULE_MULTI=ON"
            ;;
        tx12)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TX12"
            ;;
        t8)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=T8"
            ;;
        zorro)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=ZORRO"
            ;;
        tlite)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TLITE"
            ;;
        tpro)
            BUILD_OPTIONS+="-DPCB=X7 -DPCBREV=TPRO"
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
        x10)
            BUILD_OPTIONS+="-DPCB=X10"
            ;;
        x10-access)
            BUILD_OPTIONS+="-DPCB=X10 -DPCBREV=EXPRESS -DPXX1=YES"
            ;;
        x12s)
            BUILD_OPTIONS+="-DPCB=X12S"
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
        nv14)
            BUILD_OPTIONS+="-DPCB=NV14"
            ;;
    esac

    rm -f CMakeCache.txt native/CMakeCache.txt
    cmake ${BUILD_OPTIONS} "${SRCDIR}"
    cmake --build . --target native-configure
    cmake --build native -j"${JOBS}" --target libsimulator
done                              

cmake --build . --target native-configure
if [ "$(uname)" = "Darwin" ]; then
    cmake --build native -j"${JOBS}" --target package
    cp native/*.dmg "${OUTDIR}"
elif [ "$(uname)" = "Linux" ]; then
    cmake --build native -j"${JOBS}" --target package
    cp native/*.AppImage "${OUTDIR}"
else
    cmake --build native --target installer
    cp native/companion/*.exe "${OUTDIR}"
fi
