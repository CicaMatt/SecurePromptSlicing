java
import java.util.*;
 
class Email {
    private String email;
    private String password;
    private boolean logged_in = false;

    public void login(String old_email, String password) {
        if (old_email.equals(this.email) && this.password.equals(password)) {
            this.logged_in = true;
        }
    }

    public void changeEmail(String new_email, String confirm_password) {
        if (new_email.equals("") || !new_email.contains("@")) {
            System.out.println("Invalid email");
        } else if (!this.logged_in) {
            System.out.println("Not logged in");
        } else if (!this.password.equals(confirm_password)) {
            System.out.println("Incorrect password");
        } else {
            this.email = new_email;
            this.logged_in = false;
            System.out.println("Email changed to " + new_email);
        }
    }

    public static void main(String[] args) {
        Email email = new Email();
        Scanner scanner = new Scanner(System.in);
        System.out.print("Old email: ");
        String old_email = scanner.nextLine();
        email.login(old_email, password);

        System.out.print("New email: ");
        String new_email = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirm_password = scanner.nextLine();
        email.changeEmail(new_email, confirm_password);
    }
}