/*Owner : Ankan Bohara */

#include<bits/stdc++.h>

#define pb push_back
#define all(a) a.begin(),a.end()
#define cpresent(container,element) (find(all(container),element)!=container.end())
#define rep(i, a, b) 	for(int i = a; i < b; ++i)
using namespace std;

struct Bucket
{
	int ld=0;
	vector<int>a;
};
map<int,Bucket *>bmap;
int gd,bucket_capacity;
void display()
{
	rep(i,0,1<<gd)
	{
		/* code */
		cout<<"Local depth of the bucket is : "<<bmap[i]->ld<<"\n";
		for(auto j : bmap[i]->a)
			cout<<j<<" ";
		cout<<"\n";
	}
}

int search(int n)
{
	int h = n & ((1<<gd) - 1);
	return cpresent(bmap[h]->a,n);
}

void split(int sp_Index,Bucket * sp_Bucket)
{
	Bucket * newB = new Bucket;
	vector<int>temp;
	for(auto i : sp_Bucket->a)
	{
		temp.pb(i);
	}
	
	sp_Bucket->a.clear();
	
	if(sp_Bucket->ld == gd)
	{
		bmap[sp_Index ^ (1<<gd)] = newB;
		if(gd!=0)
		{
// 			for (int i = 0; i < (1<<gd); ++i)
			rep(i,0,1<<gd)
			{
				/* code */
				if(i!=sp_Index)
					bmap[i ^ (1<<gd)] = bmap[i];
			}
		}
		gd++;
		newB->ld = ++ sp_Bucket->ld;
		for(auto i : temp)
		{
			int h = i & ((1<<gd) -1);
			bmap[h]->a.pb(i);
		}
	}
	else
	{
		int k = sp_Index & (1<<(sp_Bucket->ld) - 1);
		vector<int>indices;
// 		for (int i = 0; i < (1<<gd); ++i)
		rep(i,0,1<<gd)
		{
			/* code */
			int last = i & (1<<(sp_Bucket->ld)) - 1;
			if(last==k)
				indices.pb(i);
		}
		newB->ld = ++sp_Bucket->ld;
// 		for (int i = indices.size()/2; i < indices.size(); ++i)
		rep(i, indices.size()/2, indices.size())
		{
			bmap[indices[i]] = newB;
		}

		for(auto i : temp)
		{
			int h = i & ((1<<gd) -1);
			bmap[h]->a.pb(i);
		}
	}

}
void insert(int n)
{
	int h = n & ((1<<gd) - 1);
	if(bmap[h]->a.size() < bucket_capacity)
		bmap[h]->a.pb(n);
	else
	{
		split(h,bmap[h]);
		insert(n);
	}
}

void merge()
{
	for(int i = 0; i<(1<<(gd-1));i++)
	{
		int h = i & ( ( 1<< ((bmap[i]->ld)-1) ) - 1);
		/*Current and Matched are pair of matching data buckets having ld-1 common suffix*/
		Bucket *curr = bmap[i];
		Bucket *matched = bmap[ i ^ (1<<(bmap[i]->ld-1)) ];
		if(curr != matched)
		{
			int sz = curr->a.size() + matched->a.size();
			if(sz <= bucket_capacity)
			{
				copy(all(matched->a),back_inserter(curr->a));
				vector<int>inds;
				for(auto i : bmap)
				{
					if(i.second==matched)
						inds.pb(i.first);
				}
				delete matched;
				for(auto j : inds)
					bmap[j] = bmap[i];
				bmap[i]->ld --;
			}
		}
	}
}

void shrink()
{
	set <Bucket *>buckets;
	for(auto i : bmap)
		buckets.insert(i.second);
	int count = 0;
	int sz = buckets.size();
	for(auto i : buckets)
		if ( (gd - (i->ld)) == 1)
			count++;
	if(count==sz)
		gd--;
}
void del(int n)
{
	if(search(n))
	{
		
		/*Deleting the entry */
		for(auto i : bmap)
		{
			auto it = find(all(i.second->a),n);
			if(it!=i.second->a.end())
			{
				i.second->a.erase(it);
				break;
			}
		}
		/*Merging the pair of data buckets if possible*/
		merge();

		/*If all the buckets have local depth less than global depth then shrink the directory*/
		shrink();

		cout<<"Number deleted successfully\n";
	}
	else
		cout<<"Element not found : \n";
}
void menu()
{
	int choice;
	int n;
	while(1)
	{
		cout<<"1. Insertion\n";
		cout<<"2. Deletion\n";
		cout<<"3. Display\n";
		cout<<"4. Search\n";
		cout<<"5. Exit\n";
		cout<<"--------------------\n";
		cout<<"Enter your choice : \n";
		cin>>choice;
		cout<<"--------------------\n";
		switch(choice)
		{
			case 1:
				cout<<"Enter the number to be inserted : \n";
				cin>>n;
				insert(n);
				cout<<"Number inserted successfully\n";
				break;
			case 2:
				cout<<"Enter the number to be deleted : \n";
				cin>>n;
				del(n);
				break;
			case 3:
				display();
				break;
			case 4:
				cout<<"Enter the number to be searched : \n";
				cin>>n;
				if(search(n))
					cout<<"Found\n";
				else
					cout<<"Not Found\n";
				break;
			case 5:
				exit(0);
			default:
				cout<<"Invalid choice !";
		}
	}
}
int main()
{
	cout<<"Enter bucket capacity : \n";
	cin>>bucket_capacity;
	bmap[0] = new Bucket;
	// insert(45);
	// insert(22);
	// insert(12);
	// insert(11);
	// insert(15);
	// insert(10);
	// insert()
	// display();
	// insert(22);
	menu();
}
