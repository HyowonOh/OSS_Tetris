#include "Queue.h"
#include <string.h>

void Queue_Create(Queue* queue, int capacity, size_t size){ //ť ����
	Array_Create(&(queue->data), capacity, size); // �迭�� ����Ͽ� ť�� ����
	queue->capacity = queue->data.capacity;
	queue->rear = -1; // ���� �ƹ� ���� ������ �ǹ�
}

void Queue_Destroy(Queue* queue){ // ť�� ����
	Array_Destroy(&(queue->data));
}

int Queue_Put(Queue* queue, void* object, size_t size){ //ť�� ���� �Է�
	int index;
	if (!Queue_IsFull(queue)){ //���� á�� ���
		index = Array_Store(&(queue->data), queue->rear + 1, object, size);
	}
	else{
		index = Array_AppendFromRear(&(queue->data), object, size); //���� ��ġ ���� Index�� ����
		queue->capacity++;
	}
	if (index != -1){//ť�� ���� ���ٸ� ���� ��ġ�� ���� ����
		queue->rear++; 
	}
	return queue->rear;
}

void Queue_Get(Queue* queue, void* object, size_t size){ //ť ���� �ϳ� ������
	int index;
	if (Queue_IsEmpty(queue)){ //ť�� ���� ���� ���
		memset(object, 0, size);
	}
	else{
		Array_GetAt(&(queue->data), 0, object, size);
		index = Array_DeleteFromFront(&(queue->data), size); //���� �տ� �ִ� ������ ���
		if (index == -1){ 
			queue->capacity--;
			queue->rear--;
		}
	}
}

void Queue_At(Queue* queue, void* object, int index, size_t size){ //ť �˻�
	if (Queue_IsEmpty(queue)){
		memset(object, 0, size);
	}
	else{
		Array_GetAt(&(queue->data), index, object, size);
	}
}

int Queue_IsEmpty(Queue* queue){ //ť�� ���°� ��� �ִ��� Ȯ��
	return queue->rear == -1;
}

int Queue_IsFull(Queue* queue){ //���� ť���� Ȯ��
	return queue->rear >= queue->capacity - 1;
}