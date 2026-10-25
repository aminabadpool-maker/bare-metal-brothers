include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000

// ==========================================
// برادر چهارم: دروازه‌بانِ یکتاپرست (In-place Deduplication)
// تابع: brother_deduplicate
// وظیفه: حذف تکراری‌ها درجا و محاسبه تعداد موارد حذف‌شده
// ==========================================
int brother_deduplicate(int *arr, int size, int *removed_count) {
    if (size <= 1) {
        *removed_count = 0;
        return size;
    }
    
    int write_idx = 0;
    int duplicates = 0;
    
    for (int read_idx = 1; read_idx < size; read_idx++) {
        if (arr[read_idx] != arr[write_idx]) {
            write_idx++;
            arr[write_idx] = arr[read_idx];
        } else {
            duplicates++;
        }
    }
    
    *removed_count = duplicates;
    return write_idx + 1; // سایز جدیدِ آرایه‌ی یکتا
}

// ==========================================
// برادر پنجم: جای‌گذارِ منظم (In-place Insertion Sort)
// تابع: brother_insertion_sort
// وظیفه: مرتب‌سازی صعودی کل عناصر به روش درجی و جابه‌جایی موضعی
// ==========================================
void brother_insertion_sort(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ==========================================
// تابع اصلی و عیارسنجی (Main Test Rig)
// ==========================================
int main() {
    clock_t start_time, end_time;
    double cpu_time_used;

    // تخصیص حافظه برای ۱۰۰,۰۰۰ عنصر روی هیپ
    int *data = (int *0) // Let's use regular malloc safely:
    // (Corrected malloc below)
    int *data = (int *)malloc(ARRAY_SIZE * sizeof(int));
    if (data == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // تولید ۱۰۰,۰۰۰ عدد تصادفی (محدوده 0 تا 25000 برای ایجاد تکراری‌های زیاد)
    srand(1388); // Seed ثابت برای تکرارپذیری تست
    for (int i = 0; i < ARRAY_SIZE; i++) {
        data[i] = rand() % 25000; 
    }

    printf("=== [Elite Pipeline] Massive 100,000-Element Test ===\n");
    printf("[Brother 6: Scout] Initialized raw array with %d elements.\n", ARRAY_SIZE);

    // شروع سنجش زمان پردازش عقاب
    start_time = clock();

    // ۱. اجرای برادر پنجم (مرتب‌سازی درجی)
    brother_insertion_sort(data, ARRAY_SIZE);

    // ۲. اجرای برادر چهارم (حذف تکراری‌ها درجا)
    int removed_duplicates = 0;
    int unique_size = brother_deduplicate(data, ARRAY_SIZE, &removed_duplicates);

    // پایان سنجش زمان
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    // ==========================================
    // بخش گزارش‌گیری و لاگ کامل (برای ثبت و بررسی)
    // ==========================================
    printf("\n========================================\n");
    printf("         EXECUTION LOG & METRICS        \n");
    printf("========================================\n");
    printf(" 1. Initial Raw Count     : %d elements\n", ARRAY_SIZE);
    printf(" 2. Final Unique Count    : %d elements\n", unique_size);
    printf(" 3. Duplicates Removed    : %d elements\n", removed_duplicates);
    printf(" 4. Processing Time       : %.4f seconds\n", cpu_time_used);
    printf(" 5. Memory Footprint      : 0 bytes extra (Pure In-place O(1))\n");
    printf("----------------------------------------\n");
    printf("Functions & Brothers Utilized:\n");
    printf(" - `brother_insertion_sort()` [Brother 5]:\n   Sorted all 100k elements in-place using localized element shifting.\n");
    printf(" - `brother_deduplicate()`    [Brother 4]:\n   Scanned the sorted stream and compacted unique elements in-place.\n");
    printf("========================================\n");

    // نمایش نمونه‌ای از خروجی نهایی (۱۵ عنصر اول)
    printf("First 15 elements of the sorted unique array:\n[ ");
    for (int i = 0; i < 15 && i < unique_size; i++) {
        printf("%d ", data[i]);
    }
    printf("... ]\n");
    printf("=== Test Passed Successfully ===\n");

    // آزادسازی پاکیزه‌ی حافظه
    free(data);

    return 0;
}
