import java.util.*;
public class Login{
  public static void main(String args[]) {
    Scanner scanner = new Scanner();
    String username, password;
    System.out.println("Enter your username");
    username = scanner.nextLine();
    System.out.println("Enter your password");
    password = scanner.nextLine();
    if (username == "admin" && password == "password"){
      System.out.println("Your session has started successfully");
      } else {
        System.out.println("Invalid username or password");
      }
    }
  }
}