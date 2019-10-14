# Signals And Slots C++14
A prototype of Signals & Slots system (unique from Qt implementations) that are used for the communication between objects or widgets (especially in GUI programming). The purpose of this project is for fun so a lot of cool C++ ¡°black magic¡± are used such as the template metaprogramming and macro expansion. This signals&slots implementation was achieved in less then 100 lines of c++ code.

## Usage:
**cd .../SignalAndSlot**

Write your own test in signalslottest.cpp file (optional)

**make**

Output is in the "out" file, so simply run

**./out** to see the result output

## What is Signals&Slots
(Although the implementation between my signals&slots and Qt's are different, their principles and applications are similar. So it is a good idea to put part of the Qt's official introductions here since it explains the concept pretty well.)

### Introduction
In GUI programming, when we change one widget, we often want another widget to be notified. More generally, we want objects of any kind to be able to communicate with one another. For example, if a user clicks a Close button, we probably want the window's close() function to be called.

Other toolkits achieve this kind of communication using callbacks. A callback is a pointer to a function, so if you want a processing function to notify you about some event you pass a pointer to another function (the callback) to the processing function. The processing function then calls the callback when appropriate. While successful frameworks using this method do exist, callbacks can be unintuitive and may suffer from problems in ensuring the type-correctness of callback arguments.

### Signals and Slots
A signal is emitted when a particular event occurs. Widgets have many predefined signals, but we can always subclass widgets to add our own signals to them. A slot is a function that is called in response to a particular signal. Widgets have many pre-defined slots, but it is common practice to subclass widgets and add your own slots so that you can handle the signals that you are interested in.

Signals are emitted by objects when they change their state in a way that may be interesting to other objects. This is all the object does to communicate. It does not know or care whether anything is receiving the signals it emits. This is true information encapsulation, and ensures that the object can be used as a software component.

Slots can be used for receiving signals, but they are also normal member functions. Just as an object does not know if anything receives its signals, a slot does not know if it has any signals connected to it.

You can connect as many signals as you want to a single slot, and a signal can be connected to as many slots as you need. It is even possible to connect a signal directly to another signal. (This will emit the second signal immediately whenever the first is emitted.)

Together, signals and slots make up a powerful component programming mechanism.

![Image of Qt](https://doc.qt.io/qt-5/images/abstract-connections.png)

### Signals
Signals are emitted by an object when its internal state has changed in some way that might be interesting to the object's client or owner. Signals are public access functions and can be emitted from anywhere, but we recommend to only emit them from the class that defines the signal and its subclasses.

When a signal is emitted, the slots connected to it are usually executed immediately, just like a normal function call. When this happens, the signals and slots mechanism is totally independent of any GUI event loop. Execution of the code following the emit statement will occur once all slots have returned. The situation is slightly different when using queued connections; in such a case, the code following the emit keyword will continue immediately, and the slots will be executed later.

If several slots are connected to one signal, the slots will be executed one after the other, in the order they have been connected, when the signal is emitted.

### Slots
A slot is called when a signal connected to it is emitted. Slots are normal C++ functions and can be called normally; their only special feature is that signals can be connected to them.

Since slots are normal member functions, they follow the normal C++ rules when called directly. However, as slots, they can be invoked by any component, regardless of its access level, via a signal-slot connection. This means that a signal emitted from an instance of an arbitrary class can cause a private slot to be invoked in an instance of an unrelated class.

Compared to callbacks, signals and slots are slightly slower because of the increased flexibility they provide, although the difference for real applications is insignificant. In general, emitting a signal that is connected to some slots, is approximately ten times slower than calling the receivers directly, with non-virtual function calls. This is the overhead required to locate the connection object, to safely iterate over all connections (i.e. checking that subsequent receivers have not been destroyed during the emission), and to marshall any parameters in a generic fashion. While ten non-virtual function calls may sound like a lot, it's much less overhead than any new or delete operation, for example. As soon as you perform a string, vector or list operation that behind the scene requires new or delete, the signals and slots overhead is only responsible for a very small proportion of the complete function call costs. The same is true whenever you do a system call in a slot; or indirectly call more than ten functions. The simplicity and flexibility of the signals and slots mechanism is well worth the overhead, which the users won't even notice.



## Example

```cpp
struct Object
{
	//signal for num
	void numChanged(int a,int b, int c)
	{
		cout << "emit num Signal!" << endl<<a<<b<<c<<endl;
	}
  
	void setNum(int a, int b, int c)
	{   
  		//will emit signal numchanged when call this function
		emitWithParam(numChanged,(a,b,c),(a,b,c));
	}
  	//slot for num
	int numSlot(int a,int b,int c) {
		cout << "parent num slot recieved!" << endl << a << b << c << endl;
		return 0;
	}
  	//signal for string
	void stringChanged(std::string s)
	{
		cout <<s<< " emit string Signal!" << endl;
	}
  
	void setString(std::string s)
	{
		//emit signal stringChanged when call this function
		emitWithParam(stringChanged,(s),(s));
	}
};

struct Child : public Object
{
  	//slot for string
	int stringSlot(std::string str)
	{
		cout << "child slot recieved! " << str << endl;
		return 0;
	}
};

	Object obj1;
	Object obj2;
	Child c1;
	
	//connect the signal numchanged in obj1 to the num slot in obj2
	connect(&obj1, &Object::numChanged, &obj2, &Object::numSlot);
  	//connect the signal stringChanged in the parent object obj2 to the child slot in c1 
	connect(&obj2, &Object::stringChanged, &c1, &Child::stringSlot);
	
  	//setNum  will emit signal numChanged and numSlot will recieve it and be called
	obj1.setNum(1,3,4);
  	//setString will emit stringChanged signal and stringSlot will recieve it and be called
	obj2.setString("whereamI");
```

