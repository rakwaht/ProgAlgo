using namespace std;
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<cstring>

int N,M,T;
string * dati;
int ** tab;
int ** m;

int check_row(int indice,int t);
int recursive(string s,int i,int j,char v,int t);
int sol();
int calcola(int,int);
int main(){
	ifstream in("input.txt");
	in >> N >> M >> T;
	dati = new string [N];	
	tab = new int * [N];
	for(int i=0; i<N; i++){
		tab[i] = new int [T];
	}	
	for(int i=0; i<N; i++){
		in >> dati[i];
	}
	
	
	sol();
	ofstream out("output.txt");
	out << tab[N-1][T-1];
	return 0;
}

void print(){
	for(int i=0; i<N; i++){
		cout << dati[i] << endl;
	}
}

int check_row(int indice,int t){
	int cont=0;
	m = new int * [M];
	for(int i=0; i<M; i++){
		m[i]= new int [t+1];
	}
	for(int i=0; i<M; i++){
		for(int j=0; j<=t; j++){
			m[i][j]=-1;
		}
	}
	int temp = recursive(dati[indice],0,0,'a',t);
	for(int i=0; i<M;i++){
		delete m[i];
	}
	delete m;
	return temp;
}

int recursive(string s,int i,int j,char v,int t){
	if(j==t+1){
		return -1;
	}
	else if(i==M || j>t){
		return 0;
	}
	else if(m[i][j] != -1){
		if(s[i]==v) return m[i][j]+1;
		else return m[i][j];
	}
	else if(s[i]==v){
		m[i][j] = recursive(s,i+1,j,v,t) + 1;
		return m[i][j];
	}
	else{
		m[i][j] = max(recursive(s,i+1,j,v,t),recursive(s,i+1,j+1,s[i],t)+1);
		return m[i][j];
	}
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
	cout << i << " " << j << " " << max << endl;
	return max;
}
