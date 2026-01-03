
⸻

🏨 Smart Hostel Room Allocation System

Language: C
Files: students.txt, rooms.txt, allocations.txt

A C-based console application designed to efficiently manage hostel room allocations using a simple AI-inspired logic that prioritizes students based on their year, medical condition, and gender.

⸻

💡 Project Overview

This project automates the process of assigning hostel rooms to students by considering:
	•	Medical conditions: Students with medical requirements are prioritized for lower floors (closer to lifts).
	•	Year of study: Seniors get preference for mid floors, while juniors are allocated higher floors.
	•	Gender-based room segregation: Ensures rooms are allocated according to gender.
	•	Room availability: Only empty rooms are allocated, and fallback allocation ensures all students get a room.

The system also maintains and updates records for:
	•	Students (students.txt)
	•	Rooms (rooms.txt)
	•	Allocations (allocations.txt)

⸻

🛠 Features
	1.	Add New Student
	•	Input student ID, age, year, gender, and medical condition.
	•	Records are stored in students.txt.
	2.	AI-Based Room Allocation
	•	Allocates rooms based on priority logic:
	•	Medical condition → lower floors
	•	Seniority → mid floors
	•	Junior → higher floors
	•	Same-gender and empty rooms are prioritized.
	•	Fallback mechanism ensures allocation even if preferred rooms are full.
	•	Updates room status in rooms.txt.
	•	Allocations are logged in allocations.txt with priority details.
	3.	Display Room Status
	•	View all rooms with their floor, gender, and occupancy status.

⸻
## ⚙️ How It Works
	1.	Student Priority Calculation
  int calculatePriority(struct Student s) {
    int score = 0;
    if (strcmp(s.medical, "YES") == 0) score += 50;
    if (s.year == 4) score += 40;
    else if (s.year == 3) score += 30;
    else score += 20;
    return score;
}

	2.	Preferred Floor Logic
  int preferredFloor(struct Student s) {
    if (strcmp(s.medical, "YES") == 0) return 1;
    if (s.year >= 3) return 2;
    return 3;
}

	3.	Room Allocation
	•	Rooms are read from rooms.txt.
	•	Each student is matched to the best available room based on floor, gender, and availability.
	•	Allocation is recorded in allocations.txt.
	•	Room status is updated to FULL after allocation.

  📂 File Structure
	•	main.c – Source code for the system
	•	students.txt – Student records (auto-generated)
	•	rooms.txt – Room details and status
	•	allocations.txt – Room allocation log

⸻

📝 Sample Room File (rooms.txt)

R101,1,M,EMPTY
R102,1,F,EMPTY
R201,2,M,EMPTY
R202,2,F,EMPTY
R301,3,M,EMPTY
R302,3,F,EMPTY

🏃 Usage
	1.	Compile the program:
gcc main.c -o hostel

	2.	Run the program:
  ./hostel

  	3.	Follow the menu:
	•	Add students
	•	Allocate rooms
	•	Display room status

  📌 Notes
	•	Ensure rooms.txt exists before running allocations.
	•	Allocation logic is simple AI-inspired scoring and can be enhanced further with advanced algorithms.
	•	The system assumes correct input formats (e.g., YES/NO for medical, M/F for gender).

⸻

🧠 Future Enhancements
	•	GUI interface for easier management.
	•	Database integration instead of text files.
	•	Real AI/ML-based dynamic allocation system considering preferences and roommate compatibility.
	•	Automatic notifications to students about their room allocations.

⸻

⚡ Author

Shubhi Gupta – Developed as a college-level project in C.
