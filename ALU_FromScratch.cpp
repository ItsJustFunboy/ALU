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



#include <stdio.h>

// Convertions

int boolToInt(bool input) {
    if (input) {
        return 1;
    }
    else {
        return 0;
    }
}

bool intToBool(int input) {
    if (input == 1) {
        return 1;
    }
    else {
        return 0;
    }
}
// Main classes

class bit {

public:
    bool state;

    int getDecState() {
        if (state) { return 1; }
        else { return 0; }
    }

};

class byte {

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

    bit CarryOut;

};

// More convertions 

int byteToInt(byte B) {
    int T1Val = 1 * boolToInt(B.T1.state);
    int T2Val = 2 * boolToInt(B.T2.state);
    int T3Val = 4 * boolToInt(B.T3.state);
    int T4Val = 8 * boolToInt(B.T4.state);
    int T5Val = 16 * boolToInt(B.T5.state);
    int T6Val = 32 * boolToInt(B.T6.state);
    int T7Val = 64 * boolToInt(B.T7.state);
    int T8Val = 128 * boolToInt(B.T8.state);

    int sum = T1Val + T2Val + T3Val + T4Val + T5Val + T6Val + T7Val + T8Val;

    return sum;
}

// Gates

bool NOT(bool A) {
    if (A == 1) {
        return 0;
    }
    else if (A == 0) {
        return 1;
    }
}

bool OR(bool A, bool B) {
    if (A == 1) {
        return 1;
    }
    else if (B == 1) {
        return 1;
    }
    else {
        return 0;
    }
}

bool AND(bool A, bool B) {
    if (A == 1) {
        if (B == 1) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

bool XOR(bool A, bool B) {
    return AND(NOT(AND(A, B)), OR(A, B));
}

bool NAND(bool A, bool B) {
    return NOT(AND(A, B));
}

bool NOR(bool A, bool B) {
    return NOT(OR(A, B));
}

bool XNOR(bool A, bool B) {
    return NOT(XOR(A, B));
}

// Basic Math

// ADD 

byte HalfAdd(bit A, bit B) {

    bool sum = XOR(A.state, B.state);
    bool carry = AND(A.state, B.state);

    byte returnedByte;

    returnedByte.T1.state = sum;
    returnedByte.CarryOut.state = carry;

    return returnedByte;

}

byte Add1(byte A, byte B, bool carryIn) {

    bool x1 = XOR(A.T1.state, B.T1.state);
    bool a1 = AND(A.T1.state, B.T1.state);
    bool x2 = XOR(x1, carryIn);
    bool a2 = AND(carryIn, x1);
    bool o1 = OR(a1, a2);

    byte returnedByte;

    returnedByte.T1.state = x2;

    return returnedByte;


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

    returnedByte.T1.state = x2a;
    returnedByte.T2.state = x2b;
    return returnedByte;

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

    return returnedByte;
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

    if (o1h) {
        printf("WARNING::ADD8BYTE_OVERFLOW.\n");
    }

    byte returnedByte;

    returnedByte.T1.state = x2a;
    returnedByte.T2.state = x2b;
    returnedByte.T3.state = x2c;
    returnedByte.T4.state = x2d;
    returnedByte.T5.state = x2e;
    returnedByte.T6.state = x2f;
    returnedByte.T7.state = x2g;
    returnedByte.T8.state = x2h;
  
    return returnedByte;

}

byte* Add16(byte A, byte B, bool carryIn) {

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

    byte returnedBytes[2] = {byte B2, byte B1};

    returnedBytes[1].T1.state = x2a;
    returnedBytes[1].T2.state = x2b;
    returnedBytes[1].T3.state = x2c;
    returnedBytes[1].T4.state = x2d;
    returnedBytes[1].T5.state = x2e;
    returnedBytes[1].T6.state = x2f;
    returnedBytes[1].T7.state = x2g;
    returnedBytes[1].T8.state = x2h;
    returnedBytes[1].CarryOut.state = NULL;

    returnedBytes[0].T1.state = x2i;
    returnedBytes[0].T2.state = x2j;
    returnedBytes[0].T3.state = x2k;
    returnedBytes[0].T4.state = x2l;
    returnedBytes[0].T5.state = x2m;
    returnedBytes[0].T6.state = x2n;
    returnedBytes[0].T7.state = x2o;
    returnedBytes[0].T8.state = x2p;
    returnedBytes[0].CarryOut.state = o1p;

    return returnedByte;

}



// SUB

byte HalfSub(bit A, bit B) {


    bool sum = XOR(A.state, B.state);
    bool carry = AND(NOT(A.state), B.state);

    byte returnedByte;

    returnedByte.T1.state = sum;
    returnedByte.CarryOut.state = carry;

    return returnedByte;

}

byte Sub1(byte A, byte B, bool borrowIn) {

    bool x1 = XOR(A.T1.state, B.T1.state);
    bool a1 = AND(NOT(A.T1.state), B.T1.state);
    bool x2 = XOR(x1, borrowIn);
    bool a2 = AND(borrowIn, NOT(x1));
    bool o1 = OR(a1, a2);

    if (o1) {
        byte returnedByte;

        returnedByte.T1.state = 0;
        returnedByte.T2.state = 0;
        returnedByte.T3.state = 0;
        returnedByte.T4.state = 0;
        returnedByte.T5.state = 0;
        returnedByte.T6.state = 0;
        returnedByte.T7.state = 0;
        returnedByte.T8.state = 0;

        printf("WARNING::SUB1BYTE_OVERFLOW; BYTE RESET.\n");

        return returnedByte;

    }
    else {

        byte returnedByte;
        returnedByte.T1.state = x2;

        return returnedByte;
    }

}

// Other 
// TBD, TBM

// C++ Main Func

int main() {

    byte b1;

    b1.T1.state = 1;
    b1.T2.state = 1;
    b1.T3.state = 0;
    b1.T4.state = 0;
    b1.T5.state = 0;
    b1.T6.state = 0;
    b1.T7.state = 0;
    b1.T8.state = 1;

    byte b2;

    b2.T1.state = 1;
    b2.T2.state = 1;
    b2.T3.state = 0;
    b2.T4.state = 0;
    b2.T5.state = 0;
    b2.T6.state = 0;
    b2.T7.state = 0;
    b2.T8.state = 0;

    printf("$%d\n", byteToInt(Add2(b1, b2, 0)));
 
    return 0;
}