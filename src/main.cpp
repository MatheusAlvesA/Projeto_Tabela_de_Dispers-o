#include <iostream>
#include <functional>
#include <tuple>

#include "hashtbl.h"

using namespace std;

struct Account {
    std::string mClientName;// (key) Client's name.
    int mBankCode;          // (key) Bank code.
    int mBranchCode;        // (key) Branch code.
    int mNumber;            // (key) Account number.
    float mBalance;         // Account balance.

    using AcctKey = int;

    Account( std::string _Name = "<empty>",
             int _BankCode = 1,  // Banco do Brasil.
             int _BranchCode = 1668, // Agencia UFRN.
             int _Number = 0,
             float _Balance = 0.f )
        :  mClientName( _Name ),
           mBankCode( _BankCode ),
           mBranchCode( _BranchCode ), 
           mNumber( _Number ), 
           mBalance( _Balance )
        { /* Empty */ }

    /*!
     * \brief Gera a chave (versão 1) que eh igual a conta corrente.
     */
    AcctKey getKey () const
    {
        return mNumber;
    }

    const Account& operator= ( const Account& rhs ) {
        // Avoid assigning to itself.
        if( this != &rhs ) {
            // Copy new values.
            this->mClientName = rhs.mClientName;
            this->mBankCode   = rhs.mBankCode;
            this->mBranchCode = rhs.mBranchCode;
            this->mNumber     = rhs.mNumber;
            this->mBalance    = rhs.mBalance;
        }
        return *this;
    }

    //TODO friend para imprimir
    inline friend std::ostream &operator<< ( std::ostream& _os, const Account& _acc ) {
        _os << "[ Client: <"  << _acc.mClientName <<
               "> Bank: <"    << _acc.mBankCode <<
               "> Branch: <"  << _acc.mBranchCode <<
               "> Number: <"  << _acc.mNumber <<
               "> Balance: <" << _acc.mBalance << "> ]";
        return _os;
    }
};


struct KeyHash {
    std::size_t operator()(const Account::AcctKey& k) const {
        return  std::hash<int>()( k );
    }
};
 
struct KeyEqual {
    bool operator()(const Account::AcctKey& lhs, const Account::AcctKey& rhs) const {
        return lhs == rhs;
    }
};


int main( void ) {
    MyHashTable::HashTbl< Account::AcctKey, Account > accounts(20); // Hash table shall heve size 23.
    Account MyAccts[] =
    {
        { "Jose Silva",    1, 1668, 20123, 1500.f },
        { "Carlos Prado",  1, 1668, 35091, 1250.f },
        { "Aline Bastos", 13,   33, 55723,  500.f },
        { "Pedro Gomes",   1, 1801, 87661, 5800.f },
    };

    Account::AcctKey searchKey; // An account key
    auto nAccts = sizeof( MyAccts ) / sizeof( Account );

    for ( auto i(0u) ; i < nAccts ; ++i )
    {
        accounts.insert( MyAccts[i].getKey() , MyAccts[i] );
    }

    accounts.showStructure();



#ifdef _NOT_NOW
    // Checks for accounts and prints records if found
    cout << endl;
    cout << "Enter account number (CTRL+D to exit program): ";
    while ( cin >> searchKey )
    {
        if ( accounts.retrieve( searchKey, acct ) )
        {
            cout << acct.mNumber << " " << acct.mBalance << endl;
            cout << "Removing this account....\n";
            accounts.remove( acct.getKey() );
        }
        else
            cout << "Account " << searchKey << " not found." << endl;

        cout << "Enter account number (CTRL+D to exit program): ";
    }
#endif

    std::cout << "\n>>> Normal exiting...\n";

    return EXIT_SUCCESS;
}