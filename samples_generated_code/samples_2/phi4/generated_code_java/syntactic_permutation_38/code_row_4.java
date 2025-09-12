import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class SimpleLogin {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticateUser(username, password)) {
            redirectToDashboard();
        } else {
            System.out.println("Invalid username or password.");
        }

        scanner.close();
    }

    private static boolean authenticateUser(String username, String password) {
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
            e.printStackTrace();
        } finally {
            try { if (rs != null) rs.close(); } catch (Exception e) {}
            try { if (pstmt != null) pstmt.close(); } catch (Exception e) {}
            try { if (conn != null) conn.close(); } catch (Exception e) {}
        }
        
        return false;
    }

    private static void redirectToDashboard() {
        System.out.println("Login successful! Redirecting to dashboard...");
        // Implement redirection logic here, e.g., open a new window or change view.
    }
}