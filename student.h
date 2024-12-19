#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

// ANSI转义序列定义
#define NO "\033[0m"      // 重置所有属性
#define BOLD "\033[1m"    // 粗体
#define UNDERLINE "\033[4m" // 下划线
#define BLUE "\033[34m"   // 蓝色
#define GREEN "\033[32m"  // 绿色
#define YELLOW "\033[33m" // 黄色
#define RED "\033[31m"    // 红色
#define CYAN "\033[36m"   // 青色
#define CLEAR "\033[2J\033[H" // 清屏并将光标移到开头
#define HIDE_CURSOR "\033[?25l" // 隐藏光标
#define SHOW_CURSOR "\033[?25h" // 显示光标

#define MAX_NAME_LEN 50
#define MAX_ID_LEN 20
#define MAX_STUDENTS 100

// 学生信息结构体
typedef struct {
    char name[MAX_NAME_LEN];    // 姓名
    char id[MAX_ID_LEN];        // 学号
    float chinese;              // 语文成绩
    float math;                 // 数学成绩
    float english;              // 英语成绩
    float total;                // 总分
} Student;

// 全局变量声明
extern Student students[MAX_STUDENTS];  // 学生数组
extern int studentCount;               // 当前学生数量

// 初始化函数声明
void initializeData();                 // 初始化示例数据

// 基础功能函数声明
void inputStudent();                   // 1.输入学生信息
void displayAllStudents();             // 2.显��学生信息
void searchById();                     // 3.按学号查找
void displayHighestInCourse();         // 4.显示课程最高分
void displayHighestTotal();            // 5.显示总分最高
void sortByTotalAsc();                 // 6.按总分升序

// 拓展功能函数声明
void saveToFile();                     // 8.保存到文件
void loadFromFile();                   // 8.从文件读取
void searchByName();                   // 9.按姓名查找
void analyzeScores();                  // 10.成绩分析
void analyzeScoreRanges();            // 11.成绩区间统计
void deleteStudent();                  // 12.删除学生
void modifyStudent();                  // 13.修改学生信息
void exportScores();                   // 14.导出成绩
void rankScores();                     // 15.成绩排名

// 辅助函数声明
void calculateTotal(Student* student);  // 计算总分
void displayStudent(Student* student);  // 显示单个学生信息
void displayMenu();                    // 显示菜单
int compareStudents(const void* a, const void* b);  // 比较函数

// 添加函数声明
void initializeTestData();

#endif 
