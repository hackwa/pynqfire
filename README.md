# A sample package for Pynq-Z1 board
This package encapsulates everything needed to run a FIR filter on the FPGA Fabric of Pynq-Z1 board.

## Website
http://www.pynq.io

## Installing
sudo pip3.6 install --upgrade 'git+https://github.com/hackwa/pynqfire@master#egg=fir'

## Usage
Checkout 'notebooks' Folder

## Revision
Date | README Version | Description
-----|----------------|------------
Sep2016|1.0|Initial FIR filter
Mar2018|2.0|Updated with configurable FIR coefficients

### Known issues:

1. accel.reset() throws error in xlnk - You need to edit `/opt/python3.6/lib/python3.6/site-packages/pynq/xlnk.py` and replace "self" keyword with "Xlnk" in staticmethods "cma_cast" and "cma_memcopy"
