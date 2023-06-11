#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

// console initialization
void console_init()
{
    system("cls");
    std::cout << "\t--- REGISTRATION AND LOGIN - PORTAL ---\n";
}

//// this works most of the time to clear your cin buffer
//  flush_cin_buffer
void flush()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// this is the database file!
std::fstream file("Database.txt", std::ios::in | std::ios::app);

void page_reg()
{
    std::string username, password, confirm;
    std::string line;
    console_init();

    // registration portal
    std::cout << "\n\t       -- REGISTRATION PORTAL -- \n";

    // uname
    std::cout << "\n\t\tUsername : ";
    std::cin >> username;
    flush();

    // check if username exists
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string storedUsername;
        iss >> storedUsername;
        if (storedUsername == username)
        {
            std::cout << "\n\t     -- USERNAME ALREADY EXISTS -- \n";
            std::cout << "\t           Try again? (y): ";
            char choice = 'n';
            std::cin >> choice;
            if (choice == 'y')
            {
                page_reg();
            }
            return;
        }
    }
    file.clear();

    // pass
    std::cout << "\t\tPassword : ";
    std::cin >> password;
    flush();

    // confirm pass
    std::cout << "\n\t\tConfirm \n\t\tPassword : ";
    std::cin >> confirm;
    flush();

    // if passwords dont match
    if (password != confirm)
    {
        std::cout << "\n\n\t     -- PASSWORD DOES NOT MATCH -- \n";
        std::cout << "\n\n\t           Try again? (y): ";
        char choice = 'n';
        std::cin >> choice;
        if (choice == 'y')
        {
            page_reg();
        }
        return;
    }

    // write to file
    file << username << " " << password << "\n";
    file.flush();
    file.clear();

    // success
    std::cout << "\n\t     -- REGISTRATION SUCCESSFUL -- \n";

    return;
}

void page_log()
{
    std::string username, password, line;
    bool flag = false;
    console_init();

    // login portal
    std::cout << "\n\t\t  -- LOGIN PORTAL -- \n";

    // uname
    std::cout << "\n\t\tUsername : ";
    std::cin >> username;
    flush();

    // check if username exists
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string storedUsername;
        iss >> storedUsername;
        if (storedUsername == username)
        {
            flag = true;
            break;
        }
    }
    if (flag = false)
    {
        std::cout << "\n\t     -- USERNAME DOES NOT EXIST -- \n";
        std::cout << "\t           Try again? (y): ";
        char choice = 'n';
        std::cin >> choice;
        if (choice == 'y')
        {
            page_log();
        }
        return;
    }
    file.clear();

    // pass
    std::cout << "\t\tPassword : ";
    std::cin >> password;
    flush();

    // check if password matches
    std::istringstream iss(line);
    std::string storedUsername, storedPassword;
    iss >> storedUsername >> storedPassword;
    if (password != storedPassword)
    {
        std::cout << "\n\n\t       -- INCORRECT PASSWORD -- \n";
        std::cout << "\t           Try again? (y): ";
        char choice = 'n';
        std::cin >> choice;
        if (choice == 'y')
        {
            page_log();
        }
        return;
    }
    file.clear();

    std::cout << "\n\t        -- LOGIN SUCCESSFUL -- \n";

    return;
}

void init_page()
{
    console_init();
    std::cout << "\n\t\t   Choose an option \n\t\t1- Register \n\t\t2- Login \n\t\t3- Exit \n";
    std::cout << "\n\t\t   Your choice : ";
    ////std::cout << "\n\n\t    ";
    ////system("pause");

    short int choice = 1;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        page_reg();
        break;
    case 2:
        page_log();
        break;
    case 3:
        std::cout << "\n\t      -- Program Terminated -- \n";
        exit(1);
    default:
        std::cout << "\n\t\t-- Invalid Choice -- \n";
        std::cout << "\t      -- Program terminated -- \n";
        exit(1);
    }
}

int main()
{
    if (!file.is_open())
    {
        std::cout << "ERROR !\n\t * File not found !\n\t * Link file properly and run again !" << std::endl;
        return 0;
    }

    // page1()
    init_page();
}