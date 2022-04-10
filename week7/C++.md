## 预处理和宏定义

```cpp
//#define  #ifdef  #endif   #else
#define FUN(a)(a*a)
#define FUN1(a)((a)*(a))
int main(){
    int b=3;
    FUN(b+2);//b+2*b+2=11
    FUN1(b+2);//(b+2)*(b+2)=25    
}
//
//define在预处理阶段进行简单替换，没有类型检查
//const在编译期处理，有类型检查
```

## String类的具体实现

```cpp
class String{
public:
    String(const char* str = NULL);//构造函数
    String(const String& other);//复制构造函数
    ~String();//析构函数
    String& operator=(const String& rhs);//赋值函数
private:
    char* m_data;//用于保存字符串
}
String::String(const char* str){
    //注意判空
    if(str == NULL){
        m_data = new char[1];
        m_data[0]='/0';
    }
    m_data = new char[strlen(str)+1];
    strcpy(m_data,str);
}
//注意参数
String::String(const String& other){
    delete[] m_data;
    m_data = new char[strlen(other.m_data)+1];
    strcpy(m_data,other.m_data);
}
//注意返回值
String& String::operator = (const String &rhs){
    if(this == &rhs){
        return *this;
    }
    //删除原来数据
    delete[]m_data;
    //新开一块内存
    m_data=new char[strlen(rhs.m_data)+1];
    strcpy(m_data,rhs.m_data);
    return *this;
}
String::~String(){
    delete[]m_data;
    m_data = NULL;
}
```

## C++动态分配内存:

1. new/delete是关键字，需要编译器的支持；malloc/free是库函数，需要库文件的支持
2. new无需指定大小编译器会根据类型自己 推算，malloc需要手动指定大小
3. new分配成功返回的是严格与对象匹配对象指针，无需类型转换，故是符合类型安全的操作；malloc分配成功返回void*,需要通过强制类型转换成我们需要的类型。
4. new失败抛出异常，malloc失败返回NULL
5. 自定义类型：new会先调用operator new函数申请足够内存，然后调用构造函数初始化成员变量，最后返回该类型指针，delete则会调用析构。malloc/free只负责内存申请释放，不完成构造和析构工作。

```cpp
//1.new 动态分配，delete释放申请的内存
//语法：type *pName = new type[Num]
//     delete [] pNmae;
	int num = 5;
    int *pSz = new int[num];
    delete[] pSz;
    pSz = nullptr;//注意指空，防止野指针
//2.malloc和free动态申请内存
//void malloc(unsigned int size);
//void free(void* p);
    int *p = (int*)malloc(sizeof(int)*5);
    free(p);
    p=nullptr;//注意指空，防止野指针

//eg.
struct node
{
    int age;
    int birth;
    node() : age(0), birth(0){};
};
int main()
{
    int a = 1, b = 2;
    node *N = new node;
    node *N1 = (node *)malloc(sizeof(node));
    cout << N->age << " " << N->birth << endl;//0 0
    cout << N1->age << " " << N1->birth << endl;//不确定  不确定
    //记得deleteb
}

```

## C++内存区域划分:

STACK(向下增长)->unusedmemory->HEAP（向上增长）->CONST->BSS(设置为0值)->GVAR->TEXT(高->低)

```cpp
int a = 0;   //GVAR(全局初始化区)
int* p1;//bss（全局未初始化区）

void f(int a) {}
int main()
{
    int b;//stck
    char s[] = "abc";//stack
    int* p2;//stack
    const char* p3 = "123456";//p3在stack   “123456”在常量区
    const int ci = 1;//常量区
    static int c = 0;//GAVR(全局静态初始化区)
    p1 = new int(10);//heap
    p2 = new int(20);//heap
    char* p4 = new char[7];//heap
    f(1);

    return 0;//text(代码区)
    
}
```

## RAII(Resource Acquisition Is Initialization):


```markdown
  1. 依托于栈和析构函数来对所有资源（包括堆）进行管理。
  2. 主流编程语言，C++是唯一依赖RAII来做资源管理的。RAII的存在也是GC没有在C++使用的原因。
  3. 代表：智能指针
```

## 内存泄漏：

堆内存由于某种原因未释放或无法释放，造成系统内存的浪费。后果很严重！！！


```markdown
  1. 发生的原因：分配了内存后，所有指向该内存的指针都遗失了（无法释放），忘记释放（低级错误）。
  2. 排查：无法通过编译识别，只能在程序运行中来判别。
```

## 智能指针

```markdown
1. 为什么使用智能指针？答：智能指针其实就是用来管理一个指针，防止申请空间之后忘记释放而造成内存泄漏。可以提一下RAII资源管理机制
2. auto_ptr:所有权模式，存在所有权剥夺问题，可能导致内存崩溃问题。C++11已经废弃
3. unique_ptr:用于取代auto_ptr,保证同一时间只有一个智能指针可以管理该对象。不会出现多次释放的问题
4. shared_ptr:共享式拥有的概念(强引用)，采用引用计数机制。可能导致循环引用问题，导致内存无法释放。
5. weak_ptr:(弱引用)，协助shared_ptr,避免循环引用问题。智能从shared_ptr或weak_ptr构造，他的构造不会影响引用计数
```



## argc,argv

```markdown
1. argc是传入main函数的参数的个数，第一个是该程序的名字
2. argv是main函数参数的vector
```

## RB-Tree（不公开）：

```markdown
1. 红黑树是一棵平衡二叉树，元素排列规则有利于search,insert，并保持适度平衡，不会导致任何分支过深
2. RBT保持了元素的有序性
3. RBT提供两种插入操作：insert_unique()不允许key重复，和insert_equal()允许key重复
```

## (multi/) set&map

```markdown
1. set/multiset map/multimap底层是RBT
2. value = key + data ,不能通过iterrator修改key(因为其是有序的)
3. set的value就是key，底层如何实现不修改key的功能？ 答：提供的迭代器是rbtree::const_iterrator;
4. map可以改data但value不能改，底层怎么实现？ 答：进行rbtree构造是采用如下策略：pair<const key,value>。
5. []是map独有的，multimap不能用。调用map[key]时，若map中不存在该key则会添加该key（调用lowerr_bound()查找插入位置）,data为默认值。
```

## hashtable（不公开）：

```markdown
1. 哈希冲突处理：hash+linklist(不能太长)
2. hashtable大小刻意为取质数，初始为53
3. 何时扩容？ 一般策略：元素个数大于篮子个数
4. 怎么扩容？ 一般策略：再哈希，新hashtable.size=上一个hashtable两倍最近的质数，（编译器已经提前设定算好，不用在需要扩/容时才计算。）
5. hash function+modulus（取余）:（标准库的做法：数值类型就当作hash,其他的STL也有提供。理想目的就是制造出够乱的函数，使之不容易发生碰撞）
6. unordered_(multi)set/map底层用hashtable实现
```

## vector

```markdown
1. 扩容方式？   vs:1.5倍   gcc:2倍  为了防止申请内存的浪费，现在使用较多的有2倍与1.5倍的增长方式，而1.5倍的增长方式可以更好的实现对内存的重复利用，因为更好。
2. 为什么采用成倍扩容不用每次增加一定数量值得机制？   vector在push_back以成倍增长可以在均摊后达到O(1)的事件复杂度，相对于增长指定大小的O(n)时间复杂度更好。
```

## deque&queue&stack

```markdown
1. 分段连续 （中心控制器+buffer）,扩充时copy到中段
2. 怎么插入？ 如果是插入位置是头，交给push_front()做，如果插入位置是尾，交给push_back(),否则往小的一端推动。
3. 怎么模拟连续空间？归功于各种iterrator
4. queue和stack的底层都是deque（或则list）,stack也可以选择vectorw，不过是封住了某些功能。
```

## static

```markdown
1. 作用：控制变量的存储方式和可见性
	作用1：（修饰局部变量），将局部变量生命周期放在静态区，且生命周期与程序相同。注意变量作用域没有发生变化，依旧限制在其语句块内。引入局部静态变量的原因：在多次调用时变量值得到有效的保存。
	作用2：（修饰全局变量），改变作用域范围，只对该文件可见。
	作用3：（修饰类），静态成员函数（只能访问静态数据）和静态数据成员是属于类的，而不是属于对象的。
	解释：static成员函数不能访问非静态成员的原因：因为static是属于整个类的，其没有this指针，this指针是指向本对象的指针，即其访问不到属于对象的东西。而且static成员函数不能被virtual修饰，因为虚函数的实现是为没有对象加上一个vptr,而vptr是通过调用this实现的额。
```

## const

```markdown
1. const修饰是遵循最优优先的原则
2. const数据成员初始化只能通过初始化列表给出。
3. const对象只能访问const成员函数，const成员函数不能修改数据成员。
4. C++怎么定义常量？放在哪儿？ 答：对于局部常量放在栈区，全局常量，编译器一般不分配内存而是放在符号表中以提高访问效率，字面值常量放在常量区。
```

## overload&override&重定义

```markd
1. 重载：函数名相同而参数类型个数不同
2. 重写：派生类重新定义父类的虚函数，关注函数名和参数
3. 重定义（也叫隐藏）：派生类重定义父类的非虚函数，只关注函数名
```

## 构造函数们

```markdown
1. 构造函数的作用：初始化对象的数据成员
2. 默认构造函数，什么也不做（实测基本数据类型被设为0值）
3. 有参构造函数，可重载
4. 拷贝构造函数：根据已有对象复制一个相同的对象。（系统默认的是浅拷贝，当存在指针时得自己写拷贝构造），
	那些情况会调用拷贝构造函数：以传值方式传入，返回对象，需要调用拷贝构造函数来创建一个临时对象。一个对象需要另一个对象初始化时。
	为什么必须用引用传递：参考上条，若采用传值则会造成无无限的递归调用。
5. 赋值运算符：类似拷贝构造函数，区别是左右两边对象都已经被创建出来了。（系统默认浅复制）
```

## 类型转换

```markdown
1. static_cast:
2. dynamic_cast:
3. const_cast:
4. reinterpret_cast:
```

## 野指针&悬空指针

```markdown
1. 野指针：未被初始化得指针
2. 悬空指针：指针所指内存已经被释放
防范：在定义指针时初始化它，释放内存后指针置空。
```

## volatile

```markdown
三个特性：
1. 易变性：volatile告诉编译器我修饰得变量很容易改变的，每次访问我都必须重新从内存中读取，不能偷懒。
2. 不可优化性:volatile告诉编译器不要自作聪明对我进行各种优化，我写什么你就执行什么。
3. 顺序性：能够保证volatile之间得顺序，不会被编译器乱序优化
```

## extern

```markdown
1. extern告诉编译器：这个变量是在别处声名的，要在该处引用。有了include为什么还要extern，答：因为快。
2. C++中还以此区分c函数库的调用
```

## 面向对象三大特性

```markdown
1. 封装：没啥好说的
2. 继承：没啥好说的，内容太多
3. 多态：多态与非多态的本质区别是函数地址是早绑定的还是晚绑定的（不针对重载）。早绑定的意思是编译期就可以确定函数的调用地址，并产生代码；而晚绑定是直到运行期间才能确定。

4. 多态的实现：
重载是静态多态：在编译期就决定好了要调用哪一个函数，根据传入参数来决定
动态多态通过子类重写父类的虚函数来实现，与虚函数表和虚函数指针有关。
5. 虚函数表，虚函数指针
如果类中有虚函数，C++编译器会为该类生成一个虚函数表，保存该类中虚函数的地址。当派生类继承基类时，编译器也会为派生类生成自己的虚函数表。当我们定义一个有虚函数的派生类对象时，编译器检测到该类型的对象有虚函数，则会为其初始化一个指向该类型的虚函数指针，指针的初始化在构造函数中完成。后续如果有基类类型指针指向派生类，那么会调用该类的虚函数指针去找到真正的虚函数地址一实现多态。
虚函数表的建立过程：对于派生类来说，先拷贝基类的虚函数表，会选出一个主基；类查看派生类中是否有重写基类的虚函数，有则在主基的虚表中替换；类查看派生类有没有新增的析构函数，有则添加到主基的虚表中去。

6. 析构函数定义为虚函数的原因：降低内存泄漏的可能性。如果一个基类指针指向一个派生类对象，在调用析构函数时会根据指针类型，调用当前对象的析构函数，如果没有申明为虚函数，则编译器会认为当前类型就是基类而仅仅调用基类的析构函数（因为该对象的析构函数被绑定为基类的析构函数）而导致自身资源无法被析构。如果是虚析构函数则编译器会根据当前对象实际类型进行析构函数的调用。

7. 构造函数为什么不是虚函数？
答：虚函数的调用是通过实例化的对象中的虚函数指针来找到的，都没有对象哪里来的虚函数指针

不要在构造函数或则析构函数中调用析构函数。

8. 构造函数执行顺序：。。。是调用顺序，而不是出现的顺序（以后再详细说明）

9. 静态绑定和动态绑定：
答：先说一说静态类型：程序被声明时所采用的类型  动态类型：目前对象的实际类型
静态绑定（早绑定）:绑定的是静态类型，发生在编译期间，对应的函数或属性依赖于静态类型 ，缺省参数是静态绑定
动态绑定（晚绑定）:绑定的是动态类型，发生在运行期间，对应的函数或属性依赖于动态类型 ，virtual是动态绑定
```

## 内存对齐

```markdown
1. 对其规则：第一个成员位于偏移量为0的位置，以后每个成员偏移量是（CPU规定的例如2,4,8...）min(#prag)。且对齐后所有长度之和为（CPU规定的例如2,4,8...&max(type)）整数倍。   编程技巧，大的方后面。
2. 为什么要对齐？答：CPU对内存的访问是按块访问（称为CPU内存读取粒度）的，内存对齐可以加快CPU的内存访问速度。
```



## 类间关系：继承，复合，委托

```markdown
1. Compostion（复合）:表示has-a     (Adapter模式)
	构造函数由内而外，析构由外而内。
2. Delegation（委托）：表示composition by reference     (pimpl手法，如引用计数（了解：copy on write）)
	与Compostion区别：生命周期不同
3. Inheritance（继承）：表示is-a
	构造由内而外，析构（父类析构函数必须是virtual）由外而内
	
```

## 虚函数

```markdown
//函数的继承继承的是调用权
non-virtual function:不希望子类重新定义（override）
virtual function:希望子类重新定义，且已有默认定义
pure-virtual function:希望子类一定要重新定义，且没有默认定义（可以有）

//Template Method模式:固定某些框架，将某些集体功能延迟到子类实现（继承+虚函数实现）
//Obesever模式:被观察者应该有注册和通知观察者的功能。（委托+继承实现）
//Composite模式：Composite有一个vector可以放自己，也可以放Primitive。可以考虑为这两个类设计一个共同父类，容器内放父类指针就可以。（委托+继承）
//Prototype模式 ：如何创建未来的对象，每个子类自己创造自己（static），并可以登记到父类 

//怎么实现虚机制（动态绑定）？
答：1.通过指针，2.指针向上转型，3.调用虚函数。  Shape* p= new Circle;p->draw();

00
```



