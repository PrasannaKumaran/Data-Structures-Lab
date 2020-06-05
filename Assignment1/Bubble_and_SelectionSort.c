#include<stdio.h>
int main()
{
// Bubble Sort
    int choice=0;
	int a[10],n,temp;
	do
    {
    printf("Main Menu \n");
    printf("1.Bubble Sort \n");
    printf("2.Selection Sort \n");
    printf("3.Exit \n");
    printf("Enter choice \n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
	printf("Enter no of elements \n");
	scanf("%d",&n);
	printf("Enter the elements \n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Using Bubble Sort \n");
	for(int i=0;i<n;i++)
		for(int j=i;j<n;j++)
			if(a[j]>a[i])
			{
				temp=a[j];
				a[j]=a[i];
				a[i]=temp;
			}
	printf("The final array is \n");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
		break;
// Selection Sort
case 2:
	printf("Using Selection Sort \n ");
	printf("Enter the elements \n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int pos=0;
	for ( int i=0;i<n;i++)
	{
		 pos=i;
		for(int j=i+1;j<n;j++)
			if(a[j]<a[pos])
 				pos=j;
		{
		temp=a[pos];
		a[pos]=a[i];
		a[i]=temp;
		}
	}
	printf("The final array is \n");
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
		break;
    }
    }while(choice!=3);

	return 0;
}

