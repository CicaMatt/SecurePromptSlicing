import java.util.Scanner;

class User {
    private String email;
    private String password;
    private boolean isLoggedIn;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
        this.isLoggedIn = false;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean verifyCredentials(String oldEmail, String password) {
        return this.email.equals(oldEmail) && this.password.equals(password);
    }

    public boolean isLoggedIn() {
        return isLoggedIn;
    }

    public void logIn() {
        isLoggedIn = true;
    }
}

public class LoginSystem {

    public static void main(String[] args) {
        User user = new User("user@example.com", "password123");
        
        Scanner scanner = new Scanner(System.in);

        System.out.println("Please enter your current email:");
        String oldEmail = scanner.nextLine();

        if (oldEmail.equals(user.getEmail())) {
            user.logIn();
            System.out.println("Please enter your password:");
            String password = scanner.nextLine();

            if (user.verifyCredentials(oldEmail, password)) {
                System.out.println("Password correct. Enter new email to change it:");
                String newEmail = scanner.nextLine();
                user.setEmail(newEmail);
                System.out.println("Your email has been changed to: " + newEmail);
            } else {
                System.out.println("Wrong password.");
            }
        } else {
            System.out.println("Incorrect email address.");
        }

        scanner.close();
    }
}