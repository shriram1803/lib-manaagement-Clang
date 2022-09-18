#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>

//defining the properties of the fields used in the program
#define OUT 0

void Addbook();
void Restock();
void Searchbook();
void Displaybook();
void Author();
void Stock();
void Issue();
void bookret();
void Addmembr();
void Exit();
void check_validity(int mid,char bname[25],char author[25]);
int valid_date(int date, int mon, int year);

char info[500];

struct
{
  int bid;
  int quantity;
  int issuenum;
  char bname[25] ;
  char author[25];
}book;
struct
{
  int mid;
  int availibcard;
  char mname[25] ;
  char department[25];
  char type[25];
}membr;
struct 
{
	int mnum;
	int day1;
	int mon1;
	int year1;
	char bookname[25];
	char bookauthor[25];	
}issue ;

//initializing the files used in the program

FILE *librecord;
FILE *membrrecord;
FILE *issuerecord;
FILE *fp1;
FILE *fp2;
FILE *fp3;
FILE *temp1;
FILE *temp2;
FILE *temp3;

int main()
{       
    int choice=0,i;
    printf("\n\t\t<<LIBRARY MANAGEMENT SYSTEM>> \n");
    do{
    printf("\n\t~~MENU~~\n 1> Add A New Book\n 2> Restock a Book \n 3> Search a book \n 4> Display Complete Information\n 5> Display All Books of An Author\n 6> List Count of Books (Issued & On Stock)\n 7> To Issue a Book \n 8> To Return a Book \n 9> Add A New Member\n 10> Exit the program\n\n\t Enter your choice <1-10>: ");
    scanf("%i",&choice);
       
    switch (choice)
    {   
        case 1:
            Addbook();
            break;
        case 2:
        	Restock();
        	break;
        case 3:
            Searchbook();
            break;
        case 4:
            Displaybook();
            break;
        case 5:
            Author();
            break;
        case 6:
            Stock();
            break;
        case 7:
            Issue();
            break;
        case 8:
            bookret();
            break;
        case 9:
            Addmembr();
            break;
        case 10:
            Exit();
        default:
            printf(" ! Invalid Input...\n");
    }
}while(choice!=10);
 return (0);
}
void Addbook()
{
        int i;
    	librecord = fopen("librecord.txt","a+");       //opening the librecord file
    	printf("Enter The uniqueid of The Book :(Integer) \n");
        scanf("%d",&book.bid);
        printf("Enter The Name of The Book :\n");
        scanf("%s",book.bname);
        printf("Enter The Name of Author :\n");
        scanf("%s",book.author);
        printf("Enter The Number of copies :\n");
        scanf("%d",&book.quantity);
        book.issuenum = 0;
        fprintf(librecord,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d\t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
        fclose(librecord);
        printf(" (' ' ) A New Book has been Added Successfully...\n");
}
void Addmembr()
{
    int i,opt;
    membrrecord = fopen("membrrecord.txt","a+");
    printf("\t\t1. Add Faculty\n\t\t2. Add Student\n\t\t");
        scanf("%d",&opt);
    if(opt==1){
    strcpy(membr.type,"Staff");
    membr.availibcard=250;
	}
	else{
    strcpy(membr.type,"Student");
    membr.availibcard=5;
	}
    printf("Enter The userid of the Member(Integer) :\n");
        scanf("%d",&membr.mid);
    printf("Enter The Name of the Member :\n");
        scanf("%s",membr.mname);
    printf("Enter The Department\n");
        scanf("%s",membr.department);
    fprintf(membrrecord,"\n %d\t\t%s\t\t%s\t\t%s\t\t%d\t",membr.mid,membr.mname,membr.department,membr.type,membr.availibcard);
    fclose(membrrecord);
    printf("\n (' ') Added  A New member Successfully...\n");
}
void Restock()
{
		char Target[25],Target1[25],stats[3];
        int Found=0,restocknum;
        printf("\nEnter The Name Of Book : ");
            scanf("%s",Target);
        printf("\nEnter The Author Of Book : ");
            scanf("%s",Target1);
                  fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("librecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2) && Found==0)
                                {
                                    fscanf(temp2,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.quantity,&book.issuenum);
                                    if(strcmp(Target,book.bname)==0 && strcmp(Target1,book.author)==0){
                                    	Found=1;
									}
                                    if(Found)
                                    {
                                    		printf("Current Copies of the Book : %d",book.quantity);
                                            	printf("\nEnter the Number of Copies to be Added : " );
                                                	scanf("%d",&restocknum);
                                        	book.quantity = book.quantity + restocknum;
                                        fprintf(fp2,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d\t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
                                    }
                                    else if(!Found){
                                        fprintf(fp2,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d\t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
										}
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);
                            fclose(librecord);
                            remove("librecord.txt");
                            rename("fp2.txt","librecord.txt");
                            printf(" (' ') Book Successfully Restocked...\n");
 }  
void Displaybook()
{
	int opt;
	printf("\t\t1. DISPLAY ALL INFO\n\t\t2. DISPLAY BOOK INFO\n\t\t3. DISPLAY MEMBERS INFO\n\t\t4. DISPLAY ISSUED BOOKS INFO \n\t\t   YOUR CHOICE :");
	scanf("%d",&opt);
	if (opt == 2){
    librecord = fopen("librecord.txt","a+");
    printf("\n\n\t<-------------------BOOKS INFO------------------->\n\nBookid\t\tName\t\tAuthor\t\tStock\t\tIssued\n",info);
    do
    {
        fgets(info,500,librecord);
        printf("%s\n",info);
    }while(!feof(librecord));
    fclose(librecord);
}
    else if(opt == 3){
    membrrecord = fopen("membrrecord.txt","a+");
    printf("\n\n\t<-------------------MEMBERS INFO------------------->\n\n  Mid\t\t\tName\t\tDept\t\tType\t\tAvailablecards\n");
    do
    {
        fgets(info,500,membrrecord);
        printf("%s\n",info);
    }while(!feof(membrrecord));
    fclose(membrrecord);
}
    else if(opt == 4){
    issuerecord = fopen("issuerecord.txt","a+");
    printf("\n\n\t<-------------------ISSUED BOOKS INFO-------------------->\n\nMem ID\t\tBook name\tAuthor name\tIssued Date\n");
    do{
    	fgets(info,500,issuerecord);
    	printf("%s\n",info);
	}while(!feof(issuerecord));
	fclose(issuerecord);
}
    else{
     	librecord = fopen("librecord.txt","a+");
    printf("\n\n\t<-------------------BOOKS INFO------------------->\n\nBookid\t\tName\t\tAuthor\t\tStock\t\tIssued\n",info);
    do
    {
        fgets(info,500,librecord);
        printf("%s\n",info);
    }while(!feof(librecord));
    fclose(librecord);
    membrrecord = fopen("membrrecord.txt","a+");
    printf("\n\n\t<-------------------MEMBERS INFO------------------->\n\n  Mid\t\t\tName\t\tDept\t\tType\t\tAvailablecards\n");
    do
    {
        fgets(info,500,membrrecord);
        printf("%s\n",info);
    }while(!feof(membrrecord));
    fclose(membrrecord);
    issuerecord = fopen("issuerecord.txt","a+");
    printf("\n\n\t<-------------------ISSUED BOOKS INFO-------------------->\n\nMem ID\t\tBook name\tAuthor name\tIssued Date\n");
    do{
    	fgets(info,500,issuerecord);
    	printf("%s\n",info);
	}while(!feof(issuerecord));
	fclose(issuerecord);
	 }
}
void Searchbook()
{
    int i;
    char Target[25],Target1[25],stats[3];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        printf(" ! The File is Empty...\n\n");
    else
    {
        printf("\nEnter The Name Of Book : ");
            scanf("%s",Target);
        printf("\nEnter The Author Of Book : ");
            scanf("%s",Target1);
        while(!feof(librecord) && Found==0)
        {
        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.quantity,&book.issuenum);
            if(strcmp(Target,book.bname)==0 && strcmp(Target1,book.author)==0)
            Found=1;             
        }
        if(Found)
        {
         printf("\nThe Unique ID of The Book:  %d\nThe Name of Book is:  %s\nThe Author is:  %s\nCopies in Stock:  %d\nCopies Issued:  %d\n\n",book.bid,book.bname,book.author,book.quantity,book.issuenum);
            }
        else if(!Found)
            printf("! There is no such Entry...\n");
        fclose(librecord);
    }
}
void Author()
{
    int i = 1;   
    char Target[500];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
    printf(" ! The file is empty... \n\n");
    else
    {
        printf("\nEnter The Name Of Author : ");
            scanf("%s",Target);
        printf("\nBooks:");
        while(!feof(librecord))
        {
            fscanf(librecord,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.quantity,&book.issuenum);
            if(strcmp(Target,book.author)==0)
            {
                Found=1;
                printf("\n\t%d. %s",i,book.bname);
                i++;
            }       
        }
        if(!Found)
            printf(" ! There is no such Entry...\n");
        fclose(librecord);
    }
}
void Stock()
{
    int i,issuecount=0,stockcount=0;   
    char Issued[100][20];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(librecord))
        {
            fscanf(librecord,"%d %s %s %d %d",&book.bid,book.bname,book.author,&book.quantity,&book.issuenum);
            if(feof(librecord)){
            	break;
			}
			else{
                stockcount = stockcount + book.quantity;
            
            
                issuecount = issuecount + book.issuenum;
            }
        }
        fclose(librecord);
    printf("\nCount of issued Books:%d\nCount of Books in Stock:%d\n",issuecount,stockcount-1);
    }
}
void Issue()
{
    int mid,i,Found1=0,Found2=0,Found3=0;char issubookname[25],issuauthorname[25];
    //temp1=librecord;temp2=membrrecord;
    printf("\nEnter The userid of the Member : \n");
        scanf("%d",&mid);
    if((membrrecord=fopen("membrrecord.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(membrrecord)&& Found1==0)
        {
            fscanf(membrrecord,"%d %s %s %s %d ",&membr.mid,membr.mname,membr.department,membr.type,&membr.availibcard);
            if(mid==membr.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard<1)
            {
                printf(" ! Library card not available...\n");
            }
            else
            {    printf("\nEnter The Name of book :");
                scanf("%s",issubookname);
                printf("\nEnter the Name of Author :");
                scanf("%s",issuauthorname);
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    printf(" ! The file is empty...\n\n");
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.quantity,&book.issuenum);
                        if(strcmp(issubookname,book.bname)==0 && strcmp(issuauthorname,book.author)==0)
                            Found2=1;
                    }
                    if(Found2)
                    {
                        if(book.quantity==0)
                        {
                            printf(" ! Book OUT of Stock...\n");
                        }
                        else
                        {   
                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("membrrecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %s %d  ",&membr.mid,membr.mname,membr.department,membr.type,&membr.availibcard);
                                    if(mid==membr.mid)
                                    {
                                        membr.availibcard--;
                                        fprintf(fp2,"\n %d\t\t%s\t\t%s\t\t%s\t\t%d\t",membr.mid,membr.mname,membr.department,membr.type,    membr.availibcard);
                                    }
                                    else{
                                        fprintf(fp2,"\n %d\t\t%s\t\t%s\t\t%s\t\t%d\t",membr.mid,membr.mname,membr.department,membr.type,membr.availibcard);}
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);
                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.quantity,&book.issuenum);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(issubookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d   \t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
                                    }
                                    else
                                    {
                                    	if(strcmp(issuauthorname,book.author)!=0){
                                    		 fprintf(fp1,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d\t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
										}
										else{
											book.quantity--;
											book.issuenum++;
											 fprintf(fp1,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d\t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
											 
											 issuerecord = fopen("issuerecord.txt","a+");
											 issue.mnum = mid;
											 strcpy(issue.bookname,issubookname);
											 strcpy(issue.bookauthor,issuauthorname);
											 printf("\nEnter issue date (DD/MM/YYYY): \n");
                                               scanf("%d/%d/%d",  &issue.day1,&issue.mon1, &issue.year1);
                                               fprintf(issuerecord,"\n%d\t\t%s\t\t%s\t\t%d/%d/%d",issue.mnum,issue.bookname,issue.bookauthor,issue.day1,issue.mon1,issue.year1);
                                               fclose(issuerecord);
										}
                                       
                                    }    
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(membrrecord);
                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");
                            remove("membrrecord.txt");
                            rename("fp2.txt","membrrecord.txt");
                            printf(" (' ') Book Successfully issued...\n");
                        }               
                    }
                    else if(!Found2)
                        printf(" ! There is no such Book...\n");      
                }
            }
        }
        else if(!Found1)
            printf(" ! Invalid User id...\n");
	} 
}

void bookret()
{
int mid,i,Found1=0,Found2=0,Found3=0,flag=0;char retbookname[25],retauthorname[25];
char std_type[25] = "Student";
    temp1=librecord;temp2=membrrecord;
    printf("\nEnter The userid of the Member :");
        scanf("%d",&mid);
	if((membrrecord=fopen("membrrecord.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(membrrecord)&& Found1==0)
        {
            fscanf(membrrecord,"%d %s %s %s %d",&membr.mid,membr.mname,membr.department,membr.type,&membr.availibcard);
            if(mid==membr.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(membr.availibcard>=250)
            {
                printf(" ! Error...\n");
            }
            else
            {    printf("\nEnter The Name of book :");
                scanf("%s",retbookname);
                printf("\nEnter The Name of Author :");
                scanf("%s",retauthorname);
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    printf(" ! The file is empty\n\n");
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.quantity,&book.issuenum);
                        if(strcmp(retbookname,book.bname)==0 && strcmp(retauthorname,book.author)==0)
                        Found2=1;
                    }
                    if(Found2)
                    {
                        if(book.issuenum == 0)
                        {
                            printf(" ! Error:Book already in stock...\n");
                        }
                        else
                        {   
                           
                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("membrrecord.txt","a+"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %s %d  ",&membr.mid,membr.mname,membr.department,membr.type,&membr.availibcard);
                                    if(mid==membr.mid)
                                    {
                                        membr.availibcard++;
                                        fprintf(fp2,"\n %d\t\t%s\t\t%s\t\t%s\t\t%d\t",membr.mid,membr.mname,membr.department,membr.type,    membr.availibcard);
                                    }
                                    else{
                                        fprintf(fp2,"\n %d\t\t%s\t\t%s\t\t%s\t\t%d\t",membr.mid,membr.mname,membr.department,membr.type,membr.availibcard);}
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);
                            fclose(membrrecord);
                            remove("membrrecord.txt");
                            rename("fp2.txt","membrrecord.txt");

                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &book.bid,book.bname,book.author,&book.quantity,&book.issuenum);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(retbookname,book.bname)!=0)
                                    {
                                        fprintf(fp1,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d   \t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
                                    }
                                    else
                                    {
                                    	if(strcmp(retauthorname,book.author)!=0){
                                    		 fprintf(fp1,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d\t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
										}
										else{
											book.quantity++;
											book.issuenum--;
										    fprintf(fp1,"\n%d\t\t%s\t\t%s\t\t%d\t\t%d\t",book.bid,book.bname,book.author,book.quantity,book.issuenum);
											membrrecord = fopen("membrrecord.txt","r");
											while(!feof(membrrecord) && Found3==0){
											 	fscanf(membrrecord,"%d %s %s %s %d",&membr.mid,membr.mname,membr.department,membr.type,&membr.availibcard);
											 	if(membr.mid == mid){
											 		if(strcmp(membr.type,std_type)==0)
											                 Found3=1;									               
									        	}
									        }fclose(membrrecord);
									        if(Found3){
											                
									        		check_validity(mid,retbookname,retauthorname);
												}										
										}
                                    }    
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            
                            printf("('') Book Successfully Returned...\n");
                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");
                           
                        }               
                    }
                    else if(!Found2)
                        printf("! There is no such Book...\n");               
                }
            }
        }
        else if(!Found1)
            printf("! Invalid User id...\n");
    }  
}


int valid_date(int day, int mon, int year)    
{
    int is_valid = 1, is_leap = 0;

    if (year >= 1800 && year <= 9999) 
    {

        //  check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
        {
            is_leap = 1;
        }

        // check whether mon is between 1 and 12
        if(mon >= 1 && mon <= 12)
        {
            // check for days in feb
            if (mon == 2)
            {
                if (is_leap && day == 29) 
                {
                    is_valid = 1;
                }
                else if(day > 28) 
                {
                    is_valid = 0;
                }
            }

            // check for days in April, June, September and November
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11) 
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }

            // check for days in rest of the months 
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if(day > 31)
            {            
                is_valid = 0;
            }        
        }

        else
        {
            is_valid = 0;
        }

    }
    else
    {
        is_valid = 0;
    }

    return is_valid;

}

void check_validity(int mid,char bname[25],char author[25])
{
	
	int day1, mon1, year1,day2, mon2, year2,day_diff, mon_diff, year_diff,Found5=0;
	if((issuerecord=fopen("issuerecord.txt","r"))==NULL){
		printf("\t\t\t.......! The File is Empty......");
	}
	else{
    fp3=fopen("fp3.txt","w");
	if((temp3=fopen("issuerecord.txt","r"))==NULL)
	       printf("  ! The file is empty...\n\n");
    else
		 {
		do
		{
	 		fscanf(temp3,"%d %s %s %d/%d/%d",&issue.mnum,issue.bookname,issue.bookauthor,&issue.day1,&issue.mon1,&issue.year1);
        if(issue.mnum != mid || strcmp(bname,issue.bookname)!=0 || strcmp(author,issue.bookauthor)!=0)
			{
				Found5=0;
				fprintf(fp3,"\n%d\t\t%s\t\t%s\t\t%d/%d/%d",issue.mnum,issue.bookname,issue.bookauthor,issue.day1,issue.mon1,issue.year1);	
		}
		else{
			Found5=1;
		}
		if(Found5){
				day1 = issue.day1;
				mon1 = issue.mon1;
	     		year1 = issue.year1;
				printf("\nEnter return date (DD/MM/YYYY): \n");
				 scanf("%d/%d/%d", &day2, &mon2, &year2);		 
              if(!valid_date(day2, mon2, year2))
                   {
                       printf("Given date is invalid.\n");
                        exit(0);
                             }       
       if(day2 < day1)
             {      
               // borrow days from february
        if (mon2 == 3)
         {
                   //  check whether year is a leap year
                if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0)) 
                {
                            day2 += 29;
                   }
 
                else
                     {
                           day2 += 28;
                               }                        
                }

                          // borrow days from April or June or September or November
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12) 
                     {
                     day2 += 30; 
                    }

           // borrow days from Jan or Mar or May or July or Aug or Oct or Dec
        else
          {
          day2 += 31;
              }
 
      mon2 = mon2 - 1;
    }

     if (mon2 < mon1)
          {
          mon2 += 12;
          year2 -= 1;
        }       

    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
     year_diff = year2 - year1;
    
        if (year_diff>0){
             printf("Your book has been Overdue .....\nYou are to pay a fine of Rs.%d .\n",(720*year_diff)+(60*mon_diff)+(2*day_diff));
			               	}
	    else if(year_diff==0 && mon_diff>0){
			 printf("Your book has been Overdue .....\nYou are to pay a fine of Rs.%d .\n",60*mon_diff);
							            	}
		else{
        		printf("...................................\n");
						            	}
	     issue.mnum = 0;
			}		
						}while(!feof(temp3));
				}
			}
			fclose(issuerecord);
		 fclose(temp3);
         fclose(fp3);
        remove("issuerecord.txt");
        rename("fp3.txt","issuerecord.txt");
		 }	
		 

void Exit()
{
  exit(0);
}

