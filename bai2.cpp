#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTACTS 100
#define NAME_SIZE 50
#define PHONE_SIZE 15
#define EMAIL_SIZE 50

typedef struct {
    char name[NAME_SIZE];
    char phoneNumber[PHONE_SIZE];
    char email[EMAIL_SIZE];
} Contact;

int main() {
    Contact contact_list[MAX_CONTACTS];
    int current_count = 0;
    int choice;

    do {
        printf("\n\n============ MENU QUAN LY LIEN HE ============");
        printf("\n1. Them lien he moi.");
        printf("\n2. Hien thi tat ca lien he.");
        printf("\n3. Tim kiem theo ten.");
        printf("\n4. Xoa lien he theo ten.");
        printf("\n0. Thoat");
        printf("\n============================================\n");
        printf("Chon thao tac: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nL?i: Vui long nhap so nguyen.\n");
            fflush(stdin);
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: { 
                if (current_count == 0) {
					printf("\nDanh ba rong.\n"); 
					break; 
				}
                
                Contact new_contact;
                
                printf("\n--- Nhap lien he moi ---\n");
                 
				fflush(stdin);
                printf("Nhap Ten: "); 
                fgets(new_contact.name, NAME_SIZE, stdin); 
                fflush(stdin);
                
                printf("Nhap So dien thoai: ");
                fgets(new_contact.phoneNumber, PHONE_SIZE, stdin); clean_newline(new_contact.phoneNumber);
                
                printf("Nhap Email: ");
                fgets(new_contact.email, EMAIL_SIZE, stdin); clean_newline(new_contact.email);
                
                contact_list[current_count] = new_contact;
                current_count++;
                printf("Them lien he %s thanh cong. Tong so: %d\n", new_contact.name, current_count);
                break;
            }

            case 2: { 
                if (current_count == 0) { printf("\n=> Danh b? r?ng.\n"); break; }
                
                print_contact_header();
                for (int i = 0; i < current_count; i++) {
                    print_contact_row(&contact_list[i]);
                }
                break;
            }

            case 3: {
                if (current_count == 0) {
					printf("\nDanh ba rong.\n"); 
					break; 
				}
                
                char target_name[NAME_SIZE];
                int found_index = -1;
                
                fflush(stdin);
                printf("\nNhap Ten lien he can tim: ");
                fgets(target_name, NAME_SIZE, stdin); clean_newline(target_name);
                
                for (int i = 0; i < current_count; i++) {
                    if (strcasecmp(contact_list[i].name, target_name) == 0) { 
                        found_index = i;
                        break;
                    }
                }
                
                if (found_index != -1) {
                    printf("\nTIM THAY lien he:\n");
                    print_contact_header();
                    print_contact_row(&contact_list[found_index]);
                } else {
                    printf("\nKHONG TIM THAY lien he voi ten '%s'.\n", target_name);
                }
                break;
            }

            case 4: { 
                if (current_count == 0) {
					printf("\nDanh ba rong.\n"); 
					break; 
				}
                
                char target_name[NAME_SIZE];
                int found_index = -1;
                
                fflush(stdin);
                printf("\nNhap Ten lien he can XOA: ");
                fgets(target_name, NAME_SIZE, stdin); 
				clean_newline(target_name);

                for (int i = 0; i < current_count; i++) {
                    if (strcasecmp(contact_list[i].name, target_name) == 0) { 
                        found_index = i;
                        break;
                    }
                }
                
                if (found_index != -1) {
                    for (int i = found_index; i < current_count - 1; i++) {
                        contact_list[i] = contact_list[i + 1];
                    }
                    
                    current_count--;
                    printf("=> Xoa thanh cong. Tong so lien he: %d\n", current_count);
                } else {
                    printf("=> KHONG TIM THAY lien he voi ten '%s'. Khong the xoa.\n", target_name);
                }
                break;
            }
            case 0: {
                printf("\n--- Thoát chuong trình qu?n lý liên h?. T?m bi?t! ---\n");
                break;
            }
            default: {
                printf("\nL?a ch?n không h?p l?. Vui lòng ch?n l?i.\n");
            }
        }
    } while (choice != 0);

    return 0;
}

void clean_newline(char str[]) {
    if (str[0] == '\0') return;
    str[strcspn(str, "\n")] = '\0';
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_contact_row(const Contact *c) {
    printf("| %-25s | %-15s | %-30s |\n", c->name, c->phoneNumber, c->email);
}

void print_contact_header() {
    printf("\n--------------------------------------------------------------------------------\n");
    printf("| %-25s | %-15s | %-30s |\n", "Ten", "So Dien Thoai", "Email");
    printf("--------------------------------------------------------------------------------\n");
}
