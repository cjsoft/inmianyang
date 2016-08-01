#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 105000;
struct node
{
    int wei;
    int zhi;
}xu[N];
int n,m;
int cc;
int res[N],place[N];
int getint()
{
    int res=0;
    char e=getchar();
    while(e<'0' || e>'9')
        e=getchar();
    while('0'<=e && e<='9')
    {
        res=res*10+e-'0';
        e=getchar();
    }
    return res;
}
bool cmp(struct node x,struct node y)
{
    if(x.zhi<y.zhi)
        return 1;
    if(x.zhi>y.zhi)
        return 0;
    return (x.wei<y.wei);
}
void f()
{
    int i,j,k;
    for(i=1;i<=n;i++)
    {
        xu[i].zhi=getint();
        xu[i].wei=i;
    }
    sort(xu+1,xu+n+1,cmp);
    cc=0;
    res[cc]=0;
    place[cc]=987654321;
    for(i=1;i<=n;i++)
    {
        int s=i;
        while(i<n && xu[i].zhi==xu[i+1].zhi)
            i++;
        res[cc+1]=987654321;
        for(k=cc;k>=0;k--)
        {
            int a,b;
            for(j=i;j>=s;j--)
            {
                if(xu[j].wei<place[k])
                    break;
            }
            j++;
            if(j<=i)
            {
                a=res[k];
                b=xu[j].wei;
            }
            else
            {
                a=res[k]+1;
                b=xu[s].wei;
            }
            if(a<res[k+1])
            {
                res[k+1]=a;
                place[k+1]=b;
            }
            else if(a==res[k+1] && b<place[k+1])
            {
                res[k+1]=a;
                place[k+1]=b;
            }
        }
        cc++;
    }
    for(i=0;i<=cc;i++)
    {
        if(res[i]>m)
            break;
    }
    i--;
    printf("%d\n",i);
}
int main()
{
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
    n=getint();
    m=getint();
    m=getint();
    f();
    return 0;
}
