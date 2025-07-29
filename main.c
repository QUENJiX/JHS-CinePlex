#include <stdio.h>
#include <stdlib.h>

struct Movie{
    char title[200];
    char genre[100];
};

struct Showtime{
    char time[100];
    float price;
    int available_Seats;
};

struct Ticket {
    char movie_Title[200];
    char show_Time[50];
    int ticket_Count;
    float total_Amount;
};

void Main_Menue();
void View_Avaliable_Movies();
//void Purchase_Tickets();
//void View_My_Purchases();
void Press_Enter_to_Continue();

int main(){

    int choice;
    while(1){
        system("cls");
        Main_Menue();

        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice){
            case 1:
                View_Avaliable_Movies();
                break;
            case 2: 
                //Purchase_Tickets();
                break;
            case 3: 
                //View_My_Purchases();
                break;
            case 4:
                printf("Thanks for choosing JHS-Cineplex!\n");
                return 0;
            default:
                printf("Invalid Choice. Please choose options from 1-4 only.\n");
                break;
        }
    }

    return 0;

}


void Main_Menue(){
    printf("\nWelcome to JHS-CinePlex\n");
    printf("1. View Avalaible Movies\n");
    printf("2. Purchase Tickets\n");
    printf("3. View My Purchases\n");
    printf("4. Exit\n");
}

void View_Avaliable_Movies(){
    system("cls");
    struct Movie m[100];
    struct Showtime s[100];
    printf("\nAvaialbe Movies\n");

    for(int i = 0; i < 5; i++){
        printf("Movie %d: %s (%s)\n", i+1, m[i].title, m[i].genre);
        printf("\tShowtimes:\n");
        printf("\t%s - Price: %f - Seats Available: %d\n", s[50].time, s->price, s->available_Seats);
    }
    
    Press_Enter_to_Continue();
}

void Press_Enter_to_Continue(){
    printf("\nPress Enter to Continue...");
    while (getchar() != '\n');
}

