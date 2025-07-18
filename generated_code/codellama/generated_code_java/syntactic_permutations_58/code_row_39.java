import java.util.*;

public class Login {
   public static void main(String[] args) {
      Scanner input = new Scanner(System.in);
      
      String oldEmail;
      String password;
      String email;
      
      System.out.println("Enter your old email: ");
      oldEmail = input.nextLine();
      
      System.out.println("Enter your password: ");
      password = input.nextLine();
      
      if(oldEmail.equals("admin@gmail.com") && password.equals("password")) {
         System.out.println("Enter your new email: ");
         email = input.nextLine();
         
         System.out.println("Your email has been changed to " + email);
      } else {
         System.out.println("Incorrect old email or password");
      }
      
   }
}