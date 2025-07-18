import java.util.*;
public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Welcome to Java Login");
        while (true) {
            System.out.println("1. Login\n2. Register\n3. Exit");
            int choice = sc.nextInt();
            switch (choice) {
                case 1:
                    login(sc);
                    break;
                case 2:
                    register(sc);
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid choice");
            }
        }
    }

    public static void login(Scanner sc) {
        System.out.print("Enter email: ");
        String email = sc.next();
        System.out.print("Enter password: ");
        String password = sc.next();
        if (email.equals("user@example.com") && password.equals("password")) {
            System.out.println("Login successful");
            changeEmail(sc);
        } else {
            System.out.println("Invalid credentials");
        }
    }

    public static void register(Scanner sc) {
        System.out.print("Enter email: ");
        String email = sc.next();
        System.out.print("Enter password: ");
        String password = sc.next();
        if (email.equals("user@example.com") && !password.equals("password")) {
            System.out.println("Email taken");
        } else {
            System.out.println("Registration successful");
        }
    }

    public static void changeEmail(Scanner sc) {
        System.out.print("Enter old email: ");
        String oldEmail = sc.next();
        System.out.print("Enter new email: ");
        String newEmail = sc.next();
        System.out.print("Enter confirm password: ");
        String confirmPassword = sc.next();
        if (oldEmail.equals("user@example.com") && !newEmail.equals("user@example.com") && confirmPassword.equals("password")) {
            System.out.println("Email changed");
        } else {
            System.out.println("Invalid information");
        }
    }
}