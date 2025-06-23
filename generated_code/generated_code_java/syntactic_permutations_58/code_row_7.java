import java.util.Scanner;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String email;
        String oldEmail;
        System.out.println("Enter your email: ");
        email = sc.nextLine();
        while (true) {
            System.out.println("You must be logged in to change your email.");
            System.out.println("Enter your old email and confirm password: ");
            oldEmail = sc.nextLine();
            String pass = sc.nextLine();
            if (oldEmail.equals(email) && pass.equals("password")) {
                System.out.println("You are now logged in.");
                break;
            } else {
                System.out.println("Invalid email or password");
                continue;
            }
        }
        System.out.println("Enter your new email: ");
        String newEmail = sc.nextLine();
        if (newEmail == oldEmail) {
            System.out.println("New email must be different from the old one.");
            return;
        } else {
            email = newEmail;
            System.out.println("Your email has been changed to " + email);
        }
    }
}