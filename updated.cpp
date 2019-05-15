#include<bits/stdc++.h>
using namespace std;

template<class T>
class matrix
{
	private:
		template <typename TE> friend matrix<TE> operator*(int i,const matrix<TE>& rhs);
		template <typename TE> friend matrix<TE> operator*(const matrix<TE>& a, const matrix<TE>& b);
		template <typename TE> friend ostream& operator<<(ostream &os, const matrix<TE>& x);
		vector<vector<T>> mat;
		int N,M;

	public:
		matrix<T>(): N(0), M(0) {}
		matrix<T>(int N,int M,T init=0)
		{
			this->N=N;
			this->M=M;
			mat.resize(N);
			for(int i=0;i<N;i++)
			{
				mat[i].resize(M);
				fill(mat[i].begin(),mat[i].end(),init);
			}
		}
		
		matrix<T>(const std::vector<std::vector<T>> &m)
		{
			int c=0;
			if(m.size()>0)
			{
				c=m[0].size();
				for (int i=1; i<m.size();i++)
					if(m[i].size()!=c)
						cout<<("Not a matrix");
			}
			mat=m;
			N=m.size();
			M=c;
		}
		
		float det();
		unsigned Rows() const;
		unsigned Cols() const;
		matrix<T>& AppendRow(T init=0);
		matrix<T>& AppendCol(T init=0);
		bool operator==(const matrix<T>& rhs);
		matrix<T> operator*(int i);
		matrix<T>& operator=(const matrix<T>& rhs);
		matrix<T> operator+(const matrix<T>& rhs);
		matrix<T> operator-(const matrix<T>& rhs);
		std::vector<T>& operator[](unsigned i) { return mat[i]; }
		std::vector<T> operator[](unsigned i) const { return mat[i]; }

};


template <typename T>
matrix<T>& matrix<T>::AppendCol(T init)
{
	for (unsigned i=0;i<N;i++)
		mat[i].push_back(init);
	++M;
	return *this;
}

template <typename T>
unsigned matrix<T>::Rows()const
{ 
	return N; 
}

template <typename T>
unsigned matrix<T>::Cols()const 
{ 
	return M; 
}

template <typename T>
matrix<T>& matrix<T>::AppendRow(T init)
{
	vector<T> r(M,init);
	mat.push_back(r);
	++N;
	return *this;
}


template <typename TE>
matrix<TE> operator*(int k,const matrix<TE>& rhs)
{
	matrix<TE> temp(rhs.N,rhs.M,0);
	for(int i=0; i<rhs.N; i++)
		{
			for( int j=0; j<rhs.M; j++)
			{
				temp.mat[i][j]=rhs.mat[i][j]*k;
			}
		}
	return temp;
}


template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& rhs)
{ 
	if(N==rhs.N && M==rhs.M )
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				mat[i][j]=rhs.mat[i][j];
			}
		}
	}
	else
	{
		cout<<"Not equal\n";
		exit(0);
	}	
	return *this;
}


template <typename TE> 
ostream& operator<<(ostream &os, const matrix<TE>& d)
{
	//cout<<d.N<<d.M;
	for(int i=0;i<d.N;i++)
	{
		os<<"[";
		for(int j=0;j<d.M;j++)
			os<<d.mat[i][j]<<" ";
		os<<"]\n";
	}
	return os;
}


template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& rhs)
{
	matrix<T> temp(N,M,0);
	if(N!=rhs.N||M!=rhs.M){
		cout<<"Cannot add the Matrices...they should be of same order\n";
		exit(0);
	}
	else{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				temp.mat[i][j]= mat[i][j]+ rhs.mat[i][j];
			}
		}
		return temp;
	}
}

template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& rhs)
{
	matrix<T> temp(N,M,0);	
	if(N!=rhs.N||M!=rhs.M){
		cout<<"Cannot find diff the Matrices...they should be of same order\n";
		exit(0);
	}
	else{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				temp.mat[i][j]= mat[i][j]- rhs.mat[i][j];
			}
		}
		return temp;
	}
}



template <typename TE>
matrix<TE> operator*(const matrix<TE>& a, const matrix<TE>& b)
{
	if(a.M!=b.N){
		cout<<"Multiplication of these Matrices not allowed \n";
		exit(0);
	}
	else{
		matrix<TE>res(a.N,b.M,0);
		int i, j, k; 
    	for (i = 0; i < a.N; i++) 
    	{	 
        	for (j = 0; j < b.M; j++) 
        	{ 
            	res.mat[i][j] = 0; 
            	for (k = 0; k < a.M; k++) 
                	res.mat[i][j] += a.mat[i][k] * b.mat[k][j]; 
        	} 
    	}	 
		return res;
	}
}

template <typename T>
float matrix<T>::det()
{	
	float det;
	matrix<T>res(N,N,0);
	if (N == 2)
      return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
	else
	  det = mat[0][0]*((mat[1][1]*mat[2][2]) - (mat[2][1]*mat[1][2])) 
	  -mat[0][1]*(mat[1][0]*mat[2][2] - mat[2][0]*mat[1][2]) + mat[0][2]*(mat[1][0]*mat[2][1] 
	  - mat[2][0]*mat[1][1]);
   return det;

}

template <typename T> 
bool matrix<T>::operator==(const matrix<T>& rhs)
{
	int cnt=0;
	if( N==rhs.N && M==rhs.M )
	{
		for(int i=0; i<N; i++)
		{
		for( int j=0; j<M; j++)
		{
			if( mat[i][j]!=rhs.mat[i][j] )
				return 0;
			else
				++cnt;
		}
		}
	}
	return cnt==N*M;
}


//m*3
template<typename T>
matrix<T> matrix<T>::operator*(int k)
{
	matrix<T> temp(N,M,0);
	for(int i=0; i<N; i++)
		{
			for( int j=0; j<M; j++)
			{
				temp.mat[i][j]=k*mat[i][j];
			}
		}	
	return temp;
}


int main()
{
	cout<<boolalpha;

	matrix<int> a(3,3,1);
	cout<<"Matrix a\n"<<a<<endl;

	vector<vector<int>> v={{1,2,3},{4,5,6},{7,8,9}};
	matrix<int>b(v);
	cout<<"Matrix b\n"<<b<<endl;

	matrix<int>sum=a+b;
	cout<<"a+b \n"<<sum<<endl;

	matrix<int>diff=a-b;
	cout<<"a-b \n"<<diff<<endl;

	matrix<int>prod=a*b;
	cout<<"Product of the matrices \n"<<prod<<endl;
	
	float r=a.det();
	cout<<"Determinent of matrix : \n"<<r<<"\n"; 

	matrix<int> m(3,3,1);
	auto i= m==v;
	cout<<"m==v :"<<i<<"\n";
	cout<<m;


	//m*3
	cout<<" m*3 "<<"\n";
	cout<<m*3<<"\n";
	m=m*3;
	cout<<"m=m*3"<<"\n"<<m;

	a=b;
	cout<<a<<"\n";

	vector<vector<int>> k={{1,2,3},{4,5,6},{7,8,9}};
	matrix<int> d(v);	

	//3*b
	cout<<" 3*b "<<"\n";
	cout<<3*b<<"\n";
	cout<<b<<"\n";
	m=3*b;
	cout<<m<<"\n";

	m.AppendRow(2);
	cout<<"After appending row\n"<<m;

	m.AppendCol(4);
	cout<<"After appending column\n"<<m;
	cout<<"\nRows :"<<m.Rows()<<" Cols :"<<m.Cols()<<"\n";

	cout<<m[1][1];
}
