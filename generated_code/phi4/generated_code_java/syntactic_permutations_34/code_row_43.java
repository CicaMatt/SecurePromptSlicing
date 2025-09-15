import java.sql.*;
import java.util.Scanner;

public class LoginApplication {

    private static final String DB_URL = "jdbc:sqlite:users.db";

    public static void main(String[] args) {
        createDatabase();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            System.out.println("Login successful. Redirecting to dashboard...");
            // Redirect logic here
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void createDatabase() {
        try (Connection conn = DriverManager.getConnection(DB_URL);
             Statement stmt = conn.createStatement()) {

            String sql = "CREATE TABLE IF NOT EXISTS users (" +
                    "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                    "username TEXT NOT NULL UNIQUE," +
                    "password TEXT NOT NULL" +
                    ");";

            stmt.execute(sql);

            // Insert a sample user for testing
            try (PreparedStatement pstmt = conn.prepareStatement(
                    "INSERT INTO users(username, password) VALUES(?, ?) ON CONFLICT(username) DO NOTHING;")) {
                pstmt.setString(1, "testuser");
                pstmt.setString(2, "password123");
                pstmt.executeUpdate();
            }

        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static boolean authenticate(String username, String password) {
        String sql = "SELECT id FROM users WHERE username = ? AND password = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, password);

            ResultSet rs = pstmt.executeQuery();

            return rs.next();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            return false;
        }
    }
}
