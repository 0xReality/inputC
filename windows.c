#include <stdio.h>
#include <Windows.h>
#include <time.h>

#define SECONDS_PER_MINUTE 60.0

int main() {
    char filename[100];
    time_t currentTime;
    struct tm *timeInfo;
    FILE *file;


    // Get the current time
    time(&currentTime);
    timeInfo = localtime(&currentTime);

    // Format the date and time into a string
    snprintf(filename, sizeof(filename), "user_writing_data_%02d-%02d-%02d_%02d-%02d-%02d.txt",
             timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday,
             timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);

    // Open the file with the dynamic name
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    FILETIME press_time, release_time;
    int key_code = -1;
    int key_pressed = 0; // 0: No key pressed, 1: Key press event captured

    while (1) {
        Sleep(100); // Add a small delay of 100 milliseconds to reduce the frequency of checking for key presses

        for (int ch = 0; ch < 256; ch++) {
            if (GetAsyncKeyState(ch) & 0x8000) { // Check if the key is pressed
                if (key_pressed) {
                    GetSystemTimeAsFileTime(&release_time);
                    ULARGE_INTEGER press_time_ularge, release_time_ularge;
                    press_time_ularge.LowPart = press_time.dwLowDateTime;
                    press_time_ularge.HighPart = press_time.dwHighDateTime;
                    release_time_ularge.LowPart = release_time.dwLowDateTime;
                    release_time_ularge.HighPart = release_time.dwHighDateTime;

                    double dwell_time = (release_time_ularge.QuadPart - press_time_ularge.QuadPart) / 1e7;
                    time(&currentTime);
                    timeInfo = localtime(&currentTime);
                    fprintf(file, "%02d:%02d:%02d %d %.6f\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, ch, dwell_time);
                    fflush(file);

                    key_pressed = 0;
                }

                GetSystemTimeAsFileTime(&press_time);
                key_code = ch;
                key_pressed = 1;
            }
        }
    }

    fclose(file);
    return 0;
}
