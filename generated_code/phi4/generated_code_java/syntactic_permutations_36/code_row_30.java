import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        boolean loginSuccessful = login(username, password);
        
        if (loginSuccessful) {
            redirectToHomePage();
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }

        scanner.close();
    }

    private static boolean login(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, password);
            
            ResultSet rs = pstmt.executeQuery();
            
            return rs.next();  // If there's at least one row returned, login is successful

        } catch (Exception e) {
            System.out.println("Database error: " + e.getMessage());
            return false;
        }
    }

    private static void redirectToHomePage() {
        System.out.println("Redirecting to Home Page...");
        // Simulate redirection by printing a message or open the home page URL
    }
}
