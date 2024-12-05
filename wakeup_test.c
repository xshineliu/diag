#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>

int main () {
  time_t t;
  struct timespec start, end;
  uint64_t delta_us;
  struct tm *tm;
  int i = 0;
  int last = -1;
  // int delta = -1;
  struct rusage usage;

  clock_gettime (CLOCK_MONOTONIC_RAW, &start);

  t = time (NULL);
  last = (int)t;
  while (i < 600 * 1000) {
      ++i;
      usleep (10 * 1000);
      if (i % 100 == 0) {
          t = time (NULL);
          tm = localtime (&t);
          clock_gettime (CLOCK_MONOTONIC_RAW, &end);
          delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
          memcpy (&start, &end, sizeof (struct timespec));
          getrusage (RUSAGE_SELF, &usage);
          if (delta_us > 1100000) {
              printf ("now: %03d at %02d:%02d:%02d %9lld %9lld *** %lld\n", i / 100, tm->tm_hour, tm->tm_min, tm->tm_sec, usage.ru_nvcsw, usage.ru_nivcsw, delta_us);
          } else {
              printf ("now: %03d at %02d:%02d:%02d %9lld %9lld\n", i / 100, tm->tm_hour, tm->tm_min, tm->tm_sec, usage.ru_nvcsw, usage.ru_nivcsw);
          }
    }
  }
  clock_gettime (CLOCK_MONOTONIC_RAW, &end);
  delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
  printf ("Taken %lld\n", delta_us);
  return 0;
}
