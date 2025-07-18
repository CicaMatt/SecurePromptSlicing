import java.util.*;
    
    public class LoginPage {
      public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter Username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter Password: ");
        String password = scanner.nextLine();
        
        if (username.equals("user") && password.equals("password")) {
          System.out.println("Redirecting to Session Page...");
        } else {
          System.out.println("Username or password is incorrect.");
        }
      }
    }