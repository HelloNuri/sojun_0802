#include<stdio.h>
#include<stdlib.h>
struct Node
{
	int value;
	Node *Parent;
	Node *left;
	Node *right;
};

//node�� node�� �ڽ��� ����Ѵ�.
void ShowTree(Node *node){
	printf("Node : %d\n",node->value);
	if(node->left){
		//printf("Has Left\n");
		//printf("Node left : %d\n",node->left);
		ShowTree(node->left);
	}
	if(node->right){
		//printf("Has Right\n");
		//printf("Node right : %d\n",node->right);
		ShowTree(node->right);
	}
	}

//�θ��� �ּҿ� �ڽ� ��ü�� ���޹ް� ���� �̾���
int addNode(Node* parent,Node *child){
	if(parent->value==child->value)
		return 0;
	else if(parent->value>child->value){
		if(parent->left==NULL){//����
			parent->left=child;
			child->Parent=parent;
			return 1;
		}
		else
			return addNode(parent->left,child);
	}
	else{
		//������
		if(parent->right==NULL){
			parent->right=child;
			child->Parent=parent;
			return 1;
		}
		else
			return addNode(parent->right,child);
	}

	return 0;
}

//���� �� �ڽı��� ���� ����
void delNode(Node *node){
	Node *left=node->left;
	Node *right=node->right;
	Node *parent=node->Parent;

	if(parent!=NULL){//���� node�� root��尡 �ƴ϶��, node�� ȣ������ �ĳ��� ���ؼ� �ڽ��� parent�� �³������ �������� �˾Ƴ��� �ڱ� �ڽ��� ����������.(�����Ͱ��� null��
		if(parent->left=node)
			parent->left=NULL;
		else if(parent->right=node)
			parent->left=NULL;
	}

	if(left!=NULL)
		delNode(left);
	if(right!=NULL)
		delNode(right);
	free(node);
}

//GUI
void PrintPretty(Node *parent,int depth){
	printf("%4d",parent->value);
	if(parent->right)
		PrintPretty(parent->right,depth+1);
	if(parent->left){
		printf("\n");
		for(int i=0;i<depth+1;++i)
			printf("    ");
		PrintPretty(parent->left,depth+1);
	}
}

//advanced GUI, vertical
void PrintfPretty(Node *parent){
	int depth=0;
	int *depth=&depth;
	
	if(parent->right)
		PrintfPretty(parent->right);
		
}

//��� �ϳ��� ����
void removeNode(Node *node){
	Node *parent = node->Parent;
	if(node->left==NULL&&node->right==NULL){//��尡 �ڽ��� ���� ��
		if(parent!=NULL){
			if(parent->left==node) parent->left=NULL;//ȣ���ĳ���
			else parent->right=NULL;
		}
		free(node);
		return;
	}
	else if(node->left!=NULL&&node->right!=NULL){//��尡 �ڽ��� �� �� ���� ��
		Node *nearestLow = node->right;//��忡 ���� ����� ���� �������� �ڽ�
		Node *nearestBig = node->left;//��忡 ���� ����� ū ������ �ڽ�

		while(nearestBig->left!=NULL)//������ �ڽ� �� ���� ������
			nearestBig=nearestBig->left;
		while(nearestLow->right!=NULL)//�������� �ڽ� �� ���� ����
			nearestLow=nearestLow->right;

		if(nearestBig->value - node->value > node->value - nearestLow->value){//�������� �� ū ���(���ʰ��� �� �����)
			node->value=nearestLow->value;//nearestLow�� node�� ���� �ٲ���(node�� �����ϴ� ��� ����)
			if(nearestLow->left){//���� �ִ� nearestLow�� �ڸ��� ������ �ڽ��� ������ �־��ٸ�
				nearestLow->Parent->right=nearestLow->left;
				nearestLow->left->Parent=nearestLow->Parent;
			}
			else
				nearestLow->Parent->right=NULL;//nearestLow�� �ڽ��� �����ٸ� �׳� �ڱ��ڽ��� ȣ������ �Ĵ� ������ ������
			node->value=nearestLow->value;
			free(nearestLow);
		}
		else {//������ �� ū ���
			if(nearestBig->right){//���� �ִ� nearestLow�� �ڸ��� ������ �ڽ��� ������ �־��ٸ�
				nearestBig->Parent->left=nearestBig->right;
				nearestBig->right->Parent=nearestBig->Parent;
			}
			else
				nearestBig->Parent->right=NULL;//nearestLow�� �ڽ��� �����ٸ� �׳� �ڱ��ڽ��� ȣ������ �Ĵ� ������ ������
			node->value=nearestBig->value;
			free(nearestBig);
		}
		return;
	}
	if(node->left){
		Node *left=node->left;
		if(parent!=NULL){
			if(node == parent->left)
				parent->left=left;
			else
				parent->right=left;
		}
		left->Parent=node->Parent;
		free(node);
	}
	else{
		Node *right = node->right;
		if(node == parent->left)
			parent->left=right;
		else
			parent->right=right;
		right->Parent=node->Parent;
		free(node);
	}
}


/*int CreateNode(Node* Parent,int value){//parent�� �����ڽ� �� value�� �ֳ� Ȯ��,���ٸ� value���� ������ ��带 ����
	Node *node=(Node*)malloc(sizeof(Node));

	return 1;//������ ����, �θ��� �� �� value�ڽ��� �߰��� �� �ִٸ�, �� value�� ���� �� �ڸ��� ��尡 �̹� �ְų� value�� �θ��� ���� ���ٸ� 
	//��带 �����ߴٸ� ������ ��带 main�Լ��� �ν������ �Ѵ�, �׷��� �츮�� ��ȯ���� 1,0���� ������ �����Ƿ� �����͸� ����ؼ� �����Ѵ�. �׸��� �̹� node�� �������̹Ƿ� ���� �����͸� ����Ѵ�.
}*///���� �����͸�Ȱ���ؼ� �� �����ϰ� �Ʒ���

//������ ���� �������� ��� �ϳ��� ����);
Node* CreateNode(int value){
	Node *node=(Node*)malloc(sizeof(Node));
	node->value = value;
	node->Parent=node->left=node->right=NULL;
	return node;
}

Node *root;

int main(){
	root=CreateNode(30);
	addNode(root,CreateNode(20));
	addNode(root,CreateNode(10));
	addNode(root,CreateNode(40));
	addNode(root,CreateNode(25));
	addNode(root,CreateNode(35));
	addNode(root,CreateNode(50));
	//ShowTree(root);
	PrintPretty(root,0);
	delNode(root);
}