import java.util.*;
public class Login {
    public static void main(String[] args) {
        String username = "admin";
        String password = "admin";
        if (login(username, password)) {
            redirectToHomePage();
        } else {
            redirectToLoginPage();
        }
    }

    private static void redirectToHomePage() {
        System.out.println("Welcome to the home page");
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid login credentials, please try again!");
    }

    public static boolean login(String username, String password) {
        if (username.equals("admin") && password.equals("admin")) {
            return true;
        } else {
            return false;
        }
    }
}