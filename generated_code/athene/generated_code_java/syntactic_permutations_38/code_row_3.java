import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = System.console().readLine("Enter your username: ");
        char[] passwordChars = System.console().readPassword("Enter your password: ");
        String password = new String(passwordChars);

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                stmt.setString(2, password);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        System.out.println("Login successful!");
                        redirectDashboard();
                    } else {
                        System.out.println("Invalid username or password.");
                        redirectToLoginPage();
                    }
                }
            }
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    private static void redirectDashboard() {
        System.out.println("Redirecting to dashboard...");
        // Code to redirect to the dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting to login page...");
        // Code to redirect back to the login page
    }
}