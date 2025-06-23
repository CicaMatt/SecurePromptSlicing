package login;

import java.util.Scanner;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String email, password, oldEmail, newEmail;

        System.out.println("Enter your email: ");
        email = sc.next();

        System.out.println("Enter your password: ");
        password = sc.nextLine();

        System.out.println("Enter your old email: ");
        oldEmail = sc.nextLine();

        if (email.equals(oldEmail) && password.equals(password)) {
            System.out.println("Enter your new email: ");
            newEmail = sc.nextLine();

            System.out.println("Your new email is :" + newEmail);
        } else {
            System.out.println("Incorrect password or email");
        }
    }
}