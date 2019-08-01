/*
	@author : Keshav Kabra
*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define N 30
FILE *fp;

struct library{
	int accno,flag;
	float price;
	char title[30],author[25];
};
struct library l[N];

void show_list(struct library libr)
{
	printf("Acession no = %d\nPrice = %f\nTitle = %s\n",libr.accno,libr.price,libr.title);
	printf("Author = %s\n",libr.author);
	if(libr.flag==1)
		printf("Book is issued !\n");
	else
		printf("Book is not issued !\n");

	printf("\n");
}

void sort_file()
{
	struct library lib[N]={0},L;
	int i=0,j,num=0;
	char ch;
	
	/* Entire data of file copied in variable LIB */
	while((ch=fgetc(fp))!=EOF)
	{
		fseek(fp,-1,SEEK_CUR);
		fscanf(fp,"%d\t%f\t",&lib[i].accno,&lib[i].price);
		fgets(lib[i].title,29,fp);
		fseek(fp,3,SEEK_CUR);
		fgets(lib[i].author,24,fp);
		fscanf(fp,"\t%d",&lib[i].flag);
		fseek(fp,2,SEEK_CUR);
		
		i++;
		num=i;
	}
	
	/* sorting to data */
	for(i=0;i<num;i++)
	{
		for(j=i+1;j<num;j++)
		{
			if(lib[i].accno>lib[j].accno)
			{
				L=lib[i];
				lib[i]=lib[j];
				lib[j]=L;
			}
		}
	}
	
	for(i=0;i<num;i++)
	{
		printf("Acession no = %d\nPrice = %f\nTitle = %s\n",lib[i].accno,lib[i].price,lib[i].title);
		printf("Author = %s\n",lib[i].author);
		if(lib[i].flag==1)
			printf("Book is issued !\n");
		else
			printf("Book is not issued !\n");

		printf("\n");
	}
}

void book_count()
{
	int num=0;
	char ch;
	while((ch=fgetc(fp))!=EOF)
	{
		num++;
		fseek(fp,74,SEEK_CUR);
	}
	printf("\nTotal books in library = %d\n",num);
}

void print_nam_accono()
{
	int num,acc_file;
	char ch,b[30]={0};
	printf("\nEnter the Acession number of the book :\n");
	scanf("%d",&num);
	
	char str_user[7];
	char str_file[7];
	sprintf(str_user, "%d", num);
	
	while((ch=fgetc(fp))!=EOF)
	{
		fseek(fp,-1,SEEK_CUR);
		fscanf(fp,"%6d",&acc_file);
		fseek(fp,9,SEEK_CUR);
		fgets(b,30,fp);
		sprintf(str_file, "%d", acc_file);
		if(strcmp(str_user, str_file)==0)
		{
			printf("\nBook with Acession number %d is : ",num);
			strupr(b);
			puts(b);
		}
		fseek(fp,32,SEEK_CUR);
	}
}

void print_nam_auth()
{
	char ch,a[25]={0},b[25]={0},c[31]={0};
	int i=1,x;
	printf("\nEnter the author name :\n");
	fflush(stdin);
	gets(a);
	while(strlen(a) != 23)
		strcat(a, " ");
	
	printf("\nBook(s) by Author ");
	puts(a);
	printf("\n");
	
	while((ch=fgetc(fp))!=EOF)
	{
		fseek(fp,-1,SEEK_CUR);
		
		fseek(fp,15,SEEK_CUR);
		fgets(c,30,fp);
		
		fseek(fp,2,SEEK_CUR);
		fgets(b,24,fp);
		
		x=strcmpi(b,a);
		if(x==0)
		{
			printf("%d.  ",i++);
			puts(c);
		}
		
		fseek(fp,6,SEEK_CUR);
	}
}

void display()
{
	struct library L;
	char ch;
	while((ch=fgetc(fp))!=EOF)
	{
		fflush(stdin);
		fseek(fp,-1,SEEK_CUR);	//set pointer to its original position (disturbed by 'ch')
		fscanf(fp,"%d\t%f\t",&L.accno,&L.price);
		fgets(L.title,29,fp);
		fseek(fp,3,SEEK_CUR);
		fgets(L.author,24,fp);
		fscanf(fp,"\t%d",&L.flag);
		fseek(fp,2,SEEK_CUR);
		
		show_list(L);
		
	}
}
void show_feature()
{
	printf("\n\nMenu Operation are :\n\n");
	printf("  1.Add book information\n  2.Display book information\n");
	printf("  3.List all books of given author\n");
	printf("  4.List the title of specified book (according to Acession no.)\n");
	printf("  5.List the count of books in library\n");
	printf("  6.List the books in order of their Accession number\n  7.Exit\n");
}
void show_info()
{
	printf("Enter :\n 1.Acession Number\n 2.Price\n 3.Title of book\n");
	printf(" 4.Name of Author\n 5.Book issued or not (1 for issued)\n\n");
}
void getb(int index)
{
	int i=0,len;
	printf("\n");
	scanf("%d%f",&l[index].accno,&l[index].price);
	fflush(stdin);
	gets(l[index].title);
	fflush(stdin);
	gets(l[index].author);
	fflush(stdin);
	scanf("%d",&l[index].flag);
	
	/* To write formatted info in the file */
	fprintf(fp,"%6d\t%7.2f\t%s",l[index].accno,l[index].price,l[index].title);
	len=strlen(l[index].title);
	while((30-len-i)>=0)
	{
		fprintf(fp,"%c",' ');
		i++;
	}
	i=0;
	fprintf(fp,"%s",l[index].author);
	len=strlen(l[index].author);
	while((25-len-i)>=0)
	{
		fprintf(fp,"%c",' ');
		i++;
	}
	fprintf(fp,"%d\n",l[index].flag);
}
int getbook()
{
	int i,n=0;
	for(i=0;i<3;i++)
	{
		getb(i);
		n++;
	}
	return(n);
}
int main()
{
	int optn,num=0;
	printf("Enter the process you want to do with existing file :\n");
	printf("1.Write from start  2.Apppend  3.Read\n");
	scanf("%d",&optn);
	if(optn==1)
	{
		fp=fopen("Library.txt","w");
		show_info();
		printf("Enter information of 3 books :\n");
		num=getbook();
		fclose(fp);
	}
	else if(optn==2)
		fp=fopen("Library.txt","a");
	else if(optn==3)
		fp=fopen("Library.txt","r");
	if(fp==NULL)
	{
		printf("Program can not run due to an Error !\n");
		exit(1);
	}
	system("cls");
	
	
	while(1)
	{
		system("cls");
		show_feature();
		printf("\nEnter the operation you want to perform :\n");
		scanf("%d",&optn);
		switch(optn)
		{
			case(1):
				fp=fopen("Library.txt","a");
				printf("\nEnter the information of book %d :\n",num+1);
				show_info();
				getb(num);
				num++;
				printf("\nBook has been successfully added to the list !\n");
				fclose(fp);
				break;
			case(2):
				fp=fopen("Library.txt","r");
				display();
				printf("\nPress any key to continue...");
				getch();
				fclose(fp);
				break;
			case(3):
				fp=fopen("Library.txt","r");
				print_nam_auth();
				printf("\nPress any key to continue...");
				getch();
				fclose(fp);
				break;
			case(4):
				fp=fopen("Library.txt","r");
				print_nam_accono();
				printf("\nPress any key to continue...");
				getch();
				fclose(fp);
				break;
			case(5):
				fp=fopen("Library.txt","r");
				book_count();
				printf("\nPress any key to continue...");
				getch();
				fclose(fp);
				break;
			case(6):
				fp=fopen("Library.txt","r");
				sort_file();
				printf("\nPress any key to continue...");
				getch();
				fclose(fp);
				break;
			case(7):
					printf("\nHope you liked the service !\n\n");
					printf("********** Program designed by - KESHAV KABRA **********\n");
					printf("\nPress any key to end process...");
					getch();
					exit(0);
			default:
				printf("\nInvalid key entered !\n");
				getch();
		}
	}
	
	fclose(fp);
	return 0;
}
