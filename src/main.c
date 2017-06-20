#include "game_of_life.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("Welcome to the GAME-OF-LIFE!\n");	
	
	int ret = 0;
	//初始化细胞生存空间
	ret = init_cell_space();
	if (ret < 0)
	{
		printf("初始化细胞空间失败！\n");
		return -1;
	}

	//设置初始化存活的细胞
	set_init_alive_cell();
	show_cell_space();
	sleep(3);
	//根据细胞规则进行生命
	while (1)
	{
		//printf("Hello!\n");
		show_cell_space();
		start_a_period();
		sleep(1);				
	}
	return 0;
}
