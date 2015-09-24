// wirtten by Matthew Yu for assignment 2 history use.
//2015/09/23



typedef struct node *Node;
typedef struct list *List;



// new list

List newList();


// append to first

void append(List,int);


//return total amounts of elements

int totalAmont(List);

//return specific element at certain position

int getValue(List,int index);

//get First


//set data at specific index consider head as 0
void setValue(List,int index,int data);

void freeList(List);

int checkFirstSix(List list, int data);
