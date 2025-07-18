import java.io.*;  // Importing java library for handling input/output operations
import java.util.*; // Importing java library for scanner class

//Main function starts here
public class Login{
   public static void main(String args[]) throws IOException {
      String username;
      String password;
      
      //Creating a Scanner object to get input from user
      Scanner s = new Scanner(System.in);
      
      System.out.println("Enter your username");
      username = s.nextLine();
      
      System.out.println("Enter your password");
      password = s.nextLine();
      
      //Checking if the entered username and password are correct
      if(username.equals("admin") && password.equals("password")){
         System.out.println("Session initiated...Redirecting to session page");
      }else{
         System.out.println("The entered username or password is incorrect");
      }
   }
}