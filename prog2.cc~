using namespace std;
#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include<queue>
#include<cstring>
#include <algorithm>

int N,M,T;
string * dati;
int ** tab;
int ** m;
vector < pair<int,char> > v;

int check_row(int indice,int t);
int recursive(int i, int j, char c);
int sol();
int calcola(int,int);
void raggruppa(string s);

int main(){
	ifstream in("input.txt");
	ofstream out("output.txt");
	in >> N >> M >> T;
	T += 1;
	dati = new string [N];	
	tab = new int * [N];
	for(int i=0; i<N; i++){
		tab[i] = new int [T];
	}	
	for(int i=0; i<N; i++){
		in >> dati[i];
	}
	
	//sol();
	cout << check_row(1,1) << endl;
	/*for(int i=0; i<N; i++){
		for(int j=0; j<T; j++){
			cout << tab[i][j] << " " ;
		}
		cout << endl;
	}*/

	out << tab[N-1][T-1];
	//cout << tab[N-1][T-1];
	return 0;
}

int check_row(int indice,int t){
	int cont=0;
	v.clear();
	raggruppa(dati[indice]);
	m = new int * [v.size()];
	for(int i=0; i<v.size(); i++){
		m[i]= new int [t+1];
	}
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<=t; j++){
			m[i][j]=-1;
		}
	}
	int temp = recursive(0,t,'a');	
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<=t; j++){
			cout << m[i][j] << " " ;
		}
		cout << endl;
	}	
	for(int i=0; i<v.size();i++){
		delete m[i];
	}
	delete m;
	return 0;
}

int sol(){
	//base
	for(int i=0; i<=T; i++){
		tab[0][i] = check_row(0,i); 
	}
	int i=1;
	while(i<N){
		for(int j=0;j<=T;j++){
			tab[i][j] = calcola(i,j);
		}
	 i++;
	}
	return 0;	
}

int calcola(int i, int j){
	int max=0;
	int indice = j;
	for(int k=0; k<=j; k++){
		int temp = check_row(i,indice)+tab[i-1][k];
		if(temp>max)max = temp;
		indice -= 1;
	}
	//cout << i << " " << j << " " << max << endl;
	return max;
}

int recursive(int i, int j, char c){
	cout << i << " " << j << " " << c << endl;
	if(i == v.size()){
		return 0;
	}
	else if(j<0) return -10000;
	else{
		if( m[i][j] != -1 ){
			return m[i][j];
		}
		else{
			if( v[i].second == c ){
				m[i][j] = v[i].first + recursive(i+1,j,c);
				return m[i][j];
			}
			else{
			   m[i][j] = max(v[i].first + recursive(i+1,j-1,v[i].second),recursive(i+1,j,c));
			   return m[i][j];
			}
		}
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
