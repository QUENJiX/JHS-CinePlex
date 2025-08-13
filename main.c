#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_BOLD    "\x1b[1m"

#define MAX_MOVIES 200
#define MAX_PURCHASES 500
#define MAX_USERS 200

struct Movie { char title[200]; char genre[100]; };
struct Showtime { char time[100]; int price; int available_Seats; };    
struct Ticket { char movie_Title[200]; char show_Time[50]; int ticket_Count; int total_Amount; char username[50]; char purchase_Date[20]; };
struct User { char username[50]; char password[50]; };

struct Movie m[MAX_MOVIES];
struct Showtime s[MAX_MOVIES];
struct Ticket all_purchases[MAX_PURCHASES];
struct User all_users[MAX_USERS];
int movie_count = 0;
int purchase_count = 0;
int user_count = 0;

void Read_Movies();
void Write_Movies();
void Read_Tickets();
void Write_Tickets();
void Read_Users();
void Write_Users();
void Default_Movies();

void admin_panel();
void admin_add_movie();
void admin_edit_movie();
void admin_remove_movie();
void view_all_purchases();

void user_portal();
int user_login(char* username_buffer);
void user_register();
void user_menu(char* username);
void view_available_movies();
void purchase_tickets(char* username);
void view_my_purchases(char* username);

void press_enter_to_continue() {printf(COLOR_CYAN "\nPress Enter to continue..." COLOR_RESET); getchar();}

int main() {
    Read_Users();
    Read_Movies();
    Read_Tickets();

    while (1) {
        system("cls");
        printf(COLOR_YELLOW COLOR_BOLD "====================== JHS-CinePlex - Management & Booking ======================" COLOR_RESET "\n\n");
        printf("   " COLOR_MAGENTA "[1]" COLOR_RESET " Admin Login\n");
        printf("   " COLOR_MAGENTA "[2]" COLOR_RESET " Customer Login / Register\n");
        printf("\n   " COLOR_RED "[3] Exit" COLOR_RESET "\n\n");
        printf(COLOR_CYAN ">> Enter your choice: " COLOR_RESET);

        int choice;
        scanf("%d", &choice); 
        while (getchar() != '\n'); 

        switch (choice) {
            case 1: admin_panel(); break;
            case 2: user_portal(); break;
            case 3:
                Write_Movies();
                Write_Tickets();
                Write_Users();
                printf(COLOR_GREEN "\n[SUCCESS] All data saved. Goodbye!" COLOR_RESET "\n");
                return 0;
            default: 
                printf(COLOR_RED "\n[ERROR] Invalid choice." COLOR_RESET "\n");
                press_enter_to_continue();
                break;
        }
    }
    return 0;
}

void admin_panel() {
    char username[50], password[50];
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "================================== Admin Login ==================================" COLOR_RESET "\n\n");
    
    printf(COLOR_CYAN "Enter Admin Username: " COLOR_RESET);
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf(COLOR_CYAN "Enter Admin Password: " COLOR_RESET);
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; 

    if (!((strcmp(username, "Hasib") == 0 && strcmp(password, "hasib123") == 0) ||
          (strcmp(username, "Jaima") == 0 && strcmp(password, "jaima123") == 0) ||
          (strcmp(username, "Shimu") == 0 && strcmp(password, "shimu123") == 0))) {
        printf(COLOR_RED "\n[ERROR] Incorrect username or password. Access denied." COLOR_RESET "\n");
        press_enter_to_continue();
        return;
    }

    printf(COLOR_GREEN "\n[SUCCESS] Login successful." COLOR_RESET "\n");
    press_enter_to_continue();

    while (1) {
        system("cls");
        printf(COLOR_YELLOW COLOR_BOLD "================================ Admin Dashboard ================================" COLOR_RESET "\n\n");
        int tickets_sold = 0, revenue = 0;
        for (int i = 0; i < purchase_count; ++i) {
            tickets_sold += all_purchases[i].ticket_Count;
            revenue += all_purchases[i].total_Amount;
        }
        printf(COLOR_GREEN COLOR_BOLD "  Total Movies:   " COLOR_RESET "%-10d\n", movie_count);
        printf(COLOR_GREEN COLOR_BOLD "  Tickets Sold:   " COLOR_RESET "%-10d\n", tickets_sold);
        printf(COLOR_GREEN COLOR_BOLD "  Total Revenue:  " COLOR_RESET "BDT %-10d\n\n", revenue);

        printf("   " COLOR_MAGENTA "[1]" COLOR_RESET " Add New Movie\n");
        printf("   " COLOR_MAGENTA "[2]" COLOR_RESET " Edit Movie\n");
        printf("   " COLOR_MAGENTA "[3]" COLOR_RESET " Remove Movie\n");
        printf("   " COLOR_MAGENTA    "[4]" COLOR_RESET " View All Movies\n");
        printf("   " COLOR_MAGENTA    "[5]" COLOR_RESET " View All Purchases\n");
        printf("\n   " COLOR_RED "[6] Logout" COLOR_RESET "\n\n");
        printf(COLOR_CYAN ">> Enter your choice: " COLOR_RESET);

        int choice;
        if (scanf("%d", &choice) != 1) choice = 0;
        while (getchar() != '\n');

        switch (choice) {
            case 1: admin_add_movie(); break;
            case 2: admin_edit_movie(); break;
            case 3: admin_remove_movie(); break;
            case 4: view_available_movies(); break;
            case 5: view_all_purchases(); break;
            case 6: return;
            default:
                printf(COLOR_RED "\n[ERROR] Invalid choice." COLOR_RESET "\n");
                press_enter_to_continue();
                break;
        }
    }
}

void admin_add_movie() {
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "================================ [+] Add New Movie ================================" COLOR_RESET "\n\n");
    if (movie_count >= MAX_MOVIES) {
        printf(COLOR_RED "[ERROR] Movie list is full." COLOR_RESET "\n");
        press_enter_to_continue();
        return;
    }

    printf(COLOR_CYAN "Enter Title (" COLOR_YELLOW "0 to cancel" COLOR_CYAN "): " COLOR_RESET);
    fgets(m[movie_count].title, sizeof(m[movie_count].title), stdin);
    m[movie_count].title[strcspn(m[movie_count].title, "\n")] = 0;
    if (strcmp(m[movie_count].title, "0") == 0) return;

    printf(COLOR_CYAN "Enter Genre: " COLOR_RESET);
    fgets(m[movie_count].genre, sizeof(m[movie_count].genre), stdin);
    m[movie_count].genre[strcspn(m[movie_count].genre, "\n")] = 0;

    printf(COLOR_CYAN "Enter Showtime (e.g., 08:00 PM - 10:00 PM): " COLOR_RESET);
    fgets(s[movie_count].time, sizeof(s[movie_count].time), stdin);
    s[movie_count].time[strcspn(s[movie_count].time, "\n")] = 0;

    char line[64];
    printf(COLOR_CYAN "Enter Price: " COLOR_RESET);
    fgets(line, sizeof(line), stdin);
    s[movie_count].price = atoi(line);

    printf(COLOR_CYAN "Enter Available Seats: " COLOR_RESET);
    fgets(line, sizeof(line), stdin);
    s[movie_count].available_Seats = atoi(line);

    movie_count++;
    Write_Movies();
    printf(COLOR_GREEN "\n[SUCCESS] Movie added successfully!" COLOR_RESET "\n");
    press_enter_to_continue();
}

void admin_edit_movie() {
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "================================= ~ Edit Movie =================================" COLOR_RESET "\n\n");
    if (movie_count == 0) {
        printf(COLOR_YELLOW "[INFO] No movies to edit." COLOR_RESET "\n");
        press_enter_to_continue();
        return;
    }

    printf(" "COLOR_CYAN "Select a movie to edit:" COLOR_RESET "\n\n");
    for (int i = 0; i < movie_count; ++i) {
        printf("    " COLOR_MAGENTA  "[%d] " COLOR_RESET "%s\n", i + 1, m[i].title);
    }
    printf("\n    " COLOR_RED  "[0] Back" COLOR_RESET "\n");
    printf(COLOR_CYAN "\n>> Enter movie number: " COLOR_RESET);

    int choice;
    if (scanf("%d", &choice) != 1) choice = -1;
    while (getchar() != '\n');

    if (choice == 0) return;
    if (choice < 1 || choice > movie_count) {
        printf(COLOR_RED "[ERROR] Invalid selection." COLOR_RESET "\n");
        press_enter_to_continue();
        return;
    }
    int idx = choice - 1;

    printf("\n"COLOR_GREEN "Editing Movie: " COLOR_RESET COLOR_BOLD "%s " COLOR_RESET "(%s)\n\n", m[idx].title, m[idx].genre);
    printf(COLOR_BLUE "Current Showtime: " COLOR_RESET "%s\n" COLOR_BLUE "Current Price: " COLOR_RESET "BDT %d\n" COLOR_BLUE "Current Seats: " COLOR_RESET "%d\n\n", s[idx].time, s[idx].price, s[idx].available_Seats);
    printf(COLOR_YELLOW "[INFO] Press Enter to keep the current value for any field.\n\n" COLOR_RESET);

    char buffer[256];
    printf(COLOR_CYAN "New Title: " COLOR_RESET);
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { buffer[strcspn(buffer, "\n")] = 0; strncpy(m[idx].title, buffer, sizeof(m[idx].title)-1); }
    printf(COLOR_CYAN "New Genre: " COLOR_RESET);
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { buffer[strcspn(buffer, "\n")] = 0; strncpy(m[idx].genre, buffer, sizeof(m[idx].genre)-1); }
    printf(COLOR_CYAN "New Showtime: " COLOR_RESET);
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { buffer[strcspn(buffer, "\n")] = 0; strncpy(s[idx].time, buffer, sizeof(s[idx].time)-1); }
    printf(COLOR_CYAN "New Price: " COLOR_RESET);
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { s[idx].price = atoi(buffer); }
    printf(COLOR_CYAN "New Seats: " COLOR_RESET);
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { s[idx].available_Seats = atoi(buffer); }

    Write_Movies();
    printf(COLOR_GREEN "\n[SUCCESS] Movie updated successfully." COLOR_RESET "\n");
    press_enter_to_continue();
}

void admin_remove_movie() {
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "=============================== [-] Remove Movie ===============================" COLOR_RESET "\n\n");
    if (movie_count == 0) {
        printf(COLOR_YELLOW "[INFO] No movies to remove." COLOR_RESET "\n");
        press_enter_to_continue();
        return;
    }

    printf(" "COLOR_CYAN "Select a movie to remove:" COLOR_RESET "\n\n");
    for (int i = 0; i < movie_count; ++i) {
        printf("    " COLOR_MAGENTA "[%d]" COLOR_RESET " %s\n", i + 1, m[i].title);
    }
    printf("\n    " COLOR_RED "[0] Back" COLOR_RESET "\n");
    printf(COLOR_CYAN "\n>> Enter movie number: " COLOR_RESET);

    char choice;
    if (scanf("%d", &choice) != 1) choice = -1;
    while (getchar() != '\n');

    if (choice == 0) return;
    if (choice < 1 || choice > movie_count) {
        printf(COLOR_RED "[ERROR] Invalid selection." COLOR_RESET "\n");
        press_enter_to_continue();
        return;
    }
    int idx = choice - 1;

    char ch;
    printf("\n" COLOR_YELLOW "Selected Movie: %s (%s)" COLOR_RESET "\n", m[idx].title, m[idx].genre);
    printf(COLOR_RED COLOR_BOLD "Confirm removal? This action cannot be undone. (Y/N): " COLOR_RESET);
    scanf(" %c", &ch);
    while (getchar() != '\n');

    if (toupper(ch) != 'Y') {
        printf(COLOR_YELLOW "\n[INFO] Removal cancelled." COLOR_RESET "\n");
        press_enter_to_continue();
        return;
    }

    for (int i = idx; i < movie_count - 1; ++i) { 
        m[i] = m[i+1]; 
        s[i] = s[i+1]; 
    }
    movie_count--;
    Write_Movies();
    printf(COLOR_GREEN "\n[SUCCESS] Movie has been removed." COLOR_RESET "\n");
    press_enter_to_continue();
}

void view_all_purchases() {
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "============================= All Purchase History =============================" COLOR_RESET "\n\n");
    if (purchase_count == 0) { 
        printf(COLOR_YELLOW "[INFO] No purchases have been made yet." COLOR_RESET "\n");
        press_enter_to_continue(); 
        return; 
    }
    printf(COLOR_BOLD "--------------------------------------------------------------------------------\n" COLOR_RESET);
    printf(COLOR_CYAN COLOR_BOLD "%-5s %-12s %-25s %-10s %-12s %-15s\n" COLOR_RESET, "ID", "Date", "Movie", "Tickets", "Amount", "User");
    printf(COLOR_BOLD "--------------------------------------------------------------------------------\n" COLOR_RESET);
    for (int i = 0; i < purchase_count; ++i) {
        printf(COLOR_MAGENTA "#%-5d" COLOR_RESET "%-12s %-25.25s %-10d BDT %-8d %-15.15s\n",
               i+1, all_purchases[i].purchase_Date, all_purchases[i].movie_Title,
               all_purchases[i].ticket_Count, all_purchases[i].total_Amount, all_purchases[i].username);
    }
    printf(COLOR_BOLD "--------------------------------------------------------------------------------\n" COLOR_RESET);
    press_enter_to_continue();
}

void user_portal() {
    while (1) {
        system("cls");
        printf(COLOR_YELLOW COLOR_BOLD "================================ Customer Portal ================================" COLOR_RESET "\n\n");
        printf("   " COLOR_MAGENTA "[1]" COLOR_RESET " Login to your account\n");
        printf("   " COLOR_MAGENTA "[2]" COLOR_RESET " Register a new account\n");
        printf("\n   " COLOR_RED "[3] Back to Main Menu" COLOR_RESET "\n\n");
        printf(COLOR_CYAN ">> Enter your choice: " COLOR_RESET);

        int choice;
        if (scanf("%d", &choice) != 1) choice = 0;
        while (getchar() != '\n');

        switch (choice){
            case 1: {
                char current_user[50];
                if (user_login(current_user)) user_menu(current_user);
                break;
            }
            case 2: user_register(); break;
            case 3: return;
            default: 
                printf(COLOR_RED "\n[ERROR] Invalid choice." COLOR_RESET "\n");
                press_enter_to_continue();
                break;
        }
    }
}

int user_login(char* username_buffer) {
    char username[50], password[50];
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "================================ Customer Login ================================" COLOR_RESET "\n\n");
    
    printf(COLOR_CYAN "Enter Username: " COLOR_RESET);
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf(COLOR_CYAN "Enter Password: " COLOR_RESET);
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(all_users[i].username, username) == 0 && strcmp(all_users[i].password, password) == 0) {
            printf(COLOR_GREEN "\n[SUCCESS] Login successful! Welcome back." COLOR_RESET "\n");
            strcpy(username_buffer, username);
            press_enter_to_continue();
            return 1;
        }
    }
    printf(COLOR_RED "\n[ERROR] Invalid username or password. Please try again." COLOR_RESET "\n");
    press_enter_to_continue();
    return 0;
}

void user_register() {
    char username[50], password[50];
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "============================ New User Registration =============================" COLOR_RESET "\n\n");
    printf(COLOR_CYAN "Enter a new username (" COLOR_YELLOW "0 to cancel" COLOR_CYAN "): " COLOR_RESET);
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    if (strcmp(username, "0") == 0) return;

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(all_users[i].username, username) == 0) {
            printf(COLOR_RED "\n[ERROR] This username is already taken. Please choose another." COLOR_RESET "\n");
            press_enter_to_continue();
            return;
        }
    }

    printf(COLOR_CYAN "Enter a new password: " COLOR_RESET);
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (user_count >= MAX_USERS) {
        printf(COLOR_RED "\n[ERROR] Maximum user limit reached. Cannot register new user." COLOR_RESET "\n");
        press_enter_to_continue();
        return;
    }

    strcpy(all_users[user_count].username, username);
    strcpy(all_users[user_count].password, password);
    user_count++;
    Write_Users();
    printf(COLOR_GREEN "\n[SUCCESS] Registration successful! You can now log in with your new account." COLOR_RESET "\n");
    press_enter_to_continue();
}

void user_menu(char* username) {
    while (1) {
        system("cls");
        printf(COLOR_YELLOW COLOR_BOLD "============================== Welcome, %s! ================================" COLOR_RESET "\n\n", username);
        printf("   " COLOR_MAGENTA "[1]" COLOR_RESET " View Available Movies\n");
        printf("   " COLOR_MAGENTA "[2]" COLOR_RESET " Purchase Tickets\n");
        printf("   " COLOR_MAGENTA "[3]" COLOR_RESET " View My Purchase History\n");
        printf("\n   " COLOR_RED "[4] Logout" COLOR_RESET "\n\n");
        printf(COLOR_CYAN ">> Enter your choice: " COLOR_RESET);

        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice){
            case 1: view_available_movies(); break;
            case 2: purchase_tickets(username); break;
            case 3: view_my_purchases(username); break;
            case 4: return;
            default:
                printf(COLOR_RED "\n[ERROR] Invalid choice." COLOR_RESET "\n");
                press_enter_to_continue();
                break;
        }
    }
}

void view_available_movies() {
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "=============================== Available Movies ================================" COLOR_RESET "\n\n");
    printf(COLOR_BOLD "---------------------------------------------------------------------------------\n" COLOR_RESET);
    printf(COLOR_CYAN COLOR_BOLD "%-4s %-30s %-20s %-12s %-10s\n" COLOR_RESET, "No.", "Title", "Genre", "Price", "Seats");
    printf(COLOR_BOLD "---------------------------------------------------------------------------------\n" COLOR_RESET);
    if (movie_count == 0) {
        printf(COLOR_YELLOW "\n[INFO] Sorry, there are no movies available at the moment.\n" COLOR_RESET);
    } else {

        for (int i = 0; i < movie_count; ++i) {
            printf(COLOR_MAGENTA COLOR_BOLD "%-5d" COLOR_RESET "%-30.30s %-20.20s "COLOR_YELLOW "BDT %-8d "COLOR_RESET, i+1, m[i].title, m[i].genre, s[i].price);
            if (s[i].available_Seats > 10) {
                printf(COLOR_GREEN "%-10d\n" COLOR_RESET, s[i].available_Seats);
            } else if (s[i].available_Seats > 0) {
                printf(COLOR_YELLOW "%-10d\n" COLOR_RESET, s[i].available_Seats);
            } else {
                printf(COLOR_RED "%-10s\n" COLOR_RESET, "SOLD OUT");
            }
        }
    }
    printf(COLOR_BOLD "---------------------------------------------------------------------------------\n" COLOR_RESET);
    press_enter_to_continue();
}

void purchase_tickets(char* current_username) {
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "=============================== Purchase Tickets ================================" COLOR_RESET "\n\n");
    if (movie_count == 0) { 
        printf(COLOR_YELLOW "[INFO] No movies available for purchase." COLOR_RESET "\n");
        press_enter_to_continue(); 
        return; 
    }

    for (int i = 0; i < movie_count; ++i) {
        printf("   " COLOR_MAGENTA "[%d] " COLOR_RESET "%s (%s) - Seats: ", i + 1, m[i].title, m[i].genre);
        if(s[i].available_Seats > 0) printf(COLOR_GREEN "%d\n" COLOR_RESET, s[i].available_Seats);
        else printf(COLOR_RED "SOLD OUT\n" COLOR_RESET);
    }
    printf("\n   " COLOR_RED "[0] Back" COLOR_RESET "\n");
    printf(COLOR_CYAN "\n>> Enter movie number to purchase: " COLOR_RESET);
    
    char line[128];
    int choice;
    int ticket_count;
    if (scanf("%d", &choice) != 1) {
        choice = 0; 
    }
    fgets(line, sizeof(line), stdin);
    
    if (choice == 0) return;
    if (choice < 1 || choice > movie_count) { 
        printf(COLOR_RED "\n[ERROR] Invalid movie selection." COLOR_RESET "\n"); 
        press_enter_to_continue(); return; 
    }

    int index = choice - 1;
    if (s[index].available_Seats == 0) { 
        printf(COLOR_RED "\n[ERROR] Sorry, this movie is SOLD OUT." COLOR_RESET "\n"); 
        press_enter_to_continue(); return; 
    }

    printf("\n" COLOR_GREEN "Selected Movie: " COLOR_RESET "'%s' | " COLOR_GREEN "Available Seats: " COLOR_RESET "%d\n", m[index].title, s[index].available_Seats);
    printf(COLOR_CYAN ">> Enter number of tickets to buy: " COLOR_RESET);
    
    fgets(line, sizeof(line), stdin);
    ticket_count = atoi(line);

    if (ticket_count <= 0) {
        printf(COLOR_RED "\n[ERROR] You must purchase at least one ticket." COLOR_RESET "\n"); 
        press_enter_to_continue(); return; 
    }
    if (ticket_count > s[index].available_Seats) { 
        printf(COLOR_RED "\n[ERROR] Not enough available seats. You can buy a maximum of %d tickets." COLOR_RESET "\n", s[index].available_Seats); 
        press_enter_to_continue(); return; 
    }

    int total_price = ticket_count * s[index].price;
    printf("\n" COLOR_YELLOW "--- Purchase Summary ---\n" COLOR_RESET);
    printf("   " COLOR_BLUE "Movie:    " COLOR_RESET "%s\n", m[index].title);
    printf("   " COLOR_BLUE "Showtime: " COLOR_RESET "%s\n", s[index].time);
    printf("   " COLOR_BLUE "Tickets:  " COLOR_RESET "%d\n", ticket_count);
    printf("   " COLOR_BLUE "Total:    " COLOR_RESET COLOR_BOLD "BDT %d\n" COLOR_RESET, total_price);
    printf(COLOR_YELLOW "------------------------\n" COLOR_RESET);

    printf(COLOR_CYAN "\nConfirm purchase? (Y/N): " COLOR_RESET);
    fgets(line, sizeof(line), stdin);
    if (toupper(line[0]) != 'Y') { 
        printf(COLOR_YELLOW "\n[INFO] Purchase cancelled." COLOR_RESET "\n"); 
        press_enter_to_continue(); return; 
    }
    
    if(purchase_count >= MAX_PURCHASES){
        printf(COLOR_RED "\n[ERROR] Purchase database is full. Please contact an admin." COLOR_RESET "\n");
        press_enter_to_continue(); return;
    }

    s[index].available_Seats -= ticket_count;
    strncpy(all_purchases[purchase_count].movie_Title, m[index].title, sizeof(all_purchases[purchase_count].movie_Title)-1);
    strncpy(all_purchases[purchase_count].show_Time, s[index].time, sizeof(all_purchases[purchase_count].show_Time)-1);
    all_purchases[purchase_count].ticket_Count = ticket_count;
    all_purchases[purchase_count].total_Amount = total_price;
    strncpy(all_purchases[purchase_count].username, current_username, sizeof(all_purchases[purchase_count].username)-1);

    time_t t = time(NULL); struct tm tm = *localtime(&t);
    snprintf(all_purchases[purchase_count].purchase_Date, sizeof(all_purchases[purchase_count].purchase_Date), "%d-%02d-%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
    
    Write_Tickets(); 
    Write_Movies();

    system("cls");
    printf(COLOR_GREEN "      Purchase Successful! Here is your ticket:\n" COLOR_RESET);
    printf(COLOR_CYAN " ----------------------------------------------- \n");
    printf("|            " COLOR_BOLD "JHS-CinePlex E-Ticket" COLOR_RESET COLOR_CYAN "              |\n");
    printf(" ----------------------------------------------- \n");
    printf(COLOR_RESET " " COLOR_BOLD "Movie: " COLOR_RESET "%-36.36s\n", m[index].title);
    printf(COLOR_RESET " " COLOR_BOLD "Show : " COLOR_RESET "%-36.36s\n", s[index].time);
    printf(COLOR_RESET " " COLOR_BOLD "Seats: " COLOR_RESET "%-36d\n", ticket_count);
    printf(COLOR_RESET " " COLOR_BOLD "Total: " COLOR_RESET "BDT %-31d\n", total_price);
    printf(COLOR_RESET " " COLOR_BOLD "Date : " COLOR_RESET "%-36.36s\n", all_purchases[purchase_count].purchase_Date);
    printf(COLOR_RESET " " COLOR_BOLD "User : " COLOR_RESET "%-36.36s\n", current_username);
    printf(COLOR_CYAN " ----------------------------------------------- \n" COLOR_RESET);
    
    purchase_count++; 
    press_enter_to_continue();
}

void view_my_purchases(char* current_username) {
    system("cls");
    printf(COLOR_YELLOW COLOR_BOLD "========================= Purchase History for %s =========================" COLOR_RESET "\n\n", current_username);
    int cnt = 0, total_spent = 0;
    printf(COLOR_BOLD "--------------------------------------------------------------------------\n" COLOR_RESET);
    printf(COLOR_CYAN COLOR_BOLD "%-12s %-35s %-10s %-10s\n" COLOR_RESET, "Date", "Movie Title", "Tickets", "Amount");
    printf(COLOR_BOLD "--------------------------------------------------------------------------\n" COLOR_RESET);
    for (int i = 0; i < purchase_count; ++i) {
        if (strcmp(all_purchases[i].username, current_username) == 0) {
            printf("%-12s %-35.35s %-10d " COLOR_YELLOW "BDT %-6d\n" COLOR_RESET, all_purchases[i].purchase_Date, all_purchases[i].movie_Title, all_purchases[i].ticket_Count, all_purchases[i].total_Amount);
            total_spent += all_purchases[i].total_Amount;
            cnt++;
        }
    }
    
    if (cnt == 0) {
        printf(COLOR_YELLOW "\n[INFO] You have not made any purchases yet.\n" COLOR_RESET);
    } else {
        printf(COLOR_BOLD "--------------------------------------------------------------------------\n" COLOR_RESET);
        printf(COLOR_GREEN "Total Spent: BDT %d\n" COLOR_RESET, total_spent);
    }
    press_enter_to_continue();
}

void Read_Movies() {
    FILE *file = fopen("movie_list.txt", "r");
    if (!file) { Default_Movies(); Write_Movies(); return; }
    char buffer[256];
    movie_count = 0;
    while(movie_count < MAX_MOVIES && fgets(m[movie_count].title, sizeof(m[0].title), file)) {
        m[movie_count].title[strcspn(m[movie_count].title, "\n")] = 0;
        fgets(m[movie_count].genre, sizeof(m[0].genre), file);
        m[movie_count].genre[strcspn(m[movie_count].genre, "\n")] = 0;
        fgets(s[movie_count].time, sizeof(s[0].time), file);
        s[movie_count].time[strcspn(s[movie_count].time, "\n")] = 0;
        fgets(buffer, sizeof(buffer), file); s[movie_count].price = atoi(buffer);
        fgets(buffer, sizeof(buffer), file); s[movie_count].available_Seats = atoi(buffer);
        movie_count++;
    }
    fclose(file);
}

void Write_Movies() {
    FILE *file = fopen("movie_list.txt", "w");
    if (!file) return;
    for (int i = 0; i < movie_count; ++i) {
        fprintf(file, "%s\n%s\n%s\n%d\n%d\n", m[i].title, m[i].genre, s[i].time, s[i].price, s[i].available_Seats);
    }
    fclose(file);
}

void Read_Tickets() {
    FILE *file = fopen("tickets.txt", "r");
    if (!file) return;
    char buffer[512];
    purchase_count = 0;
    while (purchase_count < MAX_PURCHASES && fgets(all_purchases[purchase_count].movie_Title, sizeof(all_purchases[0].movie_Title), file)) {
        all_purchases[purchase_count].movie_Title[strcspn(all_purchases[purchase_count].movie_Title, "\n")] = 0;
        fgets(all_purchases[purchase_count].show_Time, sizeof(all_purchases[0].show_Time), file);
        all_purchases[purchase_count].show_Time[strcspn(all_purchases[purchase_count].show_Time, "\n")] = 0;
        fgets(buffer, sizeof(buffer), file); all_purchases[purchase_count].ticket_Count = atoi(buffer);
        fgets(buffer, sizeof(buffer), file); all_purchases[purchase_count].total_Amount = atoi(buffer);
        fgets(all_purchases[purchase_count].username, sizeof(all_purchases[0].username), file);
        all_purchases[purchase_count].username[strcspn(all_purchases[purchase_count].username, "\n")] = 0;
        fgets(all_purchases[purchase_count].purchase_Date, sizeof(all_purchases[0].purchase_Date), file);
        all_purchases[purchase_count].purchase_Date[strcspn(all_purchases[purchase_count].purchase_Date, "\n")] = 0;
        purchase_count++;
    }
    fclose(file);
}

void Write_Tickets() {
    FILE *file = fopen("tickets.txt", "w");
    if (!file) return;
    for (int i = 0; i < purchase_count; ++i) {
        fprintf(file, "%s\n%s\n%d\n%d\n%s\n%s\n", all_purchases[i].movie_Title, all_purchases[i].show_Time,
                all_purchases[i].ticket_Count, all_purchases[i].total_Amount, all_purchases[i].username, all_purchases[i].purchase_Date);
    }
    fclose(file);
}

void Read_Users() {
    FILE *file = fopen("users.txt", "r");
    if (!file) return;
    char line[128];
    user_count = 0;
    while (user_count < MAX_USERS && fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%49s %49s", all_users[user_count].username, all_users[user_count].password) == 2) {
            user_count++;
        }
    }
    fclose(file);
}

void Write_Users() {
    FILE *file = fopen("users.txt", "w");
    if (!file) return;
    for (int i = 0; i < user_count; ++i) {
        fprintf(file, "%s %s\n", all_users[i].username, all_users[i].password);
    }
    fclose(file);
}

void Default_Movies() {
    movie_count = 5;
    strcpy(m[0].title, "Hereditary"); strcpy(m[0].genre, "Horror");
    strcpy(s[0].time,  "11:00 PM - 01:20 AM"); s[0].price = 200; s[0].available_Seats = 50;
    strcpy(m[1].title, "The Notebook"); strcpy(m[1].genre, "Romantic");
    strcpy(s[1].time,  "08:30 PM - 10:10 PM"); s[1].price = 200; s[1].available_Seats = 10;
    strcpy(m[2].title, "Boss Baby"); strcpy(m[2].genre, "Comedy");
    strcpy(s[2].time,  "03:00 PM - 05:00 PM"); s[2].price = 200; s[2].available_Seats = 50;
    strcpy(m[3].title, "Harry Potter"); strcpy(m[3].genre, "Fantasy");
    strcpy(s[3].time,  "05:00 PM - 08:00 PM"); s[3].price = 500; s[3].available_Seats = 0;
    strcpy(m[4].title, "Chander Pahar"); strcpy(m[4].genre, "Adventure");
    strcpy(s[4].time,  "01:00 PM - 03:30 PM"); s[4].price = 500; s[4].available_Seats = 50;
}
