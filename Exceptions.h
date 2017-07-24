#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

/*
*Contains Exception Classes for Credit Card Number Generator Tool
*Coded By bl4ckbo7
*/

class lengthException{

private:
    std::string errorLength;

public:
    lengthException(){
        errorLength = "\n[Error] Invalid Credit Card Number Size!\n\n";
    }

    std::string what(){
        return errorLength;
    }
};

class typeException{

private:
    std::string errorType;

public:
    typeException(){
        errorType = "\n[Error] Invalid Value Entered!\n\n";
    }

    std::string what(){
        return errorType;
    }
};



#endif // EXCEPTIONS_H_INCLUDED
