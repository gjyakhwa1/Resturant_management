#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<windows.h>
struct newAccount{
char accName[20];
int accNumber;
float balance;
};
struct accLogin
{
    char userID[20];
    char userName[20],p[20];
    float balance;
};
struct order {
		long int transactionID;
    	char userID[20];
    	char userName[20];
    	int orderedItems[12];
    	float total;

	};
void gotoxy(int,int);//moves the cursor position
void displayMenuList();//show the menu for customer
void orderFood(struct accLogin);//enable the customer to order food using numeric value which is switch to food
void displayOrder(struct order);//shows the bill
void writeOrder(struct order );//write order in file recorder.txt
void adminLogin(struct accLogin );//main login page for admin or employee
void newAccount(void);//helps in creating new account
void displayAccount(void);////display all the existing account which is host by admin
int i,found;
void customerLogin(struct accLogin);//login page for customer
void balanceUpdate(float , char[20]);//update the balance after ordering of food by customer
void viewSpecificOrder(long int );//it shows the previous order after entering the transaction id number
long int getTransactionID();//get transaction id from the file recorder.txt
//username.txt records the password and user id of the customer and admin
//reOrder.txt records the order
	float *currentBalance;
	long int ID;


void main()
{
    system("COLOR f0");
	struct accLogin login;
    FILE *ptr;
	ptr=fopen("userName.txt","rb");
	char userID[20],pwrd[20],p1[20],c;
	int i,j=0;
	while(1){
	system("cls");
	gotoxy(1,1);
	printf("______________________________________________________________________________________________________________________");
    gotoxy(37,3);
    printf("WELCOME TO RESTAURANT MANAGEMENT SYSTEM");
	gotoxy(1,4);
    printf("______________________________________________________________________________________________________________________");
	gotoxy(40,6);
	printf("Enter User ID  : ");
	scanf("%[^\n]",&userID);
	gotoxy(40,8);
	printf("Enter Password : ");
	fflush(stdin);
	for(i=0;i<8;i++)
    {
        c=getch();
        pwrd[i]=c;
        c='*';
        printf("%c",c);
    }
    pwrd[i]='\0';
    getch();
    found=0;
    //char a[20]={"55300"};
	while((fread(&login,sizeof(login),1,ptr))==1){
	if(((strcmp(login.userID,userID)==0))&&strcmp(pwrd,login.p)==0){
		if(!strcmp(login.userID,"55300")){
			adminLogin(login);
		}else{
		customerLogin(login);
	}
		found=1;
		break;
	}
	}
	if(found!=1){
            gotoxy(37,11);
		printf("Invalid User ID or Password ");
		getch();
	}
	gotoxy(37,13);
	printf("Do you want to exit ?(y/n))");
	//c=getch();
	while(1){
	c=getch();
	if(c=='y'){
		break;
	}else if(c=='n'){
		break;
	}
}if(c=='y') break;

	//getch();
	//printf("rewind");
	rewind(ptr);
	fflush(stdin);
}
	fclose(ptr);

}

void adminLogin(struct accLogin login){
while(1){
	system("cls");
    gotoxy(1,1);
	printf("______________________________________________________________________________________________________________________");
	gotoxy(45,3);
	printf("Welcome Admin");
	gotoxy(1,4);
    printf("______________________________________________________________________________________________________________________");
	char log;
	gotoxy(5,6);
	printf("1.CREATE NEW ACCOUNT");
	gotoxy(5,8);
	printf("2.DISPLAY EXISTING ACCOUNT");
	gotoxy(5,10);
	printf("3.LOAD BALANCE ");
	gotoxy(80,6);
	printf("4.VIEW ALL TRANSACTIONS ");
	gotoxy(80,8);
	printf("5.VIEW SPECIFIC TRANSACTION ");
	gotoxy(80,10);
	printf("6.LOG OUT");
	printf("\n______________________________________________________________________________________________________________________");
	gotoxy(45,13);
	printf("Enter number:");
fflush(stdin);
log=getch();
	if(log=='1'){
		newAccount();
	}else if(log=='6'){
	    gotoxy(37,12);
		printf("Successfully Logged Out !!");
		break;
	}else if(log=='4'){
		FILE *f;
	int i=1;
	struct order order1;
	f=fopen("recOrder.txt","rb");
    printf("\n\t\t-----------------------------------------------------------------------");
	printf("\n\t\tSN\t TRANSACTIONID \tUSERID     \tUSERNAME \tTOTAL");
	printf("\n\t\t-----------------------------------------------------------------------");
	while(fread(&order1,sizeof(order1),1,f)==1){
		printf(" \n\t\t %d\t %li \t%s           %s\t\tRs:%f ",i,order1.transactionID,order1.userID,order1.userName,order1.total);
		i++;
}
getch();
fclose(f);

	}
	else if (log=='5'){
    gotoxy(45,13);
	printf("Enter transaction ID : ");
	scanf("%li",&ID);
	viewSpecificOrder(ID);
	getch();
}
	else if(log=='2'){
		displayAccount();
	}else if(log=='3'){
		float a;
		char name[20];
		gotoxy(45,13);
		printf("Enter the user ID :");
		fflush(stdin);
		gets(name);
		gotoxy(45,15);
		printf("Enter balance you want to load:");
		scanf("%f",&a);
		balanceUpdate(a,name);
		gotoxy(42,18);
		printf("Balance sucessfully updated !!!!!!");
		getch();
	}
	//getch();
}
}

void customerLogin(struct accLogin login)
{

	currentBalance=&login.balance;

while(1){
	system("cls");
	printf("-------------------------------------------WELCOME TO OUR RESTAURANT---------------------------------------------");
    printf(" \nCustomer name:Mr.%s",login.userName);
    printf("\t\t\t\t\t\t\t\t Current Balance : %.2f",login.balance);
  printf("\n______________________________________________________________________________________________________________________");
    char log;
    gotoxy(5,4);
printf("1.ORDER FOOD");
gotoxy(5,6);
printf("2.VIEW All YOUR ORDERS");
gotoxy(80,4);
printf("3.VIEW SPECIFIC ORDER");
gotoxy(80,6);
printf("4.LOG OUT");
printf("\n______________________________________________________________________________________________________________________");
gotoxy(45,10);
printf("Enter number:");
//scanf("%d",&log);

log=getch();

if(log=='1')
{ system("cls");
orderFood(login);

}else if(log=='2'){
    int SN=0;
	FILE *f;
	struct order order1;
	f=fopen("recOrder.txt","rb");
	gotoxy(16,10);
	printf("---------------------------------------------------------------------");
	gotoxy(16,11);
	printf("SN\tTRANSACTION ID\tUSERID\t\tUSERNAME\tTOTAL");
	gotoxy(16,12);
	printf("---------------------------------------------------------------------");
	while(fread(&order1,sizeof(order1),1,f)==1){
		if((strcmp(login.userID,order1.userID)==0)){
		printf(" \n\t\t%d \t%li\t\t%s \t \t%s\t \tRs:%f ",SN+1,order1.transactionID,order1.userID,order1.userName,order1.total);
    SN++;

	}
}
getch();
fclose(f);
}else if(log=='3'){
    gotoxy(45,10);
	printf("Enter transaction ID : ");
	scanf("%li",&ID);
	viewSpecificOrder(ID);
	getch();
}
else if(log=='4'){
        gotoxy(42,10);
	printf("Successfully logged out !!");
	break;
}
else
{
 //readOrder();
}
}
//getch();
}

void displayAccount(){
	system("cls");
	struct accLogin login;
	int a=1;
    FILE *ptr;
	ptr=fopen("userName.txt","rb");
	  printf("\nSN. \tUSERID\t\tUSERNAME\tPASSWORD\tBALANCE");
	  printf("\n");
	while((fread(&login,sizeof(login),1,ptr))==1){
	printf("\n%d. \t%s\t\t%s\t\t%s\t%f",a,login.userID,login.userName,login.p,login.balance);
	a++;

	}
getch();
}

void balanceUpdate(float a, char userID[20]){
	struct accLogin login1;
    FILE *ptr;
    // FILE *ptr1;
	ptr=fopen("userName.txt","rb+");
	//ptr1=fopen("userName1.txt","wb");
	//rewind(ptr);
	while((fread(&login1,sizeof(login1),1,ptr))==1){
	//	printf("\n %s %s ",login1.userID,userID);
	//	getch();
		if(strcmp(login1.userID,userID)==0){
			fseek ( ptr, -sizeof(login1), SEEK_CUR ) ;
			login1.balance=login1.balance+a;
			fwrite(&login1,sizeof(login1),1,ptr);
			//printf("flag ");
			break;
		//	fseek ( ptr, 2*sizeof(login1), SEEK_CUR ) ;

		}
		//else{

		//fwrite(&login1,sizeof(login1),1,ptr);
		//}
			//getch();

}
fclose(ptr);//fclose(ptr1);
//rename("userName1.txt","userName.txt");
}

void newAccount()
{ long int c,d,e;
	struct accLogin login;
    char ch;
    FILE *f;
    f=fopen("userName.txt","ab");
    fflush(stdin);
    system("cls");
    printf("______________________________________________________________________________________________________________________");
    gotoxy(45,2);
    printf(" Add new account");
    printf("\n______________________________________________________________________________________________________________________");
    do
    {
        gotoxy(40,4);
        printf("Enter id :");
        scanf("%[^\n]",login.userID);
        gotoxy(40,6);
        printf("Enter name : ");
        scanf(" %[^\n]",login.userName);
        gotoxy(40,8);
        printf("Enter password :");
        scanf(" %[^\n]",login.p);
        gotoxy(40,10);
        printf("balance :");
        scanf(" %f",&login.balance);
        fwrite(&login,sizeof(login),1,f);
        fflush(stdin);
        gotoxy(35,12);
        printf(" Account Successfully Added ... ");
        gotoxy(30,14);
        printf("Do you want to add more accounts(y/n):");
        ch=getch();
    }while(ch=='y');
     fclose(f);
}


void viewSpecificOrder(long int a){
	FILE *f;
	struct order order1;
	f=fopen("recOrder.txt","rb");
	while(fread(&order1,sizeof(order1),1,f)==1){
		if(order1.transactionID==a){
		displayOrder(order1);
		//break;
	}
}
	fclose(f);
}


void orderFood(struct accLogin login)
{
    int num ,buf,i,j,priceList[12]={70,75,110,120,210,60,45,80,300,50,25,30};
    char c,confirm;
    float total=0;
    struct order order1;
    strcpy(order1.userID,login.userID);
    strcpy(order1.userName,login.userName);
    for(i=0;i<12;i++){
    		order1.orderedItems[i]=0;
	}
	displayMenuList();
	printf("\nEnter number of product you want to order:");
    scanf("%d",&num);
	for(j=0;j<num;j++){
	printf("\nEnter the product number from menu:");
    scanf("%d",&i);
     printf("Enter the quantity:");
    scanf("%d",&buf);
    order1.orderedItems[i-1]=buf+order1.orderedItems[i-1];
}

	system("cls");
    displayMenuList();
   displayOrder(order1);
   for(i=0;i<12;i++){
    		total=total+priceList[i]*order1.orderedItems[i];
	}
	order1.total=0.9*total;
   // printf("%.2f",order1.total);
   order1.transactionID=getTransactionID();
    //getch();
   if((*currentBalance)>order1.total) {
     printf("\n                            Do you want to confirm your order:y/n:");
   scanf(" %c",&confirm);
   if(confirm=='y')
   {
       writeOrder(order1);
       balanceUpdate(-order1.total,order1.userID);
       *currentBalance=*currentBalance-order1.total;
       balanceUpdate(order1.total,"55300");
       //accountPay();
       getch();
   }
}else{
	printf(" \n\t Insufficient Balance !! Please contact our Employee to load Balance in your account \n\t Thank you !!");
	getch();
}
}
 void displayMenuList()
   {
        printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-MENU-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
    printf("\n1.BUFF MOMO:Rs70\t\t2.CHOWMIEN:Rs75\t\t\t3.PIZZA:Rs110\t\t4.CHOUPSEY:Rs120");
    printf("\n\n5.SIZZLER:Rs210\t\t\t6.FRIED RICE:Rs60\t\t7.FRENCH FRY:Rs45\t8.CHICKEN MOMO:Rs80");
    printf("\n\n9.SAME BAJI SET:Rs300\t\t10.VEG PAKODA:Rs50\t\t11.COKE:Rs25\t\t12.ICECREAM:Rs30\n");
    printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
   }

long int getTransactionID(){
	struct order order1;
	FILE *f;
	f=fopen("recOrder.txt","rb");
	while(fread(&order1,sizeof(order1),1,f)==1){
		//displayOrder(order1);
	}
	return(order1.transactionID+28795);
	fclose(f);
}
void displayOrder(struct order order1)
{

	int i,j=1;
	float subTotal=0,total;
	char itemList[12][20]={"BUFF MOMO","CHOWMEIN","PIZZA    ","CHOUPSEY","SIZZLER","FRIED RICE","FRENCH FRY","CHICKEN MOMO","SAME BAJI SET","VEG PAKODA","COKE     ","ICECREAM"};
	int priceList[12]={70,75,110,120,210,60,45,80,300,50,25,30};
	 printf("\n\t\t-------------------------------------------------------------------------------------");
	printf("\n\t\t User Name :%s \t\t User ID : %s \t\t TransactionID :%li",order1.userName,order1.userID,order1.transactionID);
	 printf("\n\t\t-------------------------------------------------------------------------------------");
	printf("\n\t\t\t\t--------------------------BILL-----------------------------");
    printf("\n\t\t\t\tSN ITEMS           PRICE    \tQUANTITY   \tTOTAL PRICE");
    printf("\n\t\t\t\t------------------------------------------------------------");
    for(i=0;i<12;i++){
    	if(order1.orderedItems[i]!=0){

    	printf("\n\t\t\t\t%d.%s\t   %d\t\t%d\t\t%d ",j,itemList[i],priceList[i],order1.orderedItems[i],priceList[i]*order1.orderedItems[i]);
    	subTotal=subTotal+priceList[i]*order1.orderedItems[i];
    	j++;
	}

}
printf("\n\t\t\t\t-----------------------------------------------------------");
printf("\n\t\t\t\tTotal");
printf("\t\t\t\t\t\tRs %.2f",subTotal);
printf("\n\t\t\t\tDiscount amount");
printf("\t\t\t\t\tRs %.2f",(0.1*subTotal));
printf("\n\t\t\t\t-----------------------------------------------------------");
printf("\n\t\t\t\tGrand total");
printf("\t\t\t\t\tRs %.2f",(0.9*subTotal));
printf("\n\t\t\t\t-----------------------------------------------------------");
}

void writeOrder(struct order order1)
{
    long int c,d,e;
    FILE *fptr1;
    fptr1=fopen("recOrder.txt","ab+");
     fwrite(&order1,sizeof(order1),1,fptr1);
     printf("\n                               Paid !!");
     fclose(fptr1);
}
COORD coord={0,0};
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
