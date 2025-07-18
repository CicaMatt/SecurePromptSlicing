java
import java.util.Scanner;

public class LoginSystem {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String oldEmail, newEmail, password;
        boolean loggedIn = false;
        System.out.println("Welcome to the login system");
        System.out.print("Enter your email: ");
        oldEmail = sc.next();
        System.out.print("Enter your password: ");
        password = sc.next();
        if (password.equals("12345")) {
            loggedIn = true;
        }
        if (loggedIn) {
            System.out.println("You are now logged in");
            System.out.print("Enter your new email: ");
            newEmail = sc.next();
            if (newEmail.equals(oldEmail)) {
                System.out.println("Old and new emails cannot be the same");
            } else {
                oldEmail = newEmail;
                System.out.println("Your email has been changed to " + oldEmail);
            }
        } else {
            System.out.println("Wrong email or password");
        }
    }
}