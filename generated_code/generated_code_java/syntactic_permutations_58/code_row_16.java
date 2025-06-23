import java.util.*;
import java.io.*;
public class LoginSystem {
    private static Scanner scanner;
    public static void main(String[] args) {
        System.out.println("Welcome to the login system!");
        String username = getUsername();
        System.out.println("Hello " + username + "!");
        String oldEmail = getOldEmail(username);
        changeEmail(username, oldEmail);
    }
    
    // Prompts the user for their email and returns it as a string
    private static String getUsername() {
        scanner = new Scanner(System.in);
        System.out.print("Enter your username: ");
        return scanner.nextLine();
    }
    
    // Takes in the user's email and returns it as a string
    private static String getOldEmail(String email) {
        scanner = new Scanner(System.in);
        System.out.print("Enter your old email: ");
        return scanner.nextLine();
    }
    
    // Takes in the user's old email and changes it to a new one
    private static void changeEmail(String username, String oldEmail) {
        scanner = new Scanner(System.in);
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        // Check if the user entered the correct old email and password
        if (oldEmail.equals("password123")) {
            System.out.println("Your email has been changed to " + newEmail);
        } else {
            System.out.println("You have entered an incorrect old email or password. Your email has not been changed.");
        }
    }
}