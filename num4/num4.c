#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#define BUFSIZE 512 /* 읽혀질 덩어리의 크기 */

char practice_1[BUFSIZE] = "Hello world! input my text! i am yongjjang!";
char practice_2[BUFSIZE] = "Early bird catches the worm";
char practice_3[BUFSIZE] = "He is truly happy who makes others happy";

int main(){
    time_t start_time, end_time;
    char a[20];
    char buffer[BUFSIZE]; // 타자수 확인 버퍼
    char buf1[BUFSIZE]; // 파일 입력 버퍼
    char buf2[BUFSIZE]; // 파일 입력 버퍼
    char buf3[BUFSIZE]; // 파일 입력 버퍼
    int wrong_count=0;
    int n;
    int filedes;
    int fd;
    int sum = 0;
    double total = 0;

    //초기화
    printf("타자 연습 프로그램입니다. 시작(Enter)\n");
    printf("<<<<<<<<<<<Press Enter>>>>>>>>>>>>");
    gets(a);
    start_time = time(NULL);

    // 주어진 문자 입력 
    fprintf(stderr, "%s\n", practice_1);
    gets(buf1);

    fprintf(stderr,"%s\n", practice_2);
    gets(buf2);

    fprintf(stderr, "%s\n", practice_3);
    gets(buf3);
    end_time = time(NULL);


    // 타이핑까지 걸린 시간
    total = difftime(end_time, start_time);

    // 입력한 타이핑 전체 글자수
    sum = strlen(buf1) + strlen(buf2) + strlen(buf3);
    sum /= total/60; 

    // 잘못 입력한거 체크
    for(int i = 0; i < strlen(practice_1); i++) if(buf1[i] != practice_1[i]) wrong_count++;
    for(int i = 0; i < strlen(practice_2); i++) if(buf2[i] != practice_2[i]) wrong_count++;
    for(int i = 0; i < strlen(practice_3); i++) if(buf3[i] != practice_3[i]) wrong_count++;
    

    printf("잘못 타이핑한 횟수: %d\n",wrong_count); 
    printf("평균 분당 타자수: %ld\n", sum);
    printf("총 걸린시간: %f\n", total);

    exit(0);

    return 0;
}
