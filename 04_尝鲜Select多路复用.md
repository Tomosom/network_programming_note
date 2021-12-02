- 问题
    如何增强服务端能力，同时支持多个客户端？
    > 答：select。

- Linux的设计哲学
    <font color=red>一切皆文件！！！</font>

- Linux中的文件是什么？
    - 狭义：
        - 文件系统中物理意义上的文件（逻辑上关联的数据集合）
    - 广义：
        - 设备，管道，内存，。。。
        - Linux管理的一切对象

·理解文件描述符（File Descriptor）
-文件描述符是一个非负整数值，本质是一个句柄一切对用户（程序员）透明的资源标识都可以看作句柄
-用户使用文件描述符（句柄）与内核交互，内核通过文件描述符操作对应资源的数据结构

·一切皆文件的意义
-统一各种设备的操作方式（open， read， write， close）
-如：
.10设备（命令行，显示器）
网络设备（网卡）

Linux文件操作编程模式
```c
int fd = open ("dev", o_RDWR);
if( fd!=-1)
{
char buf[32] ={0};
int len = read(fd, buf, sizeof (buf));
len =write(fd, buf, len);
close (fd);
```

编程实验
以文件方式操作命令行

事件相关函数的分类
-阻塞式函数
函数调用后需要等待某个事件发生后才会返回
-非阻塞式函数
函数调用后能够及时返回（仅标记等待的事件）
事件发生后以回调方式传递

阻塞vs轮询
-轮询指依序询问每一个相关设备是否需要服务的方式
-轮询可用于解决阻塞函数导致程序无法继续执行的问题

神奇的select（）函数
select）用于监视指定的文件描述符是否产生事件可通过轮询的方式检测目标事件（事件产生则标记发生变化）
一根据事件类型做出具体处理（如：读取数据）
int select（int maxfd，fd_set*readset，fd_set*writeset，fd_set*exceptset，const struct timeval*timeout）；

select（）函数的使用步骤

select（）相关数据类型及操作

fdo fd1 fd2 fd3
0110
…………
…
fd set

FD ZERO（ fd set* fdset ）；
//将fd set变的所有位设置为0
FD SET（ int fd， fd set* fdset ）； //在fd set中指定需要监听的fd
FD CLR（ int fd， fd set* fdset ）； //在fd set中剔除fd，不再监听
FD ISSET（ int fd， fd set* fdset ）； //在fd set查看是否包含fd

使用select）进行轮询
编程实验
select（）初体验

·思考
使用select（）函数可以扩展服务端功能吗？
如果可以，具体怎么实现？

