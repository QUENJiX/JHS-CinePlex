#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_MOVIES 200
#define MAX_PURCHASES 500
#define MAX_USERS 200

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_BOLD    "\x1b[1m"

void clear_screen() {
    system("cls");
}

void press_enter_to_continue() {
    printf("\nPress Enter to continue...");
    getchar();
}

void print_success(const char* msg) { printf(COLOR_GREEN "[SUCCESS] %s" COLOR_RESET "\n", msg); }
void print_error(const char* msg) { printf(COLOR_RED "[ERROR] %s" COLOR_RESET "\n", msg); }
void print_info(const char* msg) { printf(COLOR_YELLOW "[INFO] %s" COLOR_RESET "\n", msg); }

typedef struct { char title[200]; char genre[100]; } Movie;
typedef struct { char time[100]; int price; int available_Seats; } Showtime;
typedef struct { char movie_Title[200]; char show_Time[50]; int ticket_Count; int total_Amount; char username[50]; char purchase_Date[20]; } Ticket;
typedef struct { char username[50]; char password[50]; } User;

Movie m[MAX_MOVIES];
Showtime s[MAX_MOVIES];
Ticket all_purchases[MAX_PURCHASES];
User all_users[MAX_USERS];
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

int get_menu_choice(int min, int max, int allow_zero);
int confirm_prompt(const char* msg);
void show_admin_dashboard();
void admin_panel();
void admin_add_movie();
void admin_edit_movie();
void admin_remove_movie();
void view_all_purchases();

void user_portal();
int user_login(char* username_buffer);
void user_register();
void user_menu(const char* username);
void view_available_movies();
void purchase_tickets(const char* username);
void view_my_purchases(const char* username);

int main() {
    Read_Users();
    Read_Movies();
    Read_Tickets();

    while (1) {
        clear_screen();
        printf("====================== JHS-CinePlex - Management & Booking ======================\n\n");
        printf("   " COLOR_MAGENTA "[1]" COLOR_RESET " Admin Login\n");
        printf("   " COLOR_MAGENTA "[2]" COLOR_RESET " Customer Login / Register\n");
        printf("   " COLOR_MAGENTA "[3]" COLOR_RESET " Exit\n\n");
        printf(">> Enter your choice: ");

        int ch = get_menu_choice(1, 3, 0);
        switch (ch) {
            case 1: admin_panel(); break;
            case 2: user_portal(); break;
            case 3:
                Write_Movies();
                Write_Tickets();
                Write_Users();
                print_success("All data saved. Goodbye!");
                return 0;
        }
    }
    return 0;
}

int get_menu_choice(int min, int max, int allow_zero) {
    int choice;
    char line[128];
    if (!fgets(line, sizeof(line), stdin)) return 0;
    if (sscanf(line, "%d", &choice) != 1) return -1;
    if (allow_zero && choice == 0) return 0;
    if (choice < min || choice > max) return -1;
    return choice;
}

int confirm_prompt(const char* msg) {
    printf("%s (Y/N): ", msg);
    char line[8];
    if (!fgets(line, sizeof(line), stdin)) return 0;
    return (toupper((unsigned char)line[0]) == 'Y');
}

void show_admin_dashboard() {
    clear_screen();
    printf("================================ Admin Dashboard ================================\n\n");

    int tickets_sold = 0, revenue = 0;
    for (int i = 0; i < purchase_count; ++i) {
        tickets_sold += all_purchases[i].ticket_Count;
        revenue += all_purchases[i].total_Amount;
    }

    printf(COLOR_BOLD "  Total Movies:   " COLOR_RESET "%d\n", movie_count);
    printf(COLOR_BOLD "  Tickets Sold:   " COLOR_RESET "%d\n", tickets_sold);
    printf(COLOR_BOLD "  Total Revenue:  " COLOR_RESET "BDT %d\n\n", revenue);
}

void admin_panel() {
    char username[50], password[50];
    clear_screen();
    printf("================================== Admin Login ==================================\n\n");
    printf("\nEnter Admin Username: ");
    if (!fgets(username, sizeof(username), stdin)) return;
    username[strcspn(username, "\n")] = 0;

    printf("Enter Admin Password: ");
    if (!fgets(password, sizeof(password), stdin)) return;
    password[strcspn(password, "\n")] = 0;

    if (!((strcmp(username, "Hasib") == 0 && strcmp(password, "hasib123") == 0) ||
          (strcmp(username, "Jaima") == 0 && strcmp(password, "jaima123") == 0) ||
          (strcmp(username, "Shimu") == 0 && strcmp(password, "shimu123") == 0))) {
        print_error("Incorrect username or password. Access denied.");
        press_enter_to_continue();
        return;
    }

    print_success("Login successful.");
    press_enter_to_continue();

    while (1) {
        show_admin_dashboard();
        printf("   " COLOR_MAGENTA "[1]" COLOR_RESET " Add New Movie\n");
        printf("   " COLOR_MAGENTA "[2]" COLOR_RESET " Edit Movie\n");
        printf("   " COLOR_MAGENTA "[3]" COLOR_RESET " Remove Movie\n");
        printf("   " COLOR_MAGENTA "[4]" COLOR_RESET " View All Movies\n");
        printf("   " COLOR_MAGENTA "[5]" COLOR_RESET " View All Purchases\n");
        printf("   " COLOR_MAGENTA "[6]" COLOR_RESET " Logout\n\n");
        printf(">> Enter your choice: ");

        int ch = get_menu_choice(1, 6, 0);
        switch (ch) {
            case 1: admin_add_movie(); break;
            case 2: admin_edit_movie(); break;
            case 3: admin_remove_movie(); break;
            case 4: view_available_movies(); break;
            case 5: view_all_purchases(); break;
            case 6: return;
        }
    }
}

void admin_add_movie() {
    clear_screen();
    printf("================================ [+] Add New Movie ================================\n\n");
    if (movie_count >= MAX_MOVIES) {
        printf("[ERROR] Movie list is full.\n");
        printf("\nPress Enter to continue..."); getchar();
        return;
    }

    printf("Enter Title (0 to cancel): ");
    if (!fgets(m[movie_count].title, sizeof(m[movie_count].title), stdin)) return;
    m[movie_count].title[strcspn(m[movie_count].title, "\n")] = 0;
    if (strcmp(m[movie_count].title, "0") == 0) return;

    printf("Enter Genre: ");
    fgets(m[movie_count].genre, sizeof(m[movie_count].genre), stdin);
    m[movie_count].genre[strcspn(m[movie_count].genre, "\n")] = 0;

    printf("Enter Showtime (e.g., 08:00 PM - 10:00 PM): ");
    fgets(s[movie_count].time, sizeof(s[movie_count].time), stdin);
    s[movie_count].time[strcspn(s[movie_count].time, "\n")] = 0;

    char line[64];
    printf("Enter Price: ");
    fgets(line, sizeof(line), stdin);
    s[movie_count].price = atoi(line);

    printf("Enter Available Seats: ");
    fgets(line, sizeof(line), stdin);
    s[movie_count].available_Seats = atoi(line);

    movie_count++;
    Write_Movies();
    printf("[SUCCESS] Movie added successfully!\n");
    printf("\nPress Enter to continue..."); getchar();
}

void admin_edit_movie() {
    clear_screen();
    printf("================================= ~ Edit Movie =================================\n\n");
    if (movie_count == 0) {
        printf("[INFO] No movies to edit.\n");
        printf("\nPress Enter to continue..."); getchar();
        return;
    }

    printf("Select a movie to edit:\n");
    for (int i = 0; i < movie_count; ++i) {
        printf("   [%d] %s\n", i + 1, m[i].title);
    }
    printf("\n   [0] Back\n");
    printf("\n>> Enter movie number: ");

    int choice = get_menu_choice(0, movie_count, 1);
    if (choice <= 0) return;
    int idx = choice - 1;

    printf("\nFound: %s (%s)\n", m[idx].title, m[idx].genre);
    printf("Showtime: %s | Price: %d | Seats: %d\n\n", s[idx].time, s[idx].price, s[idx].available_Seats);
    printf("Press Enter to keep current value.\n\n");

    char buffer[256];
    printf("New Title: ");
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { buffer[strcspn(buffer, "\n")] = 0; strncpy(m[idx].title, buffer, sizeof(m[idx].title)-1); }
    printf("New Genre: ");
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { buffer[strcspn(buffer, "\n")] = 0; strncpy(m[idx].genre, buffer, sizeof(m[idx].genre)-1); }
    printf("New Showtime: ");
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { buffer[strcspn(buffer, "\n")] = 0; strncpy(s[idx].time, buffer, sizeof(s[idx].time)-1); }
    printf("New Price: ");
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { s[idx].price = atoi(buffer); }
    printf("New Seats: ");
    if (fgets(buffer, sizeof(buffer), stdin) && buffer[0] != '\n') { s[idx].available_Seats = atoi(buffer); }

    Write_Movies();
    printf("[SUCCESS] Movie updated.\n");
    printf("\nPress Enter to continue..."); getchar();
}

void admin_remove_movie() {
    clear_screen();
    printf("=============================== [-] Remove Movie ===============================\n\n");
    if (movie_count == 0) {
        printf("[INFO] No movies to remove.\n");
        printf("\nPress Enter to continue..."); getchar();
        return;
    }

    printf("Select a movie to remove:\n");
    for (int i = 0; i < movie_count; ++i) {
        printf("   [%d] %s\n", i + 1, m[i].title);
    }
    printf("\n   [0] Back\n");
    printf("\n>> Enter movie number: ");

    int choice = get_menu_choice(0, movie_count, 1);
    if (choice <= 0) return;
    int idx = choice - 1;

    printf("\nSelected: %s (%s)\n", m[idx].title, m[idx].genre);
    printf("Confirm removal? (Y/N): ");
    char line[8];
    fgets(line, sizeof(line), stdin);

    if (toupper((unsigned char)line[0]) != 'Y') {
        printf("[INFO] Removal cancelled.\n");
        printf("\nPress Enter to continue..."); getchar();
        return;
    }

    for (int i = idx; i < movie_count - 1; ++i) { m[i] = m[i+1]; s[i] = s[i+1]; }
    movie_count--;
    Write_Movies();
    printf("[SUCCESS] Movie removed.\n");
    printf("\nPress Enter to continue..."); getchar();
}

void view_all_purchases() {
    clear_screen();
    printf("============================= All Purchase History =============================\n\n");
    if (purchase_count == 0) { print_info("No purchases yet."); press_enter_to_continue(); return; }

    printf("%-5s %-12s %-20s %-8s %-8s %-10s\n", "ID", "Date", "Movie", "Tickets", "Amount", "User");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < purchase_count; ++i) {
        printf("#%-4d %-12s %-20.20s %-8d %-8d %-10.10s\n",
               i+1, all_purchases[i].purchase_Date, all_purchases[i].movie_Title,
               all_purchases[i].ticket_Count, all_purchases[i].total_Amount, all_purchases[i].username);
    }
    press_enter_to_continue();
}

void user_portal() {
    while (1) {
        clear_screen();
        printf("================================ Customer Portal ================================\n\n");
        printf("   " COLOR_MAGENTA "[1]" COLOR_RESET " Login\n");
        printf("   " COLOR_MAGENTA "[2]" COLOR_RESET " Register\n");
        printf("   " COLOR_MAGENTA "[3]" COLOR_RESET " Back\n\n");
        printf(">> Enter your choice: ");
        int ch = get_menu_choice(1, 3, 3);
        switch (ch) {
            case 1: {
                char current_user[50];
                if (user_login(current_user)) user_menu(current_user);
                break;
            }
            case 2: user_register(); break;
            case 3: return;
        }
    }
}

int user_login(char* username_buffer) {
    char username[50], password[50];
    clear_screen();
    printf("================================ Customer Login ================================\n\n");
    printf("\nEnter Username: ");
    if (!fgets(username, sizeof(username), stdin)) return 0;
    username[strcspn(username, "\n")] = 0;

    printf("Enter Password: ");
    if (!fgets(password, sizeof(password), stdin)) return 0;
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(all_users[i].username, username) == 0 && strcmp(all_users[i].password, password) == 0) {
            print_success("Login successful!");
            strcpy(username_buffer, username);
            press_enter_to_continue();
            return 1;
        }
    }
    print_error("Invalid username or password.");
    press_enter_to_continue();
    return 0;
}

void user_register() {
    char username[50], password[50];
    clear_screen();
    printf("============================ New User Registration =============================\n\n");
    printf("\nEnter a new username (0 to cancel): ");
    if (!fgets(username, sizeof(username), stdin)) return;
    username[strcspn(username, "\n")] = 0;
    if (strcmp(username, "0") == 0) return;

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(all_users[i].username, username) == 0) {
            print_error("Username already exists.");
            press_enter_to_continue();
            return;
        }
    }

    printf("Enter a new password: ");
    if (!fgets(password, sizeof(password), stdin)) return;
    password[strcspn(password, "\n")] = 0;

    strncpy(all_users[user_count].username, username, sizeof(all_users[user_count].username)-1);
    strncpy(all_users[user_count].password, password, sizeof(all_users[user_count].password)-1);
    user_count++;
    Write_Users();
    print_success("Registration successful! You can now log in.");
    press_enter_to_continue();
}

void user_menu(const char* username) {
    while (1) {
        clear_screen();
        char title[100];
        printf("============================== Welcome, %s! ================================\n\n", username);
        print_header(title);
        printf("   " COLOR_MAGENTA "[1]" COLOR_RESET " View Available Movies\n");
        printf("   " COLOR_MAGENTA "[2]" COLOR_RESET " Purchase Tickets\n");
        printf("   " COLOR_MAGENTA "[3]" COLOR_RESET " View My Purchases\n");
        printf("   " COLOR_MAGENTA "[4]" COLOR_RESET " Logout\n\n");
        printf(">> Enter your choice: ");
        int ch = get_menu_choice(1, 4, 0);
        switch (ch) {
            case 1: view_available_movies(); break;
            case 2: purchase_tickets(username); break;
            case 3: view_my_purchases(username); break;
            case 4: return;
        }
    }
}

void view_available_movies() {
    clear_screen();
    print_header("Available Movies");
    printf("=============================== Available Movies ================================\n\n");
    printf("%-4s %-30s %-18s %-8s %-8s\n", "No.", "Title", "Genre", "Price", "Seats");
    printf("----------------------------------------------------------------------------\n");
    if (movie_count == 0) {
        print_info("No movies available.");
    } else {
        for (int i = 0; i < movie_count; ++i) {
            printf("%-4d %-30.30s %-18.18s %-8d ", i+1, m[i].title, m[i].genre, s[i].price);
            if (s[i].available_Seats > 0) {
                printf(COLOR_GREEN "%-8d" COLOR_RESET "\n", s[i].available_Seats);
            } else {
                printf(COLOR_RED "%-8s" COLOR_RESET "\n", "SOLD OUT");
            }
        }
    }
    press_enter_to_continue();
}

void purchase_tickets(const char* current_username) {
    clear_screen();
    printf("=============================== Purchase Tickets ================================\n\n");
    if (movie_count == 0) { print_info("No movies available."); press_enter_to_continue(); return; }

    for (int i = 0; i < movie_count; ++i) printf("   [%d] %s (%s) - Seats: %d\n", i + 1, m[i].title, m[i].genre, s[i].available_Seats);
    printf("\n   [0] Back\n");
    printf("\n>> Enter movie number: ");

    int choice = get_menu_choice(0, movie_count, 1);
    if (choice == 0) return;
    int index = choice - 1;
    if (s[index].available_Seats == 0) { print_error("Sorry, this movie is SOLD OUT."); press_enter_to_continue(); return; }

    printf("\nSelected: '%s' | Available Seats: %d\n", m[index].title, s[index].available_Seats);
    printf(">> Enter number of tickets to buy: ");
    char line[64];
    if (!fgets(line, sizeof(line), stdin)) return;
    int ticket_count = atoi(line);

    if (ticket_count <= 0 || ticket_count > s[index].available_Seats) { print_error("Invalid ticket count."); press_enter_to_continue(); return; }

    int total_price = ticket_count * s[index].price;
    printf("\n--- Purchase Summary ---\n");
    printf("   Movie:   %s\n", m[index].title);
    printf("   Showtime:%s\n", s[index].time);
    printf("   Tickets: %d\n", ticket_count);
    printf("   Total:   BDT %d\n", total_price);
    printf("------------------------\n");

    if (!confirm_prompt("Confirm purchase?")) { print_info("Purchase cancelled."); press_enter_to_continue(); return; }

    s[index].available_Seats -= ticket_count;
    strncpy(all_purchases[purchase_count].movie_Title, m[index].title, sizeof(all_purchases[purchase_count].movie_Title)-1);
    strncpy(all_purchases[purchase_count].show_Time, s[index].time, sizeof(all_purchases[purchase_count].show_Time)-1);
    all_purchases[purchase_count].ticket_Count = ticket_count;
    all_purchases[purchase_count].total_Amount = total_price;
    strncpy(all_purchases[purchase_count].username, current_username, sizeof(all_purchases[purchase_count].username)-1);

    time_t t = time(NULL); struct tm tm = *localtime(&t);
    snprintf(all_purchases[purchase_count].purchase_Date, sizeof(all_purchases[purchase_count].purchase_Date), "%d-%02d-%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
    purchase_count++;
    Write_Tickets(); Write_Movies();

    clear_screen();
    print_header("Ticket Receipt");
    printf("+-----------------------------------------------+\n");
    printf("|            JHS-CinePlex Ticket                |\n");
    printf("+-----------------------------------------------+\n");
    printf("  Movie: %-36.36s\n", m[index].title);
    printf("  Show : %-36.36s\n", s[index].time);
    printf("  Seats: %-36d\n", ticket_count);
    printf("  Total: BDT %-31d\n", total_price);
    printf("  Date : %-36.36s\n", all_purchases[purchase_count-1].purchase_Date);
    printf("+-----------------------------------------------+\n");
    print_success("Purchase successful!");
    press_enter_to_continue();
}

void view_my_purchases(const char* current_username) {
    clear_screen();
    char title[120];
    snprintf(title, sizeof(title), "Purchase History for %s", current_username);
    printf("======================== Purchase History for %-25s ========================\n\n", current_username);
    int cnt = 0, total_spent = 0;

    printf("%-12s %-30s %-8s %-8s\n", "Date", "Movie Title", "Tickets", "Amount");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < purchase_count; ++i) {
        if (strcmp(all_purchases[i].username, current_username) == 0) {
            printf("%-12s %-30.30s %-8d %-8d\n", all_purchases[i].purchase_Date, all_purchases[i].movie_Title, all_purchases[i].ticket_Count, all_purchases[i].total_Amount);
            total_spent += all_purchases[i].total_Amount;
            cnt++;
        }
    }
    if (cnt == 0) {
        print_info("You have not made any purchases yet.");
    } else {
        printf("---------------------------------------------------------------\n");
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
        strtok(m[movie_count].title, "\n");
        fgets(m[movie_count].genre, sizeof(m[0].genre), file); strtok(m[movie_count].genre, "\n");
        fgets(s[movie_count].time, sizeof(s[0].time), file); strtok(s[movie_count].time, "\n");
        fgets(buffer, sizeof(buffer), file); sscanf(buffer, "%d", &s[movie_count].price);
        fgets(buffer, sizeof(buffer), file); sscanf(buffer, "%d", &s[movie_count].available_Seats);
        movie_count++;
    }
    fclose(file);
}

void Write_Movies() {
    FILE *file = fopen("movie_list.txt", "w");
    if (!file) return;
    for (int i = 0; i < movie_count; ++i) fprintf(file, "%s\n%s\n%s\n%d\n%d\n", m[i].title, m[i].genre, s[i].time, s[i].price, s[i].available_Seats);
    fclose(file);
}

void Read_Tickets() {
    FILE *file = fopen("tickets.txt", "r");
    if (!file) return;
    char buffer[512];
    purchase_count = 0;
    while (purchase_count < MAX_PURCHASES && fgets(all_purchases[purchase_count].movie_Title, sizeof(all_purchases[0].movie_Title), file)) {
        strtok(all_purchases[purchase_count].movie_Title, "\n");
        fgets(all_purchases[purchase_count].show_Time, sizeof(all_purchases[0].show_Time), file); strtok(all_purchases[purchase_count].show_Time, "\n");
        fgets(buffer, sizeof(buffer), file); sscanf(buffer, "%d", &all_purchases[purchase_count].ticket_Count);
        fgets(buffer, sizeof(buffer), file); sscanf(buffer, "%d", &all_purchases[purchase_count].total_Amount);
        fgets(all_purchases[purchase_count].username, sizeof(all_purchases[0].username), file); strtok(all_purchases[purchase_count].username, "\n");
        fgets(all_purchases[purchase_count].purchase_Date, sizeof(all_purchases[0].purchase_Date), file); strtok(all_purchases[purchase_count].purchase_Date, "\n");
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
    for (int i = 0; i < user_count; ++i) fprintf(file, "%s %s\n", all_users[i].username, all_users[i].password);
    fclose(file);
}

void Default_Movies() {
    movie_count = 5;
    strcpy(m[0].title, "Hereditary"); strcpy(m[0].genre, "Horror");
    strcpy(s[0].time,  "11:00 PM - 01:20 AM"); s[0].price = 200; s[0].available_Seats = 50;
    strcpy(m[1].title, "The Notebook"); strcpy(m[1].genre, "Romantic");
    strcpy(s[1].time,  "08:30 PM - 10:10 PM"); s[1].price = 200; s[1].available_Seats = 10;
    strcpy(m[2].title, "Boss Baby"); strcpy(m[2].genre, "Family / Comedy");
    strcpy(s[2].time,  "03:00 PM - 05:00 PM"); s[2].price = 200; s[2].available_Seats = 50;
    strcpy(m[3].title, "Harry Potter and the Goblet of Fire"); strcpy(m[3].genre, "Fantasy");
    strcpy(s[3].time,  "05:00 PM - 08:00 PM"); s[3].price = 500; s[3].available_Seats = 0;
    strcpy(m[4].title, "Chander Pahar"); strcpy(m[4].genre, "Adventure");
    strcpy(s[4].time,  "01:00 PM - 03:30 PM"); s[4].price = 500; s[4].available_Seats = 50;
}
