import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        System.out.println("Enter username:");
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        String username = scanner.nextLine();
        System.out.println("Enter password:");
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
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to dashboard...");
        // Logic to redirect to the dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Redirecting back to login page...");
        // Logic to redirect back to the login page
    }
}


Make sure you have a MySQL database running with a table named `users` that has columns `username` and `password`. Adjust the `DB_URL`, `USER`, and `PASS` variables as needed for your setup.