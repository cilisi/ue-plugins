@echo off
cd ../
git checkout --orphan new
git add -A
set message=%1
if defined %message%=="" (echo message is null) else set message="clear history and caches"
git commit -sm %message%
git branch -D master
git branch -m master
git reflog expire --expire=now --all
git gc
git push origin master -f
pause