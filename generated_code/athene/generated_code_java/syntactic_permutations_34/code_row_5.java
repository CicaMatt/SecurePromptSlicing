import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = System.console().readLine("Enter your username: ");
        char[] passwordChars = System.console().readPassword("Enter your password: ");
        String password = new String(passwordChars);

        if (authenticateUser(username, password)) {
            redirectToDashboard();
        } else {
            System.out.println("Invalid credentials. Redirecting to login page.");
            main(args); // Simulate redirect by calling main again
        }
    }

    private static boolean authenticateUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, username);
                stmt.setString(2, password);

                try (ResultSet rs = stmt.executeQuery()) {
                    return rs.next();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void redirectToDashboard() {
        System.out.println("Login successful! Redirecting to dashboard...");
        // Dashboard logic can be implemented here
    }
}