/*
*                                                                               ALU by ItsJustFunboy
* 
*   Bytes are made of 8 bit values, in the order of {8 7 6 5 4 3 2 1}
*
*
*   More than 1 Byte is considered a byte array, having syntax of byte BARR(#of bytes, n)[]]= {byte Bn, byte Bn-1, ... byte B2, byte B1}. 
*
*   For example, < byte BARR4[4] = {byte B4, byteB3, byte B2, byte B1}>
*
*
*
*/



#include <iostream>

// Convertions

int boolToInt(bool input){
    if (input){
        return 1;
    } else {
        return 0;
    }
}

bool intToBool(int input){
    if (input == 1){
        return 1;
    } else{
        return 0;
    }
}
// Main classes

class bit{

    bool state;

    int getDecState(){
        if (state) {return 1;} else {return 0;}
    }

}

class nibble{

    /*
    * Layout
    *
    * T4 T3 T2 T1 (state)
    * 
    */

    public:

    bit T1;
    bit T2;
    bit T3;
    bit T4;

    int getDecValue(){
        int T1Val = 1*T1::getDecState();
        int T2Val = 2*T2::getDecState();
        int T3Val = 4*T3::getDecState();
        int T4Val = 8*T4::getDecState();

        int sum = T1Val + T2Val + T3Val + T4Val;
        
        return sum;
    }
}

class byte{

    /*
    * Layout
    *
    * T8 T7 T6 T5 T4 T3 T2 T1 (state)
    * 
    */
   
    public:

    bit T1;
    bit T2;
    bit T3;
    bit T4;
    bit T5;
    bit T6;
    bit T7;
    bit T8;

    bool carry;

    int getDecValue(){
        int T1Val = 1*T1::getDecState();
        int T2Val = 2*T2::getDecState();
        int T3Val = 4*T3::getDecState();
        int T4Val = 8*T4::getDecState();
        int T5Val = 16*T5::getDecState();
        int T6Val = 32*T6::getDecState();
        int T7Val = 64*T7::getDecState();
        int T8Val = 128*T8::getDecState();

        int sum = T1Val + T2Val + T3Val + T4Val + T5Val + T6Val + T7Val + T8Val;

        return sum;
    }
}
 

class carrySumPair{

    bit Sum;
    bit CarryOut;

}


class byteCarrySumPair{

    bit Sum;
    bit CarryOut;

}


// Gates

bool NOT(bit A){
    if (A.state == 1){
        return 0;
    } else if (A.state == 0){
        return 1;
    }
}

bool OR(bit A, bit B){
    if (A.state == 1){
        return 1;
    } else if(B.state == 1){
        return 1;
    } else {
        return 0;
    }
}

bool AND(bit A, bit B){
    if (A.state == 1){
        if (B.state == 1){
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

bool XOR(bit A, bit B){
    return AND(NOT(AND(A.state, B.state)), OR(A.state, B.state));
}

bool NAND(bit A, bit B){
    return NOT(AND(A.state, B.state));
}

bool NOR(bit A, bit B){
    return NOT(OR(A.state, B.state));
}

bool XNOR(bit A, bit B){
    return NOT(XOR(A.state, B.state));
}

// Basic Math

// ADD 

carrySumPair HalfAdd(bit A, bit B){

    bool inputA, inputB = A, B;

    bool sum = XOR(inputA, inputB);
    bool carry = AND(inputA, inputB);

    carrySumPair returnedPair;

    bit returnedPair.Rsum;
    bit returnedPair.Rcarry;

    returnedPair.Rsum.state = sum;
    returnedPair.Rcarry.state = carry;
    
    return returnedPair;

}

carrySumPair Add1(byte A, byte B, bool carryIn) {

    bool x1 = XOR(A .T1.state, B.T1.state);
    bool a1 = AND(A.T1.state, B.T1.state);
    bool x2 = XOR(x1, carryIn);
    bool a2 = AND(carryIn, x1);
    bool o1 = OR(a1, a2);

    byte returnedByte;
    returnedByte.T1.state = x2;
    returnedByte.CarryOut.state = o1;

    return returnedPair;

}

byte Add2(byte A, byte B, bool carryIn) {

    // CARRY = o1b
    // SUM = x2b

    bool x1a = XOR(A.T1.state, B.T1.state);
    bool a1a = AND(A.T1.state, B.T1.state);
    bool x2a = XOR(x1a, carryIn);
    bool a2a = AND(carryIn, x1a);
    bool o1a = OR(a1a, a2a);

    bool x1b = XOR(A.T2.state, B.T2.state);
    bool a1b = AND(A.T2.state, B.T2.state);
    bool x2b = XOR(x1b, o1a);
    bool a2b = AND(o1a, x1b);
    bool o1b = OR(a1b, a2b);

    byte returnedByte;
    returnedByte.T1.state = x2b;
    returnedByte.T2.state = x2b;
    returnedByte.carry = o1b;

    return returnedByte ;
    
}

byte Add4(byte A, byte B, bool carryIn) {

    // CARRY = o1d
    // SUM = x2d

    bool x1a = XOR(A.T1.state, B.T1.state);
    bool a1a = AND(A.T1.state, B.T1.state);
    bool x2a = XOR(x1a, carryIn);
    bool a2a = AND(carryIn, x1a);
    bool o1a = OR(a1a, a2a);

    bool x1b = XOR(A.T2.state, B.T2.state);
    bool a1b = AND(A.T2.state, B.T2.state);
    bool x2b = XOR(x1b, o1a);
    bool a2b = AND(o1a, x1b);
    bool o1b = OR(a1b, a2b);

    bool x1c = XOR(A.T3.state, B.T3.state);
    bool a1c = AND(A.T3.state, B.T3.state);
    bool x2c = XOR(x1c, o1b);
    bool a2c = AND(o1b, x1c);
    bool o1c = OR(a1c, a2c);

    bool x1d = XOR(A.T4.state, B.T4.state);
    bool a1d = AND(A.T4.state, B.T4.state);
    bool x2d = XOR(x1d, o1c);
    bool a2d = AND(o1c, x1d);
    bool o1d = OR(a1d, a2d);

    byte returnedByte;
    returnedByte.T1.state = x2a;
    returnedByte.T2.state = x2b;
    returnedByte.T3.state = x2c;
    returnedByte.T4.state = x2d;
    returnedByte.carry = o1d;

    return returnedByte ;
    
}

byte Add8(byte A, byte B, bool carryIn) {

    // CARRY = o1h
    // SUM = x2h

    bool x1a = XOR(A.T1.state, B.T1.state);
    bool a1a = AND(A.T1.state, B.T1.state);
    bool x2a = XOR(x1a, carryIn);
    bool a2a = AND(carryIn, x1a);
    bool o1a = OR(a1a, a2a);

    bool x1b = XOR(A.T2.state, B.T2.state);
    bool a1b = AND(A.T2.state, B.T2.state);
    bool x2b = XOR(x1b, o1a);
    bool a2b = AND(o1a, x1b);
    bool o1b = OR(a1b, a2b);

    bool x1c = XOR(A.T3.state, B.T3.state);
    bool a1c = AND(A.T3.state, B.T3.state);
    bool x2c = XOR(x1c, o1b);
    bool a2c = AND(o1b, x1c);
    bool o1c = OR(a1c, a2c);

    bool x1d = XOR(A.T4.state, B.T4.state);
    bool a1d = AND(A.T4.state, B.T4.state);
    bool x2d = XOR(x1d, o1c);
    bool a2d = AND(o1c, x1d);
    bool o1d = OR(a1d, a2d);

    bool x1e = XOR(A.T5.state, B.T5.state);
    bool a1e = AND(A.T5.state, B.T5.state);
    bool x2e = XOR(x1e, o1d);
    bool a2e = AND(o1d, x1e);
    bool o1e = OR(a1e, a2e);

    bool x1f = XOR(A.T6.state, B.T6.state);
    bool a1f = AND(A.T6.state, B.T6.state);
    bool x2f = XOR(x1f, o1e);
    bool a2f = AND(o1e, x1f);
    bool o1f = OR(a1f, a2f);

    bool x1g = XOR(A.T7.state, B.T7.state);
    bool a1g = AND(A.T7.state, B.T7.state);
    bool x2g = XOR(x1g, o1f);
    bool a2g = AND(o1f, x1g);
    bool o1g = OR(a1g, a2g);

    bool x1h = XOR(A.T8.state, B.T8.state);
    bool a1h = AND(A.T8.state, B.T8.state);
    bool x2h = XOR(x1h, o1g);
    bool a2h = AND(o1g, x1h);
    bool o1h = OR(a1h, a2h);

    byte returnedByte;
    returnedByte.T1.state = x2a;
    returnedByte.T2.state = x2b;
    returnedByte.T3.state = x2c;
    returnedByte.T4.state = x2d;
    returnedByte.T5.state = x2e;
    returnedByte.T6.state = x2f;
    returnedByte.T7.state = x2g;
    returnedByte.T8.state = x2h;
    returnedByte.carry = o1h;

    return returnedByte ;
    
}

byte Add16[2](byte A, byte B, bool carryIn) {

    // CARRY = o1p
    // SUM = x2p

    bool x1a = XOR(A.T1.state, B.T1.state);
    bool a1a = AND(A.T1.state, B.T1.state);
    bool x2a = XOR(x1a, carryIn);
    bool a2a = AND(carryIn, x1a);
    bool o1a = OR(a1a, a2a);

    bool x1b = XOR(A.T2.state, B.T2.state);
    bool a1b = AND(A.T2.state, B.T2.state);
    bool x2b = XOR(x1b, o1a);
    bool a2b = AND(o1a, x1b);
    bool o1b = OR(a1b, a2b);

    bool x1c = XOR(A.T3.state, B.T3.state);
    bool a1c = AND(A.T3.state, B.T3.state);
    bool x2c = XOR(x1c, o1b);
    bool a2c = AND(o1b, x1c);
    bool o1c = OR(a1c, a2c);

    bool x1d = XOR(A.T4.state, B.T4.state);
    bool a1d = AND(A.T4.state, B.T4.state);
    bool x2d = XOR(x1d, o1c);
    bool a2d = AND(o1c, x1d);
    bool o1d = OR(a1d, a2d);

    bool x1e = XOR(A.T5.state, B.T5.state);
    bool a1e = AND(A.T5.state, B.T5.state);
    bool x2e = XOR(x1e, o1d);
    bool a2e = AND(o1d, x1e);
    bool o1e = OR(a1e, a2e);

    bool x1f = XOR(A.T6.state, B.T6.state);
    bool a1f = AND(A.T6.state, B.T6.state);
    bool x2f = XOR(x1f, o1e);
    bool a2f = AND(o1e, x1e);
    bool o1f = OR(a1f, a2f);

    bool x1g = XOR(A.T7.state, B.T7.state);
    bool a1g = AND(A.T7.state, B.T7.state);
    bool x2g = XOR(x1g, o1f);
    bool a2g = AND(o1f, x1g);
    bool o1g = OR(a1g, a2g);

    bool x1h = XOR(A.T8.state, B.T8.state);
    bool a1h = AND(A.T8.state, B.T8.state);
    bool x2h = XOR(x1h, o1g);
    bool a2h = AND(o1g, x1h);
    bool o1h = OR(a1h, a2h);

    bool x1i = XOR(A.T9.state, B.T9.state);
    bool a1i = AND(A.T9.state, B.T9.state);
    bool x2i = XOR(x1i, o1h);
    bool a2i = AND(o1h, x1i);
    bool o1i = OR(a1i, a2i);

    bool x1j = XOR(A.T10.state, B.T10.state);
    bool a1j = AND(A.T10.state, B.T10.state);
    bool x2j = XOR(x1j, o1i);
    bool a2j = AND(o1i, x1j);
    bool o1j = OR(a1j, a2j);

    bool x1k = XOR(A.T11.state, B.T11.state);
    bool a1k = AND(A.T11.state, B.T11.state);
    bool x2k = XOR(x1k, o1j);
    bool a2k = AND(o1j, x1k);
    bool o1k = OR(a1k, a2k);

    bool x1l = XOR(A.T12.state, B.T12.state);
    bool a1l = AND(A.T12.state, B.T12.state);
    bool x2l = XOR(x1l, o1k);
    bool a2l = AND(o1k, x1l);
    bool o1l = OR(a1l, a2l);

    bool x1m = XOR(A.T13.state, B.T13.state);
    bool a1m = AND(A.T13.state, B.T13.state);
    bool x2m = XOR(x1m, o1l);
    bool a2m = AND(o1l, x1m);
    bool o1m = OR(a1m, a2m);

    bool x1n = XOR(A.T14.state, B.T14.state);
    bool a1n = AND(A.T14.state, B.T14.state);
    bool x2n = XOR(x1n, o1m);
    bool a2n = AND(o1m, x1n);
    bool o1n = OR(a1n, a2n);

    bool x1o = XOR(A.T15.state, B.T15.state);
    bool a1o = AND(A.T15.state, B.T15.state);
    bool x2o = XOR(x1o, o1n);
    bool a2o = AND(o1n, x1o);
    bool o1o = OR(a1o, a2o);

    bool x1p = XOR(A.T16.state, B.T16.state);
    bool a1p = AND(A.T16.state, B.T16.state);
    bool x2p = XOR(x1p, o1o);
    bool a2p = AND(o1o, x1p);
    bool o1p = OR(a1p, a2p);

    byte returnedBytes[] = {byte B2, byte B1};

    returnedBytes[1].T1.state = x2a;
    returnedBytes[1].T2.state = x2b;
    returnedBytes[1].T3.state = x2c;
    returnedBytes[1].T4.state = x2d;
    returnedBytes[1].T5.state = x2e;
    returnedBytes[1].T6.state = x2f;
    returnedBytes[1].T7.state = x2g;
    returnedBytes[1].T8.state = x2h;
    returnedBytes[1].carry = NULL;

    returnedBytes[0].T1.state = x2i;
    returnedBytes[0].T2.state = x2j;
    returnedBytes[0].T3.state = x2k;
    returnedBytes[0].T4.state = x2l;
    returnedBytes[0].T5.state = x2m;
    returnedBytes[0].T6.state = x2n;
    returnedBytes[0].T7.state = x2o;
    returnedBytes[0].T8.state = x2p;
    returnedBytes[0].carry = o1p;

    return returnedByte;
    
}

// Other 
// TBD, TBM

// C++ Main Func

int main(){

    byte b1;

    b1.T0 = 1;
    b1.T1 = 0;
    b1.T2 = 1;
    b1.T3 = 1;
    b1.T4 = 0;
    b1.T5 = 0;
    b1.T6 = 1;
    b1.T7 = 1;
    b1.T8 = 0;

    byte b2;

    b2.T0 = 1;
    b2.T1 = 1;
    b2.T2 = 1;
    b2.T3 = 1;
    b2.T4 = 0;
    b2.T5 = 0;
    b2.T6 = 1;
    b2.T7 = 0;
    b2.T8 = 0;

    std::cout << Add8(b1, b2, 0) << std::endl;

    return 0;
}