#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define VALTYPE int

//二维数组行M和列N
#define M   4
#define N   4

struct node{
    int row;
    int col;
    VALTYPE val;
    struct node *down;
    struct node *right;
};

int max_side_val;

int crossListInit(struct node **p);
int crossListStore(struct node *p, VALTYPE (*q)[N]);
int crossListRestore(struct node *p, VALTYPE (*q)[N]);
int crossListDisplay(struct node *p);
int crossListChangeVal(struct node *p, int m, int n, VALTYPE val);
VALTYPE crossListGetVal(struct node *p, int m, int n);

int crossListInit(struct node **p){
    void *tmp;
    max_side_val = (M>N)?M:N;
    tmp = malloc(sizeof(struct node) * (max_side_val+1));
    memset(tmp, 0, sizeof(struct node) * (max_side_val+1));
    *p = (struct node *)tmp;
    return 0;
}

struct node* getBeforeDownPoint(struct node *pin){
    struct node *tmp = pin;
    while(NULL != tmp->down){
        tmp = tmp->down;
    }
    return tmp;
}

int crossListStore(struct node *p, VALTYPE (*q)[N]){
    int i,j;
    void *tmp;
    struct node **prow, **pcol;           //将要指向当前节点的node的元素的重命名。
    struct node *current_node;
    prow = &(p[1].right);               //列轮询使用
    for(i = 0; i < M; i++){             //行遍历
        for(j = 0; j < N; j++){         //列遍历
            pcol = &(getBeforeDownPoint(&p[j+1])->down);
            if(0 == q[i][j]){
                continue;
            }
            tmp = malloc(sizeof(struct node));
            memset(tmp, 0, sizeof(struct node));
            current_node = (struct node *)tmp;
            current_node->row = i+1;
            current_node->col = j+1;
            current_node->val = q[i][j];
            *prow = current_node;
            *pcol = current_node;
            prow = &(current_node->right);
            if((N-1) == j){             //该行的最右侧
                *prow = &(p[i+1]);
                if((M-1) != i){         //并且不为最后一行,指向下一行
                    prow = &(p[i+2].right);
                }
            }
            if((M-1) == i){
                (*pcol)->down = &p[j+1];

            }

        }
    }
    return 0;
}

//功能：寻找行号idx_row列号:idx_col的节点，如果存在就返回节点地址，不存在就返回NULL
struct node* getPointByIndex(struct node *pin, int idx_row, int idx_col)
{
    struct node *ret = pin[idx_col+1].down;
    struct node *tmp = pin[idx_row+1].right;
    while(ret != &pin[idx_col+1]){
        tmp = pin[idx_row+1].right;
        while(tmp != &pin[idx_row+1]){
            if(tmp == ret){
                return tmp;
            }
            tmp = tmp->right;
        }
        ret = ret->down;
    }

    return NULL;
}
int crossListRestore(struct node *p, VALTYPE (*q)[N]){
    int i, j;
    struct node *prow, *pcol;           //将要指向当前节点的node的元素的重命名。
    for(i = 0; i < M; i++){                //行遍历
        prow = p[i+1].right;
        for(j = 0; j < N; j++){            //列遍历
            pcol = getPointByIndex(p, i, j);
            if(prow == pcol){
                q[i][j] = prow->val;
                prow = prow->right;
            }else{
                q[i][j] = 0;
            }
        }
    }
    return 0;

}

int crossListDisplay(struct node *p)
{
    int i, j;
    struct node *tmp;
    printf("******Cross List Display******\r\n");
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            tmp = getPointByIndex(p, i, j);
            if(NULL == tmp){
                printf("%d", 0);
            }else{
                printf("%d", tmp->val);
            }
            printf("\t");
        }
        printf("\r\n");
    }
    printf("----------------------------------\r\n");
    return 0;
}


int crossListChangeVal(struct node *p, int m, int n, VALTYPE val)
{
    int i = m, j = n;
    struct node* tmp;
    struct node* prow, *pcol;
    tmp = getPointByIndex(p, m, n);
    if(NULL == tmp){                    //该位置没有节点
        //寻找列方向上的前向节点
        while(1){
            if(0 == i){
                prow = &p[n+1];
                break;
            }
            i--;
            prow = getPointByIndex(p, i, n);
            if(NULL != prow){
                break;
            }
        }
        //寻找行方向上的前向节点
        while(1){
            if(0 == j){
                pcol = &p[m+1];
                break;
            }
            j--;
            pcol = getPointByIndex(p, m, j);
            if(NULL != pcol){
                break;
            }
        }
        tmp = malloc(sizeof(struct node));
        memset(tmp, 0, sizeof(struct node));
        tmp->down = prow->down;
        tmp->right = prow->right;
        prow->down = tmp;
        pcol->right = tmp;
        tmp->row = m;
        tmp->col = n;
        tmp->val = val;
    }else{
        tmp->val = val;
    }
    return 0;
}

VALTYPE crossListGetVal(struct node *p, int m, int n)
{
    struct node *tmp;
    VALTYPE val;
    tmp = getPointByIndex(p, m, n);
    if(tmp == NULL){
        val = 0;
    }else{
        val = tmp->val;
    }
    printf("row:%d\tcol:%d\tvalue is:%d\r\n", m, n, val);
    return val;
}

int main()
{
    struct node *head;
    VALTYPE raw_list[M][N] = {  {0,1,2,3},\
                                {4,0,6,7},\
                                {8,9,0,11},\
                                {12,13,14,15} };
    VALTYPE another_list[M][N] = {0,};
    crossListInit(&head);
    crossListStore(head, raw_list);
    crossListRestore(head, another_list);
    crossListDisplay(head);
    crossListChangeVal(head, 0, 0, 1);
    crossListDisplay(head);
    crossListGetVal(head, 3, 3);

    return 0;
}
