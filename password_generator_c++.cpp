#include<iostream>
#include<ctime>
#include<string>

using namespace std;
string passwordGenerator();
string allCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW1234567890@#$%^&(),;<=>?";
string unique_characters = "";

int main(){
    cout<<"\nThe password is: "<<passwordGenerator()<<endl;
}

string passwordGenerator(){
    string password = "";
    srand(time(0));
    for(int i = 0; i<20 ; i++){
        bool uniqueCharacterFlag = true;
        char generatedCharacter = allCharacters[rand()%(allCharacters.length()-1)];
        for(int j = 0; j<=unique_characters.length(); j++){
            if(generatedCharacter == unique_characters[j]){
                uniqueCharacterFlag = false;
                break;
            }
        }
        
        if(uniqueCharacterFlag){
            password = password + generatedCharacter;
            unique_characters += generatedCharacter;
        }
        else{
            i--;
        }
    }
    return password;
}
