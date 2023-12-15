#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 2

pthread_t threads[NUM_THREADS];
sem_t sem1, sem2;

void *print_name(void *arg) {
	char *name = (char *)arg;
	while (1) {
		usleep(500000);
		sem_wait(&sem1);  // 等待信号量sem1
		printf("%s\n", name);
		sem_post(&sem2);  // 发送信号量sem2
	}
	pthread_exit(NULL);
}

void *print_id(void *arg) {
	char *id = (char *)arg;
	while (1) {
		usleep(500000);
		sem_wait(&sem2);  // 等待信号量sem2
		printf("%s\n", id);
		sem_post(&sem1);  // 发送信号量sem1
	}
	pthread_exit(NULL);
}

int main() {
	int rc;
	void *status;
	char *name = "moweida";  // 修改为您的姓名
	char *id = "202008364152";  // 修改为您的学号

	// 初始化信号量和互斥量
	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 0);

	// 创建线程
	rc = pthread_create(&threads[0], NULL, print_name, (void *)name);
	if (rc) {
		printf("无法创建线程1。错误代码：%d\n", rc);
		exit(-1);
	}

	rc = pthread_create(&threads[1], NULL, print_id, (void *)id);
	if (rc) {
		printf("无法创建线程2。错误代码：%d\n", rc);
		exit(-1);
	}

	// 等待线程完成
	for (int i = 0; i < NUM_THREADS; i++) {
		rc = pthread_join(threads[i], &status);
		if (rc) {
			printf("错误：无法加入线程%d，错误代码：%d\n", i, rc);
			exit(-1);
		}
	}

	// 销毁信号量和互斥量
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	pthread_exit(NULL);
}




