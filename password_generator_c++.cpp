#include<iostream>
#include<ctime>
#include<string>
#include<mysql/mysql.h>

using namespace std;
string passwordGenerator();
void selectOptions(MYSQL *conn, string generatedPassword);
void storePassword(MYSQL *conn, string generatedPassword);
void retrievePassword(MYSQL *conn);

string allCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVW1234567890@#$%^&(),;<=>?";
string unique_characters = "";


int main(){
    // Connect to MySQL database
    MYSQL *conn;
    const char *server = "localhost"; // Change to your server address
    const char *user = "root"; // Change to your MySQL username
    const char *password = "";// Change to your MySQL password
    const char *database = "PasswordManager"; // Change to your database name

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    // Connect to the database
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        cout << "mysql_real_connect() failed\n";
        return EXIT_FAILURE;
    }
    else{
        cout<<"Connected to the MySQL database successfully.\n";
    }
    string generatedPassword = passwordGenerator();
    selectOptions(conn, generatedPassword);
    // cout<<"\nThe password is: "<<generatedPassword<<endl;
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

void selectOptions(MYSQL *conn, string generatedPassword){
    string opt = "";
    // cout<<"Enter "
    char option = '\0';
    while(toupper(option) != 'E'){
        cout << "\nChoose an option:\n"
             << "1. Press S to Store password\n"
             << "2. Press R to Retrieve password\n"
             << "3. Press E to Exit\n";
        cin>>opt;
        if (opt.empty()) continue;
        // cout<<opt<<endl;
        option = toupper(opt[0]);
        // cout<<option;
        if(option != 'S' && 'R' != option && option != 'E'){
            cout<<"Invalid option. Please try again.\n";
            continue;
        }
        if(option == 'S'){
            cout << "Storing password...\n";
            storePassword(conn, generatedPassword);
        }
        else if(option == 'R'){
             cout << "Retrieving password...\n";
            retrievePassword(conn);
        }
        else if(option == 'E'){
            cout << "Exiting...\n";
            mysql_close(conn);
            exit(0);
            break;
        }
        
    }
}

void storePassword(MYSQL *conn, string generatedPassword){
    MYSQL_RES *res;
    MYSQL_ROW row;
    cout<<"Enter for what application or website you want to store your password: ";
    string application="";
    cin.ignore();  // Clear the newline character left by previous input
    getline(cin, application);

    cout<<"\nEnter your email address for that application: ";
    string email="";
    // cin.ignore();
    getline(cin, email);
    // The data base has columns such as passId and the rest is given in the 
    // code below
    string queryInsert = "INSERT INTO passwords (password, webApplication, email) VALUES ('"+generatedPassword+"', '"+application+"', '"+email+"')";
    if(mysql_query(conn, queryInsert.c_str())){
        cout<<"Failed to store password. Error: "<<mysql_error(conn)<<endl;
        return;
    }
    else{
        cout<<"Password stored successfully.\n";
        string queryRead = "SELECT * FROM passwords WHERE email = '" + email + "'";
        if(mysql_query(conn, queryRead.c_str())){
        cout<<"Failed to retrieve password. Error: "<<mysql_error(conn)<<endl;
        return;
        }
        else{
            res = mysql_store_result(conn);
            if(res){
                while((row = mysql_fetch_row(res))){
                    cout<<"\nPassword: "<<row[1]<<endl;
                    cout<<"Web Application: "<<row[2]<<endl;
                    cout<<"Email: "<<row[3]<<endl;
                }
                mysql_free_result(res);
            }
        }
    }
}

void retrievePassword(MYSQL *conn){
    MYSQL_RES *res;
    MYSQL_ROW row;
    cout<<"Enter your email address for which you want to retrieve your password: ";
    string email;
    cin>>email;
    string queryRead = "SELECT * FROM passwords where email = '"+email+"'";
    if(mysql_query(conn, queryRead.c_str())){
        cout<<"Failed to retrieve password. Error: "<<mysql_error(conn)<<endl;
        return;
    }
    else{
        res = mysql_store_result(conn);
        if(res){
            while((row = mysql_fetch_row(res))){
                cout<<"\nPassword: "<<row[1]<<endl;
                cout<<"Web Application: "<<row[2]<<endl;
                cout<<"Email: "<<row[3]<<endl;
            }
            mysql_free_result(res);
        }
        else{
            cout<<"No password found for the given email address.\n";
        }
    }
    mysql_close(conn);
}