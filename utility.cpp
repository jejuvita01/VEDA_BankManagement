#include <string>
#include <ctime>

using namespace std;

#include "utility.h"

string num_to_string_with_comma(int num) {
    string ret = "";
    int cnt = 0;
    while (num) {
        if (cnt == 3) {
            cnt = 0;
            ret = "," + ret;
        }
        ret = (char)((num % 10) + '0') + ret;
        cnt++;
        num /= 10;
    }
    return ret;
}

string make_time_string(time_t now) {
    tm* p_time_info;
    p_time_info = localtime(&now);
    int year = p_time_info->tm_year + 1900;
    int month = p_time_info->tm_mon + 1;
    int day = p_time_info->tm_mday;
    string ret = "";
    ret += to_string(year) + "년 " + to_string(month) + "월 " +to_string(day) + "일";
    return ret;
}
