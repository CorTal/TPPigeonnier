#include <iostream>
#include <string>
#include <vector>
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


// Contrainte 1 pigeon est affecté à 1 et 1 seul pigeonnier
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

// Contrainte 1 pigeonnier ne doit pas contenir + de 1 pigeon
bool contrainte2(const std::vector<bool>& mat, int n, int q)
{
	unsigned int tmp;
	for(int i=0; i < q; ++i)
	{
		tmp = 0;
		for(int j=0; j < n; ++j)
		{
			tmp += mat[j*q+i];
		}

		if(tmp > 1)
			return false;
	}

	return true;
}

// Permet de vérifier si 2 matrices sont égales, pour savoir si toutes les possibilités ont été explorées
bool isequal(const std::vector<bool>& mat1, const std::vector<bool>& mat2)
{
	bool is = true;

	for(unsigned int i=0; i < mat1.size(); ++i)
	{
		is = (!is || (mat1[i] != mat2[i])) ? false : true;
	}

	return is;
}


bool solve(int n, int q, std::vector<Contrainte> contraintes)
{
	std::vector<bool> mat(n*q); //Matrice pigeon/pigeonnier initialisée à 0
	std::vector<bool> end(n*q); //Matrice finale attendue, initialisée à 1
	for(int i=0; i < (n*q); ++i)
	{
		mat[i] = false;
		end[i] = true;
	}

	unsigned int satisfiable = 0; //Nombre de solutions trouvées

	while(!isequal(mat,end))
	{
		bool tmp = true;
		for(unsigned int i=0; i < contraintes.size(); ++i) // On teste chaque contrainte sur la matrice actuelle
		{
			tmp = contrainte(mat,contraintes[i].getmin(),contraintes[i].getmax(), n, q, i); 
			if(!tmp)
				break;
		}
		
		if(tmp) { // Si toutes les contraintes sont respectées c'est qu'on a trouvé une solution
			++satisfiable;
			/*std::cout << "==Solution " << satisfiable << "==" << std::endl;
			for(int i=0; i < q; ++i) {
				for(int j=0; j < n; ++j)
				{
					std::cout << mat[j*q+i] << "|";
				}
				std::cout << std::endl;
			}*/
		}

		for(unsigned int i=0; i < mat.size(); ++i) // On modifie la matrice afin de tester une nouvelle configuration
		{
			if(mat[i])
			{
				mat[i] = false;
			}
			else
			{
				mat[i] = true;
				break;
			}
		}
	}

	return satisfiable;
}

int main(int argc, char **argv)
{
	int n = 0; // Nombre de pigeons
	int q = 0; // Nombre de pigeonniers
/*	for(int i=1; i < argc; ++i)
	{
		if(std::string(argv[i]) == "-n")
		{
			n = std::stoi(argv[i+1]);
		}
		else if(std::string(argv[i]) == "-q")
		{
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
