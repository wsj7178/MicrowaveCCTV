#include<stdio.h>
#include<string.h>
#include<wiringPi.h>
#include<time.h>
#include<stdlib.h>

//GPIO 핀
#define NEAR 4

char *itoa(int, int);

void main()
{
  wiringPiSetup();

  pinMode(NEAR, INPUT);

  for(;;)
  {
   if(digitalRead(NEAR)==1) //현재 시간 받아온 후 현재 시간으로 현재시간.jpg 로 사진 촬영
   {
      int month_num, day_num, hour_num;
  		int minute_num, second_num;
      char month[3], day[3], hour[3], minute[3], second[3];
      time_t timer;
      struct tm *t;
      timer = time(NULL);
      t = localtime(&timer);

      month_num = t->tm_mon + 1;
      day_num = t->tm_mday;
      hour_num = t->tm_hour;
      minute_num = t->tm_min;
      second_num = t->tm_sec;

      strcpy(month, itoa(month_num, 10));
      strcpy(day, itoa(day_num, 10));
      strcpy(hour, itoa(hour_num, 10));
      strcpy(minute, itoa(minute_num, 10));
      strcpy(second, itoa(second_num, 10));

      char filename[50], command[50] = "raspistill -o "
      strcpy(filename, month);
      strcat(filename, "-");
      strcat(filename, day);
      strcat(filename, "-");
      strcat(filename, hour);
      strcat(filename, ":");
      strcat(filename, minute);
      strcat(filename, ":");
      strcat(filename, second);
      strcat(filename, ".jpg");
      strcat(command, filename);
      

      system(command);
      printf("successful taken a picture!\nfilename: %s\n\n", filename);
      sleep(5);
    }
    delay(300);
  }
}

//정수를 문자열로 반환하는 함수
char *itoa(int val, int base)
{
  static char buf[32] = {0};
  int i = 30;
  for(; val && i; --i, val /= base)
  {
    buf[i] = "0123456789abcdef"[val % base];
  }
  return &buf[i+1];
}
