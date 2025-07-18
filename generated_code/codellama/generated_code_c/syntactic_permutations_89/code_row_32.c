#include <stdio.h> 
 #include <stdlib.h> 
 #include <string.h> 
 #include <unistd.h> 
 #include <sys/types.h> 
 #include <sys/socket.h> 
 #include <netinet/in.h> 
 #include <arpa/inet.h> 

 // Function to calculate price of product code 
 double getPrice(int productCode){
    if (productCode == 1) {
      return 50.0;
    } else if (productCode == 2) {
      return 30.0;
    } else if (productCode == 3) {
      return 40.0;
    } else {
      return 0.0;
    }
 } 

 // Function to calculate total price for product code and quantity 
 double calculateTotalPrice(int productCode, int quantity){
    return getPrice(productCode) * quantity;
 } 

 // Main function to run web app 
 int main() { 
   // Create socket 
   int server_fd, new_socket; 
   struct sockaddr_in address; 
   int opt = 1; 
   int addrlen = sizeof(address); 
   char buffer[1024] = {0}; 

   // Creating socket file descriptor 
   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
      perror("socket failed"); 
      exit(EXIT_FAILURE); 
   } 

   // Forcefully attaching socket to the port 8080 
   if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
      perror("setsockopt"); 
      exit(EXIT_FAILURE); 
   }

   // Address of the server 
   address.sin_family = AF_INET; 
   address.sin_addr.s_addr = INADDR_ANY; 
   address.sin_port = htons(8080); 

   // Forcefully attaching socket to the port 8080 
   if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) { 
      perror("bind failed"); 
      exit(EXIT_FAILURE); 
   } 

   // Listen to the socket 
   if (listen(server_fd, 3) < 0) { 
      perror("listen"); 
      exit(EXIT_FAILURE); 
   } 

   while(1){
      printf("\nNew Iteration...\n");

      // Accept the incoming connection 
      if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { 
         perror("accept"); 
         exit(EXIT_FAILURE); 
      } 
      
      // Read data from the socket 
      read(new_socket , buffer, 1024); 
      
      int productCode = atoi(buffer[8]);
      int quantity = atoi(buffer[35]);
      
      printf("Product Code: %d\n", productCode);
      printf("Quantity: %d\n", quantity);
      
      // Send the response to client 
      char *message = "Total price for product code and quantity is ";
      double totalPrice = calculateTotalPrice(productCode, quantity);
      strcat(message, &totalPrice);
      write(new_socket , message, strlen(message));

      // Close the socket 
      close(new_socket);  
   } 
   return 0; 
}