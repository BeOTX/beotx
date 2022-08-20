#!/usr/bin/python3

import argparse
import datetime
import os
from builtins import NotADirectoryError
import shutil
import tempfile

from boards import *

translations = [
    "EN"
]


def timestamp():
    return datetime.datetime.now().strftime("%Y%m%d")


def build(board, translation, srcdir):
    cmake_options = " ".join(["-D%s=%s" % (key, value) for key, value in boards[board].items()])
    cwd = os.getcwd()
    if not os.path.exists("output"):
        os.mkdir("output")
    path = tempfile.mkdtemp()
    os.chdir(path)
    command = "cmake %s -DTRANSLATIONS=%s -DIMRC_RELEASE=YES -DGHOST=YES %s" % (cmake_options, translation, srcdir)
    print(command)
    os.system(command)
    os.system("make firmware -j16")
    os.chdir(cwd)
    index = 0
    while 1:
        suffix = "" if index == 0 else "_%d" % index
        filename = "output/ghost_firm_%s_%s_%s%s.bin" % (board.lower(), translation.lower(), timestamp(), suffix)
        if not os.path.exists(filename):
            shutil.copy("%s/arm-none-eabi/firmware.bin" % path, filename)
            break
        index += 1
    shutil.rmtree(path)


def dir_path(string):
    if os.path.isdir(string):
        return string
    else:
        raise NotADirectoryError(string)


def main():
    parser = argparse.ArgumentParser(description="Build Ghost firmware")
    parser.add_argument("-b", "--boards", action="append", help="Destination boards", required=True)
    parser.add_argument("-t", "--translations", action="append", help="Translations", required=True)
    parser.add_argument("srcdir", type=dir_path)

    args = parser.parse_args()

    for board in (boards.keys() if "ALL" in args.boards else args.boards):
        for translation in (translations if "ALL" in args.translations else args.translations):
            build(board, translation, args.srcdir)


if __name__ == "__main__":
    main()