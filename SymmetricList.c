#include "SymmetricList.h"
#include <stdio.h>
#include <malloc.h>

/*
* ��������nodeXor
* ���ߣ�������
* �������ܣ��ڵ��ַ����������������ת��
* ����������@p ��Ԫ����ĵ�һ��������@q ��Ԫ����ĵڶ�������
* ��������ֵ����Ԫ�������Ľ��
*/
static nodeTypeDef* nodeXor(nodeTypeDef* p, nodeTypeDef* q)
{
	return (nodeTypeDef*)((unsigned long)p ^ (unsigned long)q);
}

/*
* ��������listAdd
* ���ߣ�������
* �������ܣ��½���������ִ���������Ԫ�ء�
* ����������@head ����ͷ�ڵ㣬
*			@data ��Ҫ��ӵĽڵ��ֵ
*			@index ��ѡ������-1��ʾĬ���������β��ӽڵ㣬index>=0��ʾ�ڵ�index����ӽڵ�
* ��������ֵ�� �����½��ڵ������ֵ
*/
int listAdd(nodeTypeDef** head, int data, int index)
{
	int i = 0;
	nodeTypeDef* pre, * cur, * next, * temp;
	//�ж������Ƿ�Ϊ��
	if (*head == NULL) {
		*head = (nodeTypeDef*)malloc(sizeof(nodeTypeDef));
		(*head)->data = data;
		(*head)->index = 0;
		(*head)->point = NULL;
		return (*head)->index;
	}
	pre = NULL; cur = *head; next = nodeXor(cur->point, pre);
	//�Ƿ�ΪĬ����β���
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
	//�̶�λ����ӽڵ�
	else {
		while (next != NULL && i < index) {
			i++;
			pre = cur; cur = next; next = nodeXor(cur->point, pre);
		}
		//�ж���Խ�绹�ǵ���������λ��
		//Խ��
		if (next == NULL) {
			next = (nodeTypeDef*)malloc(sizeof(nodeTypeDef));
			next->data = data;
			next->index = i + 1;
			next->point = nodeXor(cur, NULL);
			cur->point = nodeXor(pre, next);
			return next->index;
		}
		//û��Խ��
		else {
			temp = (nodeTypeDef*)malloc(sizeof(nodeTypeDef));
			temp->data = data;
			temp->index = i + 1;
			temp->point = nodeXor(cur, next);
			cur->point = nodeXor(pre, temp);
			//����ʹcurָ��next, pre cur temp next xx -->> xx xx pre cur next
			pre = temp; cur = next; next = nodeXor(nodeXor(pre->point, cur), cur->point);
			cur->point = nodeXor(pre, next);
			return pre->index;
		}
	}	

}



/*
* ��������listDel
* ���ߣ�������
* �������ܣ�ɾ��index���Ľڵ�
* ����������@head ����ͷ�ڵ�
*			@index Ҫɾ���Ľڵ������ֵ��-1��ʾ�ӽ�βɾ����index>=0��ʾɾ���̶�����λ�õĽڵ�
* ��������ֵ��res_state ��ʾ�Ƿ�ɾ���ɹ�
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
		//preΪ��
		if (NULL == pre) {
			free(cur);
			*head = NULL;
			ret = RET_OK;
			return ret;
		}
		//ǰ��һ���ڵ�,��ɾ�����һ���ڵ�
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
			//ǡ�������һ��
			if (i == index) {
				//preΪ��
				if (NULL == pre) {
					free(cur);
					*head = NULL;
					ret = RET_OK;
					return ret;
				}
				//pre��Ϊ��
				else {
					//ǰ��һ���ڵ�
					next = cur; cur = pre; pre = nodeXor(cur->point, next);
					free(next);
					cur->point = nodeXor(pre, NULL);
					ret = RET_OK;
					return ret;
				}
			}
			//Խ��
			else {
				ret = RET_OUTOFDATA;
				return ret;
			}
		}
		//û��Խ������ɾ�����˴�next�ض���Ϊ��
		else {
			//���ǰ���ڵ�Ϊ��
			if (NULL == pre) {
				//����ƶ�һ���ڵ㣬Ȼ��ɾ��pre
				pre = cur; cur = next; next = nodeXor(cur->point, pre);
				free(pre);
				cur->point = nodeXor(NULL, next);
				*head = cur;
				ret = RET_OK;
				return ret;
			}
			//�˴�pre��next�Բ�Ϊ��
			//tempָ��preǰ���ڵ�
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
* ��������listModification
* ���ߣ�������
* �������ܣ��޸�ĳ���ڵ��ֵ
* ����������@head ����ͷ�ڵ�
*			@index ��Ҫ�޸Ľڵ��������
*			@new_data ��Ҫ���µ�����
* ��������ֵ���Ƿ��޸ĳɹ�
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
* ��������listInquire
* ���ߣ�������
* �������ܣ���ѯĳ���ڵ������ֵ,������Χ����Ϊ����Ϊ0
* ����������@head ����ͷ�ڵ�
*			@index ��Ҫ��ѯ��������
* ��������ֵ��Ҫ��ѯ�ڵ������ֵ
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
* ��������listDisp
* ���ߣ�������
* �������ܣ���ӡ�������нڵ�
* ����������@head ����ͷ�ڵ�
* ��������ֵ�����غ���ִ��״̬
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
