#include <clocale>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;
typedef int *pInt;
class prog
{
	private:
		int n;
		char filename[20];
		pInt *A;
		pInt *B;
		vector <int> mas;
		vector <bool> used;
		int k,m;
		vector<vector<int> > g;
		struct list
		{
  			int in,out;
  			struct list *next;
  			struct list *prev;
		};
		list *lst;
	public:
		void getgraf();
		void spissmez();
		void dfs(int start,int curr, vector <int> mass, vector <bool> us);
		void seek();
		void printmas();
		void plusver();
		void minusver();
		void plusdug();
		void minusdug();
		int proverka();
		void izmdug();
		void work();
		void deldug(int in1,int out1);
		void listprint(list *lst);
		struct list * init(int a,int b)
		{
  			struct list *lst;
  			lst = (struct list*)malloc(sizeof(struct list));
  			lst->in = a;
  			lst->out = b;
  			lst->next = NULL;
  			lst->prev = NULL;
  			return(lst);
		}
		struct list * addelem(list *lst, int a,int b)
		{
			struct list *temp, *p;
			temp = (struct list*)malloc(sizeof(list));
			p = lst->next;
			lst->next = temp;
			temp->in = a; 
			temp->out = b; 
			temp->next = p;
			temp->prev = lst;
			if (p != NULL)
    			p->prev = temp;
			return(temp);
		}
		prog()
		{
			n=0;
		}
		~prog()
		{
			delete[]A;
			g.clear();
		}
};

void prog::getgraf()
{
	cout<<"Введите название файла, в котором содержится граф"<<endl;
	cin>>filename;
	ifstream file(filename);
	if (file.is_open())
	{
		int h,t,w;
		string ch;
		while(getline(file,ch))
		{
			if (ch=="#") break;
			n++;
		}
		file.close();
		A =new pInt[n];
		for (int i=0;i<n;i++)
		{
			A[i] =new int[n];
			for (int j=0;j<n;j++)
				A[i][j]=0;
		}
		ifstream file(filename);
		getline(file,ch,'#');
		file>>h&&file>>t&&file>>w;
		lst=init(h,t);
		A[h-1][t-1]=w;
		while (file>>h&&file>>t&&file>>w) 
		{
			A[h-1][t-1]=w;
			addelem(lst,h,t);
		}
		file.close();
		spissmez();
		work();
	}
	else
	{
		perror(filename);
	}
}

void prog::spissmez()
{
	g.clear();
	g.resize(n);
		for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
			{
				if (A[i][j]!=0) 
				g[i].push_back(j);
			}
		}
} 

void prog :: dfs (int start,int curr,vector <int> mass, vector <bool> us) 
{
	if ((start==curr)&&((mass.empty())==0))
	{
		if (mass.size()==k)
		{
			for (int l=0;l<mass.size();l++)
			{
				cout<<mass[l]+1<<"->";
			}
			cout<<start+1;
			cout<<endl;
			m++;
			return;
		}
	}
	if (us[curr]==1) return;
	vector <int> p=g[curr];
	mass.push_back(curr);
	us[curr]=1;
	for (int l=0;l<p.size();l++)
	{
		dfs(start,p[l],mass,us);
	}
}

void prog::seek()
{
	m=0;
	cout<<endl<<"Введите длину искомых циклов - ";
	cin>>k;
	for (int i=0;i<n;i++)
	{
		used.resize(n);
		mas.resize(0);
		for (int j=0;j<n;j++)
		{
			used[j]=false;
		}
		dfs(i,i,mas,used);
	}
	if (m==0) cout<<"Циклов длиной "<<k<<" не существует"<<endl;
}

void prog :: printmas()
{
	cout<<endl<<"Матрица весов:"<<endl;
	for (int i=0;i<n;i++)
		{
			for (int j=0;j<n;j++)
			{
				cout<<A[i][j]<<' ';	
			}
			cout<<endl;
		}
}

void prog::listprint(list *lst)
{
  	struct list *p;
 	p = lst;
 	cout<<endl<<"Список дуг графа:"<<endl;
  	do 
	{
   		cout<<p->in<<"->"<<p->out<<endl;
   		p = p->next;
  	}
	while (p != NULL);
}

void prog::plusver()
{
	n=n+1;
	B=new pInt[n];
		for (int i=0;i<n;i++)
		{
			B[i] =new int[n];
		}
	for (int i=0;i<n-1;i++)
		{
			for (int j=0;j<n-1;j++)
				B[i][j]=A[i][j];
		}
	delete []A;
	A=new pInt[n];
		for (int i=0;i<n;i++)
		{
			A[i] =new int[n];
			for (int j=0;j<n;j++)
				A[i][j]=B[i][j];
		}
	for (int i=0;i<n;i++)
		{
			A[n-1][i]=0;
		}
	for (int i=0;i<n;i++)
		{
			A[i][n-1]=0;
		}
	g.resize(n);
	cout<<"Вершина "<<n<<" добавлена"<<endl;
	delete []B;
}

void prog::minusver()
{
	int v;
	bool s=false;
	while (s==false)
	{
		cout<<endl<<"Введите вершину, которую хотите удалить - ";
		v=proverka();
    	if ((v<=0)||(v>n)) 
		{
			cout<<"Эту вершину нельзя удалить, так как она отсутствует"<<endl;
		}
		else if(v<n)
		{
			for (int i=v-1;i<n-1;i++)
			{
				for (int j=0;j<n;j++)
					A[i][j]=A[i+1][j];
			}
			for (int i=v-1;i<n-1;i++)
			{
				for (int j=0;j<n;j++)
					A[j][i]=A[j][i+1];
			}
			for (int i=v-1;i<n-1;i++)
			{
				g[i]=g[i+1];
			}
			s=true;
			n--;
			spissmez();
		}
		else if (v=n)
		{
			for (int i=0;i<n;i++)
			{
				A[v-1][i]=0;
			}
			for (int i=0;i<n;i++)
			{
				A[i][v-1]=0;
			}
			s=true;
			n--;
			spissmez();
		}
	}
	B=new pInt[n];
	for (int i=0;i<n;i++)
		{
			B[i] =new int[n];
			for (int j=0;j<n;j++)
				B[i][j]=A[i][j];
		}
	delete []A;
	A=new pInt[n];
		for (int i=0;i<n;i++)
		{
			A[i] =new int[n];
			for (int j=0;j<n;j++)
				A[i][j]=B[i][j];
		}
	delete []B;
	cout<<endl<<"Вершина "<<v<<" удалена. Нумерация вершин изменена."<<endl;
}

void prog::plusdug()
{
	int e,r,w;
	bool prov=false;
	cout<<endl<<"Введите начало добавляемой дуги - ";
	do
	{
		e=proverka();
		if ((e<=0)||(e>n)) 
		{
			cout<<"Эту вершину нельзя использовать, так как она отсутствует. Попробуйте ещё раз - ";
		}
		else prov=true;
	} while (prov!=true);
	prov=false;
	cout<<endl<<"Введите конец добавляемой дуги - ";
	do
	{
		r=proverka();
		if ((r<=0)||(r>n)) 
		{
			cout<<"Эту вершину нельзя использовать, так как она отсутствует. Попробуйте ещё раз - ";
		}
		else prov=true;
	} while (prov!=true);
	prov=false;
	if (A[e-1][r-1]!=0) 
	{
		cout<<"Такая дуга уже существует"<<endl;
	}
	else if (A[r-1][e-1]!=0) 
	{
		cout<<"Уже существует обратная дуга"<<endl;
	}
	else if (r==e) 
	{
		cout<<"Нельзя создавать петлю"<<endl;
	}
	else
	{
		cout<<endl<<"Введите вес добавляемой дуги - ";
		do
		{
			w=proverka();
			if ((w<=0)) 
			{
				cout<<"Вес не может быть отрицательным или нулевым. Попробуйте ещё раз - ";
			}
			else prov=true;
		} while (prov!=true);
		prov=false;
		A[e-1][r-1]=w;
		addelem(lst,e,r);
		g[e-1].push_back(r-1);
		cout<<endl<<"Дуга "<<e<<"->"<<r<<" добавлена"<<endl;
	}
}

void prog::minusdug()
{
	int e,r;
	bool prov=false;
	cout<<endl<<"Введите начало удаляемой дуги - ";
	do
	{
		e=proverka();
		if ((e<=0)||(e>n)) 
		{
			cout<<"Эту вершину нельзя использовать, так как она отсутствует. Попробуйте ещё раз - ";
		}
		else prov=true;
	} while (prov!=true);
	prov=false;
	cout<<endl<<"Введите конец удаляемой дуги - ";
	do
	{
		r=proverka();
		if ((r<=0)||(r>n)) 
		{
			cout<<"Эту вершину нельзя использовать, так как она отсутствует. Попробуйте ещё раз - ";
		}
		else prov=true;
	} while (prov!=true);
	prov=false;
	if (A[e-1][r-1]==0) 
	{
		cout<<"Эту дугу нельзя удалить, так как она отсутствует"<<endl;
	}
	else
	{
		A[e-1][r-1]=0;
		deldug(e,r);
		spissmez();
		cout<<endl<<"Дуга "<<e<<" ->"<<r<<" удалена"<<endl;
	}
}

void prog:: deldug(int in1,int out1) 
{
	if (lst == NULL) { return;}
	list* tmp = lst;
	list* prev = NULL;
	do {
		if ((tmp->in == in1)&&(tmp->out==out1)) 
		{
			if (tmp == lst && tmp->next == NULL) { lst = NULL; return; }
			if (tmp == lst && tmp->next != NULL) { lst = tmp->next; return; }
			if (prev != NULL && tmp->next != NULL) { prev->next = tmp->next; return; }	
			if (prev != NULL && tmp->next == NULL) { prev->next = NULL; return; }
		}
		prev = tmp;
		tmp = tmp->next;
	} while (tmp != NULL);
	return;
}

void prog::izmdug()
{
	int e,r,w,q;
	bool prov=false;
	cout<<endl<<"Введите начало изменяемой дуги - ";
	do
	{
		e=proverka();
		if ((e<=0)||(e>n)) 
		{
			cout<<"Эту вершину нельзя использовать, так как она отсутствует. Попробуйте ещё раз - ";
		}
		else prov=true;
	} while (prov!=true);
	prov=false;
	cout<<endl<<"Введите конец изменяемой дуги - ";
	do
	{
		r=proverka();
		if ((r<=0)||(r>n)) 
		{
			cout<<"Эту вершину нельзя использовать, так как она отсутствует. Попробуйте ещё раз - ";
		}
		else prov=true;
	} while (prov!=true);
	prov=false;
	if (A[e-1][r-1]==0) 
	{
		cout<<"С это дугой нельзя работать, так как она не существует"<<endl;
	}
	else
	{
		cout<<endl<<"1. Изменить вес дуги"<<endl<<"2. Изменить направление дуги"<<endl;
		cout<<"Введите номер желаемого действия - ";
		q=proverka();
		switch (q)
		{
			case 1:
				cout<<endl<<"Введите новый вес для дуги - ";
				do
				{
					w=proverka();
					if ((w<=0)) 
					{
						cout<<"Вес не может быть отрицательным или нулевым. Попробуйте ещё раз - ";
					}
					else prov=true;
				} while (prov!=true);
				A[e-1][r-1]=w;
				cout<<endl<<"Дуга изменена"<<endl;
				break;
			case 2:
				A[r-1][e-1]=A[e-1][r-1];
				A[e-1][r-1]=0;
				deldug(e,r);
				addelem(lst,r,e);
				spissmez();
				cout<<endl<<"Дуга изменена"<<endl;
				break;
			default:
	   			cout<<"Такого действия нет"<<endl;
	    		break;
		}
	}
}

int prog::proverka()
{
char str[100];
bool chis=true;
	do
	{
		cin>>str;
		for (int i=0; str[i]!='\0'; i++)
		if (str[i]<48 || str[i]>57) {cout<<"Неверный ввод, Поробуйте ещё раз - "; chis=false; break;}
		else chis=true;
	}
	while (chis!=true);
	return atoi(str);
}

void prog::work()
{
	int f;
	do
		{
			cout<<endl<<"1. Напечатать матрицу весов графа"<<endl<<"2. Напечатать список дуг графа"<<endl<<"3. Найти в графе циклы определённой длины"<<endl;
			cout<<"4. Добавить к графу вершину"<<endl<<"5. Удалить из графа вершину"<<endl<<"6. Добавить в граф дугу"<<endl;
			cout<<"7. Убрать из графа дугу"<<endl<<"8. Изменить дугу в графе"<<endl<<"0. Окончить работу"<<endl;
			cout<<"Введите номер желаемого действия - ";
			f=proverka();
			switch (f)
			{
				case 1:
					printmas();
					break;
				case 2:
					listprint(lst);
					break;
				case 3:
					seek();
					break;
				case 4:
					plusver();
					break;
				case 5:
					minusver();
					break;
				case 6:
					plusdug();
					break;
				case 7:
					minusdug();
					break;
				case 8:
					izmdug();
					break;
				default:
	     			if (f!=0) cout<<"Такого действия нет"<<endl;
	     			break;
			}
		} 
		while(f!=0);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	prog *graf=new prog();
	graf->getgraf();
}
