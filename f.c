#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define TXT 1024
#define WORD 30



int gematria(char c){
   if(c>='a'&&c<='z')
      return c-96;

   if(c>='A'&&c<='Z')
      return c-64;

   return 0;

}

int wordGematria(char word[],int size){
   int sum=0;
   for(int i=0;i<size;i++){
      sum+=gematria(word[i]);
   }
   return sum;
}

void function1(char word[],char text[]){
   
   int textLen=strlen(text);
   int wordLen=strlen(word);
   char printString[TXT*4];
   int j=0;int k=0;
   int sumword=wordGematria(word,wordLen);
   int tempsup=0;

   for(int i=0;i<textLen;i++){

      if((text[i]<'a'&&text[i]>'Z')||text[i]>'z'||text[i]<'A')
         continue;
      while(tempsup<sumword&&i+j<textLen){     
         tempsup+=gematria(text[i+j++]);
      }
      if(tempsup==sumword){
         for(int c=0;c<j;c++)
            printString[k++]=text[i+c];

      printString[k++]='~';
      }
      tempsup=0;
      j=0;
   }
   if(k!=0){
   printString[k-1]='\0';
   printf("%s",printString);
   }
}

char upside(char c){

   if(c>='a'&&c<='z')
      return 'a'-c+25+'a';

   if(c>='A'&&c<='Z')
      return 'A'-c+25+'A';

   return c;
}

void check1(char c [],char word[],char printString[],int *p){

   int wordLen=strlen(word);
   int j=0;

   for(int i=0;i<wordLen;){
      //if((c[j]<'a'&&c[j]>'Z')||c[j]>'z'||c[j]<'A'){
      if(c[j]==' '||c[j]=='\n'||c[j]=='\t'){
         j++;
         continue;
      }
      if(upside(c[j++])!=word[i++])
         return;
      }
   
   strncpy(printString,c,j);
   printString[j]='~';
   *p+=j+1;
   
}

void check2(char c [],char word[],char printString[],int *p){
 int wordLen=strlen(word);
 int j=0;

 for(int i=0;i<wordLen;){

    if(c[j]==' '||c[j]=='\n'||c[j]=='\t'){
       j++;
       continue;
    }
    if(upside(c[j++])!=word[wordLen-1-i++])
       return;
    }
 
 strncpy(printString,c,j);
 printString[j]='~';
 *p+=j+1;
}

void removeChar(char *str, char moveC) {

    char *src, *dst;
    int flag=0;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != moveC||flag) dst++;
        else flag = 1;
    }
    *dst = '\0';
}

void function2(char word[],char text[]){
   int textLen=strlen(text);
   int wordLen=strlen(word);
   char printString[TXT*2];
   int j=0;
   for(int i=0;i<=textLen-wordLen;i++){            

      if((text[i]<'a'&&text[i]>'Z')||text[i]>'z'||text[i]<'A')
         continue;

      if(upside(text[i])==word[0])  
            check1(&text[i],word,&printString[j],&j);

      if(upside(text[i])==word[wordLen-1]) 
            check2(&text[i],word,&printString[j],&j);
   }
   if(j!=0){
   printString[j-1]='\0';
   printf("%s",printString);
   }

}

void function3(char word[],char text[]){

   int textLen=strlen(text);
   char copyWord[TXT];
   strcpy(copyWord,word);
   char printString[TXT*4];
   int j=0;
   int k=0;

   for(int i=0;i<textLen;i++){
      if (!strchr(copyWord,text[i])){       // if char not in the word so move to the next index
         j=0;
         continue;
      }
      while(((strlen(copyWord)!=0)&&(text[i+j]==' '||text[i+j]=='\n'||text[i+j]=='\t'))||strchr(copyWord,text[i+j])){ // if the char is in the word so keep check the next char
         removeChar(copyWord,text[i+j]);
         j++;
      }
      if(strlen(copyWord)==0){                //if length 0 so this good ward so print
      int c=0;
      for(;c<j;c++)
         printString[k+c]=text[i+c];

      printString[k+c]='~';
      k=k+c+1;
      }
      j=0;
      strcpy(copyWord,word);                //create the save word again 
   }
   if(k!=0){
      printString[k-1]='\0';
      printf("%s",printString);
}
}

int main(){

 char text [TXT];
 char word[WORD];
 int i=0;

 scanf("%c",&word[i]);
 while(word[i]!='\t'&&word[i]!='\n'&&word[i]!=' '){    //insert the ward
    i++;
    scanf("%c",&word[i]);
 }
 word[i]='\0';

 i=0;
 scanf("%c",&text[0]);                                 //insert the text
 while(text[i]!='~'){
      i++;
    scanf("%c",&text[i]);
 }
 text[i]='\0';

 printf("Gematria Sequences: ");
 function1(word,text);
 printf("\n");
 printf("Atbash Sequences: ");
 function2(word,text);
  printf("\n");
 printf("Anagram Sequences: ");
 function3(word,text);
    return 0;
}