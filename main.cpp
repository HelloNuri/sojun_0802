#include<stdio.h>
#include<string.h>
/*void main(){
	FILE *fp = fopen("input.txt","wt");//fopen ("�����̸�","���")���� r�� �б����̰� t�� �ؽ�Ʈ�� �д´ٴ� ���̴�.
	int number =0;
	int number2=0;
	if(fp==NULL){
		printf("������ �� �� �����ϴ�.");
		return;
	}

	/*fscanf(fp,"%d%d",&number,&number2);//fp�� �ּҿ� �ִ� ������ �о number�� �ش�
	printf("%d\n%d\n",number,number2);
	scanf("%d",&number);*/
	/*int a=10;
	fprintf(fp,"%d + %d = %d",10,20,30);*/
	/*char text[128]={0};
	while(strcmp(text,"exit")){//strcmp(a,b) a�� b�� �Ȱ����� 0 �ٸ��� 1�� ��ȯ�Ѵ�.
		scanf("%s",text);
		fprintf(fp,"%s\n",text);
	}
	fclose(fp);//������ �б���� ���� �ִ� ������ ������ ������ �� ����. �׷��Ƿ� ������ ���� ���� ���� �ٽ� �ݾƳ��� �Ѵ�.
}*/

//target���� text�� ã���� 1
int search(const char* target,const char* text,int a){
	int targetLength=strlen(target);
	int textLength = strlen(text);
	int j=0;
	for(int i=0;i<targetLength;i++){
		if(target[i]==text[j]){
			j++;
			if(j==textLength)
				return 1;
		}
		else
			j=0;
	}
	return 0;//�ƹ��͵� �ƴϸ� 0 ��ȯ
}

void main(){
	FILE *fp = fopen("lorem.txt","rt");
	if(fp==NULL){
		printf("������ �� �� �����ϴ�.");
		return;
	}

	char target[4096];
	char text[4096];
	printf("ã������ ���ڿ� : ");
	scanf("%s",text);
	//fscanf(fp,"
	//fgets(text,4096,fp);//����� �κ� ������ �����´�. fscanf�� ���� ������ �����´�.
	while(!feof(fp)){//feof�� ������ ���� �˸���.
		fgets(target,4096,fp);
		printf("%s\n",target); 
		if(search(target,text,0)){
			printf(" $���⼭ ã�ҽ��ϴ�.$");
			break;
		}
	}
	printf("������ �� �о����ϴ�.");
	fclose(fp);
}