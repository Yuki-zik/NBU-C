@echo off
echo 正在初始化Git仓库...
git init

echo 添加文件...
git add .

echo 创建初始提交...
git commit -m "Initial commit: Student Management System"

echo 请输入你的GitHub用户名：
set /p username=

echo 关联远程仓库...
git remote add origin https://github.com/%username%/student-management-system.git

echo 推送代码到GitHub...
git push -u origin main

echo 完成！
pause 
