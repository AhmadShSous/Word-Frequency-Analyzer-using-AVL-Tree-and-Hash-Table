#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOKEN_SIZE 300
int count_words= 4;
int count_words2=0;
int sizeHash=0;  //size of each line
struct Table{ // node for do hashing
struct Table* hash; //array of struct hashing
char* Data; // array of character
int count;  // frequency of words
};
typedef struct Table* hashTable; //hashtable for change size of array hashing

struct node{  //node for AVLTree
char* Element; //array of character
struct node* Left; //to point in left node
struct node* Right; //to point in right node
int count;  //frequency of words
int Height; //the largest depth
};
typedef struct node* AVLNode; //AVLTree to point in each node



//...............................................
void MakeEmpty( AVLNode T );
AVLNode Find(char* X, AVLNode T );
AVLNode FindMin( AVLNode T );
AVLNode FindMax( AVLNode T );
int Height(AVLNode T);
int Max( int L, int R );
AVLNode SingleRotateWithLeft( AVLNode K2 );
AVLNode SingleRotateWithRight( AVLNode K1);
AVLNode DoubleRotateWithLeft( AVLNode K3 );
AVLNode DoubleRotateWithRight( AVLNode K1 );
AVLNode Insert(char* X,AVLNode T );
void PrintInOrder( AVLNode t);
int sizeOfData();
char* loaingData();
char* filtterWord(char* word);
AVLNode insertInAVLTreeFromFile(char* string,AVLNode T);
AVLNode Delete(char* X,AVLNode T);
int isPrime(int n);
hashTable createHashing(AVLNode T);
int hash1(char* key, int TableSize);
int hash2(char* key, int TableSize);
hashTable insertHashing(hashTable hash,char* text);
int strMyCmp(char* word1,char* word2);
int collisionHandling(hashTable hash,int hash1);
void insertInHashingFromAVL(hashTable hash,AVLNode T);
void printTheElementInHashing(hashTable hash,AVLNode T);
int find (char* text,hashTable hash);
void deleteHashing(char* text,hashTable Hash);
hashTable reahashing(hashTable hash,char* text);
void printAVLTreeInHashing(int rep,AVLNode t);

int main()
{
char* result=loaingData();
char* text;
hashTable hash; //hashtable
hash->hash=NULL;// array of struct hash
AVLNode tree=NULL; //create AVLTree
int selection=0;
do{
printf("please enter number between 1-11: ");
printf("\n\n1. Load data from the file.");
printf("\n2. Create the AVL tree.");
printf("\n3. Insert a word to the AVL tree.");
printf("\n4. Delete a word from the AVL tree");
printf("\n5. Print the words as sorted in the AVL tree.");
printf("\n6. Create the Hash Table.");
printf("\n7. Insert a word to the Hash table.");
printf("\n8. Delete a word from the hash table.");
printf("\n9. Search for a word in the hash table and print its frequency.");
printf("\n10. Print words statistics.");
printf("\n11. Exit\n\n");
printf("The selection is:- ");
scanf("%d", &selection);
printf("\n");
if(selection == 1) text = result;
else if(selection == 2)tree = insertInAVLTreeFromFile(text,tree) ;
else if(selection ==3){
  printf("please enter the word that you want insert:-\n");
  char word[50];
  scanf("%s",word);
  tree=Insert (filtterWord(word),tree);
}
else if(selection == 4){
    printf("please enter the word that you want delete:-\n");
    char word[50];
    scanf("%s",word);
    tree=Delete(filtterWord(word),tree);
}
else if(selection == 5){
    printf("Test to print the word sorted (In-Order):\n");
    printf("word\t||\tfrequency\n");
    PrintInOrder(tree);
}
else if(selection == 6){
        hash= createHashing(tree);
}
else if(selection == 7) {
if(hash->hash == NULL) printf("you don't do create hashing please enter 6 to create hashing");
else{
    printf("please enter the word that you want insert in hashing:-\n");
    char word[50];
    scanf("%s",word);
   hash=insertHashing(hash,filtterWord(word));
 }
}
else if(selection==8){
    printf("please enter the word that you want delete in hashing:-\n");
    char word[50];
    scanf("%s",word);
    deleteHashing(filtterWord(word),hash);
}
else if(selection==9){
    printf("please enter the word that you want search in hashing:-\n");
    char word[50];
    scanf("%s",word);
    int index = find (filtterWord(word),hash);
    if(index==-1) printf("The word not found!");
    else printf("The index is %d and the frequancy %d of word is %s",index,hash->hash[index].count,hash->hash[index].Data);
}
else if (selection== 10){
    printTheElementInHashing(hash,tree);
 }
else if (selection== 11){
    printf("\t!Thank you!");
    MakeEmpty(tree);
}
printf("\n\n");
 }while(selection != 11);

    return 0;
}


int sizeOfData(){ // to return size of all words in file by dividing each line in file
FILE* in;
in =fopen("input.txt","r");
char token[TOKEN_SIZE]; // array of character and size for it is 300
int length=0;
while(fgets(token,sizeof(token),in)!=NULL){ //to divide each line
    strtok(token,"\n");                     //to delete the new line
    int size = strlen(token);               //size is each line
    length+=(size+1);                      //+1 because there are space ending of each line
}
return length;                             // return the length of all words
}

char* loaingData(){                       //return the array of character that that having all of words in file
FILE* in;
in =fopen("input.txt","r");
int length =sizeOfData();                 //the length is the the length of all words with spaces
char* result = (char*)malloc(length);     //malloc of array of character that having all words with space
char token[TOKEN_SIZE];                   //to connect each line in file to array of characters
while(fgets(token,sizeof(token),in)!=NULL){
    strtok(token,"\n");
    strcat(token," ");                     //to adding space in ending of each line
    strcat(result,token);                  //to connect each line to the array of characters
}
result[length]= '\0';                      //ending of the result string
return result;                             //to return the array of characters that having all words with spaces
}


char* filtterWord(char* word){  //to filter words that return result that having just alphabetical characters
int length=0;                   //the length of word with alphabetical characters
for(int i=0;i<strlen(word);i++){   //to reaching in all characters and increase the size if it alphabetical characters to select the new size with alphabetical characters
  if(((int) word[i]>=65 &&  (int) word[i]<=90) || ((int) word[i]>=97 &&(int) word[i]>=122)) length++;
}

int j=0;
char* fillterWord = (char*) malloc(length+1);   //to create the array with new size with alphabetical characters

for(int i=0;i<strlen(word);i++){     //to reaching in all characters and taking the character if it is alphabetical characters

  if(((int) word[i]>=65 &&  (int) word[i]<=90) || ((int) word[i]>=97 &&(int) word[i]<=122)) { //to select if it is alphabetical characters
     fillterWord[j]=word[i];    //to adding the alphabetical characters in new array
     j++;
  }
}
fillterWord[j]='\0';           //ending of new array with just alphabetical characters
return fillterWord;            //return the new array with just alphabetical characters
}


AVLNode insertInAVLTreeFromFile(char* string,AVLNode T){ //to insert from file (array that having all words)
char* token = strtok(string," ");      //to divide in space
while(token!=NULL){                    //dividing all array of characters in space
   char* word= filtterWord(token);     //to filtter word and taking just alphabetical characters
   T = Insert(word,T);                 //insert in AVLTree
   token = strtok(NULL," ");           //dividing in space
   free(word);                         //delete the malloc of word
 }
 return T;
}



void MakeEmpty( AVLNode T )     //to make the avltree null deleting all malloc
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free(T->Element);
        free( T );
    }
}

AVLNode Find(char* X, AVLNode T ) //to find the word in AVL Tree
{
    if( T == NULL )
        return NULL;
    if( strMyCmp(X,T->Element)<0)
        return Find( X, T->Left );
    else if(strMyCmp(X,T->Element)>0)
        return Find( X, T->Right );
    else
        return T;
}

AVLNode FindMin( AVLNode T ) //to find the min string in AVLTree left left...
{
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

AVLNode FindMax( AVLNode T ) //to find the max string in AVLTree right right...
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}


int Height( AVLNode P )     //to return height of each element in AVLTree
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}


int Max( int L, int R ) // to return the max of two integer
{
       if(L>R)return L;
        else return R;
}

// This function can be called only if K2 has a left child
// Perform a rotate between a node (K2) and its left child
//Update heights, then return new root

AVLNode SingleRotateWithLeft( AVLNode K2 )
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  // New root
}


// This function can be called only if K1 has a right child
// Perform a rotate between a node (K1) and its right child
// Update heights, then return new root

AVLNode SingleRotateWithRight( AVLNode K1 )
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  //New root
}

//This function can be called only if K3 has a left
// child and K3's left child has a right child
// Do the left-right double rotation
// Update heights, then return new root

AVLNode DoubleRotateWithLeft( AVLNode K3 )
{
    // Rotate between K1 and K2
    K3->Left = SingleRotateWithRight( K3->Left );

    // Rotate between K3 and K2
    return SingleRotateWithLeft( K3 );
}
// END

//This function can be called only if K1 has a right
// child and K1's right child has a left child
// Do the right-left double rotation
// Update heights, then return new root

AVLNode DoubleRotateWithRight( AVLNode K1 )
{
    //Rotate between K3 and K2
    K1->Right = SingleRotateWithLeft( K1->Right );

    // Rotate between K1 and K2
    return SingleRotateWithRight( K1 );
}


AVLNode Insert(char* X,AVLNode T )
{
    if( T == NULL )
    {
        // Create and return a one-node tree
        T = (AVLNode)malloc( sizeof( struct node));
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
           T->count=1;
           T->Element= (char*)malloc(sizeof(X));
           strcpy(T->Element ,X);
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if( strMyCmp(X,T->Element)<0)
    {
        T->Left = Insert( X, T->Left );
        if( Height( T->Left ) - Height( T->Right ) > 1 ){
            if( strMyCmp(X,T->Left->Element)<0)
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
        }
    }
    else if(strMyCmp(X,T->Element)>0)
    {
        T->Right = Insert( X, T->Right );
        if( Height( T->Right ) - Height( T->Left ) > 1 ){
            if( strMyCmp(X,T->Right->Element)>0)
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );

        }
    }
    else if(strMyCmp(X,T->Element)==0){
            T->count++;
          return T;
    }

    T->Height = Max( Height( T->Left ), Height( T->Right ) )+ 1;

        return T;

}
// END

//in-order print to see the elements
void PrintInOrder( AVLNode t)
{
    if(t==NULL) return;
    if( t != NULL)
    {
        PrintInOrder( t->Left );
        printf("%s\t||\t%d\n", t->Element,t->count);
        PrintInOrder( t->Right );
    }
}




AVLNode Delete(char* X,AVLNode T){
if(T==NULL) printf("The element is not found!");
else if(strMyCmp(X,T->Element)<0){  //Go left
    T->Left = Delete(X,T->Left);
    }
else if(strMyCmp(X,T->Element)>0){  //Go Right
     T->Right=Delete(X,T->Right);
    }
else if(strMyCmp(X,T->Element)==0 && T->count > 1){ //if the element is frequency more than 1
      T->count--;
      return T;
    }
    else{ //after selection the node
    AVLNode temp;
if(T->Right !=NULL && T->Left!=NULL){ //if the node having two children to convert it having one or not anyone
    temp= FindMin(T->Right);
    T->Element = (char*)malloc(sizeof(temp->Element));
    strcpy(T->Element,temp->Element);
    T->Right = Delete(temp->Element,T->Right);
    }
else {    //if the node having one or not having anyone
    temp=T;
    if(T->Left!=NULL){ //if having one in left
      T =T->Left;
      free(temp->Element);
      free(temp);
     }
    else if(T->Right!= NULL){  //if having one in rigth
      T =T->Right;
      free(temp->Element);
      free(temp);
     }
     else{       //if not having any children
     free(temp->Element);
     free(temp);
     T=NULL;
     }
    }
  }

         return T;
if( Height( T->Left ) - Height( T->Right ) > 1 ){ //if the node not balanced from left
  if (Height(T->Left->Left) - Height(T->Left->Right)>=0)
      T = SingleRotateWithLeft( T );
  else
      T = DoubleRotateWithLeft( T );
    }
else if( Height( T->Right ) - Height( T->Left ) > 1 ){ //if the node not balanced from right
  if (Height(T->Right->Right) - Height(T->Right->Left)>=0)
      T = SingleRotateWithRight( T );
  else
      T = DoubleRotateWithRight( T );

    }
        T->Height = Max( Height( T->Left ), Height( T->Right ) )+ 1;

}



int isPrime(int n){ //to check if the number is prime
for(int i=2;i<=n/2;i++){
    if(n%i==0) return 0;
}
return 1;
}


//hashing
//there are struct for hashing and there are array of struct inside it and array of character and frequency


hashTable createHashing(AVLNode T){  //to create hashTable
count_words2 = count_words-1;      //to select the size of hashTable2
count_words++;
while(!isPrime(count_words2)) count_words2--;  //to select the first prime number less than the size of hashTable2
while(!isPrime(count_words)) count_words++; // to select the prime number more than the size of hashTable1
hashTable Hash;                            //to create the struct of hashTable that having array of struct and array of character and frequency
Hash=(hashTable)malloc(sizeof(struct Table));  //to create malloc of struct hashtable
Hash->hash =(hashTable)malloc(sizeof(struct Table)*count_words); //to create malloc for array of struct and the size it
for (int i = 0; i < count_words; ++i) {                          //to define array of character is null in each index of array
    Hash->hash[i].Data = NULL;
}
insertInHashingFromAVL(Hash,T);                                 //to insert from AVLTree to hashing

return Hash;
}

void insertInHashingFromAVL(hashTable hash,AVLNode T){  //to insert from AVLTree to hash
if(T!=NULL){     //if AVL node not null

insertInHashingFromAVL(hash,T->Left);   //to reaching in each element in tree it is in order
int i=T->count;                        //to insert the word if frequency of it is more than 1
while(i>=1){                           //to insert the word in hashing more than 1 if frequency for it is more than 1
hash =insertHashing(hash,T->Element);
i--;
}
insertInHashingFromAVL(hash,T->Right);
 }
}




int hash1(char* key, int TableSize){ //to calculate the index hash1

int hashValue = 0;
int i=0;
while( key[i] != '\0' ){ //to sum of all index in word if it is alphabitical character
if((int)key[i]>=65 && (int)key[i]<=90) hashValue+=32;     //if the character is capital adding 32
hashValue+=(int)key[i];
i++;
}

return (hashValue % TableSize);      //return the sum of index mod tablesize
}



int hash2(char* key, int TableSize){ //to calculate the valueof hash1
int hashValue = 0;
int i=0;
while( key[i] != '\0' ){  //to sum of all index in word if it is alphabitical character
if((int)key[i]>=65 && (int)key[i]<=90) hashValue+=32;   //if the character is capital adding 32
  hashValue+=(int)key[i];
i++;
}
return (TableSize-(hashValue % TableSize)); //return the (count_words2 - sum of index mod count_words2)

}




int strMyCmp(char* word1,char* word2){ //my function to compare two words and the capital and small are same  "Hello" and "hello" considered the same word
int i =0;
int value1=0,value2=0;
while(word1[i]!='\0' && word2[i]!='\0'){ //ending of word1 and word2
 value1=0;value2=0;
 if((int)word1[i]>=65 && (int)word1[i]<=90)value1+=32;    //if word1 capital adding 32
 if((int)word2[i]>=65 && (int)word2[i]<=90)value2+=32;     //if word2 capital adding 32
 if((int)word1[i]+value1 > (int)word2[i]+value2) return 1;  //if word1 larger than word2 return 1
 else if((int)word1[i]+value1 < (int)word2[i]+value2) return -1;       //if word1 smaller than word2 return -1
 i++;
 }
 if(word1[i]!='\0' && word2[i]=='\0') return 1;     //if word1 not end and word2 end return 1
 else if(word2[i]!='\0' && word1[i]=='\0') return -1; //if word1 end and word2 not return -1
 else return 0;                   //if two words ending return 0
}



int collisionHandling(hashTable hash,int Hash){ //to check if there are collision in index of hash if there are element in index
if(hash->hash[Hash].Data!=NULL){ //if there are return 1
          return 1;

}
else return 0;    //if not collision return 0
}



hashTable insertHashing(hashTable hash,char* text){  //to insert word in hash table

    sizeHash++;                                      //number of word in hash table
    if(sizeHash>count_words/1.5){                    //if the word in hashing reaching in 2/3 we do rehashing
    hash =reahashing(hash,text);                     //do rehashing
    }
  int j=0;
  int Hash=(hash1(text,count_words)+j*hash2(text,count_words2))%count_words; //index in hashtable to reduce the index of hash that you want reduce in it
     while(collisionHandling(hash, Hash)){            //if there are collision
            if(strMyCmp(hash->hash[Hash].Data,text)==0){ //if the word is the same in hashing the frequency +1
                hash->hash[Hash].count++;                //the frequency +1
                return hash;                              //return the hash table
            }
        j++;
        Hash=(hash1(text,count_words)+j*hash2(text,count_words2))%count_words; //new index of hashtable after collision
   }
  if(hash->hash[Hash].Data==NULL) hash->hash[Hash].Data = (char*)malloc(sizeof(text)); //new malloc of array characters to reduce string
  hash->hash[Hash].count=1;                                            //the frequency of each new word
  strcpy(hash->hash[Hash].Data,text);                                  //the new word
    return hash;                                                       //return the hashtable
}

int sumIndex(char* string){                                     //return the sum of all characters in string
int i=0;
int sum=0;
while(string[i]!='\0'){
    if((int)string[i]>=65 && (int)string[i]<=90) sum+=((int)string[i]+32);
   else  sum+= (int)string[i];
    i++;
 }
 return sum;
}



hashTable reahashing(hashTable hash,char* text){    //to do rehashing and size array hash increase
printf("enter rehashing...\n");  //begin of rehashing
int oldSize = count_words;  //the old size
count_words =2*count_words;  //the new size of hashing
count_words2= count_words-1;  //the new size of hash2
while(!isPrime(count_words)) count_words++; //to prime
while(!isPrime(count_words2)) count_words2--;
hashTable cop = hash->hash;  //copy of struct hashtable from old hash
hash->hash= (hashTable)malloc(sizeof(struct Table)*count_words); //the new array of hashing with new size
for(int i=0;i<count_words;i++){    //to define the words in new array
    hash->hash[i].Data=NULL;
}
for(int i=0;i<oldSize;i++){     //copy of old array in new array
    if(cop[i].Data!=NULL){
    hash->hash[sumIndex(cop[i].Data)%count_words].count= cop[i].count;
    hash->hash[sumIndex(cop[i].Data)%count_words].Data=(char*)malloc(sizeof(cop[i].Data));
    strcpy( hash->hash[sumIndex(cop[i].Data)%count_words].Data,cop[i].Data);
    }
 }


 printf("end rehashing...\n");     //end of rehashing
 return hash;                      //return the hash table contain array of hash with new size
 }




int find (char* text,hashTable hash){ //to search in hashing
   int j=0, counter = 0;
  int Hash=(hash1(text,count_words)+j*hash2(text,count_words2))%count_words; //select the index in array of hashing
     while(counter < count_words && (hash->hash[Hash].Data == NULL || strMyCmp(hash->hash[Hash].Data,text) != 0)){     //if there are colision
        j++;
        Hash=(hash1(text,count_words)+j*hash2(text,count_words2))%count_words; //if no search in next index by it
        ++counter;
   }
   return counter == count_words ? -1 : Hash;   //if the word not found return -1
 }



void deleteHashing(char* text,hashTable Hash){ //delete the word in hashintg
if(Hash->hash == NULL) printf("you don't do create hashing please enter 6 to create hashing");
else{                                         //if hash is empty
    int index= find(text,Hash);               //index of word in hashing
    if(index==-1)printf("The element not found!"); //if the word is not found in hashing
    else{                                          //if the word is found
        if(Hash->hash[index].count>1) {            //if the frequency of word is larger than 1 the frequency less 1
         Hash->hash[index].count--;
        return;
        }
        Hash->hash[index].Data=NULL;               //to delete word and make it null
        Hash->hash[index].count=0;
    }
 }
}




int flag2=0;//flag to print avltree in hashing

void printTheElementInHashing(hashTable hash,AVLNode T){//to print elements in hashing
if(hash->hash == NULL) printf("you don't do create hashing please enter 6 to create hashing");
else{
    int frequancy1= 0;              //to select the number of words that having frequency one in hashing
    int frequancy2= 0;              //to select the number of words that having frequency more than 1 in hashing
    int indexOfMostFrequancy=0;     //to select the index of word in hashing that having the most frequency
    printf("The all element in hashing:-\n");   //to print all elements in hashing
    printf("word\t||\tfrequency\n");
for(int i= 0;i<count_words;i++){               //to print all elements in hashing
 if(hash->hash[i].Data!=NULL){                 //if Data in hashing not null
        printf("%s\t||\t%d\n",hash->hash[i].Data,hash->hash[i].count);
        if (hash->hash[i].count==1) frequancy1++;
        else{
            frequancy2++;
            if(i+1!=count_words){             //to select the element that having the largest frequency
                if(hash->hash[i+1].count>hash->hash[indexOfMostFrequancy].count) indexOfMostFrequancy=i+1;
            }
        }

  }
 }
    printf("************************************************************\n");
    printf("\nThe number of unique words =%d\nand it is:-\n",frequancy1); //to print the unique elements
    printf("word\t||\tfrequency\n");
 for(int i= 0;i<count_words;i++){
 if(hash->hash[i].Data!=NULL && hash->hash[i].count==1){
        printf("%s\t||\t%d\n",hash->hash[i].Data,hash->hash[i].count);

  }
 }
    printf("************************************************************\n");
    printf("\nThe number of repeated words =%d\n",frequancy2); //to print the repeated words
   int mostCount =hash->hash[indexOfMostFrequancy].count;      //index of the most repeated word
    for(int i= 0;i<count_words;i++){       //to print the most repeated words
 if(hash->hash[i].Data!=NULL && hash->hash[i].count==mostCount){
        printf("*****The most frequent word is= %s and the frequency for it = %d\n",hash->hash[i].Data,hash->hash[i].count);

  }
 }
 printf("the words repeated is:-\n ");  //to print the all repeated words
 printf("word\t||\tfrequency\n");
 for(int i= 0;i<count_words;i++){
 if(hash->hash[i].Data!=NULL && hash->hash[i].count!=1){
        printf("%s\t||\t%d\n",hash->hash[i].Data,hash->hash[i].count);

  }
 }
    printf("************************************************************\n");
    int wordsRepeated=0;
    printf("please enter the specific threshold that repeated is more than it:-\n "); //enter the frequency that you want print the
    scanf("%d", &wordsRepeated);
    printf("\n\n");
    printf("The hashing is:-\n"); //to print words that repeated more than scanning
     printf("word\t||\tfrequency\n");
    int flag=0;
 for(int i= 0;i<count_words;i++){
    if(hash->hash[i].Data!=NULL && hash->hash[i].count>wordsRepeated){
            flag=1;
        printf("%s\t||\t%d\n",hash->hash[i].Data,hash->hash[i].count);

  }
 }
 if(!flag) printf("There are not any element in hashing having frequency more than %d\n", wordsRepeated);//if not any elements having frequency more than scannning
 printf("-------------\n");
 printf("The tree is:-\n");
 printf("word\t||\tfrequency\n");
 printAVLTreeInHashing(wordsRepeated,T); //to print the avltree elements having frequency more than scannning

 if(!flag2){
        printf("There are not any element in Tree having frequency more than %d\n", wordsRepeated); //if not any elements having frequency more than scannning
  }
    flag2=0;

 }
}



void printAVLTreeInHashing(int rep,AVLNode t){  //to print AVLTree nodes in print hashing
 if(t==NULL) return;
    if( t != NULL)
    {
        printAVLTreeInHashing( rep,t->Left );
        if(t->count > rep){                    //if the frequency for word more than the the frequency that you scaning it
        printf("%s\t||\t%d\n", t->Element,t->count);
        flag2=1;
        }
        printAVLTreeInHashing(rep,t->Right );
    }
}
