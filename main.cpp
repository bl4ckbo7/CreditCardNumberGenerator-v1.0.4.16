#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <fstream>
#include "version.h"
#include "Exceptions.h"

using namespace std;

//global variables
string cardNumber="";
    int cardLength;
    string cardDigit[16];
    int checkSumEven=0;
    int checkSumOdd=0;
    int totalCheckSum=0;
    int multiple=0;
    bool valid = false;
    bool passed = false;
    int splitInt=0;
    char checkDigit;
    int lastDigit=15;
    string BIN="5399";
    int binLen = 6;
    int multiLen = 0;
    string accNo="";
    int accNoLen = 15;

    char digitsGen(){

        static const char digits[] = "0123456789";

        int stringLength = sizeof(digits)-1;

        return digits[rand()%stringLength];
    }

int main()
{

    cout<<"------------------------------------------------------------------\n";
    cout<<"Version: "<<AutoVersion::FULLVERSION_STRING<<"\n\n";
    cout<<"STATUS: "<<AutoVersion::STATUS<<"\n\n";
    cout<<"AUTHOR: bl4ckbo7\n\n";
    cout<<"Copyright "<<"(c) "<<AutoVersion::YEAR<<" HackerHub\n";
    cout<<"------------------------------------------------------------------\n\n\n";

    start:

    system("title Credit Card Number Generator");
    system("color 0a");


    int totalCards;

    try{
        cout<<"How many cards to generate? ";
        cin>>totalCards;

        if(!cin){
            throw typeException();
        }
    }

    catch(typeException ErrType){
        cout<<ErrType.what()<<"\n";
        goto start;
    }


    for(int repeat=0; repeat<totalCards; repeat++){

        do{
            srand(time(0));
            ofstream saveCard;
            saveCard.open("validCC.txt", ios::app);

            try{

                cout<<"Enter the Card Number(16 digits Only): ";

                for(int u=0; u<16; u++){
                    cardDigit[u]=digitsGen();
                }

                for(int i=0; i<16; i++){
                    cardNumber+=cardDigit[i];
                }

                cout<<cardNumber<<"\n\n\n";

                //getline(cin,cardNumber);
                cardLength = cardNumber.length();

            //credit number validation section starts here

                cout<<"\n\n[Info] Checking Credit Card Number....\n\n";

                //check correct credit card number size
               if(cardLength==0||cardLength>16){
                    system("color 04");
                    cin.clear();
                    throw lengthException();
                }

            }

            catch(lengthException ErrLen){
                cout<<ErrLen.what()<<"\n";
                goto start;
            }

            //if check successfully passed
            passed = true;

            cout<<"\n\n[Info] Fetching Credit Card details...\n\n";

            cout<<"\n\nCard Number Length: "<<cardLength<<"\n\n";


            //checks last digit of the card number
            while(lastDigit==15){
                checkDigit = cardNumber[lastDigit];
                lastDigit++;
            }

            cout<<"\nCheck Digit: "<<checkDigit-48<<"\n\n";

            //For Fetching BIN number
            int b = 0;

            while(b<binLen){
                BIN += cardNumber[b];
                b++;
            }

            cout<<"\nBIN: "<<BIN<<"\n\n";

            //for fetching account number
            int m=6;

            while(m<accNoLen){
                accNo += cardNumber[m];
                m++;
            }


            cout<<"\nAccount Number: "<<accNo<<"\n\n";

            cout<<"\n\n[Info] Checking Validity of Credit Card Number....\n\n";

            //verifies the validity of the card number through check digit
            for(int i=15; i>0; i--){
                    if(i%2!=0){
                            if((static_cast<int>(cardNumber[i]-48)*2)>9){
                                splitInt = ((static_cast<int>(cardNumber[i]-48)*2)-9);
                                checkSumOdd +=splitInt;
                            }
                            else{
                                checkSumOdd += (static_cast<int>(cardNumber[i]-48)*2);
                            }
                        }

                    else if(i%2==0){
                            checkSumEven += static_cast<int>(cardNumber[i]-48);
                        }

                    else{
                            cerr<<"[Error] Something's Wrong!\n\n";
                        }
            }

                //computes the total checksum
                totalCheckSum = checkSumEven+checkSumOdd;

            //cout<<"\nChecksum: "<<totalCheckSum<<"\n\n\n";

            //multiply by 9
            multiple = totalCheckSum*9;
            //cout<<"\nMultiple: "<<multiple<<"\n\n";

            //finds the length of number
            do{
                multiLen++;
            } while ((multiple / pow(10, multiLen)) > 1);

            //cout<<"\nLength of Multiple: "<<multiLen<<"\n\n";

            //dynamic memory allocation
            int* multipleCheckDigit= new int[5];

            //compares the check digit in the card number vs the last digit in the product number
            for (int j = 0; j < multiLen; j++) {
                multipleCheckDigit[j] = static_cast<int>((multiple/pow(10,j)))%10;

                if(multipleCheckDigit[j]==static_cast<int>(checkDigit-48)){
                    cout<<"\n\n[Info] CARD IS VALID!\n\n\n";
                    saveCard<<"\n\nCard Number Length: "<<cardLength<<"\n\n";
                    saveCard<<"\nCheck Digit: "<<static_cast<int>(checkDigit)-48<<"\n\n";
                    saveCard<<"\nBIN: "<<BIN<<"\n\n";
                    saveCard<<"\nAccount Number: "<<accNo<<"\n\n";
                    saveCard<<"\nCredit Card: "<<cardNumber<<"\n\n\n";
                    saveCard.close();
                    valid=true;
                    break;
                }

                if(multipleCheckDigit[j]!=static_cast<int>(checkDigit-48)){
                    cout<<"\n\n[Info] CARD IS NOT VALID!\n\n\n";
                    BIN.clear();
                    accNo.clear();
                    cardNumber.clear();
                    cout<<"\n\n[Info] Generating again....\n\n\n\n\n";
                    //valid=false;
                    break;
                }
            }

            //deletes the free allocated memory
            delete [] multipleCheckDigit;
        }

        while(!passed||!valid);

        cardNumber.clear();
    }
return 0;
}
