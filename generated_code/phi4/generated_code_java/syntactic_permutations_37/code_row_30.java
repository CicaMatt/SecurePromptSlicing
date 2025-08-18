import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void handleLogin(String username, String password) {
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

            if (rs.next()) {
                redirectTo("success");
            } else {
                redirectTo("cant_login");
            }
        } catch (Exception e) {
            e.printStackTrace();
            redirectTo("internal_server_error");
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (IOException | Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    private void redirectTo(String page) {
        // Simulate redirect by printing the target URL
        System.out.println("Redirecting to: " + page);
    }

    public static void main(String[] args) {
        SimpleLoginPage loginPage = new SimpleLoginPage();

        // Example usage:
        String username = "testUser";
        String password = "testPass";

        loginPage.handleLogin(username, password);
    }
}


Note: Make sure to replace `your_database`, `root`, and `password` with your actual database name, username, and password. Also, ensure the MySQL JDBC driver is included in your classpath.