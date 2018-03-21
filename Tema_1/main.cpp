#include "Matrix.h"
#include "Vector.h"

using namespace std;

inline bool CHECKER(Matrix < double > A, myVec < double > x, myVec < double > y){
    for (int i = 0; i < A.size(); i++){
        if (A[i] * x != y[i]){
            return 0;
        }
    }

    return 1;
}

int main(){
    ifstream cin("test.in");
    ofstream cout("test.out");
    Matrix < double  > A, B;
    myVec < double > X, Y;
    
    X.read_data(cin);
    Y.read_data(cin);
    cin >> A;
    B = A;

    Matrix < double > C;
    C = A + B;

    //A = B = C;

    cout << X << Y << A << B << C;

    bool u = CHECKER(A, X, Y);

    if (u) cout << "ADEVARAT! Ecuatia Ax=y este valida!!!\n";
    else   cout << "FALS! Ecuatia Ax=y nu este valida!!!!\n";

    return 0;
}