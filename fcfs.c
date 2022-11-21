//先来先服务
#include <stdlib.h>
#include <stdio.h>

typedef struct{   // 定义一个结构体，里面包含的有一个进程相关的信息
	char name[10];        //进程名称 (输入)
	float arrivetime;     //到达时间 (输入)
	float servicetime;    //服务时间 (输入)
	float starttime;      //开始时间 
	float finishtime;     //结束时间 
	float zztime;        //周转时间=finishtime-arrivetime
	float dqzztime;      //带权周转时间=zztime/servicetime
}pcb;   

//输入进程信息
void input(pcb *p, int N)    //p为pdb数组名， N为pcb数组的元素个数 
{ 
	int i;   
    printf("\n"); 
	printf("请输入进程的名字  到达时间  服务时间:  (例如: 进程1 0 100)\n");
	for(i=0; i<=N-1; i++)    
	{    
		printf("请输入进程%d的信息：", i+1);  // i=0时，输入第1个进程相关信息 
		scanf("%s", &p[i].name);		
		scanf("%f", &p[i].arrivetime);		
		scanf("%f", &p[i].servicetime);
	}    
	
} 
   
//排序: 按照进程的arrivetime（从小到大）对pcb数组中的N个进程进行排序 
void sort(pcb *p, int N)   
{     
	for(int i=0; i < N-1; i++)
	{
		for(int j=i+1; j<N; j++)  
		{
			if(p[i].arrivetime > p[j].arrivetime)   
			{    
				pcb temp;    
				temp=p[i];    
				p[i]=p[j];    
				p[j]=temp;    
			}
		}
	}
} 
 
//运行
void run(pcb *p, int N)     
{
	int k;    
	for(k=0; k<=N-1; k++)    
	{    
		if(k==0) //第1个进程   
		{     
			p[k].starttime = p[k].arrivetime; //第1个进程到达之后即可执行   
			p[k].finishtime = p[k].starttime + p[k].servicetime; 
		}    
		else 
		{    
			p[k].starttime = (p[k-1].finishtime >= p[k].arrivetime)? p[k-1].finishtime: p[k].arrivetime;    
			p[k].finishtime = p[k].starttime + p[k].servicetime;
		}    
	}    
	for(k=0; k<=N-1; k++)    
	{    
		p[k].zztime = p[k].finishtime - p[k].arrivetime;    
		p[k].dqzztime = p[k].zztime / p[k].servicetime;    

     }    
} 
  
//显示
void Print(pcb*p, int N)    
{
	int k;  
	printf("调用先来先服务算法以后进程运行的顺序是: ");
	printf("%s", p[0].name); //首先运行第一个进程p[0] 
	for(k=1; k<N; k++)    
	{
		printf("-->");		
		printf("%s", p[k].name); //输出 -->p[k].name 
	}   
	printf("\n"); 
	printf("具体进程调度信息:\n");
	printf("进程名  到达时间  服务时间  开始时间  结束时间  周转时间  带权周转时间\n");
	for(k=0; k<=N-1; k++)    
	{ 
		printf("%4s", p[k].name);
		printf("%10.3f", p[k].arrivetime);		
		printf("%10.3f", p[k].servicetime);		
		printf("%10.3f", p[k].starttime);		
		printf("%10.3f", p[k].finishtime);		
		printf("%10.3f", p[k].zztime);
		printf("%10.3f\n", p[k].dqzztime);		
     }      
}

//先来先服务算法FCFS
void FCFS(pcb *p,int N)    
{       
	sort(p,N);    
	run(p, N);    
	Print(p, N); 
	int k;
	float Attime = 0; //平均周转时间 
	float AQttime = 0; //平均带权周转时间 
	for(k=0; k<=N-1; k++)    
     {   
		Attime += p[k].zztime;  
		AQttime += p[k].dqzztime;		
     }  
	Attime = Attime / N; 
	AQttime = AQttime / N;
	printf("调用先来先服务算法的平均周转时间为:");
	printf("%.3f\n", Attime);
	printf("调用先来先服务算法的平均带权周转时间为:");
	printf("%.3f\n", AQttime);      
}  

int main( )
{
	pcb a[100]; //a为pcb数组   a[0]~a[N-1]对象第1个进程到第N个进程的信息 
	int N;      //N为进程数目 
	printf("\n");
	printf("\n"); 						
	printf("<<----------!!!@@@先来先服务调度算法@@@!!!---------->>");                           
	printf("\n");						
	printf("输入进程数目:");
	scanf("%d", &N);                            
	input(a, N); //a是pcb数组名，N是实际使用数组元素个数   
	FCFS(a, N); //fcfs模拟调度 
	return 0;	
}
