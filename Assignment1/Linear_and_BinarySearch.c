//  search
#include<stdio.h>
int	 main()
{
    int choice =0;
	int a[10],n,data;
	do
    {
    printf("\nMain Menu \n");
    printf("1.Linear Search \n");
    printf("2.Binary Search \n");
    printf("3.Exit \n");
    printf("Enter choice \n");
    scanf("%d",&choice);
    switch(choice)
    {

    case 1:	printf("Enter no of elements \n");
	scanf("%d",&n);
	printf("Enter the elements \n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Enter data to be searched \n");
	scanf("%d",&data);
	int flag=0;
	printf("Using linear search \n ");
	for(int i=0;i<n;i++)
		{if (data==a[i])
			{	printf("Data found in the location %d \n",i+1);
			    flag=1;
			    break;
			 }
		}
	if(flag==0)
		printf("Data not found! \n");
    break;

	//Binary search
case 2:	printf("Using Binary Search \n");
	printf("Enter no of elements \n");
	scanf("%d",&n);
	printf("Enter the elements \n");
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Enter data to be searched \n");
	scanf("%d",&data);
	flag=0;
	int left=0,right=n-1,mid;
	while(left<=right)
	{
		mid=(left+right)/2;
		if(data==a[mid])
			{
			 printf("Data found in the location %d",mid+1);
			 flag=1;
			 break;
			}
		else if(data>a[mid])
		  left=mid+1;
		else
		  right=mid-1;
	}
	if(flag==0)
		printf("Data not found! \n");
    }}while(choice!=3);
	return 0;
}

