#ifndef __SYMMETRICLIST_
#define __SYMMETRICLIST_

//�ڵ�ṹ��
typedef struct nodeTypeDef {
	int index;
	int data;
	struct nodeTypeDef* point;
}nodeTypeDef;


//����״̬ö���ࡣ
typedef enum ret_state {
	RET_OK = 0,
	RET_OUTOFDATA = 1,
	RET_NULL = 2		//����Ϊ��
}ret_state;

//���ܺ���
int listAdd(nodeTypeDef** head, int data, int index);
ret_state listDel(nodeTypeDef** head, int index);
ret_state listModification(nodeTypeDef** head, int index, int new_data);
int listInquire(nodeTypeDef** head, int index);
ret_state listDisp(nodeTypeDef* head);


#endif

