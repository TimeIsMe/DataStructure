#include "SymmetricList.h"
#include <stdio.h>
#include <malloc.h>

/*
* 函数名：nodeXor
* 作者：王明亮
* 函数功能：节点地址异或操作，数据类型转化
* 函数参数：@p 二元运算的第一个参数，@q 二元运算的第二个参数
* 函数返回值：二元运算异或的结果
*/
static nodeTypeDef* nodeXor(nodeTypeDef* p, nodeTypeDef* q)
{
	return (nodeTypeDef*)((unsigned long)p ^ (unsigned long)q);
}

/*
* 函数名：listAdd
* 作者：王明亮
* 函数功能：新建链表或在现存链表新增元素。
* 函数参数：@head 链表头节点，
*			@data 需要添加的节点的值
*			@index 可选参数，-1表示默认在链表结尾添加节点，index>=0表示在第index处添加节点
* 函数返回值： 返回新建节点的索引值
*/
int listAdd(nodeTypeDef** head, int data, int index)
{
	int i = 0;
	nodeTypeDef* pre, * cur, * next, * temp;
	//判断链表是否为空
	if (*head == NULL) {
		*head = (nodeTypeDef*)malloc(sizeof(nodeTypeDef));
		(*head)->data = data;
		(*head)->index = 0;
		(*head)->point = NULL;
		return (*head)->index;
	}
	pre = NULL; cur = *head; next = nodeXor(cur->point, pre);
	//是否为默认链尾添加
	if (0 > index) {
		while (next != NULL) {
			i++;
			pre = cur; cur = next; next = nodeXor(cur->point, pre);
		}
		next = (nodeTypeDef*)malloc(sizeof(nodeTypeDef));
		cur->point = nodeXor(pre, next);
		next->data = data;
		next->index = i+1;
		next->point = nodeXor(cur, NULL);
		return next->index;
	}
	//固定位置添加节点
	else {
		while (next != NULL && i < index) {
			i++;
			pre = cur; cur = next; next = nodeXor(cur->point, pre);
		}
		//判断是越界还是到达了索引位置
		//越界
		if (next == NULL) {
			next = (nodeTypeDef*)malloc(sizeof(nodeTypeDef));
			next->data = data;
			next->index = i + 1;
			next->point = nodeXor(cur, NULL);
			cur->point = nodeXor(pre, next);
			return next->index;
		}
		//没有越界
		else {
			temp = (nodeTypeDef*)malloc(sizeof(nodeTypeDef));
			temp->data = data;
			temp->index = i + 1;
			temp->point = nodeXor(cur, next);
			cur->point = nodeXor(pre, temp);
			//右移使cur指向next, pre cur temp next xx -->> xx xx pre cur next
			pre = temp; cur = next; next = nodeXor(nodeXor(pre->point, cur), cur->point);
			cur->point = nodeXor(pre, next);
			return pre->index;
		}
	}	

}



/*
* 函数名：listDel
* 作者：王明亮
* 函数功能：删除index处的节点
* 函数参数：@head 链表头节点
*			@index 要删除的节点的索引值，-1表示从结尾删除，index>=0表示删除固定索引位置的节点
* 函数返回值：res_state 表示是否删除成功
*/
ret_state listDel(nodeTypeDef** head, int index)
{
	nodeTypeDef* pre, * cur, * next, * temp;
	int i = 0;
	ret_state ret;
	if (NULL == *head) {
		ret = RET_NULL;
		return ret;
	}
	pre = NULL; cur = *head; next = nodeXor(cur->point, pre);
	if (-1 == index) {	
		while (NULL != next) {
			pre = cur; cur = next; next = nodeXor(cur->point, pre);
		}
		//pre为空
		if (NULL == pre) {
			free(cur);
			*head = NULL;
			ret = RET_OK;
			return ret;
		}
		//前移一个节点,并删除最后一个节点
		next = cur; cur = pre; pre = nodeXor(cur->point, next);
		cur->point = nodeXor(pre, NULL);
		free(next);
		ret = RET_OK;
		return ret;
	}
	else {
		while (i < index && NULL != next) {
			pre = cur; cur = next; next = nodeXor(cur->point, pre);
			i++;
		}
		if (NULL == next) {
			//恰好是最后一个
			if (i == index) {
				//pre为空
				if (NULL == pre) {
					free(cur);
					*head = NULL;
					ret = RET_OK;
					return ret;
				}
				//pre不为空
				else {
					//前移一个节点
					next = cur; cur = pre; pre = nodeXor(cur->point, next);
					free(next);
					cur->point = nodeXor(pre, NULL);
					ret = RET_OK;
					return ret;
				}
			}
			//越界
			else {
				ret = RET_OUTOFDATA;
				return ret;
			}
		}
		//没有越界正常删除，此处next必定不为空
		else {
			//如果前驱节点为空
			if (NULL == pre) {
				//向后移动一个节点，然后删除pre
				pre = cur; cur = next; next = nodeXor(cur->point, pre);
				free(pre);
				cur->point = nodeXor(NULL, next);
				*head = cur;
				ret = RET_OK;
				return ret;
			}
			//此处pre，next皆不为空
			//temp指向pre前驱节点
			temp = nodeXor(pre->point, cur);
			pre->point = nodeXor(temp, next);
			next->point = nodeXor(pre, nodeXor(next->point, cur));
			free(cur);
			ret = RET_OK;
			return ret;
		}
	}

}

/*
* 函数名：listModification
* 作者：王明亮
* 函数功能：修改某个节点的值
* 函数参数：@head 链表头节点
*			@index 需要修改节点的索引号
*			@new_data 需要更新的数据
* 函数返回值：是否修改成功
*/
ret_state listModification(nodeTypeDef** head, int index, int new_data)
{
	nodeTypeDef* pre, * cur, * next;
	int i = 0;
	if (NULL == *head) {
		return RET_NULL;
	}
	pre = NULL; cur = *head; next = nodeXor(cur->point, pre);
	while (i < index && NULL != next) {
		i++;
		pre = cur; cur = next; next = nodeXor(cur->point, pre);
	}
	if (i == index) {
		cur->data = new_data;
		return RET_OK;
	}
	return RET_OUTOFDATA;
}


/*
* 函数名：listInquire
* 作者：王明亮
* 函数功能：查询某个节点的数据值,超出范围则认为数据为0
* 函数参数：@head 链表头节点
*			@index 需要查询的索引号
* 函数返回值：要查询节点的数据值
*/
int listInquire(nodeTypeDef** head, int index)
{
	nodeTypeDef* pre, * cur, * next;
	int i = 0;
	if (NULL == *head) {
		return 0;
	}
	pre = NULL; cur = *head; next = nodeXor(cur->point, pre);
	while (i < index && next != NULL) {
		i++;
		pre = cur; cur = next; next = nodeXor(cur->point, pre);
	}
	if (i < index) {
		return 0;
	}
	return cur->data;
}

/*
* 函数名：listDisp
* 作者：王明亮
* 函数功能：打印链表所有节点
* 函数参数：@head 链表头节点
* 函数返回值：返回函数执行状态
*/
ret_state listDisp(nodeTypeDef* head)
{
	nodeTypeDef* pre, * cur, * next;
	printf("*************List begin************\r\n");
	if (NULL == head) {
		printf("The list is empty.\r\n");
		printf("*************List End************\r\n");
		return RET_NULL;
	}
	pre = NULL; cur = head; next = nodeXor(cur->point, pre);
	printf("node index:%d\tnode data:%d\r\n", cur->index, cur->data);
	while (next != NULL) {
		pre = cur; cur = next; next = nodeXor(cur->point, pre);
		printf("node index:%d\tnode data:%d\r\n", cur->index, cur->data);
	}
	printf("*************List End************\r\n");
	return RET_OK;
}
