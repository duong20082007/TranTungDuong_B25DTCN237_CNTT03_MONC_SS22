#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NAME_SIZE 50
typedef struct {
    char name[50];
    int age;
    float grade; 
} Student;

void input_student_info(Student list[], int *count) {
    if (*count >= 50) {
        printf("Loi: Danh sach da day.\n");
        return;
    }
    
    Student new_student;
    
    fflush(stdin);
    printf("\n--- Nhap thong tin hoc sinh %d ---\n", *count + 1);

    fflush(stdin);
    printf("Nhap Ten: ");
    fgets(new_student.name, 50, stdin);
    
    fflush(stdin);
	printf("Nhap Tuoi: ");
    if (scanf("%d", &new_student.age) != 1) {
        printf("Loi nhap Tuoi.\n");
        return;
    }
    
    fflush(stdin);
	printf("Nhap Diem Trung binh: ");
    if (scanf("%f", &new_student.grade) != 1) {
        printf("Loi nhap Diem.\n");
        return;
    }
    list[*count] = new_student;
    (*count)++;
    printf("Them hoc sinh %s thanh cong.\n", new_student.name);
}

void display_all_students(const Student list[], int count) {
    if (count == 0) {
        printf("\nDanh sach rong.\n");
        return;
    }
    
    printf("\n--- DANH SACH HOC SINH (%d nguoi) ---\n", count);
    for (int i = 0; i < count; i++) {
        printf("HS %d | Ten: %-20s | Tuoi: %-3d | Diem: %.2f\n", 
               i + 1, list[i].name, list[i].age, list[i].grade);
    }
}
float calculate_average_grade(const Student list[], int count) {
    if (count == 0) {
        return 0.0f;
    }
    
    float sum_grades = 0.0f;
    for (int i = 0; i < count; i++) {
        sum_grades += list[i].grade;
    }
    
    return sum_grades / count;
}

int main() {
    Student student_list[50];
    int current_count = 0;
    int choice;

    do {
        printf("\n============ MENU QUAN LY HOC SINH ============");
        printf("\n1. Nhap thong tin hoc sinh.");
        printf("\n2. Hien thi thong tin cua hoc sinh.");
        printf("\n3. Tinh diem trung binh cua tat ca hoc sinh.");
        printf("\n0. Thoat");
        printf("\nChon thao tac: ");
		fflush(stdin);
        if (scanf("%d", &choice) != 1) {
            printf("\nLoi. Vui long nhap so nguyen \n");
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: 
                input_student_info(student_list, &current_count);
                break;
            case 2: 
                display_all_students(student_list, current_count);
                break;
            case 3: 
                printf("\nDiem trung binh cua tat ca hoc sinh la: %.2f\n", calculate_average_grade(student_list, current_count));
                break;
            case 0:
                printf("\n--- Thoat chuong trinh. Tam biet! ---\n");
                break;
            default:
                printf("\nLua chon khong hop le.\n");
        }
    } while (choice != 0);

    return 0;
}
