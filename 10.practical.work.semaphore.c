
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>


#define BUFFER_SIZE 10
typedef struct {
   char type; // 0=fried chicken, 1=French fries
   int amount; // pieces or weight
   char unit; // 0=piece, 1=gram
} item;
item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
sem_t se;

void produce(item *i) {
   while ((first + 1) % BUFFER_SIZE == last) {
         // do nothing -- no free buffer item
   }
	sem_wait(&se);
   	memcpy(&buffer[first], i,sizeof(item));
 	first = (first + 1) % BUFFER_SIZE;
	sem_post(&se);
}

item *consume() {
    item *i = malloc(sizeof(item));
    while (first == last) {
         // do nothing -- nothing to consume
    } 
	sem_wait(&se);
    	memcpy(i, &buffer[last], sizeof(item));
   	last = (last + 1) % BUFFER_SIZE;
    	return i;
	sem_post(&se);
}

void first_last() {
	printf("First = %d  Last = %d\n",first,last);
}
void *produce_thread(void *param){
	item i1;
	item i2;
	item i3;
	i1.type = '1';
	i1.amount = 9;
	i1.unit ='0';
	i2.type = '1';
	i2.amount = 6;
	i2.unit ='1';
	printf("The item 1 is :\n type:%c\n amount:%d\n unit:%c\n",i1.type,i1.amount,i1.unit);
	produce(&i1);
	first_last();
	

	printf("The item 2 is :\n type:%c\n amount:%d\n unit:%c\n",i2.type,i2.amount,i2.unit);
	produce(&i2);
	first_last();

	printf("The item 3 is :\n type:%c\n amount:%d\n unit:%c\n",i3.type,i3.amount,i3.unit);
	produce(&i3);
	first_last();
}
void *consume_thread(void *param) {
	item *consumed= consume();
   	printf("\n-First consuming:\n type: %c\n amount: %d\n unit: %c\n",consumed->type, consumed->amount, consumed->unit);
	
	first_last();
	printf("\n-Second consuming:\n type: %c\n amount: %d\n unit: %c\n",consumed->type, consumed->amount, consumed->unit);
	
	first_last();
}

int main() {
	sem_init(&se, 0, 1);
	pthread_t tid_1, tid_2;
	pthread_create(
		&tid_1,
		NULL,
		produce_thread,
		NULL);

	pthread_join(tid_1, NULL);

	pthread_create(
		&tid_2,
		NULL,
		consume_thread,
		NULL);

	pthread_join(tid_2, NULL);
	sem_destroy(&se);
}	
