# 一、游戏简介 
### 如果一个生命，其周围的同类生命太少，会因为得不到帮助而死亡；如果太多，则会因为得不到足够的生命资源而死亡。只需要这非常简单的规则，以及时间和空间，就能孕育出可以媲美真正生命的复杂结构。

# 二、游戏规则      
### 游戏规则如下：该游戏有一张很大的网格棋盘，但只有黑色的棋子，棋子放在格子里代表着“生命”，没有棋子的格子代表着死亡，在每个回合结束之后，每个格子都根据周围8个格子的状态获得或者失去生命，而全部规则只有四条：
### 1.生命害怕孤独：如果一个生命周围的生命少于2个，它就在回合结束时死亡。
### 2.生命讨厌拥挤：如果一个生命周围的生命超过3个，它也在回合结束时死亡。
### 3.生命也会繁殖：如果一个死格子周围有3个生命，它就在回合结束时获得生命。
### 4.生命保持不变：如果一个生命周围有2个或者3个生命，它就在回合结束时保持原样。

### 这是一个想当独特的无人游戏，玩家只需要在网格上布好初始图像，就可以观察生命演绎的过程。它在大部分时间都不需要任何操作，只需要静静的观看而已，就像小时候观看蚂蚁一样。

# 三、编译源码
### 首先进入工程目录，执行下面的编译命令：
### gcc -o obj/life\_of\_game.o -Iinclude -c src/life\_of\_game.c
### gcc -o bin/life\_of\_game -Iinclude obj/life\_of\_game.o src/main.c

# 四、运行游戏
### 在工程目录下执行：
### bin/life\_of\_game

# 五、效果展示（理想图）
![game_of_life_1](https://github.com/WhisperHear/Game-Of-Life/blob/master/photos/game_of_life_1.gif )

![game_of_life_1](https://github.com/WhisperHear/Game-Of-Life/blob/master/photos/game_of_life_2.gif )


# Contact me 
#### If you have any questions, please contact me.
#### QQ：1348351139
#### e-mail: 1348351139@qq.com
