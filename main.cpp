#include <iostream>
#include "dysearch.h"
#include "closeHashTable.h"
#include "users.h"
#include <fstream>
#include <ctime>
#include <cstdlib>

#include <sys/time.h> //ͷ�ļ�
struct timeval startTime, endTime; //ʱ�����

using namespace std;



int fx(const long long int &x)
{
    int a=x;
    a=abs(a);
    return a;
}

int main()
{
    int m=4,n=2;
    cout<<"hash"<<m<<" "<<"solve"<<n<<endl;
    double diff;

    SET<long long int,user> a;
    ifstream fin1("hash1.txt");
    if(!fin1) {cout<<"cannot open"; return 1;}
    closeHashTable<long long int,user> tab1(m,n,50003,fx);

    gettimeofday (&startTime, NULL);

    for(int i=0;i<50000;i++)
    {
        fin1>>a.key>>a.other;
        tab1.insert(a);
    }

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    //cout<<"�ļ�1�Ĳ���ʱ��"<<diff<<endl;

    ifstream fin2("hash2.txt");
    if(!fin2) {cout<<"cannot open"; return 1;}
    closeHashTable<long long int,user> tab2(m,n,50003,fx);

    gettimeofday (&startTime, NULL);

    for(int i=0;i<50000;i++)
    {
        fin2>>a.key>>a.other;
        tab2.insert(a);
    }

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    //cout<<"�ļ�2�Ĳ���ʱ��"<<diff<<endl;

    SET<int,user> b;

    ifstream fin3("hash3.txt");
    if(!fin3) {cout<<"cannot open"; return 1;}
    closeHashTable<int,user> tab3(m,n,50003);

    gettimeofday (&startTime, NULL);

    for(int i=0;i<50000;i++)
    {
        fin3>>b.key>>b.other;
        tab3.insert(b);
    }

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    //cout<<"�ļ�3�Ĳ���ʱ��"<<diff<<endl;

    ifstream fin4("hash4.txt");
    if(!fin4) {cout<<"cannot open"; return 1;}
     closeHashTable<int,user> tab4(m,n,50003);

    gettimeofday (&startTime, NULL);

    for(int i=0;i<50000;i++)
    {
        fin4>>b.key>>b.other;
        tab4.insert(b);
    }

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    //cout<<"�ļ�4�Ĳ���ʱ��"<<diff<<endl;

    long long int x;
    int y;
    srand(time(NULL));

    gettimeofday (&startTime, NULL);

    for(int i=0;i<500;i++)
    {
        x=rand()%1000000000000000000;
        tab1.remove(x);
    }

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int i=0;i<500;i++)
    {
        x=rand()%1000000000000000000;
        tab2.remove(x);
    }

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<diff<<endl;

    gettimeofday (&startTime, NULL);

    for(int i=0;i<500;i++)
    {
        y=rand()%1000000;
        tab3.remove(y);
    }

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<diff<<endl;

     gettimeofday (&startTime, NULL);

    for(int i=0;i<500;i++)
    {
        y=rand()%1000000;
        tab4.remove(y);
    }

    gettimeofday(&endTime, NULL);
    diff = 1000000 * (endTime.tv_sec - startTime.tv_sec ) + endTime.tv_usec - startTime.tv_usec;
    cout<<diff<<endl;

    return 0;
}


