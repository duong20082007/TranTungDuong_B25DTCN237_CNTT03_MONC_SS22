#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Ð?nh nghia kích thu?c
#define MAX_STUDENTS 100
#define MA_SV_LEN 10
#define NAME_LEN 50
#define PHONE_LEN 15
#define DIA_CHI_LEN 100

// C?u trúc Ngày sinh
typedef struct {
    int day;
    int month;
    int year;
} Date;

// C?u trúc Sinh vien (Struct l?ng nhau)
typedef struct {
    char ma_sv[MA_SV_LEN];
    char ho_ten[NAME_LEN];
    Date ngay_sinh;
    char dia_chi[DIA_CHI_LEN];
    char dien_thoai[PHONE_LEN];
} Student;

// Khai báo các hàm c?n thi?t
void clean_newline(char str[]);
void clear_input_buffer();
void print_student_row(const Student *s, int index);
void print_student_header();

// Hàm so sánh cho qsort
int compareStudentsByName(const void *a, const void *b);

int main() {
    Student list[MAX_STUDENTS];
    int current_count = 0;
    int choice;
    int i, j; // Bi?n ch? s? vòng l?p
    int target_id_index; // Bi?n luu ch? s? tìm du?c

    do {
        // --- HI?N TH? MENU (Gom vào main) ---
        printf("\n\n============ MENU QUAN LY SINH VIEN ============");
        printf("\n1. Nhap thong tin sinh vien");
        printf("\n2. Hien thi thong tin sinh vien");
        printf("\n3. Them sinh vien vao cuoi danh sach");
        printf("\n4. Xoa sinh vien theo ma sinh vien");
        printf("\n5. Cap nhat thong tin sinh vien theo ma sinh vien");
        printf("\n6. Sap xep sinh vien theo ho ten (A-Z)");
        printf("\n7. Tim kiem sinh vien theo ma sinh vien");
        printf("\n8. Thoat");
        printf("\n================================================\n");
        printf("Chon thao tac: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nL?i: Vui long nhap so nguyen.\n");
            clear_input_buffer();
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: {
                if (current_count >= MAX_STUDENTS) { 
					printf("Mang da day.\n"); 
					break; 
				}
                
                Student *new_sv = &list[current_count];
                clear_input_buffer(); 

                printf("\n--- Nhap SV thu %d ---\n", current_count + 1);
                printf("Ma SV: "); 
				fgets(new_sv->ma_sv, MA_SV_LEN, stdin); clean_newline(new_sv->ma_sv);
                printf("Ho Ten: "); 
				fgets(new_sv->ho_ten, NAME_LEN, stdin); clean_newline(new_sv->ho_ten);
                printf("Ngay Sinh: "); 
				scanf("%d %d %d", &new_sv->ngay_sinh.day, &new_sv->ngay_sinh.month, &new_sv->ngay_sinh.year);
                clear_input_buffer();
                printf("Dia chi: "); 
				fgets(new_sv->dia_chi, DIA_CHI_LEN, stdin); clean_newline(new_sv->dia_chi);
                printf("Dien thoai: "); 
				fgets(new_sv->dien_thoai, PHONE_LEN, stdin); clean_newline(new_sv->dien_thoai);
                
                current_count++;
                printf("Them SV thanh cong. Tong SV: %d\n", current_count);
                break;
            }

            case 2: {
                if (current_count == 0) { 
					printf("\nDanh sach rong.\n");
					break; 
				}
                print_student_header();
                for (i = 0; i < current_count; i++) {
                    print_student_row(&list[i], i + 1);
                }
                break;
            }

            case 3: {
                if (current_count >= MAX_STUDENTS) { 
					printf("Mang da day.\n"); 
					break; 
				}
                
                Student *new_sv = &list[current_count];
                clear_input_buffer(); 

                printf("\n--- Them SV vao CUOI DS ---\n");
                printf("Ma SV: "); fgets(new_sv->ma_sv, MA_SV_LEN, stdin); 
				clean_newline(new_sv->ma_sv);
                printf("Ho Ten: "); fgets(new_sv->ho_ten, NAME_LEN, stdin); 
				clean_newline(new_sv->ho_ten);
                printf("Ngay Sinh: "); scanf("%d %d %d", &new_sv->ngay_sinh.day, &new_sv->ngay_sinh.month, &new_sv->ngay_sinh.year);
                clear_input_buffer();
                printf("Dia chi: "); fgets(new_sv->dia_chi, DIA_CHI_LEN, stdin); 
				clean_newline(new_sv->dia_chi);
                printf("Dien thoai: "); fgets(new_sv->dien_thoai, PHONE_LEN, stdin); 
				clean_newline(new_sv->dien_thoai);
                
                current_count++;
                printf("Them SV vao cuoi DS thanh cong.\n");
                break;
            }

            case 4: { 
                char target_id[MA_SV_LEN];
                int found_index = -1;
                
                clear_input_buffer(); 
                printf("\nNhap Ma SV can xoa: "); fgets(target_id, MA_SV_LEN, stdin); clean_newline(target_id);

                for (i = 0; i < current_count; i++) {
                    if (strcmp(list[i].ma_sv, target_id) == 0) {
                        found_index = i;
                        break;
                    }
                }
                
                if (found_index != -1) {
                    for (i = found_index; i < current_count - 1; i++) {
                        list[i] = list[i + 1];
                    }
                    current_count--;
                    printf("Xoa SV %s thanh cong.\n", target_id);
                } else {
                    printf("KHONG TIM THAY Ma SV: %s\n", target_id);
                }
                break;
            }

            case 5: { 
                char target_id[MA_SV_LEN];
                int found_index = -1;
                
                clear_input_buffer(); 
                printf("\nNhap Ma SV can cap nhat: "); fgets(target_id, MA_SV_LEN, stdin); clean_newline(target_id);

                for (i = 0; i < current_count; i++) {
                    if (strcmp(list[i].ma_sv, target_id) == 0) {
                        found_index = i;
                        break;
                    }
                }
                
                if (found_index != -1) {
                    Student *sv = &list[found_index];
                    printf("Cap nhat SV: %s\n", sv->ho_ten);

                    clear_input_buffer(); 
                    printf("Ho Ten moi: "); 
					fgets(sv->ho_ten, NAME_LEN, stdin); clean_newline(sv->ho_ten);
                    printf("Ngay Sinh moi: "); 
					scanf("%d %d %d", &sv->ngay_sinh.day, &sv->ngay_sinh.month, &sv->ngay_sinh.year);
                    clear_input_buffer();
                    printf("Dia chi moi: "); 
					fgets(sv->dia_chi, DIA_CHI_LEN, stdin); clean_newline(sv->dia_chi);
                    printf("Dien thoai moi: "); 
					fgets(sv->dien_thoai, PHONE_LEN, stdin); clean_newline(sv->dien_thoai);

                    printf("Cap nhat thanh cong!\n");
                } else {
                    printf("KHONG TIM THAY Ma SV: %s\n", target_id);
                }
                break;
            }

            case 6: { 
                if (current_count > 1) {
                    qsort(list, current_count, sizeof(Student), compareStudentsByName);
                    printf("Danh sach da duoc sap xep theo Ten (A-Z).\n");
                } else {
                    printf("Khong du phan tu de sap xep.\n");
                }
                break;
            }

            case 7: { 
                char target_id[MA_SV_LEN];
                int found_index = -1;
                
                clear_input_buffer(); 
                printf("\nNhap Ma SV can tim: "); fgets(target_id, MA_SV_LEN, stdin); clean_newline(target_id);

                for (i = 0; i < current_count; i++) {
                    if (strcmp(list[i].ma_sv, target_id) == 0) {
                        found_index = i;
                        break;
                    }
                }
                
                if (found_index != -1) {
                    printf("\nTIM THAY SV (ID: %s)\n", target_id);
                    print_student_row(&list[found_index], 1); 
                } else {
                    printf("KHONG TIM THAY Ma SV: %s\n", target_id);
                }
                break;
            }

            case 8: {
                printf("\n--- Thoat chuong trinh. Tam biet! ---\n");
                break;
            }

            default: {
                printf("\nLua chon khong hop le. Vui long chon lai.\n");
            }
        }
    } while (choice != 8);

    return 0;
}
void clean_newline(char str[]) {
    if (str[0] == '\0') {
	return;
	}
    str[strcspn(str, "\n")] = '\0';
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_student_header() {
    printf("\n-------------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-20s | %-10s | %-30s | %-15s |\n",
           "STT", "Ma SV", "Ho Ten", "Ngay Sinh", "Dia chi", "Dien thoai");
    printf("-------------------------------------------------------------------------------------------------------------\n");
}

void print_student_row(const Student *s, int index) {
    printf("| %-5d | %-10s | %-20s | %2d/%2d/%4d | %-30s | %-15s |\n",
           index, s->ma_sv, s->ho_ten, s->ngay_sinh.day, s->ngay_sinh.month, s->ngay_sinh.year, s->dia_chi, s->dien_thoai);
}

int compareStudentsByName(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return strcmp(studentA->ho_ten, studentB->ho_ten);
}
