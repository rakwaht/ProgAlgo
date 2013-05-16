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
vector < vector < pair <int,char> > > vettori;

int check_row(int indice,int t);
int recursive(int i, int j, char c,int indice);
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
	/*for(int i=0; i<N; i++){
		in >> dati[i];
	}*/
	
	for(int i=0; i<N; i++){
		string buffer;
		in >> buffer;
		v.clear();
		raggruppa(buffer);
		vettori.push_back(v);
	}
	

	sol();
	//cout << check_row(0,1) << endl;
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
	int temp;	
	if(t>=vettori[indice].size()){
		temp = M;
	}
	else{
	m = new int * [vettori[indice].size()];
	for(int i=0; i<vettori[indice].size(); i++){
		m[i]= new int [t+1];
	}
	for(int i=0; i<vettori[indice].size(); i++){
		for(int j=0; j<=t; j++){
			m[i][j]=-1;
		}
	}
	temp = recursive(vettori[indice].size()-1,t,'a',indice);	
	/*for(int i=0; i<v.size(); i++){
		for(int j=0; j<=t; j++){
			cout << m[i][j] << " " ;
		}
		cout << endl;
	}
	cout << endl << endl << endl;*/
	for(int i=0; i<vettori[indice].size();i++){
		delete [] m[i];
	}
	delete [] m;
	}
	return temp;
}

int sol(){
	//base
	for(int i=0; i<T; i++){
		tab[0][i] = check_row(0,i); 
	}
	int i=1;
	while(i<N){
		for(int j=0;j<T;j++){
			tab[i][j] = calcola(i,j);
		}
	 i++;
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
	cout << endl << endl;

	return max;
}

int recursive(int i, int j, char c,int indice){
  //  cout << "Analizzo oggetto : " << v[i].first << " " << v[i].second  <<"  con travestimenti : " << i << " " << j;
  if ( j < 0 ){
    // cout << "  RITORNO : -infinito" << endl;
    return -10000;
  }
  else if( i < 0 ){
    //cout << "  RITORNO : 0" << endl;
    return 0;
  }
  else{
    if( vettori[indice][i].second == c ){
      //cout << "  RITORNO : char uguale" << endl;
      if ( i > 0 )
	return vettori[indice][i].first + recursive( i-1, j, c, indice );
      else
	return vettori[indice][i].first + recursive( i-2, j, c, indice );
    }
    else{
      //cout << "  RITORNO : ricorsione" << endl;
      return max( vettori[indice][i].first + recursive( i-1, j-1, vettori[indice][i].second, indice ), recursive( i-1, j, c, indice) );
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
