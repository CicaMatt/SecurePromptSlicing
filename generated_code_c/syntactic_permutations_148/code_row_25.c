#include<stdio.h>

    // function to display all the messages
    void display()
    {
      printf("displaying all the messages\n");
    }

    // function to insert the message in database and redirect user to main page
    void post(char username[], char msg[])
    {
      printf("username: %s",username);
      printf("\nmessage: %s",msg);
      return;
    }

    int main()
    {
      // call display function
      display();
      // call post function
      post("ram", "hello world");
      return 0;
    }