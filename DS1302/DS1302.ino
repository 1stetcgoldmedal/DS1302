/** GetDateTime.cpp
 *
 * Example of getting the date and time from the RTC.
 *
 * @version 1.0.1
 * @author Rafa Couto <caligari@treboada.net>
 * @license GNU Affero General Public License v3.0
 * @see https://github.com/Treboada/Ds1302
 *
 */
#include <Arduino.h>
#include <Ds1302.h>

const uint8_t PIN_RESET = 5;//리셋 핀
const uint8_t PIN_CLOCK = 7;//클록 핀
const uint8_t PIN_DAT = 6;//데이터 핀
Ds1302 rtc(PIN_RESET, PIN_CLOCK, PIN_DAT);


const static char* WeekDays[] =
{
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun"
};


void setup()
{
    Serial.begin(9600);
    rtc.init();

    
    //rtc.halt();//시간 설정 필요 시 주석 해제
    if (rtc.isHalted())
    {
        Serial.println("RTC is halted. Setting time...");
        
        Ds1302::DateTime dt = {//시간 설정 시 설정될 시간 값
            .year = 24,
            .month = Ds1302::MONTH_JUN,
            .day = 20,
            .hour = 17,
            .minute = 11,
            .second = 30,
            .dow = Ds1302::DOW_THU
        };

        rtc.setDateTime(&dt);
    }
}


void loop()
{
    // get the current time
    Ds1302::DateTime now;
    rtc.getDateTime(&now);

    static uint8_t last_second = 0;
    if (last_second != now.second)
    {
        last_second = now.second;

        Serial.print("20");
        Serial.print(now.year);    // 00-99
        Serial.print('-');
        if (now.month < 10) Serial.print('0');
        Serial.print(now.month);   // 01-12
        Serial.print('-');
        if (now.day < 10) Serial.print('0');
        Serial.print(now.day);     // 01-31
        Serial.print(' ');
        Serial.print(WeekDays[now.dow - 1]); // 1-7
        Serial.print(' ');
        if (now.hour < 10) Serial.print('0');
        Serial.print(now.hour);    // 00-23
        Serial.print(':');
        if (now.minute < 10) Serial.print('0');
        Serial.print(now.minute);  // 00-59
        Serial.print(':');
        if (now.second < 10) Serial.print('0');
        Serial.print(now.second);  // 00-59
        Serial.println();
    }

    delay(100);
}