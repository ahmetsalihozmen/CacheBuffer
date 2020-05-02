#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct buffer{
	char val[40];
	int times;
	struct buffer *next;
	struct buffer *before;
}buff;

void print(buff * head){
	//Yazd�rma fonksiyonu
	while(head->next!=NULL){
		printf("%s,%d <-> ",head->val,head->times);
		head = head->next;
	}
	printf("%s,%d\n",head->val,head->times);
}

buff * push(buff * head,int l,int t,char *vall){
	//Link ekleme fonksiyonu
	int cnt=1;
	buff * curr=head;
	buff * head1;
	while(curr->next!=NULL&& strcmp(vall,curr->val)&&cnt!=l){
		curr=curr->next;
		cnt++;
	}
	if(cnt==l || strcmp(vall,curr->val)){
		//Ayn� eleman yoksa
		head1=(buff*)malloc(sizeof(buff));
		if(cnt==l){
			while(curr->next!=NULL){
				curr=curr->next;
			}
			curr->before->next=NULL; 
			free(curr);
		}
		head->before=head1;
		head1->next= head;
		head1->before=NULL;
		strcpy(head1->val,vall);;
		head1->times=1;
		return head1;
	}	
	else{
		//Daha �nceden buffer i�inde var
		curr->times++;
		if(curr != head&&curr->times>t&& curr->before!=NULL){
			curr->before->next=curr->next;
			curr->next=head;
			curr->before=NULL;
			curr->next->before=curr;
			return curr;	
		}
		return head;
	}
}

void clear(buff * head,char *val){
	//Yeni bir link eklemeden �nce cache buffer� temizlemek isteyip istemedi�ini soruyor.
	buff *curr=head;
	while(head->next!=NULL){
		head=head->next;
	}
	while(head->before!=NULL){
		head=head->before;
		free(head->next);
		head->next=NULL;
	}
	strcpy(head->val,val);
	head->times=1;
}

void clearall(buff * head){
	//En sonda b�t�n cache buffer� temizliyor.
	while(head->next==NULL){
		head=head->next;
		free(head->before);
	}
	free(head);
}

int main(){
	setlocale(LC_ALL,"Turkish");
	buff *node;
	FILE *a;
	int i,j,T,L,choice,ch1,exit=0;
	char ch[40];
	node=(buff*)malloc(sizeof(buff));
	node->next=NULL; node->before=NULL;
	printf("Konsoldan girmek istiyorsan�z 1'i input.exe adl� dosyadan almak i�in 0'� tu�lay�n'\n");

	do
	{
		scanf("%d",&ch1);
		if(ch1!=0&&ch1!=1){
			printf("L�tfen belirtilen say�lardan birini giriniz.");
		}	
	} while (ch1!=0&&ch1!=1);
	
	if(ch1==0){
		a=fopen("input.txt","r");
		
		fscanf(a,"T=%d,L=%d %s",&T,&L,&ch);
	}
	else{
		printf("L�tfen �nce T yi sonra da L yi giriniz\n");
		scanf("%d %d",&T,&L);
		printf("Cache Buffer'a girecek eleman� giriniz\n");
		scanf("%s",ch);
	}
	strcpy(node->val,ch); node->times=1;
    print(node);
	while(exit==0){
		if(ch1==0){	
			fscanf(a,"%s",ch);
			if(feof(a)){
				exit=1;
			}
		}
		else{
			printf("Cache Buffer'a girecek eleman� giriniz\n");
			scanf("%s",&ch);
		}
		printf("Cache Buffer'� silmek ister misiniz?(Evet i�in 1 Hay�r i�in 0 � tu�lay�n�z)\n");
		do{
			scanf("%d",&choice);
			if(choice==0){
				node=push(node,L,T,ch);
				print(node);
			}
			else if(choice==1){
				clear(node,ch);
				print(node);
			}
			else{
				printf("Lutfen belirtilen say�lardan birini giriniz.\n");
			}
	}while(choice!=1&&choice!=0); 
	
	}
	
	clearall(node);
	return 0;
}
