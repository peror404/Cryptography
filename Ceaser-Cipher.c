#include<stdio.h>
#include<string.h>

//ENCRYPTION
void ceaser_encrypt(char* plaintext, int key, char* Ciphertext){


int i;
for (i=0; plaintext[i] != '\0'; i++)
{
    char ch= plaintext[i];
    if (ch >= 'A' && ch<= 'Z'){

        Ciphertext[i] = ((ch - 'A' + key)%26) + 'A';
        printf("Encrypted text is  plaintext[%d]='%c' , ciphertext[%d]='%c' \n", i,ch,i,Ciphertext[i]);
    }
    else {
        Ciphertext[i]=ch;
    }
   
}
 Ciphertext[i]= '\0';

}

//DECRYPTION
void ceaser_decrypt(char* ciphertext, int key, char* decrypted_text) {

int i;
for(i=0; ciphertext[i] != '\0'; i++){
    char ch = ciphertext[i];
    if (ch >= 'A' && ch <= 'Z') {
        decrypted_text[i] = ((ch - 'A'- key +26)% 26) + 'A';
        printf("Decrypting : ciphertext[%d]='%c', decrypted_text[%d]='%c' \n " ,i,ch,i,decrypted_text[i]);
    }
    else {
        decrypted_text[i]=ch;
    }
}
 decrypted_text[i]='\0';
}


//BRUTEFORCE

void brute_force(char* ciphertext){
    char decrypted_text[100];
    for(int key=0; key < 26; key++){
        ceaser_decrypt(ciphertext, key, decrypted_text);
        printf("Key %d: %s\n", key,decrypted_text);
    }
}

int main(){
    char plaintext[100],Ciphertext[100], decrypted_text[100];
    int key;
    printf("Enter the plaintext (UPPER CASE ONLY):");
    fgets(plaintext,sizeof(plaintext), stdin);

    printf("Enter the Key (0-25) : ");
    scanf("%d", &key);

    ceaser_encrypt(plaintext,key, Ciphertext);
    printf("Encrypted Text: %s\n", Ciphertext);

    printf("\n Attempting brute_force attack");
    brute_force(Ciphertext);

    return 0;
}