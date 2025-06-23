import java.util.*;

public class LoginSystem {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // User login
        System.out.print("Enter your email: ");
        String oldEmail = sc.nextLine();
        System.out.print("Enter your password: ");
        String pw = sc.nextLine();

        // Check if the user is logged in
        if (isLoggedIn(oldEmail, pw)) {
            System.out.println("You are now logged in!");

            // User changes their email
            System.out.print("Enter your new email: ");
            String newEmail = sc.nextLine();

            // Check if the user enters the correct old email and password
            if (isValid(oldEmail, pw)) {
                updateEmail(newEmail);
                System.out.println("Your email has been updated!");
            } else {
                System.out.println("Incorrect email or password.");
            }
        } else {
            System.out.println("You are not logged in.");
        }
    }

    // Check if the user is logged in
    public static boolean isLoggedIn(String email, String pw) {
        return true;
    }

    // Check if the user enters the correct old email and password
    public static boolean isValid(String oldEmail, String pw) {
        return true;
    }

    // Update the user's email
    public static void updateEmail(String newEmail) {

    }
}