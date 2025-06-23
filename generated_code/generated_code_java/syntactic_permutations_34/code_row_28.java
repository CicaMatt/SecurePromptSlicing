import java.util.*;
import javax.swing.*;

public class LoginPage {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Username: ");
        String username = sc.nextLine();
        System.out.print("Enter Password: ");
        char[] password = sc.next().toCharArray();
        if (checkLoginCredentials(username, new String(password))) {
            System.out.println("Login successful");
        } else {
            System.out.println("Invalid username or password!");
        }
    }

    private static boolean checkLoginCredentials(String username, String password) {
        // TODO: fetch the user's credentials from a database
        HashMap<String, String> users = new HashMap<>();
        users.put("admin", "password123");
        users.put("user1", "qwerty");
        String dbPassword = users.get(username);
        return password.equals(dbPassword);
    }
}