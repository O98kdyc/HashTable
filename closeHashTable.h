#ifndef CLOSEHASHTABLE_H_INCLUDED
#define CLOSEHASHTABLE_H_INCLUDED
#include "dysearch.h"
template <class KEY, class OTHER>
class closeHashTable:public dynamicSearchTable<KEY, OTHER>
{
 private:
      struct node
    { //散列表的结点类
        SET <KEY, OTHER>  data;
		    int  state;  //0 -- empty   1 -- active   2 -- deleted
		    node() {state = 0;}
	  };
      node *array;
      int  size;
      int (*key)(const KEY &x);
      int (closeHashTable::*hash)(int x);
      int (closeHashTable::*solve)(int pos,int n);
      static int defaultKey(const int &x) {return x;}
      int hash1(int x);
      int hash2(int x);
      int hash3(int x);
      int hash4(int x);
      int solve1(int pos,int n);
      int solve2(int pos,int n);
      int h,s;
  public:
     closeHashTable(int y=1,int z=1,int length = 101,int (*f)(const KEY &x) = defaultKey);
     ~closeHashTable() {delete [] array;}
     SET<KEY, OTHER> *find(const KEY &x);
      void insert(const SET<KEY, OTHER> &x);
      void remove(const KEY &x) ;
};

template <class KEY, class OTHER>
closeHashTable<KEY,OTHER>::closeHashTable(int y,int z,int length,int (*f)(const KEY &x))
{
	size = length;
	array = new node[size];
	key = f;
	h=y;
	s=z;
  switch(y)
  {
    case 1:hash=&closeHashTable::hash1;break;
    case 2:hash=&closeHashTable::hash2;break;
    case 3:hash=&closeHashTable::hash3;break;
    case 4:hash=&closeHashTable::hash4;break;
  }
  switch(z)
  {
    case 1:solve=&closeHashTable::solve1;break;
    case 2:solve=&closeHashTable::solve2;break;
  }
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const SET<KEY, OTHER> &x)
{
	   int initPos, pos,n=1 ;
	   initPos = pos =(this->*hash)(key(x.key));
	   //cout<<x.key<<" "<<key(x.key)<<" "<<pos<<" ";
	   //cout<<initPos<<" ";
	   do {
         if (array[pos].state != 1)
              {       // 找到空单元
                   array[pos].data = x;
                   array[pos].state = 1;
                   //cout<<endl;
                   //cout<<pos<<endl;
                   return;
              }
	       //pos = (pos+1) % size;
	       //cout<<pos<<" ";
         pos=(this->*solve)(pos,n);
         n+=1;
       } while (pos != initPos);
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x)
{
	   int initPos, pos,n=1 ;
	   initPos = pos = (this->*hash)(key(x));
        do
       {
          if (array[pos].state == 0) return;
 	        if (array[pos].state == 1 && array[pos].data.key == x)
          {  // 找到，删除
		      array[pos].state = 2;
		      return;
	        }
	        //pos = (pos+1) % size;
          pos=(this->*solve)(pos,n);
          n+=1;
       } while (pos != initPos);
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *closeHashTable<KEY, OTHER>::find(const KEY &x)
{
 	    int initPos, pos,n=1 ;
        initPos = pos = (this->*hash)(key(x));
        //cout<<initPos<<endl;
         do
        {
            if (array[pos].state == 0) return NULL;     // 没有找到
	          if (array[pos].state == 1 && array[pos].data.key == x)    // 找到
                      return (SET<KEY,OTHER> *)&array[pos];
	          //pos = (pos+1) % size;
            pos=(this->*solve)(pos,n);
            //cout<<pos<<endl;
            n+=1;
        } while (pos != initPos);
        return NULL;
}

template <class KEY, class OTHER>
int closeHashTable<KEY, OTHER>::hash1(int x)
{
   return x%size;
}

template <class KEY, class OTHER>
int closeHashTable<KEY, OTHER>::hash2(int x)
{
  int len1=0,len2=0,i=size,k=0;
  while(i>=1) {len1++; i/=10;} //计算size的位数
  int y=x,j=y;
  while(j>=1) {len2++;j/=10;}
  //取len2的中间len1位数
 for(int m=0;m<(len2-len1)/2;m++) y/=10;
 for(int m=0;m<len1;m++)
 {
   int p=1;
   for(int i=0;i<m;i++) p*=10;
   k+=p*(y%10);
   y/=10;
 }
 return k%size;
}

template <class KEY, class OTHER>
int closeHashTable<KEY, OTHER>::hash3(int x)
{
   int len1=0,len2=0,i=size,k=0;
   while(i>=1) {len1++; i/=10;} //计算size的位数
   int y=x*x,j=y;
   while(j>=1) {len2++;j/=10;}
   //取len2的中间len1位数
  for(int m=0;m<(len2-len1)/2;m++) y/=10;
  for(int m=0;m<len1;m++)
  {
    int p=1;
    for(int i=0;i<m;i++) p*=10;
    k+=p*(y%10);
    y/=10;
  }
  k=abs(k);
  return k%size;
}

template <class KEY, class OTHER>
int closeHashTable<KEY, OTHER>::hash4(int x)
{
   //判断折叠的位数
   int len1=0,len2=0,i=size,j=x,k=0,m=1,y=x;
   while(j>=1) {len2++; j/=10;}  //计算x的位数
   while(i>=1) {len1++; i/=10;}  //计算size的位数
   //按len1位折叠
   for(int i=0;i<len1;i++) m*=10; //m为10的len1次方
   for(int i=0;i<len2/len1+1;i++)
   {
      k+=y%m;
      y/=m;
   }
   k=k%m;
   return k%size;
}

template <class KEY, class OTHER>
int closeHashTable<KEY, OTHER>::solve1(int pos,int n)
{
  return (pos+1)%size;
}

template <class KEY, class OTHER>
int closeHashTable<KEY, OTHER>::solve2(int pos,int n)
{
  return (pos+2*n-1)%size;
}

#endif // CLOSEHASHTABLE_H_INCLUDED
