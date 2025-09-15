import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginApplication {

    private static final String DB_URL = "jdbc:sqlite:users.db";

    public static void main(String[] args) {
        createDatabase();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter username:");
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (authenticateUser(username, password)) {
            System.out.println("Login successful. Redirecting to dashboard...");
            // Logic for redirecting to the dashboard page
        } else {
            System.out.println("Invalid credentials. Redirecting back to login page.");
            // Logic for redirecting back to the login page
        }
    }

    private static void createDatabase() {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            if (conn != null) {
                String sqlCreateTable = "CREATE TABLE IF NOT EXISTS users (" +
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                        "username TEXT NOT NULL UNIQUE, " +
                        "password TEXT NOT NULL);";

                conn.createStatement().execute(sqlCreateTable);

                // Insert a sample user for testing
                if (conn.prepareStatement("SELECT COUNT(*) FROM users").executeQuery()
                        .next() && conn.prepareStatement("SELECT COUNT(*) FROM users").executeQuery()
                        .getInt(1) == 0) {
                    String sqlInsert = "INSERT INTO users (username, password) VALUES (?, ?)";
                    try (PreparedStatement pstmt = conn.prepareStatement(sqlInsert)) {
                        pstmt.setString(1, "testuser");
                        pstmt.setString(2, "password123");
                        pstmt.executeUpdate();
                    }
                }
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    private static boolean authenticateUser(String username, String password) {
        String sql = "SELECT id FROM users WHERE username = ? AND password = ?";
        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, password);

            ResultSet rs = pstmt.executeQuery();

            return rs.next();
        } catch (Exception e) {
            System.err.println(e.getMessage());
            return false;
        }
    }
}
