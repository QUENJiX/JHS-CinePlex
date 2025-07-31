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
    int quantity;
    int total_Amount;
};

void Main_Menue();
void Movie_Information();
void Write_Movie_to_File();
void Read_Movie_Information();
void View_Avaliable_Movies();
void Write_User_Purchases();
void Read_User_Purchases();
void Purchase_Tickets();
void View_My_Purchases();
void Press_Enter_to_Continue();

struct Movie m[100];
struct Showtime s[100];
struct Ticket t[100];
int ticket_count = 0;


int main(){
    Read_Movie_Information();
    Read_User_Purchases();

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
                Purchase_Tickets();
                break;
            case 3: 
                View_My_Purchases();
                break;
            case 4:
                Write_Movie_to_File();
                Write_User_Purchases();
                printf("\nThanks for choosing JHS-Cineplex!\n");
                return 0;
            default:
                printf("\nInvalid Choice. Please choose options from 1-4 only.\n");
                Press_Enter_to_Continue();
                break;
        }
    }

    return 0;

}

void Main_Menue(){
    printf("\n==================================\n");
    printf("      Welcome to JHS-CinePlex");
    printf("\n==================================\n");
    printf("1. View Avalaible Movies\n");
    printf("2. Purchase Tickets\n");
    printf("3. View My Purchase History\n");
    printf("4. Save & Exit");
    printf("\n==================================\n");
}

void Movie_Information(){

    strcpy(m[0].title, "Heridetary"); 
    strcpy(m[0].genre, "Horror");
    strcpy(s[0].time,  "11:00 PM - 01:20 PM"); 
    s[0].price = 200; s[0].available_Seats = 45;

    strcpy(m[1].title, "The Notebook"); 
    strcpy(m[1].genre, "Romantic"); 
    strcpy(s[1].time,  "08:30 PM - 10:10 PM"); 
    s[1].price = 200; s[1].available_Seats = 0;

    strcpy(m[2].title, "Boss Baby"); 
    strcpy(m[2].genre, "Family / Comedy");
    strcpy(s[2].time,  "03:00 PM - 05:00 PM"); 
    s[2].price = 200; s[2].available_Seats = 35;

    strcpy(m[3].title, "Harry Potter and the Goblet of Fire"); 
    strcpy(m[3].genre, "Fantasy");
    strcpy(s[3].time,  "05:00 PM - 08:00 PM"); 
    s[3].price = 500; s[3].available_Seats = 0;

    strcpy(m[4].title, "Chander Pahar"); 
    strcpy(m[4].genre, "Adventure");
    strcpy(s[4].time,  "01:00 PM - 03:30 PM"); 
    s[4].price = 500; s[4].available_Seats = 50;

}

void Read_Movie_Information(){
    FILE *file = fopen("movie_list.txt", "r");

    if (file == NULL) {
        Movie_Information();
        Write_Movie_to_File();
    }else {
        for (int i = 0; i < 5; i++) {
            fscanf(file, "%[^\n]", m[i].title);
            fgetc(file); 
            fscanf(file, "%[^\n]", m[i].genre);
            fgetc(file); 
            fscanf(file, "%[^\n]", s[i].time);
            fgetc(file); 
            fscanf(file, "%d", &s[i].price);
            fgetc(file); 
            fscanf(file, "%d", &s[i].available_Seats);
            fgetc(file); 
        }
        fclose(file);
    }
}

void Write_Movie_to_File(){
    FILE *file = fopen("movie_list.txt", "w");

    if(file == NULL){
        printf("Error! Could not save movie data.\n");
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

void Read_User_Purchases(){
    FILE *file = fopen("tickets.txt", "r");

    if (file == NULL) {
        return;
    }else {
        ticket_count = 0;
        while (fscanf(file, "%[^\n]", t[ticket_count].movie_Title) != NULL) {
            fgetc(file); 
            fscanf(file, "%[^\n]", t[ticket_count].show_Time);
            fgetc(file); 
            fscanf(file, "%d", &t[ticket_count].quantity);
            fgetc(file); 
            fscanf(file, "%d", &t[ticket_count].total_Amount);
            fgetc(file); 
            ticket_count++;
        }
        fclose(file);
    }
}

void Write_User_Purchases(){
    FILE *file = fopen("movie_list.txt", "w");

    if (file == NULL) {
        printf("Error! Could not save purchase history\n");
        return;
    }
    for (int i = 0; i < ticket_count; i++) {
        fprintf(file, "%s\n", m[i].title);
        fprintf(file, "%s\n", s[i].time);
        fprintf(file, "%d\n", s[i].price);
        fprintf(file, "%d\n", s[i].available_Seats);
    }
    fclose(file);
}

void View_Avaliable_Movies(){
    system("cls");
    printf("\n============================================================\n");
    printf("                      Available Movies");
    printf("\n============================================================\n");

    for(int i = 0; i < 5; i++){
        printf("\nMovie - %d: %s (%s)\n\n", i+1, m[i].title, m[i].genre);
        printf("Showtimes: %s\n", s[i].time);
        printf("Price: %d\n", s[i].price);
        if(s[i].available_Seats > 0){
            printf("Seats Available: %d\n", s[i].available_Seats);
        }else{
            printf("Seats: Avaialble: SOLD OUT\n");
        }
        printf("\n");
        if(i < 4){
            printf("\n------------------------------------------------------------\n");
        }
    }
    printf("\n============================================================\n");
    Press_Enter_to_Continue();
}

void Purchase_Tickets(){
    system("cls");
    int movie_choice, ticket_quantity;
    
    printf("\n=======================================\n");
    printf("            Purchase Tickets");
    printf("\n=======================================\n");
    for(int i = 0; i < 5; i++){
        printf("%d. %s\n", i+1, m[i].title);
    }
    printf("\n 0. Back to Main Menu\n");
    
    printf("=======================================\n");
    printf("Enter movie number: ");
    scanf("%d", &movie_choice);
    while (getchar() != '\n');

    if(movie_choice == 0) return;
    if(movie_choice < 1 || movie_choice > 5) {
        printf("\nInvalid movie number.\n");
        Press_Enter_to_Continue();
        return;
    }

    int movie_position = movie_choice - 1;

    if(s[movie_position].available_Seats == 0){
        printf("\nSorry, this movie is SOLD OUT.\n");
        Press_Enter_to_Continue();
        return;
    }

    printf("\n---------------------------------------");
    printf("\nSelected Movie: %s", m[movie_position].title);
    printf("\nShowtime: %s", s[movie_position].time);
    printf("\nPrice: %d", s[movie_position].price);
    printf("\nAvailable Seats: %d\n", s[movie_position].available_Seats);
    printf("----------------------------------------\n");
    printf("Enter number of tickets to buy: ");
    scanf("%d", &ticket_quantity);
    while (getchar() != '\n');

    if(ticket_quantity <= 0) {
        printf("\nInvalid Choice. Please choose options from 1-5 only.\n");
        Press_Enter_to_Continue();
        return;
    }
    if(ticket_quantity > s[movie_position].available_Seats) {
        printf("\nSorry, only %d seats are available.\n", s[movie_position].available_Seats);
        Press_Enter_to_Continue();
        return;
    }

    int total_price = ticket_quantity * s[movie_position].price; 
    printf("\n\n-----------Purchase Successful----------\n\n");
    printf("Movie: %s\n", m[movie_position].title);
    printf("Quantity: %d\n", ticket_quantity);
    printf("Total Price: %d\n", total_price);
    printf("----------------------------------------\n");

    s[movie_position].available_Seats -= ticket_quantity;
    strcpy(t[ticket_count].movie_Title, m[movie_position].title);
    strcpy(t[ticket_count].show_Time, s[movie_position].time);
    t[ticket_count].quantity = ticket_quantity;
    t[ticket_count].total_Amount = total_price;
    ticket_count++;
    Press_Enter_to_Continue();
}

void View_My_Purchases(){
    system("cls");
    printf("All Purchase History\n");

    if(ticket_count == 0){
        printf("No purchase has been made yet.\n");
    }else{
        int grand_total = 0;
        for(int i = 0; i < ticket_count; i++){
            printf("\n=======================================\n");
            printf("            Ticket - %d:\n", i+1);
            printf("=======================================\n");
            printf("Movie: %s\n", t[i].movie_Title);
            printf("Showtime: %s:\n", t[i].show_Time);
            printf("Quantity: %d\n", t[i].quantity);
            printf("Total Amount:%d\n", t[i].total_Amount);
            grand_total += t[i].total_Amount;
        }
        printf("\n-----------------------------------------");
        printf("\nTotal Amount Spent in JHS-CinePlex: %d\n", grand_total);
        printf("-----------------------------------------\n");
    }
    Press_Enter_to_Continue();
}

void Press_Enter_to_Continue(){
    printf("\nPress Enter to Continue...");
    while (getchar() != '\n');
}

