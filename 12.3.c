#include<stdio.h>
#define NUMRECS 5
struct PayRecord                                                /*构造一个全局结构类型*/
{
	int id;
	char name[20];
	double rate;
};

int main()
{
	int i;
	struct PayRecord employee[NUMRECS]={{32479,"Abrams,B.",6.72},
	                                    {33623,"Bohm,P.",7.54},
	                                    {34145,"Donaldson,S.",5.56},
	                                    {35987,"Ernst,T.",5.43},
	                                    {36203,"Gwodz,K.",8.72}
	                                   };
	for(i=0;i<NUMRECS;i++)
		printf("%d %-20s %4.2f\n",
		employee[i].id,employee[i].name,employee[i].rate);

	return 0;
}