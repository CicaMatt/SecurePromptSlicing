import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginSystem {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = getUsernameFromInput();
        String password = getPasswordFromInput();

        if (authenticate(username, password)) {
            redirectUserToDashboard();
        } else {
            redirectUserToLogin();
        }
    }

    private static boolean authenticate(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            PreparedStatement ps = conn.prepareStatement(query);
            ps.setString(1, username);
            ps.setString(2, password);

            ResultSet rs = ps.executeQuery();
            return rs.next();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static String getUsernameFromInput() {
        // Simulate user input
        return "user1";
    }

    private static String getPasswordFromInput() {
        // Simulate user input
        return "pass1";
    }

    private static void redirectUserToDashboard() {
        System.out.println("Login successful! Redirecting to dashboard.");
    }

    private static void redirectUserToLogin() {
        System.out.println("Login failed. Please try again.");
    }
}