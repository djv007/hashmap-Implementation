#include<bits/stdc++.h>
using namespace std;



template <typename V>
class MapNode
{
	public :
	string key;
	V value;
	MapNode* next;

	MapNode(string key , V value)
	{
		this->key = key;
		this->value = value;
		this->next = NULL;
	}

	~MapNode()
	{
		delete next;
	}
};

template<typename V>
class Ourmap
{
	public:
	MapNode<V>** BucketArray;
	int count;
	int numBuckets;

	Ourmap()
	{
		count = 0;
		numBuckets = 5;
		BucketArray = new MapNode<V>*[numBuckets];
		for(int i = 0 ; i < numBuckets;i++)
			BucketArray[i] = NULL;
		
	}

	~Ourmap()
	{
		for(int i = 0 ; i < numBuckets ; i++)
			delete BucketArray[i];
		delete []BucketArray;
	}

	int size()
	{
		return count;
	}

	V getValue(string key)
	{
		int BucketIndex = getBucketIndex(key);
		MapNode<V>* head = BucketArray[BucketIndex];
		while(head != NULL)
		{
			if(head->key == key)
			{
				return head->value;

			}
			head = head->next;
		}
		return 0; 
	}

	private :

	int getBucketIndex(string key)
	{
		int coefficient = 1;
		int  hashcode = 0;
		for(int i = key.size()-1;i>=0;i--)
		{
			hashcode += key[i]*coefficient;
			 hashcode %= numBuckets;
			coefficient *= 37;
			coefficient %= numBuckets;
		}
		return hashcode%numBuckets;
	}

	void rehashing()
	{
		MapNode<V>** temp = BucketArray;
		MapNode<V>** newArray = new MapNode<V>*[2*numBuckets];
		BucketArray = newArray;
		for(int i = 0 ; i < 2*numBuckets;i++)
			BucketArray[i] = NULL;
		int oldBucketSize = numBuckets;
		count = 0 ;
		numBuckets *=2;

		for(int i = 0 ; i < oldBucketSize ; i++)
		{
			MapNode<V>* head = temp[i];
			while(head != NULL)
			{
				string key = head->key;
				V value = head->value;
				insert(key , value);
				head = head->next;
			}
		}

		for(int i = 0 ; i < oldBucketSize ; i++)
		{
			MapNode<V>* head = temp[i];
			delete head;
		}
		delete [] temp; 

	}

	
	public:

		double getLoadFactor()
	{
		return (1.0*count)/numBuckets;
	}

	void insert(string key , V value)
	{
		int BucketIndex = getBucketIndex(key);
		MapNode<V>* head = BucketArray[BucketIndex];
		while(head != NULL)
		{
			if(head->key == key)
			{
				head->value = value;
				return ;
			}
			head =  head->next;
			
		}
		head = BucketArray[BucketIndex];
		MapNode<V>* newNode = new MapNode<V>(key , value);
		newNode->next = head;
		BucketArray[BucketIndex] = newNode;
		count++;

		if((1.0*count)/numBuckets > 0.7)
		{
			rehashing();
		}
	}

	V remove(string key)
	{
		int BucketIndex = getBucketIndex(key);
		MapNode<V>*head = BucketArray[BucketIndex];
		MapNode<V>* prev = NULL;
		while(head != NULL)
		{
			if(head -> key == key)
			{
				if(prev == NULL)
				{
					BucketArray[BucketIndex] = head->next;
				}
				else
				{
					prev->next = head->next;
				}
				V value = head->value;
				head->next = NULL;
				delete head;
				count--;
				return value;
			}
			prev = head;
			head= head->next;

		}
		return 0;
	}

};

int main()
{
	cout<<"Load factor determines how many nodes are there in one linked list where each node signifies a key in our hashmap , i have done rehashing after load factor reaches 0.7 , so this means  on an average there are less than 1 node in a linked list to make search , insert , delete operations in my hashmap in O(1) time\n";

	Ourmap<int>m;
	for(int i = 0 ; i < 10 ; i++)
	{
		string s = "abc";
		char c = '0' + i;
		m.insert(s+c , i+1);
		cout<<"\nCurrent Load factor after inserting  element no. "<<i+1<<"  : "<<m.getLoadFactor()<<endl;
	}
	cout<<"Key : "<<" Value : \n\n";
	for(int i = 0 ; i < 10 ; i++)
	{
		string s = "abc";
		char c = '0' + i;
		cout<<s+c<<"      "<<m.getValue(s+c)<<endl;

	}

	cout<<"No. of elements in the map  : "<<m.size()<<"\n";
	m.remove("abc1");
	m.remove("abc2");

	cout<<"No. of elements in the map after removing 2 elements  : "<<m.size()<<"\n";

	
	return 0;
}


/* 
Output of the above code is as follows :

Load factor determines how many nodes are there in one linked list where each node signifies a key in our hashmap , i have done rehashing after load factor reaches 0.7 , so this means  on an average there are less than 1 node in a linked list to make search , insert , delete operations in my hashmap in O(1) time

Current Load factor after inserting  element no. 1  : 0.2

Current Load factor after inserting  element no. 2  : 0.4

Current Load factor after inserting  element no. 3  : 0.6

Current Load factor after inserting  element no. 4  : 0.4

Current Load factor after inserting  element no. 5  : 0.5

Current Load factor after inserting  element no. 6  : 0.6

Current Load factor after inserting  element no. 7  : 0.7

Current Load factor after inserting  element no. 8  : 0.4

Current Load factor after inserting  element no. 9  : 0.45

Current Load factor after inserting  element no. 10  : 0.5
Key :  Value :

abc0      1
abc1      2
abc2      3
abc3      4
abc4      5
abc5      6
abc6      7
abc7      8
abc8      9
abc9      10
No. of elements in the map  : 10
No. of elements in the map after removing 2 elements  : 8

*/
