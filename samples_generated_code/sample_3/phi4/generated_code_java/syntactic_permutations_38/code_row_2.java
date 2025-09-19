import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class SimpleLoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }

        scanner.close();
    }

    private static boolean login(String username, String password) {
        String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
        
        try (
            Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
            PreparedStatement pstmt = conn.prepareStatement(sql);
        ) {
            
            pstmt.setString(1, username);
            pstmt.setString(2, password);

            ResultSet rs = pstmt.executeQuery();

            return rs.next();
        } catch (SQLException e) {
            System.err.println("SQL Exception: " + e.getMessage());
            return false;
        }
    }

    private static void redirectToDashboard() {
        System.out.println("Login successful. Redirecting to dashboard...");
        // Logic to redirect to the dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting to login page...");
        // Logic to redirect back to the login page
    }
}


Note: Replace `your_database_name`, `your_db_username`, and `your_db_password` with your actual database details. Ensure that you have a MySQL JDBC driver in your classpath.