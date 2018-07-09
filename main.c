#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20
#define R 60
int counter = 0, m = 0, a = 0;
int arraycheck[N];
int arrayExcess[N];

 /*Find count of keys, multiple of 7
  on odd levels of binary tree */

typedef struct node_tree{
	int key, levelT;
	struct node_tree * left, * right;
} ntree;

// functions
ntree * build_tree(ntree *, ntree *, int);
void inorder(ntree *);
void preorder(ntree *, int);
void postorder(ntree *);
void levelorder(ntree *);
int free_tree(ntree *);
void printGivenLevel(ntree* root, int level);
int height(ntree *);

//building the tree
ntree * build_tree(ntree * root, ntree * node, int key){
	if (!node){
        node = (ntree *) malloc(sizeof(ntree));
        if (!node) {
            printf("\nERROR: Bad allocation!");
            exit(1);
        }
        node->left = node->right = NULL;
        node->key = key;

        if (!root)
            return node; // create root

        if (key < root->key)
            root->left = node;
        else
            root->right = node;
        return node;
	}

	if (key < node->key){
        build_tree(node, node->left, key);
	}
	else{
        build_tree(node, node->right, key);
	}

	return root;
}

//function of print keys
void printLevelOrder(ntree * root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++){
        printGivenLevel(root, i);
    }
}

int height(ntree* node)
{
    if (node==NULL)
        return 0;
    else
    {
        int lheight = height(node->left);
        int rheight = height(node->right);

        if (lheight > rheight)
            return(lheight+1);
        else
            return(rheight+1);
    }
}

void printGivenLevel(ntree* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1){
        printf("%d \t", root->key);
    }
    else if (level > 1)
    {
        if(root->left != NULL){
            printGivenLevel(root->left, level-1);
        }
        if(root->right != NULL){
            printGivenLevel(root->right, level-1);
        }
    }
}

void fillingOfArray(ntree * root){
    arrayExcess[a] = root->key;
    a++;
}

//Find count of 7 on odd levels
void findSeven(ntree* h, int levelT){
    if(((levelT%2 == 1) && ((h->key)%7) == 0)){
        counter++;
    }

}

// inorder
void inorder(ntree * h){
	if (h->left)
        inorder(h->left);

	printf("%d\t", h->key);

	if (h->right)
        inorder(h->right);
}

// preorder
void preorder(ntree * h, int levelT){
    h -> levelT = levelT;
    printf("%d\t %d - level\n", h->key, h->levelT);
    findSeven(h, levelT);

    if (h->left){
        preorder(h->left, h->levelT+1);
    }

    if (h->right){
        preorder(h->right, h->levelT+1);
    }
}

// postorder
void postorder(ntree * h){
	if (h->left)
        postorder(h->left);

	if (h->right)
        postorder(h->right);

    printf("%d\t", h->key);
}

// deleting elements from memory
int free_tree(ntree * h){
	static int c = 0;

	if (h->left)
        free_tree(h->left);
	if (h->right)
        free_tree(h->right);

	if (h) {
		c++;
		free(h);
	}
	return c;
}
//////////////////////////////////////////////////////////////////
int main()
{
    FILE *f;
    f = fopen("numbers.txt", "r");

    ntree * root = NULL;
	srand(time(NULL));

	int i = 0;
	int key;

	printf("\t\t*************TREE*************\n");

	for (i = 0; i < N; i++) {
		fscanf(f, "%d", &key); //read information in file
		printf("%d\t", key);
		root = build_tree(root, root, key);
	}

    printf("\n\nINORDER\n");
	inorder(root);
	printf("\n\nPREORDER\n");
	preorder(root, 1);
	printf("\n\nPOSTRDER\n");
	postorder(root);
	printf("\n\nLEVELORDER\n");
	printLevelOrder(root);

	printf("\n\n%d - count of number is divisible without a remainder by 7", counter);
	printf("\n%d nodes were deleted\n", free_tree(root));

	fclose(f);
	return 0;
}
