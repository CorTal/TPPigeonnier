#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <fstream>
#include <stdlib.h> 

// Définitions des contraintes, d'autres contraintes peuvent être ajoutée en respectant cette signature
typedef bool (*CONTRAINTE) (const std::vector<bool>& mat, int n, int q);


class Contrainte{
	int min, max, dim;
public:
	void setmin(int min1){min = min1;};
	void setmax(int max1){max = max1;};
	void setdim(int dim1){dim = dim1;};
	int getmin(){return min;};
	int getmax(){return max;};
	int getdim(){return dim;};
	void show(){std::cout << "Min "<< min << " Max " << max << std::endl;};
};

// Puissance avec unsigned long long int
unsigned long long int ipow(unsigned long long int base, int exp ) {
    unsigned long long int result = 1ULL;
    while( exp ) {
        if ( exp & 1 ) {
            result *= (unsigned long long int)base;
        }
        exp >>= 1;
        base *= base;
    }
    return result;
}

std::vector<std::string> explode( const std::string &delimiter, const std::string &str)
{
    std::vector<std::string> arr;

    int strleng = str.length();
    int delleng = delimiter.length();
    if (delleng==0)
        return arr;//no change

    int i=0;
    int k=0;
    while( i<strleng )
    {
        int j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
        if (j==delleng)//found delimiter
        {
            arr.push_back(  str.substr(k, i-k) );
            i+=delleng;
            k=i;
        }
        else
        {
            i++;
        }
    }
    arr.push_back(  str.substr(k, i-k) );
    return arr;
}

std::vector<Contrainte> parser(std::string filename){
	std::vector<Contrainte> cont;

	std::ifstream file(filename, std::ifstream::in);
	if(file){
		std::string ligne;
		std::string valeur;
		while(getline(file, ligne)){  
			Contrainte tmp;
		
			if(ligne[0] == 'c'){
				ligne.erase(0,2);
				std::vector<std::string> v = explode(" ", ligne);
				tmp.setmin(atoi(v[0].c_str()));
				tmp.setmax(atoi(v[1].c_str()));
				tmp.setdim(atoi(v[2].c_str()));
				cont.push_back(tmp);
			}
		}
	}
	return cont;
}

bool contrainte(const std::vector<bool>& mat,int min, int max, int n, int q, int d)
{
	if(d == 0){
		unsigned int tmp;
			for(int i=0; i < n; ++i)
			{
				tmp = 0;
				for(int j=0; j < q; ++j)
				{
					tmp += mat[i*q+j];
				}
				if(min == max){
					if(tmp != (unsigned int)min)
						return false;
				}
				else{
					if(tmp < (unsigned int)min || tmp > (unsigned int)max)
					return false;
				}
				
			}
	}
	else{
		unsigned int tmp;
			for(int i=0; i < q; ++i)
			{
				tmp = 0;
				for(int j=0; j < n; ++j)
				{
					tmp += mat[j*q+i];
				}
				if(min == max){
					if(tmp != (unsigned int)min)
						return false;
				}
				else{
					if(tmp < (unsigned int)min || tmp > (unsigned int)max)
					return false;
				};
			}
	}
	

	return true;
}

// Contrainte 1 pigeon est affecté à 1 et 1 seul pigeonnier
bool contrainte1(const std::vector<bool>& mat, int n, int q) {
	unsigned int tmp;
	for(int i=0; i < n; ++i) {
		tmp = 0;
		for(int j=0; j < q; ++j) {
			tmp += mat[i*q+j];
		}

		if(tmp != 1)
			return false;
	}

	return true;
}

// Contrainte 1 pigeonnier ne doit pas contenir + de 1 pigeon
bool contrainte2(const std::vector<bool>& mat, int n, int q) {
	unsigned int tmp;
	for(int i=0; i < q; ++i) {
		tmp = 0;
		for(int j=0; j < n; ++j) {
			tmp += mat[j*q+i];
		}

		if(tmp < 1 && tmp > 3)
			return false;
	}

	return true;
}

// Convertis un unsigned long long int en représentation binaire dans la matrice
void conv(std::vector<bool>& mat, unsigned long long int init) {
	for(int i=mat.size()-1; i >= 0; --i) {
		mat[i] = init%2;
		init = init >> 1;
	}
}

bool solve(int n, int q, std::vector<Contrainte> contraintes) {
	unsigned int satisfiable = 0;
	unsigned long long int nbSol = ipow(2,(n*q)); // Nombre de matrices possible
	unsigned long long int size = (nbSol/omp_get_max_threads()); //Taille de matrice que chaque Thread doit traiter
	
	#pragma omp parallel for reduction(+:satisfiable) //On parallèlise la génération et le test de toutes les matrices
	for(int numThread=0; numThread<omp_get_max_threads(); numThread++) {
		unsigned long long int begin, end;
		begin = size*numThread;
		end = begin+size;
		
		std::vector<bool> mat(n*q);
		conv(mat,begin);
		
		for(unsigned long long int k=begin; k<end; ++k) {
			bool tmp = true;
			for(unsigned int i=0; i < contraintes.size(); ++i) {
				tmp = contrainte(mat,contraintes[i].getmin(),contraintes[i].getmax(), n, q, i);
				if(!tmp)
					break;
			}
		
			satisfiable+=tmp;

			for(int i=mat.size()-1; i >= 0; --i) {
				if(mat[i]) {
					mat[i] = false;
				} else {
					mat[i] = true;
					break;
				}
			}
		}
	
	}
	
	std::cout << satisfiable << std::endl;

	return satisfiable;
}

int main(int argc, char **argv) {
	int n = 0;
	int q = 0;
	/*for(int i=1; i < argc; ++i) {
		if(std::string(argv[i]) == "-n") {
			n = std::stoi(argv[i+1]);
		} else if(std::string(argv[i]) == "-q") {
			q = std::stoi(argv[i+1]);
		}
	}
	
	if(solve(n,q,{&contrainte1, &contrainte2})>0) {
		std::cout << "C'est satisfiable" << std::endl;
	} else {
		std::cout << "C'est insatisfiable" << std::endl;
	}
	*/
	std::string file = argv[1];
	std::vector<Contrainte> cont;
	cont = parser(file);

	n = cont[0].getdim();
	q = cont[1].getdim();
	if(solve(n,q,cont)>0) {
		std::cout << "C'est satisfiable" << std::endl;
	} else {
		std::cout << "C'est insatisfiable" << std::endl;
	}
	return 0;
}
