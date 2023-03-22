#
class Node:
    def __init__(self, name, roll_number):
        self.name = name
        self.roll_number = roll_number
        self.attendance = {}
        
        self.prev = None
        self.next = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
    
    def add_student(self, name, roll_number):
        new_node = Node(name, roll_number)
        if self.head is None:
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            new_node.prev = self.tail
            self.tail = new_node
    

    def take_attendance(self, subject):
        current_node = self.head
        date = input("Enter the date for which you want to take attendance (dd-mm-yyyy): ")
        while current_node is not None:
            attendance_status = input("Is " + current_node.name + " present in " + subject + "? (Y/N)")
            if attendance_status.upper() == "Y":
                if subject in current_node.attendance:
                    current_node.attendance[subject][date] = True
                else:
                    current_node.attendance[subject] = {date: True}
            else:
                if subject in current_node.attendance:
                    current_node.attendance[subject][date] = False
                else:
                    current_node.attendance[subject] = {date: False}

            current_node = current_node.next
    
    def modify_attendance(self, roll_number, subject, date):
        student = self.get_student_details(roll_number)
        if student is None:
            print("Student not found.")
        else:
            if subject in student.attendance and date in student.attendance[subject]:
                attendance_status = input("Is " + student.name + " present in " + subject + " on " + date + "? (Y/N)")
                if attendance_status.upper() == "Y":
                    student.attendance[subject][date] = True
                else:
                    student.attendance[subject][date] = False
            else:
                print("Attendance for the given subject and date is not available.")
                
    
    def modify_student_attendance(self, roll_number):
        student = self.get_student_details(roll_number)
        if student is None:
            print("Student not found.")
        else:
            print("1. Modify attendance for all subjects")
            print("2. Modify attendance for a specific subject")
            choice = input("Enter your choice: ")
            if choice == "1":
                for subject in student.attendance:
                    date = input("Enter the date for which you want to modify attendance (dd-mm-yyyy): ")
                    if date not in student.attendance[subject]:
                        print("Attendance for the given date is not available.")
                    else:
                        self.modify_attendance(roll_number, subject, date)
            elif choice == "2":
                subject = input("Enter the subject for which you want to modify attendance: ")
                date = input("Enter the date for which you want to modify attendance (dd-mm-yyyy): ")
                if subject not in student.attendance:
                    print("Attendance for the given subject is not available.")
                elif date not in student.attendance[subject]:
                    print("Attendance for the given date is not available.")
                else:
                    self.modify_attendance(roll_number, subject, date)
            else:
                print("Invalid choice.")

    def get_attendance_percentage(self, roll_number):
        student = self.get_student_details(roll_number)
        if student is None:
            print("Student not found.")
            return

        total_classes = 0
        present_classes = 0

        for subject, attendance in student.attendance.items():
            for date, status in attendance.items():
                total_classes += 1
                if status:
                    present_classes += 1
    
        if total_classes == 0:
            print("No attendance data available for the student.")
        else:
            attendance_percentage = (present_classes / total_classes) * 100
            print(student.name + "'s attendance percentage is: " + str(attendance_percentage) + "%")

    def print_attendance(self):
        current_node = self.head
        while current_node is not None:
            total_classes = 0
            present_classes = 0

            for subject, attendance in current_node.attendance.items():
                for date, status in attendance.items():
                    total_classes += 1
                    if status:
                        present_classes += 1

            if total_classes == 0:
                print(current_node.name + ": No attendance data available for the student.")
            else:
                attendance_percentage = (present_classes / total_classes) * 100
                print(current_node.name + "'s attendance percentage is: " + str(attendance_percentage) + "%")
        
            current_node = current_node.next

    def get_student_details(self, roll_number):
        current_node = self.head
        while current_node is not None:
            if current_node.roll_number == roll_number:
                print("Name:", current_node.name)
                print("Roll Number:", current_node.roll_number)
                
                print("Attendance:", current_node.attendance)
                return
            current_node = current_node.next
        print("Student not found.")
dll = DoublyLinkedList()
print("Welcome to the Attendance Management System!")
while True:
    print("\nPlease select an option from the menu below:")
    print("1. Add a new student")
    print("2. Take attendance")
    print("3. Modify attendance for a student")
    print("4. print the attendence of all the students")
    print("5. print the attendence of perticular student")
    print("6. print all the details of the students.")
    print("7. Exit")

    choice = input("\nEnter your choice: ")
    if choice == "1":
        name = input("\nEnter the name of the student: ")
        roll_number = input("Enter the roll number of the student: ")
        dll.add_student(name, roll_number)
        print("\nStudent added successfully!")
    elif choice == "2":
        subject = input("\nEnter the subject for which you want to take attendance: ")
        dll.take_attendance(subject)
        print("\nAttendance taken successfully!")
    elif choice == "3":
        roll_number = input("\nEnter the roll number of the student: ")
        dll.modify_student_attendance(roll_number)
    elif choice == "4":
        dll.print_attendance()
    elif choice == "5":
        roll_number=input("enter the roll number of the student")
        dll.get_attendance_percentage(roll_number)
    elif choice =="6":
        roll_number=input(roll_number)
        dll.get_student_details(roll_number)
    elif choice == "7":
        print("\nThank you for using the Attendance Management System!")
        break
    else:
        print("\nInvalid choice. Please try again.")
