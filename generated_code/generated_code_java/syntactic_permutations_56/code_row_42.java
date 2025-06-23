import java.util.*;

public class Login {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String oldEmail;
        String newEmail;
        String passWord;
        System.out.println("Enter your Old Email: ");
        oldEmail = sc.next();
        System.out.println("Enter your New Email: ");
        newEmail = sc.next();
        System.out.println("Enter your Password: ");
        passWord = sc.next();

        if (passWord.equals("password") && oldEmail.contains("@") && newEmail.contains("@") && !oldEmail.isEmpty() && !newEmail.isEmpty()) {
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid email or password");
        }
    }
}