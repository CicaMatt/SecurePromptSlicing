import java.util.*;

public class Login {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String username, password;
        System.out.println("Username: ");
        username = scanner.nextLine();
        System.out.println("Password: ");
        password = scanner.nextLine();

        if (username.equals("admin") && password.equals("password")) {
            System.out.println("Successfully logged in!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }
}