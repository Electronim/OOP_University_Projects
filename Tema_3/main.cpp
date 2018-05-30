// Created 2018 PETRASCO SANDU

#include "cell.h"
#include "library.h"

void MENU(){
    cout << "\t~~~ MY LIBRARY ~~~\n\n\n";
    cout << "\t----> MENU <----\n";
    cout << "1. ADD a NUMBER in the library\n";
    cout << "2. ADD a TEXT in the library\n";
    cout << "3. ADD a COMPLEX NUMBER in the library\n";
    cout << "4. ADD an ADDRESS in the library\n";
    cout << "5. REMOVE by NAME\n";
    cout << "6. REMOVE by ID\n";
    cout << "7. GET INFO by NAME\n";
    cout << "8. GET INFO by ID\n";
    cout << "9. PRINT ALL INFOs\n";
    cout << "0. EXIT\n";
}

void CHOOSE(){
    long long t, idx;
    string name;

    Library *L = Library::getInstance();

    while (1){
        cout << "\nWrite an input between 0-9: "; cin >> t;
        Cell* info = NULL;

        switch (t){
            case 0:{
                cout << "SUCCESSFUL EXIT!\n";
                delete L;
                exit(0);
            }
            case 1: {
                info = new Number;
                cin >> *info;

                cout << "Write a NAME for this info (if not, hit ENTER): ";
                getline(cin, name);
                getline(cin, name);
                if (name == "\n") name = "";
                L->put(info, name);

                break;
            }

            case 2: {
                info = new Text;
                cin >> *info;

                cout << "Write a NAME for this info (if not, hit ENTER): ";
                getline(cin, name);
                if (name == "\n") name = "";
                L->put(info, name);

                break;
            }

            case 3: {
                info = new Complex;
                cin >> *info;

                cout << "Write a NAME for this info (if not, hit ENTER): ";
                getline(cin, name);
                getline(cin, name);
                if (name == "\n") name = "";
                L->put(info, name);

                break;
            }

            case 4: {
                info = new Address;
                cin >> *info;

                cout << "Write a NAME for this info (if not, hit ENTER): ";
                getline(cin, name);
                getline(cin, name);
                if (name == "\n") name = "";
                L->put(info, name);

                break;
            }

            case 5: {
                cout << "Write the NAME of the info you want to REMOVE: ";
                getline(cin, name);
                getline(cin, name);
                L->remove(cout, name);
                break;
            }

            case 6: {
                cout << "Write the ID of the info you want to REMOVE: ";
                cin >> idx;
                L->remove(cout, idx);
                break;
            }

            case 7: {
                cout << "Write the NAME of the info you want to CHECK: ";
                getline(cin, name);
                getline(cin, name);
                L->get(cout, name);
                break;
            }

            case 8: {
                cout << "Write the ID of the info you want to CHECK: ";
                cin >> idx;
                L->get(cout, idx);
                break;
            }

            case 9: {
                cout << *L;
                break;;
            }

            default: {
                cout << "Wrong INPUT! Try again!\n";
                break;
            }
        }

        cout << "----------------------------\n";
    }
}

int main(){
    MENU();
    try{
        CHOOSE();
    } catch(invalid_argument &exception){
        cout << exception.what() << "!\n";
        exit(0);
    }

    return 0;
}