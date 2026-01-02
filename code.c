#include <stdio.h>
#include <string.h>

struct Room {
    char roomNo[10];
    int floor;
    char gender;
    char status[10];
};

struct Student {
    char id[10];
    int age;
    int year;
    char gender;
    char medical[5];
    int priority;
};

/* ================= AI LOGIC ================= */

int calculatePriority(struct Student s) {
    int score = 0;

    if (strcmp(s.medical, "YES") == 0)
        score += 50;

    if (s.year == 4) score += 40;
    else if (s.year == 3) score += 30;
    else score += 20;

    return score;
}

int preferredFloor(struct Student s) {
    if (strcmp(s.medical, "YES") == 0)
        return 1;          // Medical → lower floor (close to lift)
    if (s.year >= 3)
        return 2;          // Seniors → mid floors
    return 3;              // Juniors → higher floors
}

/* ================= ADD STUDENT ================= */

void addStudent() {
    FILE *sf = fopen("students.txt", "a");
    struct Student s;

    printf("\n➕ ADD NEW STUDENT\n");

    printf("Enter Student ID: ");
    scanf("%s", s.id);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Year (1-4): ");
    scanf("%d", &s.year);

    printf("Enter Gender (M/F): ");
    scanf(" %c", &s.gender);

    printf("Medical Condition (YES/NO): ");
    scanf("%s", s.medical);

    fprintf(sf, "%s,%d,%d,%c,%s\n",
            s.id, s.age, s.year, s.gender, s.medical);

    fclose(sf);

    printf("✅ Student added successfully!\n");
}

/* ================= ROOM ALLOCATION ================= */

void allocateRooms() {
    FILE *rf = fopen("rooms.txt", "r");
    FILE *sf = fopen("students.txt", "r");
    FILE *af = fopen("allocations.txt", "a");

    if (sf == NULL) {
        printf("❌ No students found. Add students first.\n");
        return;
    }

    struct Room rooms[100];
    struct Student s;
    int roomCount = 0;

    /* Load rooms */
    while (fscanf(rf, "%[^,],%d,%c,%s\n",
                  rooms[roomCount].roomNo,
                  &rooms[roomCount].floor,
                  &rooms[roomCount].gender,
                  rooms[roomCount].status) != EOF) {
        roomCount++;
    }
    fclose(rf);

    printf("\n🏨 AI-BASED ROOM ALLOCATION STARTED...\n");

    while (fscanf(sf, "%[^,],%d,%d,%c,%s\n",
                  s.id, &s.age, &s.year, &s.gender, s.medical) != EOF) {

        s.priority = calculatePriority(s);
        int prefFloor = preferredFloor(s);
        int allocated = 0;

        /* PRIMARY AI DECISION
           - Preferred floor
           - Same gender
           - EMPTY room
           Rooms are read top-down, so rooms 01 & 02 (close to lift)
           get automatically prioritized */
        for (int i = 0; i < roomCount; i++) {
            if (rooms[i].floor == prefFloor &&
                rooms[i].gender == s.gender &&
                strcmp(rooms[i].status, "EMPTY") == 0) {

                strcpy(rooms[i].status, "FULL");
                fprintf(af,
                        "%s -> %s (Floor %d, Gender %c, Priority %d)\n",
                        s.id, rooms[i].roomNo,
                        rooms[i].floor, s.gender, s.priority);
                allocated = 1;
                break;
            }
        }

        /* FALLBACK AI
           - Any available room of same gender */
        if (!allocated) {
            for (int i = 0; i < roomCount; i++) {
                if (rooms[i].gender == s.gender &&
                    strcmp(rooms[i].status, "EMPTY") == 0) {

                    strcpy(rooms[i].status, "FULL");
                    fprintf(af,
                            "%s -> %s (Fallback, Priority %d)\n",
                            s.id, rooms[i].roomNo, s.priority);
                    break;
                }
            }
        }
    }

    fclose(sf);
    fclose(af);

    /* Update rooms.txt */
    rf = fopen("rooms.txt", "w");
    for (int i = 0; i < roomCount; i++) {
        fprintf(rf, "%s,%d,%c,%s\n",
                rooms[i].roomNo,
                rooms[i].floor,
                rooms[i].gender,
                rooms[i].status);
    }
    fclose(rf);

    printf("✅ Allocation complete! Check allocations.txt\n");
}

/* ================= DISPLAY ROOMS ================= */

void displayRooms() {
    FILE *rf = fopen("rooms.txt", "r");
    struct Room r;

    printf("\n🏠 ROOM STATUS\n");
    printf("---------------------------------------\n");

    while (fscanf(rf, "%[^,],%d,%c,%s\n",
                  r.roomNo, &r.floor, &r.gender, r.status) != EOF) {
        printf("Room: %s | Floor: %d | Gender: %c | Status: %s\n",
               r.roomNo, r.floor, r.gender, r.status);
    }
    fclose(rf);
}

/* ================= MAIN MENU ================= */

int main() {
    int choice;

    do {
        printf("\n===== SMART HOSTEL ROOM ALLOCATION SYSTEM =====\n");
        printf("1. Add New Student\n");
        printf("2. Allocate Rooms (AI-Based)\n");
        printf("3. Display Room Status\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                allocateRooms();
                break;
            case 3:
                displayRooms();
                break;
            case 4:
                printf("👋 Exiting system\n");
                break;
            default:
                printf("❌ Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}