# XML-Parser

#### 用法

从文件加载XML

从字符串加载XML

访问节点：根据数组下标、节点名称

遍历节点：数组、迭代器、for in

添加节点

删除节点

获取、修改节点名称、属性、内容

#### XML格式

```xml
<?xml version="1.0"?>
<!--hello-->
<students>
<student id="1" class="101">
<name>Rolo</name>
</student>
</students>
```



#### API设计实现

##### xml设计

1.里面设计一个Value类：方便用来数据转换（参考INI解析器）。

其中重载运算符中的数字类型，把数字类型存入流中，然后调用str（）转化为string。

![1](D:\typora-image\image-20230108212100933.png)

2.xml类设计

数据类型使用指针方式存储(解析速度快)

注：指针操作时，判断是否为nullptr。

删除：delete p； p=nullptr；



![2](D:\typora-image\image-20230108212324591.png)

![3](D:\typora-image\image-20230108212503003.png)

##### Parser设计

解析xml，把文本或者字符串中的数据转换成代码结构。

![4](D:\typora-image\image-20230108221708712.png)

#### 琐碎知识点

```c++
isalnum()//判断里面的内容是否为字母或者数字
    
const string& name = parse_name();//需要加const，函数返回的是临时变量，如果使用引用的方式接受，需要加const防止改变。
```

```c++
for (auto it = m_child->begin(); it != m_child->end();) {
		if (it->name() == name) {
			it->clear();
			it = m_child->erase(it);//删除后返回指向的是下一个，自动偏移。
		}
	}
```

