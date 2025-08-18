import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLogin {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "root"; // Database username
    private static final String PASS = "password"; // Database password

    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);

        System.out.print("Enter Username: ");
        String username = scanner.nextLine();

        System.out.print("Enter Password: ");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            System.out.println("Invalid credentials. Redirecting to login page.");
        }

        scanner.close();
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
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (pstmt != null) pstmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return false;
    }

    private static void redirectToDashboard() {
        System.out.println("Welcome! Redirecting to dashboard...");
        // Here you would typically redirect the user in a web application context.
    }
}


**Note**: Replace `your_database_name`, `root`, and `password` with your actual database name, username, and password. This code assumes that you have a MySQL database running locally on port 3306 and a table named `users` with columns `username` and `password`.