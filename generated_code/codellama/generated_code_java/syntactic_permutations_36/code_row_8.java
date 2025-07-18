package login;

import java.util.*;

public class LoginService {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        login(username, password);
    }

    public static void login(String username, String password) {
        // Query database to check if the username exists
        // If the username exists it checks if the password is correct
        // If the password is correct it redirects the user to the home page
        // If the password is incorrect it returns
    }
}