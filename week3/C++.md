1. 预处理和宏定义

   ```cpp
   //#define  #ifdef  #endif   #else
   #define FUN(a)(a*a)
   #define FUN1(a)((a)*(a))
   int main(){
       int b=3;
       FUN(b+2);//b+2*b+2=11
       FUN1(b+2);//(b+2)*(b+2)=25    
   }
   ```

2. String类的具体实现

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
       //z
       if(str == NULL){
           m_data = new char[1];
           m_data[0]='/0';
       }
       m_data = new char[strlen(str)+1];
       strcpy(m_data,str);
   }
   
   String::String(const String& other){
       delete[] m_data;
       m_data = new char[strlen(other.m_data)+1];
       strcpy(m_data,other.m_data);
   }
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

3. 

