#include <iostream>

#include "hashtbl.h"

//! MyHashTable namespace encapsulates all class related to a simple hash function definition.
namespace MyHashTable {

    //----------------------------------------------------------------------------------------
    //! Default construtor.
    /*! Creates a hash table of the required capacity, which uses an external hash function
     *  that maps keys to unsigned long integers.
     *  If no external hash function is provided, an \r UndefinedHashFunctionException is generated.
     *  \param _initSize Required hash table capacity.
     *  \param _pfHF Pointer to an external hash function that does the first hashing and returns an unsigned long int.
     *  \throw UndefinedHashFunctionException if no external hash function is provided.
    */
      bool is_primo(unsigned int testar) { // essa é uma função auxiliar usada apenas para dizer seu um numero é primo ou não
        for(unsigned int x = 2; x < testar; x++) {
          if(testar%x == 0) return false; // se é divisivel por alguem então não é primo
        }
        return true;
    }
    unsigned int primo(unsigned int primo) { // retorna o primeiro próximo primo ao numero passado
        while(true) {
            if(is_primo(primo))
              return primo;
          else primo++;
        }
        return primo; // não deve chegar aqui
    }
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    HashTbl< KeyType, DataType, KeyHash, KeyEqual >::HashTbl ( int _initSize )
        : mSize( _initSize ), mCount( 0u )
    {
    	this->mSize = primo(this->mSize); // seta o tamanho como o  primo seguinte
        this->mpDataTable = new std::list< Entry >[mSize]; // criando a tabela dinamicamente
    }

    //----------------------------------------------------------------------------------------
    //! Destrutor that just frees the table memory, clearing all collision lists.
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    HashTbl< KeyType, DataType, KeyHash, KeyEqual >::~HashTbl ()
    {
        this->clear(); // limpando primeiro as listas
        delete [] this->mpDataTable; // deletando a tabela em si
    }

    //----------------------------------------------------------------------------------------
    //! Inserts data into the hash table.
    /*! For an insertion to occur, the client code should provide a key and the data itself
     *  If the data is already stored in the table, the function updates the data with the
     *  new information provided.
     *  \param _newKey Key associated with the data, used to get to the stored information.
     *  \param _newDataItem Data to be stored or updated, in case the information is already stored in the hash table.
     *  \return true if the data is already stored in the table and it is updated; false, otherwise.
     *  \throw std::bad_alloc In case no memory is available for dynamic allocation required in the insertion procedure.
    */
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl< KeyType, DataType, KeyHash, KeyEqual >::insert ( const KeyType & _newKey, const DataType & _newDataItem ) throw ( std::bad_alloc )
    {
    	KeyHash hash; // usada para retornar o hash
    	KeyEqual igual; // usada para comparar duas chaves
        HashEntry<KeyType, DataType > novo(_newKey, _newDataItem); // criando o novo objeto
        if(!this->mpDataTable[hash(_newKey)%this->mSize].empty()) { // se naquela posição já existe alguem
            typename std::list<Entry>::iterator i = this->mpDataTable[hash(_newKey)%this->mSize].begin(); // criando um iterador para suporte
        	for(unsigned int x = 0;x < this->mpDataTable[hash(_newKey)%this->mSize].size();x++) { // percorrer os elementos daquela lista naquela posição
             Entry temp = *i; // variavel que guarda a entrada que será lida nessa "volta" do loop
        	if(igual(temp.mKey, _newKey)) { // compara, se for igual então apenas atualiza a informação
        		temp.mData = _newDataItem; // atualizando a informação na entrada já existente
        		return false; // avisando que a chava já existia
        	}
        	i++; // caso não seja igual contitua procurando
       	} // caso não encontre uma chave igual...
        }// ou nem mesmo existam entradas naquela posição...
        this->mpDataTable[hash(_newKey)%this->mSize].push_back(novo); // insere no final da lista já existente
        this->mCount++; // almentando tamanho lógico
        return true; // retornando verdadeiro pois foi a primeira inserção
    }


    //----------------------------------------------------------------------------------------
    //! Removes data from the hash table.
    /*! Removse a data item from the table, based on the key associated with the data.
     *  If the data cannot be found, false is returned; otherwise, true is returned instead.
     *  \param _searchKey Data key to search for in the table.
     *  \return true if the data item is found; false, otherwise.
    */
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl< KeyType, DataType, KeyHash, KeyEqual >::remove ( const KeyType & _searchKey )
    {
    	KeyHash hash; // para descobrir a hash
    	KeyEqual igual; // para descobrir se duas chaves são iguais
        int local = hash(_searchKey)%this->mSize; // pega a hash da chave e escalona com o tamanho da tabela
        if(this->mpDataTable[local].isEmpty()) return false; //o elemento nao existe
       
          typename std::list<Entry>::iterator i = this->mpDataTable[hash(_searchKey)%this->mSize].begin(); // criando um iterador de auxilio
        	for(unsigned int x = 0;x < this->mpDataTable[hash(_searchKey)%this->mSize].size();x++) { // percorrendo toda lista naquela posição
                Entry temp = *i; // variavel auxiliar
        	if(igual(temp.mKey, _searchKey)) { // se encontrar alguem com chave igual
        		this->mpDataTable[hash(_searchKey)%this->mSize].erase(i); //deleta esse alguem
        		return true; // avisa que deu certo
        	}
        	i++; // continua a busca indo para o próximo elemento
       	}
        
        return false; // não encontrou ninguem com a mesma chave
    }
    

    //----------------------------------------------------------------------------------------
    //! Retrieves data from the table.
    /*! Retrieves a data item from the table, based on the key associated with the data.
     *  If the data cannot be found, false is returned; otherwise, true is returned instead.
     *  \param _searchKey Data key to search for in the table.
     *  \param _dataItem Data record to be filled in when data item is found.
     *  \return true if the data item is found; false, otherwise.
    */
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl< KeyType, DataType, KeyHash, KeyEqual >::retrieve ( const KeyType & _searchKey, DataType & _dataItem ) const
    {
    	KeyHash hash;
        int local = hash(_searchKey)%this->mSize; // conseguindo a posição
        if(this->mpDataTable[local].isEmpty()) return false; // se a chave não existe então retorna false
        else {
            typename std::list<Entry>::iterator i = this->mpDataTable[hash(_searchKey)%this->mSize].begin(); // iterador de auxilio
            KeyEqual igual;
        	for(unsigned int x = 0;x < this->mpDataTable[hash(_searchKey)%this->mSize].size();x++) { // percorre aquela linha
             Entry temp = *i; // variavel auxiliar
        	if(igual(temp.mKey, _searchKey)) { // se for igual
        		_dataItem = temp.mData; // seta o valor para retorno
        		return true; // e avisa que conseguiu encontrar
        	}
        	i++; // priximo elemento da lista
       	}
        }
        return false; // nao achou a chave
    }

    //! Clears the data table.
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    void HashTbl< KeyType, DataType, KeyHash, KeyEqual >::clear ()
    {
        for(unsigned int x = 0; x < this->mSize; x++) {
         this->mpDataTable[x].clear(); //executando o método de delecao da propria lista
        }
        this->mCount = 0; //zerando o tamanho
    }

  //! almenta a capacidade da tabela
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    void HashTbl< KeyType, DataType, KeyHash, KeyEqual >::rehash ()
    {
    KeyHash hash;
    this->mSize *= 2; // dobrar tamanho
        std::list< Entry > *nova = new std::list< Entry >[this->mSize]; // o ponteiro da nova tabela
        for(unsigned int x = 0;x < this->mSize/2;x++) { // percorrendo a tabela antiga até o final
        	if(!this->mpDataTable[x].isEmpty()) { // se encontrar alguma posição com elementos ...
                Entry temp = this->mpDataTable[x].Front(); // pegando uma entrada
        		nova[hash(temp.mKey)%this->mSize] = this->mpDataTable[x]; //... põe esse elemento na nova tabela devidamente reposicionado
        	}
        }
       delete [] this->mpDataTable; // deletando a antiga
       this->mpDataTable = nova; // atualizando o ponteiro
    }

    //! Tests whether the table is empty.
    /*!
     * \return true is table is empty, false otherwise.
     */
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    bool HashTbl< KeyType, DataType, KeyHash, KeyEqual >::isEmpty () const
    {
        return ( mCount == 0 );
    }

    //! Counts the number of elements currently stored in the table.
    /*!
     * \return The current number of elements in the table.
     */
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    unsigned long int HashTbl< KeyType, DataType, KeyHash, KeyEqual >::count () const
    {
        return mCount;
    }

    //! Prints out the hash table content.
    template < typename KeyType, typename DataType, typename KeyHash, typename KeyEqual >
    void HashTbl< KeyType, DataType, KeyHash, KeyEqual >::showStructure () const
    {
        KeyHash hashFn;

        // Traverse the list associated with the based address (idx), calculated before.
        for( auto i(0) ; i < mSize; ++i )
        {
            std::cout << i << " :{ key=";
            for( auto & e : mpDataTable[ i ] )
            {
                std::cout << hashFn( e.mKey ) << " ; " << e.mData << " " ;
            }
            std::cout << "}\n";
        }
    }

} // namespace MyHashTable