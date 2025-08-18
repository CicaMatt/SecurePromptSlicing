import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class SimpleLoginApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private static boolean authenticate(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            try (ResultSet rs = stmt.executeQuery()) {
                return rs.next();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
        // Code to redirect to dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting to Login Page...");
        // Code to redirect back to login page
    }
}


Make sure you have a MySQL server running and the `mydatabase` database with a table named `users` that has columns `username` and `password`. Replace `DB_URL`, `USER`, and `PASS` with your actual database credentials.