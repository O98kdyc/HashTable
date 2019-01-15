#ifndef SEQSTRING_H_INCLUDED
#define SEQSTRING_H_INCLUDED
#include <iostream>
using namespace std;

class seqstring
{
    friend seqstring operator+(const seqstring &s1,const seqstring &s2);
    friend bool operator==(const seqstring &s1,const seqstring &s2);
    friend bool operator!=(const seqstring &s1,const seqstring &s2);
    friend bool operator>(const seqstring &s1,const seqstring &s2);
    friend bool operator>=(const seqstring &s1,const seqstring &s2);
    friend bool operator<(const seqstring &s1,const seqstring &s2);
    friend bool operator<=(const seqstring &s1,const seqstring &s2);
    friend ostream &operator<<(ostream &os,const seqstring &s);

    private:
    char *data;
    int len;

    public:
    seqstring(const char *s="");
    seqstring(const seqstring &other);
    ~seqstring();
    int length()const;
    seqstring &operator=(const seqstring &other);
    seqstring substr(int start,int num)const;
    void insert(int start,const seqstring &s);
    void remove(int start,int num);
    void frequency();
    int find(const seqstring &sub) const;
    void replace(const seqstring&s1,const seqstring&s2);
};

seqstring::seqstring(const char *s)
{
    for(len=0;s[len]!='\0';++len);
    data=new char[len+1];

    for(len=0;s[len]!='\0';++len)
    {
        data[len]=s[len];
    }
    data[len]='\0';
}

seqstring::seqstring(const seqstring &other)
{
    data=new char[other.len+1];
    for(len=0;len<=other.len;++len)
    {
        data[len]=other.data[len];
    }
}

seqstring::~seqstring()
{
    delete data;
}

int seqstring::length()const
{
    return len;
}

seqstring &seqstring::operator=(const seqstring &other)
{
    if(this==&other) return *this;
    delete data;
    data=new char[other.len+1];
    for(len=0;len<=other.len;++len)
    data[len]=other.data[len];
    return *this;
}

seqstring seqstring::substr(int start,int num)const
{
    if(start>=len-1||start<0) return "";
    seqstring tmp;
    tmp.len=(start+num>len)?(len-start):num;
    delete tmp.data;
    tmp.data=new char[tmp.len+1];
    int i=0;
    for(i=0;i<num;++i)
    {
        tmp.data[i]=data[start+i];
    }
    tmp.data[i]='\0';
    return tmp;
}

void seqstring::insert(int start,const seqstring &s)
{
    char *tmp=data;
    int i;

    if(start>len||start<0) return;
    len+=s.len;
    data=new char[len+1];
    for(i=0;i<start;++i)
    {
        data[i]=tmp[i];
    }
    for(i=0;i<s.len;++i)
    {
        data[start+i]=s.data[i];
    }
    for(i=start;tmp[i]!='\0';++i)
    {
        data[i+s.len]=tmp[i];
    }
    data[i+s.len]='\0';
    delete tmp;
}

void seqstring::remove(int start,int num)
{
    if(start>=len-1||start<0) return;
    if(start+num>=len)
    {
        data[start]='\0';
        len=start;
    }
    else
    {
        for(len=start;data[len+num]!='\0';++len)
        {
            data[len]=data[len+num];
        }
        data[len]='\0';
    }
}

seqstring operator+(const seqstring &s1,const seqstring &s2)
{
    seqstring tmp;
    int i;

    tmp.len=s1.len+s2.len;
    delete tmp.data;
    tmp.data=new char[tmp.len+1];
    for(i=0;i<s1.len;++i)
    {
        tmp.data[i]=s1.data[i];
    }
    for(i=0;i<s2.len;++i)
    {
        tmp.data[i+s1.len]=s2.data[i];
    }
    tmp.data[s1.len+s2.len]='\0';
    return tmp;
}

bool operator==(const seqstring &s1,const seqstring &s2)
{
    if(s1.len!=s2.len) return false;
    for(int i=0;i<s1.len;++i)
    {
        if(s1.data[i]!=s2.data[i]) return false;
    }
    return true;
}

bool operator!=(const seqstring &s1,const seqstring &s2)
{
    return !(s1==s2);
}

bool operator>(const seqstring &s1,const seqstring &s2)
{
    for(int i=0;i<s1.len;++i)
          if(s1.data[i]>s2.data[i])
                return true;
          else if(s1.data[i]<s2.data[i])
                return false;
          return false;
}

bool operator>=(const seqstring &s1,const seqstring &s2)
{
    return(s1==s2||s1>s2);
}

bool operator<(const seqstring &s1,const seqstring &s2)
{
    return !(s1>=s2);
}

bool operator<=(const seqstring &s1,const seqstring &s2)
{
    return !(s1>s2);
}

ostream &operator<<(ostream &os,const seqstring &s)
{
    os<<s.data;
    return os;
};

void seqstring::frequency()
{
    int a[26]={0};
    for(int i=0;i<len;i++)
    {
        a[data[i]-'a']+=1;
    }
    double s=0;
    for(int i=0;i<26;i++) s+=a[i];
    for(int i=0;i<26;i++)
    {
        if(a[i]!=0)
        {
            double n=a[i]/s;
            cout<<char(i+'a')<<"Ƶ��"<<n<<" ";
        }
    }
}

int seqstring::find(const seqstring &sub) const
{
    int *p=new int [sub.len];
    int i, j;

    p[0]=-1;
    for(int i=1;i<sub.len;++i)
    {
        j=i-1;
        while(j>=0&&sub.data[p[j]+1]!=sub.data[i]) j=p[j];
        if(j<0) p[i]=-1;
        else p[i]=p[j]+1;
    }


i=j=0;
while(i<len&&j<sub.len)
{
    if(sub.data[j]==data[i]) {++i;++j;}
    else if(j==0) ++i;
    else j=p[j-1]+1;
}

delete []p;
if(j==sub.len) return i-j;
else return -1;
}

void seqstring::replace(const seqstring&s1,const seqstring&s2)
{
    while(find(s1)>=0)
    {
        int m=find(s1);
        remove(m,s1.len);
        insert(m,"#");
    }
    while(find("#")>=0)
    {
        int m=find("#");
        insert(m+1,s2);
        remove(m,1);
    }
}

#endif // SEQSTRING_H_INCLUDED
