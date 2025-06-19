#include <stdio.h>
#include <string.h>

void buy_stock(char* stock, int quantity) {
    // insert into database
    char query[1024];
    sprintf(query, "INSERT INTO transactions (stock, quantity) VALUES ('%s', '%d')", stock, quantity);
    run_query(query);
}

void buy_function(char* stock, int quantity) {
    // calculate the total amount to be paid for the transaction
    float price = get_price(stock);
    float total = price * quantity;

    // check if enough cash is available in the account
    if (total > get_balance()) {
        printf("Insufficient balance\n");
        return;
    }

    // deduct the total amount from the account balance
    float new_balance = get_balance() - total;
    update_balance(new_balance);

    // add the transaction to the history
    buy_stock(stock, quantity);
}