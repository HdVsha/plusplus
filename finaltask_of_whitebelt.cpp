#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <exception>
#include <sstream>
#include <stdexcept>
 
using namespace std;
 
 
class Date {
public:
    Date() { //делаем конструктор с переменными по умолчанию
        year = 0;
        month = 0;
        day = 0;
    };
 
    explicit Date(const int& tmp_year, const int& tmp_month, const int& tmp_day) {// делаем явным,
        // чтобы избежать неявного преобразования типов данных
        year = tmp_year;
        if (tmp_month < 1 || tmp_month > 12) {// контролируем корректность ввода данных
            string string_error;
            string_error = "Month value is invalid: " + to_string(tmp_month); // приводим переменную к типу "строка"
            throw runtime_error(string_error);
        }
        else if (tmp_day < 1 || tmp_day > 31) {
            string string_error;
            string_error = "Day value is invalid: " + to_string(tmp_day);
            throw runtime_error(string_error);
        }
        else {
            month = tmp_month;
            day = tmp_day;
        }
    };
    int GetYear() const { return year; } // делаем методы для возвращения приватных переменных
    int GetMonth() const { return month; }
    int GetDay() const { return day; }
 
private:
    int year;
    int month;
    int day;
};
bool operator < (const Date& lhs, const Date& rhs) { // стандартная функция сравнения
    if ((lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth() == rhs.GetMonth())) {
        return lhs.GetDay() < rhs.GetDay();
    }
    else if ((lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth() != rhs.GetMonth())) {
        return lhs.GetMonth() < rhs.GetMonth();
    }
    else {
        return lhs.GetYear() < rhs.GetYear();
    }
}
ostream& operator << (ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() << '-' // заполняем по дэфу 0000 и разделяем "-"
           << setw(2) << setfill('0') << date.GetMonth() << '-'
           << setw(2) << setfill('0') << date.GetDay();
    return stream;
}
void EnsureNextSymbolAndSkip(stringstream& stream, const string& data_str) {//stringstream- тип данных(потоковая)
    if (stream.peek() != '-') {
        stringstream ss;
        ss << "Wrong date format: " + data_str;
        throw runtime_error(ss.str());
    }
    stream.ignore(1);
}
    istream& operator >> (istream& stream, Date& date) {
        int year = 10000;
        int month = 10000;
        int day = 10000;
 
        string data_str;
        string end_error;
        if (stream >> data_str) {
            stringstream d(data_str);
            d >> year;
            EnsureNextSymbolAndSkip(d, data_str);
            d >> month;
            EnsureNextSymbolAndSkip(d, data_str);
            d >> day;
            d >> end_error;
 
            if (year > -1 && year < 10000 && month < 10000 && day < 10000 && end_error.empty()) {
                date = Date(year, month, day);
                return stream;
            }
            else {
 
                stringstream string_error;
                string_error << "Wrong date format: " + data_str;
                throw runtime_error(string_error.str());
            }
        }
        else {
 
            stringstream string_error;
            string_error << "Wrong date format: " + data_str;
            throw runtime_error(string_error.str());
        }
 
    }
 
    class Database {
    public:
 
        void AddEvent(const Date& date, const string& event) {
            DB[date].insert(event);
        }
 
        bool DeleteEvent(const Date& date, const string& event) {
            if (DB.count(date)) {
                if (DB[date].count(event)) {
                    DB[date].erase(event);
                    return true;
                }
            }
            return false;
        }
 
        int  DeleteDate(const Date& date) {
            if (DB.count(date)) {
                int c = DB[date].size();
                DB.erase(date);
                return c;
            }
            return 0;
        }
        void Find(const Date& date) const {
            if (DB.count(date)) {
                for (auto &find : DB.at(date)) {
                    cout << find << endl;
                }
            }
        }
        void Print() const {
            for (auto& p : DB) {
                for (auto& s : p.second) {
                    cout << p.first << ' ' << s << endl;
                }
            }
        }
 
    private:
        map<Date, set<string>> DB;
    };
 
    void ParseCommands(const string& command, Database& db) {
        stringstream stream(command);
        string com;
        Date date;
        string event;
 
        if (stream >> com) {
            if (com == "Add") {
                if (stream >> date) {
                    if (stream >> event) {
                        db.AddEvent(date, event);
                    }
                    else {
                        stringstream ss;
                        ss << "Wrong date format: " << date;
                        throw runtime_error(ss.str());
                    }
                }
            }
            else if (com == "Find") {
                if (stream >> date) {
                    db.Find(date);
                }
            }
            else if (com == "Print") {
                db.Print();
            }
            else if (com == "Del") {
                if (stream >> date) {
                    if (stream >> event) {
                        if (db.DeleteEvent(date, event)) {
 
                            cout << "Deleted successfully" << endl;
                        }
                        else {
 
                            cout << "Event not found" << endl;
                        }
                    }
                    else {
 
                        cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                    }
                }
            }
            else {
 
                stringstream ss;
                ss << "Unknown command: " << com;
                throw runtime_error(ss.str());
            }
        }
    }
 
int main() {
 
    Database db;
    string command;
 
    try {
        while (getline(cin, command)) {
 
            ParseCommands(command, db);
        }
    }
 
    catch (exception& ex) {
        cout << ex.what();
    }
 
    return 0;
 
}
