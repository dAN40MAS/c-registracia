#include <iostream>
#include <fstream>
using namespace std;

const string secretKey = "0123456789abcdef"; // Ваш ключ шифрования

string xorEncode(string plainText) {
    string encryptedText = "";
    
    for (size_t i = 0; i < plainText.length(); ++i) {
        encryptedText += plainText[i] ^ secretKey[i % secretKey.length()];
    }
    
    return encryptedText;
}

string xorDecode(string encryptedText) {
    string decryptedText = "";
    
    for (size_t i = 0; i < encryptedText.length(); ++i) {
        decryptedText += encryptedText[i] ^ secretKey[i % secretKey.length()];
    }
    
    return decryptedText;
}

class Password
{
public:

    void signIn()
    {
        ifstream log("login.txt", ios::out);
        ifstream pass("password.txt", ios::out);

        if (log.is_open() && pass.is_open()){
            string loginInput;
            string passInput;

            cout << "Enter ur login: "; cin >> loginInput;
            cout << "Enter ur pass: "; cin >> passInput;

            string line;
            bool flagLogin = false; bool flagPass = false;
            int n = 0; int m = 0; // номер строки с найденным логином и паролем соответственно

            while (getline(log, line)) {
                if (xorDecode(line) == loginInput) {
                    flagLogin = true;
                    break;
                }
                n += 1;
            }

            while (getline(pass, line)) {
                if (m == n && xorDecode(line) == passInput) {
                    flagPass = true;
                    break;
                }
                m += 1;
            }

            if(flagPass == true && flagLogin == true){
                cout << "U are sign in successfull!" << endl;
            }
            else{
                cout << "incorrect" << endl;
            }
        }
        else{
            cout << "Error!" << endl;
        }
    }
    void signUp()
    {
        ofstream log("login.txt", ios::app);
        ofstream pass("password.txt", ios::app);

        if (log.is_open() && pass.is_open()) {
            string logInput;
            string passInput;

            cout << "Enter ur login: "; cin >> logInput;
            cout << "Enter ur password: "; cin >> passInput;

            string line;
            bool flag_login = false;

            ifstream login_file("login.txt");
            ifstream pass_file("password.txt");

            while (getline(login_file, line)) {
                if (line == logInput) {
                    flag_login = true;
                    break;
                }
            }
            string encryptedLog, encryptedPass;

            if (!flag_login) {
                encryptedLog = xorEncode(logInput);
                encryptedPass = xorEncode(passInput);
                log << encryptedLog << endl;
                pass << encryptedPass << endl;

                cout << "Register is successful!" << endl;
            } else {
                cout << "Register is failed (login is already exists)" << endl;
            }
        } else {
            cout << "Error!" << endl;
        }
    }
};

class menu
{
public:

    int runMenu()
    {
        int choise;
        cout << "Добро пожаловать!" << endl;
        cout << "1.Вход" << endl;
        cout << "2.Регистрация" << endl;
        cin >> choise;

        if (choise != 1 && choise != 2)
        {
            cout << "Выбран неверный пункт меню!" << endl;
        }
        if (choise == 1)
        {
            Password pass;
            pass.signIn();
        }
        if (choise == 2)
        {
            Password pass;
            pass.signUp();
        }
        return 0;
    }
};

int main()
{
    setlocale(LC_ALL, "ru");

    menu Menu;

    Menu.runMenu();

    return 0;
}
