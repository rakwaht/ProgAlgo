using namespace std;
#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include<queue>
#include<cstring>
#include <algorithm>

struct nodo{
	int val;
	char c;
	int indici[2];	
};

int N,M,T;
int ** tab;
int ** m;
vector < pair<int,char> > v;
vector < vector < pair <int,char> > > vettori;
vector < nodo > grafo;
vector <int> valori;

int check_row(int indice,int t);
int sol();
int calcola(int,int);
void raggruppa(string s);
void init_grafo(int indice);
int visita(int i,int j);
int chiama_visita(int j);
void itera(int indice);
void rec(int j,int i,int sum);

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	in >> N >> M >> T;
	T += 1;
	tab = new int * [N];
	for(int i=0; i<N; i++){
		tab[i] = new int [T];
	}	

	for(int i=0; i<N; i++){
		string buffer;
		in >> buffer;
		v.clear();
		raggruppa(buffer);
		vettori.push_back(v);
	}
	

	sol();
	/*for(int k=0; k<N; k++){
		init_grafo(k);
		itera(k);
		for(int h=0; h<vettori[k].size(); h++){
			cout << vettori[k][h].second << vettori[k][h].first << " ";
		}
		cout << endl;
		for(int i=0; i<valori.size(); i++){
			cout << valori[i] << " ";
		}
		cout << endl;
	}
	//cout << "res:" << check_row(3,3) << endl;
	/for(int i=0; i<N; i++){
		for(int j=0; j<T; j++){
			cout << tab[i][j] << " " ;
		}
		cout << endl;
	}*/

	out << tab[N-1][T-1];
	return 0;
}

int check_row(int indice,int t){
	int cont=0;
	int temp;	
	if(t>=vettori[indice].size()){
		temp = M;
	}
	else if(t==0) return 0;
	else{
	//temp = chiama_visita(t);
	temp = valori[t];
	}
	return temp;
}

int sol(){
	//base
	int last;
	init_grafo(0);
	itera(0);
	for(int i=0; i<=vettori[0].size() && i<T; i++){
		tab[0][i] = check_row(0,i);
		last = tab[0][i]; 
	}
	for(int j=(vettori[0].size()+1); j<T; j++){
			tab[0][j] = last;
		}
	int i=1;
	int max_size = vettori[0].size() + vettori[1].size();
	while(i<N){
		init_grafo(i);
		itera(i);
		/*for(int p=0; p<grafo.size(); p++){
		cout << grafo[p].c << " " << grafo[p].val << " " << grafo[p].indici[0] << " " << grafo[p].indici[1] << endl;
	}*/
		for(int j=0;j<=max_size && j<T;j++){
			tab[i][j] = calcola(i,j);
			last = tab[i][j];
		}
		for(int j=(max_size+1); j<T; j++){
			tab[i][j] = last;
		}
	 i++;
	 max_size += vettori[i].size();
	}
	return 0;	
}

int calcola(int i, int j){
	int max=0;
	int indice = j;
	for(int k=0; k<=j; k++,indice--){
		int temp = check_row(i,indice)+tab[i-1][k];
		if(temp>max)max = temp;
	}
	return max;
}


void init_grafo(int indice){
	grafo.clear();
	nodo t;
	t.val=0;
	t.c='a';
	if(1<vettori[indice].size()) t.indici[0]=1;
	else{t.indici[0]=-1;}
	if(2<vettori[indice].size()) t.indici[1]=2;
	else{t.indici[1]=-1;}
	grafo.push_back(t);
	for(int i=0;i<vettori[indice].size();i++){
		nodo temp;
		temp.val = vettori[indice][i].first;
		temp.c = vettori[indice][i].second;
		if(i+2<=vettori[indice].size()){ temp.indici[0]=(i+2);}
		else{temp.indici[0]=-1;}
		if(i+3<=vettori[indice].size()){ temp.indici[1]=(i+3);}
		else{temp.indici[1]=-1;}
		grafo.push_back(temp);
	}	
}

void raggruppa(string s){
	char last=s[0];
	int cont = 0;
	for(int i=0; i<M; i++){
		if(s[i]==last){
			cont++;
		}
		else{	
			pair <int,char> p;
			p.first = cont;
			p.second = last;
			v.push_back(p);
			cont = 1;
			last =s[i];
		}
	}
	pair <int,char> p;
	p.first = cont;
	p.second = last;
	v.push_back(p);
}

void itera(int indice){
	int size = vettori[indice].size() + 1;
	valori.clear();
	valori.assign(size,0);
	if(vettori[indice].size()>=2){
	rec(1,1,0);
	rec(1,2,0);	
	}
	else{
	rec(1,1,0);   	
	}
	int temp = 0;
	for(int i=0; i<size; i++){
		if(valori[i]>temp) temp= valori[i];
		if(valori[i]<temp) valori[i] = temp;
	}
}

void rec(int j,int i,int sum){
	//cout << j << " " << i << " " << sum << endl;
	if(i != -1 && j<valori.size()){
		sum = sum + grafo[i].val;
		if(sum>valori[j]){
			valori[j] = sum;
		}
		rec(j+1,grafo[i].indici[0],sum);
		rec(j,grafo[i].indici[1],sum);
	}
	else{
		//cout << "fuori" << endl;
	}
}
