#include <iostream>
#include <iomanip>
using namespace std;

string months[] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

int daysInMonth(int month, int year) {
    if (month == 2) {
        // Leap year check
        return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28;
    }
    // Months with 30 days
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    return 31;
}

// Zeller’s Congruence to find starting day of the week
int getStartDay(int month, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int K = year % 100;
    int J = year / 100;
    int d = 1;
    int f = d + (13 * (month + 1)) / 5 + K + K/4 + J/4 + 5 * J;
    return f % 7;
}

// Map Zeller’s to calendar: 0 = Sunday, ... 6 = Saturday
int mapZellerToCalendar(int zellerDay) {
    return (zellerDay + 6) % 7;
}

void printCalendar(int month, int year) {
    int days = daysInMonth(month, year);
    int start = mapZellerToCalendar(getStartDay(month, year));

    cout << "\n📅 " << months[month] << " " << year << "\n";
    cout << "-----------------------------\n";
    cout << " Sun Mon Tue Wed Thu Fri Sat\n";

    // 2D array (6 weeks x 7 days)
    int calendar[6][7] = {0};

    int day = 1, row = 0;
    for (int i = start; day <= days; i++) {
        if (i == 7) {
            i = 0;
            row++;
        }
        calendar[row][i] = day++;
    }

    // Print calendar
    for (int i = 0; i < 6; i++) {
        bool emptyWeek = true;
        for (int j = 0; j < 7; j++) {
            if (calendar[i][j] != 0) {
                cout << setw(4) << calendar[i][j];
                emptyWeek = false;
            } else {
                cout << "    ";
            }
        }
        if (!emptyWeek) cout << "\n";
   }
}

int main() {
    int month, year;
    cout << "📆 Enter month (1-12): ";
    cin >> month;
    cout << "📅 Enter year: ";
    cin >> year;

    if (month < 1 || month > 12 || year < 1) {
        cout << "❌ Invalid input.\n";
        return 1;
    }

    printCalendar(month, year);
    return 0;
}