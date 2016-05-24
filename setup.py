from setuptools import setup, find_packages
import subprocess
import sys
import os
import shutil
import fir

def makefile():
    srclib = "src/hardware/libfir.so"
    dstlib = "fir/libfir.so"
    status = subprocess.check_call(["make", "-C", "src/hardware"])
    if status is not 0:
        print("Error while running make..Exiting")
        sys.exit(1)
    shutil.copyfile(srclib,dstlib)

if len(sys.argv) > 1 and sys.argv[1] == 'install':
    makefile()

setup(
    name = "fir",
    version = "0.1",
    url = 'https://github.com/hackwa/pynq',
    license = 'Apache Software License',
    author = "Anurag Dubey",
    author_email = "hackwad@xilinx.com",
    packages = ['fir'],
    package_data = {
    '' : ['*.bin','*.tcl','*.so'],
    },
    description = "Run a FIR filter on Hardware"
)
