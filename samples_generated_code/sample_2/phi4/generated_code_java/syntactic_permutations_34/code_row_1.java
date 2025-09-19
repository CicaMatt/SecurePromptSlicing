import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class LoginApplication {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/userdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter Username:");
        String username = scanner.nextLine();
        
        System.out.println("Enter Password:");
        String password = scanner.nextLine();

        if (authenticateUser(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private static boolean authenticateUser(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username = ? AND password = ?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();
            return rs.next();

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
        // Code to redirect to the dashboard page
    }

    private static void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to Login Page...");
        // Code to redirect back to the login page
    }
}
