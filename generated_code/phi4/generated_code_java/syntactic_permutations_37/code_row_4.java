import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Simulating request parameters
        String username = "testUser";  // Replace with actual input
        String password = "testPass";  // Replace with actual input

        try {
            if (authenticate(username, password)) {
                redirectTo("success");
            } else {
                redirectTo("cant_login");
            }
        } catch (Exception e) {
            redirectTo("internal_server_error");
        }
    }

    private static boolean authenticate(String username, String password) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, password);

            rs = pstmt.executeQuery();

            return rs.next();
        } finally {
            if (rs != null) rs.close();
            if (pstmt != null) pstmt.close();
            if (conn != null) conn.close();
        }
    }

    private static void redirectTo(String page) throws IOException {
        // Simulating a redirect by printing the target page
        System.out.println("Redirecting to: " + page);
        // In an actual web application, you would use response.sendRedirect(page);
    }
}