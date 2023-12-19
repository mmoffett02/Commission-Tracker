// Mikaela Moffett
// 12-9-2023
// M5 Capstone Project: Final 

// Include necessary libraries
#include <iostream>  // For console input/output (Requirement #4: Inputs and Outputs)
#include <fstream>   // For file operations (even (Requirement #6: File I/O)
#include <ctime>     // For time-related functions

// Define constants
const int MAX_DAYS = 31;               // Maximum number of days in a month
const int MAX_SALES_PER_DAY = 10;      // Assumed maximum sales per day

// Define a structure to hold sales data for each day
struct SalesData {
    int count;                         // Number of sales for the day (Requirement #4: Variables)
    double saleAmount[MAX_SALES_PER_DAY]; // Array to store individual sale amounts (Requirement #5: Arrays)
};

// Create an array of SalesData for each day of the month
SalesData sales[MAX_DAYS] = {};       //(Requirement #5: Arrays)

// Function to display the current date
void displayDate() {
    time_t t = time(0);                // Get current time
    tm* now = localtime(&t);           // Convert it to local time structure
    std::cout << "Current Date: " << (now->tm_mon + 1) << '-' << now->tm_mday << '-' << (now->tm_year + 1900) << std::endl;  //(Requirement #3: Inputs and Outputs)
}

// Function to calculate commission for a given sale amount (5% in this example)
double calculateCommission(double sale) {
    return sale * 0.05; //(Requirement #9: Control )
}

// Function to get total sales for the entire month
double getMonthlyTotal() {
    double monthlyTotal = 0.0;
    for (int day = 0; day < MAX_DAYS; day++) { //(Requirement #7: Iteration)
        for (int s = 0; s < sales[day].count; s++) { //(Requirement #7: Iteration)
            monthlyTotal += sales[day].saleAmount[s];
        }
    }
    return monthlyTotal;
}

// Function to add a sale amount for the current day
void addSale(double saleAmount) {
    time_t t = time(0);
    tm* now = localtime(&t);
    int day = now->tm_mday - 1;

    if (sales[day].count < MAX_SALES_PER_DAY) { //(Requirement #9: Control)
        sales[day].saleAmount[sales[day].count++] = saleAmount; //(Requirement #5: Arrays)
    } else {
        std::cout << "Max sales entries reached for today. Try again tomorrow.\n"; //(Requirement #3: Inputs and Outputs)
    }
}

// Stubs for loading and saving sales data to/from a file
void loadSales() {
    std::ifstream inFile ("sales_data.txt");
    if(!inFile) {
        std::cerr <<"Unable to open file for reading. \n";
        return;
    }

    int day, count;
    double saleAmount; 
    while (inFile >> day>> count) {
        sales[day].count = count; 
        for(int i = 0; i < count; i++){
            inFile >> saleAmount;
            sales[day].saleAmount[i]= saleAmount;
        }
    }
    inFile.close();
} 
//(Requirement #6: File I/O)
void saveSales() {
       std::ofstream outFile("sales_data.txt"); 
       if(!outFile){
        std::cerr <<"Unable to open file for writing. \n";
        return; 
       }

       for (int day=0; day< MAX_DAYS; day++){
        if (sales[day].count > 0){
            outFile << day << " " << sales[day].count;
            for (int s = 0; s < sales[day].count; s++) {
                outFile << " " <<sales[day].saleAmount[s];
            }
            outFile <<"\n";
        }
       }
       outFile.close();

} //(Requirement #6: File I/O)
 

// Main function where the program execution starts
int main() {
    loadSales();  // Load sales from file (if any) //(Requirement #6: File I/O)

    // Main loop for menu-driven interface
    while (true) { //(Requirement #8: Interaction, Requirement #7: Iteration)
        displayDate();
        std::cout << "Total Sales for the Month: $" << getMonthlyTotal() << "\n"; //(Requirement #3: Inputs and Outputs)
        std::cout << "Commission Calculator Menu:\n"; // (Requirement #3: Inputs and Outputs)
        std::cout << "1. Add Sale\n"; 
        std::cout << "2. View Sales\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter choice: ";

        int choice;
        std::cin >> choice; //(Requirement 3#: Inputs and Outputs)

        // Handle user's choice
        switch (choice) { //(Requirement #9: Control)
            case 1: {
                std::cout << "Enter sale amount: ";
                double sale;
                std::cin >> sale; //(Requirement #3: Inputs and Outputs)

                double commission = calculateCommission(sale);
                std::cout << "Commission: $" << commission << std::endl;

                addSale(sale);
                saveSales();  // Save current sales data to file //(Requirement #6: File I/O)

                break;
            }
            case 2:
                std::cout << "Sales for the month:\n";
                for (int day = 0; day < MAX_DAYS; day++) {
                    if (sales[day].count > 0) {
                        std::cout << "Day " << (day + 1) << ":\n";
                        for (int s = 0; s < sales[day].count; s++) {
                            std::cout << "   Sale " << (s + 1) << ": $" << sales[day].saleAmount[s] << std::endl;
                        }
                    }
                }
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please choose again.\n";
        }
    }

    return 0;  // End the program
}
