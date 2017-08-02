#include<stdio.h>
#include<stdlib.h>
struct Node
{
	int value;
	Node *Parent;
	Node *left;
	Node *right;
};

//node와 node의 자식을 출력한다.
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

//부모의 주소와 자식 객체를 전달받고 둘을 이어줌
int addNode(Node* parent,Node *child){
	if(parent->value==child->value)
		return 0;
	else if(parent->value>child->value){
		if(parent->left==NULL){//왼쪽
			parent->left=child;
			child->Parent=parent;
			return 1;
		}
		else
			return addNode(parent->left,child);
	}
	else{
		//오른쪽
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

//노드와 그 자식까지 전부 삭제
void delNode(Node *node){
	Node *left=node->left;
	Node *right=node->right;
	Node *parent=node->Parent;

	if(parent!=NULL){//만약 node가 root노드가 아니라면, node를 호적에서 파내기 위해서 자신이 parent의 좌노드인지 우노드인지 알아내고 자기 자신을 지워버린다.(포인터값을 null로
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

//노드 하나만 삭제
void removeNode(Node *node){
	Node *parent = node->Parent;
	if(node->left==NULL&&node->right==NULL){//노드가 자식이 없을 때
		if(parent!=NULL){
			if(parent->left==node) parent->left=NULL;//호적파내기
			else parent->right=NULL;
		}
		free(node);
		return;
	}
	else if(node->left!=NULL&&node->right!=NULL){//노드가 자식이 둘 다 있을 때
		Node *nearestLow = node->right;//노드에 가장 가까운 작은 오른쪽의 자식
		Node *nearestBig = node->left;//노드에 가장 가까운 큰 왼쪽의 자식

		while(nearestBig->left!=NULL)//왼쪽의 자식 중 가장 오른쪽
			nearestBig=nearestBig->left;
		while(nearestLow->right!=NULL)//오른쪽의 자식 중 가장 왼쪽
			nearestLow=nearestLow->right;

		if(nearestBig->value - node->value > node->value - nearestLow->value){//오른쪽이 더 큰 경우(왼쪽값이 더 가까움)
			node->value=nearestLow->value;//nearestLow와 node의 값을 바꿔줌(node는 삭제하니 상관 없음)
			if(nearestLow->left){//본래 있던 nearestLow의 자리가 왼쪽의 자식을 가지고 있었다면
				nearestLow->Parent->right=nearestLow->left;
				nearestLow->left->Parent=nearestLow->Parent;
			}
			else
				nearestLow->Parent->right=NULL;//nearestLow가 자식이 없었다면 그냥 자기자신을 호적에서 파는 것으로 마무리
			node->value=nearestLow->value;
			free(nearestLow);
		}
		else {//왼쪽이 더 큰 경우
			if(nearestBig->right){//본래 있던 nearestLow의 자리가 왼쪽의 자식을 가지고 있었다면
				nearestBig->Parent->left=nearestBig->right;
				nearestBig->right->Parent=nearestBig->Parent;
			}
			else
				nearestBig->Parent->right=NULL;//nearestLow가 자식이 없었다면 그냥 자기자신을 호적에서 파는 것으로 마무리
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


/*int CreateNode(Node* Parent,int value){//parent의 직계자식 중 value가 있나 확인,없다면 value값을 가지는 노드를 생성
	Node *node=(Node*)malloc(sizeof(Node));

	return 1;//노드생성 성공, 부모의 값 중 value자식을 추가할 수 있다면, 즉 value가 들어가야 할 자리에 노드가 이미 있거나 value가 부모의 값과 같다면 
	//노드를 생성했다면 생성한 노드를 main함수에 인식해줘야 한다, 그런데 우리가 반환값이 1,0으로 정해져 있으므로 포인터를 사용해서 전달한다. 그리고 이미 node가 포인터이므로 이중 포인터를 사용한다.
}*///이중 포인터를활용해서 더 간결하게 아래에

//족보가 없는 동떨어진 노드 하나를 생성);
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