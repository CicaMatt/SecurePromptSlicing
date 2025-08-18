import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) throws IOException {
        // Simulated user input
        String username = "testUser";
        String password = "testPass";

        if (authenticate(username, password)) {
            System.out.println("Redirecting to Dashboard...");
            // Redirect to dashboard logic here
        } else {
            System.out.println("Invalid credentials. Redirecting back to Login Page...");
            // Redirect to login page logic here
        }
    }

    private static boolean authenticate(String username, String password) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, password);

            rs = pstmt.executeQuery();

            return rs.next(); // If there's a result, the credentials are correct
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}


**Note**: Replace `your_database`, `root`, and `password` with your actual database name, username, and password. Ensure you have the MySQL JDBC driver in your classpath for this code to run correctly.