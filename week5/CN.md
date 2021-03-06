## 浅浅

1. TCP/IP网络模型：应用层，传输层（TCP，UDP），网络层（IP），数据链路层，物理层

2. HTTP（超文本传输协议）：计算机世界里专门在两点之间传输超文本数据的约定和规范。常见状态码：1xx:提示信息，2xx:成功， 3xx:重定向，4xx:用户发送报文有误，5xx:服务器错误。

3. GET：请求从服务器获取资源。  POST：向URI指定的资源提交数据（数据放在报文里）。

4. 安全：请求方法不会破坏服务器上的资源。 幂等：多次执行效果都是相同的。 GET是安全和幂等的，POST既不是安全也不是幂等的。

5. HTTP1.1: 
   1. 优点：简单灵活，易于拓展(协议中方法没有被定义死，允许开发者自定义)，（报文=header（key,value）+body）
   2. 缺点：无状态（解决方案：Cookie（通过在响应报文中写入Cookie来控制客户端的状态）），明文传输（方便调试但信息裸奔），不安全。  HTTPS（端口443）（混合加密，摘要算法，数字证书）：在HTTP（端口80）与TCP之间增加安全传输层，使得报文能加密传输，增加传输的安全性，建立TCP连接后还有加密解密的连接。
   3. 性能：基于TCP/IP，使用请求应答通信模型。是长连接的（HTTP1.0是短连接（每次发送一个请求都要重新进行一次TCP连接））

6. HTTP2：基于HTTPS。改进：1.压缩头部  2.使用二进制格式（增加数据传输效率） 3.服务器推送（不单纯是请求应答模式，服务器可以主动发消息） 4.

7. HTTP3：改进HTTP可能会发生的丢包问题，下层采用UDP+QUIC协议

8. HTTP1.1优化：
   1. 使用keepAlive改为长连接
   2. 避免发送HTTP请求：缓存在本地，减少重定向请求次数（代理服务器），合并请求，延迟发送请求
   3. 减少HTPP响应数据的大小：数据压缩

9. TCP：TCP是面向连接的，可靠的，基于字节流的传输层协议。（首部20+x byte,UDP首部：8byte）。用于保证可靠性和流量控制维护某些信息，包括，Scoket，序列号，窗口大小。
   1. 为什么是3次握手：避免重复历史连接（先发出的请求后到），同步双方初始序列号。
   2. SYN攻击：不断向服务器发送SYN，而服务器发出的ACK没法得到响应。导致服务端的SYN队列满
   3. 四次挥手：C:我想关了，不发数据。S:好的，我知道了，但是等等我还有数据没发。 S:我发完了，你可以关了 C:好的
   4. 重传机制：累计确认应答（滑动窗口（流量控制）：接收方告诉发送方自己窗口大小，发送方按照这个标准发数据），超时重传。
   5. 拥塞控制：避免发送方发送过多数据到网络中，拥塞窗口（cwnd）由发送方自己维护。只要网络没有发送拥塞cwnd增大，否则减小。（怎么知道拥塞：ACK没有及时到达。）
      1. 慢启动：慢慢增加可发送的数据量：指数增长（到慢启动门限）
      2. 拥塞避免：线性增长
      3. 拥塞发生：超时重传：慢启动    快速重传：快恢复

10. IP ，DNS ，ARP （IP->MAC），DCHP(用udp广播(DCHP 中继代理（解决不同局域网问题）):discover ,offer,request,ack)，NAT （网络地址转换），ICMP（确认IP包是否成功到达，ping基于ICMP）。

11. 键入网址到显示网页放生了什么：
    1. URL解析，DNS（hosts,本地，根。。。）查找IP，
    2. 产生HTTP请求（协议栈（TCP，IP，UDP））（打包好了）
    3. 网卡：数字信号转化为电信号
    4. 送别：交换机，路由器
    5. 到达服务器：服务器拆包裹，知道对方要什么
    6. 完成：服务器把数据发了过来

12. FTP
    1.  （C/S）模型
    2.  FTP 的独特的优势同时也是与其它客户服务器程序最大的不同点就在于它在两台通信的主机之间使用了两条 TCP 连接，一条是数据连接，用于数据传送；另一条是控制连接，用于传送控制信息（命令和响应）
    3.  FTP的传输有两种方式：ASCII、二进制
    4.  FTP支持两种模式：Standard （PORT方式，主动方式（由服务器创建数据连接客户端控制连接时给的端口+1的端口），主动方式存在弊端，因为客户端端口是随机的，如果客户端建立了防火墙，服务端建立连接可能会被拒绝。），Passive （PASV，被动方式（由客户端创建数据连接））。
    5.  用户认证：虚拟用户，系统用户，匿名用户

13. TCP三次握手四次挥手

    1.  为什么是三次不是两次？

        ```markdown
        1. 为什么要握手？
        答：因为TCP是一个可靠的数据传输协议（用seq+ack的机制来保证可靠传输），而且TCP是一个全双工的协议，客户端和服务端都必须要维护并同步彼此的seq.
        2. 为什么是三次握手？
        答：为了实现可靠传输，通信双方都必须维护一个序列号以标识已经发出去的数据中那些已经被收到。如果是两次握手，发送方序号能同步，但接收方序号得不到同步（因为没收到确认信号）。
        //《计算机网络》中的回答：防止已经失效的连接又传回服务端，因而产生错误。（不记这个啦，服务端接到请求就建立连接，可能空等，浪费资源。）
        换个角度理解为什么是三次握手：想要实现全双工通信，必须保证双方的发送，接收功能都是完好的。想要得到这个保证，必须经历三次握手（可以自己慢慢推导）
        3. 为什么不是四次握手？
        答：三次就够了，为什么要四次？
        ```

    2.  为什么是四次挥手？

        ```markdown
        1. 为什么是四次握手呢？
        答：TCP是一个全双工的协议，当有任何一方想要断开连接必须通知对方，且等待对方做好剩余的工作。
        2. 为什么客户端收到接收端的FIN报文后还要等待2MSL的时间？
        答：确保A发出去的最后一个报文能够顺利到达B，如果超时B会再向A发送一个报文；而且该缓冲时间也可以让本次连接的所有报文在网络中消失，避免对下一次连接造成影响。
        ```

14. TCP粘包和拆包

    1. 为什么说TCP有该问题，UDP为什么没有？

       ```markdown
       答：UDP是基于报文传输的，首部有对报文数据长度的标识，不会造成该问题。TCP是面向字节流的，s把数据分割成大小不同的数据包，所以会造成粘包和拆包问题。
       ```

    2. 为什么会发送粘包和拆包问题？

       ```markdown
       答：要发送的数据大于 TCP 发送缓冲区剩余空间大小，将会发生拆包。
       待发送数据大于 MSS（最大报文长度），TCP 在传输前将进行拆包。
       要发送的数据小于 TCP 发送缓冲区的大小，TCP 将多次写入缓冲区的数据一次发送出去，将会发生粘包。
       接收数据端的应用层没有及时读取接收缓冲区中的数据，将发生粘包。
       ```

    3. 怎么解决粘包和拆包问题？

       ```markdown
       由于 TCP 本身是面向字节流的，无法理解上层的业务数据，所以在底层是无法保证数据包不被拆分和重组的，这个问题只能通过上层的应用协议栈设计来解决，根据业界的主流协议的解决方案，归纳如下：
       1. 消息定长：发送端将每个数据包封装为固定长度（不够的可以通过补 0 填充），这样接收端每次接收缓冲区中读取固定长度的数据就自然而然的把每个数据包拆分开来。
       2. 设置消息边界：服务端从网络流中按消息边界分离出消息内容。在包尾增加回车换行符进行分割，例如 FTP 协议。
       3. 将消息分为消息头和消息体：消息头中包含表示消息总长度（或者消息体长度）的字段。
       ```

##  实战

### 一些基础

高新能网络编程的任务：如何保证服务器端在数据量巨大的客户端访问的时候还能保持效率和稳定。【端口，16位的整数，当客户端发起连接时，客户端的端口由OS随机分配，称为临时端口】【保留端口：大家约定俗成的被对应服务广为使用的端口，例如shh:22,ftp:21,http:80等。一般来说大于5000的端口可以为我们自己所用】【保留网段，例如192.168.xx,xx,这类网段不用做公网的IP，仅仅保留做内部使用。】【socket屏蔽了各个协议的通信细节，使得程序员不需要关心协议本身可以直接使用socket提供的接口来实现互联网不同主机间的通信。】

### 通用套接字地址格式：

问：为什么定义一个通用的地址结构：

```c
//POSIX.1g规范规定了地址族位2字节的值
typedef unsigned short int sa_family_t;
//通用套接字格式
struct socketaddr{
    sa_family_t sa_family;//地址族 16bit(表示用什么样的方式对地址进行解释和保存。例如AF_LOCAL,AF_INET,AF_INET6分别表示本地地址，IPV4地址和IPV6地址)
    char sa_data[14];//具体地址 112bit
}
```

### IPV4套接字地址格式：(固定16byte)

```c
//IPV4套接字地址值32bit
typedef uint32_t in_addr_t;
struct in_addr{
    in_addr_t s_addr;
}
//描述的IPV4套接字地址格式
struct sockaddr_in{
    sa_family_t sin_family;//16 bit
    in_port_t sin_port;//端口号 16 bit(即最多有2^16个端口)
    struct in_addr sin_addr;//网络地址 32bit（大约42亿）
    //没用，占位的
    unsigned char sin_zero[8];
}
```

### IPV6套接字地址格式：(固定28byte)

```c
struct sockaddr_in6{
    sa_family_t sin6_family;//16 bit
    in_port_t sin6_port;//传输端口号：16bit
    uint32_t sin6_flowinfo;//IPV6流控制信息32bit（先不研究）
    struct in6_addr sin6_addr;//IPV6地址值，128bit
    uint32_t sin6_scope_id;//IPV6域ID 32bit(先不研究)
}
```

### 本地套接字格式（用于本地进程间通信）(可变，最长110byte)

```c
struct sockaddr_un{
    unsigned short sun_family;//固定为AF_LOCAL
    char sun_path[108];//路径名      
}
```

为什么本地套接字格式不需要端口号，而IPV4和IPV6格式需要端口号？

答：本地socket是基于文件操作的，只需要文件路径就可以区分了。

### 服务端准备连接的过程

```c
//一，创建套接字
int socket(int domain,int type,int protocol)
//二,bind 把套接字和套接字地址绑定（设定电话号码）
//根据len字段判断传入的参数（因为设计时C语言还没有void*支持类似多态的行为）
bind(int fd,sockaddr* addr,socklen_t len)
//bind时对地址和端口可以有多种处理方式
//1.可以把地址设置成本机的IP地址,但是如果一台机器有多个网卡，可以设置通配地址
struct sockaddr_in name;
name.sin_addr.s_addr=htonl(INADDR_ANY);//IPV4通配地址
//2.可以把端口设置成0，表示把端口选择权交给操作系统内核来选择
//一般来说服务端的程序要绑定到一个总所周知的端口，便于客户端发起请求。

//一个初始化IPV4套接字例子
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netine/in.h>

int make_socket(uint16_t port){
    int sock;
    struct sockaddr_in name;
    
    //创建字节流类型的IPV4socket
    socket = socket(PF_INET,SOCK_STREAM,0);
    if(sock<0){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    //绑定port和ip
    name.sin_family=AF_INET;//IPV4
    name.sin_port=htons(port);//指定端口
    name.sin_addr_s.s_addr=htonl(INADDR_ANY);//通配地址
    //把IPV4地址转换成通用地址格式，同时传递长度
    if(bind(sock,(struct sockaddr*)&name,sizeof(name))<0){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    return sock;
}

//三，listen（接上电话线，一切准备就绪）
int listen(int socketfd,int backlog);
//socketfd为套接字描述符，backlog表示已经完成但是未accpet的队列大小（该参数的大小决定了可以接收的并发数目）

//四，accpet(电话铃响了)
int accpet(int listensockfd,struct *cliaddr,socklen_t *addrlen);
//服务端accpet后产生新的已连接的套接字（函数返回值），另外的监听套接字一直存在(第一个参数)
```

### 客户端发起连接的过程：

```c
//一，创建套接字
//同上

//二，connect(拨打电话)
int connect(int sockfd,const struct sockaddr *servaddr,socklen_t addrlen);
//客户端调用connect函数之前非必须调用bind函数，因为操作系统会给你做
//如果是TCP连接，connnect将激发TCP的三次握手仅在建立成功或出错才
```



