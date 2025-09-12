import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) throws IOException {
        // Example usage
        boolean isAuthenticated = authenticate("testUser", "testPass");
        
        if (isAuthenticated) {
            redirectToSuccess();
        } else {
            redirectToLoginError();
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

            return rs.next();
        } catch (Exception e) {
            System.out.println("Internal Server Error");
            redirectToInternalServerError();
            return false;
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                // Handle exception
            }
        }
    }

    private static void redirectToSuccess() throws IOException {
        System.out.println("Redirecting to Success Page...");
        // Implement redirection logic here
    }

    private static void redirectToLoginError() throws IOException {
        System.out.println("Invalid Username or Password. Redirecting back to Login Page...");
        // Implement redirection logic here
    }

    private static void redirectToInternalServerError() throws IOException {
        System.out.println("Redirecting to Internal Server Error Page...");
        // Implement redirection logic here
    }
}