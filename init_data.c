#include "student.h"
#include <time.h>

// 常见姓氏
const char* surnames[] = {
    "张", "王", "李", "赵", "陈", "刘", "杨", "黄", "周", "吴",
    "徐", "孙", "胡", "朱", "高", "林", "何", "郭", "马", "罗"
};

// 常见名字
const char* names[] = {
    "伟", "芳", "娜", "秀英", "敏", "静", "丽", "强", "磊", "军",
    "洋", "勇", "艳", "杰", "娟", "涛", "明", "超", "秀兰", "霞",
    "平", "刚", "桂英", "春", "晶", "建华", "文", "云", "华", "晓"
};

// 生成随机分数
float generateRandomScore() {
    // 生成60-100之间的分数，小概率生成60分以下的分数
    if (rand() % 100 < 10) {  // 10%的概率生成不及格分数
        return 40.0f + (rand() % 200) / 10.0f;  // 40-59分
    } else {
        return 60.0f + (rand() % 400) / 10.0f;  // 60-99分
    }
}

void initializeTestData() {
    srand((unsigned int)time(NULL));  // 初始化随机数种子
    
    // 清空现有数据
    studentCount = 0;
    
    // 生成20个随机学生数据
    int numStudents = 20;
    printf(BOLD BLUE "\n正在生成 %d 条随机测试数据...\n" NO, numStudents);
    
    for (int i = 0; i < numStudents; i++) {
        // 生成学号 (2023001-2023020)
        sprintf(students[studentCount].id, "2023%03d", i + 1);
        
        // 随机组合姓名
        int surnameIndex = rand() % (sizeof(surnames) / sizeof(surnames[0]));
        int nameIndex = rand() % (sizeof(names) / sizeof(names[0]));
        sprintf(students[studentCount].name, "%s%s", surnames[surnameIndex], names[nameIndex]);
        
        // 生成随机成绩
        students[studentCount].chinese = generateRandomScore();
        students[studentCount].math = generateRandomScore();
        students[studentCount].english = generateRandomScore();
        
        // 计算总分
        calculateTotal(&students[studentCount]);
        
        // 显示生成进度
        printf(CYAN "\r生成进度：" YELLOW "[");
        int progress = (i + 1) * 20 / numStudents;
        for (int j = 0; j < 20; j++) {
            if (j < progress) printf("█");
            else printf("░");
        }
        printf(YELLOW "] " GREEN "%d%%" NO, (i + 1) * 100 / numStudents);
        fflush(stdout);
        
        studentCount++;
    }
    
    printf(BOLD GREEN "\n\n成功生成 %d 条测试数据！\n" NO, studentCount);
    printf(BOLD CYAN "\n是否显示生成的数据？(Y/N): " NO);
    char choice = getchar();
    getchar();  // 清除换行符
    
    if (choice == 'Y' || choice == 'y') {
        printf(BOLD BLUE "\n╔═══════════════ 测试数据 ═══════════════╗\n" NO);
        for (int i = 0; i < studentCount; i++) {
            displayStudent(&students[i]);
        }
        printf(BOLD BLUE "╚════════════════════════════════════════╝\n" NO);
    }
} 
