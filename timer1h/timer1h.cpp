#include <iostream>
#include <windows.h>
#include <ctime>

SYSTEMTIME localTime; // Struct to hold local time
unsigned int DELAY = 0;
bool debug = false;
// Wide string literals for sound file paths
LPCWSTR night_sound = L"nighttime.wav";
LPCWSTR day_sound = L"daytime.wav";
LPCWSTR quarter_sound = L"quarter.wav";

void PlaySoundOnTime() {
    // Check if it's the top of the hour
    if (localTime.wMinute == 0) {
        if ((localTime.wHour >= 18 && localTime.wHour <= 24) || (localTime.wHour >= 0 && localTime.wHour <= 5)) {
            PlaySound(night_sound, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
        }
        else if (localTime.wHour >= 6 && localTime.wHour <= 17) {
            PlaySound(day_sound, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
        }
    }
    // Check if it's a quarter-hour mark
    else if (localTime.wMinute % 15 == 0) {
        PlaySound(quarter_sound, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
    }
}

int main() {
    // Uncomment this line to hide the console window if desired
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    PlaySound(quarter_sound, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
    if (debug == true) {
        std::wcout << L"Current time: " << localTime.wHour << L":" << localTime.wMinute << L"\n";
        std::wcout << L"Next delay: " << DELAY << L" ms\n";
    }
    while (true) {
        // Fetch current time
        GetLocalTime(&localTime);

        // Play the appropriate sound based on the current time
        PlaySoundOnTime();

        // Calculate the delay until the next quarter-hour
        DELAY = ((15 - (localTime.wMinute % 15)) * 60 - localTime.wSecond) * 1000;
        Sleep(DELAY); // Sleep until the next event
    }

    return 0;
}
