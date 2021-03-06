## 浅学

1. 进程运行状态： ps -aux | grep PID
2. 查看内存情况：free
3. 文件权限： chmod owner/group/other
4. 软链接vs硬链接 （硬链接类似于windows快捷方式,软链接保存另一个文件的路径）
5. 动态库vs静态库
6. 小端模式vs大端模式：（小：低有效字节存放在低地址。。。。），可以根据联合体判断，因为联合体总是从低字节开始存储
7. 字节序转换：网络协议规定大端模式，进行网络通信时必须转换。
8. 进程调度：FCFS，SF,HRN,时间片轮转，多级反馈   （抢占vs非抢占）
9. 物理内存（reg,cache,memory,disk）vs虚拟内存
10. 内核态vs用户态 (进入方式：系统调用，异常，中断)：处于安全性考虑
11. LRU算法：利用链表，当需要插入新数据时，存在则移动到链表头，没有则放到链表头，缓存满了就删除最后一个节点
12. 页表：虚拟内存到物理内存的映射（多级页表减少内存消耗）
13. 缺页中断：分配内存时只是建立虚拟地址空间，没有建立映射关系，进程访问时会触发缺页中断将也=页调入内存
14. 虚拟内存分布：text (代码段，二进制机器指令),data（已初始化的全局变量）,bss（未初始化的全局变量），堆（低到高），共享区，栈（高到低）
15. 进程，线程，协程：进程是程序的执行实体，线程是微进程（一个进程包含多个线程并发执行任务），
16. fork()：创建子进程，返回子进程PID.调用一次，返回两次
17. 孤儿进程：父进程退出后，子进程还在运行，被init进程收养。
18. 僵尸进程：子进程退出后父进程没有收到退出的信号，子进程的进程描述符依然保存在系统中，浪费系统资源。
19. 解决僵尸进程：1.及时wait调用，建立捕捉SIGCHLD信号的信号处理函数。2.kill 先用ps -aux | grep Z查看僵尸进程，然后kill
20. 守护进程：长期在后台运行的程序，用于控制终端，处理一些系统级别任务。
21. 进程间通信方式：管道，消息队列，信号，信号量，内存共享。
22. 进程状态：创建，就绪，执行，阻塞，中止。
23. 死锁发生的条件：互斥，请求保持，不可剥夺，环路等待
24. 自旋锁:只有一个锁，只能被一个线程持有，会造成忙等。自旋锁与锁互斥锁的区别，不会使线程状态发生改变减少了上下文切换。
25. DMA:进行数据传输时，将数据搬运工作交给DMA控制器，期间CPU可以做其他工作。
26. 零拷贝：传统的文件传输会经过4次拷贝（磁盘->内核，内核->用户，用户->socket,socket->网卡），但其实用户缓冲区没有存在的必要（因为不修改内容），减少上下文切换的成本。原因：用户没有权限操作磁盘，网卡，需要通过系统调用陷入到内核态，从而发生上下文切换。（传输大文件不能采用零拷贝技术，因为cache被占用，导致小文件无法利用cache,并且大文件的chache的命中率不高，应该采用异步IO+直接IO的方式。）
27. mmap：内核缓冲区的数据映射到用户空间，减少了一次数据拷贝。sendfile:减少了用户缓冲区。 后期：全程不通过CPU拷贝数据，而是通过DMA进行
28. epoll和select（多路IO复用）：select要等待数据的复制
29. 多路IO 复用（基于非阻塞）：吃饭有一排窗口都没做好，阿姨说做好了通知你，过了一会阿姨通知你，但是你得自己看是哪一个窗口做好了，然后等待阿姨打饭。
30. 阻塞IO：去食堂吃饭，但是没做好，一直在食堂等到饭做好并等待阿姨打饭，最后吃饭。
31. 非阻塞IO：去食堂吃饭，但是没做好，阿姨说做好通知你，你去干其他事，通知你之后你去吃饭得等待打饭的过程。
32. 异步IO：你让阿姨做好饭并打包号再通知你。
33. 水平触发与边缘触发：LT：只要缓冲区还有数据下一次就接着读   ET：只有缓冲区状态改变才能读（必须一次处理完）
34. 网络模型：物理层，数据链路层，网络层(IP)，传输层（TCP,UDP），会话层（DNS），表示层，应用层（文件传输，文件管理等）
35. 文件系统：文件（inode（磁盘里）+目录项（内存中）），文件存储方式（连续，非连续（链表（隐式，显式），索引（多级索引））），缓冲IO与非缓冲IO，直接IO（不会发生内核缓存与用户程序直接复制）与非直接IO，阻塞IO（等到数据准备和数据从内核 态到用户态的拷贝）非阻塞IO（周期轮询（轮询期间CPU不做事，所以引出IO多路复用）数据是否准备好，没有则返回，由则等待数据从内核态到用户态的拷贝。）以上都是同步调用，因为不用态之间的数据复制必须等待。

## 面试

1. 什么是进程，为什么需要进程？

   答：解决多道程序设计的问题【操作系统为了便于管理而引入的概念】（1.如何隔离不同程序需要的计算机资源。2.如何进行不同程序的调度。3。如何提升计算机资源利用率）。进程（1.系统进行资源分配和调度的基本单位。2.进程作为程序独立运行的载体保障程序正常执行。3.进程使得操作系统资源利用率提高）

2. 简述同步与异步。

   答：五态模型（创建，就绪，执行，阻塞，中止），同步与异步强调的是消息的通信机制；阻塞和非阻塞强调的是程序在等待结果时的状态。（结合实际例子来回答，例如。。。）

3. 简述进程和线程的区别。

   答：进程（1.系统进行资源分配和调度的基本单位。2.进程作为程序独立运行的载体保障程序正常执行。3.进程使得操作系统资源利用率提高），引入线程的原因（为了提升系统内程序并发执行的程度），线程（1.是操作系统中运行调度的最小单位。2.是进程中实际运作的工作单位，3.一个进程可以并发执行多个线程。）线程也可以实现进程间的并发。

4. 简述操作系统的内核态。

   答：为了更安全的操作系统管理资源。内核空间（存放内核代码和数据，进程执行操作系统的内核代码，CPU可以访问内存所有数据，包括外围设备）。用户空间（存放用户程序的代码和程序，CPU只能访问有限资源）。用户态-》内核态（1.系统调用。2.异常中断。3.外围设备中断。）

5. 简述：I/O密集型任务和CPU密集型任务

   答：计算密集型（CPU利用率高，其他事情处理满。完成一项任务的事件取决于CPU性能。如：计算1024000！，多线程可以提升速度），IO密集型（频繁读写网络，磁盘等。完成一项任务时间取决于IO设备的速度，CPU利用率低，大部分时间都在等待设备完成。如：读2G文件，可以通过缓存机制减少IO次数）。

6. 什么是协程，为什么需要协程？

   答：先说，为了减少上下文切换（每个任务运行前CPU都需要知道任务从哪里加载，从哪里开始运行。CPU进行进程的调度时发生）。协程（协作式线程，协程的本质就是用户级线程）多个协程对应一个内核态的线程。协程优点：调度，切换，管理更加的轻量级。缺点：内核无法感知协程的存在。适用于多IO的场景，但是无法发挥CPU多核的优势。

7. 什么是局部性原理？

   答：存储器的层次结构（缓存（Cache:解决CPU和主存速度不匹配的问题），主存，（主存之外加辅助存储器：解决主存容量的够的问题）辅存）。局部性原理：CPU访问存储器时，无论是存取指令还是存取数据，所访问的存储单元都趋于在一个较小的连续区域中。局部性原理应用（Redis。。。）

8. 简述什么是虚拟内存？

   答：虚拟内存是物理内存和进程之间的中间层，它为进程隐藏了物理内存这一概念，为进程提供更简洁易用的接口。虚存原理：把程序程序使用内存划分，把暂时不用的内存放置在辅存（局部性原理）。（作用：1.虚存可以起到缓存的作用，提高进程访问速度。2.虚存可以为进车提供独立的理论上无限大的空间。3.虚存可以控制进程对物理内存的直接访问，隔离不同进程对物理内存的访问权限，提高系统的安全性）。
   
9. 说说缺页中断！

   答：进程要访问的页不在内存中时会产生缺页中断，将进程需要的页调入主存。缺页中断是指令执行过程中产生的中断。页面置换的算法设计，均利用双向链表（FIFO，LFU，LRU）。熟悉这三个页面置换算法流程。

10. 说说操作系统的内存管理！

    答：分为页式管理（逻辑空间划分等分大小的页，缺点是会导致连续的页分布在不同页中，效率降低。页面大小难以设置，过大导致难以分配，过小导致页表(记录逻辑内存与物理内存的映射关系)过大。linux(4k)。没有外碎片（分区之间无法利用的微小空间）），段式管理（相比页式管理更灵活。没有内碎片（占用分区内未被利用的空间）），段页式管理。

11. 说说软链接和硬链接：

12. 简述RAID存储：

13. 说说进程间通信方式：

    1. 管道：
    2. 消息队列：
    3. 共享内存：
    4. 信号：
    5. 域套接字

14. 说说CAS原理：

    1. 大量使用锁的弊端
    2. CAS与无锁队列

15. 说说对死锁的认识：

    1. 死锁概念：两个或以上进程在执行过程中由于资源竞争造成的一种阻塞现象。
    2. 死锁的产生：资源竞争，程序设计不当
    3. 死锁产生的必要条件：互斥（进程不能同时访问同一资源），请求等待（对资源有请求且不释放自身拥有的资源），不可剥夺，环路等待（存在进程-资源环形链）
    4. 预防死锁：
    5. 应行家算法

16. 同步问题：

    1. 生产者消费者：
    2. 读者写者：
    3. 哲学家进餐：

17. 线程间通信：

    1. 乐观锁：
    2. 悲观锁：
    3. 互斥锁：
    4. 自旋锁：
    5. 信号量：













