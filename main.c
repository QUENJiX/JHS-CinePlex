#include <stdio.h>

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
    char show_Time[100];
    int ticket_Count;
    float total_Amount;
};

void Main_Menue();
void View_Avaliable_Movies();
void Purchase_Tickets();
void View_My_Purchases();

int main(){

    Main_Menue();
    int choice;

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice){
        case 1:
            View_Avaliable_Movies();
            break;
        case 2: 
            Purchase_Tickets();
            break;
        case 3: 
            View_My_Purchases();
            break;
        case 4:
            printf("Thanks for choosing JHS-Cineplex!\n");
            return 0;
        default:
            printf("Invalid Choice. Please choose options from 1-4 only.\n");
            break;
    }

    return 0;

}

void Main_Menue(){
    printf("\n\nWelcome to JHS-CinePlex\n\n");
    printf("1. View Avalaible Movies\n");
    printf("2. Purchase Tickets\n");
    printf("3. View My Purchases\n");
    printf("4. Exit\n");
}

