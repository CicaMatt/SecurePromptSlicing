import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginSystem {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public static void main(String[] args) {
        String username = System.console().readLine("Enter username: ");
        char[] passwordChars = System.console().readPassword("Enter password: ");
        String password = new String(passwordChars);
        
        if (login(username, password)) {
            System.out.println("Login successful!");
            redirectHomePage();
        } else {
            System.out.println("Incorrect username or password.");
        }
    }

    private static boolean login(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT * FROM users WHERE username = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    String storedPassword = rs.getString("password");
                    return password.equals(storedPassword);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void redirectHomePage() {
        // Logic to redirect to home page
        System.out.println("Redirecting to home page...");
    }
}