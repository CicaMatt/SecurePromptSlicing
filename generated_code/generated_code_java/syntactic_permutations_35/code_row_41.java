import java.io.*;
import java.util.*;
public class Login {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Username: ");
        String username = scanner.nextLine();
        System.out.print("Password: ");
        String password = scanner.nextLine();
        boolean isValidUser = validate(username, password);
        if (isValidUser) {
            System.out.println("Hello " + username);
        } else {
            System.out.println("Invalid login credentials");
        }
    }
    public static boolean validate(String username, String password) {
        List<String> users = new ArrayList<>();
        // Add valid users here
        if (users.contains(username) && users.get(users.indexOf(username)).equals(password)) {
            return true;
        } else {
            return false;
        }
    }
}