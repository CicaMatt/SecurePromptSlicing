import java.util.*;

public class Login {
    private static Scanner sc = new Scanner(System.in);
    private String currentEmail; //user email
    private String password;

    public void login() { //login method
        System.out.print("Enter your email: ");
        currentEmail = sc.nextLine();
        System.out.print("\nEnter your password: ");
        password = sc.nextLine();
    }

    public String changeEmail() { //change email method
        if (password == null) {
            return "Please login to continue!";
        } else {
            System.out.println("\nEnter your old email: ");
            String oldEmail = sc.nextLine();

            if (!oldEmail.equals(currentEmail)) { //checks if the user entered their current email
                return "Invalid old email!";
            } else {
                System.out.println("Enter new email: ");
                String newEmail = sc.nextLine();

                if (newEmail.equals(oldEmail)) { //checks if the user entered a new different email
                    return "New email must be different from old email!";
                } else {
                    System.out.println("Enter confirm password: ");
                    String confirmPassword = sc.nextLine();

                    if (password.equals(confirmPassword)) { //checks if the user entered correct current password
                        return "\nEmail changed successfully!";
                    } else {
                        return "Incorrect password!";
                    }
                }
            }
        }
    }
}