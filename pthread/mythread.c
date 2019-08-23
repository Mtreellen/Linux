#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

//线程库函数POSIX标准定义的POSIX thread或pthread

/*
 *函数：
 *（1）创建线程：pthread_create
 *（2）获取线程id：pthread_self
 *（3）等待新线程：pthread_join
 *（4）线程终止：不能用exit,它是进程终止，会删掉进程的pcb块，地址空间等所有信息，杀掉了所有线程。
 * 三种方法终止线程：
 * a.从线程函数中return
 * b.调用pthread_cancel终止另一个线程（新线程可以终止主线程，但是不推荐，因为这样新线程就没人管了。
 * ）
 * c.调用pthread_exit终止自己
 */

void* Thread_1(void* arg)
{
	printf("thread_1 is runing, pid:%d, ppid:%d thread_id:%lu\n", \
			getpid(), getppid(), pthread_self());

//	return (void*)23;   //线程终止方式一
//	int ret = pthread_cancel(pthread_self()); //线程终止方式二：pthread_cancel不可以终止自己
//如果thread线程被别的线程调⽤用pthread_cancel异常终掉,value_ptr所指向的单元⾥里存放 的是常数PTHREAD_CANCELED(-1)
	
	
//	pthread_t mid = *((pthread_t*)arg);   //arg-->&pthread_t
//	int ret = pthread_cancel(mid); //线程终止方式二：pthread_cancel可以新线程终止主线程

//	pthread_exit((void*)222); //退出方式三
	while(1)
	{
		printf("hello\n");
	}

	printf("end falied\n");
}

int main()
{
	pthread_t id;
	pthread_t mid;
	int retval = 0;

	int ret = pthread_create(&id, NULL, &Thread_1, &mid);
	if(ret != 0)
	{
		perror("pthread_create");
		return 1;
	}
	
	printf("main thread is runing, pid:%d, ppid:%d threadid:%lu\n", \
			getpid(), getppid(), pthread_self());
	
	sleep(2);
	pthread_cancel(id); //线程终止方式二:主线程终止新线程

	if(pthread_join(id, (void**)&retval) == 0)
	{
		printf("wait success\n");
	}

	//printf("thread_1 return val:%d\n", retval);
	return 0;
}