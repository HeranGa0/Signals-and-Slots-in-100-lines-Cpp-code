#include "signalslot.h"

struct Object
{
	//signal for num
	void numChanged(int a,int b, int c)
	{
		cout << "emit num Signal!" << endl;
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
int main()
{
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
	return 0;
}
