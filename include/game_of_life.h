/*
 * author: wwptrdudu <1348351139@qq.com>
 * github: https://github.com/wwptrdudu
 * tg: @wwptrdudu
 */

#ifndef __GAME_OF_LIFE__
#define __GAME_OF_LIFE__

/*
 * 定义显示空间，在这个空间下进行绘图
 * 此空间的数据结构暂时定义为2D空间，即二维数组
 */

#define INIT_X_LENGTH 100
#define INIT_Y_LENGTH 100
#define DEAD          22
#define ALIVE         33


typedef struct {
	int x;
	int y;
}Point;

typedef struct {
	char pixel;    //表示显示的像素，存活状态为“o”，死亡为" "
	int status;    //标志细胞状态
	
	/*
	 * 不知道还是否需要定义周围细胞的状态，待定
	 */
}Cell;

typedef struct {
	Cell **cell;    //二维细胞数组
	int  x_size;    //二维数组中每一行细胞数量
	int  y_size;    //二维数组中每一列细胞数量	
	int  total_num; //整个空间中的细胞数量
	int  alive_num; //整个空间中存活的细胞数量
	int  dead_num;  //整个空间中死亡的细胞数量
}CellSpace;

extern int init_cell_space(); 

extern int start_a_period();

extern int show_cell_space();

extern int set_init_alive_cell();

#endif
