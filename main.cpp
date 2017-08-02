#include<stdio.h>
#include<string.h>
/*void main(){
	FILE *fp = fopen("input.txt","wt");//fopen ("파일이름","방식")에서 r은 읽기모드이고 t는 텍스트를 읽는다는 것이다.
	int number =0;
	int number2=0;
	if(fp==NULL){
		printf("파일을 열 수 없습니다.");
		return;
	}

	/*fscanf(fp,"%d%d",&number,&number2);//fp의 주소에 있는 파일을 읽어서 number에 준다
	printf("%d\n%d\n",number,number2);
	scanf("%d",&number);*/
	/*int a=10;
	fprintf(fp,"%d + %d = %d",10,20,30);*/
	/*char text[128]={0};
	while(strcmp(text,"exit")){//strcmp(a,b) a와 b가 똑같으면 0 다르면 1을 반환한다.
		scanf("%s",text);
		fprintf(fp,"%s\n",text);
	}
	fclose(fp);//파일을 읽기모드로 쓰고 있는 동안은 파일을 수정할 수 없다. 그러므로 파일을 쓰지 않을 때는 다시 닫아놔야 한다.
}*/

//target에서 text를 찾으면 1
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
	return 0;//아무것도 아니면 0 반환
}

void main(){
	FILE *fp = fopen("lorem.txt","rt");
	if(fp==NULL){
		printf("파일을 열 수 없습니다.");
		return;
	}

	char target[4096];
	char text[4096];
	printf("찾으려는 문자열 : ");
	scanf("%s",text);
	//fscanf(fp,"
	//fgets(text,4096,fp);//개행된 부분 전까지 가져온다. fscanf는 띄어쓰기 전까지 가져온다.
	while(!feof(fp)){//feof는 파일의 끝을 알린다.
		fgets(target,4096,fp);
		printf("%s\n",target); 
		if(search(target,text,0)){
			printf(" $여기서 찾았습니다.$");
			break;
		}
	}
	printf("파일을 다 읽었습니다.");
	fclose(fp);
}