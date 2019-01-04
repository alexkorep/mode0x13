@echo off
SET PATH=%PATH%;C:/TC/BIN/
tcc -ITC\INCLUDE -LTC\LIB bresen.cpp
pause