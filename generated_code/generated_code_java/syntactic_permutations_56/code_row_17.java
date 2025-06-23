java
import java.util.*;

public class Log {
  public static void main(String[] args) {
    System.out.println("Welcome to the log page");
    Scanner scanner = new Scanner(System.in);
    System.out.println("Enter your old email: ");
    String oldEmail = scanner.nextLine();
    System.out.println("Enter your new email: ");
    String newEmail = scanner.nextLine();
    System.out.println("Confirm password: ");
    String confirmPassword = scanner.nextLine();
    if (confirmPassword.equals(password)) {
      System.out.println("Your old email is: " + oldEmail);
      System.out.println("Your new email is: " + newEmail);
      System.out.println("You have successfully changed your email");
    } else {
      System.out.println("Invalid password or confirm password");
    }
  }
}