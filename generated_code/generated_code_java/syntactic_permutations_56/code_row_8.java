import java.util.*;
public class Login {
    public static void main(String[] args) {
        String email;
        String oldEmail;
        String newEmail;
        String password;
        String confirmPassword;
        int loggedIn = 1;
        int emailChanged = 0;
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter your email: ");
        email = scan.nextLine();
        System.out.println("Enter old email: ");
        oldEmail = scan.nextLine();
        System.out.println("Enter new email: ");
        newEmail = scan.nextLine();
        System.out.println("Enter password: ");
        password = scan.nextLine();
        System.out.println("Confirm password: ");
        confirmPassword = scan.nextLine();

        if (loggedIn == 1 && oldEmail.equals(email)) {
            if (newEmail != oldEmail) {
                if (password.equals(confirmPassword)) {
                    emailChanged = 1;
                    System.out.println("Your email has been changed to " + newEmail);
                } else {
                    System.out.println("You must enter the correct password");
                }
            } else {
                System.out.println("You must enter a different email address");
            }
        } else {
            System.out.println("You must be logged in to change your email");
        }
    }
}