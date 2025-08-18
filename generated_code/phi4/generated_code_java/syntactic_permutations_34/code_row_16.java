import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Simulate user input
        String username = "testUser";
        String password = "testPassword";

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private static boolean authenticate(String username, String password) {
        String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, password);

            ResultSet rs = pstmt.executeQuery();

            return rs.next(); // Returns true if a record is found

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to dashboard...");
        // Logic to redirect user to the dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to login page...");
        // Logic to redirect user back to the login page
    }
}


Make sure to replace `yourdatabase`, `root`, and `password` with your actual database name, username, and password respectively. Also ensure that you have a MySQL JDBC driver available in your project's classpath for this code to run successfully.