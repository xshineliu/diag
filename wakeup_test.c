#include <unistd.h>

#include <time.h>

#include <stdio.h>

#include <stdint.h>

int main() {

  time_t t;
  struct timespec start, end;
  uint64_t delta_us;
  struct tm * tm;
  int i = 0;
  int last = -1;
  int delta = -1;

  clock_gettime(CLOCK_MONOTONIC_RAW, & start);

  t = time(NULL);
  last = (int) t;
  while (i < 6000) {
    ++i;
    usleep(100000);
    if (i % 10 == 0) {
      t = time(NULL);
      tm = localtime( & t);
      delta = (int) t - last;
      last = (int) t;
      if (delta != 1) {
        printf("now: %03d at %02d:%02d:%02d *** %d\n", i / 10, tm - > tm_hour, tm - > tm_min, tm - > tm_sec, delta);
      } else {
        printf("now: %03d at %02d:%02d:%02d\n", i / 10, tm - > tm_hour, tm - > tm_min, tm - > tm_sec);
      }
    }
  }
  clock_gettime(CLOCK_MONOTONIC_RAW, & end);
  delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
  printf("Taken %lld\n", delta_us);
  return 0;
}
