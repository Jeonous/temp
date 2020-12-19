#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct word {
	char kor[32];
	char eng[16];
	struct word *next;
};
typedef struct word ELEMENT;
typedef ELEMENT* LINK;

int compare_word(const void* p, const void* q) {
	return strcmp( (*(LINK*)p)->eng, (*(LINK*)q)->eng );
}

LINK word_to_list(FILE *ptr) {
	int size = 0;
	int ch;
	while ((ch = getc(ptr)) != EOF){
		if (ch == ' '){
			++size;
		}
	}
	
	fseek(ptr, 0, SEEK_END);
	LINK head[size];
	fseek(ptr, 0, SEEK_SET);
	for (int i = 0; i < size; ++i) {
		head[i] = malloc(sizeof(ELEMENT));
	}
    	for (int i = 0; i < size; ++i) {
        	int j;
        	for (j =  0; (ch = getc(ptr)) != 32; ++j) {
            		head[i]->eng[j] = ch;
        	}

        	head[i]->eng[j] = '\0';
        	head[i]->kor[0] = ' ';
        	for (j = 0; ((ch = getc(ptr)) != '\n'); ++j) {
            		head[i]->kor[j] = ch;
            		if (ch == EOF) {
                		j++;
                		break;
            		}
        	}
        	head[i]->kor[j] = '\0';
    	}

    	qsort(head, size, sizeof(LINK), compare_word);

    	for (int i = 0; i < size; ++i) {
        	if(i == size-1) {
            		head[i]->next = NULL;
        	}
        	else {
            		head[i]->next = head[i + 1];
        	}
    	}
    	return head[0];
}

void print_list(LINK head, int* score, float* num) {
	char answer[16];
	if (head == NULL)
		return;
	else {
		printf("%s ->  ", head->kor);
		scanf("%s", answer);
		if (!strcmp(".quit", answer)){
			return;
		}
		if (!strcmp(head->eng, answer)){
			printf("correct!\n");
			*score += 1; 
			*num += 1;
		} else {
			printf("incorrect!\n");
			*num += 1;
		}
		print_list(head->next, score, num);
	}
}

int main(void)
{
	FILE* fp;
	LINK h;
	fp = fopen("dic.txt", "r");
	h = word_to_list(fp);
	int select, score = 0, exit = 0;
	float num = 0;

	while(!exit){
		system("clear");
		printf(" >>영어 단어 맞추기 프로그램<<\n");
		printf("1. 영어 단어 맞추기     2. 프로그램 종료\n\n");
		printf("번호를 선택하세요: ");
		scanf("%d", &select);
		if (select == 1){
			select = 0;
			char wait;
			system("clear");
			printf(">> 영어 단어 맞추기 <<\n");
			print_list(h, &score, &num);
			printf("당신의 점수는 %.2f 점입니다.", ((float)score / num)*100);
				getchar();
				getchar();
		} else if (select == 2){
			exit = 1;
			system("clear");
		}
	}
	fclose(fp);
	return 0;
}
