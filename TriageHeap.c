#include <stdio.h>
#include <string.h>
#define MAX 100
struct Patient {
    char name[50];
    int age;
    int emergencyLevel;
    int priorityScore;
};
struct Patient heap[MAX];
int heapSize = 0;
// ---------- SWAP FUNCTION ----------
void swap(struct Patient *a, struct Patient *b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}
// ---------- INSERT INTO MAX HEAP ----------
void insertPatient(struct Patient p) {
    heap[++heapSize] = p;
    int i = heapSize;
    while (i > 1 && heap[i].priorityScore > heap[i/2].priorityScore) {
        swap(&heap[i], &heap[i/2]);
        i /= 2;
    }
}
// ---------- REMOVE HIGHEST PRIORITY ----------
struct Patient extractMax() {
    struct Patient maxPatient = heap[1];
    heap[1] = heap[heapSize--];
    int i = 1;
    while (1) {
        int left = 2*i;
        int right = 2*i + 1;
        int largest = i;
        if (left <= heapSize && heap[left].priorityScore > heap[largest].priorityScore)
            largest = left;
        if (right <= heapSize && heap[right].priorityScore > heap[largest].priorityScore)
        largest = right;
        if (largest == i)
            break;
        swap(&heap[i], &heap[largest]);
        i = largest;
    }
    return maxPatient;
}
// ----------------------------------------------------
// NEW FUNCTION: ASK QUESTIONS TO SET EMERGENCY LEVEL
// ----------------------------------------------------
int determineEmergencyLevel() {
    int score = 0, ans;
    printf("\n-- Answer the following to determine emergency level --\n");
    printf("1. Heavy bleeding? (1=Yes, 0=No): ");
    scanf("%d", &ans);
    if (ans == 1) score += 3;
    printf("2. Chest pain? (1=Yes, 0=No): ");
    scanf("%d", &ans);
    if (ans == 1) score += 3;
    printf("3. Difficulty breathing? (1=Yes, 0=No): ");
    scanf("%d", &ans);
    if (ans == 1) score += 3;
    printf("4. Unconscious/fainting? (1=Yes, 0=No): ");
    scanf("%d", &ans);
    if (ans == 1) score += 4;
    printf("5. Pain level (0-10): ");
    scanf("%d", &ans);
    if (ans >= 8) score += 3;
    else if (ans >= 5) score += 2;
    else if (ans >= 2) score += 1;
    // Convert score ? emergency level 1–5
    if (score >= 12) return 5;
    if (score >= 9) return 4;
    if (score >= 6) return 3;
    if (score >= 3) return 2;
    return 1;
}
// ---------- PRIORITY SCORE CALCULATION ----------
int calculatePriority(int emergency, int age) {
    int score = emergency * 10;
    if (age > 60) score += 5;
    return score;
}
// ---------- MAIN ----------
int main() {
    int n;
    printf("Enter number of patients: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        struct Patient p;
        printf("\nEnter patient %d name: ", i + 1);
        scanf("%s", p.name);
        printf("Age: ");
        scanf("%d", &p.age);
   printf("\n--- Triage assessment for %s ---\n", p.name);
    p.emergencyLevel = determineEmergencyLevel();
    printf("Calculated Emergency Level = %d\n", p.emergencyLevel);
        p.priorityScore = calculatePriority(p.emergencyLevel, p.age);
        insertPatient(p);
    }
    printf("\n===== TREATMENT ORDER (GREEDY: Highest Priority First) =====\n");
    while (heapSize > 0) {
        struct Patient p = extractMax();
        printf("Patient: %-10s | Emergency Level: %d | Age: %d | Priority Score: %d\n",
               p.name, p.emergencyLevel, p.age, p.priorityScore);
    }
    return 0;
}