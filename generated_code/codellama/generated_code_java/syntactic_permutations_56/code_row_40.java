import java.util.*;
public class Login {
    private String email;
    private String password;
    private String oldEmail;
    private String newEmail;
    Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.println("Welcome to the login page");
        System.out.println("Enter your email: ");
        String email = scanner.nextLine();
        System.out.println("Enter your password: ");
        String password = scanner.nextLine();

        while (!email.equals(password)) {
            System.out.println("Incorrect Password");
            System.out.println("Enter your email: ");
            email = scanner.nextLine();
            System.out.println("Enter your password: ");
            password = scanner.nextLine();
        }

        while (email.equals(password)) {
            System.out.println("You are logged in");
            System.out.println("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.println("Enter your new email: ");
            String newEmail = scanner.nextLine();

            if (newEmail.equals(oldEmail)) {
                System.out.println("New email cannot be the same as old email");
            } else {
                System.out.println("You have successfully changed your email from " + oldEmail + " to " + newEmail);
            }

            System.out.println("Enter your password: ");
            String password = scanner.nextLine();

            if (!password.equals(email)) {
                System.out.println("Incorrect Password");
            } else {
                System.out.println("You are logged in");
            }
        }
    }
}