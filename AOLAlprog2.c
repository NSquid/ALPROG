#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//////// Struct ////////
typedef struct {
    char location[100];
    char city[100];
    int price;
    int rooms;
    int bathrooms;
    int carParks;
    char type[100];
    char furnish[100];
} Data;

typedef struct {
    char location[100];
    char city[100];
    int price;
    int rooms;
    int bathrooms;
    int carParks;
    char type[100];
    char furnish[100];
} DataSearch;
///////////////////////

/// Global Variable ///
char sortColumn[100];
char sortOrder[10];
///////////////////////

////////////////////////// Extras //////////////////////////
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}
////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////// 2A ////////////////////////////////////////////////////////
void displayData(FILE *CSVfile, int rows){  // Display & Print data dari file CSV
    char buff[1000];
    char* token;
    const char* delimiter = ",";
    int columnWidth = 16;

    for (int i = 0; i < rows + 1; i++){
        fgets(buff, sizeof(buff), CSVfile);
        token = strtok(buff, delimiter);

        while(token != NULL) {
            printf("%-*s", columnWidth, token);
            token = strtok(NULL, delimiter);
        }

        printf("\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////// 2B ////////////////////////////////////////////////////////
void search(Data *data, int num_rows) { // Search data dari file CSV berdasarkan keyword dan column dari input user
    char column[50];
    char keyword[50];
    clearInputBuffer(); 
    printf("Enter the column you want to search in: ");
    fgets(column, sizeof(column), stdin);
    column[strcspn(column, "\n")] = 0;  // Remove the newline character

    printf("Enter the keyword you want to search for: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;  // Remove the newline character

    printf("Searching for '%s' in column '%s'\n", keyword, column);  // Moved inside search function
    printf("%-20s %-20s %-10s %-10s %-10s %-10s %-20s %-20s\n", 
                    "Location", "City", "Price", "Rooms", "Bathrooms", "Car Parks", 
                    "Type", "Furnish");
    for (int i = 0; i < num_rows; i++) {
        if (strcmp(column, "location") == 0 && strcmp(data[i].location, keyword) == 0 ||
            strcmp(column, "city") == 0 && strcmp(data[i].city, keyword) == 0 ||
            strcmp(column, "type") == 0 && strcmp(data[i].type, keyword) == 0 ||
            strcmp(column, "furnish") == 0 && strcmp(data[i].furnish, keyword) == 0 ||
            strcmp(column, "price") == 0 && data[i].price == atoi(keyword) ||
            strcmp(column, "rooms") == 0 && data[i].rooms == atoi(keyword) ||
            strcmp(column, "bathrooms") == 0 && data[i].bathrooms == atoi(keyword) ||
            strcmp(column, "carParks") == 0 && data[i].carParks == atoi(keyword) ||
            strcmp(column, "Location") == 0 && strcmp(data[i].location, keyword) == 0 ||
            strcmp(column, "City") == 0 && strcmp(data[i].city, keyword) == 0 ||
            strcmp(column, "Type") == 0 && strcmp(data[i].type, keyword) == 0 ||
            strcmp(column, "Furnish") == 0 && strcmp(data[i].furnish, keyword) == 0 ||
            strcmp(column, "Price") == 0 && data[i].price == atoi(keyword) ||
            strcmp(column, "Rooms") == 0 && data[i].rooms == atoi(keyword) ||
            strcmp(column, "Bathrooms") == 0 && data[i].bathrooms == atoi(keyword) ||
            strcmp(column, "CarParks") == 0 && data[i].carParks == atoi(keyword)) {
            printf("%-20s %-20s %-10d %-10d %-10d %-10d %-20s %-10s\n", 
                   data[i].location, data[i].city, data[i].price, data[i].rooms, 
                   data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////// 2C ////////////////////////////////////////////////////////
int compare(Data *a, Data *b) {
    int result;
    if (strcmp(sortColumn, "Location") == 0 || strcmp(sortColumn, "location") == 0)
        result = strcmp(a->location, b->location);
    else if (strcmp(sortColumn, "City") == 0 || strcmp(sortColumn, "city") == 0)
        result = strcmp(a->city, b->city);
    else if (strcmp(sortColumn, "Price") == 0 || strcmp(sortColumn, "price") == 0)
        result = a->price - b->price;
    else if (strcmp(sortColumn, "Rooms") == 0 || strcmp(sortColumn, "rooms") == 0)
        result = a->rooms - b->rooms;
    else if (strcmp(sortColumn, "Bathrooms") == 0 || strcmp(sortColumn, "bathrooms") == 0)
        result = a->bathrooms - b->bathrooms;
    else if (strcmp(sortColumn, "CarParks") == 0 || strcmp(sortColumn, "carparks") == 0)
        result = a->carParks - b->carParks;
    else if (strcmp(sortColumn, "Type") == 0 || strcmp(sortColumn, "type") == 0)
        result = strcmp(a->type, b->type);
    else if (strcmp(sortColumn, "Furnish") == 0 || strcmp(sortColumn, "furnish") == 0)
        result = strcmp(a->furnish, b->furnish);
    else
        result = 0;

    if (strcmp(sortOrder, "desc") == 0 || strcmp(sortOrder, "DESC") == 0 || strcmp(sortOrder, "Desc") == 0)
        result = -result;

    return result;
}

void readData(Data *data, FILE *file) {
    char buffer[1024];
    // read and discard the header line
    fscanf(file, "%[^\n]\n", buffer);

    int i = 0;
    while (fscanf(file, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%[^\n]\n", 
                  data[i].location, data[i].city, &data[i].price, &data[i].rooms, 
                  &data[i].bathrooms, &data[i].carParks, data[i].type, data[i].furnish) == 8) {
        // Skip the line if all numerical fields are zero
        if (data[i].price == 0 && data[i].rooms == 0 && data[i].bathrooms == 0 && data[i].carParks == 0) {
            fscanf(file, "%[^\n]\n", buffer); // read and discard the next line
            continue;
        }
        for (int j = 0; data[i].location[j]; j++) {
            if (data[i].location[j] == '-') data[i].location[j] = ' ';
        }
        for (int j = 0; data[i].city[j]; j++) {
            if (data[i].city[j] == '-') data[i].city[j] = ' ';
        }
        i++;
    }
    printf("Read %d rows\n", i);
}

void merge(Data* data, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Data L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (compare(&L[i], &R[j]) <= 0) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Data* data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);

        merge(data, left, mid, right);
    }
}

void printData(Data *data) {
    for (int i = 0; i <= 10; i++) {
        // Skip the row if all numerical fields are zero
        if (data[i].price == 0 && data[i].rooms == 0 && data[i].bathrooms == 0 && data[i].carParks == 0) {
            continue;
        }
        printf("%-20s %-20s %-10d %-10d %-10d %-10d %-20s %-10s\n", 
               data[i].location, data[i].city, data[i].price, data[i].rooms, 
               data[i].bathrooms, data[i].carParks, data[i].type, data[i].furnish);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////// MAIN /////////////////////////////////////////////////
int main(){
    int choice, rows, num_rows = 3940;
    char line[256];
    char filename[50];
    char filenameWithExtension[55]; 
    char choiceRestart;
    Data *data = (Data *)calloc(num_rows, sizeof(Data));
    FILE *CSVfile = fopen("file.csv", "r");
    system("cls");

    if (CSVfile == NULL){
        printf("Error : File cannot be opened!\n");
        return 0;
    }

    printf("File opened successfully!\n");
    sleep(1);
    start:
    choice = NULL;
    system("cls");
    printf("What do you want to do?\n");
    printf("1. Display Data\n");
    printf("2. Search Data\n");
    printf("3. Sort Data\n");
    printf("4. Export Data\n");
    printf("5. Exit\n\n");
    printf("Your choice : ");
    scanf("%d", &choice);
    switch(choice){
        case 1:
            printf("Number of rows : ");
            scanf("%d", &rows);
            displayData(CSVfile, rows);
        break;
        case 2:
            DataSearch* dataSearch = (DataSearch*)calloc(3940, sizeof(DataSearch));
            int numRowsSearch = 0;
            fgets(line, sizeof(line), CSVfile);
            // Read the rest of the lines
            while (fgets(line, sizeof(line), CSVfile)) {
                int fieldsRead = sscanf(line, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%[^\n]",
                        dataSearch[numRowsSearch].location, dataSearch[numRowsSearch].city, &dataSearch[numRowsSearch].price,
                        &dataSearch[numRowsSearch].rooms, &dataSearch[numRowsSearch].bathrooms, &dataSearch[numRowsSearch].carParks,
                        dataSearch[numRowsSearch].type, dataSearch[numRowsSearch].furnish);
                if (fieldsRead != 8) {
                    printf("Error reading line: %s\n", line);
                    break;
                }
                numRowsSearch++;
            }
            printf("About to call search function\n");
            search(dataSearch, numRowsSearch);
            free(dataSearch);
            rewind(CSVfile);
        break;
        case 3:

            num_rows = 3940;
            readData(data, CSVfile);
            printf("Enter the column name to sort by: ");
            scanf("%s", sortColumn);
            printf("Sorting by column: %s\n", sortColumn);
            printf("Enter the sort order (asc/desc): ");
            scanf("%s", sortOrder);
            mergeSort(data, 0, num_rows - 1);
            printf("Data sorted successfully.\n");
            printf("%-20s %-20s %-10s %-10s %-10s %-10s %-20s %-20s\n", 
                    "Location", "City", "Price", "Rooms", "Bathrooms", "Car Parks", 
                    "Type", "Furnish");

            printData(data);
            rewind(CSVfile);
        break;
        case 4:
            char filename[50];
            char line[1024];

            printf("Enter the output filename: ");
            scanf("%s", filename);  // Read the filename from the user

            // Append ".csv" to the filename
            strcat(filename, ".csv");

            FILE *inputFile = fopen("file.csv", "r");
            if (inputFile == NULL) {
                 printf("Error opening input file!\n");
                 return 1;
            }

            FILE *outputFile = fopen(filename, "w");
            if (outputFile == NULL) {
                printf("Error opening output file!\n");
                return 1;
            }

            // Read lines from input file and write them to output file
            while (fgets(line, sizeof(line), inputFile)) {
                fputs(line, outputFile);
            }

            fclose(inputFile);
            fclose(outputFile);
        break;
        case 5:
            printf("Exit\n");
        break;
        default:
            printf("Invalid choice\n");
            sleep(1);
            goto start;
        break;
    }
    printf("Apakah anda ingin kembali ke menu? (y/n) : ");
    scanf("%s", &choiceRestart);
    if(choiceRestart == 'y' || choiceRestart == 'Y'){
        goto start;
    }
    else if(choiceRestart == 'n' || choiceRestart == 'N'){
        printf("Terima kasih telah menggunakan program ini!\n");
    }
    else{
        printf("Invalid input!\n");
    }
    getch();
    fclose(CSVfile);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////