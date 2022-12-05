#include "stdio.h"
#include "stdlib.h"
 
typedef struct item
{
	int num;		//页号
	int time;		//等待时间，LRU算法会用到这个属性
}Pro;
 
int pageNum;		//系统分配给作业的主存中的页面数
int memoryNum;		//可用内存页面数
 
void print(Pro *page1);		//打印当前主存中的页面
int  Search(int num1, Pro *memory1);	//在页面集memory1中查找num1，如果找到，返回其在memory1中的下标，否则返回-1
 
int main(void)
{
	int i;
	int curmemory;		//调入内存中的页面个数
	int missNum;		//缺页次数
	float missRate;		//缺页率

 
	Pro *page;			//作业页面集
	Pro *memory;		//内存页面集
 
	printf("输入系统分配给作业的主存中的页面数:");
	scanf("%d", &pageNum);
	printf("输入内存页面数:");
	scanf("%d", &memoryNum);
 
	page = (Pro*)malloc(sizeof(Pro)*pageNum);
	memory = (Pro*)malloc(sizeof(Pro)*memoryNum);
 
	for (i = 0; i<pageNum; i++)
	{
		printf("第 %d 个页面号为:", i);
		scanf("%d", &page[i].num);
		page[i].time = 0;			//等待时间开始默认为0
	}
 
		for (i = 0; i<memoryNum; i++)		//初始化内存中页面
		{
			memory[i].num = -1;				//页面为空用-1表示
			memory[i].time = -1;				//
		}
 
		i = 0;
		curmemory = 0;
 

			missNum = 0;
 
			printf("FIFO页面置换情况:   \n");
			for (i = 0; i<pageNum; i++)
			{
				if (Search(page[i].num, memory)<0)//若在内存中没有找到该页面
				{
					missNum++;
					memory[curmemory].num = page[i].num;
					print(memory);
					curmemory = (curmemory + 1) % memoryNum;   //找出最先进入内存的页面
				}
			}//end for
			missRate = (float)missNum / pageNum;
			printf("缺页次数：%d   缺页率:  %f\n", missNum, missRate);
 

 
 
	return 0;
}
 
 
void print(Pro *memory1)//打印当前的页面
{
	int j;
 
	for (j = 0; j<memoryNum; j++)
		printf("%d ", memory1[j].num);
	printf("\n");
}
 
//在页面集memory1中查找num1，如果找到，返回其在memory1中的下标，否则返回-1
int  Search(int num1, Pro *memory1)
{
	int j;
 
	for (j = 0; j<memoryNum; j++)
	{
		if (num1 == memory1[j].num)
			return j;
	}
	return -1;
}

