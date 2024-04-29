/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[===========2023041004==========한윤수]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	//새로운 노드 생성
	listNode* new = (listNode*)malloc(sizeof(listNode));
	new->key = key;
	new->link = NULL;
	//만약 삽입할 노드가 첫번째 노드일 경우
	//(리스트가 비어있음 또는 첫번째 노드의 key보다 작은 경우)
	if (h->first == NULL || key < h->first->key) {
		//삽입할 노드의 링크를 기존 첫번째 노드로 설정
		new->link = h->first;
		//list의 첫번째 노드를 삽입할 노드로 설정
		h->first = new;
		//함수 종료
		return 0;
	}
	//임시 변수에 리스트의 첫 번째 노드를 저장
	listNode* temp = h->first;
	//이전 노드를 저장할 변수 (초기값은 NULL)
	listNode* prev = NULL;
	//리스트의 끝까지 또는 조건에 맞을 때까지 반복
	while (temp != NULL && key >= temp->key) {
		//이전 노드에 현재 노드를 저장
		prev = temp;
		//현재 노드를 다음 노드로 변경
		temp = temp->link;
	}
	//새로운 노드 위치에 기존 노드랑 연결
	new->link = temp;
	//이전 노드 위치에 새로운 노드 연결
	prev->link = new;
	//함수 종료
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	//새로운 노드 생성
	listNode* new = (listNode*)malloc(sizeof(listNode));
	new->key = key;
	new->link = NULL;
	//만약 리스트가 비어있는 경우
	if (h->first == NULL) {
		//리스트 첫번째 노드로 새로운 노드 삽입
		h->first = new;
		//함수 종료
		return 0;
	}
	//임시 변수에 리스트의 첫번째 노드를 저장
	listNode* temp = h->first;
	//리스트의 끝까지 반복
	while (temp->link != NULL) {
		//다음 노드로 이동
		temp = temp->link;
	}
	//마지막 노드의 링크에 새로운 노드 연결
	temp->link = new;
	//함수 종료
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	//임시 변수에 첫번째 노드를 저장
	listNode* temp = h->first;
	//첫번째 노드를 두번째 노드로 변경
	h->first = temp->link;
	//임시 변수에 저장된 (전) 첫번째 노드를 메모리 해제
	free(temp);
	//함수 종료
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	//임시 변수에 첫번째 노드를 저장
	listNode* temp = h->first;
	//이전 변수에 이전 노드를 저장 (초기값은 NULL)
	listNode* prev = NULL;
	//첫번째 노드가 삭제할 노드인 경우
	if(temp->key == key) {
		//첫번째 노드를 두번째 노드로 변경
		h->first = temp->link;
		//첫번째 노드를 메모리 해제
		free(temp);
		//함수 종료
		return 0;
	}
	else {
		//첫번째 노드가 삭제할 노드가 아닌 경우
		//첫번째 노드가 삭제할 노드가 나올 때까지 반복
		while(temp != NULL && temp->key != key) {
			//이전 노드에 현재 노드를 저장
			prev = temp;
			//현재 노드를 다음 노드로 변경
			temp = temp->link;
		}
		//삭제할 노드가 없는 경우
		if(temp == NULL) {
			//함수 비정상 종료
			return 1;
		}
		//삭제할 노드가 있는 경우
		//이전 노드의 링크를 삭제할 노드의 링크로 변경
		prev->link = temp->link;
		//삭제할 노드를 메모리 해제
		free(temp);
	}
	//함수 종료
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	//임시 변수에 첫번째 노드를 저장
	listNode* temp = h->first;
	//만약 첫번째 노드가 없는 경우
	if (temp == NULL) {
		//함수 비정상 종료
		return 1;
	}
	//다음 노드가 존재하지 않을 때까지 반복
	while (temp->link != NULL) {
		temp = temp->link;
	}
	//임시 변수에 저장된 마지막 노드를 메모리 해제
	free(temp);
	//함수 종료
	return 0;
	//return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

