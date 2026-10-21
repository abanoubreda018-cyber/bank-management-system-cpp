/*
  ============================================================================
  TOPIC: Bank System Project [Extention - 1]
  AUTHOR: Eng. Abanoub Reda
  DESCRIPTION: A simple project 
  ============================================================================
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
using namespace std;

const string ClientsFile = "Clients.txt";

// [1] Enums
enum enMainMenuOptions
{
    eShowClientsList = 1, eAddNewClient = 2, eDeleteClient = 3,
    eUpdateClientInfo = 4, eFindClient = 5, eTransactions = 6, eExit = 7
};

enum enTransactionsMenu
{
    eDeposit = 1, eWithdraw = 2, eShowTotalBalances = 3, eBackToMainMenu = 4
};

// [2] Structure
struct stClient
{
    string AccountNumber = "";
    string FullName = "";
    string PIN_Code = "";
    string PhoneNumber = "";
    double AccountBalance = 0;
    bool MarkAsForDelete = false;
};

// [3] Helper Functions
vector<string> SplitString(string Text, const string& Delim)
{
    vector<string> vWords;
    size_t Pos = 0;
    string SWord = "";

    while ((Pos = Text.find(Delim)) != std::string::npos)
    {
        SWord = Text.substr(0, Pos);
        vWords.push_back(SWord);
        Text.erase(0, Pos + Delim.length());
    }
    vWords.push_back(Text);
    return vWords;
}

string TrimLeft(string Text)
{
    for (short i = 0; i < Text.length(); i++)
    {
        if (Text[i] != ' ') return Text.substr(i, Text.length());
    }
    return "";
}

string TrimRight(string Text)
{
    for (short i = Text.length() - 1; i >= 0; i--)
    {
        if (Text[i] != ' ') return Text.substr(0, i + 1);
    }
    return "";
}

string TrimText(string Text)
{
    return TrimLeft(TrimRight(Text));
}

string ConvertFirstLetterForEachWordToCapital(string Text)
{
    bool isFirstLetter = true;
    for (short i = 0; i < Text.length(); i++)
    {
        if (Text[i] != ' ' && isFirstLetter)
        {
            Text[i] = toupper(Text[i]);
        }
        isFirstLetter = (Text[i] == ' ') ? true : false;
    }
    return Text;
}

short ReadNumber(short From, short To)
{
    short Number = 0;
    do
    {
        cin >> Number;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "[!] Invalid input, please enter a valid number: ";
            continue;
        }
    } while (Number < From || Number > To);
    return Number;
}

void ClearScreen()
{
    system("cls");
}

// [4] File System Operations
string ConvertRecordToLine(const stClient& Client, const string& Seperator = "#//#")
{
    return Client.AccountNumber + Seperator + Client.PIN_Code + Seperator +
        Client.FullName + Seperator + Client.PhoneNumber + Seperator +
        to_string(Client.AccountBalance);
}

stClient ConvertLineToRecord(const string& Line, const string& Seperator = "#//#")
{
    vector<string> vWords = SplitString(Line, Seperator);
    stClient Client;

    if (vWords.size() == 5)
    {
        Client.AccountNumber = vWords.at(0);
        Client.PIN_Code = vWords.at(1);
        Client.FullName = vWords.at(2);
        Client.PhoneNumber = vWords.at(3);
        try
        {
            Client.AccountBalance = stod(vWords.at(4));
        }
        catch (const std::exception& e)
        {
            Client.AccountBalance = 0.0;
        }
    }
    return Client;
}

bool FindClientByAccountNumber(const string& AccountNumber, stClient& Client)
{
    fstream File;
    File.open(ClientsFile, ios::in);
    if (File.is_open())
    {
        string Line;
        while (getline(File, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                File.close();
                return true;
            }
        }
        File.close();
    }
    return false;
}

vector<stClient> LoadClientsDataFromFile(const string& FileName)
{
    fstream File;
    vector<stClient> vClients;
    stClient Client;
    string Line = "";

    File.open(FileName, ios::in);
    if (File.is_open())
    {
        while (getline(File, Line))
        {
            if (Line != "")
            {
                Client = ConvertLineToRecord(Line);
                if (Client.AccountNumber != "")
                {
                    vClients.push_back(Client);
                }
            }
        }
        File.close();
    }
    return vClients;
}

bool SaveClientsDataToFile(const string& FileName, const vector<stClient>& vClients)
{
    fstream File;
    File.open(FileName, ios::out);
    if (File.is_open())
    {
        for (const stClient& Client : vClients)
        {
            if (Client.MarkAsForDelete == false)
            {
                File << ConvertRecordToLine(Client) << endl;
            }
        }
        File.close();
        return true;
    }
    return false;
}

bool AddDataLineToFile(const string& FileName, const string& Line)
{
    fstream File;
    File.open(FileName, ios::out | ios::app);
    if (File.is_open())
    {
        File << Line << endl;
        File.close();
        return true;
    }
    return false;
}

// [5] Core System Screens
void PrintClientCard(const stClient& Client)
{
    cout << "\n==========================================\n";
    cout << "============   Client Data  ==============\n";
    cout << "==========================================\n";
    cout << "Account Number  : " << Client.AccountNumber << endl;
    cout << "Client Name     : " << Client.FullName << endl;
    cout << "PIN Code        : " << Client.PIN_Code << endl;
    cout << "Phone Number    : " << Client.PhoneNumber << endl;
    cout << "Account Balance : $" << Client.AccountBalance << endl;
    cout << "==========================================\n";
}

stClient ReadClientData()
{
    stClient Client;
    cout << "Enter PIN Code        : ";
    getline(cin >> ws, Client.PIN_Code);

    cout << "Enter Full Name       : ";
    getline(cin, Client.FullName);
    Client.FullName = ConvertFirstLetterForEachWordToCapital(TrimText(Client.FullName));

    cout << "Enter Phone Number    : ";
    getline(cin, Client.PhoneNumber);

    do
    {
        cout << "Enter Account Balance : ";
        cin >> Client.AccountBalance;
        if (cin.fail() || Client.AccountBalance < 0)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "[!] Invalid balance. Please enter a valid number >= 0.\n";
            Client.AccountBalance = -1;
        }
    } while (Client.AccountBalance < 0);

    return Client;
}

void AddNewClientScreen()
{
    cout << "-------------------------------\n";
    cout << "\tAdd New Client\n";
    cout << "-------------------------------\n";

    stClient Client;
    string AccountNumber = "";
    char AddMore = 'Y';

    do {
        cout << "Enter Account Number  : ";
        cin >> AccountNumber;

        if (!FindClientByAccountNumber(AccountNumber, Client))
        {
            Client = ReadClientData();
            Client.AccountNumber = AccountNumber;
            if (AddDataLineToFile(ClientsFile, ConvertRecordToLine(Client)))
            {
                cout << "\n[-] Done, Client Added Successfully...\n";
            }
            else
            {
                cout << "\n[!] Error: Unable to save client to file!\n";
            }
        }
        else
        {
            cout << "\n[!] Client with account number (" << AccountNumber << ") already exists in bank\n";
        }
        cout << "\nDo you want to add a new client? [Y - N] : ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void DeleteClientScreen()
{
    cout << "-------------------------------\n";
    cout << "\tDelete Client\n";
    cout << "-------------------------------\n";

    stClient Client;
    string AccountNumber = "";
    char Answer = 'N';

    cout << "Enter Account Number  : ";
    cin >> AccountNumber;

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
        cout << "\nAre you sure you want to delete this client? [Y - N] : ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            vector<stClient> vClients = LoadClientsDataFromFile(ClientsFile);
            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C.MarkAsForDelete = true;
                    break;
                }
            }
            if (SaveClientsDataToFile(ClientsFile, vClients))
            {
                cout << "\n[-] Client deleted successfully...\n";
            }
            else
            {
                cout << "\n[!] Error: Failed to save changes to file!\n";
            }
        }
    }
    else
    {
        cout << "\n[!] Client with account number (" << AccountNumber << ") not found!\n";
    }
}

void UpdateClientInfoScreen()
{
    cout << "-------------------------------\n";
    cout << "\tUpdate Client Info\n";
    cout << "-------------------------------\n";

    stClient Client;
    string AccountNumber = "";
    char Answer = 'N';

    cout << "Enter Account Number  : ";
    cin >> AccountNumber;

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
        cout << "\nAre you sure you want to edit client data? [Y - N] : ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            vector<stClient> vClients = LoadClientsDataFromFile(ClientsFile);
            stClient NewClientData = ReadClientData();
            NewClientData.AccountNumber = AccountNumber;

            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = NewClientData;
                    break;
                }
            }
            if (SaveClientsDataToFile(ClientsFile, vClients))
            {
                cout << "\n[-] Client updated successfully...\n";
            }
            else
            {
                cout << "\n[!] Error: Failed to save changes to file!\n";
            }
        }
    }
    else
    {
        cout << "\n[!] Client with account number (" << AccountNumber << ") not found!\n";
    }
}

void FindClientScreen()
{
    cout << "-------------------------------\n";
    cout << "\tFind Client Info\n";
    cout << "-------------------------------\n";
    stClient Client;
    string AccountNumber = "";
    cout << "Enter Account Number  : ";
    cin >> AccountNumber;

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\n[!] Client with account number (" << AccountNumber << ") not found!\n";
    }
}

// [6] Transactions Logic
bool DepositBalanceToClientByAccountNumber(const string& AccountNumber, double Amount, vector<stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance += Amount;
            if (SaveClientsDataToFile(ClientsFile, vClients))
            {
                cout << "\n[+] Done Successfully. New Balance is: $" << C.AccountBalance << endl;
                return true;
            }
            else
            {
                cout << "\n[!] Error: Failed to update balance in file!\n";
                return false;
            }
        }
    }
    return false;
}

void DepositScreen()
{
    cout << "-------------------------------\n";
    cout << "\tDeposit Screen\n";
    cout << "-------------------------------\n";
    stClient Client;
    string AccountNumber = "";
    cout << "Enter Account Number  : ";
    cin >> AccountNumber;

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
        double Amount = 0;
        do
        {
            cout << "\nEnter deposit amount (or 0 to cancel): ";
            cin >> Amount;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "[!] Invalid input, please enter a valid number.\n";
                Amount = -1;
                continue;
            }
            if (Amount == 0)
            {
                cout << "\n[-] Transaction cancelled.\n";
                return;
            }
            if (Amount < 0) cout << "[!] Amount must be greater than 0.\n";
        } while (Amount <= 0);

        char Answer = 'N';
        cout << "\nAre you sure you want to perform this transaction? [Y - N]: ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            vector<stClient> vClients = LoadClientsDataFromFile(ClientsFile);
            DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
        }
    }
    else
    {
        cout << "\n[!] Client not found!\n";
    }
}

void WithdrawScreen()
{
    cout << "-------------------------------\n";
    cout << "\tWithdraw Screen\n";
    cout << "-------------------------------\n";
    stClient Client;
    string AccountNumber = "";
    cout << "Enter Account Number  : ";
    cin >> AccountNumber;

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);

        if (Client.AccountBalance <= 0)
        {
            cout << "\n[!] Withdraw not permitted: Client has zero balance ($0).\n";
            return;
        }

        double Amount = 0;
        do
        {
            cout << "\nEnter withdraw amount (or 0 to cancel): ";
            cin >> Amount;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "[!] Invalid input, please enter a valid number.\n";
                Amount = -1;
                continue;
            }
            if (Amount == 0)
            {
                cout << "\n[-] Transaction cancelled.\n";
                return;
            }
            if (Amount < 0)
            {
                cout << "[!] Amount must be greater than 0.\n";
            }
            else if (Amount > Client.AccountBalance)
            {
                cout << "[!] Amount exceeds current balance ($" << Client.AccountBalance << ").\n";
            }
        } while (Amount <= 0 || Amount > Client.AccountBalance);

        char Answer = 'N';
        cout << "\nAre you sure you want to perform this transaction? [Y - N]: ";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            vector<stClient> vClients = LoadClientsDataFromFile(ClientsFile);
            DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
        }
    }
    else
    {
        cout << "\n[!] Client not found!\n";
    }
}

// [7] Show Lists & Menus (Custom UI)
void ShowBankClientsDataScreen()
{
    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFile);

    cout << setw(60) << "Client List (" << vClients.size() << ") Client(s)\n";
    cout << setfill('-') << setw(120) << "";
    cout << setfill(' ') << endl;
    cout << left << setw(20) << "Account Number";
    cout << "| " << left << setw(12) << "PIN Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(15) << "Phone Number";
    cout << "| " << left << setw(15) << "Account Balance\n";
    cout << setfill('-') << setw(120) << "";
    cout << setfill(' ') << endl;

    if (vClients.size() == 0)
    {
        cout << "\n\t\t\t\tNo clients available in the system\n";
    }
    else
    {
        for (stClient& Client : vClients)
        {
            printf("%-20s| %-12s| %-40s| %-15s| $ %-13.2f\n",
                Client.AccountNumber.c_str(),
                Client.PIN_Code.c_str(),
                Client.FullName.c_str(),
                Client.PhoneNumber.c_str(),
                Client.AccountBalance
            );
        }
    }
    cout << setfill('-') << setw(120) << "";
    cout << setfill(' ') << endl;
}

void ShowAllClientsBalances()
{
    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFile);
    double TotalBalances = 0;

    cout << setw(60) << "Balances List (" << vClients.size() << ") Client(s)\n";
    cout << setfill('-') << setw(120) << "";
    cout << setfill(' ') << endl;
    cout << left << setw(40) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(15) << "Account Balance\n";
    cout << setfill('-') << setw(120) << "";
    cout << setfill(' ') << endl;

    if (vClients.size() == 0)
    {
        cout << "\n\t\t\t\tNo clients available in the system\n";
    }
    else
    {
        for (stClient& Client : vClients)
        {
            printf("%-40s| %-40s| $ %-13.2f\n",
                Client.AccountNumber.c_str(),
                Client.FullName.c_str(),
                Client.AccountBalance
            );
            TotalBalances += Client.AccountBalance;
        }
    }

    cout << setfill('-') << setw(120) << "";
    cout << setfill(' ') << endl;
    cout << "Total Balances \t\t\t\t\t\t\t\t\t  | $ " << TotalBalances << endl;
    cout << setfill('-') << setw(120) << "";
    cout << setfill(' ') << endl;
}

void ShowTransactionsMenu()
{
    ClearScreen();
    cout << setfill('=') << setw(40) << "";
    cout << setfill(' ') << endl;
    cout << "\tTransaction Menu Screen\n";
    cout << setfill('=') << setw(40) << "";
    cout << setfill(' ') << endl;
    cout << "\t[1] Deposit\n";
    cout << "\t[2] Withdraw\n";
    cout << "\t[3] Show Total Balances\n";
    cout << "\t[4] Back To Main Menu\n";
    cout << setfill('=') << setw(40) << "";
    cout << setfill(' ') << endl;
    cout << "Choose what do you want to do [1 - 4] : ";
}

void TransactionMenuLogic()
{
    short Choice = 0;
    do
    {
        ShowTransactionsMenu();
        Choice = ReadNumber(1, 4);
        ClearScreen();

        switch ((enTransactionsMenu)Choice)
        {
        case eDeposit:
            DepositScreen();
            break;
        case eWithdraw:
            WithdrawScreen();
            break;
        case eShowTotalBalances:
            ShowAllClientsBalances();
            break;
        case eBackToMainMenu:
            return;
        }
        cout << "\nPress any key to go back to Transactions Menu...";
        system("pause>nul");
    } while (Choice != eBackToMainMenu);
}

void ShowMainMenuScreen()
{
    ClearScreen();
    cout << setfill('=') << setw(40) << "";
    cout << setfill(' ') << endl;
    cout << "\tBank Main Menu Screen\n";
    cout << setfill('=') << setw(40) << "";
    cout << setfill(' ') << endl;
    cout << "\t[1] Show Clients List\n";
    cout << "\t[2] Add New Client\n";
    cout << "\t[3] Delete Client\n";
    cout << "\t[4] Update Client Info\n";
    cout << "\t[5] Find Client\n";
    cout << "\t[6] Transactions\n";
    cout << "\t[7] Exit\n";
    cout << setfill('=') << setw(40) << "";
    cout << setfill(' ') << endl;
    cout << "Choose what do you want to do [1 - 7] : ";
}

void MainMenuLogic()
{
    short Choice = 0;
    do
    {
        ShowMainMenuScreen();
        Choice = ReadNumber(1, 7);
        ClearScreen();

        switch ((enMainMenuOptions)Choice)
        {
        case eShowClientsList:
            ShowBankClientsDataScreen();
            break;
        case eAddNewClient:
            AddNewClientScreen();
            break;
        case eDeleteClient:
            DeleteClientScreen();
            break;
        case eUpdateClientInfo:
            UpdateClientInfoScreen();
            break;
        case eFindClient:
            FindClientScreen();
            break;
        case eTransactions:
            TransactionMenuLogic();
            continue; // Skip the pause for sub-menu
        case eExit:
            cout << "Goodbye, system is locked...\n";
            return;
        }
        cout << "\nPress any key to go back to Main Menu...";
        system("pause>nul");
    } while (Choice != eExit);
}

int main()
{
    MainMenuLogic();
    return 0;
}