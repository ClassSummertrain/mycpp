##  云原生框架

1. 云计算的历史：虚拟化技术->虚拟机（一台物理机运行多个虚拟机，在硬件级别分离应用程序）->容器（虚拟化的升级，从软件级别划分并共享服务器的操作系统）。
2. 云原生：面向容器化，面向微服务，支持容器的编排调度。是一系列云计算技术体系与企业管理方法的集合。
3. 云原生基础架构：微服务（将大型应用拆分成多个简单应用，每个应用单独部署迭代），容器（在单一主机上提供多个隔离的操作系统环境，每个容器右自己独立的资源），服务网络，DevOps（便于开发者和维护者之间沟通交流的方法和工具的集合）

## 微服务概述

1. 系统架构的演进：单体架构->垂直分层架构->SOA->微服务架构->云原生
2. 常见微服务架构：Java（Spring Cloud，Dubbo），Golang（Go Kit ,Go Micro）
3. 微服务设计原则：高内聚低耦合，高度自治，以业务为中心，弹性设计，日志与监控，自动化
4. 领域驱动设计

## Go语言基础

1. Go语言特性：

   1. 天然支持高并发

   2. GC

   3. 支持函数多返回值

   4. 支持匿名函数和闭包

   5. 支持反射

      ....

2. 声明的变量必须被使用，可以使用_来接收不使用的变量，匿名变量 ( _ ）不占用命名空间，也不会分配内存。

3. 原生数据类型：

   1. bool：不能与整型强转，不能参与数值运算
   
   2. 整型：各种int float
   
   3. 字符串（以原生类型出现，基于utf-8实现）所以遍历时区分byte(代表一个ASCII)和rune(UTF-8的中文占3位，相当于char).
   
      ```go
      str :="Golang编程"
      for _,g := range []byte(f){
          fmt.Printf("%c",g)//输出乱码
      }
      for _,g := range f{
          fmt.Printf("%c",g)//输出正确
      }
      ```
   
      
   
   4. 类型定义，类型别名：类型定义会创建一个新的类型。
   
      ```go
      type myInt int//类型定义
      type INT=int//类型别名
      ```
   
      
   
4. Go中常用容器：

   1. 数组：组数是一段连续空间，大小在声明时就已经确定下来，大小不可以变化。

      ```go
      //eg:
      var nums [3]int
      nums2:=[...]int{1,2,3}
      ```

   2. slice:切片是对数组一个连续片段的引用，是一个容量可变的序列。对切片的修改影响底层数组。

      ```go
      //1.从原生数组生成切片
      nums:=[...]int{1,2,3,4,5,6}
      sli:=nums[begin:end]
      //2.动态创建切片
      sli = make([]int,size,cap)
      //3.声明新的切片
      var sli []int
      //4.向数组添加元素
      sli1 := make([]int,5,5)
      sli2 := make([]int,5,10)
      sli1 = append(sli,sli2)//扩容
      sli2 = append(sli2,sli1)//不扩容
      
      ```

   3. list:（带头结点的双向链表，不限制类型成员，任何类型都可以存）

      ```go
      var lst1 list.List
      lst2 := list.New()
      ```

   4. map:(内部通过散列表实现)

      ```go
      myMap :=make(map[keyType]valueType)
      ```

   5. 容器遍历（for range）

      ```go
      //k为键（下标），v为值
      //值拷贝，修改不影响原
      for k,v := range container{
          ...
      }
      ```

5. 函数(如果希望函数被外部访问，首字母大写)

   ```go
   func name(params)(return params){
       function body
   }
   //匿名函数 
   func (params)(return params){
       function body
   }
   ```

6. 闭包（携带状态的函数，是将函数内部和函数外部连接的桥梁。闭包能引用其作用域上部的变量）

   ```go
   func f(initial int)func() int{
       if initial < 0{
           initial = 0
       }
       //引用initial,创建一个闭包
       return func() int{
           initial++
           return initial
       }
   }
   
   func main(){
       c1:=f(1)
       fmt.Println(c1())//2
       fmt.Println(c1())//3
   }
   ```

7. 接口（调用方和实现方约定的一种协议，由一个或多个方法组成）,接口可以嵌套(类似继承)

   ```go
   type name interface{
       method1(params)(return params)
       method2(params)(return params)
       ...
       other interface
   }
   ```

8. 结构体（使用之前要进行实例化（分配内存）和初始化（赋值））

   ```go
   type Person struct{
       Name string
       Brith string
   }
   //实例化
   var p1 Person
   //or
   p1 := new(Person)
   p1 := &Person{}//取值实例化
   p1.Name="张贤"
   p1.Brith="1999-17-90"
   
   //初始化
   p1 := Person{
       Name:"张贤"
       Brith:"1999-90-90"
   }
   ```

9. 方法（有特定接收器的函数，接收器可以是任何类型。也就是说任何类型都可以有自己的方法）.指针类型接收器可以改成员属性，值类型接收器不能改成员属性。

   ```go
   func (recipient recipicentType)methodName(params)(return params){
       function body
   }
   ```

10. 类型内嵌和组合

## Go语言高级特性

1. 依赖管理

   1. 包管理：main函数在main包下，首字母大写表示公开
   2. GOPATH：（src+pkg+bin）。GOPATH是Go语言的一个环境变量，它以绝对路径提供Go项目的工作目录
   3. Go Modules：自动进行包管理的工具

2. 反射：（提供在运行时对代码访问和修改的能力）

   1. reflect.Type(区分Type（类型）与Kind（品种）)
   2. reflect.StrcutFiled，reflect.Method:获取结构体下字段的类型属性
   3. refect.Value:获取反射值对象，进行查看和修改

3. 并发模型：

   1. 并发和并行
   2. 线程与锁并发模型（主要依赖于内存共享）
   3. CSP（communicating sequential processes）并发模型(倡导使用通信手段来共享内存)，两个关键概念：并发实体（线程，并发实体之间是独立的，没有共享的内存空间），通道（并发实体之间用通道进行交流，向通道中放数据或取数据会造成并发实体的阻塞）。CSP容易导致死锁。
   4. 用户线程和内核线程
   5. 常见线程模型：
      1. 用户级线程模型：一个用户进程对应一个内核线程，进程内的多线程由用户自己管理。任意用户 线程的阻塞可能导致整个进程阻塞
      2. 内核级线程模型：每个用户级线程对应一个内核线程。优点：充分利用CPU，缺点：开销大
      3. 两级线程模型：上面两种的和
      4. MPG（Machine Procssor Goroutine）线程模型：MPG模型属于一种特殊的两级线程模型，对线程的管理做了一些优化

4. 并发实践

   1. 协程goroutine(一个轻量级的线程，运行时由runtime管理)

      ```go
      //启动一个协程
      go 表达式
      ```

   2. 通道channel(属于引用类型，每个channel只能传递固定类型的数据),队列，保证先进先出

      ```go
      //channel声明
      var Name chan T
      //创建channel
      ch := make(chan T,size)
      //向channel发送数据
      channel <- val
      //从channel接收数据
      val <- channel
      ```

   3. select：可以从多个通道中读取数据，与swtich类似，但case语句后必须是IO操作，如果没有IO语句且default语句则会阻塞

   4. sync同步包

      1. Mutex
      2. RWMutex
      3. WaitGroup(并发等待组)：等待预先设定好的gorutine都提交结果才往下执行
      4. Map（并发安全词典）

## 构建Go Web服务器

1. Web的工作原理
   1. HTTP协议：
      1. 应用层协议，由请求和响应构成是一个标准的C/S模型。HTTP是Web工作的核心
      2. HTTP是无状态的，同一个客户端的两个请求并没有对应关系，服务器并不知道其来自同一个客户端。为了解决无状态的问题，引入了Session和Cookie技术
      3. HTTP Request(请求行+首部+空行+实体)
      4. HTTPResponse(状态行+响应头+空行+响应体)
   2. 访问Web站点的过程：
      1. DNS获取域名
      2. 客户机通过TCP/IP协议建立到服务器的TCP连接
      3. 客户机发送HTTP请求包，请求服务器资源
      4. 服务器发送HTTP响应包
      5. TCP断开连接。客户端解释资源
2. Go构建Web服务器
   1. http服务端执行流程：创建Listen Socket监听相应窗口，接收请求得到Client Socket，处理客户端请求（POST则还要读取用户提交的数据 ），交给相应handler处理，处理完毕给出回应
      1. 处理器处理请求
      2. 解析请求体
      3. 返回响应体
3. Golang Web 框架 Gin
4. 服务端数据存储问题
5. Golang ORM 框架 beego

## 服务注册与发现

1. 服务注册：服务实体启动时向服务注册与发现中心报告自己的信息，并在运行时通过心跳等信息报告自己信息。
2. 服务发现：服务发现指服务实例向服务注册与发现中心获取其他服务实例信息，用于进行远程调用。
3. 服务与发现中心的职责：管理微服务实力的数据信息（包括名字，IP等），维护微服务实例的心跳，清除无效的服务实例，提供服务发现能力。
4. CAP(consistency,availability,partition tolerance)原理：
   1. 一致性：系统中数据的一致性。
   2. 服务可用性：服务在接到客户端请求时能响应。
   3. 分区容忍性：能容忍分区节点之间可能会出现的通信失败（分布式系统必须满足该条件，三个条件理论上不能同时满足）。
5. 常用服务注册与发现框架：
   1. Consul（基于Raft算法（保证数据一致性）的开箱即用的服务发现组件）：服务发现，健康检查，Key/Value，多数据中心
