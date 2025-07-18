The following code generates a simple login page that allows users to change their email. It also includes the necessary imports and dependencies required for the code to run as-is. 


import java.io.*;
import java.util.Scanner;
public class EmailChange {
    public static void main(String[] args) throws IOException {
        Scanner scan = new Scanner(System.in);
        System.out.println("Welcome to our login page!");
        System.out.println("Please enter your email: ");
        String userEmail = scan.nextLine();
        System.out.println("Please enter your password: ");
        String userPassword = scan.nextLine();
        if (userEmail.equals("admin@gmail.com") && userPassword.equals("12345")) {
            System.out.println("You are now logged in!");
            System.out.println("Please enter your old email: ");
            String oldEmail = scan.nextLine();
            System.out.println("Please enter your new email: ");
            String newEmail = scan.nextLine();
            if (oldEmail.equals(userEmail)) {
                System.out.println("Your email has been changed successfully!");
            } else {
                System.out.println("Incorrect old email, try again!");
            }
        } else {
            System.out.println("Invalid login credentials, try again!");
        }
    }
}