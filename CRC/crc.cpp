#include<iostream>
using namespace std;
class Poly
{
	private:
			int coeff; 
			int power; 
	public:
			Poly();
			Poly(int,int); 
			Poly(const Poly&);
			~Poly(); 
			void gettInput(int); 
			friend class L_List;  
};

class Node
{
	private:
			Poly *c; // To store Poly number
			Node *next; // Self-Referencing Pointer
	public:
			Node();
			void getInput(int); 
	friend class L_List; // L_List is also friend of this class
};

class L_List
{
	public:
		L_List(); // Constructor
		L_List(Node*);
		L_List(const L_List&);
		~L_List(); // Destructor
		int isEmpty(); // To check whether the list is Empty or Not
		void insertAtFirst(Node*); // Insertion based on requirement
		void Display(); // Display the List
	private:
		Node *first; // Address of first node
};
Poly::Poly()
{
	coeff=power=0;
}

Poly::Poly(int r,int i)
{
	coeff=r;
	power=i;
}

Poly::Poly(const Poly &c)
{
	coeff=c.coeff;
	power=c.power;
}

Poly::~Poly()
{
	coeff=0;
	power=0;
}

void Poly::gettInput(int i)
{
	cout<<"\nEnter the"<<(i+1)<<"bit:";
	cin>>coeff;
	power=i;
}

Node::Node()
{
	c=new Poly();
	next=NULL;
}

void Node::getInput(int i)
{
	c->gettInput(i);
}

L_List :: L_List()
{
	first = NULL; // Initially List is empty 
}

L_List :: L_List(Node *f)
{
	first = f; 
}

L_List :: L_List(const L_List&f)
{
	first = f.first; 
}

L_List :: ~L_List()
{
	first = NULL;
	delete first;
}

int L_List::isEmpty()
{
	if(first==NULL)
		return 1;
	else
		return 0;
}

void L_List::insertAtFirst(Node *n)
{
	if(isEmpty())
	{
		first=n;
		cout<<"Inserted As it is Empty.....\n";
	}
	else
	{
		n->next=first;
		first=n;
		cout<<"Inserted ...\n";
	}
}

void L_List::Display()
{
	Node *temp=first;
	if(isEmpty())
	{
		cout<<"List Empty .... Nothing to display\n";
		goto x;
	}
	while(temp->next!=NULL)
	{
		cout<<temp->c->coeff<<" ^ "<<temp->c->power<<" -> ";
		temp=temp->next;
	}
	cout<<temp->c->coeff<<" ^ "<<temp->c->power;
	x:
	cout<<"\n";
}

int main()
{
	int n1;
	L_List list;
	Node *n;
	cout<<"\nEnter the no of bits:";
	cin>>n1;
	for(int i=0;i<n1;i++)
	{
		n=new Node();
		n->getInput(i);
		list.insertAtFirst(n);				
	}
	cout<<"\nAfter Insertion,\n";
	list.Display();
	return 0;
}