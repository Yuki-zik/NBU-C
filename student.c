#include "student.h"

// 辅助函数实现
void calculateTotal(Student* student) {
    student->total = student->chinese + student->math + student->english;
}

void displayStudent(Student* student) {
    printf(BOLD "╭───────────────────────────────────────────╮\n");
    printf("│ " CYAN "学号：" NO "%-12s " CYAN "姓名：" NO "%-12s       │\n", student->id, student->name);
    printf("├───────────────────────────────────────────┤\n");
    printf("│ " CYAN "语文：" NO "%6.1f  " CYAN "数学：" NO "%6.1f  " CYAN "英语：" NO "%6.1f  │\n",
           student->chinese, student->math, student->english);
    printf("│ " CYAN "总分：" NO "%6.1f  " CYAN "平均分：" NO "%6.1f              │\n",
           student->total, student->total/3);
    printf("╰───────────────────────────────────────────╯\n" NO);
}

int compareStudents(const void* a, const void* b) {
    Student* s1 = (Student*)a;
    Student* s2 = (Student*)b;
    if (s1->total > s2->total) return 1;
    if (s1->total < s2->total) return -1;
    return strcmp(s1->id, s2->id);  // 总分相同时按学号排序
}

// 基础功能实现
void inputStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("学生数量已达上限！\n");
        return;
    }

    Student newStudent;
    printf("请输入学生信息：\n");
    printf("学号：");
    scanf("%s", newStudent.id);
    getchar();
    
    // 检查学号是否已存在
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, newStudent.id) == 0) {
            printf("该学号已存在！\n");
            return;
        }
    }
    
    printf("姓名：");
    fgets(newStudent.name, MAX_NAME_LEN, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;  // 移除换行符
    
    printf("语文成绩：");
    scanf("%f", &newStudent.chinese);
    printf("数学成绩：");
    scanf("%f", &newStudent.math);
    printf("英语成绩：");
    scanf("%f", &newStudent.english);
    getchar();
    
    calculateTotal(&newStudent);
    
    // 找到合适的插入位置（按学号升序）
    int pos = studentCount;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(newStudent.id, students[i].id) < 0) {
            pos = i;
            break;
        }
    }
    
    // 移动元素，为新学生腾出位置
    for (int i = studentCount; i > pos; i--) {
        students[i] = students[i-1];
    }
    
    students[pos] = newStudent;
    studentCount++;
    printf("学生信息添加成功！\n");
}

void displayAllStudents() {
    if (studentCount == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    
    printf("\n=== 所有学生信息 ===\n");
    for (int i = 0; i < studentCount; i++) {
        printf("\n第 %d 个学生：\n", i + 1);
        displayStudent(&students[i]);
    }
}

void searchById() {
    if (studentCount == 0) {
        printf(RED "\n暂无学生信息！\n" NO);
        return;
    }
    
    char searchId[MAX_ID_LEN];
    printf(BOLD CYAN "\n请输入要查找的学号：" NO);
    fgets(searchId, MAX_ID_LEN, stdin);
    searchId[strcspn(searchId, "\n")] = 0;  // 移除换行符
    
    // 验证学号
    if (strlen(searchId) > MAX_ID_LEN - 1) {
        printf(RED "学号长度超出限制！\n" NO);
        return;
    }
    
    // 检查学号是否包含非法字符
    for (int i = 0; searchId[i]; i++) {
        if (!isalnum(searchId[i])) {  // 只允许字母和数字
            printf(RED "学号包含非法字符！\n" NO);
            return;
        }
    }
    
    printf(BOLD BLUE "\n╔════════════════════ 查找结果 ════════════════════╗\n" NO);
    
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, searchId) == 0) {
            displayStudent(&students[i]);
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf(RED "│                未找到该学号的学生！                │\n" NO);
        printf(BOLD BLUE "╚════════════════════════════════════════════════╝\n" NO);
    }
}

void displayHighestInCourse() {
    if (studentCount == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    
    int course;
    printf("请选择课程（1:语文 2:数学 3:英语）：");
    scanf("%d", &course);
    getchar();
    
    float maxScore = -1;
    switch (course) {
        case 1:
            for (int i = 0; i < studentCount; i++) {
                if (students[i].chinese > maxScore) maxScore = students[i].chinese;
            }
            printf("\n语文最高分：%.1f\n获得最高分的学生\n", maxScore);
            for (int i = 0; i < studentCount; i++) {
                if (students[i].chinese == maxScore) {
                    displayStudent(&students[i]);
                }
            }
            break;
        case 2:
            for (int i = 0; i < studentCount; i++) {
                if (students[i].math > maxScore) maxScore = students[i].math;
            }
            printf("\n数学最高分：%.1f\n获得最高分的学生：\n", maxScore);
            for (int i = 0; i < studentCount; i++) {
                if (students[i].math == maxScore) {
                    displayStudent(&students[i]);
                }
            }
            break;
        case 3:
            for (int i = 0; i < studentCount; i++) {
                if (students[i].english > maxScore) maxScore = students[i].english;
            }
            printf("\n英语最高分：%.1f\n获得最高分的学生：\n", maxScore);
            for (int i = 0; i < studentCount; i++) {
                if (students[i].english == maxScore) {
                    displayStudent(&students[i]);
                }
            }
            break;
        default:
            printf("无效的课程选择！\n");
    }
}

void displayHighestTotal() {
    if (studentCount == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    
    float maxTotal = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].total > maxTotal) maxTotal = students[i].total;
    }
    
    printf("\n最高总分：%.1f\n获得最高总分的学生：\n", maxTotal);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].total == maxTotal) {
            displayStudent(&students[i]);
        }
    }
}

void sortByTotalAsc() {
    if (studentCount == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    
    qsort(students, studentCount, sizeof(Student), compareStudents);
    printf("\n按总分升序排列结果：\n");
    displayAllStudents();
}

// 拓功能实现
void saveToFile() {
    // 使用二进制模式写入，确保字节级别的准确性
    FILE* file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf(RED "无法创建文件！\n" NO);
        return;
    }
    
    // 写入文件头标记，用于识别文件编码（UTF-8）
    const char* header = "UTF-8";
    fwrite(header, sizeof(char), 5, file);
    
    // 写入数据
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf(GREEN "数据已保存到文件！\n" NO);
}

void loadFromFile() {
    FILE* file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf(RED "未找到数据文件！\n" NO);
        return;
    }
    
    // 读取并验证文件头标记
    char header[6] = {0};
    fread(header, sizeof(char), 5, file);
    if (strcmp(header, "UTF-8") != 0) {
        printf(RED "文件格式不正确或版本不兼容！\n" NO);
        fclose(file);
        return;
    }
    
    // 读取数据
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf(GREEN "已从文件加载 %d 条学生记录！\n" NO, studentCount);
}

void searchByName() {
    if (studentCount == 0) {
        printf(RED "\n暂无学生信息！\n" NO);
        return;
    }
    
    char searchName[MAX_NAME_LEN];
    printf(BOLD CYAN "\n请输入要查找的姓名（支持姓氏/全名模糊查询）：" NO);
    fgets(searchName, MAX_NAME_LEN, stdin);
    searchName[strcspn(searchName, "\n")] = 0;  // 移除换行符
    
    // 验证姓名长度
    if (strlen(searchName) > MAX_NAME_LEN - 1) {
        printf(RED "姓名长度超出限制！\n" NO);
        return;
    }
    
    // 验证搜索关键词不为空
    if (strlen(searchName) == 0) {
        printf(RED "搜索关键词不能为空！\n" NO);
        return;
    }
    
    printf(BOLD BLUE "\n╔═══════════════════ 查找结果 ═══════════════════╗\n" NO);
    
    int foundCount = 0;
    // 第一次遍历计算匹配数量
    for (int i = 0; i < studentCount; i++) {
        int isMatch = 0;
        // 使用strstr进行子串匹配，不再假设字符编码
        if (strstr(students[i].name, searchName) != NULL) {
            isMatch = 1;
        }
        if (isMatch) {
            foundCount++;
        }
    }
    
    if (foundCount > 0) {
        printf(BOLD "│ 共找到 " YELLOW "%d" BOLD " 个匹配的学生：" NO, foundCount);
        // 补齐空格使显示对齐
        for (int i = 0; i < 20 - (foundCount > 9 ? 2 : 1); i++) printf(" ");
        printf("    │\n");
        printf(BOLD BLUE "├─────────────────────────────────────────────────┤\n" NO);
        
        // 第二次遍历显示结果
        int currentCount = 0;
        for (int i = 0; i < studentCount; i++) {
            if (strstr(students[i].name, searchName) != NULL) {
                displayStudent(&students[i]);
                currentCount++;
                if (currentCount < foundCount) {
                    printf(BOLD BLUE "├─────────────────────────────────────────────────┤\n" NO);
                }
            }
        }
        printf(BOLD BLUE "╚════════════════════════════════════════════════╝\n" NO);
    } else {
        printf(RED "│               未找到匹配的学生！               │\n" NO);
        printf(BOLD BLUE "╚════════════════════════════════════════════════╝\n" NO);
    }
}

void analyzeScores() {
    if (studentCount == 0) {
        printf(RED "\n暂无学生信息！\n" NO);
        return;
    }
    
    float chineseTotal = 0, mathTotal = 0, englishTotal = 0;
    float chineseMax = 0, mathMax = 0, englishMax = 0;
    float chineseMin = 100, mathMin = 100, englishMin = 100;
    int chinesePassed = 0, mathPassed = 0, englishPassed = 0;
    
    for (int i = 0; i < studentCount; i++) {
        // 累加总分
        chineseTotal += students[i].chinese;
        mathTotal += students[i].math;
        englishTotal += students[i].english;
        
        // 统计及格人数
        if (students[i].chinese >= 60) chinesePassed++;
        if (students[i].math >= 60) mathPassed++;
        if (students[i].english >= 60) englishPassed++;
        
        // 更新最高分
        if (students[i].chinese > chineseMax) chineseMax = students[i].chinese;
        if (students[i].math > mathMax) mathMax = students[i].math;
        if (students[i].english > englishMax) englishMax = students[i].english;
        
        // 更新最低分
        if (students[i].chinese < chineseMin) chineseMin = students[i].chinese;
        if (students[i].math < mathMin) mathMin = students[i].math;
        if (students[i].english < englishMin) englishMin = students[i].english;
    }
    
    printf(BOLD BLUE "\n╔═════════════════ 成绩分析报告 ═══════════════════╗\n" NO);
    
    // 语文分析
    printf(BOLD CYAN "\n[语文成绩分析]\n" NO);
    printf("平均分：" YELLOW "%.1f" NO "  最高分：" GREEN "%.1f" NO "  最低分：" RED "%.1f" NO "\n",
           chineseTotal/studentCount, chineseMax, chineseMin);
    printf("及格率：" YELLOW "%.1f%%" NO "  及格人数：" GREEN "%d" NO "/%d\n",
           (float)chinesePassed/studentCount*100, chinesePassed, studentCount);
    
    // 数学分析
    printf(BOLD CYAN "\n[数学成绩分析]\n" NO);
    printf("平均分：" YELLOW "%.1f" NO "  最高分：" GREEN "%.1f" NO "  最低分：" RED "%.1f" NO "\n",
           mathTotal/studentCount, mathMax, mathMin);
    printf("及格率：" YELLOW "%.1f%%" NO "  及格人数：" GREEN "%d" NO "/%d\n",
           (float)mathPassed/studentCount*100, mathPassed, studentCount);
    
    // 英语分析
    printf(BOLD CYAN "\n[英语成绩分析]\n" NO);
    printf("平均分：" YELLOW "%.1f" NO "  最高分：" GREEN "%.1f" NO "  最低分：" RED "%.1f" NO "\n",
           englishTotal/studentCount, englishMax, englishMin);
    printf("及格率：" YELLOW "%.1f%%" NO "  及格人数：" GREEN "%d" NO "/%d\n",
           (float)englishPassed/studentCount*100, englishPassed, studentCount);
    
    printf(BOLD BLUE "\n╚════════════════════════════════════════════════════╝\n" NO);
    
    printf("\n按任意键继续...");
    getch();
}

void analyzeScoreRanges() {
    if (studentCount == 0) {
        printf(RED "\n暂无学生信息！\n" NO);
        return;
    }
    
    int ranges[5] = {0}; // 0-59, 60-69, 70-79, 80-89, 90-100
    
    printf(BOLD CYAN "\n请选择要分析的课程（" NO);
    printf(YELLOW "1" NO ":语文 " YELLOW "2" NO ":数学 " YELLOW "3" NO ":英语）：");
    int choice;
    scanf("%d", &choice);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        float score;
        switch (choice) {
            case 1: score = students[i].chinese; break;
            case 2: score = students[i].math; break;
            case 3: score = students[i].english; break;
            default: printf(RED "无效的选择！\n" NO); return;
        }
        
        if (score < 60) ranges[0]++;
        else if (score < 70) ranges[1]++;
        else if (score < 80) ranges[2]++;
        else if (score < 90) ranges[3]++;
        else ranges[4]++;
    }
    
    const char* courseName = choice == 1 ? "语文" : (choice == 2 ? "数学" : "英语");
    printf(BOLD BLUE "\n╔══════════════════════ %s成绩分布 ═════════════════════╗\n" NO, courseName);
    
    // 计算最大人数，用于显示比例条
    int maxCount = 0;
    for (int i = 0; i < 5; i++) {
        if (ranges[i] > maxCount) maxCount = ranges[i];
    }
    
    const char* labels[] = {"不及格", "及格", "中等", "良好", "优秀"};
    const char* colors[] = {RED, YELLOW, CYAN, BLUE, GREEN};
    const char* ranges_str[] = {"0-59", "60-69", "70-79", "80-89", "90-100"};
    
    for (int i = 0; i < 5; i++) {
        // 左侧信息对齐
        printf("│ %s%-8s" NO "(" BOLD "%-6s" NO ")：" BOLD "%2d" NO " 人 ", 
               colors[i], labels[i], ranges_str[i], ranges[i]);
        
        // 显示比例条
        printf("│ ");
        int barLength = (ranges[i] * 20) / (maxCount > 0 ? maxCount : 1);
        for (int j = 0; j < barLength; j++) {
            printf("%s█" NO, colors[i]);
        }
        for (int j = barLength; j < 20; j++) {
            printf("░");
        }
        
        // 右侧百分比对齐
        printf(" │ %6.1f%%  │\n", (float)ranges[i]/studentCount*100);
    }
    
    printf(BOLD BLUE "╚═════════════════════════════════════════════════════════╝\n" NO);
    
    printf("\n按任意键继续...");
    getch();
}

void deleteStudent() {
    if (studentCount == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    
    char deleteId[MAX_ID_LEN];
    printf("请输入要删除的学生学号：");
    scanf("%s", deleteId);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, deleteId) == 0) {
            // 移动后面的学生信息
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("学生信息已删除！\n");
            return;
        }
    }
    
    printf("未找到该学号的学生！\n");
}

void modifyStudent() {
    if (studentCount == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    
    char modifyId[MAX_ID_LEN];
    printf("请输入要修改的学生学号：");
    scanf("%s", modifyId);
    getchar();
    
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, modifyId) == 0) {
            printf("\n当前学生信息：\n");
            displayStudent(&students[i]);
            
            printf("\n请输入新的信息：\n");
            printf("姓名（直接回车表示不修改）：");
            char newName[MAX_NAME_LEN];
            fgets(newName, MAX_NAME_LEN, stdin);
            if (newName[0] != '\n') {
                newName[strlen(newName)-1] = '\0';  // 删除换行符
                strcpy(students[i].name, newName);
            }
            
            printf("语文成绩（-1表示不修改）：");
            float score;
            scanf("%f", &score);
            if (score >= 0) students[i].chinese = score;
            
            printf("数学成绩（-1表示不修改）：");
            scanf("%f", &score);
            if (score >= 0) students[i].math = score;
            
            printf("英语成绩（-1表示不修改）：");
            scanf("%f", &score);
            if (score >= 0) students[i].english = score;
            getchar();
            
            calculateTotal(&students[i]);
            printf("\n修改后的信息：\n");
            displayStudent(&students[i]);
            return;
        }
    }
    
    printf("未找到该学号的学生！\n");
}

void exportScores() {
    if (studentCount == 0) {
        printf(RED "暂无学生信息！\n" NO);
        return;
    }
    
    printf(CYAN "请选择导出格式（1:TXT 2:CSV）：" NO);
    int format;
    scanf("%d", &format);
    getchar();
    
    FILE* file;
    if (format == 1) {
        file = fopen("scores.txt", "wb");  // 使用二进制模式
        if (file == NULL) {
            printf(RED "无法创建文件！\n" NO);
            return;
        }
        
        // 写入UTF-8 BOM
        unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        fwrite(bom, sizeof(unsigned char), 3, file);
        
        fprintf(file, "学号\t\t姓名\t\t语文\t数学\t英语\t总分\n");
        for (int i = 0; i < studentCount; i++) {
            fprintf(file, "%-15s%-15s%.1f\t%.1f\t%.1f\t%.1f\n",
                    students[i].id, students[i].name,
                    students[i].chinese, students[i].math,
                    students[i].english, students[i].total);
        }
    } else if (format == 2) {
        file = fopen("scores.csv", "wb");  // 使用二进制模式
        if (file == NULL) {
            printf(RED "无法创建文件！\n" NO);
            return;
        }
        
        // 写入UTF-8 BOM
        unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        fwrite(bom, sizeof(unsigned char), 3, file);
        
        fprintf(file, "学号,姓名,语文,数学,英语,总分\n");
        for (int i = 0; i < studentCount; i++) {
            fprintf(file, "%s,%s,%.1f,%.1f,%.1f,%.1f\n",
                    students[i].id, students[i].name,
                    students[i].chinese, students[i].math,
                    students[i].english, students[i].total);
        }
    } else {
        printf(RED "无效的格式选择！\n" NO);
        return;
    }
    
    fclose(file);
    printf(GREEN "成绩单已导出！\n" NO);
}

void rankScores() {
    if (studentCount == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    
    printf("请选择排名方式（1:总分 2:单科）：");
    int choice;
    scanf("%d", &choice);
    getchar();
    
    if (choice == 1) {
        // 按总分排序（降序）
        Student temp[MAX_STUDENTS];
        memcpy(temp, students, sizeof(Student) * studentCount);
        for (int i = 0; i < studentCount - 1; i++) {
            for (int j = 0; j < studentCount - 1 - i; j++) {
                if (temp[j].total < temp[j+1].total ||
                    (temp[j].total == temp[j+1].total && strcmp(temp[j].id, temp[j+1].id) > 0)) {
                    Student t = temp[j];
                    temp[j] = temp[j+1];
                    temp[j+1] = t;
                }
            }
        }
        
        printf("\n=== 总分排名 ===\n");
        for (int i = 0; i < studentCount; i++) {
            printf("第%d名：\n", i + 1);
            displayStudent(&temp[i]);
        }
    } else if (choice == 2) {
        printf("请选择课程（1:语文 2:数学 3:英语）：");
        int course;
        scanf("%d", &course);
        getchar();
        
        Student temp[MAX_STUDENTS];
        memcpy(temp, students, sizeof(Student) * studentCount);
        for (int i = 0; i < studentCount - 1; i++) {
            for (int j = 0; j < studentCount - 1 - i; j++) {
                float score1, score2;
                switch (course) {
                    case 1:
                        score1 = temp[j].chinese;
                        score2 = temp[j+1].chinese;
                        break;
                    case 2:
                        score1 = temp[j].math;
                        score2 = temp[j+1].math;
                        break;
                    case 3:
                        score1 = temp[j].english;
                        score2 = temp[j+1].english;
                        break;
                    default:
                        printf("无效的课程选择！\n");
                        return;
                }
                
                if (score1 < score2 ||
                    (score1 == score2 && strcmp(temp[j].id, temp[j+1].id) > 0)) {
                    Student t = temp[j];
                    temp[j] = temp[j+1];
                    temp[j+1] = t;
                }
            }
        }
        
        const char* courseName = course == 1 ? "语文" :
                               (course == 2 ? "数学" : "英语");
        printf("\n=== %s成绩排名 ===\n", courseName);
        for (int i = 0; i < studentCount; i++) {
            printf("第%d名：\n", i + 1);
            displayStudent(&temp[i]);
        }
    } else {
        printf("无效的选择！\n");
    }
} 
