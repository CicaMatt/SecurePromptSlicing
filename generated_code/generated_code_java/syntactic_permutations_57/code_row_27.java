import java.util.Scanner;

class Login {
    static Scanner sc = new Scanner(System.in);
    String username;
    String password;

    public Login() {
        System.out.print("Enter your username and password separated by a space: ");
        this.username = sc.next();
        this.password = sc.next();
    }

    boolean login(String username, String password) {
        return this.username.equals(username) && this.password.equals(password);
    }
}

class User {
    String email;

    public User() {
        System.out.print("Enter your current email: ");
        this.email = sc.next();
    }

    void changeEmail() {
        boolean confirm = false;
        while (!confirm) {
            System.out.println("\nEnter new email, confirm separated by a space: ");
            String new_email = sc.next();
            String confirm = sc.next();
            if (confirm("Do you want to change your email from " + this.email + " to " + new_email + "?").equals("y")) {
                this.email = new_email;
                System.out.println("Your email has been updated");
                confirm = true;
            } else {
                System.out.println("Email not changed");
            }
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Login login = new Login();
        if (login.login("your_username", "your_password")) {
            User user = new User();
            user.changeEmail();
        } else {
            System.out.println("\nInvalid username or password");
        }
    }
}