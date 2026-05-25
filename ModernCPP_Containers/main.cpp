/// \file main.cpp
/// \brief Demonstrates modern C++ STL containers, algorithms, and file I/O.
///
/// This example shows practical usage of:
/// - STL containers (vector, map, set, deque)
/// - Algorithms (sort, find, transform, filter)
/// - String manipulation and formatting
/// - File I/O operations
/// - Lambda expressions
/// - Range-based for loops
/// - Structured bindings (C++17)
///
/// Use case: Processing and analyzing student grades from a file.
///
/// \author Easy Examples
/// \version 1.0

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <numeric>

/// \brief Structure representing a student record.
struct Student {
    std::string name;  ///< Student name.
    int id;            ///< Student ID.
    double grade;      ///< Grade (0-100).
    
    /// \brief Default constructor.
    Student() : name(""), id(0), grade(0.0) {}
    
    /// \brief Construct student with all fields.
    /// \param n Name
    /// \param i ID
    /// \param g Grade
    Student(const std::string& n, int i, double g) : name(n), id(i), grade(g) {}
};

/// \brief Demonstrate vector container and algorithms.
void demonstrateVectors() {
    std::cout << "\n=== Vector Container & Algorithms ===" << std::endl;
    
    // Create vector of students
    std::vector<Student> students = {
        {"Alice", 101, 85.5},
        {"Bob", 102, 92.0},
        {"Charlie", 103, 78.5},
        {"Diana", 104, 95.0},
        {"Eve", 105, 88.0}
    };
    
    std::cout << "Original students:" << std::endl;
    for (const auto& student : students) {
        std::cout << "  " << student.name << " (ID: " << student.id 
                  << ") - Grade: " << student.grade << std::endl;
    }
    
    // Sort by grade (descending)
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) { return a.grade > b.grade; });
    
    std::cout << "\nSorted by grade (descending):" << std::endl;
    for (const auto& student : students) {
        std::cout << "  " << student.name << ": " << student.grade << std::endl;
    }
    
    // Find student with grade above 90
    auto highAchievers = students | 
        std::views::filter([](const Student& s) { return s.grade >= 90.0; });
    
    std::cout << "\nHigh achievers (grade >= 90):" << std::endl;
    for (const auto& student : highAchievers) {
        std::cout << "  " << student.name << ": " << student.grade << std::endl;
    }
    
    // Calculate average
    double average = std::accumulate(students.begin(), students.end(), 0.0,
        [](double sum, const Student& s) { return sum + s.grade; }) / students.size();
    
    std::cout << "\nAverage grade: " << std::fixed << std::setprecision(2) 
              << average << std::endl;
}

/// \brief Demonstrate map container for lookups.
void demonstrateMaps() {
    std::cout << "\n=== Map Container (Student Lookup) ===" << std::endl;
    
    std::map<int, std::string> gradeLetters = {
        {90, "A"}, {80, "B"}, {70, "C"}, {60, "D"}, {0, "F"}
    };
    
    std::vector<double> grades = {85.5, 92.0, 78.5, 95.0, 88.0, 55.0};
    
    std::cout << "Grade conversion:" << std::endl;
    for (double grade : grades) {
        // Find appropriate letter grade
        auto it = gradeLetters.lower_bound(static_cast<int>(grade));
        if (it != gradeLetters.begin()) {
            --it;
            std::cout << "  " << std::fixed << std::setprecision(1) 
                      << grade << " -> " << it->second << std::endl;
        }
    }
}

/// \brief Demonstrate set container for unique values.
void demonstrateSets() {
    std::cout << "\n=== Set Container (Unique Values) ===" << std::endl;
    
    std::vector<int> scores = {85, 90, 85, 95, 90, 78, 95, 88};
    
    std::set<int> uniqueScores(scores.begin(), scores.end());
    
    std::cout << "All unique scores (sorted): ";
    for (int score : uniqueScores) {
        std::cout << score << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Number of unique scores: " << uniqueScores.size() << std::endl;
}

/// \brief Demonstrate string manipulation.
void demonstrateStrings() {
    std::cout << "\n=== String Manipulation ===" << std::endl;
    
    std::string fullName = "  John Michael Smith  ";
    
    // Trim whitespace
    auto start = fullName.find_first_not_of(" \t\n\r");
    auto end = fullName.find_last_not_of(" \t\n\r");
    std::string trimmed = fullName.substr(start, end - start + 1);
    
    std::cout << "Original: \"" << fullName << "\"" << std::endl;
    std::cout << "Trimmed:  \"" << trimmed << "\"" << std::endl;
    
    // Split by space
    std::cout << "Name parts: ";
    std::istringstream iss(trimmed);
    std::string word;
    while (iss >> word) {
        std::cout << "[" << word << "] ";
    }
    std::cout << std::endl;
}

/// \brief Demonstrate file I/O operations.
void demonstrateFileIO() {
    std::cout << "\n=== File I/O Operations ===" << std::endl;
    
    // Write data to file
    const std::string filename = "grades.txt";
    {
        std::ofstream outfile(filename);
        outfile << "Student Grades Report\n";
        outfile << "====================\n";
        outfile << std::left << std::setw(15) << "Name" 
                << std::right << std::setw(10) << "Grade\n";
        outfile << std::string(25, '-') << "\n";
        
        std::vector<Student> students = {
            {"Alice", 101, 85.5},
            {"Bob", 102, 92.0},
            {"Charlie", 103, 78.5}
        };
        
        for (const auto& student : students) {
            outfile << std::left << std::setw(15) << student.name
                    << std::right << std::setw(10) << std::fixed 
                    << std::setprecision(1) << student.grade << "\n";
        }
    }
    
    std::cout << "File written: " << filename << std::endl;
    
    // Read data from file
    std::cout << "\nFile contents:\n";
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << "  " << line << std::endl;
    }
    infile.close();
}

/// \brief Demonstrate range-based for loops and structured bindings (C++17).
void demonstrateModernFeatures() {
    std::cout << "\n=== Modern C++ Features ===" << std::endl;
    
    // Map with structured bindings
    std::map<std::string, int> idMap = {
        {"Alice", 101}, {"Bob", 102}, {"Charlie", 103}
    };
    
    std::cout << "Structured bindings from map:" << std::endl;
    for (const auto& [name, id] : idMap) {
        std::cout << "  " << name << " -> " << id << std::endl;
    }
    
    // Lambda with capture
    int multiplier = 2;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    std::cout << "\nTransform with lambda (multiply by " << multiplier << "):" << std::endl;
    std::cout << "  ";
    std::transform(numbers.begin(), numbers.end(),
        std::ostream_iterator<int>(std::cout, " "),
        [multiplier](int n) { return n * multiplier; });
    std::cout << std::endl;
}

/// \brief Main entry point demonstrating all STL container and algorithm features.
int main() {
    std::cout << "=== Modern C++ Containers & Algorithms ===" << std::endl;
    std::cout << "Demonstrating STL, file I/O, and C++17 features\n";
    
    demonstrateVectors();
    demonstrateMaps();
    demonstrateSets();
    demonstrateStrings();
    demonstrateFileIO();
    demonstrateModernFeatures();
    
    std::cout << "\n=== Example completed successfully ===" << std::endl;
    
    return 0;
}
