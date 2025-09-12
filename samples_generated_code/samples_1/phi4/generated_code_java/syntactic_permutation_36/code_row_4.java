import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectToHomePage();
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }

        scanner.close();
    }

    public static boolean login(String username, String password) {
        Connection conn = null;
        PreparedStatement stmt = null;
        
        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();
            
            return rs.next(); // Returns true if a record is found

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
        
        return false;
    }

    public static void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
        // Implement the redirection logic here
        // For example, you can open a new window or change the current view in a GUI application
    }
}


**Note:** Make sure to replace `"your_database"`, `DB_URL`, `USER`, and `PASS` with your actual database name, URL, username, and password. This code assumes you have MySQL set up locally. Adjust the JDBC URL and driver if using another database system. Also, ensure that the MySQL JDBC driver is in your classpath.