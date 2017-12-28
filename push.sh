#!/bin/bash


ls_date=`date +%Y-%m-%d`
git pull 
git add .
git commit -m ${ls_date}
git push origin
