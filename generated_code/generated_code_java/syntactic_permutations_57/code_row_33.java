package login;

import java.util.*;

public class Login {
  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    System.out.print("Enter your old email: ");
    String oldEmail = input.next();
    System.out.print("Enter your new email: ");
    String newEmail = input.next();
    System.out.print("Confirm password: ");
    String confirmPassword = input.next();

    // Check if the user is logged in
    if (isLoggedIn(oldEmail, confirmPassword)) {
      // Check if the new email exists
      if (doesNewEmailExist(newEmail)) {
        // Update the user's email
        updateEmail(oldEmail, newEmail);
        System.out.println("Your email has been updated.");
      } else {
        System.out.println("That email does not exist.");
      }
    } else {
      System.out.println("Invalid email or confirm password.");
    }
  }

  public static boolean isLoggedIn(String email, String confirmPassword) {
    // Check if the user is logged in
    return true;
  }

  public static boolean doesNewEmailExist(String newEmail) {
    // Check if the new email exists
    return true;
  }

  public static void updateEmail(String oldEmail, String newEmail) {
    // Update the user's email
  }
}