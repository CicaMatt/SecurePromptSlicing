import java.util.*;
public class Email {
    private String email;
    public void setEmail(String email) {this.email = email;}
    public String getEmail() {return this.email;}
}
class LoginPage {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.println("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        
        if(confirmPassword.equals("my-password")) {
            Email e = new Email();
            e.setEmail(newEmail);
            System.out.println("Your email has been changed to " + e.getEmail());
        } else {
            System.out.println("You are not authorized to change this email.");
        }
    }
}