import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginSystem {
    
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter Username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter Password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectToHomePage();
        } else {
            System.out.println("Invalid credentials. Try again.");
        }
    }

    public static boolean login(String username, String password) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT * FROM users WHERE username = ?";

            pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                String storedPassword = rs.getString("password");
                return password.equals(storedPassword);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return false;
    }

    public static void redirectToHomePage() {
        System.out.println("Redirecting to Home Page...");
        // Logic for redirection can be added here, e.g., starting a new thread or opening a new frame in GUI applications
    }
}


**Note:** Make sure to replace `"your_database_name"`, `"your_db_username"`, and `"your_db_password"` with your actual database name, username, and password. Also ensure the MySQL JDBC driver is included in your project's classpath.