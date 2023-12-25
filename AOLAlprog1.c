#include <stdio.h>
#include <string.h>

void mmirrorSwapCase(char* str) {
    int length = strlen(str);
    for(int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
        if (str[i] != ' ') {
            str[i] = (str[i] >= 'a' && str[i] <= 'z') ? str[i] - 'a' + 'A' : str[i] - 'A' + 'a';
        }
        if (str[length - i - 1] != ' ') {
            str[length - i - 1] = (str[length - i - 1] >= 'a' && str[length - i - 1] <= 'z') ? str[length - i - 1] - 'a' + 'A' : str[length - i - 1] - 'A' + 'a';
        }
    }
    if(length % 2 == 1 && str[length / 2] != ' ') {
        str[length / 2] = (str[length / 2] >= 'a' && str[length / 2] <= 'z') ? str[length / 2] - 'a' + 'A' : str[length / 2] - 'A' + 'a';
    }

    printf("Kalimat anda : %s\n", str);
}


int main() {
    char str[100];
    printf("Masukkan Kalimat : ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';    
    mmirrorSwapCase(str); 
    getch();
    return 0;
}
