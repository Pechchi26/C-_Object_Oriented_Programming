/*
#include <iostream>
#include <vector>

using namespace std;

struct Student
{
    string name_;
    string birth_day_;
};

// Prints the given student and preceding text if such is given.
void print(Student* student, const string& pre_text = "")
{
    cout << pre_text;
    if(student)
    {
        cout << student->name_ << " --- " << student->birth_day_ << endl;
    }
    else
    {
        cout << "None" << endl;
    }
}

// Function to find the first occurrence of a student with a given name and birthday in a course.
Student* find_first_occurrence(const string& name, const string& birth_day, const vector<Student*>& course)
{
    for (Student* student : course)
    {
        if (student && student->name_ == name && student->birth_day_ == birth_day)
        {
            return student; // Return the first matching student
        }
    }
    return nullptr; // Return nullptr if no match found
}

// Function to find and print the same students in two courses.
void find_same(const vector<Student*>& course1, const vector<Student*>& course2)
{
    for (Student* student1 : course1)
    {
        for (Student* student2 : course2)
        {
            if (student1 && student2 && student1 == student2) // Check if they point to the same student
            {
                print(student1, "* Same student in two courses: ");
            }
        }
    }
}

// Function to find and print identical students from a course (same name and birthday, different students).
void find_identical(const vector<Student*>& course)
{
    bool found_identical = false;
    for (size_t i = 0; i < course.size(); ++i)
    {
        for (size_t j = i + 1; j < course.size(); ++j)
        {
            if (course[i] && course[j] &&
                course[i]->name_ == course[j]->name_ &&
                course[i]->birth_day_ == course[j]->birth_day_)
            {
                print(course[i], "* Identical students in a course: ");
                found_identical = true;
                break; // Only print once for each unique pair
            }
        }
    }
    if (!found_identical)
    {
        cout << "* No identical students in a course." << endl;
    }
}

// Don't remove! Needed for tests.
#ifndef POINTERS_TEST
#define POINTERS_TEST
// Don't remove! Needed for tests.

// Main function (an example test case)
int main()
{
    // Students
    Student stud1{"Mortti", "2001-01-01"};
    Student stud2{"Vertti", "2002-02-02"};
    Student stud3{"Mortti", "2001-01-01"};

    // Assigning students to courses
    vector<Student*> prog1 = {nullptr, &stud1, &stud2};
    vector<Student*> prog2 = {&stud1, &stud2, &stud3};
    vector<Student*> prog3 = {&stud1, &stud3};

    // Different seaches
    cout << "Seaching for same students from two different courses" << endl;
    find_same(prog1, prog2);

    cout << endl << "Searching for identical students from a course" << endl;
    find_identical(prog3);

    cout << endl << "Searching for a certain student from a course" << endl;
    Student* wanted = find_first_occurrence("Mortti", "2001-01-01", prog1);
    print(wanted, "* ");
    wanted = find_first_occurrence("Mortti", "2002-02-02", prog1);
    print(wanted, "* ");

    return 0;
}

// Don't remove! Needed for tests.
#endif //POINTERS_TEST
// Don't remove! Needed for tests. */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student
{
    string name_;
    string birth_day_;
};

// Prints the given student and preceding text if such is given.
void print(Student* student, const string& pre_text = "")
{
    cout << pre_text;
    if(student)
    {
        cout << student->name_ << " --- " << student->birth_day_ << endl;
    }
    else
    {
        cout << "None" << endl;
    }
}

Student* find_first_occurrence(const string& name, const string& birth_day, const vector<Student*>& course)
{
    for (Student* student : course)
    {
        if (student != nullptr && student->name_ == name && student->birth_day_ == birth_day)
        {
            return student;
        }
    }
    return nullptr;
}


void find_same(const vector<Student*>& course1, const vector<Student*>& course2)
{
    for (Student* student1 : course1)
    {
        for (Student* student2 : course2)
        {
            // Check if the same student exists in both courses (same pointer)
            if (student1 != nullptr && student1 == student2)
            {
                print(student1, "* Same student in two courses: ");
            }
        }
    }
}

// Function to find and print identical students (with same name and birthday but different instances)
void find_identical(const vector<Student*>& course)
{
    for (size_t i = 0; i < course.size(); ++i)
    {
        for (size_t j = i + 1; j < course.size(); ++j)
        {
            Student* student1 = course[i];
            Student* student2 = course[j];

            // Check if they are identical in terms of name and birth_day but different instances
            if (student1 != nullptr && student2 != nullptr &&
                student1->name_ == student2->name_ &&
                student1->birth_day_ == student2->birth_day_ &&
                student1 != student2)
            {
                print(student1, "* Identical students in a course: ");
            }
        }
    }
}



// Don't remove! Needed for tests.
#ifndef POINTERS_TEST
#define POINTERS_TEST
// Don't remove! Needed for tests.


// Main function (an example test case)
int main()
{
    // Students
    Student stud1{"Mortti", "2001-01-01"};
    Student stud2{"Vertti", "2002-02-02"};
    Student stud3{"Mortti", "2001-01-01"};

    // Assigning students to courses
    vector<Student*> prog1 = {nullptr, &stud1, &stud2};
    vector<Student*> prog2 = {&stud1, &stud2, &stud3};
    vector<Student*> prog3 = {&stud1, &stud3};

    // Different seaches
    cout << "Seaching for same students from two different courses" << endl;
    find_same(prog1, prog2);

    cout << endl << "Searching for identical students from a course" << endl;
    find_identical(prog3);

    cout << endl << "Searching for a certain student from a course" << endl;
    Student* wanted = find_first_occurrence("Mortti", "2001-01-01", prog1);
    print(wanted, "* ");
    wanted = find_first_occurrence("Mortti", "2002-02-02", prog1);
    print(wanted, "* ");

    return 0;
}

// Don't remove! Needed for tests.
#endif //POINTERS_TEST
// Don't remove! Needed for tests.
