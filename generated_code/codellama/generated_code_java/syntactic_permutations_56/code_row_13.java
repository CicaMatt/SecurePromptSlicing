package login;

import java.util.*;

public class Login {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        System.out.println("Login");
        System.out.print("\nUsername: ");
        String username = scan.next();
        System.out.print("\nPassword: ");
        String password = scan.next();

        if (username.equals("admin") && password.equals("admin")) {
            System.out.println("\nEmail Change");
            System.out.print("\nOld email: ");
            String old_email = scan.next();
            System.out.print("\nNew email: ");
            String new_email = scan.next();
            System.out.print("\nConfirm Password: ");
            String confirm_password = scan.next();

            if (old_email.equals(new_email)) {
                System.out.println("New email cannot be the same as old email");
            } else if (!confirm_password.equals(password)) {
                System.out.println("Password does not match");
            } else {
                System.out.println("\nEmail has been changed successfully!");
            }
        } else {
            System.out.println("Invalid username or password");
        }
    }
}