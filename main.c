#include "student.h"
#include <locale.h>
#include <windows.h>

// 全局变量定义
Student students[MAX_STUDENTS];
int studentCount = 0;

void displayMenu() {
    system("cls");  // 清屏
    printf(CLEAR HIDE_CURSOR);  // 清屏并隐藏光标
    
    printf(BOLD BLUE "\n╔════════════════════════════════╗\n");
    printf("║     学生成绩管理系统 v1.0      ║\n");
    printf("╚════════════════════════════════╝\n" NO);
    
    printf(BOLD CYAN "\n[基础功能]\n" NO);
    printf(YELLOW "1" NO ". 输入学生信息\n");
    printf(YELLOW "2" NO ". 显示学生信息\n");
    printf(YELLOW "3" NO ". 按学号查找学生信息\n");
    printf(YELLOW "4" NO ". 显示课程最高分的学生信息\n");
    printf(YELLOW "5" NO ". 显示总分最高的学生信息\n");
    printf(YELLOW "6" NO ". 按总分升序输出\n");
    printf(YELLOW "7" NO ". 退出\n");
    
    printf(BOLD CYAN "\n[拓展功能]\n" NO);
    printf(YELLOW "8" NO ". 保存/读取数据\n");
    printf(YELLOW "9" NO ". 按姓名查找\n");
    printf(YELLOW "10" NO ". 成绩分析统计\n");
    printf(YELLOW "11" NO ". 成绩区间统计\n");
    printf(YELLOW "12" NO ". 删除学生信息\n");
    printf(YELLOW "13" NO ". 修改学生信息\n");
    printf(YELLOW "14" NO ". 导出成绩单\n");
    printf(YELLOW "15" NO ". 成绩排名\n");
    printf(YELLOW "16" NO ". 初始化测试数据\n");
    
    printf(BOLD GREEN "\n请选择功能 (1-16): " NO);
    printf(SHOW_CURSOR);  // 显示光标
}

int main() {
        // 设置中文支持
    SetConsoleOutputCP(65001);  // 设置控制台输出代码页为UTF-8
    SetConsoleCP(65001);        // 设置控制台输入代码页为UTF-8
    setlocale(LC_ALL, "zh_CN.UTF-8");  // 设置本地化

    int choice;
    
    // 尝试从文件加载数据
    loadFromFile();
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // 清除输入缓冲区中的换行符
        
        printf(CLEAR);  // 清屏
        
        switch (choice) {
            case 1:
                printf(BOLD BLUE "\n=== 输入学生信息 ===\n" NO);
                inputStudent();
                break;
            case 2:
                printf(BOLD BLUE "\n=== 显示学生信息 ===\n" NO);
                displayAllStudents();
                break;
            case 3:
                printf(BOLD BLUE "\n=== 按学号查找 ===\n" NO);
                searchById();
                break;
            case 4:
                printf(BOLD BLUE "\n=== 课程最高分 ===\n" NO);
                displayHighestInCourse();
                break;
            case 5:
                printf(BOLD BLUE "\n=== 总分最高 ===\n" NO);
                displayHighestTotal();
                break;
            case 6:
                printf(BOLD BLUE "\n=== 总分升序排列 ===\n" NO);
                sortByTotalAsc();
                break;
            case 7:
                printf(BOLD GREEN "\n感谢使用！再见！\n" NO);
                return 0;
            case 8:
                printf(BOLD BLUE "\n=== 文件操作 ===\n" NO);
                printf(CYAN "1. 保存到文件\n2. 从文件读取\n请选择: " NO);
                int subChoice;
                scanf("%d", &subChoice);
                getchar();
                if (subChoice == 1) saveToFile();
                else if (subChoice == 2) loadFromFile();
                break;
            case 9:
                printf(BOLD BLUE "\n=== 按姓名查找 ===\n" NO);
                searchByName();
                break;
            case 10:
                printf(BOLD BLUE "\n=== 成绩分析 ===\n" NO);
                analyzeScores();
                break;
            case 11:
                printf(BOLD BLUE "\n=== 成绩区间统计 ===\n" NO);
                analyzeScoreRanges();
                break;
            case 12:
                printf(BOLD BLUE "\n=== 删除学生信息 ===\n" NO);
                deleteStudent();
                break;
            case 13:
                printf(BOLD BLUE "\n=== 修改学生信息 ===\n" NO);
                modifyStudent();
                break;
            case 14:
                printf(BOLD BLUE "\n=== 导出成绩单 ===\n" NO);
                exportScores();
                break;
            case 15:
                printf(BOLD BLUE "\n=== 成绩排名 ===\n" NO);
                rankScores();
                break;
            case 16:
                printf(BOLD BLUE "\n=== 初始化测试数据 ===\n" NO);
                initializeTestData();
                break;
            default:
                printf(RED "无效的选择，请重试！\n" NO);
        }
        
        printf("\n按任意键继续...");
        getch();
    }
    
    return 0;
} 
