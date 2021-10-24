#include<iostream>
#include<string.h>

using namespace std;


string addition(string num1, string num2)
{

	int size1=num1.size()-1;
	int size2=num2.size()-1;
	string ans;

	int carry=0;

	while(size1>=0 && size2>=0)
	{
		int a=num1[size1]-'0';
		int b=num2[size2]-'0';

		string s= to_string((a+b+carry)%10);
		carry=(a+b+carry)/10;
		ans = s + ans;
		size1--;
		size2--;
	}

	while(size1>=0)
	{
		int a=num1[size1]-'0';
		string s= to_string((a+carry)%10);
		carry=(a+carry)/10;
		ans=s+ans;
		size1--;
	}
	while(size2>=0)
	{
		int a=num2[size2]-'0';
		string s= to_string((a+carry)%10);
		carry=(a+carry)/10;
		ans=s+ans;
		size2--;
	}
	if(carry)
		ans = "1" + ans; 

	while(ans[0]=='0' && ans.size()>1)
		ans.erase(ans.begin());

	return ans;
}

string subtraction(string num1,string num2)
{//num1-num2 num1>=num2
	int size1=num1.size()-1;
	int size2=num2.size()-1;
	string ans="";

	while(size1>=0 && size2>=0)
	{
		if(num1[size1]>=num2[size2])
		{	
			string s= to_string(num1[size1]-num2[size2]);
			ans=s+ans; 
		}
		else
		{
			char prev = num1[size1-1];
			num1[size1-1]= ((prev-'0')-1)+'0';			
			string s= to_string(10 + num1[size1]-num2[size2]);
			ans=s+ans; 
		}
		size1--;
		size2--;
	}
	while(size1>=0)
	{
		char s;
		if(num1[size1]-'0'<0)
		{
			char prev = num1[size1-1];
			num1[size1-1]= ((prev-'0')-1)+'0';			
			s=num1[size1]+10;
		}
		else
		{
			s=num1[size1];
		}
		ans=s+ans;
		size1--;
	}
	while(ans[0]=='0' && ans.size()>1)
		ans.erase(ans.begin());
	return ans;
}

void reverse(string &s)
{
	
	int start=0;
	int end=s.size()-1;
	char tmp;
	while(start<end)
	{
		tmp=s[start];
		s[start]=s[end];
		s[end]=tmp;
		start++;
		end--;
	}
}

string multiply(string num1,string num2)
{
	
	int size1=num1.size();
	int size2=num2.size();
	reverse(num1);
	reverse(num2);	

	
	string ans(num1.size() + num2.size(),'0');
	//cout<<ans<<endl;
	

	int i=0;//num2
	int j=0;//num1
	int carry=0;
	while(i<size2)
	{
		j=0;
		carry=0;
		while(j<size1)
		{
			int tmp= (num1[j]-'0')*(num2[i]-'0') + (ans[(i+j)] - '0') + carry;
			char s=(tmp%10)+'0';
			ans[(i+j)]=s;
			carry=(tmp/10);
			j++;
		}
		if(carry)
		{
			ans[(i+j)]=( carry + '0');
		}
		i++;
	}
	reverse(ans);
	while(ans[0]=='0' && ans.size()>1)
		ans.erase(ans.begin());

	return ans;
}

string power(string num,long long int pow)
{
	string ans="1";

		while(pow>0)
		{
			if(pow&1)
				ans=multiply(ans,num);
			pow=pow>>1;
			num=multiply(num,num);
		}
	return ans;
}
string factorial(string num)
{
	string ans="1";

	while(num!="0")
	{
		ans = multiply(ans,num);
		num = subtraction(num,"1"); 
	}
	return ans;

}

bool temp(string a,string b)
{
	int s1=a.size();
	int s2=b.size();

	if(s1<s2)
	{	
		while(a.size() < s2)
		a.insert(0,"0");	
	}
	else
	{	
		while(b.size() < s1)
		b.insert(0,"0");	
	}

if(a>b)
	return true;

return false;

}
bool mycompare(string &a,string &b)
{
	int s1=a.size();
	int s2=b.size();

	int os1=s1;
	int os2=s2;
	string lastStr;
	
	if(s1<s2)
	{	
			
		while(a.size()+1 < s2)
		a+='0';

		lastStr=b;

		while(a.size()>os1+1)
		{
			while(!temp(b,a))//b>a	
			{
				a.erase(a.end()-1);
			}

			lastStr=b;
			//cout<<b<<"-"<<a<<endl;
			b = subtraction(b,a);
			

		}
		//cout<<lastStr<<"##"<<b<<endl;
		b=lastStr;
		while(a.size()>os1)
			a.erase(a.end()-1);
		
	}
	else
	{	

		while(b.size()+ 1 < s1)
			b+='0';	

		lastStr=a;

		while(b.size()>os2+1)
		{
			while(!temp(a,b))//a>b	
			{
				b.erase(b.end()-1);
			}

			lastStr=a;
			//cout<<a<<"-"<<b<<endl;
			a = subtraction(a,b);
			
			

		}
		//cout<<lastStr<<"##"<<a<<endl;
		a=lastStr;

		while(b.size()>os2)
			b.erase(b.end()-1);
	}

	//cout<<a<<"===="<<b<<endl;
	
	return true;

}
string gcd(string num1,string num2)
{
	int size1=num1.size();
	int size2=num2.size();
	string ans;

	mycompare(num1,num2);


	int cnt=0;
	while(num1!=num2)
	{

		if(temp(num1,num2))
		{
			num1=subtraction(num1,num2);
		}
		else
		{
			num2=subtraction(num2,num1);
		}
		//cout<<num1<<" "<<num2<<endl;

		if(num1=="0")
			{ans=num2;break;}
		if(num2=="0")
			{ans=num1;break;}

	}
	if(num1==num2)
		ans=num1;

	while(ans[0]=='0' && ans.size()>1)
		ans.erase(ans.begin());
	return ans;

}

int precedence(char a)
{
	if(a=='+' || a=='-')
		return 1;
	else if(a=='x')
		return 2;
	return 0;
}
string calculator(string exp)
{
	string post[10000];
	char stack[10000];
	int stop=-1;
	int ptop=0;

	string tmp="";
	int len = exp.size();
	for(int i=0;i<len;i++)
	{
		if(exp[i]!='+' && exp[i]!='x' && exp[i]!='-'  )
		{
			tmp+=exp[i];
		}
		else
		{	
			post[ptop]=tmp;
			ptop++;
			tmp.clear();
			if(stop==-1 || precedence(exp[i])>precedence(stack[stop]))
			{
				stop++;
				stack[stop]=exp[i];
			}
			else
			{
				post[ptop]=stack[stop];
				stop--;
				ptop++;

				stop++;
				stack[stop]=exp[i];

			}

		}

	}
	post[ptop]=tmp;
	ptop++;
	
	while(stop>=0)
	{
		post[ptop]=stack[stop];
		ptop++;
		stop--;
	}
<<<<<<< HEAD

	
	
	for(int i=0;i<ptop;i++)
	{
		cout<<post[i]<<"";
	}
	cout<<endl;
	
=======
	/*
	for(int i=0;i<ptop;i++)
	{
		cout<<post[i]<<" ";
	}
	cout<<endl;
	*/
>>>>>>> c959ee2d750d69eaa55b39abe42a674527c2d501
	//====================evaluating post fix exp present in post
	string eval[10000];
	string stack1[10000];
	int stop1=-1;
	for(int i=0;i<ptop;i++)
	{
<<<<<<< HEAD
		cout<<post[i]<<"#"<<endl;
		if(stop1==-1 || (post[i]!="+" && post[i]!="-" && post[i]!="x") )
=======
		if(stop1==-1 || (post[i]!="+" && post[i]!="-" && post[i]!="*") )
>>>>>>> c959ee2d750d69eaa55b39abe42a674527c2d501
		{
			stop1++;
			stack1[stop1]=post[i];
		}
		else
		{	
<<<<<<< HEAD
			

=======
>>>>>>> c959ee2d750d69eaa55b39abe42a674527c2d501
			string l,r;
			l=stack1[stop1];
			stop1--;
			r=stack1[stop1];
			stop1--;

			if(post[i]=="+")
			{
				stop1++;
				stack1[stop1]=addition(l,r);
			}
			else if(post[i]=="-")
			{
<<<<<<< HEAD
				cout<<"->"<<l<<"-"<<r<<endl;
				stop1++;
				stack1[stop1]=subtraction(r,l);
=======
				stop1++;
				stack1[stop1]=subtraction(l,r);
>>>>>>> c959ee2d750d69eaa55b39abe42a674527c2d501
			}
			else if(post[i]=="x")
			{
				stop1++;
				stack1[stop1]=multiply(l,r);
			}

<<<<<<< HEAD
			
			

		}
		
=======
		}
>>>>>>> c959ee2d750d69eaa55b39abe42a674527c2d501
	}

	return stack1[stop1];
}


int main()
{
	string a,b;
	long long int p;
	//cin>>a>>b;
	int t;
	cin>>t;

	switch(t)
	{	//case 4 calculator
		
		case 1: cin>>a;cin.ignore();cin>>p;cout<<power(a,p);break;
		case 2: cin>>a>>b;cout<<gcd(a,b);break;
		case 3: cin>>a;cout<<factorial(a);break;
		case 4: cin>>a;cout<<calculator(a);break;
		default: return 0;
	}
	

	return 0;
}
