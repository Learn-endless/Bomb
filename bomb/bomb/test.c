#include<stdio.h>
#include<windows.h>
int main()
{
	int i;
	char name[100];
	printf("Ŀ�꣺");
	scanf_s("%s", &name, 40);
	printf("������");
	scanf_s("%d", &i);
	HWND H = FindWindow(0, name);	//Ѱ�ҶԻ��� 
	while (i-->0)
	{
		SendMessage(H, WM_PASTE, 0, 0);	//ճ�� 
		SendMessage(H, WM_KEYDOWN, VK_RETURN, 0);//�س� 
	}
}
