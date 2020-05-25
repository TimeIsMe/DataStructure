#ifndef __SYMMETRICLIST_
#define __SYMMETRICLIST_

//节点结构体
typedef struct nodeTypeDef {
	int index;
	int data;
	struct nodeTypeDef* point;
}nodeTypeDef;


//返回状态枚举类。
typedef enum ret_state {
	RET_OK = 0,
	RET_OUTOFDATA = 1,
	RET_NULL = 2		//链表为空
}ret_state;

//功能函数
int listAdd(nodeTypeDef** head, int data, int index);
ret_state listDel(nodeTypeDef** head, int index);
ret_state listModification(nodeTypeDef** head, int index, int new_data);
int listInquire(nodeTypeDef** head, int index);
ret_state listDisp(nodeTypeDef* head);


#endif

