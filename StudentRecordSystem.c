 /*
   ____                 ___   __                      __    
  /  _/  _____ ____    / _ | / /  __ ____ _  ___ ____/ /__ _
 _/ /| |/ / _ `/ _ \  / __ |/ _ \/ // /  ' \/ _ `/ _  / _ `/
/___/|___/\_,_/_//_/ /_/ |_/_//_/\_,_/_/_/_/\_,_/\_,_/\_,_/ 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definition of student structure
struct student{
    int iD;
    char fname[21]; // 20 characters and 1 null ending char
    char lname[21]; // 20 characters and 1 null ending character
    float score;
    char zipcode[10];
};

// definition of node for BST
struct node {
  struct student data;
  struct node* left;
  struct node* right;
};

// funct to create new node in heap, returns the new node
struct node* createNode(struct student data){

  // definition of new node in heap
  struct node* newNode = (struct node*)malloc(sizeof(struct node));

  // setting passed student data into newly created node
  newNode->data = data;
  newNode->left = newNode->right = NULL;
  return newNode;
}

/* func to insert data in BST, returns address of root node */
struct node* insert(struct node* root,struct student data){
  if(root == NULL){ // empty tree
    root = createNode(data);
  }

  /* check if passed ID is the same as an already existing ID */
  else if(root->data.iD == data.iD){
    printf("Sorry that ID already exists.\n");
    printf("Enter a new record with a different ID: ");
    return NULL;
  }

  /* if ID is less than root, insert to left subtree */
  else if(data.iD < root->data.iD){
    root->left = insert(root->left,data);
  }

  /* else (inserted ID is greater than), insert in right subtree */
  else{
    root->right = insert(root->right,data);
  }

  return root;
}

/* function to print nodes using InOrder */
void printInOrder(struct node* root){
  if(root == NULL){ // base condition for in order recursion
    return;
  }

  /* first traverses to the left */
  printInOrder(root->left);
  /* once recursion hits base condition it will return and print */
  printf("Student ID: %d, ",root->data.iD);
  printf("First Name: %s, ",root->data.fname);
  printf("Last Name: %s, ",root->data.lname);
  printf("Score: %.2f, ",root->data.score);
  printf("Zip code: %s\n",root->data.zipcode);
  /* following the 'in order' pattern, function will check right sides
  after a NULL node has been encountered on the left */
  printInOrder(root->right);
}

/* function to find minimum in a tree */
struct node* findmin(struct node* root){
    while(root->left != NULL){
      root = root->left;
    }
    return root;
}

/* function to delete a record from tree */
struct node* delete(struct node* root, struct student data){
  if(root == NULL){ // check if empty tree
    return root;
  }

  // traverse if ID is less
  else if(strcmp(root->data.lname,data.lname) != 0){
    root->left = delete(root->left,data); // go left if target not found
    root->right = delete(root->right,data); // go right if target not found
  }

  /* else would mean tree isn't empty */
  else{
    /* if found node has no child */
    if(root->left == NULL && root->right == NULL){
      free(root);
      root = NULL;
    }
    // 1 child
    else if(root->left == NULL){ // if left child is NULL
      struct node* temp = root;
      root = root->right;
      free(temp);
      temp = NULL;
    }
    else if(root->right == NULL){ // if right child is NULL
      struct node* temp = root;
      root = root->left;
      free(temp);
      temp = NULL;
    }
    // 2 children
    else{
      struct node* temp = findmin(root->right);
      root->data = temp->data;
      root->right = delete(root->right,temp->data);
    }
  }
  return root;
}

void printZip(struct node* root, struct student data){
  if(root == NULL){ // checking for empty tree
    return;
  }
  printZip(root->left,data); // in order requires left subtree traversed first
  /* if the zipcode passed and zipcode in node matches then print it */
  if(strcmp(root->data.zipcode,data.zipcode) == 0){
    /* print current root */
    printf("Student ID: %d, ",root->data.iD);
    printf("First Name: %s, ",root->data.fname);
    printf("Last Name: %s, ",root->data.lname);
    printf("Score: %.2f, ",root->data.score);
    printf("Zip code: %s\n",root->data.zipcode);
  }
  printZip(root->right,data); // following inorder algorithm right is checked after root
}

void printInRange(struct node* root,float min,float max){
  if(root == NULL){ // check for empty tree
    return;
  }
  printInRange(root->left,min,max);
  /* if IN range */
  if(root->data.score >= min && root->data.score <= max){
    /* print current root */
    printf("Student ID: %d, ",root->data.iD);
    printf("First Name: %s, ",root->data.fname);
    printf("Last Name: %s, ",root->data.lname);
    printf("Score: %.2f, ",root->data.score);
    printf("Zip code: %s\n",root->data.zipcode);
  }
  printInRange(root->right,min,max);
}

int getScoresInArray(struct node* root, float scoresArr[],int index){
  if(root == NULL){ // base condition for stopping recursion
    return index;
  }
  /* setting current nodes score into array */
  scoresArr[index] = root->data.score;
  index++;

  if(root->left != NULL){ // checking if left subtree NULL
    index = getScoresInArray(root->left,scoresArr,index);
  }
  if(root->right != NULL){ // check if right subtree is NULL
    index = getScoresInArray(root->right, scoresArr, index);
  }

  return index;
}

void findMedian(float scoresArr[],int index){
  int i, j, cnt = 0; // cnt keeps track of students above median
  float temp, medianScores;

  /* bubble sort */
  for(i = 0;i < index - 1; i++){
    for(j = i + 1; j < index; j++){
      if(scoresArr[j] < scoresArr[i]){
        temp = scoresArr[i];
        scoresArr[i] = scoresArr[j];
        scoresArr[j] = temp;
      }
    }
  }
  /* now continuing to finding the median after sorted */
  if( index % 2 == 0){ // if size is even
    medianScores = (scoresArr[index/2] + scoresArr[index/2 -1])/2.0;
  }
  else{ // otherwise size is odd
    medianScores = scoresArr[index/2];
  }

  /* traverses the scoresArr to find how many are above median */
  for(i = 0;i < index; i++){
    if(medianScores < scoresArr[i]){
      cnt++; // if a target found increment count
    }
  }
  /* printing median value and student above that median */
  printf("The median is: %.2f\n",medianScores);
  printf("Number of students above the median: %d\n",cnt);
}

int main(){
  /* definition of student data to be passed */
  struct student* recordToPass = (struct student*)malloc(sizeof(struct student));
  struct node* root = NULL; //creats an empty tree
  int recordAmt = 0, i, sid, choice;

  /* loop to check amount of records were meeting minimum */
  while(recordAmt < 5){
    printf("Enter the amount of records to be stored (min 5): ");
    scanf("%d",&recordAmt); // scan amount of records to be stored
    if(recordAmt < 5){
      /* inform user they need more records */
      printf("Sorry, need more records to store. Try again.\n");
    }
  }
  /* prompt user to enter records in suitable format */
  printf("Please input records of students (enter a new line after each ");
  printf("record),\nwith following format(Student ID numbers range ");
  printf("from 1000-1100): <firstname ");
  printf("lastname score studentID zipcode>\n");

  /* creating node for each record and inserting into tree */
  for(i = 0; i < recordAmt; i++){
    sid = 0;
    /* check for suitable ID range entered and scan information
    for records to be passed */
    while(sid < 1000 || sid > 1100 || root == NULL){
      scanf("%s",recordToPass->fname);
      scanf("%s",recordToPass->lname);
      scanf("%f",&recordToPass->score);
      scanf("%d",&sid);
      scanf("%s",recordToPass->zipcode);
      while(sid < 1000 || sid > 1100){
        printf("Sorry, that ID number is out of acceptable range.\n");
        printf("Please enter an ID within range (just enter the ID): ");
        scanf("%d",&sid);
      }
      recordToPass->iD = sid; // once id checked, set it to record
      root = insert(root,*recordToPass); // insert the newly created record
    }
  }

  /* menu will print continously until choice is 0 aka exit */
  do{
    printf("\n\n----------MENU----------\n");
    printf("Print records (press 1)\n");
    printf("Add a new record (press 2)\n");
    printf("Delete record(s) (press 3)\n");
    printf("Search by zip code (press 4)\n");
    printf("Search by score range (press 5)\n");
    printf("Find median score (press 6)\n");
    printf("Exit the program (press 0)\n");
    scanf("%d",&choice); // taking user input for choice

    /* choice to print records */
    if(choice == 1){
      printInOrder(root);
    }

    /* choice to add a new record */
    else if(choice == 2){
      /* prompt user to enter records in suitable format */
      printf("Please input record of student to be added ");
      printf("\nin the following format(Student ID numbers range ");
      printf("from 1000-1100): <firstname ");
      printf("lastname score studentID zipcode>\n");

      sid = 0;
      /* check for suitable ID range entered and scan information
      for records to be passed */
      while(sid < 1000 || sid > 1100 || root == NULL){
        scanf("%s",recordToPass->fname);
        scanf("%s",recordToPass->lname);
        scanf("%f",&recordToPass->score);
        scanf("%d",&sid);
        scanf("%s",recordToPass->zipcode);
        while(sid < 1000 || sid > 1100){
          printf("Sorry, that ID number is out of acceptable range.\n");
          printf("Please enter an ID within range (just enter the ID): ");
          scanf("%d",&sid);
        }
        recordToPass->iD = sid; // once id checked, set it to record
        root = insert(root,*recordToPass); // insert the newly created record
      }
    }

    /* choice to delete a record */
    else if(choice == 3){
      char c;
      scanf("%c",&c); // eats character in buffer
      /* ask user for last name to be deleted */
      printf("Enter the last name of the record you would like to delete: ");
      scanf("%s",recordToPass->lname);
      root = delete(root,*recordToPass);
    }

    /* choice to print students given zipcodes */
    else if(choice == 4){
      printf("Enter zip code to search by: ");
      /* scanning zip code to be printed for reference */
      scanf("%s",recordToPass->zipcode);
      printZip(root,*recordToPass);
    }

    /* choice to search in given score range */
    else if(choice == 5){
      float min=0, max=0; // variables for searching range of scores
      printf("Enter minimum score to search by: ");
      scanf("%f",&min);
      printf("\nEnter maximum score to search by: ");
      scanf("%f",&max);
      printInRange(root,min,max);
    }

    /* choice to find the median score */
    else if(choice == 6){
      float scoresArr[1000]; // array to store the scores of students to be sorted
      int index = 0; // will keep track of which index is being traversed
      index = getScoresInArray(root,scoresArr,index);
      findMedian(scoresArr,index);
    }
  }
  while(choice != 0);

  return 0;
}
