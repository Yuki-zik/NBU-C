@echo off
chcp 65001 > nul
echo 正在编译...
gcc -o student_system main.c student.c init_data.c -Wall -fexec-charset=UTF-8 -finput-charset=UTF-8
if %errorlevel% equ 0 (
    echo 编译成功！
    echo 正在运行程序...
    student_system
) else (
    echo 编译失败！
    pause
) 
