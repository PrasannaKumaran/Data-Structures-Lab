#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"queue.h"
#include"djkstra_list_heap.h"

Queue *q;
int *dist;
char loc[][30]={"Adyar","kilpauk","Chetpet","Nungambakkam","Kodambakkam","Mylapore","Royapettah","Mogappair","Parrys"};
void bill(user obj)
{
    if(strcmp(obj.notify,"\nYour booking has been confirmed... ")==0)
    {
        /*transport: dist*10; rs.10 per km
            water: 5 rs per litr
            additional cost ..5% of total*/
        printf("\n-----Bill-----\n");
        printf("\nDistance from %s to %s : %d",loc[0],loc[obj.location],dist[obj.location]);
        printf("\nDemand : %d",obj.demand);
        printf("\nTransportation charges : %d",dist[obj.location]*10);
        printf("\nWater charges: %d",obj.demand*5);
        float tot=dist[obj.location]*10+obj.demand*5;
        printf("\nAdditional Charges: %.2f",0.05*tot);
        tot+=0.05*tot;
        printf("\nTotal Cost : %.2f",tot);
    }
    else
    {
        printf("\nNo current bookings!!!!");
    }
}

void put_details(user obj)
{
    printf("\nName: %s \t\tPhone No.: %lu\nEmail Id: %s\tLocation: %s\tStorage :%d",obj.name,obj.ph,obj.email,loc[obj.location],obj.cap);
}
void admin(struct Graph* graph)
{
    printf("\n\n-----Admin-----");
    FILE *fp;
    user obj,*u;
    char uname[40],str[100];
    int ch,op;
    do
    {
        printf("\nMENU"); 
        printf("\n1. Process Registrations\n2. Add Edges\n3. Confirm booking\n4. Exit\nEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                fp=fopen("record.dat","r+b");
                fseek(fp,sizeof(user),0);
                while(!feof(fp))
                {
                    fread(&obj,sizeof(user),1,fp);
                    if(obj.v==0)
                    {
                        put_details(obj);
                        printf("\n1-Accept\t0-Reject : ");
                        scanf("%d",&op);
                        if(op==1)
                            obj.v=1;
                        else 
                            obj.v=2;
                        fseek(fp,-sizeof(user),SEEK_CUR);
                        fwrite(&obj,sizeof(user),1,fp);
                    }
                       
                }
                fclose(fp);
                break;
            case 2:
            for(int i=0;i<9;++i){
                printf("\n\t%d - %s",i,loc[i]);
            }
            int s,e,dis;
            printf("\nSelect starting vertex and ending vertex: ");
            scanf("%d",&s);
            scanf("%d",&e);
            printf("\nEnter distance between them: ");
            scanf("%d",&dis);
            addEdge(graph,s,e,dis);
         	 break;
                
            case 3:
                while(!isEmpty(q))
                {
                    u=dequeue(q);
                    printf("\nno: %s,book: %d",u->uname,u->book);
                    
                    put_details(*u);
                    printf("\nDemand: %d",u->demand);
                    printf("\n1-Confirm\t0-Dismiss : ");
                    scanf("%d",&op);
                    if(op==1)
                    {
                        u->book=0;
                        strcpy(u->notify,"\nYour booking has been confirmed... ");
                        printf("%s\n",u->notify );
                        
    		    		dist =Djikstra(graph, 0); 
    		    /*
                        call dijstra here 
                        get distance and calculate bill and assign it to bill variable..
                        */
                        int d=dist[u->location];
                        if(d==9999)
                        {
                        strcpy(u->notify,"\nServices not provided to the given area... ");
                        }
                        //printf("\nDistance: %d",d);
                    }
                    else 
                    {
                        u->book=0;
                        strcpy(u->notify,"\nYour booking has been cancelled due to unavailibility of resources...\nsorry for the inconvinience. ");
                        //printf("%s\n",u->notify );
                    } 
                    {
                        fp=fopen("record.dat","r+b");
                        if(!feof(fp))
                            fread(&obj,sizeof(user),1,fp);
                        while(!feof(fp))
                        {
                            if(strcmp(obj.uname,u->uname)==0)
                            {
                                fseek(fp,-sizeof(user),SEEK_CUR);
                                fwrite(u,sizeof(user),1,fp);
                            }
                            fread(&obj,sizeof(user),1,fp);
                        }
                        fclose(fp);
                    }   
                }
                break;
            case 4:
                return;
            default:
                printf("\nInvalid choice...");
                break;
        }
    }while(ch!=4);
}

user user_menu(user obj)
{
    int ch;
    do
    { 
    printf("\n\n------User Menu------");
    printf("\n\n1. Book water\n2. View Booking Status\n3. View Bill\n4. Exit\nEnter your choice: ");
    scanf("%d",&ch);
    switch(ch){
        case 1:
            printf("\n-----Booking-----");
            printf("\nEnter Demand(in ltrs.): ");
            scanf("%d",&obj.demand);
            while(obj.demand>obj.cap)
            {
                printf("\nDemand cannot be more than your storage capacity...");
                printf("\nRe-enter Demand(in ltrs.): ");
                scanf("%d",&obj.demand);
            }
            obj.book=1;
            Enqueue(q,&obj);
            strcpy(obj.notify,"Your booking is yet to be confirmed...");
            printf("\n%s ",obj.notify);
            break;
        case 2:
            printf("\n\n-----Booking Status-----");
            printf("\n %s",obj.notify);
            break;
        case 3:
        	bill(obj);
            break;
        case 4:
            return obj;
        default:
            printf("\nInvalid choice....");
    }
    }while(ch!=4);
    return obj;
}
void get_user(char uname[])
{
    char re[40];
    FILE *fp;
    user obj;
    strcpy(obj.uname,uname);
    fp=fopen("record.dat","ab");
    printf("\nEnter your Name: ");
    scanf(" %[^\n]",obj.name);
    do
    { 
        printf("\nEnter new password: ");
        scanf("%s",obj.pwd);
        printf("\nRe-enter password: ");
        scanf("%s",re);
        if(strcmp(obj.pwd,re))
            printf("\nNot matching!!!");
    }while(strcmp(obj.pwd,re));
    printf("\nEnter Email Id:");
    scanf("%s",obj.email);
    for(int i=0;i<9;++i){
        printf("\n\t%d - %s",i,loc[i]);
    }
    printf("\nSelect location(0-8): ");
    scanf("%d",&obj.location);
    printf("\nEnter phone Number : ");
    scanf("%li",&obj.ph);
    printf("\nEnter water storage capacity: ");
    scanf("%d",&obj.cap);
    obj.book=0;
    obj.demand=0;
    obj.v=0;
    strcpy(obj.notify,"No bookings done...");
    fwrite(&obj,sizeof(user),1,fp);
    printf("\nRegister Successfully!!!!");
    printf("\nWait for admin verification...");
    fclose(fp);
}
void login(struct Graph* graph)
{
    printf("\n------Login------\n");
    char uname[40],pwd[40];
    FILE *fp;
    user obj;
    fp=fopen("record.dat","rb");
    printf("\nEnter username: ");
    scanf("%s",uname);
    int f=0;
    fread(&obj,sizeof(user),1,fp);
    while(!feof(fp))
    {
        if(strcmp(uname,obj.uname)==0)
        {
            f=1;
            if(obj.v==1)
            { 
                printf("\nEnter password: ");
                scanf("%s",pwd);
                if(strcmp(pwd,obj.pwd)==0)
                {
                    printf("\nLogin Successful......");
                    fclose(fp);
                    if(strcmp(uname,"admin")==0)
                        admin(graph);
                    else
                        {
                        obj=user_menu(obj);
                        fseek(fp,-sizeof(user),SEEK_CUR);
                        fwrite(&obj,sizeof(user),1,fp);
                        fclose(fp);
                    }
                    return;
                }
                else
                {
                    printf("\nLogin failed....");
                    break;
                }
            }
            else if(obj.v==0)
            {
                printf("\nAccount not yet verified!!! Try some time later...");
                fclose(fp);
                return;
            }
            else if(obj.v==2)
            {
                printf("\nYour Registration has been rejected by the admin... try registering again...");
                fseek(fp,0,SEEK_SET);
                FILE *ftemp=fopen("temp.dat","wb");
                fread(&obj,sizeof(user),1,fp);
                while(!feof(fp))
                {
                    if(strcmp(obj.uname,uname)!=0)
                        fwrite(&obj,sizeof(user),1,ftemp);
                    fread(&obj,sizeof(user),1,fp);
                }
                fclose(ftemp);
                fclose(fp);
                remove("record.dat");
                rename("temp.dat","record.dat");
                return;
            }
        }
        fread(&obj,sizeof(user),1,fp);
    }
    fclose(fp);
    if(f==0)
        printf("\nEnter valid user name...");
}

int regis()
{
    printf("\n----REGISTER----\n");
    char uname[40],pwd[40],re[40];
    user obj;
    FILE *fp;
    fp=fopen("record.dat","rb");
    printf("\nEnter user name(0-quit): ");
    scanf("%s",uname);
    while(!feof(fp))
    {
        fread(&obj,sizeof(user),1,fp);
        if(strcmp(uname,"0")==0)
        {
            fclose(fp);
            return 0;
        }
        if(strcmp(uname,obj.uname)==0)
        {
            printf("\nUsername already taken!!!\nRe-Enter!!!");
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    get_user(uname);
    return 0;
}
int main()
{
    int ch;
    q=createQueue(9);
    struct Graph* graph = createGraph(9);
    {
        remove("record.dat");
        remove("complaints.txt");
        FILE *fp=fopen("record.dat","wb");
        user obj;
        strcpy(obj.uname,"admin");
        strcpy(obj.pwd,"admin");
        obj.v=1;
        fwrite(&obj,sizeof(user),1,fp);
        fclose(fp);
    }
    do
    {
        printf("\n\n------WATER MANAGEMENT SYSTEM------");
        printf("\n\n1.Register\n2.Login\n3.Exit\nEnter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                if(regis())
                    regis();
                break;
            case 2:
                login(graph);
                break;
            case 3:
            	break;
            default:
                if(ch!=3)
                    printf("\nInvalid choice....");
                break;
        }
    }while(ch!=3);
    return 0;
}
