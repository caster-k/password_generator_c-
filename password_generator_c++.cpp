#include<iostream>
#include<ctime>
#include<string>
using namespace std;
// string password_generator_using_find();
string passwordGenerator();

string allCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW1234567890@#$%^&(),;<=>?";
string unique_characters = "";


int main(){
    char ch = '1';
    // cout<<unique_characters.find(ch)<<endl;
    // if(unique_characters.find(ch)) {
    //     cout<<"Character found in allCharacters!"<<endl;
    // }
    // else {
    //     cout<<"Character not found in allCharacters!"<<endl;
    
    // }
    cout<<"\n\n The password is: "<<passwordGenerator()<<endl;
    // string password;
    // srand(time(0));
    // // cout<<allCharacters[rand()%allCharacters.size()
    // cout<<allCharacters.length()<<endl;

    // for(int i = 0; i<20 ; i++){

    //     password = password + allCharacters[rand()%(allCharacters.length()-1)];
    // }
    // cout<<password<<endl;
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
        // for(int j = 0; j<=unique_characters.length(); j++){
            // cout<<generatedCharacter<<endl;
            if(uniqueCharacterFlag){
                password = password + generatedCharacter;
                unique_characters += generatedCharacter;
                // break;
                // cout<<generatedCharacter<<endl;
            }
            else{
                // cout<<"khai k pa hudai xa"<<endl;
                i--;
                // break;
            }
    // }
    }
    // cout<<password<<endl;
    return password;
}

// string password_generator_using_find(){
//     string password = "";
//     srand(time(0));
//     for(int i = 0; i<20 ; i++){
//         char ch = allCharacters[rand()%(allCharacters.length()-1)];
        
//         if (!(unique_characters.find(ch))){
//             cout<<ch<<endl;
//             password = password + ch;
//             unique_characters += ch;
//             continue;
//         }
//         else{
//             i--;
//             continue;
//         }
//     }
//     return password;
// }
// string remove_duplicates(string password){

// }