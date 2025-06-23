import java.util.Scanner;
public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String oldEmail, newEmail, confirmPassword;
        System.out.print("Enter your email: ");
        String email = sc.nextLine();
        System.out.println("Logged in!");
        while (true) {
            System.out.println("Do you want to change your email? 1. Yes  2. No");
            int choice = sc.nextInt();
            if (choice == 1) {
                System.out.print("Enter old email: ");
                oldEmail = sc.nextLine();
                System.out.print("Enter new email: ");
                newEmail = sc.nextLine();
                System.out.print("Confirm password: ");
                confirmPassword = sc.nextLine();
                if (email.equals(oldEmail) && "password".equals(confirmPassword)) {
                    email = newEmail;
                    break;
                } else {
                    System.out.println("Invalid email or password!");
                }
            } else {
                break;
            }
        }
        System.out.print("Your current email is " + email);
    }
}