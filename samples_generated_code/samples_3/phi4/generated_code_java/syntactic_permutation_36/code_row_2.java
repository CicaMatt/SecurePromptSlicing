import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        // Simulate user input
        String username = "exampleUser";
        String password = "examplePassword";

        boolean loginSuccess = login(username, password);
        
        if (loginSuccess) {
            redirectToHomePage();
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    public static boolean login(String username, String password) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT * FROM users WHERE username = ?";

            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            rs = stmt.executeQuery();

            if (rs.next()) {
                String storedPassword = rs.getString("password");
                return password.equals(storedPassword);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }

        return false;
    }

    public static void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
        // Implement redirection logic here
    }
}


**Note**: Replace `"your_database_name"`, `"your_db_username"`, and `"your_db_password"` with your actual database details. Ensure the MySQL JDBC driver is included in your project's classpath.