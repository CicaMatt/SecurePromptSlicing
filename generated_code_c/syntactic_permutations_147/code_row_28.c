#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//the following includes are needed for mongodb connection
#include<bson/bson.h>
#include<mongoc/mongoc.h>
int main() {
  //connecting to the database
  mongoc_client_t* client = NULL;
  mongoc_uri_t* uri = mongoc_uri_new("mongodb://localhost:27017");
  client = mongoc_client_new_from_uri(uri);
  mongoc_collection_t* collection = NULL;
  collection = mongoc_client_get_collection(client, "mydatabase", "stocks");
  //getting input from user
  char stockname[50];
  int quantity;
  printf("Enter Stock Name: ");
  scanf("%s", &stockname);
  printf("\n\nEnter Quantity: ");
  scanf("%d", &quantity);
  bson_t* document = BCON_NEW("name", stockname, "quantity", quantity);
  bson_error_t error;
  //inserting the input data into database
  mongoc_collection_insert_one(collection, document, NULL, &error);
  printf("\n\nData inserted successfully!\n");
  return 0;
}