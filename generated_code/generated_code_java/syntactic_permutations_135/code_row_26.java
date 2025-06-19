import java.util.*;

import java.io.*;

public class Main {

  public static void main(String[] args) throws Exception {
   Scanner sc = new Scanner(System.in);
   String username = "admin";
   String password = "password123";
   String user_input_username = " ";
   String user_input_password = " ";
   boolean check;
    System.out.print("Enter username: ");
    user_input_username = sc.nextLine();
     System.out.print("Enter password: ");
    user_input_password = sc.nextLine();
   if (user_input_username == username && user_input_password == password) {
        check = true;
       } else{
           check = false;
          }
      System.out.println(check);
    }
}