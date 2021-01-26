#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
////////////  STRUCTURE AND VARIABLE DECLARATION   ///////////////////

struct order { int index;
               int quantity;
               } ;

struct customer
{   
       char name[20];
       char phone_no[10];
       char email[50];
       char password[20];
       char add1[20];
       char add2[20];
       char add3[20];
    
};


int ch_menu,ch_cat,qty,ch_item,ans;
float cost,amt;
char beverage[6][20]={"Elaichi Tea","Cold Coffee","Hot Coffee","Lemonande","Iced Tea","Hot choco"};
char bev_pri[6][4]={"50","80","50","90","100","120"};
char snacks[6][20]={"Aloo Tikki","Aloo Samosa","Vada Pav","Chicken S/w","Egg puff","Cheese S/w"};
char snacks_pri[6][4]={"100","20","40","100","120","80"};
char dessert[6][20]={"Oat Cookie","Cookie    ","Apple Tart","Pastry   ","Choco pops","Muffin   "};
char dessert_pri[6][4]={"30","40","60","50","30","40"};
    
int bev_pri_[6]={50,80,50,90,100,120};
int snacks_pri_[6]={100,20,40,100,120,80};
int dessert_pri_[6]={30,40,60,50,30,40};
    
FILE *m1,*m2,*m3,*ord,*cust_data,*cust_details,*bill;

/////////////////////////    FUNCTIONS          ////////////////////
void introduction();
void signup();
void payment_choice();
void show(FILE* m);
void paybill();
void choose(struct order *ORDER);
void readybill(struct customer *C);
void login();
void view();
void initialize();


void signup(void)
{
    char pass[20];
    struct customer cu;
    printf("\n\t\t Enter username : \n\t\t");
    scanf("%s",cu.name);
    printf("\n\t\t Enter Email Id : \n\t\t");
    scanf("%s",cu.email);
    printf("\n\t\t Enter password : \n\t\t");
    scanf("%s",cu.password);
    printf("\n\t\t Re-enter password : \n\t\t");
    scanf("%s",pass);
    
    if(strcmp(pass,cu.password)==0)
    {
      printf("\n\t\tEnter phone number : \n\t\t");
      scanf("%s",cu.phone_no);
      printf("\n\t\tEnter Address in 3 lines and about 20 characters each : \n\t\t");
      scanf("%s",cu.add1);
      printf("\n\t\t");
      scanf("%s",cu.add2);
      printf("\n\t\t");
      scanf("%s",cu.add3);
      int c;
      printf("\n\t\t ENTER 1 TO PLACE AN ORDER \n\t\t ENTER 2 TO EXIT ");
      fflush(stdin);
      scanf("%d",&c);
      if(c==1)
        { readybill(&cu);
          cust_data = fopen("Customer_data.txt","w");
          fwrite(&cu, sizeof(struct customer) , 1 , cust_data);
          fclose(cust_data);
          }
      else if(c==2)        
        { system("clear");
          printf("\n\n\n\n\t\t\t THANK YOU FOR CHOOSING US !! HAVE A GREAT DAY :) \n\n\n\n\n\n\n\n\n ");
          exit(0);
          }
    }
    else
    {
      printf("Password doesn't match!\nTry again\n");
      signup();
    }
    
}

void introduction(void)
{
    printf("\t\t-------------------------------------------------------------\n\n");
    printf("\t\t\t\tWELCOME TO CUSTOMER BILLING SYSTEM\n\n");
    printf("\t\t--------------------------------------------------------------\n\n");

}

void payment_choice()
{ system("setterm -bold on");
  printf("\t\t===============================================================");
  printf("\n\t\t||\t\t\tYou can pay using :                  ||\n");
  printf("\t\t===============================================================");
  printf("\n\t\t|\t\t\t1)Credit Card \t\t\t      |");
  printf("\n\t\t|\t\t\t2)Debit Card  \t\t\t      |");
  printf("\n\t\t|\t\t\t3)Net Banking \t\t\t      |");
  printf("\n\t\t|\t\t\t4)UPI         \t\t\t      |\n");
  printf("\t\t| \t\t\t\t\t\t\t      |");
  printf("\n\t\t\t\tENTER YOUR CHOICE USING NUMBERS ON LEFT           \n\n \t\t\t\t");
  int choice;
  scanf("%d",&choice);
  system("clear");
  printf("\n\n\n\n\n\n\t\t\t\tRedirecting in a moment....    \n\n\n\n\n\n ");
  remove("Order.txt");
  remove("Customer_Details.txt");
  
  }

void show(FILE* m)
{ char c;
  while(1)
        {
        c = fgetc(m);
        if(c ==  EOF) 
            break;
        else 
            printf("%c",c);
        }
}

void paybill()
{   ord=fopen("Order.txt","r");
    cust_details=fopen("Customer_Details.txt","r");
    bill=fopen("Bill.txt","w");
    show(bill);
    show(cust_details);
    show(ord);
    remove("Order.txt");
    fclose(bill);
    fclose(cust_details);
    payment_choice();
}

void choose(struct order *CUST)
{printf("Enter serial no. of dish to choose  : ");
 scanf("%d",&ch_item);
 if(ch_item== 1 || ch_item==2)
   {if (ch_menu ==2)
    ch_item+=2;
        
   else if(ch_menu == 3)
    ch_item+=4;
               
 printf("Enter quantity: ");
 scanf("%d",&qty);
 CUST->index=ch_item-1;
 CUST->quantity=qty;
 ord=fopen("Order.txt","w");
   }
   else
     printf("!! INVALID CHOICE !!");
}

void readybill(struct customer *C)
{ cust_details=fopen("Customer_Details.txt","w");
  fprintf(cust_details,"\n\t\t Name : %s",C->name);
  fprintf(cust_details,"\n\t\t Phone number : %s",C->phone_no);
  fprintf(cust_details,"\n\t\t Delivery Address : %s , %s , %s ",C->add1,C->add2,C->add3);
  fprintf(cust_details,"\n\t\t Email Address : %s",C->email);
  fprintf(cust_details,"\n\t\t------------------------------ORDER-------------------------------------\n\n");
  fclose(cust_details);
  view();
}
void login()
{   //starting the login window
    //login process started
    struct customer check,verify;
    printf("-------------------------------------------\n");
    printf("\n\t\t USER ACCOUNT AUTHENTICATION \n\n");
   
    printf("  USER NAME:-\n");           //entering the data in the structure to be compared
    fflush(stdin);
    scanf("%s",check.name);
    
    printf(" PASSWORD:-\n");
    fflush(stdin);
    scanf("%s",check.password);
    
    printf(" Phone number:-\n");
    fflush(stdin);
    scanf("%s",check.phone_no);
    
    cust_data=fopen("Customer_Data.txt","r");
    while(fread(&verify, sizeof(struct customer) , 1, cust_data))
        
        { if ( verify.phone_no==check.phone_no && verify.password == check.password)
             { readybill(&verify);
               printf("\n\t\t GREAT !! LOGIN WAS SUCCESSFUL  :) \n");
               }
          else
            { printf("\n\t\t INVALID LOGIN CREDENTIALS PLEASE TRY AGAIN !!\n");
              login();
              }
        }
}

void view()
{   struct order cus;
    system("clear");
    printf("\n\t !!! WELCOME TO GO FOOD THE PERFECT PLACE TO ORDER YOUR MEAL !!! \n");
    printf("\n\t\tEnter 1 for THE GRIND HOUSE CAFE\n\t\tEnter 2 for THE HIDEOUT\n\t\tEnter 3 for WENDY'S CAFE\n\t\t");
    printf("Enter choice of restaurant  : ");
    scanf("%d",&ch_menu);
    system("clear");
    if(ch_menu == 1)
    {
         m1=fopen("menu1.txt","r");
         show(m1);
    }
    else if(ch_menu == 2)
    {
        m2=fopen("menu2.txt","r");
        show(m2);
    }
    
    else if(ch_menu == 3)
    {
          m3=fopen("menu3.txt","r");
         show(m3);
    }
    else
      printf("\n\t\t!!!  INVALID !!! \n \t\tENTER A VALID CHOICE \n");
      
    do{
    printf("Enter \n 1 for Snacks,\n 2 for Desserts,\n 3 for Beverages\n");
    printf("Choose category  :  ");
    scanf("%d",&ch_cat);
    switch(ch_cat)
    {
        case 1: choose(&cus);
                cost=(snacks_pri_[ch_item-1]*qty);
                fprintf(ord,"\n\t\t%s\t%s X %d = %f\n",snacks[cus.index],snacks_pri[cus.index],cus.quantity,cost);
                amt+=cost;
                break;
        case 2: choose(&cus);
                cost=(dessert_pri_[ch_item-1]*qty);
                fprintf(ord,"\n\t\t%s\t%s X %d = %f\n",dessert[cus.index],dessert_pri[cus.index],cus.quantity,cost);
                amt+=cost;
                break;
        case 3: choose(&cus);
                cost+=(bev_pri_[ch_item-1]*qty);
                fprintf(ord,"\n\t\t%s\t%s X %d = %f\n",beverage[cus.index],bev_pri[cus.index],cus.quantity,cost);
                amt+=cost;
                break;
        default: printf("\t\t!!!  INVALID !!! \n \t\tENTER A VALID CHOICE ");
    }
    printf("Add another item? (1 for yes and 2 for no) : ");
    scanf("%d",&ans);
    }while(ans==1);
    
    printf("\nTHE AMOUNT TO BE PAID = %f",amt);
    fprintf(ord,"\n\t\t   THE TOTAL = %f \n",amt);
    fprintf(ord,"\n\t\t         TAX = 10%% \n");
    amt=amt-(0.1*amt);
    fprintf(ord,"\n\t\t      AMOUNT = %f",amt);
    fclose(ord);
    printf("\n\tPROCEED TO BILL PAYMENT (ENTER 1 TO PROCEED/ENTER 2 TO CHOOSE ANOTHER RESTAURANT/ENTER 3 TO EXIT : ");
    scanf("%d",&ans);
    if(ans==1)
        paybill();
    else if(ans==2)
       { system("clear");
         view();
         }
    else if(ans==3)
            { system("clear");
              printf("\n\n\n\n\t\t\t THANK YOU FOR CHOOSING US !! HAVE A GREAT DAY :) \n\n\n\n\n\n\n\n\n ");
            }
    else
       printf(" !! INVALID CHOICE !! ");
}  



void initialize()
{   int i;
    FILE *m1,*m2,*m3;
    m1=fopen("menu1.txt","w");
    fprintf(m1,"%s","-----------------------------------------------------------------------------------------\n\t\t\t\t\tGRIND HOUSE MENU\n-----------------------------------------------------------------------------------------\nSNACKS\n-------------\t\t\t\t\t\tPrice(in Rs.)\n");
    for(i=0;i<2;i++)
    {
        fprintf(m1,"%s\t\t\t\t\t\t",snacks[i]);
        fprintf(m1,"%s",snacks_pri[i]);
        fprintf(m1,"%s","\n");
    }
    fprintf(m1,"%s","\nDESSERTS\n-------------\n");
    for(i=0;i<2;i++)
    {
        fprintf(m1,"%s\t\t\t\t\t\t",dessert[i]);
        fprintf(m1,"%s",dessert_pri[i]);
        fprintf(m1,"%s","\n");
    }
    fprintf(m1,"%s","\nBEVERAGES\n-------------\n");
    for(i=0;i<2;i++)
    {
        fprintf(m1,"%s\t\t\t\t\t\t",beverage[i]);
        fprintf(m1,"%s",bev_pri[i]);
        fprintf(m1,"%s","\n");
    }
    fprintf(m1,"%s","\n");
    fclose(m1);
    
    m2=fopen("menu2.txt","w");
    fprintf(m2,"%s","-----------------------------------------------------------------------------------------\n\t\t\t\t\tHIDEOUT CAFE MENU\n-----------------------------------------------------------------------------------------\nSNACKS\n-------------\t\t\t\t\t\tPrice(in Rs.)\n");
    for(i=2;i<4;i++)
    {
        fprintf(m2,"%s\t\t\t\t\t\t\t",snacks[i]);
        fprintf(m2,"%s",snacks_pri[i]);
        fprintf(m2,"%s","\n");
    }
    fprintf(m2,"%s","\nDESSERTS\n-------------\n");
    for(i=2;i<4;i++)
    {
        fprintf(m2,"%s\t\t\t\t\t\t\t",dessert[i]);
        fprintf(m2,"%s",dessert_pri[i]);
        fprintf(m2,"%s","\n");
    }
    fprintf(m2,"%s","\nBEVARAGES\n-------------\n");
    for(i=2;i<4;i++)
    {
        fprintf(m2,"%s\t\t\t\t\t\t\t",beverage[i]);
        fprintf(m2,"%s",bev_pri[i]);
        fprintf(m2,"%s","\n");
    }
    fprintf(m2,"%s","\n");
    fclose(m2);
    
    m3=fopen("menu3.txt","w");
    fprintf(m3,"%s","-----------------------------------------------------------------------------------------\n\t\t\t\t\tWENDY'S CAFE MENU\n-----------------------------------------------------------------------------------------\nSNACKS\n-------------\t\t\t\t\t\tPrice(in Rs.)\n");
    for(i=4;i<6;i++)
    {
        fprintf(m3,"%s\t\t\t\t\t\t\t",snacks[i]);
        fprintf(m3,"%s",snacks_pri[i]);
        fprintf(m3,"%s","\n");
    }
    fprintf(m3,"%s","\nDESSERTS\n-------------\n");
    for(i=4;i<6;i++)
    {
        fprintf(m3,"%s\t\t\t\t\t\t\t",dessert[i]);
        fprintf(m3,"%s",dessert_pri[i]);
        fprintf(m3,"%s","\n");
    }
    fprintf(m3,"%s","\nBEVARAGES\n-------------\n");
    for(i=4;i<6;i++)
    {
        fprintf(m3,"%s\t\t\t\t\t\t\t",beverage[i]);
        fprintf(m3,"%s",bev_pri[i]);
        fprintf(m3,"%s","\n");
    }
    fprintf(m3,"%s","\n");
    fclose(m3);
    
    bill=fopen("Bill.txt","w");
    fprintf(bill,"\t\t========================================================================");
    fprintf(bill," \n\t\t||\t\t\t\t                BILL \t\t\t\t                 ||\n");
    fprintf(bill,"\t\t========================================================================");  
    fclose(bill);
}  


int main()
{ system("setterm -bold on");
  initialize();
  int choice;
  printf("\n\t\t !!! WELCOME TO JUNKVILLLE EMPIRE THE PERFECT PLACE TO ORDER YOUR MEAL !!! \n\n");
  introduction();
  printf("\t\t\t ENTER 1 IF YOU WANT TO CREATE AN ACCOUNT \n\t\t\t ENTER 2 IF YOU WANT TO LOGIN ");
  scanf("%d",&choice);
  here:
  if(choice==1)
      signup();
  else if(choice==2)
      login();
  else 
      { printf("\n INVALID CHOICE "); goto here;}
  payment_choice();
  
}
