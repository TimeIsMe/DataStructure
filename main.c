#include <stdio.h>
#include "SymmetricList.h"


int main(int argc, char* argv[]) {
	nodeTypeDef* head = NULL;
	int ret = 0;
	ret_state sta;
	//����������ͨ��
	ret = listAdd(&head, 1, 0);
	listDisp(head);
	//Ĭ�Ͻ�β��Ӳ���ͨ��
	ret = listAdd(&head, 2, -1);
	listDisp(head);
	//Խ����ӽڵ����ͨ��
	ret = listAdd(&head, 3, 10);
	listDisp(head);
	ret = listAdd(&head, 4, 10);
	listDisp(head);
	ret = listAdd(&head, 5, 10);
	listDisp(head);
	ret = listAdd(&head, 6, 10);
	listDisp(head);

	//����ɾ������
	//Ĭ����βɾ������ �ɹ�
	sta = listDel(&head, -1);
	listDisp(head);
	//������βɾ������ �ɹ�
	sta = listDel(&head, 4);
	listDisp(head);
	//�����м�ɾ������ �ɹ�
	sta = listDel(&head, 2);
	listDisp(head);
	//����ͷ��ɾ������ �ɹ�
	sta = listDel(&head, 0);
	listDisp(head);
	//����ɾ�����ڵ�������� �ɹ�
	sta = listDel(&head, 1);
	sta = listDel(&head, 0);
	listDisp(head);
	//����ɾ�����ڵ�������� �ɹ�
	ret = listAdd(&head, 1, 0);
	sta = listDel(&head, -1);
	listDisp(head);

	//�����޸Ĳ���
	//���ڵ��޸Ĳ��� �ɹ�
	ret = listAdd(&head, 1, 0);
	sta = listModification(&head, ret, 6);
	sta = listDisp(head);

	//β�ڵ��޸Ĳ��� �ɹ�
	ret = listAdd(&head, 2, 1);
	sta = listModification(&head, ret, 7);
	sta = listDisp(head);

	//�м�ڵ��޸Ĳ��� �ɹ�
	ret = listAdd(&head, 3, -1);
	ret = listAdd(&head, 4, -1);
	sta = listModification(&head, 2, 8);
	sta = listDisp(head);

	//��ѯ����
	//ͷ���ѯ���� �ɹ�
	ret = listInquire(&head, 0);

	//β�ڵ��ѯ���� �ɹ�
	ret = listInquire(&head, 3);

	//�����ڵ��ѯ���� �ɹ�
	sta = listDel(&head, -1);
	sta = listDel(&head, -1);
	sta = listDel(&head, -1);
	ret = listInquire(&head, 0);

	//Խ���ѯ���� �ɹ�
	ret = listInquire(&head, 10);

	//�սڵ��ѯ���� �ɹ�
	sta = listDel(&head, -1);
	ret = listInquire(&head, 0);



	return 0;

}