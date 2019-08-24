# netstat命令详解

### 功能:

netstat 用于显示linux中各种网络相关信息。如网络链接, 路由表, 接口状态链接, 多播成员等等。

### 参数:

-a (all)默认不显示LISTEN相关,使用-a显示所有选项
-t (tcp)仅显示tcp相关选项
-u (udp)仅显示udp相关选项
-n (numeric)拒绝显示别名，能显示数字的全部转化成数字(Local Address列用IP:PORT对应的数字表示)
-l (listening)仅列出有在 Listen (监听) 的服務状态
-p (programs)显示建立相关链接的程序名
-r (route)显示路由信息，路由表
-e 显示扩展信息，例如uid等
-s 按各个协议进行统计
-c (continuous)持续列出网络状态,每隔1秒就重新显示一遍，直到用户中断它。
-o(timers)显示计时器； 提示：LISTEN和LISTENING的状态只有用-a或者-l才能看到
*套接口类型*：
-t ：TCP
-u ：UDP
-raw ：RAW类型
--unix ：UNIX域类型
--ax25 ：AX25类型
--ipx ：ipx类型
--netrom ：netrom类型

### 常用命令:

- 列出所有端口 (包括监听和未监听的)

  - netstat -a #列出所有端口
  - netstat -at #列出所有tcp端口
  - netstat -au #列出所有udp端口

- 列出所有处于监听状态的 Sockets

  - netstat -l #只显示监听端口
  - netstat -lt #只列出所有监听 tcp 端口
  - netstat -lu #只列出所有监听 udp 端口
  - netstat -lx #只列出所有监听 UNIX 端口

- 显示每个协议的统计信息

  - netstat -s 显示所有端口的统计信息
  - netstat -st 显示TCP端口的统计信息
  - netstat -su 显示UDP端口的统计信息

- 显示每个协议的统计信息

  - netstat -s 显示所有端口的统计信息
  - netstat -st/-su 显示 TCP/UDP 端口的统计信息

- 在 netstat 输出中显示 PID 和进程名称

  - netstat -p

- 在 netstat 输出中不显示主机，使用数字代替那些名称端口和用户名 (host, port or user)

  - netstat -n
  - 如果只是不想让这三个名称中的一个被显示，使用以下命令
    netstat -a --numeric-ports #port用数字显示 netstat -a --numeric-hosts #host用数字显示 netstat -a --numeric-users #user用数字显示

- 持续输出netstat信息

  - netstat -c #每隔一秒输出网络信息

- 显示系统不支持的地址族(Address Families)

  - netstat --verbose

- 显示核心路由信息

  - netstat -r

- 找出程序运行的端口和指定端口运行的程序

  (并不是所有的进程都能找到，没有权限的会不显示，使用 root 权限查看所有的信息)

  - netstat -ap -n | grep 程序名 #找程序运行的端口
  - netstat -an -p | grep ':端口号' # 找出运行在指定端口的进程

- 显示网络接口列表

  - netstat -i #显示网卡列表
  - netstat -ie #显示详细信息

- __ IP和TCP分析__

  - 查看连接某服务端口最多的的IP地址:
    `netstat -nat | grep "192.168.1.15:22" |awk '{print $5}'|awk -F: '{print $1}'|sort|uniq -c|sort -nr|head -20`
  - TCP各种状态列表:
    `netstat -nat |awk '{print $6}'`

### 命令执行结果:

netstat | head -n2:显示netstat结果的前两行(取出列名).
从整体上看，netstat的输出结果可以分为两个部分：

1. 一个是Active Internet connections是激活Internet连接 Proto显示连接使用的协议
   "Recv-Q"和"Send-Q"指的是接收队列和发送队列。这些数字一般都应该是0。如果不是则表示软件包正在队列中堆积。这种情况只能在非常少的情况见到。
   Local Address本地地址
   Foreign Address外部地址 State显示套接口当前的状态
2. 另一个是Active UNIX domain sockets，称为活跃的UNIX域套接字(和网络套接字一样，但是只能用于本机通信，性能可以提高一倍)。
   Proto显示连接使用的协议
   RefCnt表示连接到本套接口上的进程号
   Types显示套接口的类型
   State显示套接口当前的状态
   Path表示连接到套接口的其它进程使用的路径名。