#include<stdio.h>
#include<windows.h>
int main()
{
	int i;
	char name[100];
	printf("目标：");
	scanf_s("%s", &name, 40);
	printf("次数：");
	scanf_s("%d", &i);
	HWND H = FindWindow(0, name);	//寻找对话框 
	while (i-->0)
	{
		SendMessage(H, WM_PASTE, 0, 0);	//粘贴 
		SendMessage(H, WM_KEYDOWN, VK_RETURN, 0);//回车 
	}
}
