#include <stdio.h>
#include <time.h>
#include <string.h>

void getTime(char *buffer, size_t size) {
    time_t t;
    time(&t);
    strftime(buffer, size, "%H:%M:%S", localtime(&t));
}

void getDate(char *buffer, size_t size) {
    time_t t;
    time(&t);
    strftime(buffer, size, "%Y-%m-%d", localtime(&t));
}

int getRandomBetween(int min, int max) {return (rand() % max) + min;}