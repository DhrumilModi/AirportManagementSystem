#include<string.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

// For loop macros
#define FOR(i,a,b)      for(i=a;i<b;i++)
#define RFOR(i,a,b)     for(i=b-1;i>=0;i--)

// scanf macros
#define GI(x)           scanf("%d",&x);
#define GS(x)           scanf("%s",x);
#define GSLN(x)         gets(x);

// macros for airplane status.
#define NOT_AVAILABLE   0
#define SECURITY_CHECK  1
#define BOARDING        2
#define DEPARTED        3
#define DELAYED         4
#define CANCELLED      -1

//macros for user status.
#define CHECKED_IN            1
#define CANCELLED            -1

// structure for time.
typedef struct
{
      int hour;
      int mins;
} Time;

// structure for airplane
typedef struct a
{
      char company[100];
      char type[100];
      char number[100];
      Time boarding_time;
      Time departure_time;
      char destination[100];
      int status;
      int terminal;
      struct a* link;
} airplane;

// structure for passenger
typedef struct
{
      char first_name[100];
      char second_name[100];
      char flight_no[100];
      int status;
      double luggage;
} passenger;

airplane* flights = NULL; // linked list.
//int pid=0;
passenger*  users = NULL; // dynamic array.
int max_capacity = 1,capacity = 1;

// Function related to airplanes at the airport.
void add_airplane();
airplane* create_node();
void change_status_airplane();
int valid_fid(char[]);
void insert_flight(airplane*);
void display_airplanes();
void remove_airplanes();
void change_terminal();
void change_time();
void airline_operation(int);
void display_flight();

// Functions related to passenger.
void add_passenger();
void change_passenger_status();
void passenger_details();
void passenger_operation(int);
int pid_assign();
int check_pid(int);
void upgrade_max_capacity();

// Other functions.
void show_menu(int);
void main_menu();
void airplane_menu();
void passenger_menu();
int choice();

// Main Driver Function
int main()
{
      users = (passenger*) malloc(sizeof(passenger));
      while(1) show_menu(0);
      return 0;
}

// Shows Menu
void show_menu(int id)
{
      switch(id)
      {
	    case 0 : main_menu();return;
	    case 1 : airplane_menu();break;
	    case 2 : passenger_menu();break;
	    case 3 : exit(0);
	    default : printf("Wrong choice!\n");main_menu();return;
      }
      return;
}

void main_menu()
{

      int k;
      printf("\n***********MAIN MENU***************");
      printf("\n1. Flight Related Menu (Search, Display, Add, Change Existing)");
      printf("\n2. Passenger Related Menu (Add, Display, Change Status)");
      printf("\n3. Exit");
      printf("\nMain> ");

      k = choice();
      show_menu(k);
}

void airplane_menu()
{
      int k=0;

      printf("\n********FLIGHT MENU************\n");
      printf("1. Display Current Flights\n");
      printf("2. Add New Flight\n");
      printf("3. Change Flight Status\n");
      printf("4. Change Flight Timing\n");
      printf("5. Change Flight Terminal\n");
      printf("6. Remove Flight\n");
      printf("Press any other digit to go back...");
      printf("\nFlight> ");

      k = choice();
      if(k>=1 && k<=6)
      {
	    airline_operation(k);
	    show_menu(1);
      }
}

void passenger_menu()
{
      int k=0;

      printf("\n********PASSENGER MENU************\n");
      printf("1. Display Passenger Details\n");
      printf("2. Add New Passenger\n");
      printf("3. Change Passenger Status\n");
      printf("Press any other digit to go back...");
      printf("\nPassenger> ");

      k = choice();
      if(k>=1 && k<=3)
      {
	    passenger_operation(k);
	    show_menu(2);
      }
}

int choice()
{
      int k;
      GI(k);
      return k;
}

void airline_operation(int choice)
{
      switch(choice)
      {
	    case 1: display_airplanes(); break;
	    case 2: add_airplane(); break;
	    case 3: change_status_airplane(); break;
	    case 4: change_time(); break;
	    case 5: change_terminal(); break;
	    case 6: remove_airplanes(); break;
      }
}

airplane* create_node()
{
      airplane* newptr = (airplane*) malloc(sizeof(airplane));
      newptr->link = NULL;
      return newptr;
}

void insert_flight(airplane* ptr)
{
      airplane* i;
      if(flights == NULL)
      {
	    flights = ptr;
	    return ;
      }
      i = flights;
      while(i->link != NULL) i = i->link;
      i->link = ptr;
}

void add_airplane()
{
      FILE *fp;
      char ch;
      airplane* newptr = create_node();
      struct a ar;
      fp=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","a");

      printf("Enter company name : ");

      scanf("%c",&ch);
      gets(newptr->company);
      printf("Enter Airbus type : ");
      gets(newptr->type);
      printf("Enter Flight ID : ");
      gets(newptr->number);
      printf("Enter Destination : ");
      gets(newptr->destination);
      printf("Enter Boarding Time in HH:MM format : ");
      scanf("%d:%d",&newptr->boarding_time.hour,&newptr->boarding_time.mins);
      printf("Enter Departure Time in HH:MM format : ");
      scanf("%d:%d",&newptr->departure_time.hour,&newptr->departure_time.mins);

      newptr->status = 0;
      newptr->terminal = -1;

      fprintf(fp,"%s %s %s %s %d %d %d %d %d %d \n",newptr->company,newptr->type,newptr->number,newptr->destination,newptr->boarding_time.hour,newptr->boarding_time.mins,newptr->departure_time.hour,newptr->departure_time.mins,0,-1);

      insert_flight(newptr);
      fclose(fp);
      printf("Flight Has Been Added! You can alter the status and terminal from the flight menu!\n");
}



void remove_airplanes()
{
      char abc[100],tid[100];
      int avl=-1;
      FILE *fao,*fat;
      airplane* srch;
      airplane* a = create_node();
      printf("\n********Change Flight Terminal*************\n");

      printf("Enter Flight ID : ");
      scanf("%s",abc);
      avl = valid_fid(abc);

      if(avl == 0)
	  {
		  printf("Incorrect Flight Id\n");
		printf("\t\t\t\t\tFlight Id %s is not available in database....",abc);
	  }
      else
      {



			fao=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","r");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","w");

			while(fscanf(fao, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
			{
						 strcpy(tid,a->number);
						 if(!(strcmp(tid,abc)))
						 {

									   printf("Flight %s is deleted successfully.. ",tid);

						 }
						 else
						 {
								fprintf(fat,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);
						 }
				}
		}

		fclose(fao);
		fclose(fat);

			fao=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","w");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","r");
			while(fscanf(fat, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
			{

					fprintf(fao,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);

			}
				fclose(fao);
				fclose(fat);
	 }

void change_time()
{
	  char abc[100],tid[100];
      int hr=0,mm=0,ch=0,avl=-1;
      FILE *fao,*fat;
      airplane* srch;
      airplane* a = create_node();
      printf("\n********Change Flight Timing*************\n");
      printf("Enter Flight ID : ");
      scanf("%s",abc);
      avl = valid_fid(abc);

      if(avl == 0)
	  {
		  printf("Incorrect Flight Id\n");
		printf("\t\t\t\t\tFlight Id %s is not available in database....",abc);
	  }
      else
      {



			fao=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","r");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","w");

			while(fscanf(fao, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
			{
						 strcpy(tid,a->number);
						 if(!(strcmp(tid,abc)))
						 {
							 printf("Enter 1 for Boarding Time..\n");
							 printf("Enter 2 for Departure Time..\n");
							 printf("Enter 3 for Main Menu\n");
							ch=choice();
								switch(ch)
								{

									case 1:
													printf("New Boarding Time> Hours : ");
												hr = choice();
												    printf("New Boarding Time> Minutes : ");
												    mm = choice();
												    fprintf(fat,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,hr,mm,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);
													break;
									case 2:
													printf("New Departure Time> Hours : ");
												hr = choice();
												    printf("New Departure Time> Minutes : ");
												    mm = choice();
												    fprintf(fat,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,hr,mm,a->status,a->terminal);
													break;
									case 3:
													return;
									default:
													printf("Invalid Choice");
								 }


						 }
						 else
						 {
								fprintf(fat,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);
						 }
				}
		}

		fclose(fao);
		fclose(fat);

			fao=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","w");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","r");
			while(fscanf(fat, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
			{

					fprintf(fao,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);

			}
				fclose(fao);
				fclose(fat);
	}






void change_terminal()
{

	  char abc[100],tid[100];
      int k=0,avl=-1;
      FILE *fao,*fat;
      airplane* srch;
      airplane* a = create_node();
      printf("\n********Change Flight Terminal*************\n");

      printf("Enter Flight ID : ");
      scanf("%s",abc);
      avl = valid_fid(abc);

      if(avl == 0)
	  {
		  printf("Incorrect Flight Id\n");
		printf("\t\t\t\t\tFlight Id %s is not available in database....",abc);
	  }
      else
      {



			fao=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","r");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","w");

			while(fscanf(fao, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
			{
						 strcpy(tid,a->number);
						 if(!(strcmp(tid,abc)))
						 {

									   printf("Enter Terminal Number : ");
									   k = choice();
									   fprintf(fat,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,k);

						 }
						 else
						 {
								fprintf(fat,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);
						 }
				}
		}

		fclose(fao);
		fclose(fat);

			fao=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","w");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","r");
			while(fscanf(fat, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
			{

					fprintf(fao,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);

			}
				fclose(fao);
				fclose(fat);

}


void change_status_airplane()
{
	  char abc[100],tid[100];
      int k=0,avl=-1;
      FILE *fao,*fat;
      airplane* srch;
      airplane* a = create_node();
      printf("\n********Change Flight Status*************\n");
      printf("Enter Flight ID : ");
      scanf("%s",abc);
      avl = valid_fid(abc);

      if(avl == 0)
	  {
		  printf("Incorrect Flight Id\n");
		printf("\t\t\t\t\tFlight Id %s is not available in database....",abc);
	  }
      else
      {
	    printf("1. Security Checking\n2. Boarding\n3. Departed\n4. Delayed\n5. Cancelled\n6.Not available\nAny other digit to go back..\nStatus> ");

	    k = choice();
	    if(k>=1 && k<=6)
	    {
		  if(k == 5) k = -1;
		  else if(k == 6) k = 0;

			fao=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","r");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","w");

			while(fscanf(fao, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
			{
						 strcpy(tid,a->number);
						 if(!(strcmp(tid,abc)))
						 {
								fprintf(fat,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,k,a->terminal);

						 }
						 else
						 {
								fprintf(fat,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);
						 }
			}
		  }

		fclose(fao);
		fclose(fat);

			fao=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","w");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","r");
			while(fscanf(fat, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
			{

					fprintf(fao,"%s %s %s %s %d %d %d %d %d %d \n",a->company,a->type,a->number,a->destination,a->boarding_time.hour,a->boarding_time.mins,a->departure_time.hour,a->departure_time.mins,a->status,a->terminal);

			}
				fclose(fao);
				fclose(fat);
		}

   }

int valid_fid(char id[])
{
	airplane* a = create_node();
	FILE *fp;
	fp=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","r");

		while( fscanf(fp, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
	   {


		if(!strcmp(id,a->number))
		{
			fclose(fp);
			return 1;
		 }
	  }
	fclose(fp);
	return 0;

}
airplane* search_flight(char num[])
{
      airplane* temp = flights;
      while(temp != NULL)
      {
	    if(!strcmp(temp->number,num)) break;
	    temp = temp->link;
      }
      return temp;
}

void display_flight()
{

	FILE *fp;
	airplane* a = create_node();
	fp=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","r");

//	  if(fp==NULL)
//      {
//      	printf("\nERROR");
//	  }
//	  else
//	  {
//	  	printf("\nSUCCESS");
//	  }
		while( fscanf(fp, "%s %s %s %s %d %d %d %d %d %d\n", a->company,a->type,a->number,a->destination,&a->boarding_time.hour,&a->boarding_time.mins,&a->departure_time.hour,&a->departure_time.mins,&a->status,&a->terminal) != EOF )
	   {

      printf("\n");
      printf("Company : %s\nID : %s\nDeparture : %02d:%02d\nDestination : %s\n",a->company,a->number,a->departure_time.hour,a->departure_time.mins,a->destination);
     printf("Status : ");
      switch(a->status)
      {
	    case -1:printf("CANCEL");break;
	    case 0: printf("NA");break;
	    case 1: printf("SEC CHK");break;
	    case 2: printf("BOARD");break;
	    case 3: printf("DEPART");break;
	    case 4: printf("DELAY");break;
      }
      printf("\nTerminal : %d\n",a->terminal);
		}
}
void display_air()
{
	FILE *fp;
	airplane* newptr = create_node();
	fp=fopen("C:/TURBOC3/AirportManagementSystem/air.txt","r");

	  if(fp==NULL)
      {
	printf("\nERROR");
	  }
	  else
	  {
		printf("\nSUCCESS");
	  }

	while( fscanf(fp, "%s %s %s %s %d %d %d %d %d %d\n", newptr->company,newptr->type,newptr->number,newptr->destination,&newptr->boarding_time.hour,&newptr->boarding_time.mins,&newptr->departure_time.hour,&newptr->departure_time.mins,&newptr->status,&newptr->terminal) != EOF )
    {
       printf("%s %s %s %s %d:%d %d:%d %d %d \n",newptr->company,newptr->type,newptr->number,newptr->destination,newptr->boarding_time.hour,newptr->boarding_time.mins,newptr->departure_time.hour,newptr->departure_time.mins,0,-1);

    }
}
	void display_airplanes()
{
//     airplane* start;
//
//      printf("\n*************FLIGHTS*************\n");
//
//      if(flights == NULL)
//      {
//	    printf("No flights on display yet!\n");
//	    return;
//      }
//      start = flights;
//      while(start!=NULL)
//      {
//	    display_flight(start);
//	    start = start->link;
//      }
		display_flight();
}

void passenger_operation(int choice)
{
      switch(choice)
      {
	    case 1: passenger_details(); break;
	    case 2: add_passenger(); break;
	    case 3: change_passenger_status();
				break;
      }
}


int pid_assign()
{
	FILE *fp;
    passenger p1;
	int pid=0,t=0;
	fp=fopen("C:/TURBOC3/AirportManagementSystem/passengers.txt","r");

	  if(fp==NULL)
      {
	printf("\nERROR");
	return -1;
	  }
	  else
	  {
		printf("\nSUCCESS");
			while(fscanf(fp,"%d %s %s %s %lf %d",&pid,p1.first_name,p1.second_name,p1.flight_no,&p1.luggage,&p1.status) != EOF )
		    {
			t=pid;
		    }
		}
		fclose(fp);
		return ++t;
}

void add_passenger()
{
      char abc[100],tid[100];
      int avl=-1,p,pid=0;
	  passenger p1;
	  FILE *fp;
	  fp=fopen("C:/TURBOC3/AirportManagementSystem/passengers.txt","a");

	  printf("\n********Add Passenger*************\n");

					printf("Passenger Details> ");
		      pid=pid_assign();
				  printf("Enter First Name : ");
				  scanf("%s",p1.first_name);
			      printf("Passenger Details> ");
			      printf("Enter Last Name : ");
			      scanf("%s",p1.second_name);
			      printf("Passenger Details> ");
			      printf("Enter Flight ID : ");
			  scanf("%s",p1.flight_no);
			  avl = valid_fid(p1.flight_no);
				  printf("Passenger Details> ");
			      printf("Enter Luggage Weight : ");
			      scanf("%lf",&p1.luggage);
			      p1.status = CHECKED_IN;
				  if(avl==0)
				  {
						 printf("Wrong Flight Number! Re fill the data correctly\n");

				  }
				   else
			       {
						fprintf(fp,"\n%d %s %s %s %lf %d",pid,p1.first_name,p1.second_name,p1.flight_no,p1.luggage,p1.status);
					}
					fclose(fp);
					return;
      }

int check_pid(int id)
{
	FILE *fp;
    passenger p1;
	int pid=0,t=0;
	fp=fopen("C:\\TURBOC3\\AirportManagementSystem\\passengers.txt","r");

	  if(fp==NULL)
      {
	printf("\nERROR");
	return 0;
	  }
	  else
	  {
			while(fscanf(fp,"%d %s %s %s %lf %d",&pid,p1.first_name,p1.second_name,p1.flight_no,&p1.luggage,&p1.status) != EOF )
		    {
			t=pid;
		    }
		}
		if(t>=id && id>=0)
		{
			return 1;
		}
		fclose(fp);
		return 0;

}
void passenger_details()
{
      int k=0,x=0;
	  FILE *fp;
      passenger p1;
	  int pid=0;
	  fp=fopen("C:\\TURBOC3\\AirportManagementSystem\\passengers.txt","r");


      printf("\n*******Passenger Details*********\n");
      printf("Enter Passenger ID : ");
      k = choice();
      if(!check_pid(k))
      {
	    printf("Invalid choice!\n");
	    return;
      }
      else
      {
		printf("\nSUCCESS");

		while(fscanf(fp,"%d %s %s %s %lf %d",&pid,p1.first_name,p1.second_name,p1.flight_no,&p1.luggage,&p1.status) != EOF )
		{
			 if(k==pid)
			 {
			  
			  printf("Passenger Details.... \n");
		      printf("Name : %s %s\n",p1.first_name,p1.second_name);
		      printf("Flight : %s\n",p1.flight_no);
		      printf("Luggage : %.3lf\n",p1.luggage);
		      printf("Status : ");
		      x = p1.status;
		      if(x == CHECKED_IN) printf("Checked In");
		      else printf("Cancelled");
		      printf("\n");   		
			}
		}
	  }
    
}
void change_passenger_status()
{
	  int p=0;
	  int pid=0;
      passenger p1;    
	  int k=0;
      FILE *fao,*fat;
      printf("\n********Change Passenger Status*************\n");
      printf("Enter Passenger ID : ");
      p=choice();
      
	
      if(!check_pid(p))
	  {
		  printf("Incorrect Flight Id\n");
		printf("\t\t\t\t\tPassenger Id %d is not available in database....",p);
	  }
      else
      {
	   printf("1. Change status to Checked In\n2. Change status to cancelled\nAny Other Digit To Go back\nStatus>");
        k = choice();
	    if(k>=1 && k<=3)
	    {
		  if(k == 1) k=CHECKED_IN;
		  else if(k == 2) k=CANCELLED;
		  else {return; }
		  
		  	fao=fopen("C:/TURBOC3/AirportManagementSystem/passengers.txt","r");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","w");
			
			while(fscanf(fao,"%d %s %s %s %lf %d",&pid,p1.first_name,p1.second_name,p1.flight_no,&p1.luggage,&p1.status) != EOF )
 	   		{
						 
						 if(p==pid)	
						 {
								fprintf(fat,"\n%d %s %s %s %lf %d",pid,p1.first_name,p1.second_name,p1.flight_no,p1.luggage,k);						 
						 
						 }
						 else
						 {
								fprintf(fat,"\n%d %s %s %s %lf %d",pid,p1.first_name,p1.second_name,p1.flight_no,p1.luggage,p1.status);						 
						 }	
			}
		  }
	    
		fclose(fao);
		fclose(fat);
			
			fao=fopen("C:/TURBOC3/AirportManagementSystem/passengers.txt","w");
			fat=fopen("C:/TURBOC3/AirportManagementSystem/temp.txt","r");
			while(fscanf(fat,"%d %s %s %s %lf %d",&pid,p1.first_name,p1.second_name,p1.flight_no,&p1.luggage,&p1.status) != EOF )
 	   		{	
				
								fprintf(fao,"\n%d %s %s %s %lf %d",pid,p1.first_name,p1.second_name,p1.flight_no,p1.luggage,p1.status);						 
						
			}
				fclose(fao);
				fclose(fat);
		}
   
	  
	  
}

