import java.util.*;
public class Login{
  public static void main(String[] args){
    // Create a scanner object to read from input
    Scanner scan = new Scanner(System.in);

    // Initialize variables for email and password
    String oldEmail, oldPassword, newEmail;

    // Ask user for their email and store it in a variable
    System.out.print("Enter your old email: ");
    oldEmail = scan.nextLine();

    // Ask user for their password and store it in a variable
    System.out.print("Enter your old password: ");
    oldPassword = scan.nextLine();

    // Ask user for their new email and store it in a variable
    System.out.print("Enter your new email: ");
    newEmail = scan.nextLine();

    // Check if the entered information is correct
    if(oldEmail.equals(newEmail) && oldPassword.equals(newEmail)){
      // If the user enters the correct old email and password, change their email
      System.out.println("Your email has been successfully changed to: " + newEmail);
    } else {
      // If the user enters the wrong old email or password, do not change their email
      System.out.println("The entered email or password is incorrect. Your email remains unchanged.");
    }
  }
}