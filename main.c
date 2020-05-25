#include <stdio.h>
#include "SymmetricList.h"


int main(int argc, char* argv[]) {
	nodeTypeDef* head = NULL;
	int ret = 0;
	ret_state sta;
	//链表创建测试通过
	ret = listAdd(&head, 1, 0);
	listDisp(head);
	//默认结尾添加测试通过
	ret = listAdd(&head, 2, -1);
	listDisp(head);
	//越界添加节点测试通过
	ret = listAdd(&head, 3, 10);
	listDisp(head);
	ret = listAdd(&head, 4, 10);
	listDisp(head);
	ret = listAdd(&head, 5, 10);
	listDisp(head);
	ret = listAdd(&head, 6, 10);
	listDisp(head);

	//链表删除测试
	//默认链尾删除测试 成功
	sta = listDel(&head, -1);
	listDisp(head);
	//主动链尾删除测试 成功
	sta = listDel(&head, 4);
	listDisp(head);
	//主动中间删除测试 成功
	sta = listDel(&head, 2);
	listDisp(head);
	//主动头部删除测试 成功
	sta = listDel(&head, 0);
	listDisp(head);
	//主动删除单节点链表测试 成功
	sta = listDel(&head, 1);
	sta = listDel(&head, 0);
	listDisp(head);
	//被动删除单节点链表测试 成功
	ret = listAdd(&head, 1, 0);
	sta = listDel(&head, -1);
	listDisp(head);

	//链表修改测试
	//单节点修改测试 成功
	ret = listAdd(&head, 1, 0);
	sta = listModification(&head, ret, 6);
	sta = listDisp(head);

	//尾节点修改测试 成功
	ret = listAdd(&head, 2, 1);
	sta = listModification(&head, ret, 7);
	sta = listDisp(head);

	//中间节点修改测试 成功
	ret = listAdd(&head, 3, -1);
	ret = listAdd(&head, 4, -1);
	sta = listModification(&head, 2, 8);
	sta = listDisp(head);

	//查询测试
	//头点查询测试 成功
	ret = listInquire(&head, 0);

	//尾节点查询测试 成功
	ret = listInquire(&head, 3);

	//单个节点查询测试 成功
	sta = listDel(&head, -1);
	sta = listDel(&head, -1);
	sta = listDel(&head, -1);
	ret = listInquire(&head, 0);

	//越界查询测试 成功
	ret = listInquire(&head, 10);

	//空节点查询测试 成功
	sta = listDel(&head, -1);
	ret = listInquire(&head, 0);



	return 0;

}