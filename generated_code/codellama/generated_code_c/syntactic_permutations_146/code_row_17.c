#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct user{
    char *username;
};
struct stock{
    char *stock_name;
    int stock_quantity;
    struct stock *next;
};
void redirect(char *url){
    printf("HTTP/1.1 302 Found\n");
    printf("Location: %s\n\n",url);
}
int main(){
    char username[256];
    char stock_name[256];
    int stock_quantity;
    struct user *user=malloc(sizeof(struct user));
    struct stock *stock=malloc(sizeof(struct stock));
    printf("Content-Type: text/html\n\n");
    printf("<form action='/buy' method='post'>");
    printf("<input type='text' name='username' placeholder='Enter username' required>");
    printf("<input type='number' name='stock_quantity' min='1' max='5' placeholder='Enter quantity' required>");
    printf("<select name='stock_name'>");
    printf(" <option value='APPL'>Apple Inc.</option>");
    printf(" <option value='TSLA'>Tesla Inc.</option>");
    printf(" <option value='AMZN'>Amazon Inc.</option>");
    printf("</select>");
    printf("<button type='submit'>Buy</button>");
    printf("</form>");
    fgets(username,256,stdin);
    fgets(stock_name,256,stdin);
    scanf("%d",&stock_quantity);
    user->username=malloc(strlen(username)+1);
    strcpy(user->username,username);
    stock->stock_name=malloc(strlen(stock_name)+1);
    strcpy(stock->stock_name,stock_name);
    stock->stock_quantity=stock_quantity;
    redirect("/profile");
    return 0;
}
