#include "game_of_life.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
/*
 Game of Life.cpp : Defines the entry point for the console application.
 使用一个2维数组来实现其规则
 在这个数组中，每个存储位子都能容纳一个LIFE元胞。
 世代(gennerations)用于标记时间的流逝。每个世代都会LIFE社会带来生与死。
 
 每个格子的生死遵循下面的原则：

　　1． 如果一个细胞周围有3个细胞为生（一个细胞周围共有8个细胞），
	则该细胞为生（即该细胞若原先为死，则转为生，若原先为生，则保持不变） 。

　　2． 如果一个细胞周围有2个细胞为生，则该细胞的生死状态保持不变；

　　3． 在其它情况下，该细胞为死（即该细胞若原先为生，则转为死，若原先为死，则保持不变。
	设定图像中每个像素的初始状态后依据上述的游戏规则演绎生命的变化，由于初始状态和迭代次数不同，将会得到令人叹服的优美图案）。
 */

static CellSpace cell_space;

/*
 * 功能：设置该坐标的细胞为存活状态
 * 参数：x, y
 * 返回值：成功返回0，失败返回-1
 */
static int set_cell_alive(int x, int y)
{
	if (x > cell_space.x_size || x < 0 || y > cell_space.y_size || y < 0)
	{
		printf("设置存活的细胞不在该细胞空间中：细胞[%d, %d]越界！\n", x, y);
		return -1;
	}
	
	cell_space.cell[x][y].status = ALIVE;
	cell_space.cell[x][y].pixel = 'o';
}

/*
 * 功能：设置该坐标的细胞为死亡状态
 * 参数：x, y
 * 返回值：成功返回0，失败返回-1
 */
static int set_cell_dead(int x, int y)
{
	if (x > cell_space.x_size || x < 0 || y > cell_space.y_size || y < 0)
        {
                printf("设置死亡的细胞不在该细胞空间中：细胞[%d, %d]越界！\n", x, y);
                return -1;
        }

	cell_space.cell[x][y].status = DEAD;
	cell_space.cell[x][y].pixel = ' ';
}


/*
 * 功能：初始化整个细胞生活空间，默认都为死亡状态，细胞数量为INIT_X_LENGTH * INIT_Y_LENGTH
 * 参数：无
 * 返回值：成功返回0，失败返回-1
 */
int init_cell_space()
{
	cell_space.x_size = INIT_X_LENGTH;
	cell_space.y_size = INIT_Y_LENGTH;
	cell_space.cell	= (Cell **)calloc(cell_space.x_size, sizeof(Cell)); //分配x空间(指针数组)
	if (cell_space.cell == NULL)
	{
		return -1;
	}
	int x = 0;
	for (; x < cell_space.x_size; x++) 
	{
		//为每一个指针数组中的指针分配y_size个Cell大小
		*(cell_space.cell + x) = (Cell *)calloc(cell_space.y_size, sizeof(Cell));
		if (*(cell_space.cell + x) == NULL)
		{
			return -1;
		}
	}
	
	//初始化所有的细胞都为死亡状态
	int y = 0;
	for (x = 0; x < cell_space.x_size; x++)
	{
		for (y = 0; y < cell_space.y_size; y++)
		{
			set_cell_dead(x, y);					
		}
	}
	
	cell_space.total_num = cell_space.x_size * cell_space.y_size;
	cell_space.alive_num = 0;
	cell_space.dead_num = cell_space.total_num;

	return 0;
}

/*
 * 功能：判断某个细胞周围有多少个存活的细胞
 * 参数：x，y为这个细胞的坐标
 * 返回值：成功返回存活的细胞数目，不包含该坐标的细胞的状态
	   出错返回-1
 */
static int alive_nums_circling_cell(int x, int y)
{
	if (x < 0 || y < 0 || x > cell_space.x_size || y > cell_space.y_size)
	{
		printf("无法判断该细胞周围存活的细胞数目，细胞[%d, %d]越界！\n", x, y);
		return -1;
	}

	int count = 0;  //存活细胞总数
	if (x - 1 > 0 && y - 1 > 0) //左上角细胞空间存在
	{
		if (cell_space.cell[x-1][y-1].status == ALIVE)
		{
			count++;
		}
	}
	if (y - 1 > 0)  //正上方细胞空间存在
	{
		if (cell_space.cell[x][y-1].status == ALIVE)
		{
			count++;
		}
	}	
	if (x + 1 < cell_space.x_size && y - 1 > 0) //右上方细胞存在
	{
		if (cell_space.cell[x+1][y-1].status == ALIVE)
		{
			count++;
		}
	}	
	if (x - 1 > 0)	//正左方细胞存在
	{
		if (cell_space.cell[x-1][y].status == ALIVE)
		{
			count++;
		}
	}
	if (x + 1 < cell_space.x_size) //正右方细胞空间存在
	{
		if (cell_space.cell[x+1][y].status == ALIVE)
		{
			count++;
		}
	}
	if (x - 1 > 0 && y + 1 < cell_space.y_size) //左下方细胞存在
	{
		if (cell_space.cell[x-1][y+1].status == ALIVE)
		{
			count++;
		}
	}
	if (y + 1 < cell_space.y_size) //正下方细胞存在
	{
		if (cell_space.cell[x][y+1].status == ALIVE)
		{
			count++;
		}
	}
	if (x + 1 < cell_space.x_size && y + 1 < cell_space.y_size)	
	{
		if (cell_space.cell[x+1][y+1].status == ALIVE)
		{
			count++;
		}
	}
	
	return count;
}

/*
 * 功能：开始运行一次判定周期
 * 参数：无
 * 返回值：成功返回0，失败返回-1
 */
int start_a_period()
{
	/*
	 * 1、一个细胞当前状态为死：如果周围有三个细胞存活，则该细胞转为存活状态
	 *			    否则依旧为死亡状态
	 * 2、一个细胞当前状态为活：如果周围有两个细胞，则依旧存活
	 *			    否则转为死亡状态
	 *
         * 3、注意当全部遍历完一遍之后再更新全部的细胞状态
	 */						
	//定义两个坐标数组，确定这个周期将要死亡或者生存的细胞，占用了大量的内存，以后优化！
	Point survival_cell[INIT_X_LENGTH * INIT_Y_LENGTH];
	memset(survival_cell, -1,  sizeof(Point) * INIT_X_LENGTH * INIT_Y_LENGTH);
	Point dying_cell[INIT_X_LENGTH * INIT_Y_LENGTH];
	memset(dying_cell, -1, sizeof(Point) * INIT_X_LENGTH * INIT_Y_LENGTH);
	int s = 0, d = 0; //遍历上面两个数组用
	
	//判断这个周期将要死亡或者生存的细胞位置，保存到上面的两个数组中
	int x = 0, y = 0;
	for (; x < cell_space.x_size; x++) 
	{
		for (y = 0; y < cell_space.y_size; y++)
		{
			int alive_nums = alive_nums_circling_cell(x, y);
			
			//如果当前细胞为存活状态
			if (cell_space.cell[x][y].status == ALIVE)
			{
				if (alive_nums != 2 && alive_nums != 3)
				{
					dying_cell[d].x = x;
					dying_cell[d].y = y;
					d++;
				}
			}
			//如果当前细胞为死亡状态
			if (cell_space.cell[x][y].status == DEAD)
			{
				if (alive_nums == 3)
				{
					survival_cell[s].x = x;
					survival_cell[s].y = y;
					s++;
				}
			}
		}
	}

	//对要处理的细胞进行生存活死亡操作
	for (x = 0; x < s; x++)
	{
		set_cell_alive(survival_cell[x].x, survival_cell[x].y);
	}	
	for (x = 0; x < d; x++)
	{
		set_cell_dead(dying_cell[x].x, dying_cell[x].y);
	}

	//计算当前细胞空间的状态：存活的细胞数量，死亡的细胞数量
	cell_space.alive_num = 0;
	cell_space.dead_num = 0;
	for (x = 0; x < cell_space.x_size; x++)
	{
		for (y = 0; y < cell_space.y_size; y++)
		{
			if(cell_space.cell[x][y].status == ALIVE)
			{
				cell_space.alive_num++;			
			}
			else
			{
				cell_space.dead_num++;
			}		
		}
	}
	if (cell_space.alive_num + cell_space.dead_num != cell_space.total_num)
	{
		printf("细胞空间出现次元震，异常！\n");
		return -1;
	}

	return 0;
}

/*
 * 功能：将整个细胞空间的情况打印出来，如果细胞为死亡状态则打印" "，如果细胞为存活状态
 *       打印"*"
 * 参数：无
 * 返回值：成功返回0，失败返回-1
 */
int time = 0;
int show_cell_space()
{
	system("clear");
	printf("生命周期 %d：\n", time++);
	
	printf("cell_space.y_size: %d, x_size:%d\n", cell_space.y_size, cell_space.x_size);
	printf("total:%d, alive:%d, dead:%d\n", cell_space.total_num, cell_space.alive_num, cell_space.dead_num);
	int i = 0;
	for (; i < 100; i++)
	{
		printf("o");
	}
	printf("\n");
	int x = 0, y = 0;
	for (; y < cell_space.y_size; y++)
	{
		for (x = 0; x < cell_space.x_size; x++)
		{
			//printf("[%d, %d]: ", x, y);
			printf("%c", cell_space.cell[x][y].pixel);
		}
		printf("\n");
	}
	return 0;
}


/*
 * 功能：设置初始的存活细胞，将以这些细胞进行生命开始【测试函数】
 * 参数：无
 * 返回值：成功返回0，失败返回-1
 */
int set_init_alive_cell()
{
	/*
	set_cell_alive(49, 20);
	set_cell_alive(49, 21);
	set_cell_alive(50, 19);
	set_cell_alive(50, 21);
	set_cell_alive(51, 19);	
	cell_space.alive_num = 5;
	cell_space.dead_num = 9995;
	*/

	/*
	 * 滑翔者
 	 */
	//             列  行
	/*
	set_cell_alive(49, 50);
	set_cell_alive(50, 51);
	set_cell_alive(51, 49);
	set_cell_alive(51, 50);
	set_cell_alive(51, 51);	
	cell_space.alive_num = 5;
	cell_space.dead_num = 9995;
	*/

	/*
	 * 好玩的爆炸
	 */
	int i = 35;
	for (; i < 9 + 35; i++)
	{
		set_cell_alive(i, 50);
	}
	i = 48;
	for (; i < 48 + 10; i++)
	{
		set_cell_alive(i, 50);
	}
	i = 63;
	for (; i < 63 + 3; i++)
	{
		set_cell_alive(i, 50);
	}
	
	/*
	 * 震动子
	 */
	/*
	set_cell_alive(49, 50);
	set_cell_alive(50, 50);
	set_cell_alive(51, 50);
	*/
	return 0;
}


