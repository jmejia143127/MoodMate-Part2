//***************************************************************
//Author.....: Jorge Mejia
//Assignment.: MoodMate - Part 2
//Description: This program stores mood entries using a MoodEntry
//             class and manages them using a MoodTracker class.
//
//***************************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

class MoodEntry {
private:
    string date;
    int rating;
    string note;
public:
    MoodEntry();
    MoodEntry(string date, int rating, string note);
    void setDate(string date);
    void setRating(int rating);
    void setNote(string note);
    string getDate() const;
    int getRating() const;
    string getNote() const;
    string getMoodLabel() const;
    void printEntry() const;
};

class MoodTracker {
private:
    MoodEntry entries[20];
    int entryCount;
public:
    MoodTracker();
    void addEntry(const MoodEntry& entry);
    void displayEntries() const;
    double calculateAverage() const;
    MoodEntry getHighestMood() const;
    MoodEntry getLowestMood() const;
    int getEntryCount() const;
};

MoodEntry::MoodEntry() {
    date = "Unspecified";
    rating = 3;
    note = "No note";
}

MoodEntry::MoodEntry(string date, int rating, string note) {
    setDate(date);
    setRating(rating);
    setNote(note);
}

void MoodEntry::setDate(string date) {
    this->date = date.empty() ? "Unspecified" : date;
}

void MoodEntry::setRating(int rating) {
    this->rating = (rating >= 1 && rating <= 5) ? rating : 3;
}

void MoodEntry::setNote(string note) {
    this->note = note.empty() ? "No note" : note;
}

string MoodEntry::getDate() const { return date; }
int MoodEntry::getRating() const { return rating; }
string MoodEntry::getNote() const { return note; }

string MoodEntry::getMoodLabel() const {
    switch (rating) {
        case 1: return "Very Bad";
        case 2: return "Bad";
        case 3: return "Okay";
        case 4: return "Good";
        case 5: return "Great";
        default: return "Unknown";
    }
}

void MoodEntry::printEntry() const {
    cout << "Date: " << date << endl;
    cout << "Mood Rating: " << rating << endl;
    cout << "Mood: " << getMoodLabel() << endl;
    cout << "Note: " << note << endl;
}

MoodTracker::MoodTracker() {
    entryCount = 0;
}

void MoodTracker::addEntry(const MoodEntry& entry) {
    if (entryCount < 20) {
        entries[entryCount] = entry;
        entryCount++;
        cout << "\nMood entry added!" << endl;
    } else {
        cout << "\nMood tracker is full." << endl;
    }
}

void MoodTracker::displayEntries() const {
    if (entryCount == 0) {
        cout << "\nNo mood entries have been added yet." << endl;
        return;
    }
    cout << "\n========== MOOD ENTRIES ==========" << endl;
    for (int i = 0; i < entryCount; i++) {
        cout << "\nEntry #" << i + 1 << endl;
        entries[i].printEntry();
    }
}

double MoodTracker::calculateAverage() const {
    if (entryCount == 0) return 0.0;
    int total = 0;
    for (int i = 0; i < entryCount; i++)
        total += entries[i].getRating();
    return static_cast<double>(total) / entryCount;
}

MoodEntry MoodTracker::getHighestMood() const {
    if (entryCount == 0) return MoodEntry();
    int highestIndex = 0;
    for (int i = 1; i < entryCount; i++)
        if (entries[i].getRating() > entries[highestIndex].getRating())
            highestIndex = i;
    return entries[highestIndex];
}

MoodEntry MoodTracker::getLowestMood() const {
    if (entryCount == 0) return MoodEntry();
    int lowestIndex = 0;
    for (int i = 1; i < entryCount; i++)
        if (entries[i].getRating() < entries[lowestIndex].getRating())
            lowestIndex = i;
    return entries[lowestIndex];
}

int MoodTracker::getEntryCount() const {
    return entryCount;
}

int main() {
    MoodTracker tracker;
    int choice = 0;

    do {
        cout << "\n=========================" << endl;
        cout << "       MOODMATE" << endl;
        cout << "=========================" << endl;
        cout << "1. Add Mood Entry" << endl;
        cout << "2. View All Entries" << endl;
        cout << "3. View Average Mood" << endl;
        cout << "4. View Highest Mood" << endl;
        cout << "5. View Lowest Mood" << endl;
        cout << "6. Exit" << endl;
        cout << "=========================" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid menu choice." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string date, note;
            int rating;

            cout << "\nEnter date: ";
            getline(cin, date);
            cout << "Enter mood rating (1-5): ";

            if (!(cin >> rating)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid rating." << endl;
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter note: ";
            getline(cin, note);

            MoodEntry today(date, rating, note);
            tracker.addEntry(today);
        }
        else if (choice == 2) {
            tracker.displayEntries();
        }
        else if (choice == 3) {
            if (tracker.getEntryCount() == 0)
                cout << "\nNo entries available." << endl;
            else {
                cout << fixed << setprecision(1);
                cout << "\nAverage Mood: " << tracker.calculateAverage() << endl;
            }
        }
        else if (choice == 4) {
            if (tracker.getEntryCount() == 0)
                cout << "\nNo entries available." << endl;
            else {
                cout << "\n----- Highest Mood -----" << endl;
                MoodEntry highest = tracker.getHighestMood();
                highest.printEntry();
            }
        }
        else if (choice == 5) {
            if (tracker.getEntryCount() == 0)
                cout << "\nNo entries available." << endl;
            else {
                cout << "\n----- Lowest Mood -----" << endl;
                MoodEntry lowest = tracker.getLowestMood();
                lowest.printEntry();
            }
        }
        else if (choice == 6) {
            cout << "\nThank you for using MoodMate!" << endl;
        }
        else {
            cout << "\nInvalid menu choice." << endl;
        }
    } while (choice != 6);

    return 0;
}
