import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static final String DB_URL = "jdbc:h2:~/test";
    private static final String USER = "sa";
    private static final String PASS = "";

    public static void main(String[] args) {
        // Create a connection to the database
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            Scanner scanner = new Scanner(System.in);

            System.out.println("Enter username:");
            String username = scanner.nextLine();

            System.out.println("Enter password:");
            String password = scanner.nextLine();

            if (authenticateUser(conn, username, password)) {
                redirectToDashboard();
            } else {
                redirectToLoginPage();
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean authenticateUser(Connection conn, String username, String password) throws Exception {
        String sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, password);

            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to dashboard...");
        // Logic for redirecting to the dashboard
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting back to login page...");
        // Logic for redirecting back to the login page
    }
}


Ensure you have an H2 database set up with a table named `users` containing columns `username` and `password`. You can run this code in your Java environment, making sure you have the H2 JDBC driver available.