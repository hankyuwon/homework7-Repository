#include<stdio.h>
#include<stdlib.h>

typedef struct Node { // 이중 연결 리스트
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;

int initialize(headNode** h);
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("---------------[hankyuwon]--------[2019037002]-------------\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
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
			initialize(&headnode);
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


int initialize(headNode** h) { // 헤드 노드 생성
	if(*h != NULL)
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){ // 리스트 메모리 해제

	listNode* p = h->first; // listNode의 모든 메모리를 해제함

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h); // 헤더 노드 메모리 해제
	return 0;
}


void printList(headNode* h) { // listNode 출력
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
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}

int insertLast(headNode* h, int key) { // listNode의 마지막에 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL) // listNode가 비어있을 시
	{
		h->first = node; // headerNode 다음에 삽입
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL) { // listNode가 비어있지 않을 시 listNode의 마지막 부분 찾아서 삽입
		n = n->rlink;
	}
	n->rlink = node; // rlink에 node 삽입
	node->llink = n; // llink에 node 이전인 n 삽입
	return 0;
}

int deleteLast(headNode* h) { // listNode의 마지막 노드 삭제

	if (h->first == NULL) // listNode가 비어있을 시
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->rlink == NULL) { // listNode에 노드가 하나 있을 경우
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->rlink != NULL) { // listNode에 노드가 하나 이상 있는 경우
		trail = n;
		n = n->rlink;
	}

	trail->rlink = NULL;
	free(n);

	return 0;
}

int insertFirst(headNode* h, int key) { // listNode 첫부분에 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode)); // listNode node 구조체 포인터 동적할당
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first; // node를 h->first와 h 사이에 끼워줌
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

int deleteFirst(headNode* h) { // listNode 첫 부분 노드 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // listNode의 첫 부분 n으로 정의, 삭제
	h->first = n->rlink;

	free(n);

	return 0;
}

int invertList(headNode* h) { // listNode 역순


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){ // trail, middle, n 을 이용하여 listNode 역순으로 만들기
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}

int insertNode(headNode* h, int key) { // 입력 값 listNode의 특정 부분에 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while(n != NULL) { // 입력값을 비교하며 입력값보다 큰값 앞에 node 삽입
		if(n->key >= key) {
			if(n == h->first) { // listNode의 첫 노드일때
				insertFirst(h, key);
			} else { // listNode의 첫 노드가 아닐때
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);
	return 0;
}

int deleteNode(headNode* h, int key) { // 입력 값 listNode에서 찾아서 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) { // node->key에 입력값과 동일한 값이 있는지 찾기
		if(n->key == key) {
			if(n == h->first) { // listNode의 첫 노드일 때
				deleteFirst(h);
			} else if (n->rlink == NULL){ // listNode의 마지막 노드일 때
				deleteLast(h);
			} else {
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key); // 입력 key 값을 listNode에서 찾지 못했을 때
	return 1;
}