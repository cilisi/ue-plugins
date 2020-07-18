@echo off
set CONSTANT_MESSAGE="update"
set message=%1
if defined %message%=="" (echo message is null) else set message=%CONSTANT_MESSAGE%
git add -A
git commit -sm %message%
git push origin master
pause