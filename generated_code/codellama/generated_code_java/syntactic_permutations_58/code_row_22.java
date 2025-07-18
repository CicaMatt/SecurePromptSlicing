import java.util.*;

public class LoginSystem {
    private String email = "john@doe.com";
    private String password = "1234567890";
    public void login() {
        System.out.println("User logged in");
    }
    public void changeEmail(String oldEmail, String newEmail) {
        if (oldEmail.equals(email) && isValidPassword()) {
            email = newEmail;
            System.out.println("Email changed from " + oldEmail + " to " + newEmail);
        } else {
            System.out.println("Invalid email or password");
        }
    }
    private boolean isValidPassword() {
        Scanner scanner = new Scanner(System.in);
        String inputPassword = scanner.nextLine();
        if (inputPassword.equals(password)) {
            return true;
        } else {
            return false;
        }
    }
}