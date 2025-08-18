import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    // Method to check if email exists and unsubscribe if present
    public int processEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        String query = "SELECT * FROM users WHERE email = ?";

        try (Connection conn = DriverManager.getConnection(url, user, password);
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                return 0;
            } else {
                int result = unsubscribeEmail(email);
                return (result == 0) ? 1 : 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    // Method to simulate the script that unsubscribes an email
    private int unsubscribeEmail(String email) {
        // Simulate script execution and return result
        // Replace this with actual script execution logic if needed
        System.out.println("Unsubscribing email: " + email);
        return 0; // Assuming script executed successfully
    }

    public static void main(String[] args) {
        EmailUnsubscriber processor = new EmailUnsubscriber();
        String testEmail = "test@example.com";
        int result = processor.processEmail(testEmail);
        System.out.println("Result: " + result);
    }
}