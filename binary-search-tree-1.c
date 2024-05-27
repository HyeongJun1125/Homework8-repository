/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node **h);

/* functions that you have to implement */
void inorderTraversal(Node *ptr);			/* recursive inorder traversal */
void preorderTraversal(Node *ptr);			/* recursive preorder traversal */
void postorderTraversal(Node *ptr);			/* recursive postorder traversal */
int insert(Node *head, int key);			/* insert a node to the tree */
int deleteLeafNode(Node *head, int key);	/* delete the leaf node for the key */
Node *searchRecursive(Node *ptr, int key);	/* search the node for the key */
Node *searchIterative(Node *head, int key); /* search the node for the key */
int freeBST(Node *head);					/* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int main()
{
	printf("\n2021041069 ������");
	char command;
	int key;
	Node *head = NULL;
	Node *ptr = NULL; /* temp */

	do
	{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command)
		{
		case 'z':
		case 'Z':
			initializeBST(&head);
			break;
		case 'q':
		case 'Q':
			freeBST(head);
			break;
		case 'n':
		case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd':
		case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f':
		case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's':
		case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if (ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i':
		case 'I':
			inorderTraversal(head->left);
			break;
		case 'p':
		case 'P':
			preorderTraversal(head->left);
			break;
		case 't':
		case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node **h)
{

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node *)malloc(sizeof(Node));
	(*h)->left = NULL; /* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}

void inorderTraversal(Node *ptr) // ���� ��ȸ
{
	// ptr : head->left
	if (ptr != NULL)
	{
		inorderTraversal(ptr->left);  // Ʈ���� �����ϰ� ���� ����
		printf("[%d] ", ptr->key);	  // �߾� ���
		inorderTraversal(ptr->right); // ������ �ڽ� ���
	}
}

void preorderTraversal(Node *ptr) // ���� ��ȸ
{
	if (ptr != NULL)
	{
		printf("[%d] ", ptr->key);	   // �߾� ���
		preorderTraversal(ptr->left);  // ���� �ڽ� ���
		preorderTraversal(ptr->right); // ������ �ڽ� ���
	}
}

void postorderTraversal(Node *ptr) // ���� ��ȸ
{
	if (ptr != NULL)
	{
		postorderTraversal(ptr->left);	// ���� �ڽ� ���
		postorderTraversal(ptr->right); // ������ �ڽ� ���
		printf("[%d] ", ptr->key);		// �߾� ���
	}
}

int insert(Node *head, int key) // ����
{
	Node *newNode = (Node *)malloc(sizeof(Node)); // �߰��� ��带 ���� ���� �Ҵ�
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	Node *prev = NULL;
	Node *ptr = head->left; // �� root�� head->left

	if (ptr == NULL)
	{
		// ***** ptr=newNode�� �ؼ� �ȵ� ���� :
		// ptr�� head->left�� ����Ű�� ���� ���� ���� ����Ű����
		// ptr�� newNode�� ����ų �� head�ʹ� ���������̹Ƿ�
		head->left = newNode;
		return 0;
	}

	while (ptr) // ����Ű�� ���� �����ϴ� ����
	{
		prev = ptr;
		if (newNode->key < ptr->key)	  // ptr�� ������ ������
			ptr = ptr->left;			  // ��������
		else if (newNode->key > ptr->key) // ptr�� ������ ũ�ٸ�
			ptr = ptr->right;			  // ����������
		else							  // �̹� ����ִ� ���� �����ϴٸ�
			return 0;					  // ����
	}
	// Ž���� �������� �� ptr : NULL, prev : ������ ���
	if (newNode->key < prev->key) // ������ ����� ������ �۴ٸ�
		prev->left = newNode;	  // ���� �ڽ� ���� �̾��ְ�
	else						  // ũ�ٸ�
		prev->right = newNode;	  // ������ �ڽ� ��忡 �̾���
	return 0;
}

int deleteLeafNode(Node *head, int key) // �� ����� ����
{
	Node *ptr = head->left;
	Node *prev = NULL;

	if (ptr == NULL) // head�� ���� �������� ���� ���
		return 0;

	while (ptr && ptr->key != key) // head�� ���� �����ϸ� key���� �߰��� ������ �ݺ�.
	{
		prev = ptr;
		if (key < ptr->key)	  // head�������� key�� ����Ű�� key���� ������
			ptr = ptr->left;  // �������� �̵�
		else				  // �׷��� ������ (Ŭ ���)
			ptr = ptr->right; // ���������� �̵�
	}

	// Ž���� ����ǵ��� ���� ã�� ���ϰų�, key���� ã���� ���� Case �и�.

	// ***** ptr == NULL �� ���ǹ��� key���� ã�� ��캸�� ���� ���;� �ϴ� ���� :
	// ptr->key == key�� ��� ���� ptr==NULL�̸� ���� �߻�.
	// ���� �ݵ�� ����Ǿ�� ��.

	if (ptr == NULL) // ���� ã�� ������ ���
	{
		printf("The node [%d] does not exist\n", key);
		return 0;
	}

	// ������ Two case�� ������ �ɷ����� ������
	//  ptr->key == key�� �����̹Ƿ�
	// ���� if�� �Ƚᵵ ������ �������� ���� ����.

	if (ptr->key == key) // ���� ã���� ���
	{
		if (ptr->left != NULL || ptr->right != NULL) // �ڽ��� ������
		{
			printf("The node [%d] is not a leaf node\n", key); // �� ��尡 �ƴϹǷ� ���� �Ұ�
			return 0;
		}
		else // �ڽ��� ���� ���
		{
			if (prev->left == ptr) // ���� ����� ���� �ڽ��� ptr�̸�
				prev->left = NULL; // ���� ����� ���� �ڽ��� NULL��
			else
				prev->right = NULL; // ���� ����� ������ �ڽ��� NULL��
			free(ptr);				// ptr�� ����

			//*** �׳� free(ptr)���� �ص� ��������
			// prev�� ������ left�� right�� ����Ű�� �ǹǷ�
			// prev���� �¿� �½��� ����Ű�� �ʰ� �ϰ� ptr�� ����.
		}
	}
	return 0;
}

// �������� Ž���� �����ϰ� ������� ���
Node *searchRecursive(Node *ptr, int key)
{
	if (ptr == NULL)
		return NULL;
	if (key == ptr->key) // ã���� ���
		return ptr;		 // ��ȯ
	else if (key < ptr->key)
		return searchRecursive(ptr->left, key); // ã�� ������ ��������
	else
		return searchRecursive(ptr->right, key); // ã�� ������ ����������
}

Node *searchIterative(Node *head, int key)
{
	Node *ptr = head->left;
	while (ptr) // ���� �����ϴ� ���� �ݺ�
	{
		if (key < ptr->key)
			ptr = ptr->left;
		else if (key > ptr->key)
			ptr = ptr->right;
		else
			return ptr;
	}
	// �������� ���� ���
	return NULL;
}

int freeBST(Node *head) // Ʈ���� ���� �Ҵ� ����
{
	Node *ptr = head->left;
	if (ptr != NULL)
	{
		freeBST(ptr->left);	 // ���� ����Ʈ���� ����
		freeBST(ptr->right); // ������ ����Ʈ���� ����
		free(ptr);			 // ���� ��带 ����
	}
	free(head); // head�� ����
	return 0;
}
