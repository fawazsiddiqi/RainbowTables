//Mohammad Fawaz Siddiqi
//5461563
//CSCI262 Assignment 1 Rainbow Tables

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <vector>
#include "md5.h"

using namespace std;
//Protoypes of fucntions
void read();
string ReductionFunction (string);
string RainbowCreate(string,string);
void search(string,string);
void startendtablecreator(string);
void searchchains(string,string);
void findpassword(string,string,string);
void startendreader();
//vectors initialization
vector<string> vecPassword;
vector<string> vecStartPoint;
vector<string> vecEndPoint;
vector <string> vecfound;

//global variables
const int chain_length = 1000;

int main()
{
    read();
    
    string input_hash; //user inouts hash
    string challengeinput;
    
    cout << "Please enter the Hash ";
    cin >> input_hash;
    challengeinput = "419626379";
    
    string reduction_of_hash = ReductionFunction(input_hash); //the hash is then reduced
    
    //startendtablecreator(challengeinput);
    startendreader();
    cout << "Reading the Start and end points" << endl;
    cout << "Reading through password chains" << endl;
    
    clock_t t;
    t = clock();
    
    searchchains(reduction_of_hash,challengeinput); //searches the chains for the password
    for(int i=0 ; i<vecfound.size() ; i++)
    {
        string passfind = vecfound[i];
        findpassword(passfind,challengeinput,reduction_of_hash); //finds the password using password stored in the vector,challenge and the reduction of hash
    }
    
    t = clock() - t;
    cout << "Time taken to search the password: " << ((float)t/CLOCKS_PER_SEC)/60 << " minutes" << endl << endl;
}

void findpassword(string red_string, string challengeinput, string reduction_of_hash) //findpassword function
{
    string firstHash, firstReduction;
    string combine = red_string + challengeinput;
    
    for (int j = 0; j<chain_length;)
    {
        firstHash = md5(combine); //md5 of the combination
        j += 1;
        
        firstReduction = ReductionFunction(firstHash); //gets the reduction
        
        if (reduction_of_hash == firstReduction)
        {
            cout << "Password retrieved: " << red_string << endl; //if the reduction of the hash is equal to the firstreduction then
            break;                                                      //password is found
        }
        
        j += 1;
        
        combine = firstReduction + challengeinput;
    }
    
}

void startendtablecreator(string challengeinput) //creates the start and end table
{
    cout <<  endl << "Creating Start and end points table table" << endl;
    ofstream file ("StartAndEnd.txt");
    
    clock_t t;
    t = clock();
    for(int i=0 ; i<vecPassword.size(); i++)
    {
        vecStartPoint.push_back(vecPassword[i]); //vector push back is used to add a password
        vecEndPoint.push_back(RainbowCreate(vecPassword[i], challengeinput));
        file << vecStartPoint[i] << " " << vecEndPoint[i] << endl; //writes the start point and end point
    }
    t = clock() - t;
    cout << "Time taken to generate Rainbow Table is: " << ((float)t/CLOCKS_PER_SEC)/60 << " minutes" << endl << endl; //displaying the time taken to make the table
    file.close();
}

void read() //reads from rock you file
{
    string line;
 
    ifstream file ("rockyoufinal.txt");
    int count=0;
    if(!file)
    {
        cout << "Error opening file!" << endl;
    }
    else
    {
        while(file>>line)
        {
            if(line.length() == 7)
            {
                vecPassword.push_back(line); //uses push_back to add passwords
                count++;
            }
        }
    }
    
    cout << "Number of passwords (7 characters long): " << count << endl;
    file.close();
}

void startendreader() //reads the starts and end point in the vector
{
    ifstream file ("StartAndEnd.txt");
    
    string start;
    string end;
    
    while(file >> start >> end)
    {
        vecStartPoint.push_back(start);
        vecEndPoint.push_back(end);
    }
    
    file.close();
}

void searchchains(string reduction_of_hash , string challengeinput) //searches the chains
{
    bool found = NULL;
    
    for(int i=0 ; i<vecEndPoint.size(); i++)
    {
        if(reduction_of_hash == vecEndPoint[i])
        {
            cout << "Match found: " << vecEndPoint[i] << endl; //if any are they are displayed
            cout << "Start Point: " << vecStartPoint[i] << endl;
        }
        else
        {
            found = false;
        }
    }
    if(found == false) //if found is false then it searches again
    {
        search(reduction_of_hash,challengeinput);
    }
}

string ReductionFunction(string input_hash)
{
    string red_string = input_hash.substr(0,7); //reduction fucntion takes a part of the hash and reduces accoridngly
    
    for(int i=0 ; i<red_string.length() ; i++)
    {
        if(red_string[i] == '0')
        {
            red_string[i] = 'i';
        }
        
        if(red_string[i] == '1')
        {
            red_string[i] = 'v';
        }
        
        if(red_string[i] == '2')
        {
            red_string[i] = 'j';
        }
        
        if(red_string[i] == '3')
        {
            red_string[i] = 'k';
        }
        
        if(red_string[i] == '4')
        {
            red_string[i] = 'l';
        }
        
        if(red_string[i] == '5')
        {
            red_string[i] = 'z';
        }
        
        if(red_string[i] == '6')
        {
            red_string[i] = 'o';
        }
        
        if(red_string[i] == '7')
        {
            red_string[i] = 'q';
        }
        
        if(red_string[i] == '8')
        {
            red_string[i] = 'r';
        }
        
        if(red_string[i] == '9')
        {
            red_string[i] = 't';
        }
        
    }
    
    return red_string;
}

void search(string red_string,string challengeinput) //searches according to the reduction string
{
    string input_hash, red_string_after;
    string combine = red_string + challengeinput;
    
    for(int j=0; j<chain_length ;)
    {
        input_hash = md5(combine);
        j+=1;
        
        red_string_after = ReductionFunction(input_hash);
        for(int i=0 ; i<vecStartPoint.size(); i++)
        {
            if(red_string_after == vecEndPoint[i])
            {
                vecfound.push_back(vecStartPoint[i]);
            }
        }
        j+=1;
        
        combine = red_string_after + challengeinput;
    }
}

string RainbowCreate(string password,string challengeinput) //creates the rainbow table and returns the reduction
{
    string input_hash,reduction;
    string combin = password + challengeinput;
    
    for(int j=0; j<chain_length ;)
    {
        input_hash = md5(combin);
        j+=1;
        
        reduction = ReductionFunction(input_hash);
        j+=1;
        
        combin = reduction + challengeinput;
    }
    
    return reduction;
}

