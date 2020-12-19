@echo off

:start
cls
call:test %random%+%random%*(%random%+%random%)-%random%*%random%-(%random%-%random%*%random%)*%random%
pause
goto start

echo.
pause
goto:eof


:: TEST FUNCTIONS

:test
echo %~1 > input
echo Input: %~1
inf_calc input -log
echo.
echo ================================
goto:eof