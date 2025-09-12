import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkAndUnsubscribe(emailToCheck);
        System.out.println(result);
    }

    public static int checkAndUnsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the email exists
            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkQuery)) {
                checkStmt.setString(1, email);
                ResultSet resultSet = checkStmt.executeQuery();
                int count = 0;
                if (resultSet.next()) {
                    count = resultSet.getInt(1);
                }
            }

            // If email does not exist, return 0
            if (count == 0) {
                return 0;
            }

            // Call unsubscribe script
            boolean unsubscribeResult = callUnsubscribeScript(email);

            // Return based on the result of unsubscribe script
            return unsubscribeResult ? 1 : 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return -1; // Indicate an error occurred
        }
    }

    private static boolean callUnsubscribeScript(String email) {
        // Simulate calling a script to unsubscribe the email
        // In real scenario, this could be a system command or another service call
        System.out.println("Calling unsubscribe script for: " + email);
        
        // For demonstration purposes, assume the script always succeeds
        return true;
    }
}