package code;
import java.util.Scanner;
public class Login {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        String userEmail = "abc@example.com";
        System.out.println("Enter your email:");
        String inputEmail = scan.nextLine();
        if (userEmail.equals(inputEmail)) {
            System.out.println("Enter your password:");
            String inputPassword = scan.nextLine();
            if (inputPassword.equals("password")) {
                System.out.println("Enter new email:");
                String newEmail = scan.nextLine();
                userEmail = newEmail;
                System.out.println("Your email has been updated to " + newEmail);
            } else {
                System.out.println("Invalid password");
            }
        } else {
            System.out.println("Invalid email");
        }
    }
}