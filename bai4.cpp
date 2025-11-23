#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Ð?nh nghia kích thu?c
#define MAX_ORDERS 100
#define MA_DON_HANG_LEN 10
#define NAME_LEN 50
#define TRANG_THAI_LEN 20

// C?u trúc Ngày d?t hàng
typedef struct {
    int day;
    int month;
    int year;
} Date;

// C?u trúc Ðon hàng (Order)
typedef struct {
    char ma_don_hang[MA_DON_HANG_LEN];
    char ten_khach_hang[NAME_LEN];
    Date ngay_dat_hang;
    float tong_tien;
    char trang_thai[TRANG_THAI_LEN];
} Order;
void clean_newline(char str[]) {
    if (str[0] == '\0') return;
    str[strcspn(str, "\n")] = '\0';
}
void print_order_row(const Order *o, int index) {
    printf("| %-5d | %-10s | %-20s | %02d/%02d/%4d | %-10.2f | %-20s |\n",
           index, o->ma_don_hang, o->ten_khach_hang, 
           o->ngay_dat_hang.day, o->ngay_dat_hang.month, o->ngay_dat_hang.year,
           o->tong_tien, o->trang_thai);
}
void print_order_header() {
    printf("\n-----------------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-10s | %-20s | %-10s | %-10s | %-20s |\n", "STT", "Ma DH", "Ten KH", "Ngay Dat", "Tong Tien", "Trang Thai");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
}
int find_index_by_id(const Order list[], int count, const char *target_id) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].ma_don_hang, target_id) == 0) {
            return i;
        }
    }
    return -1;
}

int compare_total_asc(const void *a, const void *b) {
    const Order *orderA = (const Order *)a;
    const Order *orderB = (const Order *)b;
    if (orderA->tong_tien > orderB->tong_tien) return 1;
    if (orderA->tong_tien < orderB->tong_tien) return -1;
    return 0;
}
int compare_total_desc(const void *a, const void *b) {
    const Order *orderA = (const Order *)a;
    const Order *orderB = (const Order *)b;
    if (orderB->tong_tien > orderA->tong_tien) return 1;
    if (orderB->tong_tien < orderA->tong_tien) return -1;
    return 0;
}


int main() {
    Order order_list[MAX_ORDERS];
    int current_count = 0;
    int choice;

    do {
        printf("\n\n=============== MENU QUAN LY DON HANG ===============");
        printf("\n1. Nhap thong tin don hang moi");
        printf("\n2. Hien thi chi tiet tat ca don hang");
        printf("\n3. Cap nhat trang thai don hang");
        printf("\n4. Xoa don hang theo ma don hang");
        printf("\n5. Sap xep don hang theo tong tien");
        printf("\n6. Tim kiem don hang theo ma don hang");
        printf("\n7. Thoat");
        printf("\n=====================================================\n");
        printf("Chon thao tac: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nLoI: Vui long nhap so nguyen.\n");
            fflush(stdin);
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1: { 
                if (current_count >= MAX_ORDERS) { 
					printf("\nLOI: Danh sach da day.\n"); 
					break; 
					}
                Order *new_order = &order_list[current_count];
                
                printf("\n--- Nhap Don Hang Moi ---\n");
                fflush(stdin); 
                printf("Nhap Ma Don Hang: "); 
				fgets(new_order->ma_don_hang, MA_DON_HANG_LEN, stdin); 
				clean_newline(new_order->ma_don_hang);
                printf("Nhap Ten Khach Hang: "); 
				fgets(new_order->ten_khach_hang, NAME_LEN, stdin); 
				clean_newline(new_order->ten_khach_hang);
                printf("Ngay Dat Hang (dd mm yyyy): "); 
				scanf("%d %d %d", &new_order->ngay_dat_hang.day, &new_order->ngay_dat_hang.month, &new_order->ngay_dat_hang.year);
                printf("Nhap Tong Tien: "); 
				scanf("%f", &new_order->tong_tien);
                fflush(stdin);
                printf("Nhap Trang Thai (Dang xu ly/Da giao/Huy): "); 
				fgets(new_order->trang_thai, TRANG_THAI_LEN, stdin); 
				clean_newline(new_order->trang_thai);
                
                current_count++;
                printf("Them Don Hang %s thanh cong. Tong so: %d\n", new_order->ma_don_hang, current_count);
                break;
            }
            case 2: { 
                if (current_count == 0) { 
					printf("\nDanh sach don hang rong.\n"); 
					break; 
				}
                print_order_header();
                for (int i = 0; i < current_count; i++) {
                    print_order_row(&order_list[i], i + 1);
                }
                break;
            }
            case 3: {
                if (current_count == 0) { 
					printf("\nDanh sach rong.\n"); 
					break; 
				}
                char target_id[MA_DON_HANG_LEN];
                fflush(stdin); 
                printf("\nNhap Ma Don Hang can cap nhat: "); 
				fgets(target_id, MA_DON_HANG_LEN, stdin); 
				clean_newline(target_id);
                int index = find_index_by_id(order_list, current_count, target_id);

                if (index != -1) {
                    Order *o = &order_list[index];
                    printf("Trang thai hien tai: %s\n", o->trang_thai);
                    fflush(stdin);
                    printf("Nhap Trang Thai moi: ");
                    fgets(o->trang_thai, TRANG_THAI_LEN, stdin); 
					clean_newline(o->trang_thai);
                    
                    printf("Cap nhat trang thai thanh cong cho DH %s.\n", target_id);
                } else {
                    printf("KHONG TIM THAY Ma DH: %s\n", target_id);
                }
                break;
            }
            case 4: {
                if (current_count == 0) { 
					printf("\nDanh sach rong.\n"); 
					break; 
				}
                char target_id[MA_DON_HANG_LEN];
                fflush(stdin);
                printf("\nNhap Ma Don Hang can xoa: "); 
				fgets(target_id, MA_DON_HANG_LEN, stdin); 
				clean_newline(target_id);

                int index = find_index_by_id(order_list, current_count, target_id);

                if (index != -1) {
                    for (int i = index; i < current_count - 1; i++) {
                        order_list[i] = order_list[i + 1];
                    }
                    current_count--;
                    printf("Xoa thanh cong. Tong so don hang: %d\n", current_count);
                } else {
                    printf("KHONG TIM THAY Ma DH: %s\n", target_id);
                }
                break;
            }
            case 5: { 
                if (current_count <= 1) { 
					printf("\nDanh sach khong du de sap xep.\n"); 
					break; 
				}
                int sort_type;
                printf("\n--- MENU SAP XEP ---");
                printf("\n1. Tang dan theo Tong Tien");
                printf("\n2. Giam dan theo Tong Tien");
                printf("\nChon kieu sap xep (1/2): ");
                if (scanf("%d", &sort_type) != 1 || (sort_type != 1 && sort_type != 2)) { 
					printf("Loi lua chon.\n"); 
					break; 
				}
                
                if (sort_type == 1) {
                    qsort(order_list, current_count, sizeof(Order), compare_total_asc);
                    printf("Sap xep TANG DAN thanh cong.\n");
                } else {
                    qsort(order_list, current_count, sizeof(Order), compare_total_desc);
                    printf("Sap xep GIAM DAN thanh cong.\n");
                }
                break;
            }
            case 6: { 
                if (current_count == 0) { 
					printf("\nDanh sach rong.\n"); 
					break; 
				}
                char target_id[MA_DON_HANG_LEN];
                fflush(stdin);
                printf("\nNhap Ma Don Hang can tim: "); 
				fgets(target_id, MA_DON_HANG_LEN, stdin); 
				clean_newline(target_id);
                int index = find_index_by_id(order_list, current_count, target_id);

                if (index != -1) {
                    printf("\nTIM THAY Don Hang (Ma DH: %s):\n", target_id);
                    print_order_row(&order_list[index], index + 1);
                } else {
                    printf("\nKHONG TIM THAY Ma DH: %s\n", target_id);
                }
                break;
            }
            case 7: {
                printf("\n--- Thoat chuong trinh quan ly don hang. Tam biet! ---\n");
                break;
            }
            default: {
                printf("\nLua chon khong hop le.\n");
            }
        }
    } while (choice != 7);

    return 0;
}

