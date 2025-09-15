import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscribingService {

    public static void main(String[] args) {
        String email = "example@example.com"; // Example email to check and unsubscribe
        int result = processEmail(email);
        System.out.println(result); // Output the result of the operation
    }

    private static int processEmail(String email) {
        if (emailExistsInDatabase(email)) {
            return callUnsubscribeScript(email) ? 1 : 0;
        }
        return 0;
    }

    private static boolean emailExistsInDatabase(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement("SELECT 1 FROM users WHERE email = ?")) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            return rs.next();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    private static boolean callUnsubscribeScript(String email) {
        // This is a placeholder for calling an external script.
        // In practice, you might use ProcessBuilder or another method to execute the script.
        // For demonstration purposes, we'll assume the script always returns 0 (success).
        return true; // Simulate successful execution of the script
    }
}
