# Clinic Management System
This project is a command-line based clinic management system implemented in C. It allows administrative staff to manage patient records, schedule appointments with doctors, and make reservations for available time slots. It also provides users with the ability to view patient records and today's reservations.

# Features
* User authentication with password protection for administrative mode.
* Add new patient records with unique IDs.
* Edit existing patient records.
* Reserve available time slots with doctors.
* Cancel reservations.
* View all patients' records.
* View today's reservations.

# System Requirements
To run this project, you need:

* C compiler (GCC or any C compiler that supports C99)
* Standard C libraries (stdio.h, stdlib.h, string.h)

# Instructions
1. Clone the repository to your local machine.
```
 git clone https://github.com/your-username/clinic-management-system.git
```

2. Compile the source code using a compatible C compiler.
```
gcc main.c -o clinic
```

3. Run the compiled binary.
```
./clinic
```

4. Choose between Admin Mode or User Mode by entering the corresponding option:
* Admin Mode: Enter the provided password (default password: 1234) for access to administrative features.
* User Mode: No password is required. Users can view patient records and today's reservations.

# Usage
# Admin Mode
In Admin Mode, the following features are available:

* Add new patient record: Enter the patient's name, age, gender, and a unique ID.
* Edit patient record: Enter the patient ID to modify their information.
* Reserve a slot with the doctor: Choose an available time slot and enter the patient ID.
* Cancel reservation: Enter the patient ID to cancel a reservation.
* Print all patients: Display all patient records.
* Print all reservations: Show all reservations made.

# User Mode
In User Mode, the following features are available:

* View patient record: Enter the patient ID to view their information.
* View today's reservations: Display all reservations for the current day.

# Contributing
Contributions are welcome! Feel free to open issues or submit pull requests to improve the project.

# License
This project is licensed under the MIT License.

# Acknowledgments
Special thanks to IMT and iti for their help and support in teaching me to be able to develop this project.


