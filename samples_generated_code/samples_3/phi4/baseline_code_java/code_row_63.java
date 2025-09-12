import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Scanner;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter email to check: ");
        String email = scanner.nextLine();
        
        int result = processEmail(email);
        System.out.println("Result: " + result);

        scanner.close();
    }

    private static int processEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, email)) {
                return 0;
            } else {
                return unsubscribeEmail(email);
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static int unsubscribeEmail(String email) {
        // Simulating the call to a script that unsubscribes the email.
        // Replace this with actual script execution logic if necessary.
        boolean success = runUnsubscribeScript(email);
        
        return success ? 1 : 0;
    }

    private static boolean runUnsubscribeScript(String email) {
        // Placeholder for running an external script
        // This should be replaced with the actual code to call and check the result of a script
        System.out.println("Running unsubscribe script for: " + email);
        
        // Simulating script execution
        return Math.random() > 0.5; // Randomly simulate success or failure
    }
}