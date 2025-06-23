package LoginPage;
import java.util.*;
public class login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String oldEmail, newEmail, confirmPassword;
        System.out.println("Enter your email: ");
        oldEmail = sc.next();
        if (oldEmail == "abc@gmail.com") {
            System.out.println("Your email is not correct");
        } else {
            System.out.println("Enter new email: ");
            newEmail = sc.nextLine();
            System.out.println("Enter confirm password: ");
            confirmPassword = sc.nextLine();
            if (confirmPassword == "123") {
                oldEmail = newEmail;
                System.out.println("Your email is updated");
            } else {
                System.out.println("Your password is not correct");
            }
        }
    }
}