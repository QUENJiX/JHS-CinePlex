#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Movie{
    char title[200];
    char genre[100];
};

struct Showtime{
    char time[100];
    int price;
    int available_Seats;
};

struct Ticket {
    char movie_Title[200];
    char show_Time[50];
    int ticket_Count;
    int total_Amount;
};

void Main_Menue();
void View_Avaliable_Movies();
void Purchase_Tickets();
//void View_My_Purchases();
void Movie_Information();
void Write_Movie_to_File();
void Read_Movie_Information();
void Press_Enter_to_Continue();

struct Movie m[100];
struct Showtime s[100];

int main(){
    Read_Movie_Information();

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

void Movie_Information(){

    strcpy(m[0].title, "Heridetary");
    strcpy(m[0].genre, "Horror");
    strcpy(s[0].time,  "11:00 PM - 01:20 PM");
    s[0].price = 200;
    s[0].available_Seats = 50;

    strcpy(m[1].title, "The Notebook");
    strcpy(m[1].genre, "Romantic");
    strcpy(s[1].time,  "08:30 PM - 10:10 PM");
    s[1].price = 200;
    s[1].available_Seats = 0;

    strcpy(m[2].title, "Boss Baby");
    strcpy(m[2].genre, "Family / Comedy");
    strcpy(s[2].time,  "03:00 PM - 05:00 PM");
    s[2].price = 200;
    s[2].available_Seats = 50;

    strcpy(m[3].title, "Harry Potter and the Goblet of Fire");
    strcpy(m[3].genre, "Fantasy");
    strcpy(s[3].time,  "05:00 PM - 08:00 PM");
    s[3].price = 500;
    s[3].available_Seats = 0;

    strcpy(m[4].title, "Chander Pahar");
    strcpy(m[4].genre, "Adventure");
    strcpy(s[4].time,  "01:00 PM - 03:30 PM");
    s[4].price = 500;
    s[4].available_Seats = 50;

}

void Read_Movie_Information(){
    FILE *file = fopen("movie_list.txt", "r");

    if (file == NULL) {
        Movie_Information();
        Write_Movie_to_File();
    }else {
        for(int i = 0; i < 5; i++){
            fscanf(file, "%[^\n]", m[i].title);
            fscanf(file, "%[^\n]", m[i].genre);
            fscanf(file, "%s %d %d", s[i].time, s[i].price, s[i].available_Seats);
        }
        fclose(file);
    }
}

void Write_Movie_to_File(){
    FILE *file = fopen("movie_list.txt", "w");

    if(file == NULL){
        printf("Error!\n");
        return;
    }
    for(int i = 0; i < 5; i++){
        fprintf(file, "%s\n", m[i].title);
        fprintf(file, "%s\n", m[i].genre);
        fprintf(file, "%s\n", s[i].time); 
        fprintf(file, "%d\n", s[i].price); 
        fprintf(file, "%d\n", s[i].available_Seats); 
    }
    fclose(file);
}

void View_Avaliable_Movies(){
    system("cls");
    printf("\nAvaialbe Movies\n");

    for(int i = 0; i < 5; i++){
        printf("Movie %d: %s (%s)\n", i+1, m[i].title, m[i].genre);
        printf("\tShowtimes: %s\n", s[i].time);
        printf("\tPrice: %d\n", s[i].price);
        printf("\tSeats Available: %d\n\n", s[i].available_Seats);
    }
    Press_Enter_to_Continue();
}

void Purchase_Tickets(){
    system("cls");
    int movie_choice, ticket_count;
    
    printf("Purchase Tickets\n");

    for(int i = 0; i < 5; i++){
        printf("%d. %s (%s)\n", i+1, m[i].title, m[i].genre);
    }
    printf("Enter movie number: ");
    scanf("%d", &movie_choice);
    while (getchar() != '\n');

    //Edge case

    int movie_position = movie_choice - 1;

    printf("\nSelected Movie: %s\n", m[movie_position].title);
    printf("\nShowtime: %s\n", s[movie_position].time);
    printf("\nPrice: %d\n", s[movie_position].price);
    printf("\nAvailable Seats: %d\n", s[movie_position].available_Seats);

    printf("Enter number of tickets to buy: ");
    scanf("%d", &ticket_count);
    while (getchar() != '\n');

    //Edge case

    int total_price = ticket_count * s[movie_position].price; 

    printf("\n\nPurchase Successful\n");
    printf("Movie: %s", m[movie_position].title);
    printf("Tickets: %d", ticket_count);
    printf("Total Price: %d", total_price);

    s[movie_position].available_Seats -= ticket_count;
    //continue tomorrow
    
}

void Press_Enter_to_Continue(){
    printf("\nPress Enter to Continue...");
    while (getchar() != '\n');
}

