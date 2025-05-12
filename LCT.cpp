#include<bits/stdc++.h>
const int N=33e4,M=N*2;
#define l sn[0][u]
#define r sn[1][u]
#define dr(u) (sn[1][f[u]]==u)
#define nt(u) (sn[0][f[u]]==u||sn[1][f[u]]==u)
using namespace std;
int f[M],g[M],sm[M],sn[2][M],st[M];
bool rv[M];
void upd(int u)
{
	sm[u]=sm[l]+sm[r]+g[u];
	if(l)f[l]=u;if(r)f[r]=u;
}
void rev(int u)
{
	rv[u]^=1,swap(l,r);
}
void down(int u)
{
	if(rv[u])rev(l),rev(r),rv[u]=0;
}
void turn(int u)
{
	bool k=dr(u);
	int v=f[u];
	if(nt(v))sn[dr(v)][f[v]]=u;
	f[u]=f[v],sn[k][v]=sn[!k][u],
	upd(v),sn[!k][u]=v,
	upd(u);
}
void splay(int u)
{
	int v=u,tp;
	for(tp=0;nt(v);v=f[v])st[++tp]=v;
	for(st[++tp]=v;tp;--tp)down(st[tp]);
	while(nt(u))
	{
		if(nt(f[u]))
			if(dr(u)==dr(f[u]))turn(f[u]);
			else turn(u);
		turn(u);
	}
}
void access(int u)
{
	for(int v=0;u;v=u,u=f[u])
		splay(u),r=v,upd(u);
}
void make_root(int u)
{
	access(u),splay(u),rev(u);
}
void split(int u,int v)
{
	make_root(u),access(v),splay(v);
}
int find_root(int u)
{
	access(u),splay(u);
	while(l)down(u),u=l;
	splay(u);return u;
}
void link(int u,int v)
{
	make_root(u);
	if(find_root(v)!=u)
		f[u]=v;
}
void cut(int u,int v)
{
	split(u,v);
	if(sn[0][v]==u&&!l&&!r)
		sn[0][v]=f[u]=0;
}
#undef l
#undef r
#define up(a,b,c)for(int a=b;a<=c;++a)
int n,m,d[M],l[N],r[N],e[M];
set<pair<int,int>>S;
int main()
{
	cin>>n;
	up(i,1,n)cin>>l[i]>>r[i],d[m++]=l[i],d[m++]=r[i];
	sort(d,d+m),m=unique(d,d+m)-d;
	up(i,1,m)link(i,i+1),e[i]=i+1;
	up(i,1,n)
	{
		l[i]=lower_bound(d,d+m,l[i])-d+1,
		r[i]=lower_bound(d,d+m,r[i])-d+1;
		auto x=S.insert(make_pair(l[i],-r[i])).first;
		if(next(x)!=S.end()&&-next(x)->second<r[i])
			S.erase(x);
		else
		{
			while(x!=S.begin()&&-prev(x)->second>=r[i])
			{
				int j=prev(x)->first;
				cut(j,e[j]),link(j,e[j]=j+1),g[j]=0,S.erase(prev(x));
			}
			cut(l[i],e[l[i]]),link(l[i],e[l[i]]=r[i]+1),g[l[i]]=1;
		}
		split(m+1,1),cout<<sm[1]<<'\n';
	}
	return 0;
}