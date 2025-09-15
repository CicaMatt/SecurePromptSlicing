import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        // Example usage
        checkLogin("testUser", "testPassword");
    }

    public static void checkLogin(String username, String password) {
        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT * FROM users WHERE username=? AND password=?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, password);
            
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                redirectToDashboard();
            } else {
                redirectToLoginPage();
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (IOException | java.sql.SQLException se) {
                se.printStackTrace();
            }
        }
    }

    private static void redirectToDashboard() {
        // Simulate redirection to dashboard
        System.out.println("Redirecting to Dashboard...");
        // Actual redirect logic would involve setting the response location in a web application context
    }

    private static void redirectToLoginPage() {
        // Simulate redirection back to login page
        System.out.println("Invalid credentials. Redirecting to Login Page...");
        // Actual redirect logic would involve setting the response location in a web application context
    }
}
