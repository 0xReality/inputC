#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>

#define SECONDS_PER_MINUTE 60.0

int main() {
    const char *dev = "/dev/input/event3"; // event 3 for keyboard event 5 for mouse
    int fd = open(dev, O_RDONLY);
    if (fd == -1) {
        perror("Error opening device");
        return 1;
    }

    FILE *file = fopen("user_writing_data.txt", "a");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    struct input_event ev;
    struct timeval press_time, release_time;
    int key_code = -1;
    int key_pressed = 0; // 0: No key pressed, 1: Key press event captured

    while (1) {
        read(fd, &ev, sizeof(struct input_event));
        if (ev.type == EV_KEY) {
            if (ev.value == 1) { // Key press event
                gettimeofday(&press_time, NULL);
                key_code = ev.code;
                key_pressed = 1;
            } else if (ev.value == 0 && key_pressed && ev.code == key_code) { // Key release event for the same key
                gettimeofday(&release_time, NULL);
                double dwell_time = (release_time.tv_sec - press_time.tv_sec) +
                                    (release_time.tv_usec - press_time.tv_usec) / 1e6;
                time_t currentTime;
                time(&currentTime);
                struct tm *timeInfo = localtime(&currentTime);

                fprintf(file, "%02d:%02d:%02d %d %.6f\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, key_code, dwell_time);
                fflush(file); // Flush the file to ensure the data is written immediately

                key_pressed = 0;
            }
        }
    }

    fclose(file);
    close(fd);
    return 0;
}
