/* Vanessa Gutierrez
   Discrete Structures 2, Lab 2
*/

#include <iostream>
#include <math.h>
#include <assert.h>
using namespace std;

int main() {
    // NOTE: uint is used instead of int to allow for the higher int 
    // values produced by exp_mod that would otherwise overflow
    uint EuclidAlgGCD(uint, uint);
    uint ExtendedEuclidAlgGCD(uint, uint, uint&, uint&);
    uint inverse(uint, uint);
    uint RelativePrime(uint);
    uint Decode(uint, uint, uint);
    uint Encode(uint, uint, uint);

    uint option;
    uint a, b, s, t;
    // RSA Algorithm only works with very small P and Q, otherwise 
    // we run into overflow errors
    uint P = 7, Q = 5, d, e, C, M, M1;
    uint PQ = P*Q;

    do{
        cout << "\n----------------- MENU -----------------" << endl;
        cout << "Select one of the following options:" << endl;
        cout << "1. Calculate Greatest Common Divisor\n";
        cout << "2. Calculate Greatest Common Divisor Coefficient\n";
        cout << "3. Calculate Inverse Modulo\n";
        cout << "4. Find Relative Prime\n";
        cout << "5. Encode and Decode with the RSA Encoding Algorithm\n";
        cout << "6. Quit\n";
        cout << "Enter: ";
        cin >> option;
        cout << endl;

        switch (option) {
            case 1:
            cout << "\n----------------- GCD -----------------" << endl;
                cout << "Enter two numbers to find their greatest common divisor: ";
                cin >> a >> b;
                cout << "The GCD is: " << EuclidAlgGCD(a, b) << endl;
                break;
    
            case 2:
            cout << "\n----------------- GCD COEFFICIENT -----------------" << endl;
                cout << "Enter two numbers to find their greatest common divisor: ";
                cin >> a >> b;
                cout << "The GCD is: " << ExtendedEuclidAlgGCD(a, b, s, t) << endl;
                break;
    
            case 3:
            cout << "\n----------------- INVERSE MOD -----------------" << endl;
                cout << "Enter two numbers to find their inverse modulo: ";
                cin >> a >> b;
                cout << "The inverse modulo is: " << inverse(a, b) << endl;
                break;
    
            case 4:
                cout << "\n----------------- RELATIVE PRIME -----------------" << endl;
                cout << "Enter a number to find it's nearest relative prime: ";
                cin >> a;
                cout << "Relative prime: " << RelativePrime(a) << endl;
                break;
            
            case 5:
                cout << "\n----------------- RSA -----------------" << endl;
                d = RelativePrime((P-1)*(Q-1));
                e = inverse( d, (P-1)*(Q-1));
                
                /* M is an uinteger that is smaller than PQ */
                cout << "Enter an integer that is smaller than "<< PQ << ": ";
                cin >> M;
                
                C = Encode (M, d, PQ);
                cout << "Encoded int: " << C << endl;
                M1 = Decode (C, e, PQ);
                cout << "Decoded int: " << M1 << endl;

                assert (M == M1);
                cout << "Original integer matches!" << endl;
                break;
            
            case 6:
                cout << "Goodbye!" << endl;
        }
    } while (option != 6);
}

/* precondition: a >=b>=0 */
/* postcondition: return d=gcd (a,b) */
uint EuclidAlgGCD (uint a, uint b) {
    //cout << a << " " << b << endl;
    if (b == 0)
        return a;

    return EuclidAlgGCD(b, a%b);
}

/* precondition: a >=b>=0 
   postcondition: return d=gcd (a,b), s and t are set 
   so that d= sa + tb */
uint ExtendedEuclidAlgGCD (uint a, uint b, uint & s, uint & t) {
    uint s1 = 0, s2 = 1, t1 = 1, t2 = 0, q, r;
    
    // Implementation of the extended euclidean algorithm example found at: 
    // https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Example
    while (a % b != 0) {
        q = a / b;
        r = a % b;
        s = s2 - q * s1;
        t = t2 - q * t1;

        s2 = s1;
        s1 = s;
        t2 = t1;
        t1 = t;
        a = b;
        b = r;
    }

    return r;
}

/* n>1, a is nonnegative 
 a <= n 
 a and n are relative prime to each other 
 return s such that a*s mod n is 1 */
uint inverse (uint a, uint n) {
    uint s, t; 
    uint d = ExtendedEuclidAlgGCD (n, a, s ,t);
    uint mod(uint, uint);

    if (d==1) {
        return (mod(t,n)); // t might be negative, use mod() to reduce to 
	    // an uinteger between 0 and n-1 
    }
    else {
        cout << "a,n are not relative prime!\n";
        return 0;
    }
}

uint RelativePrime(uint n) {
    uint EuclidAlgGCD(uint, uint);

    for (uint i = 2; i < n-1; i++) {
        if(EuclidAlgGCD(i,n) == 1)
            return i;
    }

    return n-1;
}

// Return M^d mod PQ 
uint Encode (uint M, uint d, uint PQ) {
    uint exp_mod(uint, uint, uint);
 
    return (exp_mod(M, d, PQ));
}

//Return C^e mod PQ 
uint Decode (uint C, uint e, uint PQ) {
    uint exp_mod(uint, uint, uint);

    return (exp_mod(C, e, PQ));
}

/*
* calcuate a^e mod n
precondition: e>=0, n>=1
postcondition: return a^e mod n
*/
uint exp_mod (uint a, uint e, uint n)
{
    uint mod(uint, uint);
    assert (e>=0 && n>=1);

    if (e==0)
        return 1;
    else{
        uint result = exp_mod (a, e/2, n);
        if (e%2==0) //if e is even
        {
            return mod (result*result, n);
        }
        else
        { //e is odd
            return mod (result*result*a, n);
        }
    }
}

uint mod(uint a, uint b) {
	uint div, mod;

    if (b <= 1) {
        cout << "You must modulo by an uinteger greater than 1." << endl;
        return 0;
    }

    // Recall that -1 mod 3 = 2 as -1= (-1)*3+2.
    // This if-else is necessary for an int implementation, note this version uses uint
    //if (a >= 0) {
        div = a / b;
        mod = a - (b * div);
    //}
    /*else if (a < 0){
        mod = a - a*b;
    }*/

	return mod;
}